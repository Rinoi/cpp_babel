#ifndef AUDIOCALL_H
#define AUDIOCALL_H

#if defined(AUDIOCALL_LIBRARY)
# define AUDIOCALLSHARED_EXPORT Q_DECL_EXPORT
#else
# define CONNECTIONSHARED_EXPORT Q_DECL_IMPORT
#endif

#include    "../../Common/IClientPlugin.h"

namespace Babel
{
namespace   Client
{
namespace   Plugins
{
namespace   AudioCall
{
class AUDIOCALLSHARED_EXPORT Kernel : public ::Babel::Client::Common::IClientPlugin
{

public:
    Kernel(void);
    ~Kernel(void) {}

public:
    bool            handlePacket(const Babel::Common::Network::Packet &);
    bool            needGraphicUI(void);
    void            setGraphicUI(Babel::Client::Common::IPluginView *ipluginView);
    void            setNetworkInterface(Babel::Client::Common::INetworkManager *network);

private:
    Babel::Client::Common::IPluginView      *_graphicView;
    Babel::Client::Common::INetworkManager  *_network;
};

}
}
}
}


#endif // AUDIOCALL_H
