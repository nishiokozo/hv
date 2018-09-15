TAR = sys.a

OBJS = \
	obj/sys.o \
	obj/vec.o \
	obj/mouse.o \
	obj/gl.o \
	obj/gra.o \
	obj/file.o \
	obj/env.o \
	obj/win.o \
	obj/joystick.o \
	obj/glfilter.o \
	obj/glbitmap.o \
	obj/glfont.o \
	obj/bmp.o \
	obj/key.o \
	obj/texture.o \
	obj/sound.o \
	obj/gdi.o \
	obj/gram.o \

FLGS   = \
	-c \
	-g \
	-Wall \
	-Werror \
	-Wno-unused-function \
	-Wno-unused-variable \
	-Wno-sign-compare \
	-Wno-unused-but-set-variable \
	-Wno-format \

INCS = \
	 -I. \
	 -Ic:/msys64 \

#CC	= clang++
CC	= g++

all:obj $(TAR)
#

$(TAR): $(OBJS)
	ar r $@ $^ 

obj/%.o:%.cpp
	$(CC)   $< -o $@ $(FLGS) $(INCS)

obj:
	mkdir obj

clean:
	rm -rf $(TAR) obj

	