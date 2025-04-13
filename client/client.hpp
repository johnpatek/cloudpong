#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <memory>

#include <SDL3/SDL.h>

#include <wx/wx.h>
#include <wx/msgdlg.h>

namespace client 
{
    class app : public wxApp
    {
    public:
        virtual bool OnInit() override;
        virtual int OnRun() override;
        virtual int OnExit() override;
    private:
        bool _running = false;
    };

    void run(int argc, const char **argv);
}

#endif // CLIENT_HPP