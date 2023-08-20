#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_shape.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_events.h>

#include "s-imgui.h"

int main(int argc, char **argv) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_Log("Failed to initialize SDL.");
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

	simgui_SetRenderer(win, ren);

	SDL_Rect b1 = (SDL_Rect){
		.x = 300,
		.y = 600,
		.w = 200,
		.h = 100,
	};

	SDL_Rect b2 = (SDL_Rect){
		.x = 700,
		.y = 600,
		.w = 200,
		.h = 100,
	};

	int b1_presses = 0, b2_presses = 0;

	while (1) {
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				goto end;
			}
			simgui_ProcessEvent(&e);
		}

		SDL_SetRenderDrawColor(ren, 0x16, 0x16, 0x16, 0xff);
		SDL_RenderClear(ren);

		simgui_Prepare();

		if (simgui_Button(&b1))
			SDL_Log("The button 1 was pressed %d times.\n", ++b1_presses);

		if (simgui_Button(&b2))
			SDL_Log("The button 2 was pressed %d times.\n", ++b2_presses);

		simgui_End();

		SDL_RenderPresent(ren);
	}

end:
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}
