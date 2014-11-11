#include	"Session.hpp"
#include	"../../Common/Network/PacketManager.hpp"

namespace	Babel
{
  
  namespace	Server
  {
    
    namespace	Network
    {
      
      Session::Session(tcp::socket socket, Room &room) :
	_socket(std::move(socket)), _room(room)
      {
	std::cout << "[SESSION] : Construction of a new session for the participant." << std::endl;//////////////////////////
      }
      
      Session::~Session()
      {
	std::cout << "[SESSION] : Destruction of a session." << std::endl;//////////////////////////
      }
      
      void	Session::start()
      {
	std::cout << "[SESSION] : Starting the session for the new participant." << std::endl;//////////////////////////
	this->_room.joinAnonymous(this);
	this->readPacket();
      }

      void                            Session::joinConnectedRoom(unsigned int id)
      {
	this->_room.joinConnected(this, id);
      }

      void                            Session::leaveAnonymousRoom()
      {
	this->_room.leaveAnonymous(this);
      }
      
      void	Session::readPacket()
      {
	byte	*data;
	auto	self(shared_from_this());
	
	std::cout << "[SESSION] : Reading a header from a participant." << std::endl;//////////////////////////	
	boost::asio::async_read(this->_socket,
				boost::asio::buffer(&this->_packet.getHeader(), this->_packet.getHeaderSize()),
				[this, self, &data](boost::system::error_code ec, std::size_t)
				{
				  std::cout << "[SESSION] : Header received from a participant." << std::endl;//////////////////////////
				  if (!ec && this->_packet.isHeaderValid())
				    {
				      data = new byte[this->_packet.getDataSize()];//delete
				      this->_packet.setData(data);
				      std::cout << "[SESSION] : Reading a body from a participant." << std::endl;//////////////////////////
				      boost::asio::async_read(this->_socket,
							      boost::asio::buffer(data, this->_packet.getDataSize()),
							      [this, self](boost::system::error_code ec, std::size_t)
							      {
								std::cout << "[SESSION] : Body received from a participant." << std::endl;//////////////////////////
								if (!ec)
								  {
								    std::cout << "[SESSION] : Data : [" << this->_packet.getData() << "]" << std::endl;//////////////////////////
								    Babel::Common::Network::PacketManager::getInstance()->addPacket(this->_packet, this);
								    //std::cout << "NBR OF PACKET ALREADY RECEIVED : " << Babel::Network::PacketManager::getInstance()->getPackets().size() << std::endl;   
								    return (this->readPacket());
								  }
								else
								  {
								    //this->_room.leave(shared_from_this());
								  }
							      });
				      
				    }
				  else
				    {
				      //				      this->_room.leave(shared_from_this());
				    }
				});
      }
      
      void	Session::writePacket(const Babel::Common::Network::Packet & packet)
      {
	auto	self(shared_from_this());
	
	std::cout << "[SESSION] : Writing a header to a participant." << std::endl;//////////////////////////	
	boost::asio::async_write(this->_socket,
				 boost::asio::buffer(&packet.getConstHeader(), packet.getHeaderSize()),
				 [this, self, packet](boost::system::error_code ec, std::size_t)
				 {
				   if (!ec)
				     {
				       std::cout << "[SESSION] : Header wrote to a participant." << std::endl;//////////////////////////
				       std::cout << "[SESSION] : Writing a body to a participant." << std::endl;/////////////////////
				       std::cout << "[SESSION] : receiverId : " << packet.getConstHeader().receiverId << " size : " << packet.getConstHeader().dataSize << std::endl;/////////////////////
				       boost::asio::async_write(this->_socket,
								boost::asio::buffer(packet.getData(), packet.getDataSize()),
								[this, self](boost::system::error_code ec, std::size_t)
								{
								  if (!ec)
								    {
								      std::cout << "[SESSION] : Body wrote to a participant." << std::endl;////////////////////////
								    }
								  else
								    {
								      //                                       this->_room.leave(shared_from_this());
								    }
								});
				       
				     }
				   else
				     {
				       //				       this->_room.leave(shared_from_this());
				     }
				 });
      }

      Room &		Session::getRoom()
      {
	return (this->_room);
      }

    }
    
  }
  
}
