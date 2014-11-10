#ifndef __AUDIO_OUTPUT_PORT_AUDIO_PERIPH__
# define __AUDIO_OUTPUT_PORT_AUDIO_PERIPH__

extern "C"
{
 #include <stdio.h>
 #include <stdlib.h>
 #include "portaudio.h"
}

# include "Babel/Audio/Output/APeriph.hpp"
# include "Babel/Audio/PortAudio/Stream.hh"

namespace Babel
{
  namespace Audio
  {
    namespace Output
    {
      namespace PortAudio
      {

	class	Periph : public Babel::Audio::Output::APeriph
	{
	public:
	  Periph(int device);
	  ~Periph();

	  const std::string       &getName();

	  Babel::IStream          *getStream();

	private:
	  void			init();
	  void			destroy();

	private:
	  std::string		name;
	  PaStreamParameters	param;	  

	};

      }
    }
  }
}

#endif
