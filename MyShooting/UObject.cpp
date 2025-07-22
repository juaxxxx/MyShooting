#include "pch.h"
#include "UObject.h"
#include "UAnimator.h"
#include "TextureResource.h"
#include "Camera.h"

UObject::~UObject()
{
	SAFE_DELETE(_anim);
}

int32 UObject::PosToIndex(float pos)
{
	return (int32)(pos / Grid::CELL_SIZE);
}

int32 UObject::PosToIndex(float pos, bool IsX)
{
	if (IsX)
	{
		Vector convert = Camera::ConvertScreenPos(Vector(pos, 0));
		return (int32)(convert.x / Grid::CELL_SIZE);
	}
	else
	{
		Vector convert = Camera::ConvertScreenPos(Vector(0, pos));
		return (int32)(convert.y / Grid::CELL_SIZE);
	}
}
