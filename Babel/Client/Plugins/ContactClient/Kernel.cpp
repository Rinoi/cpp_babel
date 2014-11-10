#include "Kernel.h"

#ifdef Q_OS_WIN
#  define MY_EXPORT __declspec(dllexport)
#else
#  define MY_EXPORT
#endif

extern "C" MY_EXPORT Babel::Client::Common::IClientPlugin *Instantiate(void)
{
  return new Babel::Client::Plugins::ContactClient::Kernel();
}

#include <QDebug>

namespace	Babel {
namespace		Client {
namespace			Plugins {
namespace				ContactClient {

Kernel::Kernel(void) {
    qDebug() << "Connection plugin initialised";
}

bool
Kernel::handlePacket(const Babel::Common::Network::Packet &) {
    qDebug() << "Connection method handlePacket called";
    return false;
}

bool
Kernel::needGraphicUI() {
    return true;
}

void
Kernel::setGraphicUI(Babel::Client::Common::IPluginView *view) {
    this->_graphicView = view;
    this->_graphicView->setSource(QUrl(QStringLiteral("qrc:/Resources/Connection.qml")));
    QQuickItem *item = this->_graphicView->getItem();
    if (item == 0)
    {
        qDebug() << "child not found";
    }
    else
    {
        item->setSize(QSize(this->_graphicView->getWidth(), this->_graphicView->getHeight()));
    }
    view->setContextProperty("connectionAnchor", &this->_anchor);
    this->_graphicView->show();
}

void
Kernel::setNetworkInterface(Babel::Client::Common::INetworkManager *network) {
    qDebug() << "network set";
    this->_network = network;
}
}
}
}
}
