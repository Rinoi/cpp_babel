#ifndef INETWORKMANAGER_H
#define INETWORKMANAGER_H

#include <QString>

#include "../../Common/Network/Packet.hpp"

namespace Babel {
namespace Client {
namespace Common {

class INetworkManager
{
public:
    virtual ~INetworkManager() {}

    virtual const QString &getHost() const = 0;
    virtual int getPort() const = 0;

    virtual void setHost(const QString &) = 0;
    virtual void setPort(int) = 0;

    virtual void    sendToYourself(const ::Babel::Common::Network::Packet &pack) = 0;

    // TCP protocol, works with server
    virtual bool SendToServer(const ::Babel::Common::Network::Packet &pack) = 0;
    virtual ::Babel::Common::Network::Packet *RetrieveServerPacket() = 0;
    virtual bool DeconnectFromServer() = 0;

    // UDP protocol, preaparing multicast
    virtual bool goMulticast(const QString &) = 0;
    virtual bool goSingleCast() = 0;
    // UDP protocol, works with ONE client
    virtual bool ConnectToClient(const QString &, int) = 0;
    virtual bool SendToClient(const ::Babel::Common::Network::Packet &pack) = 0;
    virtual ::Babel::Common::Network::Packet *RetrieveClientPacket() = 0;
    virtual bool DeconnectFromCient() = 0;
};
}
}
}

#endif // INETWORKMANAGER_H
