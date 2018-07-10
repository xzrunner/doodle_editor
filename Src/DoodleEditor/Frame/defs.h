#ifndef _DEDITOR_DEFS_H_
#define _DEDITOR_DEFS_H_

#include <Fruits2D/Fruits2D.h>
#include <wx/wx.h>

enum MenuID
{
	ID_TASK_COMMON_BEGIN = 100,
	ID_TASK_SIMPLE_BEGIN = 140,
	ID_TASK_COMPLEX_BEGIN = 180,
	ID_TASK_LEVEL_BEGIN = 200,
	ID_OTHERS_BEGIN = 500,
	ID_PREVIEW = 600
};

static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 480;

//static const float LIGHT_GRAY[] = { 0.8f, 0.8f, 0.8f };
static const f2Colorf LIGHT_GRAY = f2Colorf(0.8f, 0.8f, 0.8f);

static const wxString MANUAL_COMPOSE_TASK_TAG = wxT("manual");
static const wxString COMPRESS_PICTURES_TASK_TAG = wxT("compress");
static const wxString AUTOMATIC_MERGE_TASK_TAG = wxT("automatic");
static const wxString BOUNDARY_EXTRACTION_TASK_TAG = wxT("extract");
static const wxString BINARIES_PACKAGE_TASK_TAG = wxT("package");

static const wxString EDIT_TEXTURE_TASK_TAG = wxT("texture");
static const wxString EDIT_SHAPE_TASK_TAG = wxT("shapes");
static const wxString FILLING_POLYGON_TASK_TAG = wxT("surface");

static const wxString COMBINATION_TASK_TAG = wxT("combination");
static const wxString MODELING_TASK_TAG = wxT("modeling");

static const wxString SKATER_TASK_TAG = wxT("skater");
static const wxString MOTOX_TASK_TAG = wxT("motox");
static const wxString SHOOT_BUBBLE_TASK_TAG = wxT("sbubble");
static const wxString MONSTER_TASK_TAG = wxT("monster");
static const wxString MAGIC_DEFENCE_TASK_TAG = wxT("magic");
static const wxString HILL_CLIMB_TASK_TAG = wxT("climb");

#endif // _DEDITOR_DEFS_H_