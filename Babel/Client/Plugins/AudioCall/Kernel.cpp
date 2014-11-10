#include "Kernel.h"

#include <QDebug>

namespace   Babel
{
namespace   Client
{
namespace   Plugins
{
namespace   AudioCall
{
    Kernel::Kernel(void)
    {
        qDebug() << "audiocall initialized";
    }

    bool
    Kernel::handlePacket(const Babel::Common::Network::Packet &)
    {
        return true;
    }

    bool
    Kernel::needGraphicUI()
    {
        return false;
    }

    void
    Kernel::setGraphicUI(Common::IPluginView *ipluginView)
    {
        this->_graphicView = ipluginView;
    }

    void
    Kernel::setNetworkInterface(Common::INetworkManager *network)
    {
        this->_network = network;
    }

}
}
}
}
