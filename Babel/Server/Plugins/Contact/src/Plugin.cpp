#include <iostream>
#include <vector>
#include <boost/algorithm/string.hpp>

#include "Plugin.hh"
#include "Session.hpp"
#include "AbsModelBDatabase.hpp"
#include "UserModel.hpp"

namespace Contact
{
  Plugin::Plugin(Babel::Server::Network::Server *server)
  {
    this->name = "contact";
    this->server = server;
    this->max_fct = 4;
    this->list = new fct[this->max_fct];
    this->list[0] = &Plugin::logIn;
    this->list[1] = &Plugin::logOut;
    this->list[2] = &Plugin::addFriend;
    this->list[3] = &Plugin::deleteFriend;
  }

  Plugin::~Plugin()
  {

  }

  bool			Plugin::init()
  {
    int		idx;
    
    idx = this->server->getPluginId("connection");
    if (idx == 0)
      return (false);

    {
      byte				*data;

      data = new byte[sizeof(byte) * 2];
      *(byte *)(data) = (byte)(1);
      *(byte *)(data + 1) = (byte)(1);
      Babel::Common::Network::Packet	p(idx, 4, 0, 0, 0, sizeof(int), data);
      this->server->send(p);
    }

    {
      byte				*data;

      data = new byte[sizeof(byte) * 2];
      *(byte *)(data) = (byte)(2);
      *(byte *)(data + 1) = (byte)(2);
      Babel::Common::Network::Packet	p(idx, 4, 0, 0, 0, sizeof(int), data);
      this->server->send(p);
    }
    return (true);
  }

  bool			Plugin::handlePacket(const ::Babel::Common::Network::Packet &p)
  {
    const Babel::Common::Network::Header	header = p.getConstHeader();
    int						idx;

    idx = header.actionId;
    if (idx > this->max_fct)
      return (false);
    else
      (this->*list[idx - 1])(p);
    return (true);
  }

  bool			Plugin::logIn(const ::Babel::Common::Network::Packet &p)
  {
    auto		header = p.getConstHeader();
    int			idx;
    std::list<int>	list;

    if (header.senderId != 0)
      return (false);
    idx = *(const int *)(p.getData());
    list = getFriendsList(idx);
    this->sendFriendsList(idx, list);
    this->changeStatus(idx, true);
    this->notifFriend(1, idx, list);
    return (true);
  }

  bool			Plugin::logOut(const ::Babel::Common::Network::Packet &p)
  {
    auto		header = p.getConstHeader();
    int			idx;
    std::list<int>	list;
    
    if (header.senderId != 0)
      return (false);
    idx = *(const int *)(p.getData());
    this->changeStatus(idx, false);
    this->notifFriend(2, idx);
    return (true);
  }

  bool			Plugin::addFriend(const ::Babel::Common::Network::Packet &p)
  {
    (void) p;
    return (true);
  }

  bool			Plugin::deleteFriend(const ::Babel::Common::Network::Packet &p)
  {
    (void) p;
    return (true);
  }

  bool			Plugin::sendFriendsList(int idx)
  {
    std::list<int>	list;

    list = getFriendsList(idx);
    return (this->sendFriendsList(idx, list));
  }

  bool			Plugin::sendFriendsList(int idx, const std::list<int> &list)
  {
    auto		it = list.begin();
    unsigned int	size;
    std::string		name;
    byte		*data;
    byte		*tmp;

    size = 0;
    while (it != list.end())
      {
	size += sizeof(int) + this->getName(*it).size() + 1;
	++it;
      }
    size += sizeof(int)/*id*/;
    size += sizeof(int)/*nb friend*/;
    size += sizeof(byte) * name.size() + 1/*name*/;
    data = new byte[size];
    tmp = data;

    *(int *)(data) = idx;
    *(unsigned int *)(data) = list.size();
    data += sizeof(int) * 2;
    for (unsigned int i = 0; i <= name.size(); i += 1)
      data[i] = name[i];
    data += name.size() + 1;

    // send Friend LIst
    it = list.begin();
    while (it != list.end())
      {
	std::string s;

	s = this->getName(*it);
	*(int *)(data) = *it; //id
	data += sizeof(int);
	// we need status
	for (unsigned int i = 0; i <= name.size(); i += 1) //name
	  *data++ = name[i];
	
	++it;
      }
    Babel::Common::Network::Packet	p(this->id, 1, 0, 0, idx, size, tmp);
    this->server->send(p);
    
    return (true);
  }

  bool			Plugin::notifFriend(int act, int idx)
  {
    std::list<int>	list;

    list = getFriendsList(idx);
    return (this->notifFriend(act, idx, list));
  }

  bool			Plugin::notifFriend(int act, int idx, const std::list<int> &list)
  {
    auto		it = list.begin();
    std::string		name;
    unsigned int	size;

    name = this->getName(idx);
    size = sizeof(byte) + sizeof(int) + sizeof(char) * (name.size() + 1);
    while (it != list.end())
      {
	byte		*data = new byte[size];

	*data = (byte)(act);
	*((int *)(data + 1)) = idx;
	for (unsigned int i = 0; i <= name.size(); i += 1)
	  data[i + 1 + sizeof(int)] = name[i];
	Babel::Common::Network::Packet	p(this->id, 2, 0, 0, *it, size, data);
	this->server->send(p);
	++it;
      }
    return (true);
  }

  //FONCTION A FAIRE ! ! ! ! ! !


  bool			Plugin::changeStatus(int idx, bool status)
  {
    (void) idx;
    (void) status;
    //change status;
    return (true);
  }

  std::list<int>       	Plugin::getFriendsList(int idx)
  {
    std::list<int>	list;

    (void) idx;
    return (list);
  }

  std::string		Plugin::getName(int idx)
  {
    std::string		name;

    (void) idx;
    return (name);
  }

}
