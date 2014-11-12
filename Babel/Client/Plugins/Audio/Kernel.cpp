#include "Kernel.h"

#ifdef Q_OS_WIN
#  define MY_EXPORT __declspec(dllexport)
#else
#  define MY_EXPORT
#endif


extern "C" MY_EXPORT Babel::Client::Common::IClientPlugin *Instantiate(void)
{
  return new Babel::Client::Plugins::Audio::Kernel();
}


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
    qDebug() << "[AUDIO PLUGIN] : handle packet called";


    qDebug() << "[AUDIO action id] : " << packet.getConstHeader().actionId;

    if (packet.getConstHeader().actionId == 1)
        return (this->getInputStream(packet));
    if (packet.getConstHeader().actionId == 2)
        return (this->getOutputStream(packet));

    return true;
}

bool
Kernel::getInputStream(const Babel::Common::Network::Packet &packet)
{
    const Babel::Common::Network::Header &header = packet.getConstHeader();

    qDebug() << "[AUDIO PLUGIN]get InputStream called";
    qDebug() << header.dataSize;
    if (header.dataSize == sizeof(byte))
    {
        byte b;

        b = *packet.getData();
        byte *data = new byte[sizeof(void *)];
        void *ptn = (void *)(this->userP.getDefaultAInput()->getStream());

        qDebug() << "ptn : " << ptn;
        *((void **)(data)) = (void *)(ptn);
        qDebug() << "re ptn : " << *(void **)(data);
        Babel::Common::Network::Packet p(2, b, 0, 0, 0, sizeof(void *), data);
        this->_network->sendToYourself(p);
        return (true);
    }
    return (false);

}

bool
Kernel::getOutputStream(const Babel::Common::Network::Packet &packet)
{
    const Babel::Common::Network::Header &header = packet.getConstHeader();

    if (header.dataSize == sizeof(byte))
    {
        byte b;

        b = *packet.getData();
        byte *data = new byte[sizeof(void *)];

        *(void **)(data) = (void *)(this->userP.getDefaultAInput()->getStream());
        Babel::Common::Network::Packet p(2, b, 0, 0, 0, sizeof(void *), data);
        this->_network->sendToYourself(p);
        return (true);
    }
    return (false);
}

}
}
}
}
