# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/Augustine/Documents/ECE4122/BattleSystem

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/Augustine/Documents/ECE4122/BattleSystem

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /mnt/c/Users/Augustine/Documents/ECE4122/BattleSystem/CMakeFiles /mnt/c/Users/Augustine/Documents/ECE4122/BattleSystem/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /mnt/c/Users/Augustine/Documents/ECE4122/BattleSystem/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named run

# Build rule for target.
run: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 run
.PHONY : run

# fast build rule for target.
run/fast:
	$(MAKE) -f CMakeFiles/run.dir/build.make CMakeFiles/run.dir/build
.PHONY : run/fast

#=============================================================================
# Target rules for targets named SFMLDemo

# Build rule for target.
SFMLDemo: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 SFMLDemo
.PHONY : SFMLDemo

# fast build rule for target.
SFMLDemo/fast:
	$(MAKE) -f CMakeFiles/SFMLDemo.dir/build.make CMakeFiles/SFMLDemo.dir/build
.PHONY : SFMLDemo/fast

MoveButton.o: MoveButton.cpp.o

.PHONY : MoveButton.o

# target to build an object file
MoveButton.cpp.o:
	$(MAKE) -f CMakeFiles/SFMLDemo.dir/build.make CMakeFiles/SFMLDemo.dir/MoveButton.cpp.o
.PHONY : MoveButton.cpp.o

MoveButton.i: MoveButton.cpp.i

.PHONY : MoveButton.i

# target to preprocess a source file
MoveButton.cpp.i:
	$(MAKE) -f CMakeFiles/SFMLDemo.dir/build.make CMakeFiles/SFMLDemo.dir/MoveButton.cpp.i
.PHONY : MoveButton.cpp.i

MoveButton.s: MoveButton.cpp.s

.PHONY : MoveButton.s

# target to generate assembly for a file
MoveButton.cpp.s:
	$(MAKE) -f CMakeFiles/SFMLDemo.dir/build.make CMakeFiles/SFMLDemo.dir/MoveButton.cpp.s
.PHONY : MoveButton.cpp.s

MoveMenu.o: MoveMenu.cpp.o

.PHONY : MoveMenu.o

# target to build an object file
MoveMenu.cpp.o:
	$(MAKE) -f CMakeFiles/SFMLDemo.dir/build.make CMakeFiles/SFMLDemo.dir/MoveMenu.cpp.o
.PHONY : MoveMenu.cpp.o

MoveMenu.i: MoveMenu.cpp.i

.PHONY : MoveMenu.i

# target to preprocess a source file
MoveMenu.cpp.i:
	$(MAKE) -f CMakeFiles/SFMLDemo.dir/build.make CMakeFiles/SFMLDemo.dir/MoveMenu.cpp.i
.PHONY : MoveMenu.cpp.i

MoveMenu.s: MoveMenu.cpp.s

.PHONY : MoveMenu.s

# target to generate assembly for a file
MoveMenu.cpp.s:
	$(MAKE) -f CMakeFiles/SFMLDemo.dir/build.make CMakeFiles/SFMLDemo.dir/MoveMenu.cpp.s
.PHONY : MoveMenu.cpp.s

character.o: character.cpp.o

.PHONY : character.o

# target to build an object file
character.cpp.o:
	$(MAKE) -f CMakeFiles/SFMLDemo.dir/build.make CMakeFiles/SFMLDemo.dir/character.cpp.o
.PHONY : character.cpp.o

character.i: character.cpp.i

.PHONY : character.i

# target to preprocess a source file
character.cpp.i:
	$(MAKE) -f CMakeFiles/SFMLDemo.dir/build.make CMakeFiles/SFMLDemo.dir/character.cpp.i
.PHONY : character.cpp.i

character.s: character.cpp.s

.PHONY : character.s

# target to generate assembly for a file
character.cpp.s:
	$(MAKE) -f CMakeFiles/SFMLDemo.dir/build.make CMakeFiles/SFMLDemo.dir/character.cpp.s
.PHONY : character.cpp.s

main.o: main.cpp.o

.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) -f CMakeFiles/SFMLDemo.dir/build.make CMakeFiles/SFMLDemo.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i

.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) -f CMakeFiles/SFMLDemo.dir/build.make CMakeFiles/SFMLDemo.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s

.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) -f CMakeFiles/SFMLDemo.dir/build.make CMakeFiles/SFMLDemo.dir/main.cpp.s
.PHONY : main.cpp.s

move.o: move.cpp.o

.PHONY : move.o

# target to build an object file
move.cpp.o:
	$(MAKE) -f CMakeFiles/SFMLDemo.dir/build.make CMakeFiles/SFMLDemo.dir/move.cpp.o
.PHONY : move.cpp.o

move.i: move.cpp.i

.PHONY : move.i

# target to preprocess a source file
move.cpp.i:
	$(MAKE) -f CMakeFiles/SFMLDemo.dir/build.make CMakeFiles/SFMLDemo.dir/move.cpp.i
.PHONY : move.cpp.i

move.s: move.cpp.s

.PHONY : move.s

# target to generate assembly for a file
move.cpp.s:
	$(MAKE) -f CMakeFiles/SFMLDemo.dir/build.make CMakeFiles/SFMLDemo.dir/move.cpp.s
.PHONY : move.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... run"
	@echo "... SFMLDemo"
	@echo "... MoveButton.o"
	@echo "... MoveButton.i"
	@echo "... MoveButton.s"
	@echo "... MoveMenu.o"
	@echo "... MoveMenu.i"
	@echo "... MoveMenu.s"
	@echo "... character.o"
	@echo "... character.i"
	@echo "... character.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... move.o"
	@echo "... move.i"
	@echo "... move.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

