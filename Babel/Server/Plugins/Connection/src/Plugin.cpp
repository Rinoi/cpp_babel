#include <iostream>
#include <vector>
#include <boost/algorithm/string.hpp>

#include "Plugin.hh"
#include "../../../Network/Session.hpp"
#include "../../../Database/AbsModelBDatabase.hpp"
#include "../../../Database/Models/UserModel.hpp"

namespace Connection
{
  Plugin::Plugin(Babel::Server::Network::IServer *server)
  {
    this->server = server;
    this->max_fct = 4;
    this->list = new fct[this->max_fct];
    this->list[0] = &Plugin::signUp;
    this->list[1] = &Plugin::signIn;
    this->list[2] = &Plugin::logOut;
    this->list[3] = &Plugin::addEvt;
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


  void		Plugin::loadUser(const std::string      &mail		/*in*/,
				 const std::string      &pwd		/*in*/,
				 std::string            &firstName	/*out*/,
				 std::string            &lastName	/*out*/,
				 int                    &idx		/*out*/)
  {
    Babel::Server::Database::BabelDatabase &d = this->server->getDb();
    User	u;
    std::string req("email=:email");

    (void) d;
    u.email = std::string(mail);
    u.password = std::string(pwd);
    u.firstName = "";
    u.lastName = "";
    u.userName = "";
    u.id = 0;
    try {
      d.selectWhere<User>(u, req);
      firstName = u.firstName;
      lastName = u.lastName;
      idx = u.id;
    }
    catch (std::exception const &e)
      {
	std::cerr << "Error: loadUser don't match : " << e.what() << '\n';
      }
  }

  byte		Plugin::createUser(const std::string	&mail		/*in*/,
				   const std::string	&pwd		/*in*/,
				   const std::string	&firstName	/*int*/,
				   const std::string	&lastName	/*in*/,
				   int			&idx		/*out*/)
  {
    User						u;
    Babel::Server::Database::BabelDatabase &d = this->server->getDb();
    std::string					req("email=:email");

    u.firstName = firstName;
    u.lastName = lastName;
    u.password = pwd;
    u.email = mail;
    u.userName = firstName + " " + lastName;
    try {
      d.insert<User>(u);
    }
    catch (std::exception const &e)
      {
	std::cerr << "Error: createUser : email already used : " << e.what() << '\n';
	return (21);
      }
    try {
      d.selectWhere<User>(u, req);
    }
    catch (std::exception const &e)
      {
	std::cerr << "Error: createUser : impossible arrived : " << e.what() << '\n';
      }
    idx = u.id;
    return (1);
  }

  bool		Plugin::signIn(const ::Babel::Common::Network::Packet &p)
  {
    const Babel::Common::Network::Header	header = p.getConstHeader();
    std::string					mail;
    std::string					pwd;
    std::string					firstName;
    std::string					lastName;
    int						idx = 0;
    Babel::Server::Network::ISession		*session;
    std::string					s;
    std::string					c(" ");

    c[0] = 4;
    p.getData();
    s = std::string((const char *)p.getData());
    std::vector<std::string> strs;
    boost::split(strs, s, boost::is_any_of(c.c_str()));
    std::cout << "NBR : " << strs.size() << std::endl;
    Babel::Server::Network::ISession ** pp;

    pp = (Babel::Server::Network::ISession **)(p.getData() + header.dataSize);
    session = (Babel::Server::Network::ISession *)(*pp);
    if (strs.size() != 2)
      {
	Babel::Common::Network::Packet p(header.pluginId, header.actionId, 10, 0, 0, 0, NULL);
	session->writePacket(p);
	//send packet error general
	return (false);
      }
    std::cout << session << " " << pp << std::endl;
    mail = strs[0];
    pwd = strs[1];
    this->loadUser(mail, pwd, firstName, lastName, idx);
    if (idx > 0) // si sa match
      {
	session->leaveAnonymousRoom();
	session->joinConnectedRoom(idx); //LOOOOOL
	std::string	s;

	s += firstName;
	s += (char)(4);
	s += lastName;

	Babel::Common::Network::Packet p(header.pluginId, header.actionId, 1, 0, idx,
					 s.size() + 1, (byte *)(s.c_str()));
	this->server->send(p);
	this->sendToEvent(1, idx, session);
	return (true);
      }
    else
      {
	Babel::Common::Network::Packet p(header.pluginId, header.actionId, 21, 0, 0, 0, NULL);
	session->writePacket(p);
	//send packet error
      }
    return (true);
  }

  bool		Plugin::signUp(const ::Babel::Common::Network::Packet &p)
  {
    const Babel::Common::Network::Header	header = p.getConstHeader();
    std::string					mail;
    std::string					pwd;
    std::string					firstName;
    std::string					lastName;
    int						idx = 0;
    Babel::Server::Network::Session		*session;
    std::string					s;
    std::string					c;

    c += (char)(4);
    p.getData();
    s = std::string((const char *)p.getData());
    std::vector<std::string> strs;
    boost::split(strs, s, boost::is_any_of(c.c_str()));
    Babel::Server::Network::Session ** pp;

    pp = (Babel::Server::Network::Session **)(p.getData() + header.dataSize);
    session = (Babel::Server::Network::Session *)(*pp);
    if (strs.size() != 4)
      {
	Babel::Common::Network::Packet p(header.pluginId, header.actionId, 10, 0, 0, 0, NULL);
	session->writePacket(p);
	//send packet error general
	return (false);
      }
    firstName = strs[0];
    lastName = strs[1];
    mail = strs[2];
    pwd = strs[3];

    byte	r;

    r = this->createUser(mail, pwd, firstName, lastName, idx);
    if (idx == 0)
      {
	Babel::Common::Network::Packet p(header.pluginId, header.actionId, r, 0, 0, 0, NULL);
	session->writePacket(p);
	return (false);
      }
    else
      {
	Babel::Common::Network::Packet p(header.pluginId, header.actionId, 1, 0, 0, 0, NULL);
	session->writePacket(p);
      }
    return (true);
  }

  bool		Plugin::logOut(const ::Babel::Common::Network::Packet &p)
  {
    const Babel::Common::Network::Header	header = p.getConstHeader();

    this->sendToEvent(2, header.senderId, NULL);
    return (true);
  }

  bool		Plugin::addEvt(const ::Babel::Common::Network::Packet &p)
  {
    const Babel::Common::Network::Header	header = p.getConstHeader();
    const byte					*data;
    byte					op;
    byte					type;
    t_plugin_event				st;

    if (header.dataSize != 2)
      return (false);
    data = p.getData();
    type = *data;
    op = *(data + 1);
    st.plugin = header.pluginId;
    st.op = op;
    if (type == 1 || type == 3)
	this->eventSignIn.push_front(st);
    if (type == 2 || type == 3)
      this->eventLogOut.push_front(st);
    return (true);
  }

  void		Plugin::sendToEvent(int flag, int idx, void *p)
  {
    if (1 > flag && flag < 2)
      return ;

    (void) idx;
    std::list<t_plugin_event>::iterator	it;

    it = flag == 1 ? this->eventSignIn.begin() : this->eventLogOut.begin();
    while (it != (flag == 1 ? this->eventSignIn.end() : this->eventLogOut.end())) //ofc is very . . . strange
      {
	byte				*data;

	if ((*it).plugin == this->server->getPluginId("contact"))
	  {
	    data = new byte[sizeof(int) + sizeof(void *)];
	    *(void **)(data + sizeof(int)) = p;
	  }
	else
	    data = new byte[sizeof(int)];
	*((int *)(data)) = idx;

	Babel::Common::Network::Packet	p((*it).plugin, (*it).op, 0, 0, 0,
					 sizeof(int), data);
	this->server->send(p);
	++it;
      }
  }
  
}
