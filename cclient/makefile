include makefile.local

#Can be one of win32, macos, linux
PLATFORM ?= win32

OBJ_DIR ?= obj
DEPS_DIR ?= dep
EXECUTABLE = apricot

C_FILES = $(wildcard *.c)
CPP_FILES = $(wildcard *.cpp) $(wildcard test/*.cpp)
HEADER_DIRS += $(SDL_INCLUDE_DIR)
LIB_DIRS += $(SDL_LIB_DIR)
LDLIBS += $(SDL_LIBS)

ifeq ($(PLATFORM),win32)
	include makefile.win32
else
	#put non-windows-specific definitions here
	OBJ_FILES = $(adprefix $(OBJ_DIR)/,$(C_FILES):.c=.o)
endif


.DEFAULT : $(EXECUTABLE)
debug : $(EXECUTABLE)

.PHONY : clean
clean :
	$(RM) obj/*
	$(RM) dep/*
	$(RM) $(EXECUTABLE)

-include $(patsubst %.cpp,$(DEPS_DIR)/%.d,$(CPP_FILES))


