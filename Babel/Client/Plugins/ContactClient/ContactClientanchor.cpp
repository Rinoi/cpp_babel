#include "ContactClientAnchor.h"
#include "../../Network/packet.h"

#include <QDebug> // a supprimer

namespace	Babel {
namespace		Client {
namespace			Plugins {
namespace				ContactClient {

ContactClientAnchor::ContactClientAnchor() {
    qDebug() << "Connection Anchor initialized !";
}

ContactClientAnchor::~ContactClientAnchor() {

}

void
ContactClientAnchor::onConnectionClicked()
{
}
}
}
}
}
