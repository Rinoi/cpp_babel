#ifndef __AUDIO_PACKET__
# define __AUDIO_PACKET__

# include <iostream>
# include <list>

# include "Babel/Audio/IEncode.hpp"
# include "Babel/Audio/IStream.hpp"
# include "Babel/ASerialize.hpp"

namespace Babel
{
  namespace Audio
  {

    class	AudioPacket : public Babel::ASerialize
    {

    private:
      static IEncode	*encodeur;

    public:
      AudioPacket();
      AudioPacket(SAMPLE *data, unsigned int size);
      AudioPacket(const AudioPacket &p);
      ~AudioPacket();

      bool		encode(SAMPLE *data, unsigned int size);
      SAMPLE		*decode(unsigned int *size) const;
      void		clear();

      const byte	*serialize() const;
      void		deserialize(const byte *data, unsigned int size);

      const AudioPacket	&operator=(const AudioPacket &p);


    private:
      bool						alloc;
      std::list<Babel::Audio::IEncode::t_packet>	pack;
      unsigned int					prev_size;

    };

  }
}

#endif
