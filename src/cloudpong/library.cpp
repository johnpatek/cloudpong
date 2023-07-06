#include "cloudpong.hpp"

std::string cloudpong::library::get_library(cloudpong::library_name name)
{
    const std::unordered_map<cloudpong::library_name, std::string> libraries{
        {cloudpong::library_name::sdl2, "libSDL2.so"},
        {cloudpong::library_name::gst, "libgstreamer-1.0.so"},
        {cloudpong::library_name::gst_app, "libgstapp-1.0.so"},
        {cloudpong::library_name::gst_rtsp, "libgstrtsp-1.0.so"},
        {cloudpong::library_name::gst_rtsp_server, "libgstrtspserver-1.0.so"},
        {cloudpong::library_name::curl, "libcurl.so.4"},
    };
    std::unordered_map<cloudpong::library_name, std::string>::const_iterator library = libraries.find(name);
    if (library == libraries.cend())
    {
        throw std::runtime_error("invalid library");
    }
    return library->second;
}

cloudpong::library::library(cloudpong::library_name name)
{
    std::string library = cloudpong::library::get_library(name);
    _handle = std::unique_ptr<void, std::function<void(void *)>>(
        dlopen(library.c_str(), RTLD_LAZY),
        [](void *handle)
        {
                if (handle != nullptr)
                {
                    dlclose(handle);
                } });
    if (_handle == nullptr)
    {
        throw std::runtime_error(std::string("failed to load library: ") + std::string(dlerror()));
    }
}

void cloudpong::library::bind_symbol(const std::string &symbol)
{
    void *address;

    if (_handle == nullptr)
    {
        throw std::runtime_error("no handle");
    }

    address = dlsym(_handle.get(), symbol.c_str());
    if (address == nullptr)
    {
        throw std::runtime_error("bad symbol \"" + symbol + "\": " + dlerror());
    }

    _symbols.emplace(symbol, address);
}

cloudpong::sdl2_library::sdl2_library(uint32_t init_flags) : library(library_name::sdl2)
{
    if (call<int>("SDL_Init", SDL_INIT_EVERYTHING) < 0)
    {
        std::string init_error(this->SDL_GetError());
        throw std::runtime_error("sdl2_library: SDL_Init failed: " + init_error);
    }
}

cloudpong::sdl2_library::~sdl2_library()
{
    call<void>("SDL_Quit");
}

const char *cloudpong::sdl2_library::SDL_GetError()
{
    return call<const char *>("SDL_GetError");
}

SDL_Window *cloudpong::sdl2_library::SDL_CreateWindow(
    const char *title,
    int x, int y, int w,
    int h, Uint32 flags)
{
    return call<SDL_Window *>(
        "SDL_CreateWindow",
        title,
        x,
        y,
        w,
        h,
        flags);
}

void cloudpong::sdl2_library::SDL_DestroyWindow(
    SDL_Window *window)
{
    call<void>("SDL_DestroyWindow", window);
}

SDL_Renderer *cloudpong::sdl2_library::SDL_CreateRenderer(
    SDL_Window *window,
    int index, Uint32 flags)
{
    return call<SDL_Renderer *>(
        "SDL_CreateRenderer", 
        window, 
        index, 
        flags);
}