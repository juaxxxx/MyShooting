#pragma once
#include <type_traits> 
#include "UObject.h"

class ObjectPool
{
public:
	// 템플릿 함수는 구현부가 헤더 파일 내부에서 같이 정의되어야
	// 컴파일 타임 때 인스턴스화할 수 있어 링크 에러가 발생하지 않는다.
	template<typename T>
	void Init(int32 size)
	{
		for (int32 i = 0; i < size; i++)
		{
			T* object = new T();

			_pool.push(object);
		}
	}

	void Clear();

	template<typename T>
	T* Acquire()
	{
		if (_pool.empty())
		{
			T* object = new T();

			_pool.push(object);
		}

		T* obj = static_cast<T*>(_pool.top());
		_pool.pop();

		return obj;
	}

	void Return(UObject* object);

public:
	stack<UObject*> _pool;
};