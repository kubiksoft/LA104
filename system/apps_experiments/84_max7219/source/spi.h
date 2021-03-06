class CPinIoBase
{
public:
    enum EPin {SCK, MOSI, MISO, CS};
    enum EDir {Input, Output};
    
    virtual void Init() = 0;
    virtual void PinMode(EPin p, EDir d) = 0;
    virtual void Set(EPin p, bool b) = 0;
};

class CPinIoGpio : public CPinIoBase
{
public:
    virtual void Init() override
    {
    }

    BIOS::GPIO::EPin Pin(EPin p)
    {
        switch (p)
        {
            case CPinIoBase::SCK: return BIOS::GPIO::EPin::P1;
            case CPinIoBase::CS: return BIOS::GPIO::EPin::P2;
            case CPinIoBase::MOSI: return BIOS::GPIO::EPin::P3;
            default:
                _ASSERT(0);
                return BIOS::GPIO::EPin::P1;
        }
    }
    
    virtual void PinMode(EPin p, EDir d) override
    {
        if (d == EDir::Input)
            BIOS::GPIO::PinMode(Pin(p), BIOS::GPIO::EMode::Input);
        else
            BIOS::GPIO::PinMode(Pin(p), BIOS::GPIO::EMode::Output);
    }
    
    virtual void Set(EPin p, bool b) override
    {
        BIOS::GPIO::DigitalWrite(Pin(p), b);
    }
};

class CSpi : public CPinIoGpio
{
  // https://github.com/Flickerstrip/SoftwareSPI/blob/master/SoftwareSPI.cpp
public:

  void begin() 
  {
      PinMode(CPinIoBase::CS, CPinIoBase::Output);
      PinMode(CPinIoBase::SCK, CPinIoBase::Output);
      PinMode(CPinIoBase::MOSI, CPinIoBase::Output);

      Set(CPinIoBase::CS, true);
      Set(CPinIoBase::SCK, true);
      Set(CPinIoBase::MOSI, false);
      deselect();
  }
    
    void end()
    {
        PinMode(CPinIoBase::CS, CPinIoBase::Input);
        PinMode(CPinIoBase::SCK, CPinIoBase::Input);
        PinMode(CPinIoBase::MOSI, CPinIoBase::Input);
        PinMode(CPinIoBase::MISO, CPinIoBase::Input);
    }

  uint8_t transfer(uint8_t b) 
  {
    uint8_t rec = 0;

    for (int i = 0; i < 8; i++) 
    {
        Set(CPinIoBase::MOSI, b & (1<<(7-i))); //MSB first
        Set(CPinIoBase::SCK, true);
        Set(CPinIoBase::SCK, false);
    }
      
    return rec;
  }

  void select() 
  {
      Set(CPinIoBase::CS, false);
  }

  void deselect() 
  {
      Set(CPinIoBase::CS, true);
  }
};

