#ifndef CONTACTCLIENTANCHOR_H
#define CONTACTCLIENTANCHOR_H

#include "../../Common/INetworkManager.h"

#include <QObject>

namespace	Babel {
namespace	Client {
namespace   Plugins {
namespace	ContactClient {

class ContactClientAnchor : public QObject
{
    Q_OBJECT

public:
    ContactClientAnchor();
    ~ContactClientAnchor();

public:
    Q_INVOKABLE void onConnectionClicked();

public:
    void  setNetworkInterface(::Babel::Client::Common::INetworkManager *network)
    {
        this->_network = network;
    }

private:
    ::Babel::Client::Common::INetworkManager    *_network;
};

}
}
}
}

#endif // CONNECTIONANCHOR_H
