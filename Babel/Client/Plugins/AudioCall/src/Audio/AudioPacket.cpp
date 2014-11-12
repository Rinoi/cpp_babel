#include "../../inc/Babel/Audio/AudioPacket.hh"
#include "../../inc/Babel/Audio/Opus/Encode.hh"



namespace Babel
{
  namespace Audio
  {
    IEncode	*AudioPacket::encodeur = NULL;
    
    AudioPacket::AudioPacket()
    {
      if (this->encodeur == NULL)
	this->encodeur = new Babel::Audio::Opus::Encode(SAMPLE_RATE * 0.01);
      this->prev_size = 0;
      this->alloc = false;
    }

    AudioPacket::AudioPacket(SAMPLE *data, unsigned int size)
    {
      if (this->encodeur == NULL)
	this->encodeur = new Babel::Audio::Opus::Encode(SAMPLE_RATE * 0.01);
      this->prev_size = 0;
      this->alloc = false;
      this->encode(data, size);
    }
    

    AudioPacket::AudioPacket(const AudioPacket &p)
    {
      this->prev_size = p.prev_size;
      this->pack = p.pack;
      this->alloc = false;
    }

    AudioPacket::~AudioPacket()
    {
      this->clear();
    }

    const AudioPacket	&AudioPacket::operator=(const AudioPacket &p)
    {
      this->clear();
      this->prev_size = p.prev_size;
      this->pack = p.pack;
      this->alloc = false;
      return (*this);
    }
    
    bool		AudioPacket::encode(SAMPLE *data, unsigned int size)
    {
      this->pack = this->encodeur->encode(data, size);
      if (this->pack.size() == 0)
	return (false);
      this->alloc = true;
      this->prev_size = size;
      return (true);
    }
    
    SAMPLE		*AudioPacket::decode(unsigned int *size) const
    {
      return (this->encodeur->decode(this->pack, size));
      *size = this->prev_size;
    }

    void		AudioPacket::clear()
    {
      if (this->alloc == true)
	{
	  std::list<Babel::Audio::IEncode::t_packet>::iterator it;

	  it = this->pack.begin();
	  while (it != this->pack.end())
	    {
	      delete[] (*it).data;
	      it++;
	    }
	  this->pack.clear();
	  this->alloc = false;
	}
      this->prev_size = 0;
    }

    const byte		*AudioPacket::serialize() const
    {
      unsigned int	size;
      std::list<Babel::Audio::IEncode::t_packet>::const_iterator	it;
      byte		*r;
      byte		*tmp;

      size = 0;
      it = this->pack.begin();
      while (it != this->pack.end())
	{
	  size += (*it).size + sizeof(unsigned int);
	  it++;
	}
      r = new byte[size];
      tmp = r;
      this->serializeSize = size;
      it = this->pack.begin();
      while (it != this->pack.end())
	{
	  *((unsigned int *)(r)) = (*it).size;
	  r += sizeof(unsigned int);
	  
	  byte	*data = (*it).data;
	  for (unsigned int i = 0; i < (*it).size; i += 1)
	    *r++ = *data++;
	  it++;
	}
      return (tmp);
    }

    void		AudioPacket::deserialize(const byte *data, unsigned int size)
    {
      this->clear();
      while (size > 0)
	{
	  Babel::Audio::IEncode::t_packet	pack;
	  unsigned int				size_p;
	  byte					*data_p;
	  byte					*tmp;

	  size_p = *((unsigned int *)(data));
	  data += sizeof(unsigned int);
	  size -= sizeof(unsigned int);
	  data_p = new byte[size_p];
	  tmp = data_p;
	  for (unsigned int i = 0; i < size; i += 1)
	    *data_p++ = *data++;
	  pack.size = size_p;
	  pack.data = tmp;
	  this->pack.push_back(pack);
	}
    }

  }
}
