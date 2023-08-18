#include <stdlib.h>

#include "s-imgui.h"

typedef struct _Button {
	/** Temporary content just to try out the allocator */
	char a[128];
} Button;

typedef union _ButtonPoolElement {
	Button but;
	/** Holds the next free button handle (Linked List) */
	ButtonHandle nf; 
} ButtonPoolElement;

enum CONSTANTS {
	BUTTONS_POOL_INITIAL_BUFFER_SIZE = 32,
};


static ButtonPoolElement *button_pool;
static unsigned long      button_pool_size;
static ButtonHandle       button_pool_next_free;


int simgui_init() {
	button_pool = malloc(BUTTONS_POOL_INITIAL_BUFFER_SIZE * sizeof(*button_pool));
	if (button_pool == NULL) {
		return 1;
	}
	
	int i;
	for (i = 0; i < BUTTONS_POOL_INITIAL_BUFFER_SIZE - 1; ++i) {
		button_pool[i].nf.n = i + 2;
	}
	button_pool[i].nf.n = 0;
	button_pool_next_free.n = 1;

	return 0;
};


ButtonHandle simgui_allocButton() {
	if (button_pool_next_free.n == 0) {
		return button_pool_next_free;
	}	

	unsigned long i = button_pool_next_free.n - 1;
	ButtonHandle tmp = button_pool_next_free;
	button_pool_next_free = button_pool[i].nf;

	return tmp;
}

void simgui_freeButton(ButtonHandle b) {
	unsigned long i = b.n - 1;
	button_pool[i].nf = button_pool_next_free;
	button_pool_next_free = b;
}