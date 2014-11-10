#include						"PacketManager.hpp"

namespace						Babel
{

  namespace						Common
  {

    namespace						Network
    {
      
      PacketManager					*PacketManager::_packetManager = NULL;
      
      PacketManager::PacketManager()
      {
	
      }
      
      PacketManager::~PacketManager()
      {
	
      }
      
      PacketManager					*PacketManager::getInstance()
      {
	if (PacketManager::_packetManager == NULL)
	  {
	    PacketManager::_packetManager = new PacketManager();
	  }
	return (PacketManager::_packetManager);
	
      }
      
      void						PacketManager::addPacket(const Packet &packet, Session *session)
      {
	boost::lock_guard<boost::mutex>			lock(this->_mutex);

	this->_packets.push(std::make_pair(packet, session));
	this->_condvar.notify_one();
      }
      
      std::queue<std::pair<Packet, Session *>> &	PacketManager::getPackets()
      {
	return (this->_packets);
      }
      
      boost::mutex &					PacketManager::getMutex()
      {
	return (this->_mutex);
      }
      
      boost::condition_variable &			PacketManager::getCondvar()
      {
	return (this->_condvar);
      }
      
    }
    
  }

}
