#include "Packet.hpp"

namespace	Babel
{
  
  namespace   Common
  {
    
    namespace	Network
    {
      
      Packet::Packet() {
      }
      
      Packet::Packet
      (byte pluginId, byte actionId, byte response, unsigned int senderId, unsigned int receiverId, unsigned short int dataSize, byte *data) {
	_header.pluginId = pluginId;
	_header.actionId = actionId;
	_header.response = response;
	_header.receiverId = receiverId;
	_header.dataSize = dataSize;
	_header.senderId = senderId;
	_data = data;
      }
      
      Packet::~Packet() {
	
      }
      
      Header &Packet::getHeader() {
	return (this->_header);
      }
      
      void Packet::setActionId(byte a) {
	this->_header.actionId = a;
      }
      
      void Packet::setPluginId(byte a) {
	this->_header.pluginId = a;
      }
      
      void Packet::setResponse(byte a) {
	this->_header.response = a;
      }
      
      void Packet::setSenderId(unsigned int a) {
	this->_header.actionId = a;
      }
      
      void Packet::setReceiverId(unsigned int a) {
	this->_header.actionId = a;
      }
      
      
      const Header &Packet::getConstHeader() const {
	return (this->_header);
      }
      
      short int	Packet::getHeaderSize() const {
	return (sizeof(Header));
      }
      
      bool	Packet::isHeaderValid() const {
	//for the lulz ???
	return (true);
      }
      
      const byte	*Packet::getData() const{
	return (this->_data);
      }
      
      void	Packet::setData(byte *data) {
	this->_data = data;
      }
      
      void    Packet::setDataSize(short int val) {
	this->_header.dataSize = val;
      }
      
      short int	Packet::getDataSize() const{
	return (this->_header.dataSize);
      }
      
    }

  }

}
