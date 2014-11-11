#ifndef					__ISERVER_HPP__
#define					__ISERVER_HPP__

#include                                                                "../Database/AbsModelBDatabase.hpp"

namespace				Babel
{

  namespace		                Server
  {

    namespace				Network
    {

      class				IServer
      {

      public:

        virtual ~IServer() {};

      public:

        virtual void			send(const Common::Network::Packet &) = 0;
        virtual byte			getPluginId(const std::string &) = 0;
	virtual Babel::Server::Database::BabelDatabase &                        getDb() = 0;

      };

    }

  }

}


#endif
