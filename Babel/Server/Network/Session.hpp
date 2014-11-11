#ifndef					__SESSION_HPP__
#define					__SESSION_HPP__

#include			        <boost/asio.hpp>
#include				"Room.hpp"
#include				"ISession.hpp"
#include				"../../Common/Network/Packet.hpp"

using					boost::asio::ip::tcp;

namespace				Babel
{

  namespace				Server
  {

    namespace				Network
    {

      class				Session : public std::enable_shared_from_this<Session>, public ISession
      {
	
      public:
	
	Session(tcp::socket, Room &);
	~Session();
	
      public:
	
	void				start();
	void				readPacket();
	void				writePacket(const Babel::Common::Network::Packet &);
	void                            joinConnectedRoom(unsigned int);
        void                            leaveAnonymousRoom();

      public:
	
	Room &				getRoom();
	
      private:
	
	tcp::socket			_socket;
	Babel::Common::Network::Packet	_packet;
	Room				&_room;
	
      };
      
    }
    
  }
  
}
  
#endif
