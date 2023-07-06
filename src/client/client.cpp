#include "client.hpp"

client::client()
{
    int width;
    int height;

    if (_sdl_library->call<int>(
            "SDL_GetCurrentDisplayMode",
            0,
            &width,
            &height) < 0)
    {
        std::string sdl_error(
            _sdl_library->call<const char *>(
                "SDL_GetError"));
        throw std::runtime_error("SDL_GetCurrentDisplayMode: " + sdl_error);
    }

    _window = std::unique_ptr<SDL_Window, std::function<void(SDL_Window *)>>(
        _sdl_library->call<SDL_Window *>(
            "SDL_CreateWindow",
            "pong",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width,
            height,
            0),
        [&](SDL_Window *window)
        {
            if (window != nullptr)
            {
                _sdl_library->call<void>(
                    "SDL_DestroyWindow", window);
            }
        });

    _renderer = std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer *)>>(
        _sdl_library->call<SDL_Renderer *>(
            "SDL_CreateRenderer",
            _window.get(),
            -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC),
        [&](SDL_Renderer *renderer)
        {
            if (renderer != nullptr)
            {
                _sdl_library->call<void>(
                    "SDL_DestroyRenderer",
                    renderer);
            }
        });

    _texture = std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture *)>>(
        _sdl_library->call<SDL_Texture *>(
            "SDL_CreateTexture",
            _renderer.get(),
            SDL_PIXELFORMAT_ABGR32,
            SDL_TEXTUREACCESS_STATIC,
            width,
            height),
        [&](SDL_Texture *texture)
        {
            if (texture != nullptr)
            {
                _sdl_library->call<void>(
                    "SDL_DestroyTexture",
                    texture);
            }
        });
}