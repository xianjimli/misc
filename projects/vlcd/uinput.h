#ifndef UINPUT_H
#define UINPUT_H

#ifdef __cplusplus
extern "C" {
#endif

struct _UInput;
typedef struct _UInput UInput;

UInput* uinput_create(const char* dev, int xmax, int ymax);
void uinput_report_lbutton_event(UInput* thiz, int press);
void uinput_report_mbutton_event(UInput* thiz, int press);
void uinput_report_rbutton_event(UInput* thiz, int press);
void uinput_report_move_event(UInput* thiz, int x, int y);

void uinput_report_key_event(UInput* thiz, unsigned short key, int press);
void uinput_report_touch_event(UInput* thiz, int x, int y, int press/*1(down) 0(up) -1(move)*/);
void uinput_destroy(UInput* thiz);

#ifdef __cplusplus
}
#endif
#endif/*UINPUT_H*/

