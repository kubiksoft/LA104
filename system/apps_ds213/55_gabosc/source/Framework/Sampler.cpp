#include <Library.h>

namespace Sampler
{
  BIOS::ADC::TSample::SampleType& GetAt(int)
  {
    static BIOS::ADC::TSample::SampleType v{0};
    return v;
  }
}

// TODO: move
namespace CUtils
{
	extern char tmp[16];
	

/*static*/ char* MidiNote(int n)
{
	const static char notes[] = "C-" "C#" "D-" "D#" "E-" "F-" "F#" "G-" "G#" "A-" "A#" "B-";
	if ( n < 12 || n >= 78 )
	{
		tmp[0] = '?';
		tmp[1] = 0;
		return tmp;
	}
	int nOctave = (n / 12)-1;
	int nNote = n % 12;
	tmp[0] = notes[nNote*2];
	tmp[1] = notes[nNote*2+1];
	tmp[2] = '0' + nOctave;
	tmp[3] = 0;
	return tmp;
}
}