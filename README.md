**Classic Paint**

Description:
Classic Paint is a compact, minimal paint application built with SDL2 and C. It demonstrates basic drawing interactions: selecting colors from a palette, drawing freehand with a variable brush size, and simple live rendering to an SDL window. The project is intended as a learning/demo tool and a starting point for adding features like undo, saving, or a GUI.

Features:
- Click a color from the bottom palette to select it.
- Left-click and drag to draw freehand using the selected color.
- Adjust brush size with the mouse wheel (scroll up/down).

**Prerequisites**
- C compiler (GCC/clang) and build tools.
- SDL2 development libraries (the `sdl2-config` helper should be available).

Install SDL2 (examples):
- Debian / Ubuntu:
  ```bash
  sudo apt update
  sudo apt install build-essential libsdl2-dev
  ```
- Fedora:
  ```bash
  sudo dnf install gcc make SDL2-devel
  ```
- Arch Linux:
  ```bash
  sudo pacman -S base-devel sdl2
  ```
- macOS (Homebrew):
  ```bash
  brew install sdl2
  ```
- Windows (MSYS2):
  Install MSYS2 and then in the MSYS2 MinGW shell:
  ```bash
  pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-SDL2
  ```

**Build**
From the project folder run:
```bash
gcc -Wall -Wextra -g -o classic_paint classic_paint.c `sdl2-config --cflags --libs`
```

If `sdl2-config` is not on your PATH, install the SDL2 development package for your OS or provide the SDL2 include/lib flags manually.

**Run**
```bash
./classic_paint
```

**Controls**
- Color selection: click a color swatch at the bottom palette.
- Draw: left-click + drag to draw freehand.
- Brush size: mouse wheel up/down to increase/decrease brush radius.
- Quit: close the window.

**Notes**
- To change the palette colors or default brush size, edit `classic_paint.c` and recompile.
- This project is intended as a simple demo; no undo/redo or persistence is provided.

**Files**
- [classic_paint.c](classic_paint.c) — main application source.
- [README.md](README.md) — this file.

Enjoy! Feel free to ask for extra features (on-screen UI, undo, save/load).