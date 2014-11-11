#ifndef				__ABSTRACT_ORM_MYSQL__
#define				__ABSTRACT_ORM_MYSQL__

#include			<iostream>
#include			<boost/predef.h>

# if BOOST_OS_WINDOWS
#include "core\soci.h"
# include "backends\mysql\soci-mysql.h"
# else
#  include			"soci/soci.h"
#  include			"soci/mysql/soci-mysql.h"
# endif

namespace			Babel {
  namespace			Server {
    namespace			Database {

      class			BabelDatabase {
      private:
        BabelDatabase();
        BabelDatabase(const BabelDatabase&);
        ~BabelDatabase();
        BabelDatabase&					operator=(const BabelDatabase&){ return (*this); }

	soci::session					*sql;
        static BabelDatabase				_instance;
	template<typename T>std::string&		_reqInsert(const T &t)
	{
	  std::string                   *r = new std::string("");

	  *r += t.col_tab[0] + "(";
	  for (int i = 1; i < t.col_tab.size() ; i++)
	    {
	      *r += t.col_tab[i];
	      if (i + 1 < t.col_tab.size())
		*r += ", ";
	    }
	  *r += ") VALUES(:";
	  for (int i = 1; i < t.col_tab.size() ; i++)
	    {
	      *r += t.col_tab[i];
	      if (i + 1 < t.col_tab.size())
		*r += ", :";
	    }
	  *r += ")";
	  return *r;
	}
	template<typename T> std::string&		_reqUpdate(const T &t)
	{
	  std::string                   *r = new std::string("");

	  *r += t.col_tab[0] += " SET ";
	  for (int i = 1; i < t.col_tab.size() ; i++)
	    {
	      *r += t.col_tab[i] + "=:" + t.col_tab[i];
	      if (i + 1 < t.col_tab.size())
		*r += ", ";
	    }
	  *r += " WHERE id=:id";
	  std::cout << *r << std::endl;
	  return *r;
	}
      public:
	int						id;
        static BabelDatabase				&getInstance();
	soci::session&					getDB()
        {
          return *sql;
        }

	template<typename T>void			insert(const T &t) {
	  std::cout << "Req : " << "INSERT INTO " << this->_reqInsert(t) << std::endl;
	  this->getDB() << "INSERT INTO " << this->_reqInsert(t), soci::use<T>(t);
	}

	template<typename T> void			remove(const T &t) {
	  this->getDB() << "REMOVE FROM " << t.col_tab[0] << " WHERE id=:id", soci::use(t);
	}

	template<typename T> void			update(const T &t) {
	  this->getDB() << "UPDATE " << this->_reqUpdate(t), soci::use(t);
	}

	template<typename T> void			select(T &t) {
	  this->getDB() << "SELECT * FROM " << t.col_tab[0] << " WHERE id=:id", soci::use<T>(t), soci::into<T>(t);
	}

	template<typename T> void			selectWhere(T &t, const std::string& w) {
	  this->getDB() << "SELECT * FROM " << t.col_tab[0] << " WHERE " << w/*, soci::use<T>(t)*/, soci::into(t);
	}

	template<typename T> soci::rowset<T>&		selectMulti(const std::string& q) {
       	  soci::rowset<T>				*r;
       	  soci::rowset<T>				tmp = (this->getDB()).prepare << q;

	  r = new soci::rowset<T>(tmp);
	  return *r;
	}

	void						queryWrite(const std::string& q) {
	  this->getDB() << q;
	}
	
      };
    }
  }
}

#endif
