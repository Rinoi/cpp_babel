
#ifndef __MESSAGE_PLUGIN__
#define __MESSAGE_PLUGIN__

#include <iostream>
#include <list>

#include "AServerPlugin.hpp"
#include "IServer.hpp"

namespace Message
{
  
  class Plugin;

  typedef bool	(Plugin::*fct) (const Babel::Common::Network::Packet &p); // ???
  
  class Plugin : public Babel::Server::Plugin::AServerPlugin
  {

  public:
    typedef struct	s_plugin_event
    {
      byte		plugin;
      byte		op;
    } t_plugin_event;

    Plugin(Babel::Server::Network::IServer *server);
    ~Plugin();

    bool				init();
    
    bool				handlePacket(const ::Babel::Common::Network::Packet &);

  private:

    bool				manageMsg(const ::Babel::Common::Network::Packet &);
    

    fct					*list;
    int					max_fct;
    Babel::Server::Network::IServer *	server;

  };

}


#endif
