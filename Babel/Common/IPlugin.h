#ifndef		__BABEL_COMMON_I_PLUGIN_H__
# define	__BABEL_COMMON_I_PLUGIN_H__

#include	"Network/Packet.hpp"

namespace	Babel
{
  namespace		Common
  {
    class			IPlugin
    {
    public:
      virtual bool    handlePacket(const ::Babel::Common::Network::Packet &) = 0;
    };
  }
}

#endif // __BABEL_COMMON_I_PLUGIN_H__
