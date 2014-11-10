#ifndef AUDIOCALL_H
#define AUDIOCALL_H

#if defined(AUDIOCALL_LIBRARY)
# define AUDIOCALLSHARED_EXPORT Q_DECL_EXPORT
#else
# define CONNECTIONSHARED_EXPORT Q_DECL_IMPORT
#endif

#include    "../../Common/IClientPlugin.h"
#include    "IStream.hpp"
#include    "IEncode.hpp"

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
    bool            needGraphicUI(void)
    {
        return false;
    }

    void            setGraphicUI(Babel::Client::Common::IPluginView *ipluginView) {}
    void            setNetworkInterface(Babel::Client::Common::INetworkManager *network)
    {
        this->_network = network;
    }

    bool            init();

private:

    bool            getInputStream(const Babel::Common::Network::Packet &);
    bool            getOutputStream(const Babel::Common::Network::Packet &);
    bool            getEncode(const Babel::Common::Network::Packet &);

    //tmp

    bool            call(const QString &ip);

private:

    Babel::IStream                          *inputStream;
    Babel::IStream                          *outputStream;
    Babel::Audio::IEncode                   *encode;

    Babel::Client::Common::IPluginView      *_graphicView;
    Babel::Client::Common::INetworkManager  *_network;
};

}
}
}
}


#endif // AUDIOCALL_H
