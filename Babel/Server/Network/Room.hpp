#ifndef					__ROOM_HPP__
#define					__ROOM_HPP__

#include				<list>
#include				<map>
#include				<iostream>

namespace				Babel
{
  
  namespace				Server
  {
    
    namespace				Network
    {

      class				Session;

      class				Room
      {
	
      public:
	
	Room();
	~Room();
	
      public:
	
	void				joinAnonymous(Session *);
	void				joinConnected(Session *, unsigned int);
	void				leaveAnonymous(Session *);
	void				leaveConnected(Session *);

      public:

	const std::map<unsigned int, Session *> & getConnectedParticipants() const;
	
      private:
	
	std::list<Session *>			_anonymous_participants;
	std::map<unsigned int, Session *>	_connected_participants;
	
      };

    }

  }

}

#endif
