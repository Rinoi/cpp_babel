#ifndef		__BABEL_CLIENT_PLUGINLOADER_H__
# define	__BABEL_CLIENT_PLUGINLOADER_H__

#include	<QMap>

#include	"./Common/IClientPlugin.h"

namespace	Babel
{
  namespace		Client
  {
    class			PluginLoader
    {
    public:
      //-------------------------------
      // Constructor
      //-------------------------------
      PluginLoader(void) {}

      //-------------------------------
      // Destructor
      //-------------------------------
      ~PluginLoader() {}

      //-------------------------------
      //
      //-------------------------------
      Babel::Client::Common::IClientPlugin			*loadPlugin(const QString &);
      void               redirectPacket(const Babel::Common::Network::Packet &packet);
      bool                 setPluginId(const QString &name, Babel::Common::Network::byte id);
    private:
      QMap<QString, Babel::Client::Common::IClientPlugin *>	_loadedPlugins;
      QList<QString>                                        _needId;
      QMap<Babel::Common::Network::byte, Babel::Client::Common::IClientPlugin *>     _loadedIdentified;
    };
  }
}

#endif // __BABEL_CLIENT_PLUGINLOADER_H__
