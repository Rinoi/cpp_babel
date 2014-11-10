#ifndef		__BABEL_CLIENT_PLUGINS_CONNECTION_KERNEL_H__
# define	__BABEL_CLIENT_PLUGINS_CONNECTION_KERNEL_H__

#include	<QtCore/qglobal.h>

#if defined(CONNECTION_LIBRARY)
#  define CONNECTIONSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CONNECTIONSHARED_EXPORT Q_DECL_IMPORT
#endif

#include	<QtPlugin>
#include	<QObject>
#include	<QUrl>

#include	"ConnectionAnchor.h"
#include	"../../Common/IClientPlugin.h"

namespace	Babel
{
  namespace		Client
  {
    namespace			Plugins
    {
      namespace				Connection
      {
    class CONNECTIONSHARED_EXPORT		Kernel : public ::Babel::Client::Common::IClientPlugin
    {

    public:
      Kernel(void);
      ~Kernel(void) {}

    public:
      bool										handlePacket(const Babel::Common::Network::Packet &);
      bool										needGraphicUI(void);
      void										setGraphicUI(Babel::Client::Common::IPluginView *view);
      void										setNetworkInterface(Babel::Client::Common::INetworkManager *);

    private:
      Babel::Client::Common::IPluginView		*_graphicView;
      ConnectionAnchor							_anchor;
      Babel::Client::Common::INetworkManager	*_network;
    };
      }
    }
  }
}

#endif // __BABEL_CLIENT_PLUGINS_CONNECTION_KERNEL_H__
