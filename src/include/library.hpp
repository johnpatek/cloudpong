#ifndef CLOUDPONG_LIBRARY_HPP
#define CLOUDPONG_LIBRARY_HPP

#include <functional>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>

#include <dlfcn.h>

// TODO: this might need to be moved out
#include <SDL2/SDL.h>
#include <gst/gst.h>

namespace cloudpong
{
    enum class library_name
    {
        sdl2,
        gst,
        gst_app,
        gst_rtsp,
        gst_rtsp_server,
        curl,
    };

    class library
    {
    private:
        static std::string get_library(library_name name);

        library_name _name;
        std::unique_ptr<void, std::function<void(void *)>> _handle;
        std::unordered_map<std::string, void *> _symbols;

        void bind_symbol(const std::string &symbol);

    public:
        static std::shared_ptr<library> load_sdl2(uint32_t init_flags);
        static std::shared_ptr<library> load_gst(int *argc, char ***argv);
        static std::shared_ptr<library> load_gst_app();
        static std::shared_ptr<library> load_gst_rtsp();
        static std::shared_ptr<library> load_gst_rtsp_server();
        static std::shared_ptr<library> load_curl(long flags);

        library(library_name name);

        library(const library &copy) = delete;

        library(library &&move) = default;

        virtual ~library() = default;

        template <class ResultType, class... Args>
        ResultType call(const std::string &symbol, Args &&...args)
        {
            if (_symbols.find(symbol) == _symbols.end())
            {
                bind_symbol(symbol);
            }

            return reinterpret_cast<ResultType (*)(Args...)>(_symbols.at(symbol))(args...);
        }
    };

    class sdl2_library : public library
    {
    public:
        sdl2_library(uint32_t init_flags);
        virtual ~sdl2_library();

        const char *SDL_GetError();

        SDL_Window *SDL_CreateWindow(
            const char *title,
            int x, int y, int w,
            int h, Uint32 flags);

        void SDL_DestroyWindow(
            SDL_Window *window);

        SDL_Renderer *SDL_CreateRenderer(
            SDL_Window *window,
            int index, Uint32 flags);
    };

}

#endif