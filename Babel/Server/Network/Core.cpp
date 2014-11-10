#include			"Core.hpp"

namespace			Babel
{
  
  namespace			Server
  {

    namespace			Network
    {
      
      Core::Core()
      {
	std::cout << "[CORE] : Construction of the core module." << std::endl;//////////////////////////		
      }
      
      Core::~Core()
      {
	std::cout << "[CORE] : Destruction of the core module." << std::endl;//////////////////////////		
      }
      
      void			Core::run()
      {
	std::cout << "[CORE] : Starting the core module." << std::endl;//////////////////////////		
	this->_io_service.poll();
      }
      
      boost::asio::io_service &	Core::getIoService()
      {
	return (this->_io_service);
      }
      
      void			Core::addChannel(const short int &port)
      {
	tcp::endpoint		endpoint(tcp::v4(), port);
	
	std::cout << "[CORE] : Creating a new channel listening to the port " << port << "." << std::endl;//////////////////////////		
	this->_channels.emplace_back(this->_io_service, endpoint);
      }

      const std::list<Channel> &	Core::getChannels() const
      {
	return (this->_channels);
      }

    }

  }

}
