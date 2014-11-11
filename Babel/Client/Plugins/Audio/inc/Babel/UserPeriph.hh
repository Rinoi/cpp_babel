#ifndef __USER_PERIPH__
# define __USER_PERIPH__

# include <iostream>
# include <list>

//#include "../../inc/Babel/Audio/Input/PortAudio/Periph.hh"
//#include "../../inc/Babel/Audio/Output/PortAudio/Periph.hh"
#include "../../inc/Babel/IPeriph.hpp"

namespace Babel
{

  class		UserPeriph
  {
  public:

		UserPeriph();
		~UserPeriph();

    Babel::IPeriph		*getDefaultAInput();
    Babel::IPeriph		*getDefaultAOutput();

  private:

    std::list<IPeriph *>			periphs;
    Babel::IPeriph		*defaultAInput;
    Babel::IPeriph		*defaultAOutput;

  };

}

#endif
