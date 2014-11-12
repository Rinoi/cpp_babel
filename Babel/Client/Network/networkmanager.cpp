#include "networkmanager.h"
#include "../Common/QPacket.h"

namespace Babel {
namespace Client {
namespace Network {

NetworkManager::NetworkManager(int udport) :
    _host(QString("")), _port(4242), _inst(NULL), _callBack(NULL) {
    this->_clients.initSocket(udport);
}

NetworkManager::NetworkManager(const QString &serv, int port, int my) :
    _host(serv), _port(port), _inst(NULL), _callBack(NULL), _server(), _clients() {
    this->_clients.initSocket(my);
}

NetworkManager::~NetworkManager() {

}

const QString &NetworkManager::getHost() const {
    return this->_host;
}

int NetworkManager::getPort() const {
    return this->_port;
}

void NetworkManager::setHost(const QString &str) {
    this->_host = str;
}

void NetworkManager::setPort(int p) {
    this->_port = p;
}

bool NetworkManager::WaitToConnectServer() {
    return this->_server.waitConnectionServer();
}

bool NetworkManager::ConnectToServer(Babel::Client::Application *inst, appPtr callBack) {
    this->_server.setConnectionCallback(inst, callBack);
    this->_server.connectToHost(this->_host, this->_port);
    return true;
}

bool NetworkManager::DeconnectFromServer() {
    this->_server.deconnectFromHost();
    return (!this->_server.isConnected());
}

bool NetworkManager::SendToServer(const ::Babel::Common::Network::Packet &pack) {
    if (this->_server.isConnected()) {
        this->_server.send(pack);
        return true;
    }
    return false;
}

void    NetworkManager::sendToYourself(const ::Babel::Common::Network::Packet &pack) {
    if (this->_inst && this->_callBack) {

//        const ::Babel::Common::Network::Header &hed = pack.getConstHeader();

//        QByteArray  data((const char *)pack.getData(),hed.dataSize);
//        ::Babel::Client::Network::QPacket *packet = new ::Babel::Client::Network::QPacket(hed.pluginId, hed.actionId, hed.response, hed.senderId, hed.receiverId, data);

        (this->_inst->*(this->_callBack))(pack);
    }
}


bool NetworkManager::ConnectToClient(const QString &ip, int port) {
    this->_clients.connectClient(ip, port);
    return true;
}

bool NetworkManager::SendToClient(const ::Babel::Common::Network::Packet &pack) {
        this->_clients.send(pack);
    return false;
}

::Babel::Common::Network::Packet  *NetworkManager::RetrieveClientPacket() {
    return this->_clients.getPacket();
}

bool NetworkManager::DeconnectFromCient() {
    return false;
}

::Babel::Common::Network::Packet  *NetworkManager::RetrieveServerPacket() {
    return this->_server.getPacket();
}

bool     NetworkManager::goMulticast(const QString &group) {
    if (this->_clients.isConnected() && !this->_clients.isMulticast()) {
        this->_clients.connectMulticast(group);
        return (this->_clients.isConnected());
    }
    return false;
}

bool     NetworkManager::goSingleCast() {
    if (this->_clients.isConnected() && this->_clients.isMulticast()) {
        this->_clients.leaveMulticast();
        return (!this->_clients.isConnected());
    }
    return true;
}

void    NetworkManager::setRedirect(Babel::Client::PluginLoader *inst, plugloadPtr callBack) {
    this->_server.setRedirectCallback(inst, callBack);
    this->_inst = inst;
    this->_callBack = callBack;
}

}
}
}
