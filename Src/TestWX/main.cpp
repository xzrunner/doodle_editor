#include "main.h"

// #include "simple.h"
// #include "icon.h"
// #include "button.h"
// #include "Communicate.h"
// 
// #include "menu.h"
// #include "toolbar.h"
// 
// #include "absolute.h"
// #include "sizer.h"
// #include "border.h"
// #include "align.h"
// #include "gotoclass.h"
// #include "gridsizer.h"
// #include "flexgridsizer.h"
// 
// #include "button1.h"
// #include "move.h"
// #include "propagate.h"
// #include "Veto.h"
// #include "ident.h"
// 
// #include "Messages.h"
// #include "openfile.h"
// #include "fontdialog.h"
// #include "customdialog.h"
// 
// #include "checkbox.h"
// #include "bitmapbutton.h"
// #include "togglebutton.h"
// #include "staticline.h"
// #include "statictext.h"
// #include "Slider.h"
// #include "Listbox.h"
// #include "Notebook.h"
// #include "scrolledwindow.h"
// 
// #include "textdrop.h"
// 
// #include "line.h"
// #include "text.h"
// #include "point.h"
// #include "pen.h"
// #include "Regions.h"
// #include "gradient.h"
// #include "shapes.h"
// 
// #include "burning.h"
// 
#include "Tetris.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
	// simple

// 	Simple *simple = new Simple(wxT("Simple"));
// 	simple->Show(true);

// 	Icon *icon = new Icon(wxT("Icon"));
// 	icon->Show(true);

// 	Button *btnapp = new Button(wxT("Button"));
// 	btnapp->Show(true);

// 	Communicate *communicate = new Communicate(wxT("Widgets communicate"));
// 	communicate->Show(true);

	// menu & toolbar

// 	SimpleMenu *menu = new SimpleMenu(wxT("Simple Menu"));
// 	menu->Show(true);

// 	SubMenu *smenu = new SubMenu(wxT("Submenu"));
// 	smenu->Show(true);

// 	Toolbar *toolbar = new Toolbar(wxT("Toolbar"));
// 	toolbar->Show(true);

	// layout manager

// 	Absolute *absolute = new Absolute(wxT("Absolute"));
// 	absolute->Show(true);

// 	Sizer *sizer = new Sizer(wxT("Sizer"));
// 	sizer->Show(true);

// 	Border *border = new Border(wxT("Border"));
// 	border->Show(true);

// 	Align *align = new Align(wxT("Align"));
// 	align->Show(true);

// 	GotoClass *gotoclass = new GotoClass(wxT("GotoClass"));
// 	gotoclass->Show(true);

// 	GridSizer *gs = new GridSizer(wxT("GridSizer"));
// 	gs->Show(true);

//	FlexGridSizer *fgs = new FlexGridSizer(wxT("FlexGridSizer"));
//	fgs->Show(true);

	// Event

// 	MyButton *button = new MyButton(wxT("Button"));
// 	button->Show(true);

// 	Move *move = new Move(wxT("Move event"));
// 	move->Show(true);

// 	Propagate *prop = new Propagate(wxT("Propagate"));
// 	prop->Show(true);

// 	Veto *veto = new Veto(wxT("Veto"));
// 	veto->Show(true);

// 	Ident *ident = new Ident(wxT("Identifiers"));
// 	ident->Show(true);

	// Dialogs

// 	Messages *msgs = new Messages(wxT("Messages"));
// 	msgs->Show(true);

// 	Openfile *open = new Openfile(wxT("Openfile"));
// 	open->Show(true);

// 	ChangeFont *change = new ChangeFont(wxT("Change font"));
// 	change->Show(true);

// 	CustomDialog *custom = new CustomDialog(wxT("CustomDialog"));
// 	custom->Show(true);

	// Widgets

// 	CheckBox *cb = new CheckBox(wxT("CheckBox"));
// 	cb->Show(true);

// 	BitmapButton *bb = new BitmapButton(wxT("BitmapButton"));
// 	bb->Show(true);

// 	ToggleButton *button = new ToggleButton(wxT("ToggleButton"));
// 	button->Centre();
// 	button->Show(true);

// 	Staticline *sl = new Staticline(wxT("The Central Europe"));
// 	sl->ShowModal();
// 	sl->Destroy();

// 	StaticText *st = new StaticText(wxT("StaticText"));
// 	st->Show(true);

// 	Slider *slider = new Slider(wxT("Slider"));
// 	slider->Show(true);

// 	Listbox *listbox = new Listbox(wxT("Listbox"));
// 	listbox->Show(true);

// 	Notebook *notebook = new Notebook(wxT("Notebook"));
// 	notebook->Show(true);

// 	ScrWindow *sw = new ScrWindow(wxT("ScrolledWindow"));
// 	sw->Show(true);

	// Drag

// 	TextDrop *td = new TextDrop(wxT("TextDrop"));
// 	td->Show(true);

	// DC

// 	Line *line = new Line(wxT("Line"));
// 	line->Show(true);

// 	Text *text = new Text(wxT("Text"));
// 	text->Show(true);

// 	Points *points = new Points(wxT("Points"));
// 	points->Show(true);

// 	Pen *pen = new Pen(wxT("Pen"));
// 	pen->Show(true);

// 	Regions *regions = new Regions(wxT("Regions"));
// 	regions->Show(true);

// 	Gradient *grad = new Gradient(wxT("Gradient"));
// 	grad->Show(true);

// 	Shapes *shapes = new Shapes(wxT("Shapes"));
// 	shapes->Show(true);

	// Custom widget

// 	Burning *burning = new Burning(wxT("The Burning Widget"));
// 	burning->Show(true);

	// Tetris

	srand(time(NULL));
	Tetris *tetris = new Tetris(wxT("Tetris"));
	tetris->Centre();
	tetris->Show(true);

	return true;
}