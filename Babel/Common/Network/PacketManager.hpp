#ifndef		      					__PACKET_MANAGER_HPP__
#define	      						__PACKET_MANAGER_HPP__

#include		     				<cstdlib>
#include       						<queue>
#include						<boost/thread/mutex.hpp>
#include						<boost/thread/thread.hpp>
#include	       					"Packet.hpp"
#include							"../../Server/Network/Session.hpp"

using namespace Babel::Server::Network;

namespace			      			Babel
{

  namespace				       		Common
  {

    namespace						Network
    {

      class					 	PacketManager
      {
	
      private:
	
	PacketManager();
	~PacketManager();
	
      public:
	
	static PacketManager   				*getInstance();
	
      public:
	
	void			      			addPacket(const Packet &, Session *);
	std::queue<std::pair<Packet, Session *> > &	getPackets();
	boost::mutex &					getMutex();
	boost::condition_variable &    			getCondvar();
	
      private:
	
	static PacketManager		       		*_packetManager;
	std::queue<std::pair<Packet, Session *> >      	_packets;
	boost::condition_variable			_condvar;
	boost::mutex					_mutex;
	
      };
      
    }
    
  }
  
}

#endif
