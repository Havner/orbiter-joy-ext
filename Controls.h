#include "stdafx.h"

#include <Orbitersdk.h>

typedef void (*setOAPIValue)(VESSEL *vessel, float value);

void setRudder(VESSEL *vessel, float value);
void setLinHorizon(VESSEL *vessel, float value);
void setHover(VESSEL *vessel, float value);
void setRetro(VESSEL *vessel, float value);
void setLeftWheelBrake(VESSEL *vessel, float value);
void setRightWheelBrake(VESSEL *vessel, float value);
