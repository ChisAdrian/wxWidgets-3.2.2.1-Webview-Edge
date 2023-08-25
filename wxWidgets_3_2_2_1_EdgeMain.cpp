/***************************************************************
 * Name:      wxWidgets_3_2_2_1_EdgeMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Adrian Chis (chis.adrian@gmail.com)
 * Created:   2023-08-24
 * Copyright: Adrian Chis ()
 * License:
 **************************************************************/

#include "wxWidgets_3_2_2_1_EdgeMain.h"
#include <wx/msgdlg.h>


const long wxWidgets_3_2_2_1_EdgeFrame::ID_WEBW = wxNewId();

//(*InternalHeaders(wxWidgets_3_2_2_1_EdgeFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(wxWidgets_3_2_2_1_EdgeFrame)
const long wxWidgets_3_2_2_1_EdgeFrame::idMenuQuit = wxNewId();
const long wxWidgets_3_2_2_1_EdgeFrame::idMenuAbout = wxNewId();
const long wxWidgets_3_2_2_1_EdgeFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxWidgets_3_2_2_1_EdgeFrame,wxFrame)
    //(*EventTable(wxWidgets_3_2_2_1_EdgeFrame)
    //*)
END_EVENT_TABLE()

#define wxUSE_WEBVIEW 1
#include "wx/webview.h"


#include <wx/webview.h>
#include "mssql.h"

std::string CONN_STR = "DRIVER={SQL Server};..................your string ";

 wxWebView *webView;

wxWidgets_3_2_2_1_EdgeFrame::wxWidgets_3_2_2_1_EdgeFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(wxWidgets_3_2_2_1_EdgeFrame)
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;

    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);

    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxWidgets_3_2_2_1_EdgeFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxWidgets_3_2_2_1_EdgeFrame::OnAbout);
    //*)



wxString htmlp = "";

htmlp += "<!DOCTYPE html>";
htmlp += "<html>";
htmlp +=  "<title>INI</title>";
htmlp += "<body>";
htmlp += "<button onclick='clicked();'>Refresh</button>";
htmlp += "<script>";
htmlp += "function clicked() {";
htmlp += " document.title = 'Refresh'";
htmlp += "}";
htmlp += "</script>";
htmlp += "</body>";
htmlp += "</html>";


// wxMessageBox(wxString::FromDouble(  wxWebView::IsBackendAvailable(wxWebViewBackendEdge)));

webView = wxWebView::New(this, ID_WEBW);//, "about:blank", wxDefaultPosition, wxDefaultSize, wxWebViewBackendEdge);
webView->SetPage(htmlp,"");

Connect(ID_WEBW,wxEVT_WEBVIEW_TITLE_CHANGED ,(wxObjectEventFunction)&wxWidgets_3_2_2_1_EdgeFrame::OnwxWebView);

}

wxWidgets_3_2_2_1_EdgeFrame::~wxWidgets_3_2_2_1_EdgeFrame()
{
    //(*Destroy(wxWidgets_3_2_2_1_EdgeFrame)
    //*)
}

void wxWidgets_3_2_2_1_EdgeFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

wxArrayString tableBodys;
wxString paginators;
wxString strylestr;
std::string tableHead;

void RefreshFromSQL()
{

    tableBodys.Clear();
    paginators = "";
    strylestr = "";
    tableHead = "<tr>";

/*
wxString loader = "";

loader += "<!DOCTYPE html>";
loader += "<html>";
loader +=  "<title>INI</title>";
loader += "<body>";
loader += "<label>Loading</label>";

loader += "</body>";
loader += "</html>";

webView->SetPage(loader,"");
*/

std::vector<std::vector<std::string>> opti_arr = SQL_SERV_VEXT_V2("SELECT top 1001 SN, COMP_R, QUAN_R, LOCAT, ENTRY_DATE FROM MEZANIN;", CONN_STR ,true);

std::string tableBody = "";

int rowCnt = 0;
int maxCnt = 0;
int maxRows = 1000;
int pageCnt = 0;

 for(auto c:opti_arr[0])
    tableHead += "<th>" + c + "</th>" ;

tableHead += "</tr>\n";


for(auto v : opti_arr)
{
    tableBody += "<tr>";

    if(rowCnt>0)
        for(auto c:v)
            tableBody += "<td>" + c + "</td>" ;


    tableBody += "</tr>\n";

        if(maxCnt == maxRows)
        {
            tableBodys.Add(tableBody);

                paginators += "<button onclick='pageClick(this)'> Page:" + wxString::FromDouble(pageCnt) + "</button>";

            pageCnt ++;
            tableBody = "";
            maxCnt = 0;
        }

    maxCnt ++;
    rowCnt ++;
}

tableBodys.Add(tableBody);

 strylestr += "\n<style>\n";

strylestr += " thead {\n  ";
strylestr += "    background: white;\n  ";
strylestr += "   position: sticky;\n  ";
strylestr += "   top: 0;";
strylestr += "   box-shadow: 0 2px 2px -1px rgba(0, 0, 0, 0.4);\n  ";
strylestr += " }\n  ";


strylestr += "#table-parent \n  ";
strylestr += "{ \n  ";
strylestr += "  height:85vh; \n  ";
strylestr += "  overflow:scroll; \n  ";
strylestr += "   border-radius :10px; \n  ";
strylestr += "    border: 1px solid grey; \n  ";
strylestr += "    width:99%; \n  ";
strylestr += "} \n  ";
strylestr += " \n  ";
strylestr += "table{ \n  ";
strylestr += " width : 100%; \n  ";
strylestr += " overflow:scroll; \n  ";
strylestr += "} \n  ";
strylestr += " \n  ";
strylestr += " \n  ";
strylestr += "table, td { \n  ";
strylestr += "  border: 1px solid black; \n  ";
strylestr += "  border-collapse: collapse; \n  ";
strylestr += "  word-wrap:break-word; \n  ";
strylestr += "} \n  ";
strylestr += " \n  ";
strylestr += "th{ \n  ";
strylestr += "  background-color:white; \n  ";
strylestr += "  color:black; \n  ";
strylestr += "  font-weight:bold; \n  ";
strylestr += "  border: 1px solid black; \n  ";
strylestr += "  border-collapse: collapse; \n  ";
strylestr += "} \n  ";

strylestr += " .pagination { ";
strylestr += "  display: inline-block; } ";

strylestr += " .pagination button { ";
strylestr += "  color: black;";
strylestr += "  float: left;";
strylestr += "  text-decoration: none; }";

 strylestr += "\n</style>\n";

wxString htmlp = "";
htmlp += "<!DOCTYPE html>";
htmlp += "<html>";
htmlp +=  "<title>INI</title>";
htmlp += "\n<head>";
htmlp +=  strylestr;
htmlp += "</head>\n";
htmlp += "<body>\n";
htmlp += "<button onclick='clicked(this);'>Refresh</button>\n";
htmlp += "<script>\n";
htmlp += "function clicked(el) {";
htmlp += "document.title = 'Refresh' ;  el.innerText ='Loading...'; ";
htmlp += "}";

htmlp += " \n function pageClick(el)\n {document.title = el.innerText} \n";
htmlp += "\n</script>\n";

htmlp += "\n<div id='table-parent'>";
htmlp += "\n<table>\n";


htmlp += "\n</table>\n";


htmlp += "</div>\n";

htmlp += "<div class='pagination'>\n" + paginators + "</div>";
htmlp += "</body>\n";
htmlp += "</html>";

webView->SetPage(htmlp,"");



}



void callfromHtmlPage(wxString PageNum)
{
PageNum.Replace("Page:","");
//wxMessageBox(PageNum);

//wxMessageBox( wxString::FromDouble(tableBodys.size()));

if(tableBodys.size()==0) return;

wxString htmlp = "";
htmlp += "<!DOCTYPE html>";
htmlp += "<html>";
htmlp +=  "<title>INI</title>";
htmlp += "\n<head>";
htmlp +=  strylestr;
htmlp += "</head>\n";
htmlp += "<body>\n";
htmlp += "<button onclick='clicked(this);'>Refresh</button>\n";
htmlp += "<script>\n";
htmlp += "function clicked(el) {";
htmlp += "document.title = 'Refresh';  el.innerText ='Loading...'; ";
htmlp += "}";

htmlp += " \n function pageClick(el)\n {document.title = el.innerText ; el.innerText ='Loading...';} \n";
htmlp += "\n</script>\n";

htmlp += "\n<div id='table-parent'>";
htmlp += "\n<table>\n";
htmlp += "\n  <thead id='tthead'>\n" + tableHead + "</thead>\n";
htmlp += "\n  <tbody id='ttbody'>" + tableBodys[wxAtoi(PageNum) ] + "</tbody>\n";

htmlp += "\n</table>\n";
htmlp += "</div>\n";

htmlp += "<div class='pagination'>\n" +  paginators + "</div>";

htmlp += "</body>\n";
htmlp += "</html>";

webView->SetPage(htmlp,"");
}

void wxWidgets_3_2_2_1_EdgeFrame::OnwxWebView(wxWebViewEvent& event)
{
     wxString str = event.GetString();
     if(str == "Refresh") RefreshFromSQL();
     else if(str != "INI") callfromHtmlPage(str);

}

void wxWidgets_3_2_2_1_EdgeFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void wxWidgets_3_2_2_1_EdgeFrame::OnButton1Click(wxCommandEvent& event)
{
}
