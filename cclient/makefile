include makefile.local

.SECONDEXPANSION :

#Can be one of win32, macos, linux
PLATFORM ?= win32

OBJ_DIR ?= obj
DEPS_DIR ?= dep
EXECUTABLE = apricot

SUBDIRS = 	test \
			rendering \
			sdl

CPP_FILES = $(wildcard *.cpp) \
			$(wildcard test/*.cpp) \
			$(wildcard rendering/*.cpp) \
			$(wildcard sdl/*.cpp)

ALL_OBJ_DIRS = $(OBJ_DIR) $(addprefix $(OBJ_DIR)/,$(SUBDIRS))
ALL_DEPS_DIRS = $(DEPS_DIR) $(addprefix $(DEPS_DIR)/,$(SUBDIRS))

HEADER_DIRS += $(SDL_INCLUDE_DIR) .
LIB_DIRS += $(SDL_LIB_DIR)
LDLIBS += $(SDL_LIBS)

ifeq ($(PLATFORM),win32)
#For windows
include makefile.win32

else
#For everyone else
MKDIR = mkdir -p

OBJ_FILES = $(addprefix $(OBJ_DIR)/,$(CPP_FILES:.cpp=.o))
CXXFLAGS += $(addprefix -I,$(HEADER_DIRS))
LDFLAGS += $(addprefix -L,$(LIB_DIRS))
LDLIBS := $(addprefix -l,$(LDLIBS))

debug: CXXFLAGS += -pg -g

$(EXECUTABLE) : $(OBJ_FILES)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LOADLIBES) $(LDLIBS) 

$(OBJ_DIR)/%.o : %.cpp | $$(@D)
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(CXXFLAGS) -c -o $@ $<

$(DEPS_DIR)/%.d : %.cpp | $$(@D)
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(CXXFLAGS) -MM -o $@.tmp $<
	sed 's;\<\([^ \t]*\.o\)[ :]*; \1 $@ :;g' < $@.tmp > $@
	$(RM) $@.tmp

endif


debug : $(EXECUTABLE)

$(ALL_OBJ_DIRS) $(ALL_DEPS_DIRS) :
	$(MKDIR) $@ 

.PHONY : clean
clean :
	$(RM) $(addsuffix /*.o,$(ALL_OBJ_DIRS))
	$(RM) $(addsuffix /*.d,$(ALL_DEPS_DIRS))
	$(RM) $(addsuffix /*.obj,$(ALL_OBJ_DIRS))
	$(RM) $(addsuffix /*.dep,$(ALL_DEPS_DIRS))
	$(RM) $(EXECUTABLE)


#include dep files
ifneq ($(MAKECMDGOALS),clean)
-include $(patsubst %.cpp,$(DEPS_DIR)/%.d,$(CPP_FILES))
endif


