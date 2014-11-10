#ifndef				__PLUGIN_MODEL__
#define				__PLUGIN_MODEL__

#include			<string>
#include			"AbsModelBDatabase.hpp"

class Plugin {
public:
  std::vector<std::string>	col_tab;
  Plugin() {
    this->col_tab.push_back("plugin");
    this->col_tab.push_back("id");
    this->col_tab.push_back("name");
  }

  int		id;
  std::string	name;
};

namespace                       soci {
  template<>
  struct                        type_conversion<Plugin>
  {
    typedef values              base_type;

    static void                 from_base(values const &v, indicator /*ind*/, Plugin &p)
    {
      p.id = v.get<int>("id");
      p.name = v.get<std::string>("name");
    }

    static void                 to_base(const Plugin &p, values &v, indicator &ind)
    {
      v.set("id", p.id);
      v.set("name", p.name);
      ind = i_ok;
    }
  };
}

#endif
