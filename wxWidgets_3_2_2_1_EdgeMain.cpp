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

// helper functions
enum wxbuildinfoformat
{
    short_f,
    long_f
};

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f)
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
//*)

BEGIN_EVENT_TABLE(wxWidgets_3_2_2_1_EdgeFrame, wxFrame)
//(*EventTable(wxWidgets_3_2_2_1_EdgeFrame)
//*)
END_EVENT_TABLE()

#define wxUSE_WEBVIEW 1
#include "wx/webview.h"

#include <wx/webview.h>
#include "mssql.h"

std::string CONN_STR = "DRIVER={SQL Server};Server=?;Network Library=DBMSSOCN;Database=?;OLE DB Services=-2;Uid=?;Port=1433;Pwd=?;";

wxWebView *webView;

wxWidgets_3_2_2_1_EdgeFrame::wxWidgets_3_2_2_1_EdgeFrame(wxWindow *parent, wxWindowID id)
{
    //(*Initialize(wxWidgets_3_2_2_1_EdgeFrame)
    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    //*)

    wxString htmlp = "";
    htmlp += "<!DOCTYPE html>";
    htmlp += "<html>";
    htmlp += "<title>INI</title>";
    htmlp += "<body>";

    htmlp += " <textarea style='width:99%;' id='qTXT' name='qTXT' rows='4' cols='50'>SELECT  SN, COMP_R, QUAN_R, LOCAT, ENTRY_DATE FROM MEZANIN;</textarea>";

    htmlp += "<br><button onclick='clicked();'>Exec</button>";
    htmlp += "<script>";

    htmlp += "function clicked() {";
    htmlp += " document.title = 'Refresh:' + document.getElementById('qTXT').value ;";
    htmlp += "}";

    htmlp += "</script>";
    htmlp += "</body>";
    htmlp += "</html>";



    // wxMessageBox(wxString::FromDouble(  wxWebView::IsBackendAvailable(wxWebViewBackendEdge)));

    webView = wxWebView::New(this, ID_WEBW); //, "about:blank", wxDefaultPosition, wxDefaultSize, wxWebViewBackendEdge);
    webView->EnableHistory(false);

    webView->SetPage(htmlp, "");

    Connect(ID_WEBW, wxEVT_WEBVIEW_TITLE_CHANGED, (wxObjectEventFunction)&wxWidgets_3_2_2_1_EdgeFrame::OnwxWebView);
}

wxWidgets_3_2_2_1_EdgeFrame::~wxWidgets_3_2_2_1_EdgeFrame()
{
    //(*Destroy(wxWidgets_3_2_2_1_EdgeFrame)
    //*)
}

void wxWidgets_3_2_2_1_EdgeFrame::OnQuit(wxCommandEvent &event)
{
    Close();
}

wxArrayString tableBodys;
wxArrayString paginator_all;

std::string stylesheet_str;
std::string tableHead;
int currentPage = 0;
#include "stylesheet.h"

wxString paginatorHTML(int CurrentpageNUmber , wxArrayString  PGaLL )
{
    wxString paginators = "";
    int pgCnt = 0;
    int gaper = 8;

    for(auto page : PGaLL)
    {

         if ( (pgCnt >= CurrentpageNUmber - gaper  && pgCnt <= CurrentpageNUmber + gaper)
                                            || pgCnt == 0 || pgCnt == (int)PGaLL.size()-1)
         {
            if (pgCnt == CurrentpageNUmber)
            {
                page.Replace("<button","<button style='background-color:grey;color: white;border-radius: 5px;' ");
            }

            paginators += page;

         }
             if (pgCnt+1 == CurrentpageNUmber - gaper ) paginators +=   "<button> ... </button>";
             if(pgCnt == CurrentpageNUmber + gaper ) paginators +=   "<button> ... </button>";

         pgCnt ++;
    }
    return paginators;
}


void RefreshFromSQL(wxString qTXT)
{
    currentPage = 0;
    tableBodys.Clear();
    paginator_all.Clear();
    stylesheet_str = styleSheet_build();
    tableHead = "<tr>";

    std::vector<std::vector<std::string>> opti_arr = SQL_SERV_VEXT_V2(qTXT.ToStdString(), CONN_STR, true);

    std::string tableBody = "";

    int rowCnt = 0;
    int maxCnt = 0;
    int maxRows = 1000;


    for (auto c : opti_arr[0])
        tableHead += "<th>" + c + "</th>";

    tableHead += "</tr>\n";

    for (auto v : opti_arr)
    {
        tableBody += "<tr>";

        if (rowCnt > 0)
            for (auto c : v)
                tableBody += "<td>" + c + "</td>";

        tableBody += "</tr>\n";

        if (maxCnt == maxRows)
        {
            tableBodys.Add(tableBody);
            tableBody = "";
            maxCnt = 0;
        }
        maxCnt++;
        rowCnt++;
    }

    if (tableBody != "")
    {
        tableBodys.Add(tableBody);

    }

    // Generate Paginator

    int pageCnt = 0 ;
    for(auto tb:tableBodys)
    {
        paginator_all.Add("<button onclick='pageClick(this)'> Page:" + wxString::FromDouble(pageCnt) + "</button>");
        pageCnt++;
    }



    wxString htmlp = "";
    htmlp += "<!DOCTYPE html>";
    htmlp += "<html>";
    htmlp += "<title>INI</title>";
    htmlp += "\n<head>";
    htmlp += stylesheet_str;
    htmlp += "</head>\n";
    htmlp += "<body>\n";

    htmlp += " <textarea id='qTXT' name='qTXT' rows='4' cols='50'>";
    htmlp += qTXT;
    htmlp += "</textarea>";

    htmlp += "<br><button onclick='clicked(this);'>Exec</button>\n";

    htmlp += "<script>\n";

    htmlp += "function clicked() {";
    htmlp += " document.title = 'Refresh:' + document.getElementById('qTXT').value ;  el.innerText ='Loading...';";
    htmlp += "}";

    htmlp += " \n function pageClick(el)\n";
    htmlp += " {document.title = el.innerText + '?' +  document.getElementById('qTXT').value   ; el.innerText ='Loading...'; } \n";
    htmlp += "\n</script>\n";

    htmlp += "\n<div id='table-parent'>";
    htmlp += "\n<table>\n";

    htmlp += "\n</table>\n";

    htmlp += "</div>\n";


    htmlp += "<div class='pagination'>\n" + paginatorHTML(0,paginator_all) + "</div>";
    htmlp += "</body>\n";
    htmlp += "</html>";

    webView->SetPage(htmlp, "");
}

void pageClick(wxString PageNum)
{
    wxString pgNum = PageNum.AfterFirst(':').BeforeFirst('?');
    wxString qTxt = PageNum.AfterFirst('?');

    if (tableBodys.size() == 0)
        return;


    wxString htmlp = "";
    htmlp += "<!DOCTYPE html>";
    htmlp += "<html>";
    htmlp += "<title>INI</title>";
    htmlp += "\n<head>";
    htmlp += stylesheet_str;
    htmlp += "</head>\n";
    htmlp += "<body>\n";

    htmlp += " <textarea id='qTXT' name='qTXT' rows='4' cols='50'>";
    htmlp += qTxt;
    htmlp += "</textarea>";

    htmlp += "<br><button onclick='clicked(this);'>Exec</button>\n";
    htmlp += "<script>\n";

    htmlp += "function clicked(el) {";
    htmlp += " document.title = 'Refresh:' + document.getElementById('qTXT').value ;";
    htmlp += "}";

    htmlp += " \n function pageClick(el)\n";
    htmlp += " {document.title = el.innerText + '?' +  document.getElementById('qTXT').value   ; el.innerText ='Loading...'; } \n";
    htmlp += "\n</script>\n";

    htmlp += "\n<div id='table-parent'>";
    htmlp += "\n<table>\n";
    htmlp += "\n  <thead id='tthead'>\n" + tableHead + "</thead>\n";
    htmlp += "\n  <tbody id='ttbody'>" + tableBodys[wxAtoi(pgNum)] + "</tbody>\n";

    htmlp += "\n</table>\n";
    htmlp += "</div>\n";

    htmlp += "<div class='pagination'>\n" +  paginatorHTML(wxAtoi(pgNum),paginator_all) + "</div>";

    htmlp += "</body>\n";
    htmlp += "</html>";

    webView->SetPage(htmlp, "");

    /*
    // pageClick
    FILE *fp;

    fp = fopen("htmlp.html", "w+");

    fputs(htmlp.c_str(), fp);
    fclose(fp);
*/
}

// Events from HTML -JS - C++

void wxWidgets_3_2_2_1_EdgeFrame::OnwxWebView(wxWebViewEvent &event)
{
    wxString str = event.GetString();

    if (str.Contains("Refresh") == true)
        RefreshFromSQL(str.AfterLast(':'));
    else if (str != "INI")
        pageClick(str);
}


