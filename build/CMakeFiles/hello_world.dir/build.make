# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.11

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.11.4/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.11.4/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/pb/Desktop/Riscv/happy-hedgehog

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/pb/Desktop/Riscv/happy-hedgehog/build

# Include any dependencies generated for this target.
include CMakeFiles/hello_world.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/hello_world.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hello_world.dir/flags.make

CMakeFiles/hello_world.dir/src/hello_world/ccsbcs.c.obj: CMakeFiles/hello_world.dir/flags.make
CMakeFiles/hello_world.dir/src/hello_world/ccsbcs.c.obj: ../src/hello_world/ccsbcs.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/pb/Desktop/Riscv/happy-hedgehog/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/hello_world.dir/src/hello_world/ccsbcs.c.obj"
	/usr/local/riscv/bin/riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hello_world.dir/src/hello_world/ccsbcs.c.obj   -c /Users/pb/Desktop/Riscv/happy-hedgehog/src/hello_world/ccsbcs.c

CMakeFiles/hello_world.dir/src/hello_world/ccsbcs.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hello_world.dir/src/hello_world/ccsbcs.c.i"
	/usr/local/riscv/bin/riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/pb/Desktop/Riscv/happy-hedgehog/src/hello_world/ccsbcs.c > CMakeFiles/hello_world.dir/src/hello_world/ccsbcs.c.i

CMakeFiles/hello_world.dir/src/hello_world/ccsbcs.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hello_world.dir/src/hello_world/ccsbcs.c.s"
	/usr/local/riscv/bin/riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/pb/Desktop/Riscv/happy-hedgehog/src/hello_world/ccsbcs.c -o CMakeFiles/hello_world.dir/src/hello_world/ccsbcs.c.s

CMakeFiles/hello_world.dir/src/hello_world/diskio.c.obj: CMakeFiles/hello_world.dir/flags.make
CMakeFiles/hello_world.dir/src/hello_world/diskio.c.obj: ../src/hello_world/diskio.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/pb/Desktop/Riscv/happy-hedgehog/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/hello_world.dir/src/hello_world/diskio.c.obj"
	/usr/local/riscv/bin/riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hello_world.dir/src/hello_world/diskio.c.obj   -c /Users/pb/Desktop/Riscv/happy-hedgehog/src/hello_world/diskio.c

CMakeFiles/hello_world.dir/src/hello_world/diskio.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hello_world.dir/src/hello_world/diskio.c.i"
	/usr/local/riscv/bin/riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/pb/Desktop/Riscv/happy-hedgehog/src/hello_world/diskio.c > CMakeFiles/hello_world.dir/src/hello_world/diskio.c.i

CMakeFiles/hello_world.dir/src/hello_world/diskio.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hello_world.dir/src/hello_world/diskio.c.s"
	/usr/local/riscv/bin/riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/pb/Desktop/Riscv/happy-hedgehog/src/hello_world/diskio.c -o CMakeFiles/hello_world.dir/src/hello_world/diskio.c.s

CMakeFiles/hello_world.dir/src/hello_world/ff.c.obj: CMakeFiles/hello_world.dir/flags.make
CMakeFiles/hello_world.dir/src/hello_world/ff.c.obj: ../src/hello_world/ff.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/pb/Desktop/Riscv/happy-hedgehog/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/hello_world.dir/src/hello_world/ff.c.obj"
	/usr/local/riscv/bin/riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hello_world.dir/src/hello_world/ff.c.obj   -c /Users/pb/Desktop/Riscv/happy-hedgehog/src/hello_world/ff.c

CMakeFiles/hello_world.dir/src/hello_world/ff.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hello_world.dir/src/hello_world/ff.c.i"
	/usr/local/riscv/bin/riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/pb/Desktop/Riscv/happy-hedgehog/src/hello_world/ff.c > CMakeFiles/hello_world.dir/src/hello_world/ff.c.i

CMakeFiles/hello_world.dir/src/hello_world/ff.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hello_world.dir/src/hello_world/ff.c.s"
	/usr/local/riscv/bin/riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/pb/Desktop/Riscv/happy-hedgehog/src/hello_world/ff.c -o CMakeFiles/hello_world.dir/src/hello_world/ff.c.s

CMakeFiles/hello_world.dir/src/hello_world/lcd.c.obj: CMakeFiles/hello_world.dir/flags.make
CMakeFiles/hello_world.dir/src/hello_world/lcd.c.obj: ../src/hello_world/lcd.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/pb/Desktop/Riscv/happy-hedgehog/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/hello_world.dir/src/hello_world/lcd.c.obj"
	/usr/local/riscv/bin/riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hello_world.dir/src/hello_world/lcd.c.obj   -c /Users/pb/Desktop/Riscv/happy-hedgehog/src/hello_world/lcd.c

CMakeFiles/hello_world.dir/src/hello_world/lcd.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hello_world.dir/src/hello_world/lcd.c.i"
	/usr/local/riscv/bin/riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/pb/Desktop/Riscv/happy-hedgehog/src/hello_world/lcd.c > CMakeFiles/hello_world.dir/src/hello_world/lcd.c.i

CMakeFiles/hello_world.dir/src/hello_world/lcd.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hello_world.dir/src/hello_world/lcd.c.s"
	/usr/local/riscv/bin/riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/pb/Desktop/Riscv/happy-hedgehog/src/hello_world/lcd.c -o CMakeFiles/hello_world.dir/src/hello_world/lcd.c.s

CMakeFiles/hello_world.dir/src/hello_world/main.c.obj: CMakeFiles/hello_world.dir/flags.make
CMakeFiles/hello_world.dir/src/hello_world/main.c.obj: ../src/hello_world/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/pb/Desktop/Riscv/happy-hedgehog/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/hello_world.dir/src/hello_world/main.c.obj"
	/usr/local/riscv/bin/riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hello_world.dir/src/hello_world/main.c.obj   -c /Users/pb/Desktop/Riscv/happy-hedgehog/src/hello_world/main.c

CMakeFiles/hello_world.dir/src/hello_world/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hello_world.dir/src/hello_world/main.c.i"
	/usr/local/riscv/bin/riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/pb/Desktop/Riscv/happy-hedgehog/src/hello_world/main.c > CMakeFiles/hello_world.dir/src/hello_world/main.c.i

CMakeFiles/hello_world.dir/src/hello_world/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hello_world.dir/src/hello_world/main.c.s"
	/usr/local/riscv/bin/riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/pb/Desktop/Riscv/happy-hedgehog/src/hello_world/main.c -o CMakeFiles/hello_world.dir/src/hello_world/main.c.s

CMakeFiles/hello_world.dir/src/hello_world/movement.c.obj: CMakeFiles/hello_world.dir/flags.make
CMakeFiles/hello_world.dir/src/hello_world/movement.c.obj: ../src/hello_world/movement.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/pb/Desktop/Riscv/happy-hedgehog/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/hello_world.dir/src/hello_world/movement.c.obj"
	/usr/local/riscv/bin/riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hello_world.dir/src/hello_world/movement.c.obj   -c /Users/pb/Desktop/Riscv/happy-hedgehog/src/hello_world/movement.c

CMakeFiles/hello_world.dir/src/hello_world/movement.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hello_world.dir/src/hello_world/movement.c.i"
	/usr/local/riscv/bin/riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/pb/Desktop/Riscv/happy-hedgehog/src/hello_world/movement.c > CMakeFiles/hello_world.dir/src/hello_world/movement.c.i

CMakeFiles/hello_world.dir/src/hello_world/movement.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hello_world.dir/src/hello_world/movement.c.s"
	/usr/local/riscv/bin/riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/pb/Desktop/Riscv/happy-hedgehog/src/hello_world/movement.c -o CMakeFiles/hello_world.dir/src/hello_world/movement.c.s

CMakeFiles/hello_world.dir/src/hello_world/nt35310.c.obj: CMakeFiles/hello_world.dir/flags.make
CMakeFiles/hello_world.dir/src/hello_world/nt35310.c.obj: ../src/hello_world/nt35310.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/pb/Desktop/Riscv/happy-hedgehog/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/hello_world.dir/src/hello_world/nt35310.c.obj"
	/usr/local/riscv/bin/riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hello_world.dir/src/hello_world/nt35310.c.obj   -c /Users/pb/Desktop/Riscv/happy-hedgehog/src/hello_world/nt35310.c

CMakeFiles/hello_world.dir/src/hello_world/nt35310.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hello_world.dir/src/hello_world/nt35310.c.i"
	/usr/local/riscv/bin/riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/pb/Desktop/Riscv/happy-hedgehog/src/hello_world/nt35310.c > CMakeFiles/hello_world.dir/src/hello_world/nt35310.c.i

CMakeFiles/hello_world.dir/src/hello_world/nt35310.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hello_world.dir/src/hello_world/nt35310.c.s"
	/usr/local/riscv/bin/riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/pb/Desktop/Riscv/happy-hedgehog/src/hello_world/nt35310.c -o CMakeFiles/hello_world.dir/src/hello_world/nt35310.c.s

CMakeFiles/hello_world.dir/src/hello_world/sdcard.c.obj: CMakeFiles/hello_world.dir/flags.make
CMakeFiles/hello_world.dir/src/hello_world/sdcard.c.obj: ../src/hello_world/sdcard.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/pb/Desktop/Riscv/happy-hedgehog/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/hello_world.dir/src/hello_world/sdcard.c.obj"
	/usr/local/riscv/bin/riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hello_world.dir/src/hello_world/sdcard.c.obj   -c /Users/pb/Desktop/Riscv/happy-hedgehog/src/hello_world/sdcard.c

CMakeFiles/hello_world.dir/src/hello_world/sdcard.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hello_world.dir/src/hello_world/sdcard.c.i"
	/usr/local/riscv/bin/riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/pb/Desktop/Riscv/happy-hedgehog/src/hello_world/sdcard.c > CMakeFiles/hello_world.dir/src/hello_world/sdcard.c.i

CMakeFiles/hello_world.dir/src/hello_world/sdcard.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hello_world.dir/src/hello_world/sdcard.c.s"
	/usr/local/riscv/bin/riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/pb/Desktop/Riscv/happy-hedgehog/src/hello_world/sdcard.c -o CMakeFiles/hello_world.dir/src/hello_world/sdcard.c.s

CMakeFiles/hello_world.dir/src/hello_world/supplementary.c.obj: CMakeFiles/hello_world.dir/flags.make
CMakeFiles/hello_world.dir/src/hello_world/supplementary.c.obj: ../src/hello_world/supplementary.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/pb/Desktop/Riscv/happy-hedgehog/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/hello_world.dir/src/hello_world/supplementary.c.obj"
	/usr/local/riscv/bin/riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hello_world.dir/src/hello_world/supplementary.c.obj   -c /Users/pb/Desktop/Riscv/happy-hedgehog/src/hello_world/supplementary.c

CMakeFiles/hello_world.dir/src/hello_world/supplementary.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hello_world.dir/src/hello_world/supplementary.c.i"
	/usr/local/riscv/bin/riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/pb/Desktop/Riscv/happy-hedgehog/src/hello_world/supplementary.c > CMakeFiles/hello_world.dir/src/hello_world/supplementary.c.i

CMakeFiles/hello_world.dir/src/hello_world/supplementary.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hello_world.dir/src/hello_world/supplementary.c.s"
	/usr/local/riscv/bin/riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/pb/Desktop/Riscv/happy-hedgehog/src/hello_world/supplementary.c -o CMakeFiles/hello_world.dir/src/hello_world/supplementary.c.s

CMakeFiles/hello_world.dir/src/hello_world/wav_decode.c.obj: CMakeFiles/hello_world.dir/flags.make
CMakeFiles/hello_world.dir/src/hello_world/wav_decode.c.obj: ../src/hello_world/wav_decode.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/pb/Desktop/Riscv/happy-hedgehog/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/hello_world.dir/src/hello_world/wav_decode.c.obj"
	/usr/local/riscv/bin/riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hello_world.dir/src/hello_world/wav_decode.c.obj   -c /Users/pb/Desktop/Riscv/happy-hedgehog/src/hello_world/wav_decode.c

CMakeFiles/hello_world.dir/src/hello_world/wav_decode.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hello_world.dir/src/hello_world/wav_decode.c.i"
	/usr/local/riscv/bin/riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/pb/Desktop/Riscv/happy-hedgehog/src/hello_world/wav_decode.c > CMakeFiles/hello_world.dir/src/hello_world/wav_decode.c.i

CMakeFiles/hello_world.dir/src/hello_world/wav_decode.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hello_world.dir/src/hello_world/wav_decode.c.s"
	/usr/local/riscv/bin/riscv64-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/pb/Desktop/Riscv/happy-hedgehog/src/hello_world/wav_decode.c -o CMakeFiles/hello_world.dir/src/hello_world/wav_decode.c.s

# Object files for target hello_world
hello_world_OBJECTS = \
"CMakeFiles/hello_world.dir/src/hello_world/ccsbcs.c.obj" \
"CMakeFiles/hello_world.dir/src/hello_world/diskio.c.obj" \
"CMakeFiles/hello_world.dir/src/hello_world/ff.c.obj" \
"CMakeFiles/hello_world.dir/src/hello_world/lcd.c.obj" \
"CMakeFiles/hello_world.dir/src/hello_world/main.c.obj" \
"CMakeFiles/hello_world.dir/src/hello_world/movement.c.obj" \
"CMakeFiles/hello_world.dir/src/hello_world/nt35310.c.obj" \
"CMakeFiles/hello_world.dir/src/hello_world/sdcard.c.obj" \
"CMakeFiles/hello_world.dir/src/hello_world/supplementary.c.obj" \
"CMakeFiles/hello_world.dir/src/hello_world/wav_decode.c.obj"

# External object files for target hello_world
hello_world_EXTERNAL_OBJECTS =

hello_world: CMakeFiles/hello_world.dir/src/hello_world/ccsbcs.c.obj
hello_world: CMakeFiles/hello_world.dir/src/hello_world/diskio.c.obj
hello_world: CMakeFiles/hello_world.dir/src/hello_world/ff.c.obj
hello_world: CMakeFiles/hello_world.dir/src/hello_world/lcd.c.obj
hello_world: CMakeFiles/hello_world.dir/src/hello_world/main.c.obj
hello_world: CMakeFiles/hello_world.dir/src/hello_world/movement.c.obj
hello_world: CMakeFiles/hello_world.dir/src/hello_world/nt35310.c.obj
hello_world: CMakeFiles/hello_world.dir/src/hello_world/sdcard.c.obj
hello_world: CMakeFiles/hello_world.dir/src/hello_world/supplementary.c.obj
hello_world: CMakeFiles/hello_world.dir/src/hello_world/wav_decode.c.obj
hello_world: CMakeFiles/hello_world.dir/build.make
hello_world: lib/libkendryte.a
hello_world: CMakeFiles/hello_world.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/pb/Desktop/Riscv/happy-hedgehog/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking C executable hello_world"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hello_world.dir/link.txt --verbose=$(VERBOSE)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating .bin file ..."
	/usr/local/riscv/bin/riscv64-unknown-elf-objcopy --output-format=binary /Users/pb/Desktop/Riscv/happy-hedgehog/build/hello_world /Users/pb/Desktop/Riscv/happy-hedgehog/build/hello_world.bin

# Rule to build all files generated by this target.
CMakeFiles/hello_world.dir/build: hello_world

.PHONY : CMakeFiles/hello_world.dir/build

CMakeFiles/hello_world.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/hello_world.dir/cmake_clean.cmake
.PHONY : CMakeFiles/hello_world.dir/clean

CMakeFiles/hello_world.dir/depend:
	cd /Users/pb/Desktop/Riscv/happy-hedgehog/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/pb/Desktop/Riscv/happy-hedgehog /Users/pb/Desktop/Riscv/happy-hedgehog /Users/pb/Desktop/Riscv/happy-hedgehog/build /Users/pb/Desktop/Riscv/happy-hedgehog/build /Users/pb/Desktop/Riscv/happy-hedgehog/build/CMakeFiles/hello_world.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hello_world.dir/depend

