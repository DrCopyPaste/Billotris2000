# Billotris2000
A maybe futile attempt to salvage a thirteen year old throw away tetris clone.

## 2019-12-28 12:15
I just recently rediscovered my old code for this cheap tetris clone from 2006.
The exe files that I have still run, though I have not yet tried to get the IDE running for playing with the source code.
The plan for this is the following:

- get the original code and game from 2006 (i saw 3 different versions, lets see how I would release those)
- setup to be able to build it with a current IDE
- setup project management and issues
- change identifiers and indentation etc. to be consistent
- maybe change default background/ bricks and preview
- sort methods and classes into separate files
- now look on how to improve readability further and simplify code
- add captions for numbers ingame (which score is which where is level display?)
- try upgrading to a current sdl version (2006 version uses  1.2)
- add game mode selection screen and highscore table
- try using real fonts instead of bmp-fonts
- work out bugs (like rotation movement)
- sounds?
- controller/different keyboards?
- multiplayer? (same computer split screen / network)
- setup cross platform builds (azure integration?)

## 2019-12-28 18:03

I originally wanted to recreate the project using the same tools I did back in 2006.
Well, that would have been using devcpp (from https://www.bloodshed.net/devcpp.html) But I stopped trying to get that to work, because I want to migrate this to a more current version (SDL or something else) anyways -
and that I definetely want to do using a modern IDE.

But it turns out, this is even more tedious than I anticipated, I tried to get it to work with VS for a few hours, but last I was stuck on some "unresolved external symbol" errors, what I tried was the following:
- The source code itself is just one main.cpp with everything
- started Visual Studio Installer and installed the c++ workload, crossing fingers that and SDL dev dlls might be enough
- got the development libraries from https://www.libsdl.org/release/SDL-devel-1.2.15-VC.zip @ https://www.libsdl.org/download-1.2.php
- then created a new empty C++ project in Visual Studio
(following https://stackoverflow.com/a/57787026 and http://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/msvsnet2010u/index.php)
- setting additional include and library folders in project configuration for SDL
- setting up linker additional configuration for SDL
- adding legacy_stdio_definitions.lib got me rid of a few errors, maybe I just need more of those legacy definitions, or maybe an older compiler?
(Or just maybe try again using devcpp, maybe you can get a build from 2006 (and packages?))

This is pretty much where I stopped, since I am caught up in other things, I won't be able to give this another shot for a few days or longer.

## 2020-01-04 11:33

Huh seems I am not the only one having those problems, so even with SDL 2 people have problems using Visual Studio, so maybe I should just join them.
So, moved back my expectations:
- now just trying to get a basic SDL 2 init code working in Visual Studio, hopefully this is easier
- and if that works I try to rework the tetris' code to comply with SDL 2 and things will start working magically (right? riiiight?)

clean new sdl project (following https://www.youtube.com/watch?v=MHbLQq47Gdw)
- get dev libs from https://www.libsdl.org/download-2.0.php
- using https://www.libsdl.org/release/SDL2-devel-2.0.10-VC.zip
- i just added one simple main.cpp with SDL initialization code in it
- AND IT BUILDS! nice, now I am just saving this minimal example to this repository and try to "superimpose" my old tetris code on top of that

## 2020-01-04 12:21

I dumped the original code and bmp-sources under original_sources (for anyone still trying to get this to work with SDL 1.2)
Now I am trying to migrate that code with as little changes as possible to work under SDL2.

## 2020-01-05 16:56
- I didn't get as many errors as I expected, seems only a few things critical to me have changed:
- SDL_SetVideoMode
- SDL_UpdateRect
- SDL_GetKeyState
- SDL_SRCCOLORKEY

So using migration guide from https://wiki.libsdl.org/MigrationGuide
- added window variable because screen itself is not a surface anymore
- blitting is still done against all those surfaces and then blitted on top of screen surface
(but then a new screenTexture is updated from that screen surface and the screenTexture is then used to render the screen)
- pass SDL_TRUE instead of SDL_SRCCOLORKEY
- SDL_GetKeyState renamed to SDL_GetKeyboardState
- now need a rendering context
- instead of SDL_UpdateRect/SDL_Flip use SDL_RenderPresent
- and changing back system to console, because that is what is currently used by this code
- it not actually builds and the game it produces looks pretty familiar to me :D

## 2020-01-05 18:44
- moved images to subfolder
- include SDL2.dll into build output folder
- changed code generation ("msvcp140.dll missing" on other machines error)
- SDL2Client now should build right after checkout and be usable without manually copying the dll files over

## 2020-01-07 00:51
Now that the project is building again I can finally try to make it more readable.
There is a lot of dead code though (at least in the comments) and I'll be leaving that in for now...

First I am just adding some indentation and try having a somewhat consistent style of using braces and semicolons...