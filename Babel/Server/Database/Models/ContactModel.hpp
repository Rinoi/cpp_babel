#ifndef				__CONTACT_MODEL__
#define				__CONTACT_MODEL__

#include			<string>
#include			"AbsModelBDatabase.hpp"

enum ContactStatus { FRIEND, REQUEST_SEND, REQUEST_WAITING, BLOCKED };

class Contact {
public:
  std::vector<std::string>	col_tab;
  Contact() {
    this->col_tab.push_back("contact");
    this->col_tab.push_back("user_id");
    this->col_tab.push_back("contact_id");
    this->col_tab.push_back("status");
  }

  int	id;
  int	userId;
  int	contactId;
  ContactStatus	status;
};

namespace                       soci {
  template<>
  struct                        type_conversion<Contact>
  {
    typedef values              base_type;

    static void                 from_base(values const &v, indicator /*ind*/, Contact &c)
    {
      c.id = v.get<int>("id");
      c.userId = v.get<int>("user_id");
      c.contactId = v.get<int>("contact_id");
      c.status = v.get<int>("status");
    }

    static void                 to_base(const Contact &c, values &v, indicator &ind)
    {
      v.set("id", c.id);
      v.set("user_id", c.userId);
      v.set("contact_id", c.contactId);
      v.set("status", c.status);
      ind = i_ok;
    }
  };
}

#endif
