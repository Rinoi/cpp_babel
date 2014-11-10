#include	<iostream>///////////////
#include	"Channel.hpp"

namespace	Babel
{
  
  namespace	Server
  {
    
    namespace	Network
    {
      
      Channel::Channel(boost::asio::io_service &io_service, const tcp::endpoint &endpoint) :
	_acceptor(io_service, endpoint), _socket(io_service)
      {
	std::cout << "[CHANNEL] : Construction of a new channel." << std::endl;//////////////////////////
	accept();
      }
      
      Channel::~Channel()
      {
	std::cout << "[CHANNEL] : Destruction of a channel." << std::endl;//////////////////////////
      }
      
      void	Channel::accept()
      {
	std::cout << "[CHANNEL] : Waiting for a participant connection." << std::endl;//////////////////////////
	this->_acceptor.async_accept(this->_socket,
				     [this](boost::system::error_code ec)
				     {
				       if (!ec)
					 {
					   std::cout << "[CHANNEL] : Creating a session for the new participant." << std::endl;//////////////////////////
					   std::make_shared<Session>(std::move(this->_socket), this->_room)->start();
					 }
				       this->accept();
				     });
      }
      
      const Room &	Channel::getRoom() const
      {
	return (this->_room);
      }
      
    }
    
  }
  
}
