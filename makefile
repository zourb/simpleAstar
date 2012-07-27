CC=g++ -fpic -g

ifeq ($(DEBUG),yes)
	CXXFLAGS=-Wall -g
	LDFLAGS=-Wall -g
else
	CXXFLAGS=-Wall
	LDFLAGS=-Wall
endif

INCPATH=inc
SRCPATH=src
OBJPATH=obj
LIBPATH=lib
BINPATH=bin

SRC=$(SRCPATH)/State_Base.cpp \
    $(SRCPATH)/State.cpp \
    $(SRCPATH)/A_Star.cpp \
    $(SRCPATH)/main.cpp \
    $(SRCPATH)/PriorMap.cpp
OBJ=$(OBJPATH)/State_Base.o \
    $(OBJPATH)/State.o \
    $(OBJPATH)/A_Star.o \
    $(OBJPATH)/main.o \
    $(OBJPATH)/PriorMap.o
EXEC=$(BINPATH)/example

INCLUDES=-I ./$(INCPATH)

default: $(EXEC)

$(EXEC): $(OBJ)
#	$(CC) $(LDFLAGS) -o $@ $^
	$(CC) -shared -o lib/libastar.so $(OBJ) 

$(OBJPATH)/%.o: $(SRCPATH)/%.cpp
	$(CC) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: clean cleanall

clean:
	rm -f $(OBJPATH)/*.o 
	rm -f lib/libastar.so

cleanall: clean
	rm -f $(EXEC)

