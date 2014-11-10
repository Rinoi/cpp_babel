#ifndef				__USER_STRUCT__
#define				__USER_STRUCT__

#include			<string>
#include			"AbsModelBDatabase.hpp"

class					User {
public:
  std::vector<std::string>		col_tab;
  User(){
    this->col_tab.push_back("contact");
    this->col_tab.push_back("first_name");
    this->col_tab.push_back("last_name");
    this->col_tab.push_back("user_name");
    this->col_tab.push_back("email");
    this->col_tab.push_back("password");
  }  

  int				id;
  std::string			firstName;
  std::string			lastName;
  std::string			userName;
  std::string			email;
  std::string			password;
};


/* ************** MAPPING FOR DB ******************* */



namespace                       soci {
  template<>
  struct                        type_conversion<User>
  {
    typedef values              base_type;

    static void                 from_base(values const &v, indicator /*ind*/, User &u)
    {
      u.id = v.get<int>("id");
      u.firstName = v.get<std::string>("first_name");
      u.lastName = v.get<std::string>("last_name");
      u.userName = v.get<std::string>("user_name");
      u.email = v.get<std::string>("email");
      u.password = v.get<std::string>("password");
    }

    static void                 to_base(const User &u, values &v, indicator &ind)
    {
      v.set("id", u.id);
      v.set("first_name", u.firstName);
      v.set("last_name", u.lastName);
      v.set("user_name", u.userName);
      v.set("email", u.email);
      v.set("password", u.password);
      ind = i_ok;
    }
  };
}

#endif
