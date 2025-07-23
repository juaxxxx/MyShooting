#include "pch.h"
#include "TextureResource.h"
#include "Game.h"
#include "Camera.h"

TextureResource::~TextureResource()
{
	if (_textureHdc != nullptr)
	{
		::DeleteDC(_textureHdc);
		_textureHdc = nullptr;
	}
	if (_bitmap != nullptr)
	{
		::DeleteObject(_bitmap);
		_bitmap = nullptr;
	}
}

void TextureResource::Load(wstring fileName)
{
	// 이전 리소스 해제
	if (_textureHdc)
	{
		::DeleteDC(_textureHdc);
		_textureHdc = nullptr;
	}

	if (_bitmap)
	{
		::DeleteObject(_bitmap);
		_bitmap = nullptr;
	}

	// WinAPI 텍스처 로딩하는 방법
	{
		fs::path dirPath("C:/Users/inha/source/repos/SVNTest/MyShooting/MyShooting/Resources");
		//fs::path dirPath("C:/Users/82102/Desktop/정리함/교육/WinAPI/MyShooting/Resources");

		fs::path fullPath = dirPath / fileName;
		//fs::path fullPath = fs::current_path() / fileName;

		HDC hdc = ::GetDC(Game::GetInstance()->GetHwnd());

		_textureHdc = ::CreateCompatibleDC(hdc);
		::ReleaseDC(Game::GetInstance()->GetHwnd(), hdc); // GetDC로 얻은 HDC는 반드시 Release해야한다.

		_bitmap = (HBITMAP)::LoadImageW(
			nullptr,
			fullPath.c_str(),
			IMAGE_BITMAP,
			0,
			0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION
		);
		if (_bitmap == 0)
		{
			::MessageBox(Game::GetInstance()->GetHwnd(), fullPath.c_str(), L"Invalid Texture Load", MB_OK);
			return;
		}

		_transparent = RGB(252, 0, 255);

		HBITMAP prev = (HBITMAP)::SelectObject(_textureHdc, _bitmap);
		//::DeleteObject(prev);

		BITMAP bit = {};
		::GetObject(_bitmap, sizeof(BITMAP), &bit);

		_sizeX = bit.bmWidth;
		_sizeY = bit.bmHeight;
	}
}

void TextureResource::Render(HDC hdc, Vector pos)
{
	// 카메라 기준으로 좌표 변환을 해준다.

	Vector screenPos = Camera::ConvertScreenPos(pos);

	if (_transparent == -1)
	{
		::BitBlt(hdc,	// 백버퍼에
			(int32)screenPos.x - (_sizeX / 2),	// 텍스처를 중심좌표로 그리기위해 size의 절반만큼 빼준다.
			(int32)screenPos.y - (_sizeY / 2),
			_sizeX,
			_sizeY,
			_textureHdc,	// 텍스쳐 그리기
			0,
			0,
			SRCCOPY);
	}
	else
	{
		::TransparentBlt(hdc,
			(int32)screenPos.x - (_sizeX / 2),
			(int32)screenPos.y - (_sizeY / 2),
			_sizeX,
			_sizeY,
			_textureHdc,
			0,
			0,
			_sizeX,
			_sizeY,
			_transparent);	// 어떤색상을 투명하게 그릴까
	}
}

void TextureResource::Render(HDC hdc, Vector pos, Vector frame, Vector size)
{
	// 카메라 기준으로 좌표 변환을 해준다.

	Vector screenPos = Camera::ConvertScreenPos(pos);

	//::BitBlt(hdc,	// 백버퍼에
	//	(int32)screenPos.x - (size.x / 2),	// 텍스처를 중심좌표로 그리기위해 size의 절반만큼 빼준다.
	//	(int32)screenPos.y - (size.y / 2),
	//	size.x,
	//	size.y,
	//	_textureHdc,	// 텍스쳐 그리기
	//	frame.x,
	//	frame.y,
	//	SRCCOPY);
	if (_transparent == -1)
	{
		::BitBlt(hdc,	// 백버퍼에
			(int32)screenPos.x - (size.x / 2),	// 텍스처를 중심좌표로 그리기위해 size의 절반만큼 빼준다.
			(int32)screenPos.y - (size.y / 2),
			size.x,
			size.y,
			_textureHdc,	// 텍스쳐 그리기
			frame.x,
			frame.y,
			SRCCOPY);
	}
	else
	{
		::TransparentBlt(hdc,
			(int32)screenPos.x - (size.x / 2),	// 텍스처를 중심좌표로 그리기위해 size의 절반만큼 빼준다.
			(int32)screenPos.y - (size.y / 2),
			size.x,
			size.y,
			_textureHdc,
			frame.x,
			frame.y,
			size.x,
			size.y,
			_transparent);	// 어떤색상을 투명하게 그릴까
	}
}
