#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

using namespace std;

class Texture
{
    public:
        Texture();
        ~Texture();
        SDL_Texture* texture;
        bool load_from_file(const string& path, SDL_Renderer* renderer);
        void free();
        int get_width();
        int get_height();


    private:
        int width;
        int height;
};

#endif // TEXTURE_H
