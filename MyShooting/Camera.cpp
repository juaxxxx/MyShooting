#include "pch.h"
#include "Camera.h"

Vector Camera::_cameraPos = Vector(0, 0);

void Camera::Update(Vector playerPos, Vector mapSize)
{
	_cameraPos = playerPos;

	float halfSizeX = GWinSizeX / 2;
	float halfSizeY = GWinSizeY / 2;

	_cameraPos.x = clamp(_cameraPos.x, halfSizeX, mapSize.x - halfSizeX);
	_cameraPos.y = clamp(_cameraPos.y, halfSizeX, mapSize.y - halfSizeY);
}

Vector Camera::ConvertScreenPos(Vector worldPos)
{
	Vector convertPos;
	convertPos.x = worldPos.x - (_cameraPos.x - (GWinSizeX / 2));
	convertPos.y = worldPos.y - (_cameraPos.y - (GWinSizeY / 2));
	
	return convertPos;
}
