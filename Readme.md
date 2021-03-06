## Reversi

### Screenshot
![](./image/reversi.png)

### Overview
Reversi (also called Othello) is a kind of strategy board game which involves play by two parties on an eight-by-eight square grid. For details of reversi please go to [https://en.wikipedia.org/wiki/Reversi](https://en.wikipedia.org/wiki/Reversi).

This reversi project is my simple work. The kernel is written in C++11 whith a bit inline assembly. Script language python and tcl can be embeded to ease the interaction with users. The GUI is built with wxwidgets. It can be written in C++ or python. The sources of this project can be merged in to a single file and submitted to [Botzone](https://botzone.org) which is a online platform for competetion of differnt bots made by students and other programming learners.

### Build reversi

- Prerequisites
	- Essential
		- gcc compiler  
			C++11 must be supported by this version of gcc. It cannot be compiled by Visual Studio as MS compiler supports neither 64-bit inline assembly nor AT&T flavor syntax. I'm not sure whether other compilers like Clang++ works or not.
	- Optional
		- CodeBlocks or Cbp2make (if you want to utilize the .cbp codeblocks project file to build this project)
		- TCL (if you want to embed tool command language)
		- cpptcl (if you want to embed tool command language)
		- Boost (required by cpptcl)
		- wxWidgets (required by the GUI version written in C++)
		- python3 (required by the GUI version written in Python and some simple scripts)
		- swig (required by the GUI version written in Python)
		- wxPython (required by the GUI version written in Python)

Personally, I've only built the project on 64-bit windows and cygwin but I believe it can migrates to other platforms.

- Build reversi with only basic functions
	1. Install latest version of gcc.
	2. Create a C++ project.
	3. Add following files to your project.  
		type.h type.cc reversi.h reversi.cc flip.cc search.h search.cc pattern.h pattern.cc (game.h game.cc)
	4. Write your main.cc source file with "reversi.h" ("game.h") included.
	5. Compile it.

- Build reversi with tcl embeded
	1. Install latest version of gcc, TCL, Boost. Download cpptcl.
	2. Open reversi.cbp with CodeBlocks or use cbp2make.exe to generate makefile on your own platform.
	3. Change the paths of libraries.
	4. Compile it.

- Build reversi GUI version with tcl embeded
	1. Install latest version of gcc, TCL, Boost, wxwidgets. Download cpptcl.
	2. Open reversi_gui.cbp with CodeBlocks or use cbp2make.exe to generate makefile on your own platform.
	3. Change the paths of libraries.
	4. Compile it.

- Build reversi python GUI version (apparently there's no need to embed tcl anymore)
	1. Install latest version of gcc, python3, swig, wxpython.
	2. Run cmd/shell.
	3. Enter the directory $(REVERSI_PROJECT)/python/
	4. Type following command.  
		`swig -python -c++ -threads reversi_wrap.cxx`  
		`python3 setup.py build_ext --inplace --compiler=mingw32`  
		Note: `--compiler=mingw32` has to changed according to your compiler.  
		If it's built successfully, dynamic link library _reversi.pyd or _reversi.dll or _reversi.so should be generated and main.py can be executed.

### Development

	class board
	│	flip()
	│	search()    
	│	...
	│
	└───class game
	│	│
	│	└───reversi_tcl
	│	│	│
	│	│	└───main.cc (C++ tcl console project)
	│	│	│
	│	│	└───reversi_gui
	│	│		│
	│	│		└───reversi_guiFrame (C++ tcl GUI project)
	│	│
	│	└───reversi_gui.py
	│		│
	│		└───main.py (python GUI project)
	│
	└───main_json (Botzone online project)
