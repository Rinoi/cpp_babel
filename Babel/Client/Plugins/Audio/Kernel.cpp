#include "Kernel.h"

namespace   Babel
{
namespace   Client
{
namespace   Plugins
{
namespace   Audio
{

Kernel::Kernel()
{
}

Kernel::~Kernel(void)
{

}

bool
Kernel::handlePacket(const Babel::Common::Network::Packet &packet)
{
    qDebug() << "[ENCODE PLUGIN] : handle packet called";

    if (packet.getConstHeader().actionId == 1)
        return (this->getInputStream(packet));
    if (packet.getConstHeader().actionId == 1)
        return (this->getOutputStream(packet));

    return true;
}

bool
Kernel::getInputStream(const Babel::Common::Network::Packet &packet)
{
    const Babel::Common::Network::Header &header = packet.getConstHeader();

    if (header.dataSize == 1)
    {
        byte b;

        b = *packet.getData();
        byte *data = new byte[sizeof(void *)];

        *(void **)(data) = (void *)(this->userP.getDefaultAInput());
        Babel::Common::Network::Packet p(header.pluginId, b, 0, 0, 0, sizeof(void *), data);
        this->_network->SendToServer(p);
        return (true);
    }
    return (false);

}

bool
Kernel::getOutputStream(const Babel::Common::Network::Packet &packet)
{
    const Babel::Common::Network::Header &header = packet.getConstHeader();

    if (header.dataSize == 1)
    {
        byte b;

        b = *packet.getData();
        byte *data = new byte[sizeof(void *)];

        *(void **)(data) = (void *)(this->userP.getDefaultAInput());
        Babel::Common::Network::Packet p(header.pluginId, b, 0, 0, 0, sizeof(void *), data);
        this->_network->SendToServer(p);
        return (true);
    }
    return (false);

}

}
}
}
}
