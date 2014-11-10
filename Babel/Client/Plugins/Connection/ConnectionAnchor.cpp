#include "ConnectionAnchor.h"
#include "../../Common/QPacket.h"

#include <QDebug> // a supprimer

namespace	Babel
{
  namespace		Client
  {
    namespace			Plugins
    {
      namespace				Connection
      {
	ConnectionAnchor::ConnectionAnchor(void)
	{
	  qDebug() << "Connection Anchor initialized !";
	}

	void
    ConnectionAnchor::onConnectionClicked(const QString &email, const QString &password)
	{
        qDebug() << "on Connection called : email : " << email << " | password : " << password;
        QByteArray  data(email.toStdString().c_str());
        data.append((char)4);
        data.append(password);
        data.append((char)0);

        qDebug() << "[" << data.data() << "]";
        qDebug() << "[" << data.length() << "]";

        Babel::Client::Network::QPacket  pack(1, 2, 0, UNLOGGED_ID, SERVER_ID, data);
        this->_network->SendToServer(pack);
    }

    void
    ConnectionAnchor::onSubscribeClicked(const QString &firstName, const QString &lastName, const QString &email, const QString &password)
    {
        qDebug() << "on subscribe called : firstName : " << firstName << " | lastName : " << lastName << " | email : " << email << " | password : " << password;
        QByteArray  data(firstName.toStdString().c_str());

        data.append((char)4);
        data.append(lastName);
        data.append((char)4);
        data.append(email);
        data.append((char)4);
        data.append(password);
        data.append((char)0);


        Babel::Client::Network::QPacket  pack(1, 1, 0, UNLOGGED_ID, SERVER_ID, data);

        this->_network->SendToServer(pack);

      }

    void
    ConnectionAnchor::onConnectionFailed(const QString &error)
    {
        qDebug() << "onConnectionFailed : " << error;
    }

    void
    ConnectionAnchor::onConnectionSuccess()
    {
        qDebug() << "onConnectionSuccess";
    }

    }


  }
}
}
