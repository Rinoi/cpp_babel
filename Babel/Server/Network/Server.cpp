#include					"Server.hpp"
#include					"../../Common/Network/Packet.hpp"
#include					"../../Common/Network/PacketManager.hpp"
#include					"../Plugins/PluginModel.hpp"

#include					<boost/predef.h>
# if BOOST_OS_WINDOWS
#  include "../Plugins/PluginLoaderWindows.hh"
# else
#  include					"../Plugins/PluginLoaderUnix.hh"
# endif // BOOST_OS_WINDOWS

namespace					Babel
{
  
  namespace					Server
  {

    namespace					Network
    {
      
      Server::Server() : _db(Babel::Server::Database::BabelDatabase::getInstance())
      {
	std::cout << "[SERVER] : Construction of the server." << std::endl;//////////////////////////
	//if windows...
#if BOOST_OS_WINDOWS
	this->_pluginLoader = new Babel::Server::Plugin::PluginLoaderWindows(this);
#else
	this->_pluginLoader = new Babel::Server::Plugin::PluginLoaderUnix(this);
#endif
	this->initPlugins();
      }
      
      Server::~Server()
      {
	std::cout << "[SERVER] : Destruction of the server." << std::endl;//////////////////////////		
      }

      void					Server::run()
      {
	this->_core.run();
      }

      Core &					Server::getCore()
      {
	return (this->_core);
      }

      Babel::Server::Database::BabelDatabase &	Server::getDb()
      {
	return (this->_db);
      }

      void					Server::addChannel(const unsigned short int &port)
      {
	this->_core.addChannel(port);
      }

      void					Server::initPlugins()
      {
	Babel::Server::Plugin::AServerPlugin				*plugin;
	std::string				req("SELECT * FROM plugin");
	try {

		soci::rowset<PluginModel>		plugins = this->_db.selectMulti<PluginModel>(req);

	std::cout << "[SERVER] : Loading plugins." << std::endl;//////////////////////////
	for (auto it = plugins.begin(); it != plugins.end(); it++)
	  {
	    plugin = this->_pluginLoader->Load("./Plugins/" + it->name + "/plugin" + it->name);
	    if (plugin != NULL)
	      {
		this->_plugins[it->id] = plugin;
		std::cout << it->name << " (" << plugin->getName() << ")" << std::endl;
	      }
		else
		{
			std::cerr << it->name << " can't be loaded" << std::endl;
		}

	  }
	this->_connection_plugin = 1;
	this->_signup_action = 1;
	this->_signin_action = 2;
	}
	catch (soci::soci_error e)
	{
		std::cout << e.what() << std::endl;
	}

      }
      
      void					Server::send(const Common::Network::Packet &packet)
      {
	std::map<unsigned int, Session *>	participants;
	unsigned int				receiverId;
	Session					*session;

	receiverId = packet.getConstHeader().receiverId;
	if (receiverId == 0)
	  {
	    Babel::Common::Network::PacketManager::getInstance()->addPacket(packet, NULL);
	  }
	else
	  {
	    for (auto channel_iterator = this->_core.getChannels().begin(), channel_end = this->_core.getChannels().end(); channel_iterator != channel_end; ++channel_iterator)
	      {
		participants = (*channel_iterator).getRoom().getConnectedParticipants();
		if (participants.find(receiverId) != participants.end())
		  {
		    session = participants[receiverId];
		    session->writePacket(packet);
		  }
	      }
	  }
      }
      
      void					Server::handlePacket()
      {
	Babel::Common::Network::Packet		packet;
	boost::unique_lock<boost::mutex>	lock(Babel::Common::Network::PacketManager::getInstance()->getMutex());
	int					i;
	byte					*data;
	void					*ptr;

	while (1)
	  {
	    if (Babel::Common::Network::PacketManager::getInstance()->getPackets().size() > 0)
	      {
		packet = Babel::Common::Network::PacketManager::getInstance()->getPackets().front().first;
		if (packet.getHeader().pluginId == this->_connection_plugin
		    && (packet.getHeader().actionId == this->_signup_action || packet.getHeader().actionId == this->_signin_action))
		  {
		    i = 0;
		    data = new byte[packet.getDataSize() + sizeof(void *)];
		    while (i < packet.getDataSize())
		      {
			data[i] = packet.getData()[i];
			i = i + 1;
		      }
		    ptr = (void *)(data + i);
		    std::cout << "ptr : " << ptr << std::endl;
		    std::cout << (void *)(Babel::Common::Network::PacketManager::getInstance()->getPackets().front().second) << std::endl;
		    std::cout << "NBR " << packet.getConstHeader().dataSize << std::endl;
		    *((void **)(ptr)) = (void *)(Babel::Common::Network::PacketManager::getInstance()->getPackets().front().second);
		    delete [] packet.getData();
		    packet.setData(data);
		  }
		if (this->_plugins.find((int)packet.getHeader().pluginId) != this->_plugins.end())
		  {
		    this->_plugins[(int)packet.getHeader().pluginId]->handlePacket(packet);
		  }
		delete [] packet.getData();
		Babel::Common::Network::PacketManager::getInstance()->getPackets().pop();
	      }
	      else
		Babel::Common::Network::PacketManager::getInstance()->getCondvar().wait(lock);
	  }
      }

      byte					Server::getPluginId(const std::string &s)
      {
	auto					it = this->_plugins.begin();

	while (it != this->_plugins.end())
	  {
	    if (it->second->getName() == s)
	      return (it->first);
	    ++it;
	  }
	return (0);
      }
      
    }

  }

}
