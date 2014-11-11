#ifndef                                 __I_SESSION_HPP__
#define                                 __I_SESSION_HPP__

#include                                "../../Common/Network/Packet.hpp"

namespace                               Babel
{

  namespace                             Server
  {

    namespace                           Network
    {

      class                             ISession
      {

      public:

        virtual ~ISession() {};

      public:

        virtual void                            writePacket(const Babel::Common::Network::Packet &) = 0;
        virtual void	       			joinConnectedRoom(unsigned int) = 0;
        virtual void	       			leaveAnonymousRoom() = 0;
      };

    }

  }

}

#endif
