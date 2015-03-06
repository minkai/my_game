# my_game
Advance Tic Tac Toe

This game uses SDL.
https://www.libsdl.org/

To setup in Visual Studio:
Go to Debug > Advance Tic Tac Toe Properties
1) Configuration Properties > VC++ Directories > Include Directories
Add SDL2_image-2.0.0\include
Add SDL2_ttf-2.0.12\include
Add SDL2-2.0.3\include
Add Minkai_Library

2) Configuration Properties > VC++ Directories > Library Directories
Add SDL2_image-2.0.0\lib\x86
Add SDL2_ttf-2.0.12\lib\x86
Add SDL2-2.0.3\lib\x86

3) Configuration Properties > Linker > Input > Additional Dependencies
Add
SDL2.lib
SDL2main.lib
SDL2_ttf.lib
SDL2_image.lib

4) Configuration Properties > Linker > System > Subsystem
Set to Windows

