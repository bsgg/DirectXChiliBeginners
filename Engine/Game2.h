#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Board.h"
#include "Snake.h"
#include "FrameTimer.h"
#include "SoundEffect.h"
#include <random>

class Game2
{
public:
	Game2(class MainWindow& wnd);
	Game2(const Game2&) = delete;
	Game2& operator=(const Game2&) = delete;
	void Go();
private:
	void DrawFrame();
	void UpdateFrame();
private:

	MainWindow& wnd;
	Graphics gfx;
	FrameTimer ft;
	std::mt19937 rng;
	Board board;
	Snake snake;
	// Snake starts moving to the right
	Location delta_loc = { 1,0 };

	// Soundds
	SoundEffect sfxEat = SoundEffect({ L"Sounds\\Eat.wav" });
	SoundEffect sfxSlither = SoundEffect({ L"Sounds\\Slither0.wav",L"Sounds\\Slither1.wav",L"Sounds\\Slither2.wav" });
	Sound sndMusic = Sound(L"Sounds\\Music_Loop.wav", Sound::LoopType::AutoFullSound);
	Sound sndTitle = Sound(L"Sounds\\Title.wav");
	Sound sndFart = Sound(L"Sounds\\Fart.wav");
	
	// How many frames the snake takes to move (60 / 20 = 3 frames per second)
	static constexpr float snakeMovePeriodMin = 0.040f;
	static constexpr float snakeMovePeriodSpeedup = 0.15f;
	static constexpr int nPoison = 240;
	static constexpr int nFood = 12;
	float snakeMovePeriod = 0.4f;
	float snakeMoveCounter = 0.0f;
	static constexpr float snakeSpeedupFactor = 0.9f;
	bool gameIsOver = false;
	bool gameIsStarted = false;
};
