#include <client.hpp>


void client::run(int argc, const char **argv)
{
    std::unique_ptr<client::app> app(new client::app());
    wxApp::SetInstance(app.get()));  // REQUIRED
    wxEntryStart(argc, argv);
    wxTheApp->CallOnInit();
    wxTheApp->OnRun();
    wxTheApp->OnExit();
    wxEntryCleanup();
}
