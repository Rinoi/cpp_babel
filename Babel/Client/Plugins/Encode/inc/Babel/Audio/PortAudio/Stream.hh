#ifndef __AUDIO_STREAM_PORT_AUDIO_PERIPH__
# define __AUDIO_STREAM_PORT_AUDIO_PERIPH__

#include <cstdio>
#include <cstdlib>
#include <QMutex>

extern "C"
{
 #include <string.h>
 #include "portaudio.h"
}

#include <iostream>

# define DEFAULT_BUFFER_SIZE    (131072)
// #define SAMPLE_RATE  (44100)

# define SAMPLE_RATE            (48000)
// #define FRAMES_PER_BUFFER (512)

# define FRAMES_PER_BUFFER      (256)
# define NUM_CHANNELS           (2)

# define PA_SAMPLE_TYPE         paFloat32
typedef float SAMPLE;
# define SAMPLE_SILENCE         (0.0f)

typedef int     (*DAT_FCT)(const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData );

#include "../../../../inc/Babel/Audio/IStream.hpp"

namespace Babel
{
  namespace Audio
  {
    namespace PortAudio
    {

      typedef struct s_buffer
      {
	int                         idx;
	int                         max_idx;
	SAMPLE                      *data;
	QMutex                      *mutex;
	const struct s_buffer       *parent;
      } t_buffer;
      
      class Stream : public Babel::Audio::IStream
      {
      public:
	enum Type
	  {
	    OUTPUT, INPUT
	  };

      public:

	Stream(PaStreamParameters *param, Type type, int size);
	Stream(const Stream &parent);
	~Stream();

	bool			start(DAT_FCT fct);

	int			read(SAMPLE *data ,int size);
	int			read(byte *data, int size);
	  
	int			write(SAMPLE *data, int size);
	int			write(byte *data, int size);

	void			flush();

      private:

	t_buffer		buffer;
	Type			type;

	PaStreamParameters	*param;
	PaStream		*PA_stream;
      };

    }
  }
}

#endif
