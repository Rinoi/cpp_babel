
#include "../../../../inc/Babel/Audio/Output/PortAudio/Periph.hh"

namespace Babel
{
  namespace Audio
  {
    namespace Output
    {
      namespace PortAudio
      {

	Periph::Periph(int device)
	{
	  const PaDeviceInfo  *deviceInfo;

	  this->activity = false;
	  this->stream = NULL;

	  this->param.device = device;
	  if (this->param.device == paNoDevice)
	    {
	      std::cout << "cannot creat param" << std::endl;
	      return ;
	    }
      else
          std::cout << "DEVICE CREATE" << std::endl;
	  this->param.channelCount = 2; // stereo input                                                                     
	  this->param.sampleFormat = PA_SAMPLE_TYPE;
	  this->param.suggestedLatency = Pa_GetDeviceInfo(this->param.device)->defaultLowInputLatency;
	  this->param.hostApiSpecificStreamInfo = NULL;

	  deviceInfo = Pa_GetDeviceInfo(device);
      this->name = std::string(deviceInfo->name);
	}

	Periph::~Periph()
	{
	  if (this->activity == true)
	    this->changeActivity();
	}

	Babel::IStream		*Periph::getStream()
	{
	  return (new Babel::Audio::PortAudio::Stream((const Babel::Audio::PortAudio::Stream &)(*this->stream)));
	}

	const std::string	&Periph::getName()
	{
	  return (this->name);
	}

	static int playCallback( const void *inputBuffer, void *outputBuffer,
				 unsigned long framesPerBuffer,
				 const PaStreamCallbackTimeInfo* timeInfo,
				 PaStreamCallbackFlags statusFlags,
				 void *userData )
	{
	  Babel::Audio::PortAudio::t_buffer            *self = (Babel::Audio::PortAudio::t_buffer *)(userData);
	  SAMPLE              *output = (SAMPLE *)(outputBuffer);

	  (void) inputBuffer;
	  (void) timeInfo;
	  (void) statusFlags;

      self->mutex->lock();
	  for (unsigned long i = 0; i < framesPerBuffer; i += 1)
	    {
	      for (int nb = NUM_CHANNELS; nb > 0; nb -= 1)
		{
		  *output++ = self->data[self->idx];
		  self->data[self->idx] = SAMPLE_SILENCE;
		  self->idx = self->idx + 1 > self->max_idx ? 0 : self->idx + 1; // buffer circulaire
		}
	    }
      self->mutex->unlock();
	  return (paContinue);
	}

	void			Periph::init()
	{
	  Babel::Audio::PortAudio::Stream *s;

	  s = new Babel::Audio::PortAudio::Stream(&this->param, Babel::Audio::PortAudio::Stream::OUTPUT, DEFAULT_BUFFER_SIZE);
	  s->start(playCallback);
	  this->stream = s;
	}

	void			Periph::destroy()
	{
	  if (this->stream != NULL)
	    delete stream;
	}

      }
    }
  }
}
