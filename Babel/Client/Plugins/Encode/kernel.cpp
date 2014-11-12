#include <QDebug>

#include "kernel.h"
#include "inc/Babel/Audio/Opus/Encode.hh"


#ifdef Q_OS_WIN
#  define MY_EXPORT __declspec(dllexport)
#else
#  define MY_EXPORT
#endif


extern "C" MY_EXPORT Babel::Client::Common::IClientPlugin *Instantiate(void)
{
  return new Babel::Client::Plugins::Encode::Kernel();
}

namespace   Babel
{
namespace   Client
{
namespace   Plugins
{
namespace   Encode
{


Kernel::Kernel(void)
{
    this->encode = new Babel::Audio::Opus::Encode(SAMPLE_RATE);
}

Kernel::~Kernel(void)
{
}

bool
Kernel::handlePacket(const Babel::Common::Network::Packet &packet)
{
    qDebug() << "[ENCODE PLUGIN] : handle packet called";

    if (packet.getConstHeader().actionId == 1)
        return (this->getEncode(packet));

    return true;
}

bool
Kernel::getEncode(const Babel::Common::Network::Packet &packet) const
{
    const Babel::Common::Network::Header &header = packet.getConstHeader();

    if (header.dataSize == 1)
    {
        byte b;

        b = *packet.getData();
        byte *data = new byte[sizeof(void *)];

        *(void **)(data) = (void *)(this->encode);
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
