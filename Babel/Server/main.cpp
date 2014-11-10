#include	<iostream>
#include	<boost/thread.hpp>
#include	"Network/Server.hpp"
#include	"../Common/Network/PacketManager.hpp"

using boost::asio::ip::tcp;

int		main(int ac, char **av)
{
  Babel::Server::Network::Server	server;

  try
    {
      if (ac < 2)
        {
	  std::cerr << "Usage: ./a.out <port> [<port> ...]\n";
          return (EXIT_FAILURE);
        }
      for (int i = 1; i < ac; ++i)
	server.addChannel(std::atoi(av[i]));
      boost::thread thread(boost::bind(&boost::asio::io_service::run, &server.getCore().getIoService()));
      server.handlePacket();
    }
  catch (std::exception& e)
    {
      std::cerr << "Exception: " << e.what() << "\n";
    }  
  return (EXIT_SUCCESS);
}
