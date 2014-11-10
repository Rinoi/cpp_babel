#include "Kernel.h"

#ifdef Q_OS_WIN
#  define MY_EXPORT __declspec(dllexport)
#else
#  define MY_EXPORT
#endif

#include <qresource.h>
#include <iostream>

extern "C" MY_EXPORT Babel::Client::Common::IClientPlugin *Instantiate(void)
{
  return new Babel::Client::Plugins::Connection::Kernel();
}

#include <QDebug>

namespace	Babel
{
  namespace		Client
  {
    namespace			Plugins
    {
      namespace				Connection
      {

    Kernel::Kernel(void)
    {
      qDebug() << "Connection plugin initialised";
    }

    bool
    Kernel::handlePacket(const Babel::Common::Network::Packet &packet)
    {
      qDebug() << "Connection method handlePacket called";

      const Babel::Common::Network::Header    &header = packet.getConstHeader();

        if (header.response == 1)
        {
            this->_anchor.onConnectionSuccess();
        }
        else
        {
            this->_anchor.onConnectionFailed("something wrong append.");
        }

      return false;
    }

    bool
    Kernel::needGraphicUI()
    {
      return true;
    }

    void
    Kernel::setGraphicUI(Babel::Client::Common::IPluginView *view)
    {
        this->_graphicView = view;

        std::cout << "Setting UI" << std::endl;
        this->_graphicView->setSource(QUrl(QStringLiteral("qrc:/Resources/Connection.qml")));
        view->setContextProperty("connectionAnchor", &this->_anchor);

        std::cout << "Setting getting anglris cxte" << std::endl;
        this->_graphicView->show();
        std::cout << "show cxte" << std::endl;

    }

    void
    Kernel::setNetworkInterface(Babel::Client::Common::INetworkManager *network)
    {
        qDebug() << "network set";
        this->_network = network;
        this->_anchor.setNetworkInterface(network);
        qDebug() << "network set";
      }
    }
  }
}
}
