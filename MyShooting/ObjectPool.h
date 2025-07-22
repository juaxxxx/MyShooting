#pragma once
#include <type_traits> 
#include "UObject.h"

class ObjectPool
{
public:
	// ���ø� �Լ��� �����ΰ� ��� ���� ���ο��� ���� ���ǵǾ��
	// ������ Ÿ�� �� �ν��Ͻ�ȭ�� �� �־� ��ũ ������ �߻����� �ʴ´�.
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