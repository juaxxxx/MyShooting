#pragma once

//  우리가 정의하는 공용 선언들.
constexpr int GWinSizeX = 600;
constexpr int GWinSizeY = 800;

// 엔씨에 있을때 사용하던 방식 & 언리얼도 이렇게 씁니다.
using int8 = char;					// 정수 저장하는데 1bit 짜리
using int16 = short;
using int32 = int;
using int64 = long long;		// 매번 long long 쓰기 귀찮아서 int64
using uint8 = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long long;

float RadianToDegree(float radian);
float DegreeToRadian(float degree);

// 언리얼에서 가져옴.
#define SMALL_NUMBER			(1.e-8f)

// vector 구현 ((방향+크기)를 나타내는 벡터)
struct Vector
{
	// 좌표
	float x = 0;
	float y = 0;

	Vector() : x(0), y(0) {}
	Vector(float x, float y) : x(x), y(y) {}
	Vector(POINT pt) : x(pt.x), y(pt.y) {}

	// 사칙연산 정의
	// +, - , *, / 
	Vector operator+(const Vector& other)
	{
		Vector ret;
		ret.x = x + other.x;
		ret.y = y + other.y;
		return ret;
	}
	Vector operator-(const Vector& other)
	{
		Vector ret;
		ret.x = x - other.x;
		ret.y = y - other.y;
		return ret;
	}
	Vector operator*(float ratio)
	{
		Vector ret;
		ret.x = x * ratio;
		ret.y = y * ratio;
		return ret;
	}

	void operator+=(const Vector& other)
	{
		x += other.x;
		y += other.y;
	}
	void operator-=(const Vector& other)
	{
		x -= other.x;
		y -= other.y;
	}
	void operator*=(float ratio)
	{
		x *= ratio;
		y *= ratio;
	}

	// 벡터를 나눗셈할일이 많지가 않다...
	// 연산자 안만들어도 쓸일이 거의없을듯.


	// 벡터의 길이 구하기
	// 엔진 살펴보면, Legnth, LengthSquared (벡터는 보통 길이를 리턴하는 함수가 2종류)
	// sqrt(루트) 연산은 생각보다 비싸기 때문에, 꼭 진짜 길이가 필요한 경우가 아니면,
	// LengthSquared (제곱 길이) 버전을 사용하는게 더 좋다.
	float Length()
	{
		return ::sqrt(x * x + y * y);
	}

	// 길이의 제곱 버전
	float LengthSquared()
	{
		return (x * x + y * y);
	}

	// 이것도 게임만들다가. 다양한 버전이 필요하면 여기에 재정의 하면 되요.
	void Normalize()
	{
		float length = Length();

		if (length < SMALL_NUMBER)
			return;	// 굳이 정규화안하고 리턴

		// 정규화.
		x /= length;
		y /= length;
	}

	// 내적은 Dot 
	float Dot(const Vector& other)
	{
		return x * other.x + y * other.y;
	}

	// radian 각도만큼 회전시키자.
	Vector Rotate(float radian)
	{
		float cosA = ::cosf(radian);
		float sinA = ::sinf(radian);

		return Vector(x * cosA - y * sinA, x * sinA + y * cosA);
	}

	// 외적은 Cross
	float Cross(const Vector& other)
	{
		return x * other.y - y * other.x;
	}
};

// ORDER BY LAYER
enum class LAYER_TYPE
{
	BACKGROUND,
	DEFAULT,
	EFFECT,
	ENEMY,
	MISSILE,
	ENEMYMISSILE,
	PLAYER,
	ENEMYSPAWNER,
	END,
};

enum class ENEMY_TYPE
{
	ENEMY1,
	ENEMY2,
	ENEMY3,
	ENEMY4,
	NONE,
};

// Circle Collider Struct
struct Collider
{
	float radius;
	POINT offset;
};