# MMP-Raycaster-Maze
These are my project files for the Major Project module at Aberystwyth University.

Raycaster Maze is a video game, developed using C++ and SFML2.5.1, that uses raycasting as its rendering method. Raycasting was adapted from: https://lodev.org/cgtutor/raycasting.html
and
https://github.com/tmsbrg/adventure3d.

Game tasks player with traversing a maze and finding exit. It contains locked doors along with keys, and treasure money bags that add-up to the score.

===
Current version 1.0
==
AI to be implemented,
human vs. human to be implemented,
additional UI to be implemented.



REQUIRED TO RUN:

Currenet version of the setup needs to be adjusted as it doesn't translate to other machines.

mingw32 7.30 32bi\
https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/7.3.0/threads-posix/dwarf/i686-7.3.0-release-posix-dwarf-rt_v5-rev0.7z/download

SFML 2.5.1 32bit\
https://www.sfml-dev.org/files/SFML-2.5.1-windows-gcc-7.3.0-mingw-32-bit.zip

Python 3.10 32bit, CMakeList.txt points where to change values in-code so the game finds Python installation.
https://www.python.org/downloads/windows/

Both links for mingw and sfml are also available from SFML Download site.

SFML .dll files are required to be in the same directory as project's .exe file, also
arial.ttf (font file) is required in the same directory for text displays to work.
