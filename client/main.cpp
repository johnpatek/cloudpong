/*

class MyApp : public wxApp
{
public:
    virtual bool OnInit() override;
    virtual int OnExit() override
    {
        SDL_Quit();
        return wxApp::OnExit();
    }
};

class MyFrame : public wxFrame
{
public:
    MyFrame() : wxFrame(nullptr, wxID_ANY, "wxWidgets Dialog Example")
    {
        wxMessageBox("Hello from wxWidgets!", "Dialog Box", wxOK | wxICON_INFORMATION, this);
        Close(); // Close after showing the dialog
    }
};

bool MyApp::OnInit()
{
    if (!SDL_Init(SDL_INIT_EVENTS | SDL_INIT_JOYSTICK | SDL_INIT_GAMEPAD))
    {
        wxLogError("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }
    return true;
}



int main(int argc, char **argv)
{
    int rc(0);
    wxEntryStart(argc, argv);
    wxTheApp->CallOnInit();

    wxMessageBox("Hello from wxWidgets!", "Dialog Box", wxOK | wxICON_INFORMATION);
    
    rc = wxTheApp->OnExit();
    wxEntryCleanup();

    return rc;
}
*/

#include <client.hpp>

wxIMPLEMENT_APP(client::app);