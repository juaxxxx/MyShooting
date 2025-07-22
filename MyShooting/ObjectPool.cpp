#include "pch.h"
#include "ObjectPool.h"


void ObjectPool::Clear()
{
	while (!_pool.empty())
	{
		UObject* object = _pool.top();
		SAFE_DELETE(object);

		_pool.pop();
	}
}

void ObjectPool::Return(UObject* object)
{
	if (nullptr == object)
		return;

	_pool.push(object);
}