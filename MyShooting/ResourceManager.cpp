#include "pch.h"
#include "ResourceManager.h"
#include "TextureResource.h"

void ResourceManager::Init()
{
    {
        TextureResource* texture = new TextureResource();
        texture->Load(L"Player.bmp");
        _textures["Player"] = texture;
    }
    {
        TextureResource* texture = new TextureResource();
        texture->Load(L"Enemy1.bmp");
        _textures["Enemy1"] = texture;
    }
    {
        TextureResource* texture = new TextureResource();
        texture->Load(L"Enemy2.bmp");
        _textures["Enemy2"] = texture;
    }
    {
        TextureResource* texture = new TextureResource();
        texture->Load(L"Enemy3.bmp");
        _textures["Enemy3"] = texture;
    }
    {
        TextureResource* texture = new TextureResource();
        texture->Load(L"Enemy4.bmp");
        _textures["Enemy4"] = texture;
    }
    {
        TextureResource* texture = new TextureResource();
        texture->Load(L"Playerbullet.bmp");
        _textures["PlayerMISSILE"] = texture;
    }
    {
        TextureResource* texture = new TextureResource();
        texture->Load(L"EnemyBullet.bmp");
        _textures["EnemyMISSILE"] = texture;
    }
    {
        TextureResource* texture = new TextureResource();
        texture->Load(L"BG.bmp");
        _textures["BackGround"] = texture;
    }
    {
        TextureResource* texture = new TextureResource();
        texture->Load(L"explosion.bmp");
        _textures["Explosion"] = texture;
    }
    {
        TextureResource* texture = new TextureResource();
        texture->Load(L"PlayerHp.bmp");
        _textures["PlayerHp"] = texture;
    }
}

void ResourceManager::Destroy()
{
    for (auto& iter : _textures)
    {
        SAFE_DELETE(iter.second);
        //delete iter.second;
    }
    _textures.clear();
}

TextureResource* ResourceManager::GetTexture(string meshName)
{
    // 전체적으로 관리하고 있는 모든 라인메시중에 meshName 해당하는 리소스를 반환한다.
    auto iter = _textures.find(meshName);
    if (iter != _textures.end())
    {
        return iter->second;
    }
    // 로딩이 안됐거나, 이름이 잘못됐거나
    return nullptr;
}
