#ifndef S_IMGUI_H
#define S_IMGUI_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _ButtonHandle {
	unsigned long n;
} ButtonHandle;

extern int simgui_init();
extern ButtonHandle simgui_allocButton();
extern void simgui_freeButton(ButtonHandle b);

#ifdef __cplusplus
}
#endif

#endif