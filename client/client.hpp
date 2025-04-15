#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <fstream>
#include <memory>
#include <sstream>
#include <thread>

#include <SDL3/SDL.h>

#include <wx/wx.h>
#include <wx/msgdlg.h>
#include <wx/webview.h>
#include <wx/uri.h>

namespace client
{
    class MyFrame : public wxFrame
    {
    public:
        MyFrame() : wxFrame(nullptr, wxID_ANY, "Input Collection Example", wxDefaultPosition, wxSize(600, 400))
        {
            wxWebView *webView = wxWebView::New(this, wxID_ANY, "", wxDefaultPosition, GetSize(), wxWebViewBackendEdge);
            if(!webView)
            {
                wxMessageBox("Failed to create web view", "Error", wxOK | wxICON_ERROR);
                return;
            }
            
            webView->Bind(wxEVT_WEBVIEW_NAVIGATING, &MyFrame::OnWebEvent, this);
            auto sizer = new wxBoxSizer(wxVERTICAL);
            sizer->Add(webView, 1, wxEXPAND);
            SetSizer(sizer);
            wxMessageBox("Hello from wxWidgets!", "Dialog Box", wxOK | wxICON_INFORMATION);
        }

    private:
        void OnWebEvent(wxWebViewEvent &event)
        {
            std::ofstream log("log.txt", std::ios::app);
            wxString url = event.GetURL();
            log << "URL: " << url.ToStdString() << std::endl;

            if (url.StartsWith("event://submit/"))
            {
                wxString encoded = url.Mid(strlen("event://submit/"));
                wxString decoded = wxURI::Unescape(encoded);
                
                event.Veto(); // Stop navigation
            }
        }

        wxWebView *webView;
    };

    class app : public wxApp
    {
    public:
        virtual bool OnInit() override;
        virtual int OnExit() override;
    private:
        std::stringstream _error;
        bool _running = false;
    };
}

#endif // CLIENT_HPP