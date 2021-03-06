#include "SharedData.h"

void Button::Set(float factorMinX, float factorMaxX, float factorMinY, float factorMaxY)
{
    minX = SharedData::GetInstance()->width * factorMinX;
    maxX = SharedData::GetInstance()->width * factorMaxX;

    minY = SharedData::GetInstance()->height * factorMinY;
    maxY = SharedData::GetInstance()->height * factorMaxY;
}