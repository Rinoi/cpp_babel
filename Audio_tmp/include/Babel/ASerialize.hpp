#ifndef __A_SERIALIZE__
# define __A_SERIALIZE__

namespace Babel
{
  class ASerialize
  {
  public:
    ASerialize()
    {this->serializeSize = 0;}

    virtual ~ASerialize()
    {}

    virtual const byte		*serialize() const = 0;

    virtual void       		deserialize(const byte *data, unsigned int size) = 0;

    unsigned int		getSerializeSize() const
    {return (this->serializeSize);}

  protected:
    mutable unsigned int	serializeSize;
  };
}

#endif
