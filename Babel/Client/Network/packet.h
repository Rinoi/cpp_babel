#ifndef PACKET_H
#define PACKET_H

namespace Babel {
namespace Client {
namespace Network {

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

    bool isHeaderValid() const;
    void setData(byte *);
    void setDataSize(short int);
    void setPluginId(byte);
    void setActionId(byte);
    void setResponse(byte);
    void setSenderId(unsigned int);
    void setReceiverId(unsigned int);

    Header &getHeader();
    byte *getData();
    short int getHeaderSize() const;
    short int getDataSize() const;
    const Header &getConstHeader() const;
    byte *getConstData() const;

private:
    Header  _header;
    byte    *_data;
};

}
}
}

#endif // PACKET_H
