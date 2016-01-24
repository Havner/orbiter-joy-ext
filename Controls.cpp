#include "stdafx.h"

#include "Controls.h"

void setRudder(VESSEL *vessel, float value)
{
	double newVal = value * 2.0 - 1.0;
	int attMode = vessel->GetAttitudeMode();

	if (vessel->GetADCtrlMode() & 0x02)
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

void setLeftWheelBrake(VESSEL *vessel, float value)
{
	vessel->SetWheelbrakeLevel(value, 1);
}

void setRightWheelBrake(VESSEL *vessel, float value)
{
	vessel->SetWheelbrakeLevel(value, 2);
}
