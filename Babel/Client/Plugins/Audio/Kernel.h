#ifndef KERNEL_H
#define KERNEL_H

#include <QtCore/qglobal.h>
#include "./inc/Babel/UserPeriph.hh"

#if defined(AUDIO_LIBRARY)
#  define AUDIOSHARED_EXPORT Q_DECL_EXPORT
#else
#  define AUDIOSHARED_EXPORT Q_DECL_IMPORT
#endif

#include "../../Common/IClientPlugin.h"

namespace   Babel
{
namespace   Client
{
namespace   Plugins
{
namespace   Audio
{

class AUDIOSHARED_EXPORT Kernel : public Babel::Client::Common::IClientPlugin
{
public:
    Kernel();
    ~Kernel(void);

public:
    inline bool     needGraphicUI(void)
    {
        return false;
    }

    inline void     setGraphicUI(::Babel::Client::Common::IPluginView *) {}

    inline void     setNetworkInterface(Common::INetworkManager *network)
    {
        this->_network = network;
    }

    bool            handlePacket(const Babel::Common::Network::Packet &);

private:

    bool            getInputStream(const Babel::Common::Network::Packet &);
    bool            getOutputStream(const Babel::Common::Network::Packet &);

private:
    Common::INetworkManager *_network;
    Babel::UserPeriph       userP;

};


}
}
}
}


#endif // KERNEL_H
