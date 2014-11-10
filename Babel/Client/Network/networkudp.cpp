#include "networkudp.h"

namespace Babel {
namespace Client {
namespace Network {

NetworkUDP::NetworkUDP() :
    QObject(0), _sock(this),
    _completing(false), _header(false), _multicaster(false), _linkedClient(false)
{
}

NetworkUDP::~NetworkUDP() {
}

bool    NetworkUDP::isConnected() const {
    return (this->_sock.state() == QAbstractSocket::ConnectedState);
}

void    NetworkUDP::initSocket(int port) {
    connect(&_sock, SIGNAL(readyRead()), this, SLOT(readPackets()));
    connect(&_sock, SIGNAL(error(QAbstractSocket::SocketError)), this,
            SLOT(readErr(QAbstractSocket::SocketError)));
    this->_sock.bind(port);
}

void    NetworkUDP::deconnectSocket() {
    this->_sock.abort();
}

void    NetworkUDP::deconnectClient() {
    this->_linkedClient = false;
}

void    NetworkUDP::connectClient(const QString &ip, int port) {
    this->_linkedClient = true;
    this->_client_adress = QHostAddress(ip);
    this->_port_client = port;
}

bool    NetworkUDP::isMulticast() const {
    return (this->_multicaster);
}

void    NetworkUDP::connectMulticast(const QString &groupAddr) {
    this->_groupmulticast = QHostAddress(groupAddr);
    this->_sock.joinMulticastGroup(this->_groupmulticast);
}


void    NetworkUDP::leaveMulticast() {
    this->_sock.leaveMulticastGroup(this->_groupmulticast);
    this->_multicaster = false;
}

void    NetworkUDP::readPackets()
{
    std::cout << "HELLO I AM READING" << std::endl;
    QByteArray buffer;
    QHostAddress sender;
    quint16 senderPort;
    int i = 0;

    while (this->_sock.hasPendingDatagrams()) {
        std::cout << "HELLO I AM READING" << i++ << std::endl;
        buffer.resize(this->_sock.pendingDatagramSize());
        std::cout << "HELLO I AM READING" << i - 1 << std::endl;
        this->_sock.readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);
        std::cout << "HELLO I AM READING" << i - 1 << std::endl;
        this->updatePackets(buffer);
        std::cout << "HELLO I AM READING lol" << i - 1 << std::endl;
    }
}

void    NetworkUDP::readErr(QAbstractSocket::SocketError scktErr)
{
    switch (scktErr) {
        case QAbstractSocket::RemoteHostClosedError:
            break;
        case QAbstractSocket::HostNotFoundError:
            std::cerr << "Network UDP : "
                      << "The host was not found. Please check the "
                                        "host name and port settings."
                      << std::endl;
            break;
        case QAbstractSocket::ConnectionRefusedError:
            std::cerr << "Network UDP : "
                  << "The connection was refused by the peer. "
                     "Make sure the server is running, "
                     "and check that the host name and port "
                     "settings are correct."
                  << std::endl;
            break;
        default:
        std::cerr << "Network UDP : "
              << "The following error occurred: "
              << this->_sock.errorString().toStdString() << std::endl;
        }
}

int NetworkUDP::send(const QString &addr, qint16 port, const ::Babel::Common::Network::Packet &pack)
{
    (void)addr;
    QByteArray      header((const char *)&pack.getConstHeader(), SIZE_HEADER);
    QByteArray      data((const char *)pack.getData(), pack.getDataSize());

    if (this->isConnected())
    {
        this->_sock.writeDatagram(header,  QHostAddress::Broadcast, port);
        this->_sock.writeDatagram(data,  QHostAddress::Broadcast, port);
        if (this->_sock.waitForBytesWritten() == false) {
            std::cerr << "Network UDP : Cannot send message (unknown)"
                      << std::endl;
        }
    }
    std::cerr << "Network UDP : Cannot send message (not connected)"
              << std::endl;
    return 0;
}


int NetworkUDP::send(const ::Babel::Common::Network::Packet &pack)
{
    if (this->_multicaster && this->isConnected()) {

        QByteArray      header((const char *)&pack.getConstHeader(), SIZE_HEADER);
        QByteArray      data((const char *)pack.getData(), pack.getDataSize());

        this->_sock.writeDatagram(header, this->_groupmulticast, 4242);
        this->_sock.writeDatagram(data, this->_groupmulticast, 4242);
        this->_sock.waitForBytesWritten();
    }
    else if (this->_linkedClient) {

        QByteArray      header((const char *)&pack.getConstHeader(), SIZE_HEADER);
        QByteArray      data((const char *)pack.getData(), pack.getDataSize());

        this->_sock.writeDatagram(header, QHostAddress::Broadcast, this->_port_client);
        this->_sock.writeDatagram(data, QHostAddress::Broadcast, this->_port_client);
        this->_sock.waitForBytesWritten();
    }
    return 0;
}


::Babel::Common::Network::Packet *NetworkUDP::recieve()
{
    return (this->getPacket());
}

const ::Babel::Common::Network::byte *NetworkUDP::serialize(::Babel::Common::Network::Packet &pack)
{
    return (pack.getData());
}

::Babel::Common::Network::Packet NetworkUDP::deserialize(::Babel::Common::Network::byte *data)
{
    ::Babel::Common::Network::Packet  pack;

    pack.setData(data);
    return pack;
}

QString NetworkUDP::encrypt(const QString &) {
    return QString("");
}

QString NetworkUDP::decrypt(const QString &) {
    return QString("");

}

std::string NetworkUDP::encrypt(const std::string &) {
    return ("");
}

std::string NetworkUDP::decrypt(const std::string &) {
    return ("");
}

void    NetworkUDP::fillPacketHeader() {
    ::Babel::Common::Network::Header  &head = this->_current->getHeader();

    head = *((::Babel::Common::Network::Header *)(this->_currentData.data()));
    this->_currentData = this->_currentData.right(this->_currentData.size() - SIZE_HEADER);
}

void    NetworkUDP::updatePackets(QByteArray &data) {
    if (!this->_completing) {
        unsigned long   len = 0;
        len = this->_currentData.size();
        this->_currentData.append(data);
        if (!this->_header) {
            if (len >= SIZE_HEADER) {
                this->_header = true;
                this->_current = new ::Babel::Common::Network::Packet();
                fillPacketHeader();
            }
        }
        if (this->_current)
            len = this->_current->getDataSize();
        if (this->_header &&
            this->_current->getDataSize() - this->_currentData.size() >= 0) {
            this->_completing = true;
        }
    }
    if (this->_completing) {

        this->_currentData = this->_currentData.right(this->_current->getDataSize());
        this->_current->setData((::Babel::Common::Network::byte *)(this->_currentData.data()));
        this->_completing = false;
        this->_header = false;
        this->_packets.append(this->_current);
        this->_current = NULL;
    }
}

::Babel::Common::Network::Packet  *NetworkUDP::getPacket() {
    if (this->_packets.isEmpty())
        return NULL;
    ::Babel::Common::Network::Packet  *pack = this->_packets.front();
    this->_packets.pop_front();
    return pack;
}

}
}
}
