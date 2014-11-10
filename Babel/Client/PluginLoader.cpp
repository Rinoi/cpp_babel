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

      ::std::cerr << absolutePath.toStdString();
	  if (lib.load() == true)
	    {
	      funcPtr	instantiatePlugin = (funcPtr)(lib.resolve("Instantiate"));
	      if (instantiatePlugin)
		{
          Common::IClientPlugin	*plugin = instantiatePlugin();
		  this->_loadedPlugins[filename] = plugin;
          this->_needId.append(filename);
          (void)filename;
		  return (plugin);
		}
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
        if (!_loadedIdentified.contains(pluginId)) {
            if (!this->_needId.empty()) {
                this->_loadedIdentified[pluginId] = this->_loadedPlugins[this->_needId.front()];
                this->_needId.pop_front();
            }
        }
        if (_loadedIdentified.contains(pluginId)) {
            this->_loadedIdentified[pluginId]->handlePacket(packet);
        }
    }
}
}
