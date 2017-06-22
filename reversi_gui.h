#ifndef REVERSI_GUI_H
#define REVERSI_GUI_H

#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/textctrl.h>
#include <wx/dcbuffer.h>
#include <wx/dcgraph.h>
#include <wx/graphics.h>
#include <wx/msgdlg.h>
#include <wx/menu.h>
#include <wx/textfile.h>
#include <wx/treectrl.h>

#include "game.h"

#include "cpptcl.h"

using namespace Tcl;

const int bias = 10;
const int num = 8;
const int cell = 50;
const int width = num * cell;
const int cbias = bias + cell / 2;
const int radius = cell / 2 - 5;

extern wxFrame* ptr_frame;
extern wxPanel* ptr_panel;
extern wxTextCtrl* ptr_term;
extern wxTextCtrl* ptr_log;
extern wxTextCtrl* ptr_input;
extern wxTreeCtrl* ptr_book;

extern interpreter* ptr_inter;

class myTreeItemData: public wxTreeItemData{
public:
	myTreeItemData(node*const& _ptr): ptr(_ptr){}
	node* ptr;
};

class game_gui:public game{
public:
	virtual void show();
};

void do_show(wxDC& dc);

void process(const string& str);
void load(const string& path);
void load_book(const string& path);
void load_node(const wxTreeItemId& item, node* ptr);

extern game_gui mygame;

#endif //REVERSI_GUI_H
