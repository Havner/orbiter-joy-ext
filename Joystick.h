#pragma once

#include "stdafx.h"

// TODO, no way to get the second slider
bool getValue(int nJoy, GUID Guid, float *fValue);

HRESULT InitDirectInput();
VOID FreeDirectInput();
void UpdateJoystick();
