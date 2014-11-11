
#include "QPacket.h"

namespace Babel {
namespace Client {
namespace Network {

QPacket::QPacket
(Babel::Common::Network::byte pluginId, Babel::Common::Network::byte actionId, Babel::Common::Network::byte response, unsigned int senderId, unsigned int receiverId, const QByteArray &data) :
Babel::Common::Network::Packet(pluginId, actionId, response, senderId, receiverId, data.size(), 0)
{
    this->_qData = new QByteArray(data);
    this->setData((Babel::Common::Network::byte *)this->_qData->data());
}

QPacket::~QPacket() {
    delete (this->_qData);
}

}
}
}
