#pragma once
#include <appbase/plugin.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/core/demangle.hpp>
#include <boost/asio.hpp>

namespace appbase {
   namespace bpo = boost::program_options;
   namespace bfs = boost::filesystem;

   class application
   {
      public:
         ~application();

         /** @brief Set version
          *
          * @param version Version output with -v/--version
          */
         void set_version(uint64_t version);
         /** @brief Get version
          *
          * @return Version output with -v/--version
          */
         uint64_t version() const;
         /** @brief Set default data directory
          *
          * @param data_dir Default data directory to use if not specified
          *                 on the command line.
          */
         void set_default_data_dir(const bfs::path& data_dir = "data-dir");
         /** @brief Get data directory
          *
          * @return Data directory, possibly from command line
          */
         bfs::path data_dir() const;
         /** @brief Set default config directory
          *
          * @param config_dir Default configuration directory to use if not
          *                   specified on the command line.
          */
         void set_default_config_dir(const bfs::path& config_dir = "etc");
         /** @brief Get config directory
          *
          * @return Config directory, possibly from command line
          */
         bfs::path config_dir() const;
         /** @brief Get logging configuration path.
          *
          * @return Logging configuration location from command line
          */
         bfs::path get_logging_conf() const;
         /**
          * @brief Looks for the --plugin commandline / config option and calls initialize on those plugins
          *
          * @tparam Plugin List of plugins to initalize even if not mentioned by configuration. For plugins started by
          * configuration settings or dependency resolution, this template has no effect.
          * @return true if the application and plugins were initialized, false or exception on error
          */
         template<typename... Plugin>
         bool                 initialize(int argc, char** argv) {
            return initialize_impl(argc, argv, {find_plugin<Plugin>()...});
         }

         void                  startup();
         void                  shutdown();

         /**
          *  Wait until quit(), SIGINT or SIGTERM and then shutdown
          */
         void                 exec();
         void                 quit();

         static application&  instance();

         abstract_plugin* find_plugin(const string& name)const;
         abstract_plugin& get_plugin(const string& name)const;

         template<typename Plugin>
         auto& register_plugin() {
            auto existing = find_plugin<Plugin>();
            if(existing)
               return *existing;

            auto plug = new Plugin();
            plugins[plug->name()].reset(plug);
            plug->register_dependencies();
            return *plug;
         }

         template<typename Plugin>
         Plugin* find_plugin()const {
            string name = boost::core::demangle(typeid(Plugin).name());
            return dynamic_cast<Plugin*>(find_plugin(name));
         }

         template<typename Plugin>
         Plugin& get_plugin()const {
            auto ptr = find_plugin<Plugin>();
            return *ptr;
         }

         boost::asio::io_service& get_io_service() { return *io_serv; }
      protected:
         template<typename Impl>
         friend class plugin;

         bool initialize_impl(int argc, char** argv, vector<abstract_plugin*> autostart_plugins);

         /** these notifications get called from the plugin when their state changes so that
          * the application can call shutdown in the reverse order.
          */
         ///@{
         void plugin_initialized(abstract_plugin& plug){ initialized_plugins.push_back(&plug); }
         void plugin_started(abstract_plugin& plug){ running_plugins.push_back(&plug); }
         ///@}

      private:
         application(); ///< private because application is a singleton that should be accessed via instance()
         map<string, std::unique_ptr<abstract_plugin>> plugins; ///< all registered plugins
         vector<abstract_plugin*>                  initialized_plugins; ///< stored in the order they were started running
         vector<abstract_plugin*>                  running_plugins; ///< stored in the order they were started running
         std::shared_ptr<boost::asio::io_service>  io_serv;

         void set_program_options();
         void write_default_config(const bfs::path& cfg_file);
         void print_default_config(std::ostream& os);
         std::unique_ptr<class application_impl> my;

   };

   application& app();


   template<typename Impl>
   class plugin : public abstract_plugin {
      public:
         plugin():_name(boost::core::demangle(typeid(Impl).name())){}
         virtual ~plugin(){}

         virtual state get_state()const override         { return _state; }
         virtual const std::string& name()const override { return _name; }

         virtual void register_dependencies() {
            static_cast<Impl*>(this)->plugin_requires([&](auto& plug){});
         }

         virtual void initialize(const variables_map& options) override {
            if(_state == registered) {
               _state = initialized;
               static_cast<Impl*>(this)->plugin_requires([&](auto& plug){ plug.initialize(options); });
               static_cast<Impl*>(this)->plugin_initialize(options);
               //ilog( "initializing plugin ${name}", ("name",name()) );
               app().plugin_initialized(*this);
            }
            assert(_state == initialized); /// if initial state was not registered, final state cannot be initiaized
         }

         virtual void startup() override {
            if(_state == initialized) {
               _state = started;
               static_cast<Impl*>(this)->plugin_requires([&](auto& plug){ plug.startup(); });
               static_cast<Impl*>(this)->plugin_startup();
               app().plugin_started(*this);
            }
            assert(_state == started); // if initial state was not initialized, final state cannot be started
         }

         virtual void shutdown() override {
            if(_state == started) {
               _state = stopped;
               //ilog( "shutting down plugin ${name}", ("name",name()) );
               static_cast<Impl*>(this)->plugin_shutdown();
            }
         }

      protected:
         plugin(const string& name) : _name(name){}

      private:
         state _state = abstract_plugin::registered;
         std::string _name;
   };
}
