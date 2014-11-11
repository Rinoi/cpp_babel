#ifndef		__BABEL_CLIENT_COMMON_I_CLIENT_PLUGIN_H__
# define	__BABEL_CLIENT_COMMON_I_CLIENT_PLUGIN_H__

#include	"../../Common/IPlugin.h"
#include	"INetworkManager.h"
#include	"IPluginView.h"

namespace	Babel
{
  namespace		Client
  {
    namespace			Common
    {
      class				IClientPlugin : public Babel::Common::IPlugin
      {
      public:
          virtual bool    init(void) = 0;
          virtual bool    needGraphicUI(void) = 0;
          virtual void    setGraphicUI(IPluginView *) = 0;
          virtual void    setNetworkInterface(Babel::Client::Common::INetworkManager *) = 0;
      };
    }
  }
}

#endif // __BABEL_CLIENT_COMMON_I_CLIENT_PLUGIN_H__
