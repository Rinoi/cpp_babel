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
            if (plugin->needGraphicUI() == true)
            {
                std::cout << "HELLO efwefwe" << std::endl;
                QQuickView *view = new QQuickView(&this->_qmlEngine, this->_window);
                view->setMinimumSize(QSize(this->_window->width(), this->_window->height()));
//                view->setY(25);
                Babel::Client::Common::IPluginView *connectionView = new Babel::Client::PluginView(view);
                plugin->setNetworkInterface(&this->_network);

                plugin->setGraphicUI(connectionView);
                view->show();
                std::cout << "HELLO efwefwe" << std::endl;
            }
        }
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
