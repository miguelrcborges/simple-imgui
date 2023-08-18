#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_shape.h>
#include <SDL2/SDL_video.h>

#include "s-imgui.h"

int main(int argc, char **argv) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_Log("Failed to initialize SDL.");
		return 1;
	}

	if (simgui_init() != 0) {
		SDL_Log("Failed to initialize s-imgui.");
		return 1;
	} 

	SDL_Window *win = SDL_CreateWindow(
		"demo",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		1600,
		900,
		SDL_WINDOW_SHOWN
	);

	SDL_Renderer *ren = SDL_CreateRenderer(
		win,
		-1,
		SDL_RENDERER_PRESENTVSYNC
	);

	ButtonHandle a = simgui_allocButton();
	ButtonHandle b = simgui_allocButton();
	ButtonHandle c = simgui_allocButton();
	simgui_freeButton(a);
	ButtonHandle d = simgui_allocButton();
	SDL_Log("%lu %lu %lu %lu", a.n, b.n, c.n, d.n);

	while (1) {
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				goto end;
			}
		}

		SDL_SetRenderDrawColor(ren, 0x16, 0x16, 0x16, 0xff);
		SDL_RenderClear(ren);
		SDL_RenderPresent(ren);
	}

end:
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}