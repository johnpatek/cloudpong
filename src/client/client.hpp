#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <cloudpong.hpp>

#include <SDL2/SDL.h>

#include <gst/gst.h>
#include <gst/app/app.h>

class client
{
private:
    std::unique_ptr<cloudpong::library> _gstreamer_library;
    std::unique_ptr<cloudpong::library> _gstreamer_app_library;
    std::unique_ptr<cloudpong::library> _sdl_library;

    std::unique_ptr<SDL_Window,std::function<void(SDL_Window*)>> _window;
    std::unique_ptr<SDL_Renderer,std::function<void(SDL_Renderer*)>> _renderer;
    std::unique_ptr<SDL_Texture,std::function<void(SDL_Texture*)>> _texture;
    


public:
    client();
    
    ~client();


};

#endif