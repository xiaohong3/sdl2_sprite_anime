#include <iostream>
#include <SDL2/SDL.h>
#include <Texture.h>

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

const int WALKING_ANIME_FRAMES = 4;
SDL_Rect sprite_clips[WALKING_ANIME_FRAMES];
Texture sprite_sheet_texture;
const int CLIP_WIDTH = 64;
const int CLIP_HEIGHT = 205;

bool init();
bool init_sdl();
bool init_sdl_img();
bool create_window();
bool create_renderer();
bool load_media();
void run_game();
void render_clip();
void render(int& current_frame);
void close();

int main()
{
    if (!init())
    {
        return -1;
    }

    if (!load_media())
    {
        return -1;
    }

    run_game();

    close();

    return 0;
}

bool init()
{
    if (!init_sdl())
    {
        return false;
    }

    if (!create_window())
    {
        return false;
    }

    if (!create_renderer())
    {
        return false;
    }

    if (!init_sdl_img())
    {
        return false;
    }
    return true;
}

bool init_sdl()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "SDL could not be initialized. SDL error: " << SDL_GetError() << "\n";
        return false;
    }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        cout << "Warning: Linear texture filtering not enabled!";
    }

    return true;
}

bool create_window()
{
    window = SDL_CreateWindow("SDL2 sprite sheet animation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr)
    {
        cout << "SDL_CreateWindow fails. SDL error: " << SDL_GetError() << "\n";
        return false;
    }
    else
    {
        return true;
    }
}

bool create_renderer()
{
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
        cout << "SDL_CreateRenderer fails. SDL error: " << SDL_GetError() << "\n";
        return false;
    }
    else
    {
        return true;
    }
}

bool init_sdl_img()
{
    if (!IMG_Init(IMG_INIT_PNG))
    {
        cout << "SDL Image can not be initialized. SDL error: " << SDL_GetError() << "\n";
        return false;
    }
    else
    {
        return true;
    }
}

bool load_media()
{
    if (!sprite_sheet_texture.load_from_file("foo.png", renderer))
    {
        cout << "Failed to load png sprite sheet.\n";
        return false;
    }
    else{
        for (int i = 0; i < WALKING_ANIME_FRAMES; ++i)
        {
            sprite_clips[i].x = i * 64;
            sprite_clips[i].y = 0;
            sprite_clips[i].w = CLIP_WIDTH;
            sprite_clips[i].h = CLIP_HEIGHT;
        }
        return true;
    }
}

void run_game()
{
    bool quit = false;
    SDL_Event e;
    int current_frame = 0;
    SDL_Rect dst_rect = {
        SCREEN_WIDTH / 2 - CLIP_WIDTH / 2,
        SCREEN_HEIGHT / 2 - CLIP_HEIGHT / 2,
        CLIP_WIDTH,
        CLIP_HEIGHT
    };

    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_Rect clip_rect = sprite_clips[current_frame / 4];

        SDL_RenderCopy(renderer, sprite_sheet_texture.texture, &clip_rect, &dst_rect);
        SDL_RenderPresent(renderer);

        ++current_frame;

        if ((current_frame / 4) >= WALKING_ANIME_FRAMES)
        {
            current_frame = 0;
        }
    }
}

void close()
{
    sprite_sheet_texture.free();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = nullptr;
    renderer = nullptr;

    IMG_Quit();
    SDL_Quit();
}
