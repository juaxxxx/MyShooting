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
	// ���� ���ҽ� ����
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

	// WinAPI �ؽ�ó �ε��ϴ� ���
	{
		fs::path dirPath("C:/Users/inha/source/repos/SVNTest/MyShooting/MyShooting/Resources");
		//fs::path dirPath("C:/Users/82102/Desktop/������/����/WinAPI/MyShooting/Resources");

		fs::path fullPath = dirPath / fileName;
		//fs::path fullPath = fs::current_path() / fileName;

		HDC hdc = ::GetDC(Game::GetInstance()->GetHwnd());

		_textureHdc = ::CreateCompatibleDC(hdc);
		::ReleaseDC(Game::GetInstance()->GetHwnd(), hdc); // GetDC�� ���� HDC�� �ݵ�� Release�ؾ��Ѵ�.

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
	// ī�޶� �������� ��ǥ ��ȯ�� ���ش�.

	Vector screenPos = Camera::ConvertScreenPos(pos);

	if (_transparent == -1)
	{
		::BitBlt(hdc,	// ����ۿ�
			(int32)screenPos.x - (_sizeX / 2),	// �ؽ�ó�� �߽���ǥ�� �׸������� size�� ���ݸ�ŭ ���ش�.
			(int32)screenPos.y - (_sizeY / 2),
			_sizeX,
			_sizeY,
			_textureHdc,	// �ؽ��� �׸���
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
			_transparent);	// ������� �����ϰ� �׸���
	}
}

void TextureResource::Render(HDC hdc, Vector pos, Vector frame, Vector size)
{
	// ī�޶� �������� ��ǥ ��ȯ�� ���ش�.

	Vector screenPos = Camera::ConvertScreenPos(pos);

	//::BitBlt(hdc,	// ����ۿ�
	//	(int32)screenPos.x - (size.x / 2),	// �ؽ�ó�� �߽���ǥ�� �׸������� size�� ���ݸ�ŭ ���ش�.
	//	(int32)screenPos.y - (size.y / 2),
	//	size.x,
	//	size.y,
	//	_textureHdc,	// �ؽ��� �׸���
	//	frame.x,
	//	frame.y,
	//	SRCCOPY);
	if (_transparent == -1)
	{
		::BitBlt(hdc,	// ����ۿ�
			(int32)screenPos.x - (size.x / 2),	// �ؽ�ó�� �߽���ǥ�� �׸������� size�� ���ݸ�ŭ ���ش�.
			(int32)screenPos.y - (size.y / 2),
			size.x,
			size.y,
			_textureHdc,	// �ؽ��� �׸���
			frame.x,
			frame.y,
			SRCCOPY);
	}
	else
	{
		::TransparentBlt(hdc,
			(int32)screenPos.x - (size.x / 2),	// �ؽ�ó�� �߽���ǥ�� �׸������� size�� ���ݸ�ŭ ���ش�.
			(int32)screenPos.y - (size.y / 2),
			size.x,
			size.y,
			_textureHdc,
			frame.x,
			frame.y,
			size.x,
			size.y,
			_transparent);	// ������� �����ϰ� �׸���
	}
}
