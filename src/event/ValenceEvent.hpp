#ifndef __VALENCEEVENT_CLASS__
#define __VALENCEEVENT_CLASS__

class ValenceEvent
{
	public:
		ValenceEvent(float value);
		float get_value() const;
	private:
		float _value;
};

#endif
