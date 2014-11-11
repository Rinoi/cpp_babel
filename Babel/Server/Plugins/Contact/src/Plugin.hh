#ifndef __PLUGIN__CONTACT__
#define __PLUGIN__CONTACT__

#include <iostream>
#include <list>

#include "AServerPlugin.hpp"
#include "IServer.hpp"

namespace Contact
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
    Plugin(Babel::Server::Network::IServer *server);
    ~Plugin();

    bool				init();
    
    bool				handlePacket(const ::Babel::Common::Network::Packet &);

  private:

    bool				logIn(const ::Babel::Common::Network::Packet &);
    bool				logOut(const ::Babel::Common::Network::Packet &);

    bool				addFriend(const ::Babel::Common::Network::Packet &);
    bool				deleteFriend(const ::Babel::Common::Network::Packet &);

  private:

    std::list<int>			getFriendsList(int idx);

    bool				sendFriendsList(int idx);
    bool				sendFriendsList(int idx, const std::list<int> &list);

    bool				notifFriend(int act, int idx);
    bool				notifFriend(int act, int idx, const std::list<int> &list);

    bool				changeStatus(int idx, bool status);

    std::string				getName(int idx);

  private:

    fct					*list;
    int					max_fct;
    Babel::Server::Network::IServer *	server;


  };

}

#endif
