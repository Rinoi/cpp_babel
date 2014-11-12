#ifndef __IPERIPH__
# define __IPERIPH__

# include <iostream>

# include "Babel/IStream.hpp"

namespace Babel
{

  class		IPeriph
  {
  public:
    virtual	~IPeriph() {}

    virtual const std::string	&getName() = 0;
    
    virtual bool		isActivate() = 0;

    virtual void		changeActivity() = 0;

    virtual IStream		*getStream() = 0;

  };

}

#endif
