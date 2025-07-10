#include "pch.h"
#include "HpHeart.h"
#include "GameScene.h"
#include "TextureResource.h"
#include "ResourceManager.h"
#include "Player.h"
#include "UObject.h"

void HpHeart::Init(float posX, float posY)
{
	_pos = Vector(posX, posY);

	_texture = ResourceManager::GetInstance()->GetTexture("PlayerHp");
}


void HpHeart::Render(HDC hdc)
{
	if (_texture)
	{
		GameScene* gameScene = GameScene::GetGameScene();
		Player* player = dynamic_cast<Player*>(gameScene->GetPlayer());
		if (nullptr == player) return;

		switch (player->GetHp())
		{
		case 3:
			_texture->Render(hdc, _pos + Vector(-30, 0));
		case 2:
			_texture->Render(hdc, _pos);
		case 1:
			_texture->Render(hdc, _pos + Vector(30, 0));
			break;
		}
	}
}
