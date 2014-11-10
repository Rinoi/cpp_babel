#ifndef		__BABEL_CLIENT_APPLICATION_H__
#define		__BABEL_CLIENT_APPLICATION_H__

#include	<QApplication>
#include	<QQmlApplicationEngine>
#include	<QWindow>

#include    "Network/networkmanager.h"
#include	"PluginLoader.h"
#include    "ApplicationAnchor.h"

namespace	Babel
{
  namespace		Client
  {

    class			Application
    {
    public:
      Application(int ac, char *av[]);

    public:
      int			exec(void);
      void          onConnectedToServer(bool onConnected = true);
      void          onConnectionFailed(void);
      void          onConnectionSuccess(void);
      void          loadConnectionPlugin(void);
      void          reconnectToServer(void);

    private:
      QApplication                              _app;
      QQmlApplicationEngine                 	_qmlEngine;
      PluginLoader                              _pluginLoader;
      QWindow                                   *_window;
      Network::NetworkManager                   _network;
      Babel::Client::ApplicationAnchor          _anchor;
    };
  }
}

#endif // __BABEL_CLIENT_APPLICATION_H__
