#pragma once

#include "stdafx.h"

HRESULT InitDirectInput();
VOID FreeDirectInput();
void UpdateJoystick();
bool getValue(int nJoy, GUID Guid, float *fValue);
