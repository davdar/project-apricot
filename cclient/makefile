include makefile.local

#Used for builds on windows
MSYS_BASE ?= C:/MinGW/msys/1.0
MSYS_BIN = $(MSYS_BASE)/bin 

#Used for excluding system included from .d makefiles
SYSTEM_INCLUDE_PATTERN = /\(microsoft visual studio\)/I

#Can be one of win32, macos, linux
PLATFORM ?= win32

OBJ_DIR ?= obj
DEPS_DIR ?= dep
EXECUTABLE = apricot

C_FILES = $(wildcard *.c)
CPP_FILES = $(wildcard *.cpp) \
			$(wildcard test/*.cpp)
HEADER_DIRS += $(SDL_INCLUDE_DIR)
LIB_DIRS += $(SDL_LIB_DIR)
LDLIBS += $(SDL_LIBS)

#Platform-specific variables
ifeq ($(PLATFORM),win32)
	CC = cl.exe
	CPP = cl.exe
	CXX = cl.exe
	RM = "$(MSYS_BIN)/rm" -Rf
	MKDIR = "$(MSYS_BIN)/mkdir" -p
	MV = "$(MSYS_BIN)/mv"
	EXECUTABLE := $(EXECUTABLE).exe
	OBJ_FILES = $(addprefix $(OBJ_DIR)/,$(C_FILES:.c=.obj) $(CPP_FILES:.cpp=.obj))
	CRTFLAG = /MD

#re-define CRTFLAG and add to CXXFLAGS if a debug build
debug : CRTFLAG = /MDd
debug : CXXFLAGS += /Od /Yd /Zi /DDEBUG

	CPPFLAGS += $(addprefix /I,$(HEADER_DIRS))  
	CXXFLAGS += $(CRTFLAG)
	LDFLAGS := /link $(addprefix /LIBPATH:,$(LIB_DIRS)) $(LDFLAGS) /SUBSYSTEM:CONSOLE
	LDLIBS := $(addprefix /DEFAULTLIB:,$(LDLIBS))

else
	#put non-windows-specific definitions here
	OBJ_FILES = $(adprefix $(OBJ_DIR)/,$(C_FILES):.c=.o)
endif


.DEFAULT : $(EXECUTABLE)
$(EXECUTABLE) : $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) $(LDFLAGS) $(LOADLIBES) $(LDLIBS)

debug : $(EXECUTABLE)

.PHONY : clean
clean :
	$(RM) obj/*
	$(RM) dep/*
	$(RM) $(EXECUTABLE)

#Platform-specific rules
ifeq ($(PLATFORM),win32)
$(OBJ_DIR)/%.obj : %.cpp
	$(MKDIR) $(dir $@)
	$(CXX) $(CFLAGS) $(CPPFLAGS) $(CXXFLAGS) $< /Fo$@ /c

$(DEPS_DIR)/%.d : %.cpp
	$(CPP) $(CPPFLAGS) /P $<
	$(MKDIR) $(dir $@)
	"$(MSYS_BIN)/sed" -n 's/^#line [0-9]* "\(.*\.h\)"/\1/gp' $(notdir $(patsubst %.cpp,%.i,$<)) | "$(MSYS_BIN)/uniq" | "$(MSYS_BIN)/sed" -e '1,1 i $@ $(patsubst %.cpp,$(OBJ_DIR)/%.obj,$<):' -e '$(SYSTEM_INCLUDE_PATTERN) d' | "$(MSYS_BIN)/tr" '\n' ' ' > $@
	$(RM) $(notdir $(patsubst %.cpp,%.i,$<))
endif

include $(patsubst %.cpp,$(DEPS_DIR)/%.d,$(CPP_FILES))


