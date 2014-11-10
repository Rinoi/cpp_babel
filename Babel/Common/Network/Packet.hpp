#ifndef	__PACKET_HPP__
#define __PACKET_HPP__

#define SERVER_ID 0
#define UNLOGGED_ID 1

typedef unsigned char byte;

namespace Babel
{
  
  namespace Common
  {
    
    namespace Network
    {

      typedef unsigned char byte;
      struct s_packetHeader
      {
	byte                pluginId;
	byte                actionId;
	byte                response;
	unsigned int        senderId;
	unsigned int        receiverId;
	unsigned short int  dataSize;
      };
      typedef struct s_packetHeader Header;
      
      class Packet
      {
      public:
	Packet();
	Packet(byte pluginId, byte actionId, byte response, unsigned int senderId, unsigned int receiverId, unsigned short int dataSize, byte *data);
	~Packet();
	
	virtual bool isHeaderValid() const;
	virtual void setData(byte *);
	virtual void setDataSize(short int);
	virtual void setPluginId(byte);
	virtual void setActionId(byte);
	virtual void setResponse(byte);
	virtual void setSenderId(unsigned int);
	virtual void setReceiverId(unsigned int);
	
	virtual Header &getHeader();
	virtual const byte *getData() const;
	virtual short int getHeaderSize() const;
	virtual short int getDataSize() const;
	virtual const Header &getConstHeader() const;
	
      private:
	Header  _header;
	byte    *_data;
      };
      
    }

  }

}

#endif
