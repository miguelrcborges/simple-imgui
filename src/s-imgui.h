/*
 * The following headers should be included before this:
 * - <SDL2/SDL_video.h>
 * - <SDL2/SDL_render.h>
 * - <SDL2/SDL_event.h>
 */

#ifndef S_IMGUI_H
#define S_IMGUI_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _ButtonHandle {
	unsigned long n;
} ButtonHandle;

extern void simgui_Prepare(void);
extern void simgui_End(void);
extern void simgui_SetRenderer(SDL_Window *win, SDL_Renderer *ren);
extern void simgui_ProcessEvent(SDL_Event *ev);
extern int  simgui_ButtonID(int id, SDL_Rect *r);

#ifdef S_IMGUI_FILE_ID
#define simgui_Button(r) (simgui_ButtonID(S_IMGUI_FILE_ID + (__LINE__), r))
#else
#define simgui_Button(r) (simgui_ButtonID((__LINE__), r))
#endif

#ifdef __cplusplus
}
#endif

#endif
