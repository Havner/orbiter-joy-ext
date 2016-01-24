#include "stdafx.h"

#include <Orbitersdk.h>

#define BIT_ELEVATOR 0x01
#define BIT_RUDDER   0x02
#define BIT_AILERON  0x04


typedef void (*setOAPIValue)(VESSEL *vessel, float value);

void setRudder(VESSEL *vessel, float value);
void setLinHorizon(VESSEL *vessel, float value);
void setHover(VESSEL *vessel, float value);
void setRetro(VESSEL *vessel, float value);
void setLeftWheelBrake(VESSEL *vessel, float value);
void setRightWheelBrake(VESSEL *vessel, float value);

void resetControls(VESSEL *vessel);
