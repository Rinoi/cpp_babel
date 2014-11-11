#include <iostream>
#include "Plugin.hh"
#include "Server.hpp"

extern "C"
{
  Babel::Server::Plugin::AServerPlugin	*getPlugin(Babel::Server::Network::IServer *server)
  {
    return (new Message::Plugin(server));
  }
}
