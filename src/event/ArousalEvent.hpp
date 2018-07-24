#ifndef __AROUSALEVENT_CLASS__
#define __AROUSALEVENT_CLASS__

class ArousalEvent
{
	public:
		ArousalEvent(float value);
		float get_value() const;
	private:
		float _value;
};

#endif
