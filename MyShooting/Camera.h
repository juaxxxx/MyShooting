#pragma once

// ���ӿ��� �Ѱ��� �����ϴϱ� �̱���� ���������,
// ������ GetInstance �ϱ� �����Ƽ�
// ī�޶�� ī�޶��� ��ǥ���� �ʿ��ؼ� ���� �̱������� ���� �ʴ´�.

class Camera
{
public:
	static void Update(Vector playerPos, Vector mapSize, float deltaTime);
	static Vector ConvertScreenPos(Vector worldPos);

	static void SetCameraPos(Vector pos) { _cameraPos = pos; }
	static Vector GetCameraPos() { return _cameraPos; }

	
private:
	static Vector _cameraPos;
	static float _speed;
};

