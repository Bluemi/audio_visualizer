#ifndef __BEATEVENT_CLASS__
#define __BEATEVENT_CLASS__

class BeatEvent
{
	public:
		BeatEvent(float relative_amplitude);
		float get_relative_amplitude() const;
	private:
		float _relative_amplitude;
};

#endif
