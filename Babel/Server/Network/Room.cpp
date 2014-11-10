#include	"Room.hpp"

namespace	Babel
{
  
  namespace	Server
  {
    
    namespace	Network
    {
      
      Room::Room()
      {
	std::cout << "[ROOM] : Construction of a new room." << std::endl;//////////////////////////	
      }
      
      Room::~Room()
      {
	std::cout << "[ROOM] : Destruction of a room." << std::endl;//////////////////////////	
      }
      
      void	Room::joinAnonymous(Session *participant)
      {
	std::cout << "[ROOM] : A participant joined the room anonymous." << std::endl;//////////////////////////	
	this->_anonymous_participants.push_back(participant);
      }

      void      Room::joinConnected(Session *participant, unsigned id)
      {
	std::cout << "[ROOM] : A participant joined the room connected." << std::endl;
	this->_connected_participants[id] = participant;
      }
      
      void	Room::leaveAnonymous(Session *participant)
      {
	std::cout << "[ROOM] : A participant left the room anonymous." << std::endl;//////////////////////////	
	this->_anonymous_participants.remove(participant);
      }

      void      Room::leaveConnected(Session *participant)
      {
	/*	std::cout << "[ROOM] : A participant left the room connected." << std::endl;
		this->_connected_participants.erase(participant);*/
      }

      const std::map<unsigned int, Session *> & Room::getConnectedParticipants() const
      {
	return (this->_connected_participants);
      }
      
    }

  }

}
