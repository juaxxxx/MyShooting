#pragma once

class TextureResource
{
public:
	TextureResource() {};
	~TextureResource();

	void Load(wstring fileName);

	// 해당 리소스가 그려지는 부분
	void Render(HDC hdc, Vector pos);
	void Render(HDC hdc, Vector pos, Vector frame, Vector size);

public:
	// 텍스처를 그리기위한 변수
	HDC		_textureHdc = 0;
	HBITMAP _bitmap;
	int32 _transparent = -1;	// 투명하게 보여야하는 색상
	int32 _sizeX = 0;
	int32 _sizeY = 0;
	int32 _frameCountX;
	int32 _frameCountY;
};

