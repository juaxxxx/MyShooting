#include "pch.h"
#include "Background.h"
#include "Game.h"
#include "GameScene.h"
#include "TextureResource.h"
#include "ResourceManager.h"

void Background::Init(float posX, float posY)
{
	_pos.x = posX;
	_pos.y = posY;
	_speed = 120;

	// Colider Init
	_collider.radius = 0;
	_collider.offset = POINT(0, 0);

	_texture = ResourceManager::GetInstance()->GetTexture("BG");
}

void Background::Update(float deltaTime)
{
	_pos.y += (_speed * deltaTime);


	if (_pos.y >= GWinSizeY + 400.0f)
	{
		_pos.y = -400.0f;
	}

}

void Background::Render(HDC hdc)
{
	if (_texture) _texture->Render(hdc, _pos);
}
