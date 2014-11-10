#ifndef									__SERVER_HPP__
#define									__SERVER_HPP__

#include								<list>
#include								"Core.hpp"
#include								"../Plugins/IPluginLoader.hpp"
#include								"../Plugins/AServerPlugin.hpp"
#include								"../Database/AbsModelBDatabase.hpp"

namespace								Babel
{
  
  namespace								Server
  {
    
    namespace								Network
    {
      
      class								Server
      {
	
      public:
	
	Server();
	~Server();
	
      public:

	void								run();
	void								addChannel(const unsigned short int &);
	void								handlePacket();
	void								initPlugins();
      	void								send(const Common::Network::Packet &);
	byte								getPluginId(const std::string &);

      public:

	Core &								getCore();
	Babel::Server::Database::BabelDatabase &			getDb();
	
      private:

	Core								_core;
	byte								_connection_plugin;
	byte								_signup_action;
	byte								_signin_action;
	std::map<short int, Babel::Server::Plugin::AServerPlugin *>	_plugins;
	Babel::Server::Database::BabelDatabase				&_db;
	Babel::Server::Plugin::IPluginLoader    	       		*_pluginLoader;
	
      };
      
    }

  }

}

#endif
