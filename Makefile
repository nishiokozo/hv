OBJS   = main.o ed.o pcg.o

TARGETS = main

#CFLAGS   =  -g -Wall -Werror -Wno-unused-variable  -Wno-format -Wno-unused-value -Wno-unused-label
#CFLAGS   =  -g -Wall -Werror -Wno-unused-but-set-variable -Wno-unused-variable -Wno-sign-compare -Wno-unused-label      -Wno-uninitialized
CFLAGS   =  -g -Wall -Wformat -Wno-unused-but-set-variable -Wno-unused-variable -Wno-sign-compare -Wno-unused-label      -Wno-uninitialized
LDFLAGS  = 
#LDLIBS   =  -Ilib/ $(OBJS) lib/sys.a -mwindows -lopengl32 -lglew32 -static-libgcc -static-libstdc++
#LDLIBS   =  -Ilib/ $(OBJS) lib/sys.a -mwindows -mconsole -lwinmm -static-libgcc -static-libstdc++
#LDLIBS   =  -Ilib/ $(OBJS) lib/sys.a -mwindows -mconsole -lwinmm -static-libgcc -static-libstdc++ -lopengl32 -lglew32
LDLIBS   =  -Ilib/ $(OBJS) lib/sys.a -mwindows -mconsole -lwinmm -static-libgcc -static-libstdc++ -lopengl32


#all: $(TARGETS) 

main.exe: makefile lib/sys.a $(OBJS) 
	g++ -o main.exe $(LDLIBS) -g  

release:
	rm -rf hoverattack
	mkdir hoverattack
	g++ -o hoverattack/hoverattack.exe $(LDLIBS)
	cp env.ini		hoverattack/
	cp font.bmp		hoverattack/
#	cp font.glsl	hoverattack/
	cp hv.bin		hoverattack/
	cp glew32.dll	hoverattack/
#	cp f_streach_discard.glsl	hoverattack/
	cp hv-title.bmp	hoverattack/
	cp readme.txt	hoverattack/


sys:
	startsysmk.bat

.cpp.o:
	g++ -c -o $@ $^ $(CFLAGS) -Ilib/ -Ic:/msys64

clean:
	rm -f lib/*.o lib/*.out lib/*.a $(TARGETS)
	rm -f *.o *.out *.exe $(TARGETS)
