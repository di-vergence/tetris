#include "Well.h"
#include "Tetramino.h"
#include "Figures.h"
#include "Memento.h"

bool Memento::Save(tetra_type id, shared_ptr<Tetramino> thisTetramino) {
	shared_array<SDL_Rect> thisBox;
	thisBox = shared_array<SDL_Rect> (new SDL_Rect[4]);	

	std::ofstream save("game_save");
	save << id;
	save << " ";

	save << thisTetramino->get_x();
	save << " ";
	save << thisTetramino->get_y();
	save << " ";
	save << thisTetramino->get_color();
	save << " ";
	save << thisTetramino->get_angle();
	save << " ";	
	thisBox = thisTetramino->get_box();

	for(int i = 0; i < 4; ++i) {
		save << thisBox[i].x;
		save << " ";
		save << thisBox[i].y;
		save << " ";
		save << thisBox[i].h;
		save << " ";
		save << thisBox[i].w;
		save << " ";
	}
	save << "\n";
	save.close();
	return true;
}

bool Memento::Save_mask(bool **mask) {
	std::ofstream save("mask_save");

	for(int i = 0; i < WELL_HEIGHT / CUBE_S; ++i) {
		for(int j = 0; j < WELL_WIDTH / CUBE_S; ++j) {
			save << mask[i][j];
			save << " ";
		}
	}

	save.close();
	return true;
}

bool Memento::Load_fig(shared_ptr<Tetramino> thisTetramino) {
	std::ifstream load("game_save");
	if(load != NULL) {
		int offset, x, y, h, w, angle, id;
		Uint32 color;
		shared_array<SDL_Rect> thisBox;
		thisBox = shared_array<SDL_Rect> (new SDL_Rect[4]);

		load >> id;

		load >> offset;
		thisTetramino->set_x(offset);

		load >> offset;
		thisTetramino->set_y(offset);

		load >> color;
		thisTetramino->set_color(color);

		load >> angle;
		thisTetramino->set_angle(angle);

		for(int i = 0; i < 4; ++i) {
			load >> thisBox[i].x;
			load >> thisBox[i].y;
			load >> thisBox[i].h;
			load >> thisBox[i].w;
			
		}
		thisTetramino->set_box(thisBox);
	}

	return true;
}

bool Memento::Load_mask(Well* thisWell) {
	std::ifstream load("mask_save");
	 bool **thisMask = thisWell->get_mask();

		for(int i = 0; i < WELL_HEIGHT / CUBE_S; ++i) {
			for(int j = 0; j < WELL_WIDTH / CUBE_S; ++j) {
				load >> thisMask[i][j];
			}
		}
		thisWell->set_mask(thisMask);
		load.close();
}