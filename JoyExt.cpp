// ==============================================================
// JoyExt.cpp
//
// A small plugin which extends orbiter's joystick support
// ==============================================================

#include "stdafx.h"

#define ORBITER_MODULE
#include <Orbitersdk.h>

#include "Controls.h"
#include "Joystick.h"


struct Configuration
{
	setOAPIValue funct;
	int joy;
	GUID guid;
	bool inv;
};

// This config can be used with Orbiter's joystick implementation
// it complements it, pressuming that rudder is on separate device.
// It adds some custom stuff.
struct Configuration config1[] = {
	{ setRudder,          3, GUID_RzAxis, false },
	{ setLinHorizon,      0, GUID_XAxis,  false },
	{ setHover,           0, GUID_RxAxis, true  },
	{ setRetro,           0, GUID_RyAxis, true  },
	{ setLeftWheelBrake,  3, GUID_XAxis,  false },
	{ setRightWheelBrake, 3, GUID_YAxis,  false },
	{ NULL }
};

// This re-implements everything. Orbiter's joystick implementation
// is not used here at all, should be disabled.
struct Configuration config2[] = {
	{ setElevator,        0, GUID_YAxis,  false },
	{ setAileron,         0, GUID_XAxis,  false },
	{ setRudder,          3, GUID_RzAxis, false },
	{ setThrottle,        0, GUID_ZAxis,  true  },
	{ setHover,           0, GUID_RzAxis, true  },
	{ setRetro,           0, GUID_Slider, true  },
	{ setLeftWheelBrake,  3, GUID_XAxis,  false },
	{ setRightWheelBrake, 3, GUID_YAxis,  false },
	{ NULL }
};

// Currently used configuration
struct Configuration *config = config2;


namespace oapi {

// ==============================================================
// The module interface class

class JoyExt : public Module
{
	public:
		JoyExt (HINSTANCE hDLL) : Module (hDLL) {}
		~JoyExt () {}
		void clbkSimulationStart (RenderMode mode);
		void clbkPreStep (double simt, double simdt, double mjd);
};

// ==============================================================
// JoyExt implementation

void JoyExt::clbkSimulationStart (RenderMode mode)
{
}

// Frame update
void JoyExt::clbkPreStep (double simt, double simdt, double mjd)
{
	UpdateJoystick();

	VESSEL *vessel = oapiGetFocusInterface();
	resetControls(vessel);

	for (int i = 0; config[i].funct; ++i)
	{
		float val;
		if (!getValue(config[i].joy, config[i].guid, &val))
			continue;

		if (config[i].inv)
			val = 1.0f - val;

		config[i].funct(vessel, val);
	}
}

}; // namespace oapi


// ==============================================================
// DLL entry and exit 

DLLCLBK void InitModule (HINSTANCE hDLL)
{
	if( FAILED( InitDirectInput() ) )
	{
		MessageBox( NULL, TEXT( "Error Initializing DirectInput." ),
				TEXT( "JoyExt" ), MB_ICONERROR | MB_OK );
	}

	// Register the module
	oapi::JoyExt *joyext = new oapi::JoyExt (hDLL);
	oapiRegisterModule (joyext);
}

DLLCLBK void ExitModule (HINSTANCE hDLL)
{
	FreeDirectInput();
}
