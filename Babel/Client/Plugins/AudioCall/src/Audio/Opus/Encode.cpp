#include <iostream>


#include "../../../inc/Babel/Audio/Opus/Encode.hh"




namespace Babel
{
  namespace Audio
  {
    namespace Opus
    {

      Encode::Encode(int nb_frame)
      {
	this->nb_frame = nb_frame;
      }

      Encode::~Encode()
      {

      }

      std::list<Babel::Audio::IEncode::t_packet>
      Encode::encode(SAMPLE *data, unsigned int sss) const
      {
	std::list<Babel::Audio::IEncode::t_packet>	r;
	OpusEncoder					*enc;
	int						error;
	int						s;
	int						size;

	size = sss;
	enc = opus_encoder_create(SAMPLE_RATE, 2, OPUS_APPLICATION_VOIP, &error);
	if (enc == NULL)
	  return (r);
	while (size > 0)
	  {
	    t_packet        packet;
	    int             nb_frame;

	    nb_frame = this->nb_frame;
	    packet.data = new unsigned char[nb_frame];
	    s = opus_encode_float(
				  enc,
				  data,
				  nb_frame,
				  packet.data,
				  nb_frame
				  );
	    if (s <= 0)
	      {
		opus_encoder_destroy(enc);
		return (r);
	      }
	    packet.size = s;
	    data += nb_frame;
	    size -= nb_frame;
	    r.push_back(packet);
	  }
	opus_encoder_destroy(enc);
	return (r);
      }

      SAMPLE
      *Encode::decode(const std::list<Babel::Audio::IEncode::t_packet> &packet, unsigned int *size) const
      {
	OpusDecoder				*dec;
	int					error;
	SAMPLE					*r;

	std::list<Babel::Audio::IEncode::t_packet>::const_iterator
						it;
	int					s;

	(void) error;
	r = NULL;
	*size = 0;
	dec = opus_decoder_create(SAMPLE_RATE, 2, &error);
	if (dec == NULL || packet.size() == 0)
	  return (r);
	r = new SAMPLE[(unsigned int)(packet.size() * 1.5 * this->nb_frame)];
	it = packet.begin();
	while (it != packet.end())
	  {
	    Babel::Audio::IEncode::t_packet	pack;

	    pack = (*it);
	    s = opus_decode_float(
				  dec,
				  pack.data,
				  pack.size,
				  r + *size,
				  this->nb_frame,
				  0
				  );
	    if (s > 0)
	      *size += s;
	    else
	      {
		delete[] r;
		return (NULL);
	      }
	    it++;
	  }
	opus_decoder_destroy(dec);
	return (r);
      }

    }
  }
}
