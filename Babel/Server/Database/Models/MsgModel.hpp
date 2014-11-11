#ifndef				__MSG_STRUCT__
#define				__MSG_STRUCT__

#include			<string>
#include			<ctime>
#include			"AbsModelBDatabase.hpp"

class					Msg {
public:
  std::vector<std::string>		col_tab;
  Msg(){
    this->col_tab.push_back("message");
    this->col_tab.push_back("from");
    this->col_tab.push_back("to");
    this->col_tab.push_back("content");
    this->col_tab.push_back("date");
  }

  int				id;
  int				from;
  int				to;
  std::string			content;
  std::tm			date;
};


/* ************** MAPPING FOR DB ******************* */



namespace                       soci {
  template<>
  struct                        type_conversion<Msg>
  {
    typedef values              base_type;

    static void                 from_base(values const &v, indicator /*ind*/, Msg &u)
    {
      u.id = v.get<int>("id");
      u.from = v.get<int>("from");
      u.to = v.get<int>("to");
      u.content = v.get<std::string>("content");
      u.date = v.get<std::tm>("date");
    }

    static void                 to_base(const Msg &u, values &v, indicator &ind)
    {
      v.set("id", u.id);
      v.set("from", u.from);
      v.set("to", u.to);
      v.set("content", u.content);
      v.set("date", u.date);
      ind = i_ok;
    }
  };
}

#endif
