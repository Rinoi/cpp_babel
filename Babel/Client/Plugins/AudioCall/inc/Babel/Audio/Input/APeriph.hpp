#ifndef __AUDIO_INPUT_APERIPH__
# define __AUDIO_INPUT_APERIPH__

# include <cstdlib>

# include <iostream>


#include "Babel/IStream.hpp"

#include "Babel/Audio/IPeriph.hpp"

namespace Babel
{
  namespace Audio
  {
    namespace Input
    {

      class	APeriph : public Babel::Audio::IPeriph
      {
      public:
        APeriph()
	{this->stream = NULL; this->activity = false;}

	APeriph(Babel::Audio::IStream *stream)
	{this->stream = stream; this->activity = false;}

	virtual	~APeriph()
	{
	  if (this->activity == true)
	    this->changeActivity();
	}

	virtual const std::string	&getName() = 0;
    
	virtual bool			isActivate()
	{return (this->activity);}

	void				changeActivity()
	{
	  this->activity = !this->activity;
	  if (this->activity == true)
	    this->init();
	  else
	    this->destroy();
	}

	virtual Babel::IStream			*getStream()
	{return (this->stream);}

      protected:

	virtual void			init() = 0;
	virtual void			destroy() = 0;

      protected:
	
	bool				activity;
	Babel::Audio::IStream	       	*stream;
      };
    }
  }
}

#endif
