#ifndef __IENCODE__
# define __IENCODE__

typedef unsigned char byte;
typedef float SAMPLE;

#include <iostream>
#include <list>

namespace Babel
{
  namespace Audio
  {

    class	IEncode
    {
    public:
      typedef struct      s_packet
      {
	byte		*data;
	unsigned int	size;
      } t_packet;
      
    public:

      virtual ~IEncode() {}

      virtual std::list<t_packet>	encode(SAMPLE *data, unsigned int size) const = 0;
      virtual SAMPLE			*decode(const std::list<t_packet> &packet, unsigned int *size) const = 0;
    };

  }
}

#endif
