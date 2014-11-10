#ifndef APPLICATIONANCHOR_H
#define APPLICATIONANCHOR_H


#include <QObject>

namespace   Babel
{
namespace   Client
{
class Application;

class ApplicationAnchor : public QObject
{
    Q_OBJECT

public:
    ApplicationAnchor(Babel::Client::Application &);

    Q_INVOKABLE void    reconnectToServer(void);
    Q_INVOKABLE void    loadConnectionPlugin(void);

private:
    Babel::Client::Application  &_app;
};

}
}

#endif // APPLICATIONANCHOR_H
