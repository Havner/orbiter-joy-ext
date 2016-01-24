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

#define NELEM(X)     (sizeof(X)/sizeof(*(X)))


struct Value
{
	setOAPIValue funct;
	int joy;
	GUID guid;
	bool inv;
} values[] = {
	{ setRudder,          3, GUID_RzAxis, false },
	{ setLinHorizon,      0, GUID_XAxis, false },
	{ setHover,           0, GUID_RxAxis, true },
	{ setRetro,           0, GUID_RyAxis, true },
	{ setLeftWheelBrake,  3, GUID_XAxis, false },
	{ setRightWheelBrake, 3, GUID_YAxis, false },
};

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

	for (int i = 0; i < NELEM(values); ++i)
	{
		float val;
		if (!getValue(values[i].joy, values[i].guid, &val))
			continue;

		if (values[i].inv)
			val = 1.0f - val;

		values[i].funct(vessel, val);
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
