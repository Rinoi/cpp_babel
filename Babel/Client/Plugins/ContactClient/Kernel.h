#ifndef __BABEL_CLIENT_PLUGINS_CONTACT_CLIENT_KERNEL_H__
#define __BABEL_CLIENT_PLUGINS_CONTACT_CLIENT_KERNEL_H__

#include	<QtCore/qglobal.h>

#if defined(CONTACTCLIENT_LIBRARY)
#  define CONTACTCLIENTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CONTACTCLIENTSHARED_EXPORT Q_DECL_IMPORT
#endif

#include	<QtPlugin>
#include	<QObject>
#include	<QUrl>

#include    "ContactClientanchor.h"
#include	"../../Common/IClientPlugin.h"

namespace Babel {
namespace Client {
namespace Plugins {
namespace ContactClient {

class CONTACTCLIENTSHARED_EXPORT Kernel : public ::Babel::Client::Common::IClientPlugin
{

public:
    Kernel();
    ~Kernel() {}

  public:
    bool	handlePacket(const Babel::Common::Network::Packet &);
    bool	needGraphicUI(void);
    void	setGraphicUI(Babel::Client::Common::IPluginView *view);
    void	setNetworkInterface(Babel::Client::Common::INetworkManager *);

  private:
    Babel::Client::Common::IPluginView		*_graphicView;
    ContactClientAnchor                     _anchor;
    Babel::Client::Common::INetworkManager	*_network;
};

}
}
}
}

#endif // __BABEL_CLIENT_PLUGINS_CONTACT_CLIENT_KERNEL_H__
