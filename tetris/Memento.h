#ifndef MEMENTO_H_
#define MEMENTO_H_

#include "includes.h"
#include "Well.h"
#include "Tetramino.h"


class Memento {
protected:
	bool state_save;
public:
	Memento(){ state_save = false; };
	bool get_state() { return state_save; };
	void set_state(bool new_state) {state_save = new_state;};
	bool Save(tetra_type id, shared_ptr<Tetramino>);
	bool Load_fig(shared_ptr<Tetramino>);
	bool Save_mask(bool **);
	bool Load_mask(Well*);


};

#endif /* VEVENTO_H_ */