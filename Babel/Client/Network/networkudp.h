#ifndef NETWORKUDP_H
#define NETWORKUDP_H

#include <iostream>

#include <QByteArray>
#include <QString>
#include <QList>
#include <QUdpSocket>
#include <QMessageBox>
#include <QDataStream>

#include "inetwork.h"

namespace Babel {
namespace Client {
namespace Network {

class NetworkUDP : public QObject, public INetwork
{
public:
    Q_OBJECT
public:
    NetworkUDP();
    virtual ~NetworkUDP();

    bool isConnected() const; //OK
    void initSocket(int); //OK
    void connectClient(const QString &, int); // OK
    void deconnectClient(); // OK
    void deconnectSocket(); //OK
    void connectMulticast(const QString &groupAddr); //WRK
    void leaveMulticast(); //WRK
    bool isMulticast() const; // OK

    virtual int send(const ::Babel::Common::Network::Packet &); //Not bullshit anymore -> to test
    virtual int send(const QString &, qint16, const ::Babel::Common::Network::Packet &); //OK

    virtual ::Babel::Common::Network::Packet *recieve(); // OK ? -> Need test
    virtual const ::Babel::Common::Network::byte *serialize(::Babel::Common::Network::Packet &); // OK
    virtual ::Babel::Common::Network::Packet deserialize(::Babel::Common::Network::byte *); // OK

    ::Babel::Common::Network::Packet *getPacket();

private slots:
    void readPackets();
    void readErr(QAbstractSocket::SocketError scktErr);

private:
    virtual QString encrypt(const QString &);
    virtual QString decrypt(const QString &);
    virtual std::string encrypt(const std::string &);
    virtual std::string decrypt(const std::string &);

    void    fillPacketHeader();
    void    updatePackets(QByteArray &data);

private:
    QUdpSocket              _sock;
    bool                    _completing;
    bool                    _header;
    bool                    _multicaster;
    bool                    _linkedClient;
    QList<Babel::Common::Network::Packet *>         _packets;
    ::Babel::Common::Network::Packet                  *_current;
    QByteArray              _currentData;
    QHostAddress            _groupmulticast;
    QHostAddress            _client_adress;
    int                     _port_client;
};

}
}
}
#endif // NETWORKUDP_H
