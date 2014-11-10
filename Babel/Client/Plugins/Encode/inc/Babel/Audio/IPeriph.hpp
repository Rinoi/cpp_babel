#ifndef __AUDIO_IPERIPH__
# define __AUDIO_IPERIPH__

# include <iostream>

# include "Babel/IPeriph.hpp"
# include "Babel/Audio/IStream.hpp"

namespace Babel
{
  namespace Audio
  {
    class      	IPeriph : public Babel::IPeriph
    {
    public:
      virtual	~IPeriph() {}

      virtual const std::string	&getName() = 0;

      virtual bool		isActivate() = 0;

      virtual void		changeActivity() = 0;

      virtual Babel::IStream	*getStream() = 0;
    };
  }
}

#endif
