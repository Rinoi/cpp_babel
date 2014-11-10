#ifndef __AUDIO_ISTREAM__
# define __AUDIO_ISTREAM__

#include "Babel/IStream.hpp"

typedef float SAMPLE;

namespace Babel
{
  namespace Audio
  {
    class      	IStream : public Babel::IStream
    {
    public:
      virtual	~IStream() {}

      virtual int      		read(byte *buff, int size) = 0;
      virtual int      		read(SAMPLE *buff, int size) = 0;

      virtual int      		write(byte *buff, int size) = 0;
      virtual int      		write(SAMPLE *buff, int size) = 0;
      
      virtual void		flush() = 0;

    };
  }
}

#endif
