#include "ApplicationAnchor.h"
#include "Application.h"

namespace Babel
{
namespace Client
{

ApplicationAnchor::ApplicationAnchor(Babel::Client::Application &app) :
        _app(app)
{
}


void
ApplicationAnchor::reconnectToServer()
{
    this->_app.reconnectToServer();
}

bool
ApplicationAnchor::loadConnectionPlugin()
{
    return this->_app.loadConnectionPlugin();
}

}
}
