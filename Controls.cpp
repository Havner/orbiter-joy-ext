#include "stdafx.h"

#include "Controls.h"

void setRudder(VESSEL *vessel, float value)
{
	double newVal = value * 2.0 - 1.0;
	int attMode = vessel->GetAttitudeMode();

	if (vessel->GetADCtrlMode() & BIT_RUDDER)
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

void resetControls(VESSEL *vessel)
{
	bool rcsRot = (vessel->GetAttitudeMode() == RCS_ROT);
	bool rcsLin = (vessel->GetAttitudeMode() == RCS_LIN);
	bool ctlElv = ((vessel->GetADCtrlMode() & BIT_ELEVATOR) == BIT_ELEVATOR);
	bool ctlRud = ((vessel->GetADCtrlMode() & BIT_RUDDER) == BIT_RUDDER);
	bool ctlAil = ((vessel->GetADCtrlMode() & BIT_AILERON) == BIT_AILERON);

	static bool prevRcsRot = rcsRot;
	static bool prevRcsLin = rcsLin;
	static bool prevCtlElv = ctlElv;
	static bool prevCtlRud = ctlRud;
	static bool prevCtlAil = ctlAil;

	if (prevRcsRot != rcsRot && rcsRot == false)
	{
		vessel->SetThrusterGroupLevel(THGROUP_ATT_PITCHUP, 0);
		vessel->SetThrusterGroupLevel(THGROUP_ATT_PITCHDOWN, 0);
		vessel->SetThrusterGroupLevel(THGROUP_ATT_YAWLEFT, 0);
		vessel->SetThrusterGroupLevel(THGROUP_ATT_YAWRIGHT, 0);
		vessel->SetThrusterGroupLevel(THGROUP_ATT_BANKLEFT, 0);
		vessel->SetThrusterGroupLevel(THGROUP_ATT_BANKRIGHT, 0);
	}

	if (prevRcsLin != rcsLin && rcsLin == false)
	{
		vessel->SetThrusterGroupLevel(THGROUP_ATT_RIGHT, 0);
		vessel->SetThrusterGroupLevel(THGROUP_ATT_LEFT, 0);
		vessel->SetThrusterGroupLevel(THGROUP_ATT_UP, 0);
		vessel->SetThrusterGroupLevel(THGROUP_ATT_DOWN, 0);
		vessel->SetThrusterGroupLevel(THGROUP_ATT_FORWARD, 0);
		vessel->SetThrusterGroupLevel(THGROUP_ATT_BACK, 0);
	}

	if (prevCtlElv != ctlElv && ctlElv == false)
		vessel->SetControlSurfaceLevel (AIRCTRL_ELEVATOR, 0);

	if (prevCtlRud != ctlRud && ctlRud == false)
		vessel->SetControlSurfaceLevel (AIRCTRL_RUDDER, 0);

	if (prevCtlAil != ctlAil && ctlAil == false)
		vessel->SetControlSurfaceLevel (AIRCTRL_AILERON, 0);

	prevRcsRot = rcsRot;
	prevRcsLin = rcsLin;
	prevCtlElv = ctlElv;
	prevCtlRud = ctlRud;
	prevCtlAil = ctlAil;
}
