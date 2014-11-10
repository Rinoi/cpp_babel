#ifndef				__USER_PLUGINS_MODEL__
#define				__USER_PLUGINS_MODEL__

#include			<string>
#include			"AbsModelBDatabase.hpp"

class UserPlugin {
public:
  std::vector<std::string>	col_tab;
  Plugin() {
    this->col_tab.push_back("user_plugins");
    this->col_tab.push_back("user_id");
    this->col_tab.push_back("plugin_id");
  }

  int	userId;
  int	pluginId;
};

namespace                       soci {
  template<>
  struct                        type_conversion<UserPlugin>
  {
    typedef values              base_type;

    static void                 from_base(values const &v, indicator /*ind*/, UserPlugin &p)
    {
      p.userId = v.get<int>("user_id");
      p.pluginId = v.get<int>("name");
    }

    static void                 to_base(const UserPlugin &p, values &v, indicator &ind)
    {
      v.set("user_id", p.userId);
      v.set("plugin_id", p.pluginId);
      ind = i_ok;
    }
  };
}

#endif
