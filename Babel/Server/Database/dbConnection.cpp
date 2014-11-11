#include			<iostream>
#include			"AbsModelBDatabase.hpp"

using namespace Babel;
using namespace Server;
using namespace Database;
using namespace soci;

#define CONTACT                 "users(id INT NOT NULL AUTO_INCREMENT, first_name VARCHAR(255) NOT NULL, last_name VARCHAR(255) NOT NULL, user_name VARCHAR(255) NOT NULL, email VARCHAR(255) NOT NULL, password VARCHAR(255) NOT NULL, PRIMARY KEY(id), UNIQUE(email))"
#define PLUGIN                  "plugin(id INT NOT NULL AUTO_INCREMENT, name VARCHAR(255) NOT NULL, PRIMARY KEY(id), UNIQUE(name))"
#define MESSAGE			"message(id INT NOT NULL AUTO_INCREMENT, `from` INT NOT NULL, `to` INT NOT NULL, content VARCHAR(255) NOT NULL, PRIMARY KEY(id))"
#define USERDB                  "babel"
#define PASSDB                  "babel"
#define DBNAME                  "babel"


BabelDatabase			BabelDatabase::_instance = BabelDatabase();

BabelDatabase::BabelDatabase()
{
  std::cout << "Connection to Babel Database..." << std::endl;
  try
    {
	  this->sql = new soci::session(mysql, "service=" DBNAME " user=" USERDB " password=" PASSDB);
    }
  catch (std::exception const &e)
    {
      std::cerr << "Error: " << e.what() << std::endl;
    }
  std::cout << "Connection success." << std::endl;
  try {
  *(this->sql) << "CREATE TABLE IF NOT EXISTS " CONTACT;
  *(this->sql) << "CREATE TABLE IF NOT EXISTS " PLUGIN;
  *(this->sql) << "CREATE TABLE IF NOT EXISTS " MESSAGE;
  }
  catch (std::exception const &e)
    {
      std::cerr << "Error: " << e.what() << '\n';
    }
}

BabelDatabase::~BabelDatabase()
{
  std::cout << "Connection to Babel Database closed." << std::endl;
}

BabelDatabase&			BabelDatabase::getInstance()
{
  return _instance;
}
