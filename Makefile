# inspired by: github.com/KRMisha/Makefile
# and: https://stackoverflow.com/questions/27001837/makefile-to-compile-all-cpp-files-in-all-subdirs

#Executable name
EXEC = library-test

# Build and bin directories
BUILD_DIR_ROOT = build
BIN_DIR_ROOT   = bin

# Source directries (searches recursively)
SRC_DIR = src
ifneq ($(OS), Windows_NT)
  SRCS := $(sort $(shell find $(SRC_DIR) -name '*.cpp'))
else
	#SRCS := $(sort $(shell dir /s/b $(SRC_DIR)\*.cpp))
  SRCS := $(sort $(shell forfiles /P $(SRC_DIR) /S /M *.cpp /C "cmd /c echo @relpath"))
  SRCS := $(patsubst ".\\%",$(SRC_DIR)\\%,$(SRCS))
endif

# Include directory
INCLUDE_DIR = include
INCLUDES := -I$(INCLUDE_DIR)

# C preprocessor settings
CPPFLAGS = $(INCLUDES) -MMD -MP

# C++ compiler settings
CXX      = g++
CXXFLAGS = -std=c++23
WARNINGS = -Wall -Wpedantic -Wextra

# Linker flags
LDFLAGS =

# Libraries to link
LDLIBS = 

ifeq ($(OS), Windows_NT)
  OS = windows
else
  UNAME := $(shell uname -s)
  ifeq ($(UNAME), Darwin)
    OS = macos
  else ifeq ($(UNAME), Linux)
    OS = linux
  else
    $(error OS not supported...) 
  endif
endif

# OS-specific settings
ifeq ($(OS), windows)
  # add here windows specific settings
else ifeq ($(OS), macos)
  # add here macos specific settings
else ifeq ($(OS), linux)
  # add here linux specific settings
endif

# Default windows-specific settings
ifeq ($(OS), windows)
  # Add .exe extension
  EXEC := $(EXEC).exe

  # Hint for windows 32-bit or windows 64-bit
  ifeq ($(win32), 1)
    CXXFLAGS += -m32
  else
    CXXFLAGS += -m64
  endif
endif

# OS-specific directories
BUILD_DIR := $(BUILD_DIR_ROOT)/$(OS)
BIN_DIR   := $(BIN_DIR_ROOT)/$(OS)

ifeq ($(OS), windows)	
  ifeq ($(win32), 1)
    BUILD_DIR := $(BUILD_DIR)32
    BIN_DIR   := $(BIN_DIR)32
  else
    BUILD_DIR := $(BUILD_DIR)64
    BIN_DIR   := $(BIN_DIR)64
  endif
endif

# Debug and release modes settings and directories
ifeq ($(release), 1)
  BUILD_DIR := $(BUILD_DIR)/release
  BIN_DIR   := $(BIN_DIR)/release
  # Maximum optimizations
  CXXFLAGS  += -O3
  CPPFLAGS  += -DNDEBUG
else
  BUILD_DIR := $(BUILD_DIR)/debug
  BIN_DIR   := $(BIN_DIR)/debug
  CXXFLAGS  += -O0 -g
endif

# Return code variable & file remove cmd
ifeq ($(OS), windows)
  RETURN_CODE = %errorlevel%
  RM = del /S/Q
  MKDIR_D = if not exist $(@D) mkdir $(subst /,\,$(@D))
else
  RETURN_CODE = $?
  RM = rm -r
  MKDIR_D = mkdir -p $(@D)
endif

# Objects
ifneq ($(OS), windows)
  OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
else
  OBJS := $(SRCS:$(SRC_DIR)\\%.cpp=$(BUILD_DIR)/%.o)
endif

# All files (sources and headers)
FILES   := $(SRCS) $(INCLUDES)
#FILES := $(shell find $(SRC_DIR) $(INCLUDE_DIR) -name '*.cpp' -o -name '*.h' -o -name '*.hpp')

# Default (first) target
default: run

# Build rule
build: $(BIN_DIR)/$(EXEC)

# Build executable
$(BIN_DIR)/$(EXEC): $(OBJS)
	$(info Building executable: $@)
	@$(MKDIR_D)
	@$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

# Compile C++ source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(info Compiling: $<)
	@$(MKDIR_D)
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(WARNINGS) -c $< -o $@

# Include automatically generated dependencies
#-include $(DEPS)

# Build and run
run: build
	$(info Starting program: $(BIN_DIR)/$(EXEC):)
	$(info )
	@$(BIN_DIR)/$(EXEC)
	@echo Program exited with code: $(RETURN_CODE)

# Clean build and bin directories
clean:
	$(info Cleaning $(BUILD_DIR_ROOT) and $(BIN_DIR_ROOT) directories)
	@$(RM) $(BUILD_DIR_ROOT)
	@$(RM) $(BIN_DIR_ROOT)

# Print help
help:
	$(info Usage: make target.. [options...])
	$(info |)
	$(info | Targets:)
	$(info | 	default   Build and run the executable)
	$(info | 	build     Only build the executable)
	$(info |	run       Build and run the executable)
	$(info | 	clean     Clean build and bin directories)
	$(info | 	help      Print this help information)
	$(info | 	print     Print the Make variables for debug)
	$(info | )
	$(info | Options:)
	$(info | 	release=1 Build in release mode instead of debug mode)
	$(info | 	win32=1   Build for 32-bit Windows)

# Print Make variables
print:
	$(info OS: $(OS))
	$(info EXEC: $(EXEC))
	$(info BUILD_DIR: $(BUILD_DIR))
	$(info BIN_DIR: $(BIN_DIR))
	$(info BUILD_DIR_ROOT: $(BUILD_DIR_ROOT))
	$(info BIN_DIR_ROOT: $(BIN_DIR_ROOT))
	$(info SRC_DIR: $(SRC_DIR))
	$(info SRCS: $(SRCS))
	$(info INCLUDE_DIR: $(INCLUDE_DIR))
	$(info INCLUDES: $(INCLUDES))
	$(info FILES: $(FILES))
	$(info OBJS: $(OBJS))
	$(info CXX: $(CXX))
	$(info CPPFLAGS: $(CPPFLAGS))
	$(info CXXFLAGS: $(CXXFLAGS))
	$(info WARNINGS: $(WARNINGS))
	$(info LDFLAGS: $(LDFLAGS))
	$(info LDLIBS: $(LDLIBS))
