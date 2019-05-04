#pragma once
class GameManager {
public:
	enum Screens {
		MAIN,
		GAME
	};
	int currentScreen = MAIN;
	bool gameover = false;
	float score = 0;
};