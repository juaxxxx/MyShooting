#include "pch.h"
#include "GameOverText.h"
#include "GameScene.h"
#include "TextureResource.h"
#include "ResourceManager.h"
#include "Player.h"
#include "UObject.h"

void GameOverText::Init(float posX, float posY)
{
	_pos = Vector(posX, posY);

}

void GameOverText::Render(HDC hdc)
{
	GameScene* gameScene = GameScene::GetGameScene();
	Player* player = dynamic_cast<Player*>(gameScene->GetPlayer());

	if (nullptr == player || player->GetHp() == 0)
	{
		// 임시 게임오버 UI
		wstring str = L"GAME OVER";
		::TextOut(hdc, _pos.x, _pos.y, str.c_str(), static_cast<int32>(str.size()));
	}
}
