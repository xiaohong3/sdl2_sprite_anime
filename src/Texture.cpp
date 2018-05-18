#include "Texture.h"

Texture::Texture()
{
    texture = nullptr;
    width = 0;
    height = 0;
}

Texture::~Texture()
{
    free();
}

bool Texture::load_from_file(const string& path, SDL_Renderer* renderer)
{
    free();

    if (renderer == nullptr)
    {
        cout << "Renderer can not be null to load file with.\n";
        return false;
    }

    texture = IMG_LoadTexture(renderer, path.c_str());

    if (texture == nullptr)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
        return false;
    }
    else
    {
        SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
        return true;
    }
}

void Texture::free()
{
    if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
        width = 0;
        height = 0;
    }
}

int Texture::get_width()
{
    return width;
}

int Texture::get_height()
{
    return height;
}
