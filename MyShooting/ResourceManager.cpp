#include "pch.h"
#include "ResourceManager.h"
#include "TextureResource.h"
#include "Game.h"

void ResourceManager::Init()
{
    //{
    //    TextureResource* texture = new TextureResource();
    //    texture->Load(L"Player.bmp");
    //    _textures["Player"] = texture;
    //}
    //{
    //    TextureResource* texture = new TextureResource();
    //    texture->Load(L"Enemy1.bmp");
    //    _textures["Enemy1"] = texture;
    //}
    //{
    //    TextureResource* texture = new TextureResource();
    //    texture->Load(L"Enemy2.bmp");
    //    _textures["Enemy2"] = texture;
    //}
    //{
    //    TextureResource* texture = new TextureResource();
    //    texture->Load(L"Enemy3.bmp");
    //    _textures["Enemy3"] = texture;
    //}
    //{
    //    TextureResource* texture = new TextureResource();
    //    texture->Load(L"Enemy4.bmp");
    //    _textures["Enemy4"] = texture;
    //}
    //{
    //    TextureResource* texture = new TextureResource();
    //    texture->Load(L"Playerbullet.bmp");
    //    _textures["PlayerMISSILE"] = texture;
    //}
    //{
    //    TextureResource* texture = new TextureResource();
    //    texture->Load(L"EnemyBullet.bmp");
    //    _textures["EnemyMISSILE"] = texture;
    //}
    //{
    //    TextureResource* texture = new TextureResource();
    //    texture->Load(L"BG.bmp");
    //    _textures["BackGround"] = texture;
    //}
    //{
    //    TextureResource* texture = new TextureResource();
    //    texture->Load(L"explosion.bmp");
    //    _textures["Explosion"] = texture;
    //}
    //{
    //    TextureResource* texture = new TextureResource();
    //    texture->Load(L"PlayerHp.bmp");
    //    _textures["PlayerHp"] = texture;
    //}
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

void ResourceManager::LoadTexture(string key, string texturePath, int32 transparent, int32 xFrameCount, int32 yFrameCount)
{
    TextureResource* texture = new TextureResource();
    {
        fs::path fullPath = fs::current_path() / L"../Resources/" / texturePath;

        HDC hdc = ::GetDC(Game::GetInstance()->GetHwnd());

        texture->_textureHdc = ::CreateCompatibleDC(hdc);
        texture->_bitmap = (HBITMAP)::LoadImageW(
            nullptr,
            fullPath.c_str(),
            IMAGE_BITMAP,
            0,
            0,
            LR_LOADFROMFILE | LR_CREATEDIBSECTION
        );
        if (texture->_bitmap == 0)
        {
            ::MessageBox(Game::GetInstance()->GetHwnd(), fullPath.c_str(), L"Invalid Texture Load", MB_OK);
            return;
        }

        texture->_transparent = transparent; //RGB(252, 0, 255);

        HBITMAP prev = (HBITMAP)::SelectObject(texture->_textureHdc, texture->_bitmap);
        ::DeleteObject(prev);

        BITMAP bit = {};
        ::GetObject(texture->_bitmap, sizeof(BITMAP), &bit);

        texture->_sizeX = bit.bmWidth;
        texture->_sizeY = bit.bmHeight;

        texture->_frameCountX = xFrameCount;
        texture->_frameCountY = yFrameCount;
    }

    _textures[key] = texture;
}
