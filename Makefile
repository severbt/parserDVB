# Name of output file
PROG_NAME	:= parser

# Compiler define
CC 		?= gcc

# Quiet build by default
QUIET 		?= @
#DEBUG_ENABLED	?= n

# Make rules
.PHONY: clean build checkbuilddirs

# Project dir
PROJ_DIR	:= $(shell pwd)
# Source and include dirs (must be edit if differs from actual)
SRC_DIRS	:= $(PROJ_DIR)/src
INC_DIRS	:= $(PROJ_DIR)/include
# Inner dirs defines
BLD_DIR		:= $(PROJ_DIR)/build
OBJ_DIR		:= $(BLD_DIR)/obj
TARG_DIR	:= $(BLD_DIR)/bin

# Paths and dirs
SRC_FILES	:= $(foreach dirname, $(SRC_DIRS), $(wildcard $(dirname)/*.cpp))
OBJ_FILES	:= $(foreach filename, $(notdir $(SRC_FILES)), $(OBJ_DIR)/$(filename:.cpp=.o))
VPATH		:= $(sort $(SRC_DIRS) $(foreach srcfile, $(SRC_FILES), $(dir $(srcfile))))
LOCAL_INCLUDES	:= $(foreach dirs, $(INC_DIRS), -I$(dirs))
PROG_FULL_NAME	:= $(TARG_DIR)/$(PROG_NAME)
CFLAGS		:= $(LOCAL_INCLUDES)

#ifeq ($(DEBUG_ENABLED),y)
#	CFLAGS += -g
#endif

CFLAGS += -std=c++11

# Build all
build:	checkbuilddirs $(PROG_FULL_NAME)

# Output
$(PROG_FULL_NAME): $(OBJ_FILES)
	$(QUIET)$(CC) $(CFLAGS) -o $@ $^
	@echo "Build complete"

# Object files
$(OBJ_DIR)/%.o: %.cpp
	@echo "Compiling $(notdir $^)..."
	$(QUIET)$(CC) -c $(CFLAGS) -o $@ $^

# Clean all
clean:
	$(QUIET)rm -f $(OBJ_FILES) $(PROG_FULL_NAME)
	$(QUIET)rm -f $(BLD_DIR) -r
	@echo "Project outputs cleaned"

# Create dirs
checkbuilddirs:
	$(QUIET)mkdir -p $(BLD_DIR)
	$(QUIET)mkdir -p $(OBJ_DIR)
	$(QUIET)mkdir -p $(TARG_DIR)

print:
	@echo $(OBJ_DIR)
	@echo $(OBJ_FILES)


