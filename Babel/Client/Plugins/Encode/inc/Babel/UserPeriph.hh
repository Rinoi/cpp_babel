#ifndef __USER_PERIPH__
# define __USER_PERIPH__

# include <iostream>
# include <list>

#include "../../inc/Babel/Audio/Input/PortAudio/Periph.hh"
#include "../../inc/Babel/Audio/Output/PortAudio/Periph.hh"


namespace Babel
{

  class		UserPeriph
  {
  public:

		UserPeriph();
		~UserPeriph();

    Babel::Audio::Input::APeriph		*getDefaultAInput();
    Babel::Audio::Output::APeriph		*getDefaultAOutput();

  private:

    std::list<IPeriph *>			periphs;
    Babel::Audio::Input::APeriph		*defaultAInput;
    Babel::Audio::Output::APeriph		*defaultAOutput;

  };

}

#endif
