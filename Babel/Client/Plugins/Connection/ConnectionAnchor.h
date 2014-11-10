#ifndef CONNECTIONANCHOR_H
#define CONNECTIONANCHOR_H

#include "../../Common/INetworkManager.h"

#include <QObject>

namespace	Babel
{
  namespace		Client
  {
    namespace			Plugins
    {
      namespace				Connection
      {
      class ConnectionAnchor : public QObject
      {
          Q_OBJECT

      public:
          ConnectionAnchor(void);
	
      public:
          Q_INVOKABLE void onConnectionClicked(const QString &email, const QString &password);
          Q_INVOKABLE void onSubscribeClicked(const QString &firstName, const QString &lastName, const QString &email, const QString &password);

          Q_INVOKABLE void onConnectionFailed(const QString &error);
          Q_INVOKABLE void onConnectionSuccess();

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
