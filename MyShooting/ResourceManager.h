#pragma once

#include "Singleton.h"

// 리소스 개념이 게임에서 다양하게 등장.
// 텍스처 / 메시 / 사운드 / 이펙트 등등..
// 모든 리소스들을 관리하는 매니저
class ResourceManager : public Singleton<ResourceManager>
{
	friend Singleton<ResourceManager>;
	ResourceManager() {}
public:

	void Init();
	void Destroy();	// 리소스 정리

	class TextureResource* GetTexture(string meshName);
	void LoadTexture(string key, string texturePath, int32 transparent, int32 xFrameCount = 1, int32 yFrameCount = 1);

private:
	unordered_map<string, class TextureResource*> _textures;
};

