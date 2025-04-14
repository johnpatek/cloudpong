#include <client.hpp>

bool client::app::OnInit()
{
    MyFrame *frame = new MyFrame();
    frame->Show(true);
    return true;
}

int client::app::OnExit()
{
    return 0;
}
