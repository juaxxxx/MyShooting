#pragma once

class HpHeart;
class ScoreScreen;
class GameOverText;

class GUI
{
public:
	GUI() {}
	~GUI();

	void Init();
	void Render(HDC hdc);
private:
	HpHeart* _hpHeart = nullptr;
	ScoreScreen* _scoreScreen = nullptr;
	GameOverText* _gameoverText = nullptr;
};

