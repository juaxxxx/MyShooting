#pragma once

class UAnimator;
class TextureResource;

#define TEXTURE_SIZE 64

struct Frame
{
	uint32 x;
	uint32 y;
	uint32 frameCount;
};

class UAnimation
{
public:
	UAnimation(wstring name, UAnimator* animator, TextureResource* texture, uint32 totalframecount, uint32 framecount, uint32 totalcount)
		: _name(name), _animator(animator), _texture(texture), _colCount(totalframecount), _count(framecount), _totalCount(totalcount), _curFrameCount(0), _time(0), _gap(0.05f){ }
	~UAnimation() {};
	void Init();
	void Update(float deltaTime);
	void Render(HDC hdc);

	void CreateAnimation();
	Vector GetCurFrame();

private:
	wstring _name;
	UAnimator* _animator;
	TextureResource* _texture;
	uint32 _totalCount;
	uint32 _colCount;
	uint32 _count;

	vector<Frame> _frames;
	uint32 _curFrameCount;
	//float _duration;
	float _time;
	float _gap;
};