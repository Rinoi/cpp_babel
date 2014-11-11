#ifndef KERNEL_H
#define KERNEL_H

#include <QtCore/qglobal.h>

#if defined(ENCODE_LIBRARY)
#  define ENCODESHARED_EXPORT Q_DECL_EXPORT
#else
#  define ENCODESHARED_EXPORT Q_DECL_IMPORT
#endif

#include "inc/Babel/Audio/IEncode.hpp"

#include    "../../Common/IClientPlugin.h"

namespace   Babel
{
namespace   Client
{
namespace   Plugins
{
namespace   Encode
{
class ENCODESHARED_EXPORT Kernel : public Babel::Client::Common::IClientPlugin
{

public:
    Kernel();
    ~Kernel(void);

public:

    inline bool         init(void) { return true; }

    inline bool        needGraphicUI(void)
    {
        return false;
    }

    inline void        setGraphicUI(::Babel::Client::Common::IPluginView *)
    {
    }

    inline void         setNetworkInterface(Common::INetworkManager *network)
    {
        this->_network = network;
    }

    bool                handlePacket(const Babel::Common::Network::Packet &packet);

private:
    bool                getEncode(const Babel::Common::Network::Packet &packet) const;

private:

    Babel::Audio::IEncode       *encode;
    Common::INetworkManager     *_network;
    int                         nb_frame;

};

}
}
}
}


#endif // KERNEL_H
