#ifndef QPACKET_H
#define QPACKET_H

#include <QByteArray>
#include "../../Common/Network/Packet.hpp"

namespace Babel {
namespace Client {
namespace Network {

class QPacket : public Babel::Common::Network::Packet
{
public:
    QPacket(Babel::Common::Network::byte pluginId,
            Babel::Common::Network::byte actionId,
            Babel::Common::Network::byte response,
            unsigned int senderId, unsigned int receiverId, const QByteArray &);
    ~QPacket();
private:
    QByteArray  *_qData;
};

}
}
}

#endif // QPACKET_H
