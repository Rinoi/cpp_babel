#include <unistd.h>
#include "Babel/UserPeriph.hh"
#include "Babel/Audio/AudioPacket.hh"

int main()
{
  Babel::UserPeriph		user_periph;
  Babel::Audio::IStream		*in;
  Babel::Audio::IStream		*out;
  SAMPLE       			*buffer;
  unsigned int		       	size;

  in =  (Babel::Audio::IStream *)user_periph.getDefaultAInput()->getStream();
  out = (Babel::Audio::IStream *)user_periph.getDefaultAOutput()->getStream();
  buffer = new SAMPLE[DEFAULT_BUFFER_SIZE * sizeof(SAMPLE)];
  while (42)
    {
      Pa_Sleep(100);
      size = in->read(buffer, DEFAULT_BUFFER_SIZE * sizeof(SAMPLE));
      if (size > 0)
  	{
  	  std::cout << "size : " << size << std::endl;

  	  Babel::Audio::AudioPacket	packet(buffer, size);

  	  buffer = packet.decode(&size);
  	  out->write(buffer, size);
  	}
    }
  return (0);
}
