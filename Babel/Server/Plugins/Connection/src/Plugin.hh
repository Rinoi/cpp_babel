#ifndef __PLUGIN__CONNECTION__
#define __PLUGIN__CONNECTION__

#include <iostream>
#include <list>

#include "../../AServerPlugin.hpp"
#include "../../../Network/Server.hpp"

namespace Connection
{
  
  class Plugin;

  typedef bool	(Plugin::*fct) (const Babel::Common::Network::Packet &p);
  
  class Plugin : public Babel::Server::Plugin::AServerPlugin
  {

  public:
    typedef struct	s_plugin_event
    {
      byte		plugin;
      byte		op;
    } t_plugin_event;

  public:
    Plugin(Babel::Server::Network::Server *server);
    ~Plugin();

    bool				init();
    
    bool				handlePacket(const ::Babel::Common::Network::Packet &);

  private:

    bool				signUp(const ::Babel::Common::Network::Packet &);
    bool				signIn(const ::Babel::Common::Network::Packet &);
    bool				logOut(const ::Babel::Common::Network::Packet &);
    bool				addEvt(const ::Babel::Common::Network::Packet &);

  private:

    void				sendToEvent(int flag, int idx, void *p);
    void				loadUser(const std::string	&mail		/*in*/,
						 const std::string	&pwd		/*in*/,
						 std::string		&firstName	/*out*/,
						 std::string		&lastName	/*out*/,
						 int			&idx		/*out*/);

    byte				createUser(const std::string    &mail           /*in*/,
						   const std::string    &pwd            /*in*/,
						   const std::string    &firstName      /*int*/,
						   const std::string    &lastName       /*in*/,
						   int                  &idx            /*out*/);


  private:

    std::list<t_plugin_event>		eventSignIn;
    std::list<t_plugin_event>		eventLogOut;
    fct					*list;
    int					max_fct;
    Babel::Server::Network::Server *	server;


  };

}

#endif
