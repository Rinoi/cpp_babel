#include <QLibrary>

#include "PluginLoader.h"

typedef Babel::Client::Common::IClientPlugin	*(*funcPtr)(void);

#include <iostream>
namespace	Babel
{
  namespace		Client
  {
    Common::IClientPlugin *
    PluginLoader::loadPlugin(const QString &filename)
    {
      QString	absolutePath = "./plugins/" + filename + "/" + filename;

      if (this->_loadedPlugins.contains(filename) == false)
	{
      QLibrary	lib(absolutePath);

      qDebug() << absolutePath;
	  if (lib.load() == true)
	    {
	      funcPtr	instantiatePlugin = (funcPtr)(lib.resolve("Instantiate"));
	      if (instantiatePlugin)
		{
          Common::IClientPlugin	*plugin = instantiatePlugin();
		  this->_loadedPlugins[filename] = plugin;
          this->_needId.append(filename);
		  return (plugin);
		}
        else
          {
          qDebug() << "problem de resolution de nom";
          }
	    }
      else
      {
          qDebug() << "lib not loaded";
      }
	  // replace by a runtime_error throw
      qDebug() << lib.errorString();
      return (0);
	}
      return (this->_loadedPlugins[filename]);
    }

    void
    PluginLoader::redirectPacket(const Babel::Common::Network::Packet &packet) {
        const Babel::Common::Network::Header &head = packet.getConstHeader();
        Babel::Common::Network::byte pluginId = head.pluginId;
        qDebug() << "GETTING PACKET FOR ID : " << pluginId;

//        if (!_loadedIdentified.contains(pluginId)) {
//            qDebug() << "Does not contqins pluginID " << pluginId;
//            if (!this->_needId.empty()) {

//                qDebug() << pluginId << " : " << this->_needId.front();

//                this->_loadedIdentified[pluginId] = this->_loadedPlugins[this->_needId.front()];
//                this->_needId.pop_front();
//            }
//        }
        qDebug() << "SO DATA data size : " << head.dataSize;

        if (_loadedIdentified.contains(pluginId)) {
            this->_loadedIdentified[pluginId]->handlePacket(packet);
        }
    }

    bool
    PluginLoader::setPluginId(const QString &name, Babel::Common::Network::byte id) {

        if (_loadedPlugins.contains(name)) {
            this->_loadedIdentified[id] = _loadedPlugins[name];
            qDebug() << "true";
            return (true);
        }
        qDebug() << "false";
        return false;
    }

}
}
