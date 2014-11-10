#include "Babel/Audio/PortAudio/Stream.hh"

namespace Babel
{
  namespace Audio
  {
    namespace PortAudio
    {

      Stream::Stream(PaStreamParameters *param, Stream::Type type, int size)
      {
	this->param = param;
	this->type = type;

	this->buffer.idx = 0;
	this->buffer.max_idx = size;
	this->buffer.data = new SAMPLE[this->buffer.max_idx + 1];
	bzero(this->buffer.data, sizeof(SAMPLE) * this->buffer.max_idx);

	this->buffer.parent = NULL;
	this->buffer.mutex = new pthread_mutex_t;
	pthread_mutex_init(this->buffer.mutex, NULL);
      }

      Stream::Stream(const Stream &parent)
      {
	this->buffer.mutex = parent.buffer.mutex;
	pthread_mutex_lock(this->buffer.mutex);
	this->buffer.parent = &parent.buffer;
	this->buffer.idx = this->buffer.parent->idx;
	this->buffer.max_idx = this->buffer.parent->max_idx;
	this->buffer.data = this->buffer.parent->data;
	pthread_mutex_unlock(this->buffer.mutex);
      }

      Stream::~Stream()
      {
	if (this->buffer.parent == NULL)
	  {
	    Pa_CloseStream(this->PA_stream);
	    delete[] this->buffer.data;
	    pthread_mutex_destroy(this->buffer.mutex);
	    delete this->buffer.mutex;
	  }
      }

      bool			Stream::start(DAT_FCT fct)
      {
	int			err;

	err = Pa_OpenStream(
			    &this->PA_stream,
			    this->type == INPUT ? this->param : NULL,
			    this->type == OUTPUT ? this->param : NULL,
			    SAMPLE_RATE,
			    FRAMES_PER_BUFFER,
			    paClipOff,
			    fct,
			    &this->buffer
			    );
	if (err != paNoError)
	  {
	    std::cout << "error for opening stream : " << err << std::endl;
	    return false;
	  }
	err = Pa_StartStream(this->PA_stream);
	if (err != paNoError)
	  {
	    std::cout << "error for start stream" << std::endl;
	    return false;
	  }
	return (true);
      }

      int			Stream::read(byte *r, int size)
      {
	int			idx_parent;
	int			max_read;
	byte			*d_data;

	d_data = (byte*)(this->buffer.data);
	pthread_mutex_lock(this->buffer.mutex);
	idx_parent = this->buffer.parent->idx;
	pthread_mutex_unlock(this->buffer.mutex);
	if (this->buffer.idx < idx_parent)
	  max_read = idx_parent - this->buffer.idx;
	else
	  max_read = this->buffer.max_idx - this->buffer.idx + idx_parent;
	max_read *= sizeof(SAMPLE);
	if (size > max_read)
	  size = max_read;
	if (size <= 1)
	  return (0);
	int i = 0;
	while (i < size)
	  {
	    for (unsigned int n = 0; n < sizeof(SAMPLE); n += 1)
	      {
		r[i] = d_data[(this->buffer.idx * sizeof(SAMPLE)) + n];
		i += 1;
	      }
	    this->buffer.idx += 1;
	    if (this->buffer.idx > this->buffer.max_idx)
	      this->buffer.idx = 0;
	  }
	return (size);
      }

      int			Stream::read(SAMPLE *r, int size)
      {
	int			idx_parent;
	int			max_read;

	pthread_mutex_lock(this->buffer.mutex);
	idx_parent = this->buffer.parent->idx;
	pthread_mutex_unlock(this->buffer.mutex);
	if (this->buffer.idx < idx_parent)
	  max_read = idx_parent - this->buffer.idx;
	else
	  max_read = this->buffer.max_idx - this->buffer.idx + idx_parent;
	if (size > max_read)
	  size = max_read;
	if (size <= 1)
	  return (0);
	for (int i = 0; i < size; i += 1)
	  {
	    r[i] = this->buffer.data[this->buffer.idx];
	    this->buffer.idx += 1;
	    if (this->buffer.idx > this->buffer.max_idx)
	      this->buffer.idx = 0;
	  }
	return (size);
      }

      int			Stream::write(byte *data, int size)
      {
	byte			*d_data;

	d_data = (byte*)(this->buffer.data);
	this->flush();
	this->buffer.idx = (this->buffer.idx + FRAMES_PER_BUFFER) % this->buffer.max_idx;
	int i = 0;
	while(i < size)
	  {
	    for (unsigned int n = 0; n < sizeof(SAMPLE); n += 1)
	      {
		d_data[this->buffer.idx * sizeof(SAMPLE) + n] = data[i];
		i += 1;
	      }
	    this->buffer.idx += 1;
	    if (this->buffer.idx > this->buffer.max_idx)
	      this->buffer.idx = 0;
	  }
	return (size);
      }

      int			Stream::write(SAMPLE *data, int size)
      {
	this->flush();
	this->buffer.idx = (this->buffer.idx + FRAMES_PER_BUFFER) % this->buffer.max_idx;
	for(int i = 0; i < size; i += 1)
	  {
	    this->buffer.data[this->buffer.idx] = data[i];
	    this->buffer.idx += 1;
	    if (this->buffer.idx > this->buffer.max_idx)
	      this->buffer.idx = 0;
	  }
	return (size);
      }

      void			Stream::flush()
      {
	if (this->buffer.parent == NULL)
	  return ;
	pthread_mutex_lock(this->buffer.mutex);
	this->buffer.idx = this->buffer.parent->idx;
	pthread_mutex_unlock(this->buffer.mutex);
      }


    }
  }
}
