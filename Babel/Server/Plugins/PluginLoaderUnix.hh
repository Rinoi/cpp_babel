
#ifndef __PLUGIN__LOADER_UNIX__
# define __PLUGIN__LOADER_UNIX__

# include "AServerPlugin.hpp"
# include "IPluginLoader.hpp"
#include	"../Network/Server.hpp"

namespace Babel
{
  namespace Server
  {
    namespace Plugin
    {

      typedef AServerPlugin   *(*ftc_plugin)(Babel::Server::Network::Server *server);


      class PluginLoaderUnix : public IPluginLoader
      {
      public:
	PluginLoaderUnix(Babel::Server::Network::Server *server);
	~PluginLoaderUnix();

	AServerPlugin   *Load(const std::string &name);

      private:

	Babel::Server::Network::Server *server;

      };
    }
  }
}

#endif
