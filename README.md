# sdl2_shootemup_prototype
a 2d game shoot em up hobby project in C using SDL2 library, fresh at the beginning of development.

Take a look at the WIKI ... for some descriptions


used tools:
    

==> Visual Studio Code

https://code.visualstudio.com


==> TDM-gcc (C-Compiler) 

https://jmeubank.github.io/tdm-gcc/download
    
==> SDL2-Library (Simple DirectMedia Layer)

https://github.com/libsdl-org/SDL/releases/tag/release-2.32.2

==> Aseprite (pixel based graphics/animation tool)

https://www.aseprite.org/


==> Tiled (tile based map-editor tool)

https://www.mapeditor.org/


==> Protracker 2.3d Clone for making the music

https://16-bits.org/pt2.php


# basic considerations

* 2D horizontal scrolling shoot´em´up game like in the 80s/90s.
* graphics will be stored in BMP-format with a colorkey-mask for the transparency, like in 90s
* no dynamic memory management, e.g. for sprite data-structures, the number of sprites is fixed from the beginning 
* no sprite-object creation in memory while playing, deactivating unused sprite-objects, only (simple sprite pooling).


#### most important! have fun and keep all things pragmatic

<br/>

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

    take a look at the simple Makefile

# Compilation

    mingw32-make
    mingw32-make run
    mingw32-make clean
    
