#pragma once
class TextureResource
{
public:
	void Load(wstring fileName);

	// �ش� ���ҽ��� �׷����� �κ�
	void Render(HDC hdc, Vector pos);
	void Render(HDC hdc, Vector pos, Vector frame, Vector size);

private:
	// �ؽ�ó�� �׸������� ����
	HDC		_textureHdc = 0;
	HBITMAP _bitmap;
	int32 _transparent = -1;	// �����ϰ� �������ϴ� ����
	int32 _sizeX = 0;
	int32 _sizeY = 0;
};

