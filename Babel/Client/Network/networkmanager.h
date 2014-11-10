#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include "../Common/INetworkManager.h"
#include "networktcp.h"
#include "networkudp.h"

namespace Babel {
namespace Client {
namespace Network {

class NetworkManager : public Babel::Client::Common::INetworkManager
{
public:
    NetworkManager(int udpPort);
    NetworkManager(const QString &serverIp, int serverPort, int udpPort);
    ~NetworkManager();

    const QString &getHost() const;
    int getPort() const;

    void setHost(const QString &);
    void setPort(int);

    // To yourself
    void    sendToYourself(const ::Babel::Common::Network::Packet &pack);

    // TCP protocol, works with server
    bool ConnectToServer(Babel::Client::Application *instance, appPtr ptrCallback);
    bool SendToServer(const ::Babel::Common::Network::Packet &pack);
    ::Babel::Common::Network::Packet *RetrieveServerPacket();
    bool WaitToConnectServer();
    bool DeconnectFromServer();

    // UDP protocol, preaparing multicast
    bool goMulticast(const  QString &);
    bool goSingleCast();
    // UDP protocol, works with ONE client
    bool ConnectToClient(const QString &, int);
    bool SendToClient(const ::Babel::Common::Network::Packet &pack);
    ::Babel::Common::Network::Packet *RetrieveClientPacket();
    bool DeconnectFromCient();
    void    setRedirect(Babel::Client::PluginLoader *inst, plugloadPtr callBack);

private:
    QString         _host;
    int             _port;
    Babel::Client::PluginLoader *_inst;
    plugloadPtr     _callBack;
    NetworkTCP      _server;
    NetworkUDP      _clients;
};

}
}
}

#endif // NETWORKMANAGER_H
