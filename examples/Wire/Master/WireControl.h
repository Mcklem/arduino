#ifndef WireControl_h
#define WireControl_h

class WireControl
{
	public:
		static void sendWireMessage(int device, String message);
		static String readWireMessage();	
};

#endif
