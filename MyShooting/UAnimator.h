#pragma once

class TextureResource;
class UObject;
class UAnimation;

class UAnimator
{
public:
	UAnimator() : _object(nullptr), _texture(nullptr), _curAnim(nullptr), _loop(false) {}
	~UAnimator() {}; // delete 작업 필요
	void Update(float deltaTime);
	void Render(HDC hdc);

	void Play();
	void CreateAnimation(wstring name, TextureResource* texture, uint32 colcount, uint32 framecount, uint32 totalcount);
	void ChangeAnimation(wstring name);
	UAnimation* GetAnimation() { return _curAnim; }
	void SetOwner(UObject* object) { _object = object; }
	UObject* GetOwner() { return _object; }

private:
	map<wstring, UAnimation*> _anims;
	UObject* _object;
	TextureResource* _texture;
	UAnimation* _curAnim;
	bool _loop;
};

// 애니메이션 스프라이트 재생.