#include <iostream>
#include "Plugin.hh"
#include "../../../Network/Server.hpp"
#include "boost/predef.h"

#if BOOST_OS_WINDOWS
# define DLL_EXPORT __declspec(dllexport)
#else
# define DLL_EXPORT
#endif

extern "C"
{
	DLL_EXPORT Babel::Server::Plugin::AServerPlugin	*getPlugin(Babel::Server::Network::IServer *server)
  {
    return (new Connection::Plugin(server));
  }
}
