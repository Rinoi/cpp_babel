#ifndef __ISTREAM__
# define __ISTREAM__

typedef unsigned char byte;

namespace Babel
{

  class		IStream
  {
  public:
    virtual	~IStream() {}

    virtual int			read(byte *buff, int size) = 0;

    virtual int			write(byte *buff, int size) = 0;
      
    virtual void		flush() = 0;

  };

}

#endif
