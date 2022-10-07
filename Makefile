CC=g++

CFLAGS+=-Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wmissing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -D_DEBUG -D_EJUDGE_CLIENT_SIDE

COMP_OBJ = compiler.o

all: wtfcomp.exe

wtfcomp.exe: $(COMP_OBJ)
	$(CC) $(COMP_OBJ) $(CFLAGS) -o wtfcomp.exe

a.exe: $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o a.exe

*.o: *.cpp
	$(CC) $(CFLAGS) *.cpp -c

clean:
	rm -rf *.o *.exe*
	clear