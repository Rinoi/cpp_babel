#ifndef __PLUGIN__LOADER__
# define __PLUGIN__LOADER__

# include <iostream>

# include "AServerPlugin.hpp"

namespace Babel
{
  namespace Server
  {
    namespace Plugin
    {
      class	IPluginLoader
      {
      public:
	virtual ~IPluginLoader()
	{}

	virtual AServerPlugin	*Load(const std::string &name) = 0;
      };
    }
  }
}

#endif
