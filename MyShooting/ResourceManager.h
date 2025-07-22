#pragma once

#include "Singleton.h"

// ���ҽ� ������ ���ӿ��� �پ��ϰ� ����.
// �ؽ�ó / �޽� / ���� / ����Ʈ ���..
// ��� ���ҽ����� �����ϴ� �Ŵ���
class ResourceManager : public Singleton<ResourceManager>
{
	friend Singleton<ResourceManager>;
	ResourceManager() {}
public:

	void Init();
	void Destroy();	// ���ҽ� ����

	class TextureResource* GetTexture(string meshName);
	void LoadTexture(string key, string texturePath, int32 transparent, int32 xFrameCount = 1, int32 yFrameCount = 1);

private:
	unordered_map<string, class TextureResource*> _textures;
};

