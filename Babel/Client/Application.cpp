#include	<QUrl>
#include	<QObject>

#include	"Application.h"
#include	"PluginView.h"
#include	"./Common/IClientPlugin.h"

#include	"Network/networkmanager.h"

namespace	Babel
{
  namespace		Client
  {

    Application::Application(int ac, char *av[]) :
      _app(ac, av),
      _network("localhost", 4242, 8080),
//      _network("10.17.72.243", 4242, 8080),
//      _network("localhost", 4242, 8080),
      _anchor(*this)
    {
      this->_qmlEngine.load(QUrl(QStringLiteral("qrc:/main.qml")));
      this->_window = qobject_cast<QWindow *>(this->_qmlEngine.rootObjects().first());
        this->_qmlEngine.rootContext()->setContextProperty("applicationAnchor", &this->_anchor);
    }

    void
    Application::onConnectedToServer(bool onConnected)
    {
        if (!onConnected) {
            this->onConnectionFailed();
        } else {
            this->onConnectionSuccess();
        }
    }

    void
    Application::loadConnectionPlugin(void)
    {
        Babel::Client::Common::IClientPlugin	*plugin;

        if ((plugin = this->_pluginLoader.loadPlugin("connection")) != 0)
        {
            this->_pluginLoader.setPluginId("connection", 1);
            plugin->setNetworkInterface(&this->_network);
            if (plugin->needGraphicUI() == true)
            {
                QQuickView *view = new QQuickView(&this->_qmlEngine, this->_window);
                view->setMinimumSize(QSize(this->_window->width(), this->_window->height()));
//                view->setY(25);
                Babel::Client::Common::IPluginView *connectionView = new Babel::Client::PluginView(view);
                plugin->setGraphicUI(connectionView);
                view->show();
            }
        }


        if ((plugin = this->_pluginLoader.loadPlugin("Audio")) != 0)
        {
            this->_pluginLoader.setPluginId("Audio", 3);
            plugin->setNetworkInterface(&this->_network);
                qDebug() << "module Audio loaded";
        }

        if ((plugin = this->_pluginLoader.loadPlugin("Encode")) != 0)
        {
            this->_pluginLoader.setPluginId("Encode", 4);
            plugin->setNetworkInterface(&this->_network);
                qDebug() << "module Encode loaded";
        }

        if ((plugin = this->_pluginLoader.loadPlugin("AudioCall")) != 0)
        {
            this->_pluginLoader.setPluginId("AudioCall", 2);
            plugin->setNetworkInterface(&this->_network);
            qDebug() << "module AudioCall loaded";
        }


        plugin->init();

    }

    void
    Application::onConnectionSuccess(void)
    {
        QObject *obj = this->_qmlEngine.rootObjects().first();
        QObject *child = obj->findChild<QObject *>("infoText");

        child->setProperty("text", "connection to server failed");
        QMetaObject::invokeMethod(child, "onConnectionSuccess");
    }

    void
    Application::onConnectionFailed(void)
    {
        QObject *obj = this->_qmlEngine.rootObjects().first();
        QObject *child = obj->findChild<QObject *>("infoText");

        child->setProperty("text", "connection to server failed");
        QMetaObject::invokeMethod(child, "onConnectionFailed");
    }

    void
    Application::reconnectToServer()
    {
        this->_network.ConnectToServer(this, &Application::onConnectedToServer);
    }

    int
    Application::exec(void)
    {
      this->_network.ConnectToServer(this, &Application::onConnectedToServer);
      this->_network.setRedirect(&this->_pluginLoader, &Babel::Client::PluginLoader::redirectPacket);
      //this->loadConnectionPlugin();
	  return this->_app.exec();
    }
  }
}
