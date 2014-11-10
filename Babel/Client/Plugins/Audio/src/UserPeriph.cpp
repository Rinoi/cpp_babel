#include "../inc/Babel/UserPeriph.hh"

namespace Babel
{
  UserPeriph::UserPeriph()
  {
    int         err;

    err = Pa_Initialize();
    if (err != paNoError)
      {
	std::cout << "cannot init pa" << std::endl;
        return ;
      }
    this->defaultAInput = new Babel::Audio::Input::PortAudio::Periph(Pa_GetDefaultInputDevice());
    this->defaultAInput->changeActivity();
    this->defaultAOutput = new Babel::Audio::Output::PortAudio::Periph(Pa_GetDefaultOutputDevice());
    this->defaultAOutput->changeActivity();
  }

  UserPeriph::~UserPeriph()
  {

  }

  Audio::Input::APeriph		*UserPeriph::getDefaultAInput()
  {
    return (this->defaultAInput);
  }

  Audio::Output::APeriph       	*UserPeriph::getDefaultAOutput()
  {
    return (this->defaultAOutput);
  }

}
