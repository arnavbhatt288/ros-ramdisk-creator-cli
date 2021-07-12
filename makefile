.POSIX:

CC=gcc

ifeq ($(OS),Windows_NT)
	CFLAGS += -std=c99
	CLEAN =  del ramdisk-creator.exe main.o $(COMPONENTS:=.o)
	COMPONENTS = ini win32_volume
else
	CLEAN = rm -f ramdisk-creator main.o $(COMPONENTS:=.o)
	COMPONENTS = ini volume
endif

all: ramdisk-creator

main.o: main.c arg.h fs_data.h ini.h ini_data.h volume.h win32_volume.h
ini.o: volume.c ini.h
volume.o: volume.c volume.h
win32_volume.o: win32_volume.c win32_volume.h

ramdisk-creator: $(COMPONENTS:=.o) $(COMPONENTS:=.h) main.o
	$(CC) -o $@ $(CFLAGS) main.o $(COMPONENTS:=.o) $(LDFLAGS)

clean:
	$(CLEAN)