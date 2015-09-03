#include "Game.h"
#include "Well.h"
#include "Tetramino.h"
#include "Timer.h"
#include "Memento.h"
#include "thread"
#include "pthread.h"
#include "unistd.h"

Game::Game() : lvl(1), started(false), paused(false), stopped(false) {}


Memento mem;
bool quit = false;
// pthread_mutex_t m;


int Game::start() {
	if(init() == false) {
		return -1;
	}

	srand(time(NULL));

	shared_ptr<Tetramino> tetramino (new Tetramino);

	Well well;
	if(well.get_surf() == NULL) {
		return 1;
	}

	Timer fps;
	Timer delta;
	pthread_t thread;
	bool flag = true;


	int result;

	if(SDL_EnableKeyRepeat(100, 25) == -1) {
		return 1;
	}
	delta.start();
    
	
    
    int size_game = 0;
    int size_mask = 0;
    tetra_type tetra_id;

    
	// std::ifstream load("game_save");
	// 	if(load != NULL) {				 	
	// 	 	load >> tetra_id;

	// 	 	if( load.fail() == true ) {
	//             return false;
	//         }
	// 		tetramino = TetraminoFactory::instance().createTetramino(tetra_id);
	// 	 	mem.Load_fig(tetramino);
	// 	 	std::ifstream load("mask_save");
	 		
	//  		if(load != NULL) 
	//  			mem.Load_mask(&well);	

	// 	 	load.close();
	// 	 	tetramino->draw();
	// 	 	std::remove("game_save");
	// 	 	std::remove("mask_save");
	// 	 } else {
	// 		tetra_id = rand() % 7;
	// 		tetramino = TetraminoFactory::instance().createTetramino(tetra_id);
	// 	}
	// 	Tetramino *test = tetramino.get();
	// 	result = pthread_create(&thread, NULL, handl, test);
	// 	pthread_detach(thread); 
		 

	while(!quit) {		

		std::ifstream load("game_save");
		 if(load != NULL) {				 	
		 	load >> tetra_id;

		 	if( load.fail() == true ) {
	            return false;
	        }
			tetramino = TetraminoFactory::instance().createTetramino(tetra_id);
		 	mem.Load_fig(tetramino);
		 	std::ifstream load("mask_save");
	 		
	 		if(load != NULL) 
	 			mem.Load_mask(&well);	

		 	load.close();
		 	tetramino->draw();
		 	std::remove("game_save");
		 	std::remove("mask_save");
		 } else {
			tetra_id = rand() % 7;
			tetramino = TetraminoFactory::instance().createTetramino(tetra_id);
		}
		if(tetramino->get_surf() == NULL) {
			return -1;
		}
		Tetramino *test = tetramino.get();
		result = pthread_create(&thread, NULL, handl, test);

		while(!tetramino->is_fallen() && !quit) {
			fps.start();
			tetramino->move(delta.get_ticks(), lvl, well.get_mask());
			
			delta.start();
			SDL_FillRect(screen.get(), &screen->clip_rect, SDL_MapRGB(screen->format, 255, 255, 255));
			well.show();
			tetramino->show();
			if(SDL_Flip(screen.get()) == -1) {  // обновление экрана
				return 1;
			}
			if(fps.get_ticks() < 1000 / FRAMES_PER_SECOND) {  // частота кадров
				SDL_Delay(1000 / FRAMES_PER_SECOND - fps.get_ticks()); 
			}
			tetramino->incr_frames();
			if(mem.get_state()) {
				mem.Save_mask(well.get_mask());
				mem.Save(tetra_id, tetramino);
			}	
		}

		well.unite(tetramino->get_box(), (int)tetramino->get_x(), (int)tetramino->get_y());
		well.show();
		if(SDL_Flip(screen.get()) == -1) {
			return 1;
		}
		// tetra_id = rand() % 7;
		// tetramino = TetraminoFactory::instance().createTetramino(tetra_id);
	}
	result = pthread_join(thread, NULL);
	clean_up();

	return 0;
}

void* Game::handl(void *arg) {
	Tetramino * tetramino1 = (Tetramino *)arg;
	while(!tetramino1->is_fallen() && !quit) {
		while(SDL_PollEvent(&event)) { 
		 	tetramino1->handle_input();
			if(event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {  
				quit = true;
			}
			if(event.key.keysym.sym == SDLK_s) {
				mem.set_state(true);
			}

		}
	}
}



