#include <stdio.h>
#include  <SDL2/SDL.h>
#include <stdbool.h>

#define WIDTH 900
#define HEIGHT 600
#define START_RADIUS 10

#define Target_FPS 60   // Target frames per second fixing the cpu resource usage

void draw_palette (SDL_Surface *surface, Uint32 *colors, int num_colors) {
    SDL_Rect rect;
    rect.w = WIDTH / num_colors;
    rect.h = 50;
    rect.y = HEIGHT - rect.h;

    for (int i = 0; i < num_colors; i++) {
        rect.x = i * rect.w;
        SDL_FillRect(surface, &rect, colors[i]);
    }
}

void draw_circle(SDL_Surface *surface, int x_center, int y_center, int radius, Uint32 color) {
    SDL_Rect pixel = {0, 0, 1, 1};
    for (int x=x_center - radius; x <= x_center + radius; x++) {
        for (int y=y_center - radius; y <= y_center + radius; y++) {
            int dx = x - x_center;
            int dy = y - y_center;
            if (dx*dx + dy*dy <= radius*radius) {
                pixel.x = x;
                pixel.y = y;
                SDL_FillRect(surface, &pixel, color);
            }
        }
    }

}

void draw_rectangle(SDL_Surface *surface, int x1, int y1, int x2, int y2, Uint32 color) {
    SDL_Rect r;
    if (x2 < x1) { r.x = x2; r.w = x1 - x2; } else { r.x = x1; r.w = x2 - x1; }
    if (y2 < y1) { r.y = y2; r.h = y1 - y2; } else { r.y = y1; r.h = y2 - y1; }
    if (r.w == 0) r.w = 1;
    if (r.h == 0) r.h = 1;
    SDL_FillRect(surface, &r, color);
}

int main() {

    bool done = false;

    SDL_Init(SDL_INIT_VIDEO);        

    SDL_Window *window = SDL_CreateWindow("ultra paint",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH,                          
        HEIGHT,                         
        0
    );

    SDL_Surface *surface = SDL_GetWindowSurface(window);

    float delay_millis = (1.0 / Target_FPS) * 1000;     // Calculate delay in milliseconds

    Uint32 color_palette[] = {
        SDL_MapRGB(surface->format, 255, 0, 0),    // Red
        SDL_MapRGB(surface->format, 0, 255, 0),    // Green
        SDL_MapRGB(surface->format, 0, 0, 255),    // Blue
        SDL_MapRGB(surface->format, 255, 255, 0),  // Yellow
        SDL_MapRGB(surface->format, 255, 165, 0),  // Orange
        SDL_MapRGB(surface->format, 128, 0, 128),  // Purple
        SDL_MapRGB(surface->format, 0, 0, 0),      // Black
        SDL_MapRGB(surface->format, 255, 255, 255) // White
    };
    
    bool draw = false;
    int x, y;
    int radius = START_RADIUS;
    const int min_radius = 1;
    const int max_radius = 200;

    const int palette_height = 50;
    int num_colors = sizeof(color_palette)/sizeof(color_palette[0]);
    int selected_color_index = 0;
    Uint32 selected_color = color_palette[selected_color_index];

    /* Freehand drawing: user draws by clicking and dragging. Shape keys removed. */

    while (!done) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch(event.type)
            {
                case SDL_QUIT:
                    done = true;
                    break;
                case SDL_MOUSEMOTION:
                    x = event.motion.x;
                    y = event.motion.y;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    x = event.button.x;
                    y = event.button.y;
                    /* If click is inside palette area, select color instead of drawing */
                    if (y >= HEIGHT - palette_height) {
                        int pxw = WIDTH / num_colors;
                        int idx = x / pxw;
                        if (idx < 0) idx = 0;
                        if (idx >= num_colors) idx = num_colors - 1;
                        selected_color_index = idx;
                        selected_color = color_palette[selected_color_index];
                    } else {
                        /* Start freehand drawing */
                        draw = true;
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    /* End freehand drawing */
                    draw = false;
                    break;
                case SDL_MOUSEWHEEL:
                    /* Mouse wheel adjusts brush size */
                    radius += event.wheel.y; /* y > 0 scroll up, y < 0 scroll down */
                    if (radius < min_radius) radius = min_radius;
                    if (radius > max_radius) radius = max_radius;
                    break;
            }
        }

        if (draw){
            draw_circle(surface, x, y, radius, selected_color);
        }

        /* Always draw the palette and update the window each frame. This ensures
           `color_palette` is used and avoids the -Wunused-variable warning. */
        draw_palette(surface, color_palette, sizeof(color_palette)/sizeof(color_palette[0]));
        SDL_UpdateWindowSurface(window);
        SDL_Delay((Uint32)delay_millis);
       
    }

    return 0;
}
