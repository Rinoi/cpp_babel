#include "Kernel.h"

#include <QDebug>
#include <QTime>


#ifdef Q_OS_WIN
#  define MY_EXPORT __declspec(dllexport)
#else
#  define MY_EXPORT
#endif


extern "C" MY_EXPORT Babel::Client::Common::IClientPlugin *Instantiate(void)
{
  return new Babel::Client::Plugins::AudioCall::Kernel();
}

namespace   Babel
{
namespace   Client
{
namespace   Plugins
{
namespace   AudioCall
{
    Kernel::Kernel(void)
    {
        qDebug() << "audiocall initialized";

        this->inputStream = NULL;
        this->outputStream = NULL;
        this->inputStream = NULL;
    }

    bool
    Kernel::init()
    {
        {
            byte    *data = new byte[1];

            *data = 41;
            const Babel::Common::Network::Packet p(3, 1, 0, 0, 0, sizeof(data), data);
            this->_network->sendToYourself(p);
        }
        {
            byte    *data = new byte[1];

            *data = 42;
            const Babel::Common::Network::Packet p(3, 2, 0, 0, 0, sizeof(data), data);

            this->_network->sendToYourself(p);
        }
        {
            byte    *data = new byte[1];

            *data = 43;
            const Babel::Common::Network::Packet p(4, 1, 0, 0, 0, sizeof(data), data);

            this->_network->sendToYourself(p);
        }
        return (true);
    }

    bool
    Kernel::handlePacket(const Babel::Common::Network::Packet &p)
    {
        if (p.getConstHeader().actionId == 42)
            return (this->getInputStream(p));
        if (p.getConstHeader().actionId == 42)
            return (this->getOutputStream(p));
        if (p.getConstHeader().actionId == 42)
            return (this->getEncode(p));
        return true;
    }

    bool
    Kernel::getInputStream(const Babel::Common::Network::Packet &p)
    {
        if (p.getConstHeader().dataSize == sizeof(void *))
        {
            this->inputStream = (Babel::IStream *)(p.getData());
            return (true);
        }
        return (false);
    }

    bool
    Kernel::getOutputStream(const Babel::Common::Network::Packet &p)
    {
        if (p.getConstHeader().dataSize == sizeof(void *))
        {
            this->outputStream = (Babel::IStream *)(p.getData());
            if (this->outputStream != NULL && this->inputStream != NULL)
                this->call("loool");
            return (true);
        }
        return (false);
    }

    bool
    Kernel::getEncode(const Babel::Common::Network::Packet &p)
    {
        if (p.getConstHeader().dataSize == sizeof(void *))
        {
            this->encode = (Babel::Audio::IEncode *)(p.getData());
            return (true);
        }
        return (false);
    }

#define DEFAULT_BUFFER_SIZE (42000 * 5)

    bool
    Kernel::call(const QString &)
    {
        byte      *buffer;
        unsigned int size;

        buffer = new byte[DEFAULT_BUFFER_SIZE * sizeof(SAMPLE)];
        while (42)
        {
            QTime dieTime= QTime::currentTime().addMSecs(100);
            while( QTime::currentTime() < dieTime )
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
            size = this->inputStream->read(buffer, DEFAULT_BUFFER_SIZE);
            this->outputStream->write(buffer, size);
        }
    }
}
}
}
}
