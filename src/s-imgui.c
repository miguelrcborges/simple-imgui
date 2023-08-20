#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_events.h>

#include "s-imgui.h"

static SDL_Window   *win;
static SDL_Renderer *ren;
static int mouse_x;
static int mouse_y;
static int mouse_down;
static int hot_item;
static int active_item;

void simgui_Prepare(void) {
	hot_item = 0;
}

void simgui_End(void) {
	if (mouse_down == 0)
		active_item = 0;
	else
		/* Doesn't let widget activation from dragging
		 * from emptyness to the widget */
		if (active_item == 0)
			active_item = -1;
}

void simgui_SetRenderer(SDL_Window *nwin, SDL_Renderer *nren) {
	win = nwin;
	ren = nren;
	hot_item = 0;
}

void simgui_ProcessEvent(SDL_Event *e) {
	switch (e->type) {
	case SDL_MOUSEMOTION:
		mouse_x = e->motion.x;
		mouse_y = e->motion.y;
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (e->button.button == SDL_BUTTON_LEFT)
			mouse_down = 1;
		break;
	case SDL_MOUSEBUTTONUP:
		if (e->button.button == SDL_BUTTON_LEFT)
			mouse_down = 0;
		break;
	}
}

int simgui_ButtonID(int id, SDL_Rect *r) {
	if (
		r->x < mouse_x &&
		r->x + r->w > mouse_x &&
		r->y < mouse_y &&
		r->y + r->h > mouse_y
	) {
		hot_item = id;
		if (mouse_down && active_item == 0)
			active_item = id;
	}

	if (id == hot_item) {
		if (id == active_item) {
			SDL_SetRenderDrawColor(ren, 0x33, 0x33, 0x33, 0xff);
		} else {
			SDL_SetRenderDrawColor(ren, 0xee, 0xee, 0xee, 0xff);
		}
	} else {
		SDL_SetRenderDrawColor(ren, 0xaa, 0xaa, 0xaa, 0xff);
	}
	SDL_RenderFillRect(ren, r);
	return active_item == id &&
		hot_item == id &&
		mouse_down == 0;
}
