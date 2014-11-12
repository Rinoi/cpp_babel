#ifndef __OPUS_ENCODE__
# define __OPUS_ENCODE__

#include "Babel/Audio/IEncode.hpp"
#ifdef Q_WS_WIN
#include <opus.h>
#else
#include <opus/opus.h>
#endif

#define SAMPLE_RATE     (48000)

namespace Babel
{
  namespace Audio
  {
    namespace Opus
    {

      class    	Encode : public Babel::Audio::IEncode
      {
      public:

	Encode(int nb_frame);
	~Encode();

	std::list<Babel::Audio::IEncode::t_packet>
	encode(SAMPLE *data, unsigned int size) const;

	SAMPLE
	*decode(const std::list<Babel::Audio::IEncode::t_packet> &packet, unsigned int *size) const;

      private:
	int	nb_frame;
      };
    }
  }
}

#endif
