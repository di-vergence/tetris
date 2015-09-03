#pragma once
#ifndef GAME_H_
#define GAME_H_

#include "includes.h"
#include "Tetramino.h"

class Game {
	int lvl;
	bool started;
	bool paused;
	bool stopped;


public:
	Game();
	int getlvl() { return lvl;}
	bool is_started() { return started; }
	bool is_paused() { return paused; }
	bool is_stopped() { return stopped; }

	int start();
	static void* handl(void*);

	void pause();
	void restart();
};


#endif /* GAME_H_ */
