#ifndef				__PLUGIN_MODEL__
#define				__PLUGIN_MODEL__

#include			<string>
#include			"../Database/AbsModelBDatabase.hpp"

class					PluginModel {
public:
  std::vector<std::string>		col_tab;
  PluginModel(){
    this->col_tab.push_back("plugin");
    this->col_tab.push_back("name");
  }  

  int				id;
  std::string			name;
};


/* ************** MAPPING FOR DB ******************* */

namespace                       soci {
  template<>
  struct                        type_conversion<PluginModel>
  {
    typedef values              base_type;

    static void                 from_base(values const &v, indicator /*ind*/, PluginModel &pm)
    {
      pm.id = v.get<int>("id");
      pm.name = v.get<std::string>("name");
    }

    static void                 to_base(const PluginModel &pm, values &v, indicator &ind)
    {
      v.set("id", pm.id);
      v.set("name", pm.name);
      ind = i_ok;
    }
  };
}

#endif
