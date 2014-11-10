#ifndef			__CHANNEL_HPP__
#define			__CHANNEL_HPP__

#include                <boost/asio.hpp>
#include		"Session.hpp"

using			boost::asio::ip::tcp;

namespace		Babel
{
  
  namespace		Server
  {
    
    namespace		Network
    {

      class		Channel
      {
	
      public:
	
	Channel(boost::asio::io_service &, const tcp::endpoint &);
	~Channel();
	
      public:
	
	void	       	accept();

      public:
	
	const Room &	getRoom() const;
	
      private:
	
	tcp::acceptor	_acceptor;
	tcp::socket	_socket;
	Room		_room;
	
      };
      
    }

  }

}

#endif
