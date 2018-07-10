#include "Common/ComposeImg/Control.h"
#include "Common/ExtractEdge/Control.h"
#include "Common/FillColor/Control.h"

#include "Texture/Merge/Control.h"

#include "Special/Chessboard/Control.h"
#include "Special/Monster/Control.h"
#include "Special/Skater/Control.h"

#include "MotoX/Level/Control.h"
#include "MotoX/Joint/Control.h"
#include "MotoX/Package/Control.h"

#include "Test/Basketball/Control.h"
#include "Test/Rendering/Control.h"
#include "Test/SimulateCloth/Control.h"

#include "SoftRender/Control.h"

using namespace FEDITOR;

TaskEntry g_taskEntries[] =
{
	{ "Common ", NULL },
	{ "Compose Picture", COMPOSE_IMG::Control::Create },
	{ "Extract Edge", EXTRACT_EDGE::Control::Create },
	{ "Fill Color", FILL_COLOR::Control::Create },
	{ "Texture ", NULL },
	{ "Merge", TEXTURE_MERGE::Control::Create },
	{ "Special ", NULL },
	{ "Chessboard", CHESSBOARD::Control::Create },
	{ "Monster", MONSTER::Control::Create },
	{ "Skater", SKATER::Control::Create },
	{ "MotoX ", NULL },
	{ "Map Level", MOTOX::LEVEL::Control::Create },
	{ "Motion Joint", MOTOX::JOINT::Control::Create },
	{ "Package", MOTOX::PACKAGE::Control::Create },
	{ "Test ", NULL },
	{ "Basketball", BASKETBALL::Control::Create },
	{ "Rendering", TEST_RENDERING::Control::Create },
	{ "Simulate Cloth", SIMULATE_CLOTH::Control::Create },
	{ "SoftRender", NULL },
	{ "Demo", SOFT_RENDER::Control::Create },
	{ NULL, NULL }
};
