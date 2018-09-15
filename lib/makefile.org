OBJS   = sys.o vec.o mouse.o gl.o gra.o file.o env.o win.o joystick.o glfilter.o glbitmap.o glfont.o bmp.o key.o texture.o sound.o gdi.o gram.o


#CFLAGS   = -g -Wall -Werror -Wno-unused-variable -Wno-unused-but-set-variable -Wno-format -Wno-unused-value -Wno-unused-label 
#CFLAGS   = -g -Wall -Werror -Wno-unused-function -Wno-unused-variable -Wno-sign-compare -Wno-unused-but-set-variable -Wno-format
CFLAGS   = -g -Wall -Werror -Wno-unused-function -Wno-unused-variable -Wno-sign-compare -Wno-unused-but-set-variable -Wno-format
LDFLAGS  = 
LDLIBS   =    


sys.a: $(OBJS)
	ar r $@ $^ 


.cpp.o:
	g++ -c -o $@ $^ $(CFLAGS) -I.  -Ic:/msys64

clean:
	rm -f *.o *.out *.exe $(TARGET)

	