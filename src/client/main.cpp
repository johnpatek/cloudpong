#include <SDL2/SDL.h>
#include <library.hpp>

int main()
{
    std::shared_ptr<cloudpong::library> sdl_library;
    sdl_library = std::make_shared<cloudpong::library>(cloudpong::library_name::sdl2);
    if (sdl_library->call<int>("SDL_Init", SDL_INIT_EVERYTHING) < 0)
    {
        return -1;
    }

    SDL_Window *window;

    window = sdl_library->call<SDL_Window *>("SDL_CreateWindow", "title",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);

    sdl_library->call<void>("SDL_Delay", 5000);

    sdl_library->call<void>("SDL_DestroyWindow", window);

    sdl_library->call<void>("SDL_Quit");
    
    return 0;
}