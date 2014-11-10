#include "PluginLoaderUnix.hh"

extern "C"
{
#include <dlfcn.h>
}

#include <cstdio>
#include <cstdlib>

namespace Babel
{
  namespace Server
  {
    namespace Plugin
    {

      PluginLoaderUnix::PluginLoaderUnix(Babel::Server::Network::Server *server)
      {
	this->server = server;
      }

      PluginLoaderUnix::~PluginLoaderUnix()
      {

      }

      AServerPlugin	*PluginLoaderUnix::Load(const std::string &name)
      {
	void		*hand;
	AServerPlugin	*r;
	char		*str;
	ftc_plugin	fct;
	void		*ptn;
	//remettre dlerror
	r = NULL;
	std::cout << name + ".so" << std::endl;
	hand = dlopen((name + ".so").c_str(), RTLD_LAZY);
	if (hand == NULL)
	  {
	    return (r);
	  }
        ptn = dlsym(hand, "getPlugin");
	if (ptn != NULL)
	  {
	    fct = (ftc_plugin)(ptn);
	    r = fct(this->server);
	  }
	return (r);
      }

    }
  }
}
