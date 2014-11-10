#ifndef BNETWORKTCP_H
#define BNETWORKTCP_H

#include <iostream>

#include <QByteArray>
#include <QString>
#include <QList>
#include <QTcpSocket>
#include <QMessageBox>
#include <QDataStream>

#include "inetwork.h"


namespace Babel {
namespace Client {
class Application;
class PluginLoader;
}
}

namespace Babel {
namespace Client {
namespace Network {

typedef void (Babel::Client::Application::*appPtr)( bool);
typedef void (Babel::Client::PluginLoader::*plugloadPtr)(const Babel::Common::Network::Packet&);

class NetworkTCP : public QObject, public INetwork
{

    Q_OBJECT
public:
    NetworkTCP();
    virtual ~NetworkTCP();

    bool isConnected();
    void connectToHost(const QString &, int);
    void deconnectFromHost();
    bool    waitConnectionServer();
    void    setConnectionCallback(Babel::Client::Application *inst, appPtr callBack);
    void    setRedirectCallback(Babel::Client::PluginLoader *inst, plugloadPtr callBack);

    virtual int send(const ::Babel::Common::Network::Packet &);
    virtual ::Babel::Common::Network::Packet *recieve();
    virtual const ::Babel::Common::Network::byte *serialize(::Babel::Common::Network::Packet &);
    virtual ::Babel::Common::Network::Packet deserialize(::Babel::Common::Network::byte *);

    //get the oldest packet recieved from server.
    ::Babel::Common::Network::Packet *getPacket();

private slots:
    void readPackets();
    void readErr(QAbstractSocket::SocketError scktErr);
    void serverConnected();

private:
    virtual QString encrypt(const QString &);
    virtual QString decrypt(const QString &);
    virtual std::string encrypt(const std::string &);
    virtual std::string decrypt(const std::string &);

    void    fillPacketHeader();
    void    updatePackets(QByteArray &);

private:
    QTcpSocket                                      _sock;
    quint16                                         _blockSize;
    bool                                            _connected;
    bool                                            _completing;
    bool                                            _header;
    appPtr                                          _connectionCallback;
    ::Babel::Client::Application                    *_callbackInst;
    plugloadPtr                                     _redirectCallback;
    ::Babel::Client::PluginLoader                   *_redirectInst;
    QList<Babel::Common::Network::Packet *>         _packets;
    ::Babel::Common::Network::Packet                *_current;
    QByteArray                                      _currentData;

};

}
}
}

#endif // BNETWORKTCP_H
