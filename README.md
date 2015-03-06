Advance Tic Tac Toe

This game uses SDL. https://www.libsdl.org/<br>

To setup in Visual Studio:<br>
Go to Debug > Advance Tic Tac Toe Properties<br>
1) Configuration Properties > VC++ Directories > Include Directories<br>
Add SDL2_image-2.0.0\include<br>
Add SDL2_ttf-2.0.12\include<br>
Add SDL2-2.0.3\include<br>
Add Minkai_Library<br>

2) Configuration Properties > VC++ Directories > Library Directories<br>
Add SDL2_image-2.0.0\lib\x86<br>
Add SDL2_ttf-2.0.12\lib\x86<br>
Add SDL2-2.0.3\lib\x86<br>

3) Configuration Properties > Linker > Input > Additional Dependencies<br>
Add<br>
SDL2.lib<br>
SDL2main.lib<br>
SDL2_ttf.lib<br>
SDL2_image.lib<br>

4) Configuration Properties > Linker > System > Subsystem<br>
Set to Windows<br>

