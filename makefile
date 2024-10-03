SOURCE   	:= $(patsubst src/%.cc,%.cc,$(wildcard src/*.cc))
RESOURCE 	:= $(patsubst res/%.rc,%.rc,$(wildcard res/*.rc))
OBJECT   	:= $(strip $(SOURCE:.cc=.o) $(RESOURCE:.rc=.o))



CPPCOMPILER := clang++
RESCOMPILER := windres

OFLAGS      := -Wall -Wextra -std=c++23 -c
EFLAGS      := -static -Wl,--subsystem,windows

INCDIRS  	:= -I inc
LIBS     	:= -l user32 -l comctl32 -l winmm -l gdi32


ifdef DEBUG
OFLAGS += -O0 -D DEVELOPMENT -ggdb
else
OFLAGS += -O2
endif

.PHONY: prepare all clean

all: prepare out/wildass.exe

prepare:
	if not exist obj md obj
	if not exist out md out

clean:
	rd /S/Q obj


obj/%.o: src/%.cc
	$(CPPCOMPILER) -o $@ $^ $(OFLAGS) $(INCDIRS)

obj/%.o: res/%.rc
	$(RESCOMPILER) -o $@ $^

out/wildass.exe: $(addprefix obj/,$(OBJECT))
	$(CPPCOMPILER) -o $@ $^ $(EFLAGS) $(LIBS)