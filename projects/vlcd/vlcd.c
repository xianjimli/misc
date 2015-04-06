/*
 * File:    vlcd.c 
 * Author:  Li XianJing <lixianjing@broncho.cn>
 * Brief:   virtual lcd for android.
 *
 * Copyright (c) 2009  topwise, Inc.
 *
 * Licensed under the Academic Free License version 2.1
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * History:
 * ================================================================
 * 2009-06-01 Li XianJing <lixianjing@broncho.cn> created
 *
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <linux/kd.h>
#include <rfb/rfb.h>
#include <rfb/keysym.h>
#include <linux/input.h>

typedef struct _FrameBuffer
{
	int fd;
	size_t size;
	unsigned short* buffer;
	struct fb_fix_screeninfo fix;
	struct fb_var_screeninfo var;
}FrameBuffer;

#define fb_width(fb) ((fb)->var.xres)
#define fb_height(fb) ((fb)->var.yres)
#define fb_size(fb) ((fb)->var.xres * (fb)->var.yres * 2)

FrameBuffer* framebuffer_create(const char* file_name)
{
	FrameBuffer* fb = (FrameBuffer*)calloc(1, sizeof(FrameBuffer));
	
	do
	{
		if((fb->fd = open(file_name, O_RDWR)) < 0) break;
		if(ioctl(fb->fd, FBIOGET_FSCREENINFO, &fb->fix) < 0) break;
		if(ioctl(fb->fd, FBIOGET_VSCREENINFO, &fb->var) < 0) break;

		fb->buffer = mmap(0, fb_size(fb), PROT_READ | PROT_WRITE, MAP_SHARED, fb->fd, 0);
		if(fb->buffer == MAP_FAILED) break;

		printf("%s: width=%d height=%d\n", file_name, fb_width(fb), fb_height(fb));
		return fb;
	}while(0);

	if(fb != NULL)
	{
		if(fb->fd > 0)
		{
			close(fb->fd);
		}

		free(fb);
	}

	return NULL;
}

void framebuffer_destroy(FrameBuffer* fb)
{
	if(fb != NULL)
	{
		munmap(fb->buffer, fb_size(fb));
		close(fb->fd);
		free(fb);
	}

	return;
}

static int g_max_x= 0;
static int g_max_y= 0;
static int g_client_nr = 0;

typedef struct ClientData 
{
  rfbBool oldButton;
  int oldx;
  int oldy;
} ClientData;

static void on_client_gone(rfbClientPtr cl)
{
  g_client_nr--;
  free(cl->clientData);
  fprintf(stderr, "%s g_client_nr=%d\n", __func__, g_client_nr);

  return;
}

static enum rfbNewClientAction on_new_client(rfbClientPtr cl)
{
  g_client_nr++;
  cl->clientData = (void*)calloc(sizeof(ClientData),1);
  cl->clientGoneHook = on_client_gone;
  fprintf(stderr, "%s g_client_nr=%d\n", __func__, g_client_nr);

  return RFB_CLIENT_ACCEPT;
}

#if 0
struct mouse_event
{
    int press;
    int x;
    int y;
};

static int g_vmouse_fd    = 0;
static int g_vkeyboard_fd = 0;

static void open_input_device(void)
{
	g_vmouse_fd = open("/dev/vmouse", O_RDWR);
	g_vkeyboard_fd = open("/dev/vkeyboard", O_RDWR);

	return;
}

static void on_pointer_event(int buttonMask,int x,int y,rfbClientPtr cl)
{
	ClientData* cd=cl->clientData;
	struct mouse_event event = {.x = x, .y = y};	
	if(x>=0 && y>=0 && x<g_max_x && y<g_max_y) 
	{
		if(buttonMask) 
		{
			 if(cd->oldButton==buttonMask) 
			 { 
			 	printf("move %d %d\n", x, y);
				event.press = -1;
				write(g_vmouse_fd, &event, sizeof(event));
			 } else 
			 { 
			 	printf("press g_vmouse_fd=%d %d %d\n", g_vmouse_fd, x, y);
				event.press = 1;
				write(g_vmouse_fd, &event, sizeof(event));
			 }
		}
		else
		{
			if(cd->oldButton)
			{
				printf("up %d %d\n", x, y);
				event.press = 0;
				write(g_vmouse_fd, &event, sizeof(event));
			}
			
			cd->oldButton=0;
		}
		cd->oldx=x; cd->oldy=y; cd->oldButton=buttonMask;
	}
	rfbDefaultPtrAddEvent(buttonMask,x,y,cl);

	return;
}

struct keyboard_event
{
	int press;
	int key;
};

static int key_map[256] = 
{
	['1'] = KEY_1,
	['2'] = KEY_2,
	['3'] = KEY_3,
	['4'] = KEY_4,
	['5'] = KEY_5,
	['6'] = KEY_6,
	['7'] = KEY_7,
	['8'] = KEY_8,
	['9'] = KEY_9,
	['0'] = KEY_0,
	['a'] = KEY_A,
	['b'] = KEY_B,
	['c'] = KEY_C,
	['d'] = KEY_D,
	['e'] = KEY_E,
	['f'] = KEY_F,
	['g'] = KEY_G,
	['h'] = KEY_H,
	['i'] = KEY_I,
	['j'] = KEY_J,
	['k'] = KEY_K,
	['l'] = KEY_L,
	['m'] = KEY_M,
	['n'] = KEY_N,
	['o'] = KEY_O,
	['p'] = KEY_P,
	['q'] = KEY_Q,
	['r'] = KEY_R,
	['s'] = KEY_S,
	['t'] = KEY_T,
	['u'] = KEY_U,
	['v'] = KEY_V,
	['w'] = KEY_W,
	['x'] = KEY_X,
	['y'] = KEY_Y,
	['z'] = KEY_Z,
	[','] = KEY_COMMA,
	['.'] = KEY_DOT,
	['/'] = KEY_SLASH,
};

static void on_key_event(rfbBool down,rfbKeySym key,rfbClientPtr cl)
{
	struct keyboard_event event = {.press = down, .key = key};
  	if(key < 0x100)
  	{
  		key = key_map[key];
  	}
  	else
  	{
  		switch(key)
  		{
  			case 0xffbe: key = 102;break; /*F1-->HOME*/
  			case 0xffbf: key = 59;break; /*MENU*/
  			case 0xffc0: key = 158;break; /*BACK*/
  			case 0xffc1: key = 115;break; /*VOLUME_UP*/
  			case 0xffc2: key = 114;break; /*VOLUME_DOWN*/
  			case 0xffc3: key = KEY_FN_F5;break;
  			case 0xff0d: key = KEY_ENTER; break;
  			case 0xff08: key = KEY_BACKSPACE;break;
  			default:break;
  		}
  	}
  	
  	printf("g_vkeyboard_fd=%d %d %d->%d\n", g_vkeyboard_fd, down, event.key, key);
  	event.key = key;
  	write(g_vkeyboard_fd, &event, sizeof(event));

  	return;
}

static void close_input_device(void)
{
	close(g_vmouse_fd);
	close(g_vkeyboard_fd);

	return;
}
#else
#include "uinput.h"
static UInput* g_input;
static void open_input_device(void)
{
	g_input = uinput_create(NULL, 320, 480);
	printf("%s: g_input=%p\n", __func__, g_input);
}
static void on_pointer_event(int buttonMask, int x,int y, rfbClientPtr cl)
{
	ClientData* cd=cl->clientData;
	if(x>=0 && y>=0 && x<g_max_x && y<g_max_y) 
	{
		if(buttonMask) 
		{
			 if(cd->oldButton==buttonMask) 
			 { 
			 	printf("move %d %d\n", x, y);
			 	uinput_report_touch_event(g_input, x, y, -1);
			 } else 
			 { 
			 	printf("press %d %d\n", x, y);
			 	uinput_report_touch_event(g_input, x, y, 1);
			 }
		}
		else
		{
			if(cd->oldButton)
			{
				printf("up %d %d\n", x, y);
			 	uinput_report_touch_event(g_input, x, y, 0);
			}
			
			cd->oldButton=0;
		}
		cd->oldx=x; cd->oldy=y; cd->oldButton=buttonMask;
	}
	rfbDefaultPtrAddEvent(buttonMask,x,y,cl);

	return;
}

static void on_key_event(rfbBool down,rfbKeySym key,rfbClientPtr cl)
{
	uinput_report_key_event(g_input, key, down);

	return;
}

static void close_input_device(void)
{
	uinput_destroy(g_input);
	g_input = NULL;

	return;
}

#endif

static void on_set_xcut_text (char* str,int len, struct _rfbClientRec* cl)
{
	printf("%s: %s\n", __func__, str);
	return;
}

static int  on_get_file_transfer_permitted(struct _rfbClientRec* cl)
{
	return 1;
}

static void on_set_text_chat(struct _rfbClientRec* cl, int length, char *string)
{
	printf("%s: %s\n", __func__, string);
	return;
}


#define FBDEVICE "/dev/fb0"
static const char* fb_devices[] =
{
	 "/dev/fb1",
	 "/dev/fb0",
	 "/dev/graphics/fb0",
	 NULL
};

int main(int argc,char** argv)
{
	int i;
	FrameBuffer* fb = NULL;
	for(i = 0; fb_devices[i] != NULL && fb == NULL; i++)
	{
		fb = framebuffer_create(fb_devices[i]);
	}

	if(fb == NULL)
	{
		printf("open framebuffer failed.\n");

		return -1;
	}

	open_input_device();
	rfbScreenInfoPtr rfbScreen=rfbGetScreen(&argc, argv, fb_width(fb), fb_height(fb), 5, 3, 2);
	rfbScreen->desktopName  = "Android Virtual LCD";
	rfbScreen->frameBuffer  = (char*)calloc(1, fb_width(fb) * fb_height(fb) * 2);
	rfbScreen->alwaysShared = 0;
	
	g_max_x = fb_width(fb);
	g_max_y = fb_height(fb);

	rfbScreen->ptrAddEvent = on_pointer_event;
	rfbScreen->kbdAddEvent = on_key_event;
	rfbScreen->newClientHook = on_new_client;
	rfbScreen->setXCutText = on_set_xcut_text;
	rfbScreen->setTextChat = on_set_text_chat;

	rfbInitServer(rfbScreen);
    
	struct timeval tv = {0};
	struct timeval last_update = {0};
	gettimeofday(&last_update, NULL);
	for(i=0;rfbIsActive(rfbScreen);i++) 
	{
		int w = 0;
		int h = 0;
		unsigned short r, g, b;
		unsigned short color = 0;
		unsigned short* src = fb->buffer;
		unsigned short* dst = (unsigned short*)rfbScreen->frameBuffer;
		int diff_update = 0;
		gettimeofday(&tv, NULL);
		diff_update = (tv.tv_sec-last_update.tv_sec)*1000 + (tv.tv_usec - last_update.tv_usec)/1000;

		if(g_client_nr > 0 && diff_update > 200)
		{
			for(h = 0; h < fb_height(fb); h++)
			{
				for(w = 0; w < fb_width(fb); w++)
				{
					color = src[w];
					b = (color >> 11) & 0x1f;
					g = (color >> 6) & 0x1f;
					r = color & 0x1f;
					dst[w] = (r << 10) | (g << 5) | b;
				}
				dst = (unsigned short*)((size_t)dst + fb->fix.line_length);
				src = (unsigned short*)((size_t)src + fb->fix.line_length);
			}
			gettimeofday(&last_update, NULL);
			rfbMarkRectAsModified(rfbScreen, 0, 0, fb_width(fb), fb_height(fb));
			printf("update lcd\n");
		}
		else if(g_client_nr == 0)
		{
			sleep(1);
		}
		rfbProcessEvents(rfbScreen,200000);
	}

	close_input_device();

	free(rfbScreen->frameBuffer);
	rfbScreenCleanup(rfbScreen);
	framebuffer_destroy(fb);

	return(0);
}
