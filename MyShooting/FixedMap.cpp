#include "pch.h"
#include "FixedMap.h"
#include "Game.h"
#include "GameScene.h"
#include "TextureResource.h"
#include "ResourceManager.h"

void FixedMap::Init(float posX, float posY)
{
	_pos.x = posX;
	_pos.y = posY;
	_speed = 30.f;
	_layer = LAYER_TYPE::BACKGROUND;

	_texture = ResourceManager::GetInstance()->GetTexture("BG_2");
}
void FixedMap::Update(float deltaTime)
{
	_pos.y += (_speed * deltaTime);
}
void FixedMap::Render(HDC hdc)
{
	if (_texture) _texture->Render(hdc, _pos);
}