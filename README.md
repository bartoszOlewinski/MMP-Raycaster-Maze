# MMP-Raycaster-Maze
![Raycaster Maze](clion_project/resources/textures/icon.png)

These are my project files for the Major Project module at Aberystwyth University.

Raycaster Maze is a video game, developed using C++14 and SFML2.5.1, that uses raycasting as its rendering method. Raycasting was adapted from: https://lodev.org/cgtutor/raycasting.html
and
https://github.com/tmsbrg/adventure3d.

Game tasks player with traversing a maze and finding exit. It contains locked doors along with keys, and treasure money bags that add-up to the score.

## Current version 1.0.1
### Latest Fixes:
- Fixed ceiling and floor colouring bug
- Fixed texture misalignment rendering


### To be implemented:
- [ ] AI,
- [ ] human vs. human,
- [ ] additional UI.

## REQUIRED TO RUN:
Download latest [raycaster_maze.zip](https://github.com/bartoszOlewinski/MMP-Raycaster-Maze/releases).

- Install in default path [Python 3.10 32bit](https://www.python.org/downloads/windows/)

for Windows based machine, following environment paths must be set up:
- PYTHONHOME - this is python's installation directory


## REQUIRED TO COMPILE:
Steps regarding Python from **REQUIRED TO RUN** section as well as:

- PYTHONPATH - this is project's **torch** directory

- [mingw32 7.30 32bit](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/7.3.0/threads-posix/dwarf/i686-7.3.0-release-posix-dwarf-rt_v5-rev0.7z/download)

- [SFML 2.5.1 32bit](https://www.sfml-dev.org/files/SFML-2.5.1-windows-gcc-7.3.0-mingw-32-bit.zip)

_Both links for mingw and sfml are also available from SFML Download site_

- **SFML .dll** files are required to be in the same directory as project's .exe file
- **arial.ttf** (font file) is required in the same directory for text displays to work.
- **Python310.dll** file is required in the same directory as .exe file.
- Mingw32 compiler .dll files are required, copy them from **mingw32/bin** directory.

