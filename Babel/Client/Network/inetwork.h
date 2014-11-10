#ifndef BINETWORK_H
#define BINETWORK_H

#include <string>

#include "../../Common/Network/Packet.hpp"

namespace Babel {
namespace Client {
namespace Network {

#define SIZE_HEADER sizeof(::Babel::Common::Network::Header)

class INetwork
{
public:
    virtual ~INetwork() {}

    virtual int send(const ::Babel::Common::Network::Packet &) = 0;
    virtual ::Babel::Common::Network::Packet *recieve() = 0;
    virtual const ::Babel::Common::Network::byte *serialize(::Babel::Common::Network::Packet &) = 0;
    virtual ::Babel::Common::Network::Packet deserialize(::Babel::Common::Network::byte *) = 0;

private:
    virtual std::string encrypt(const std::string &) = 0;
    virtual std::string decrypt(const std::string &) = 0;
};

}
}
}

#endif // BINETWORK_H
