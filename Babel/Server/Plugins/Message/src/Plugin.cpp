#include <iostream>
#include <vector>
#include <boost/algorithm/string.hpp>

#include "Plugin.hh"
#include "Session.hpp"
#include "AbsModelBDatabase.hpp"
#include "UserExample.hpp"
#include "MsgModel.hpp"

namespace Message
{
  Plugin::Plugin(Babel::Server::Network::Server *server)
  {
    this->server = server;
    this->max_fct = 1;
    this->list = new fct[this->max_fct];
    this->list[0] = &Plugin::manageMsg;
  }

  Plugin::~Plugin()
  {

  }

  bool		Plugin::init()
  {
    return (true);
  }

  bool		Plugin::handlePacket(const ::Babel::Common::Network::Packet &p)
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

  bool		Plugin::manageMsg(const ::Babel::Common::Network::Packet &p)
  {
    int		id;
    std::string	ms;
    const byte	*d;
    Babel::Server::Database::BabelDatabase &b = this->server->getDb();
    Msg		m;

    d = p.getData();
    id = *((const int *)(d));
    ms = std::string(((const char*)(d+sizeof(int))));
    m.from = (p.getConstHeader()).senderId;
    m.to = id;
    m.content = ms;
    b.insert<Msg>(m);
    Babel::Common::Network::Packet  np(this->id, 1, 0, 0, id,
				       ms.size(), (byte*)(ms.c_str()));
    this->server->send(np);
    return true;
  }
}
