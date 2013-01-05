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
#For windows
include makefile.win32

else
#For everyone else
MKDIR = mkdir -p

OBJ_FILES = $(addprefix $(OBJ_DIR)/,$(C_FILES:.c=.o) $(CPP_FILES:.cpp=.o))
CXXFLAGS += $(addprefix -I,$(HEADER_DIRS))
LDFLAGS += $(addprefix -L,$(LIB_DIRS))
LDLIBS := $(addprefix -l,$(LDLIBS))

debug: CXXFLAGS += -pg

$(EXECUTABLE) : $(OBJ_FILES)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LOADLIBES) $(LDLIBS) 

$(OBJ_DIR)/%.o : %.cpp | $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(CXXFLAGS) -c -o $@ $<

$(DEPS_DIR)/%.d : %.cpp | $(DEPS_DIR)
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(CXXFLAGS) -MM -o $@.tmp $<
	sed 's;\<\([^ \t]*\.o\)[ :]*; \1 $@ :;g' < $@.tmp > $@
	$(RM) $@.tmp

endif


debug : $(EXECUTABLE)

$(OBJ_DIR) :
	$(MKDIR) $(OBJ_DIR)

$(DEPS_DIR) :
	$(MKDIR) $(DEPS_DIR)

.PHONY : clean
clean :
	$(RM) obj/*
	$(RM) dep/*
	$(RM) $(EXECUTABLE)


#include dep files
ifneq ($(MAKECMDGOALS),clean)
-include $(patsubst %.cpp,$(DEPS_DIR)/%.d,$(CPP_FILES))
endif


