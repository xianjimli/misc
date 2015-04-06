LOCAL_PATH=$(PWD)
OBJS:= \
	./libvncserver/main.o\
	./libvncserver/httpd.o\
	./libvncserver/d3des.o\
	./libvncserver/rre.o\
	./libvncserver/auth.o\
	./libvncserver/rfbregion.o\
	./libvncserver/zlib.o\
	./libvncserver/vncauth.o\
	./libvncserver/cursor.o\
	./libvncserver/translate.o\
	./libvncserver/ultra.o\
	./libvncserver/stats.o\
	./libvncserver/sockets.o\
	./libvncserver/draw.o\
	./libvncserver/minilzo.o\
	./libvncserver/rfbserver.o\
	./libvncserver/zrlepalettehelper.o\
	./libvncserver/zrle.o\
	./libvncserver/font.o\
	./libvncserver/cargs.o\
	./libvncserver/hextile.o\
	./libvncserver/zrleoutstream.o\
	./libvncserver/selbox.o\
	./libvncserver/scale.o\
	./libvncserver/cutpaste.o\
	./libvncserver/corre.o\
	./libvncserver/tight.o\
	./vlcd.o ./uinput.o

LOCAL_CFLAGS += -I$(LOCAL_PATH) -I$(LOCAL_PATH)/rfb -I$(LOCAL_PATH)/libvncserver
.c.o: $<
	gcc -g -c $(LOCAL_CFLAGS) $< -o $@

all: $(OBJS)
	gcc $(LOCAL_CFLAGS) $(OBJS) -ljpeg -lpng -lz -lpthread -o vlcd
clean:
	rm -f *.o $(OBJS) vlcd

