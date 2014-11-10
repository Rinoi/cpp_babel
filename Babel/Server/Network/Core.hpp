#ifndef					__CORE_HPP__
#define					__CORE_HPP__

#include				<list>
#include				"Channel.hpp"

namespace				Babel
{
  
  namespace				Server
  {
    
    namespace				Network
    {
      
      class				Core
      {
	
      public:
	
	Core();
	~Core();
	
      public:
	
	void			      	run();
	void			  	addChannel(const short int &);
	
      public:
	
	boost::asio::io_service &	getIoService();
	const std::list<Channel> &	getChannels() const;
	
      private:
	
	boost::asio::io_service		_io_service;
	std::list<Channel>		_channels;
	
      };
      
    }

  }

}

#endif
