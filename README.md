# sdl2_shootemup_prototype
a shoot em up 2d game hobby project in C using SDL2 library.

used tools:
    
    VScode

    tdm-gcc c-compiler 
    https://github.com/jmeubank tdm-gcc/releases/download/v10.3.0-tdm64-2/tdm64-gcc-10.3.0-2.exe
    
    SDL2-Library
    https://github.com/libsdl-org/SDL/releases/tag/release-2.32.2

    Aseprite
    https://www.aseprite.org/

    Tiled
    https://www.mapeditor.org/


# basic considerations

* horizontal scrolling shoot´em´up game like in the 80s/90s.
* graphics will be stored in BMP-format with a colorkey-mask for the transparency, like in 90s
* no dynamic memory management, e.g. for sprite data-structures, the number of sprites is fixed from the beginning 


# folders

### 0aseprite

    game graphics in aseprite-format


### 0tiled

    Tiled tile-maps and tilesets


### gamedata 

    contains all game data like graphics, music, sounds and level-data

### build

    the compiled and linked code


### src

    the c-source code of the project

# in-game keys

    cursor-keys for player movement
    key-d as primary fire-button
    escape-key to quit


# SDL2-dev libraries sources and path under windows 10/11

    C:\SDL2-2.32.2-dev\

    take a look a the simple Makefile

# Compilation

    mingw32-make
    mingw32-run

