// ==============================================================
// JoyExt.cpp
//
// A small plugin which extends orbiter's joystick support
// ==============================================================

#include "stdafx.h"

#include "Joystick.h"
#include "Config.h"

#define ORBITER_MODULE
#include <Orbitersdk.h>

#define NELEM(X)     (sizeof(X)/sizeof(*(X)))


typedef void (*setOAPIValue)(VESSEL *vessel, float value);

// ==============================================================
// Helpers for the OAPI

void setRudder(VESSEL *vessel, float value)
{
	double newVal = value * 2.0 - 1.0;
	int attMode = vessel->GetAttitudeMode();

	vessel->SetControlSurfaceLevel (AIRCTRL_RUDDER, newVal);

	switch (attMode)
	{
	case RCS_NONE:
	case RCS_LIN:
		break;
	case RCS_ROT:
		if (newVal < 0)
			vessel->SetThrusterGroupLevel(THGROUP_ATT_YAWLEFT, newVal * -1);
		else
			vessel->SetThrusterGroupLevel(THGROUP_ATT_YAWRIGHT, newVal);
		break;
	default:
		break;
	}
}

void setLinHorizon(VESSEL *vessel, float value)
{
	double newVal = value * 2.0 - 1.0;
	int attMode = vessel->GetAttitudeMode();

	switch (attMode)
	{
	case RCS_NONE:
	case RCS_ROT:
		break;
	case RCS_LIN:
		if (newVal < 0)
			vessel->SetThrusterGroupLevel(THGROUP_ATT_LEFT, newVal * -1);
		else
			vessel->SetThrusterGroupLevel(THGROUP_ATT_RIGHT, newVal);
		break;
	default:
		break;
	}
}

void setHover(VESSEL *vessel, float value)
{
	vessel->SetThrusterGroupLevel (THGROUP_HOVER, value);
}

void setRetro(VESSEL *vessel, float value)
{
	vessel->SetThrusterGroupLevel (THGROUP_RETRO, value);
}

struct Value
{
	setOAPIValue funct;
	int joy;
	GUID guid;
	bool inv;
} values[] = {
	{ setRudder, 3, GUID_RzAxis, false },
	{ setLinHorizon, 0, GUID_XAxis, false },
	{ setHover, 0, GUID_RxAxis, true },
	{ setRetro, 0, GUID_RyAxis, true }
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
