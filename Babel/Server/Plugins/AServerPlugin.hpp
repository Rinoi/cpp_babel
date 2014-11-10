#ifndef __SERVEUR__PLUGIN__
# define __SERVEUR__PLUGIN__

#include <iostream>
#include "../../Common/IPlugin.h"

namespace Babel
{
  namespace Server
  {
    namespace Plugin
    {

      class AServerPlugin : public Babel::Common::IPlugin
      {

      public:
	AServerPlugin()
	{
	}
	~AServerPlugin() {} ;

	const AServerPlugin	&operator=(const AServerPlugin &u)
	{
	  this->id = u.id;
	  this->name = u.name;
	  return (*this);
	}

	virtual	bool	init() = 0;

	virtual bool    handlePacket(const ::Babel::Common::Network::Packet &) = 0;

	byte	getId() const
	{return (this->id);}

	void	setId(byte id)
	{this->id = id;}

	const std::string	&getName() const
	{return (this->name);}

	void			setName(const std::string &s)
	{this->name = s;}

      protected:
	byte		id;
	std::string	name;

      };

    }
  }
}

// namespace                       soci {
//   template<>
//   struct                        type_conversion<Babel::Server::Plugin::AServerPlugin>
//   {
//     typedef values              base_type;
//     static void                 from_base(values const &v, indicator /*ind*/, Babel::Server::Plugin::AServerPlugin &u)
//     {
//       u.setId(v.get<byte>("id"));
//       u.setName(v.get<std::string>("name"));
//     }
//     static void                 to_base(const Babel::Server::Plugin::AServerPlugin &u, values &v, indicator &ind)
//     {
//       v.set("id", u.getId());
//       v.set("name", u.getName());
//       ind = i_ok;
//     }
//   };
// }


#endif
