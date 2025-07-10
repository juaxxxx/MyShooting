#include "pch.h"
#include "UObject.h"
#include "UAnimator.h"
#include "TextureResource.h"
UObject::~UObject()
{
	SAFE_DELETE(_anim);
}
