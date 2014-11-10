
#ifndef __PLUGIN__LOADER_WINDOWS__
# define __PLUGIN__LOADER_WINDOWS__

# include "AServerPlugin.hpp"
# include "IPluginLoader.hpp"
#include	"../Network/Server.hpp"

namespace Babel
{
  namespace Server
  {
    namespace Plugin
    {

		typedef AServerPlugin	*(*getPluginFuncPtr)(Babel::Server::Network::Server *server);

		class PluginLoaderWindows : public IPluginLoader
		{
		public:
			PluginLoaderWindows(Babel::Server::Network::Server *server) : _server(server) {}
			~PluginLoaderWindows() {}

			AServerPlugin   *Load(const std::string &name);

		private:
			Babel::Server::Network::Server *_server;

      };
    }
  }
}

#endif
