#include "stdafx.h"

#include <Orbitersdk.h>

#define BIT_ELEVATOR 0x01
#define BIT_RUDDER   0x02
#define BIT_AILERON  0x04


typedef void (*setOAPIValue)(VESSEL *vessel, float value);

// Main controls
void setElevator(VESSEL *vessel, float value);
void setAileron(VESSEL *vessel, float value);
void setRudder(VESSEL *vessel, float value);

// For use with the default joystick implementation in orbiter for aileron axis
void setLinHorizon(VESSEL *vessel, float value);

// Throttles
void setThrottle(VESSEL *vessel, float value);
void setHover(VESSEL *vessel, float value);
void setRetro(VESSEL *vessel, float value);

// Misc
void setLeftWheelBrake(VESSEL *vessel, float value);
void setRightWheelBrake(VESSEL *vessel, float value);

// Resets controls on switch change to off
void resetControls(VESSEL *vessel);
