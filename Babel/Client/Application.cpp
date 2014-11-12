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
      _network("10.17.73.4", 4242, 8080),
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

    bool
    Application::loadConnectionPlugin(void)
    {
        Babel::Client::Common::IClientPlugin	*plugin;
        bool    ret = false;

        if ((plugin = this->_pluginLoader.loadPlugin("connection")) != 0)
        {
            plugin->setNetworkInterface(&this->_network);
            if (plugin->needGraphicUI() == true)
            {
                QQuickView *view = new QQuickView(&this->_qmlEngine, this->_window);
                view->setMinimumSize(QSize(this->_window->width(), this->_window->height()));
//                view->setY(25);
                Babel::Client::Common::IPluginView *connectionView = new Babel::Client::PluginView(view);
                plugin->setGraphicUI(connectionView);
                view->show();
                ret = true;
            }
        }


        if ((plugin = this->_pluginLoader.loadPlugin("Audio")) != 0)
        {
            plugin->setNetworkInterface(&this->_network);
                qDebug() << "module Audio loaded";
        }

        if ((plugin = this->_pluginLoader.loadPlugin("Encode")) != 0)
        {
            plugin->setNetworkInterface(&this->_network);
                qDebug() << "module Encode loaded";
        }

        if ((plugin = this->_pluginLoader.loadPlugin("AudioCall")) != 0)
        {
            plugin->setNetworkInterface(&this->_network);
                qDebug() << "module AudioCall loaded";
        }


        //plugin->init();
        return ret;
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
