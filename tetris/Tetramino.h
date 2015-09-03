#pragma once
#ifndef TETRAMINO_H_
#define TETRAMINO_H_


#include "includes.h"


class Tetramino {
protected:
	shared_array<SDL_Rect> box;
	shared_ptr<SDL_Surface> tetramino;
	int x;
	int y;
	int xVel;	// velocity
	int yVel;
	int frames;
	int x_move_flag;	// -1 -> moving left	1 -> moving right
	int angle;
	bool down_pressed;
	bool fallen;
	
	Uint32 t_color;

public:
	Tetramino();
	virtual ~Tetramino() {};

	void show();
	void move(Uint32 deltaticks, int lvl, bool **mask = NULL);
	void handle_input();
	void check_y_collision(bool **mask = NULL);
	void check_x_collision(bool **mask = NULL);
	void draw();
	void incr_frames() { ++frames; }
	virtual void rotate();
	void save();

	bool is_fallen() { return fallen; }
	int get_x() { return x; }
	int get_y() { return y; }
	int get_angle() { return angle; }
	void set_angle(int ang) { angle = ang; }
	void set_x(int X){x = X;};
	void set_y(int Y){y = Y;};
	Uint32 get_color() { return t_color; }; 
	void set_color(Uint32 c) { t_color = c; };
	virtual shared_array<SDL_Rect> get_box() { return box; }
	void set_box(shared_array<SDL_Rect> b) { box = b; };
	shared_ptr<SDL_Surface> get_surf() { return tetramino; }

};

class TetraminoFactory {
private:
	static TetraminoFactory* inst;
	TetraminoFactory(){};
	virtual ~TetraminoFactory(){};

public:

	static TetraminoFactory& instance() {
		if(inst == NULL)
			inst = new TetraminoFactory;
		return *inst;
	}

	virtual shared_ptr<Tetramino> createTetramino(tetra_type id);
	
};




#endif /* TETRAMINO_H_ */
