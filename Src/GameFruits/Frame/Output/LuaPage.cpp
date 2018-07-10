#include "LuaPage.h"
#include "Dataset/InterimData.h"

using namespace GAME_FRUITS;
using namespace GAME_FRUITS::OUTPUT;

LuaPage::LuaPage(wxWindow* parent)
	: wxStyledTextCtrl(parent)
{
}

void LuaPage::storeToInterimData(InterimData& interim) const
{
	wxMessageBox(wxT("error! not implemented: LuaPage::storeToInterimData"));
	assert(0);
}

void LuaPage::loadFromInterimData(const InterimData& interim)
{
	wxString totText;
	totText += "\n";
	totText += getCreateSceneFuncCode(interim);
	totText += "\n";
	totText += getMainFuncCode(interim);
	SetText(totText);
}

wxString LuaPage::getMainFuncCode(const InterimData& interim) const
{
	wxString ret;
	ret += "-- run\n";
	ret += "local " + interim.m_sceneName + " = CCScene:node()\n";
	ret += "gameScene:addChild(createScene())\n";
	ret += "CCDirector:sharedDirector():runWithScene(gameScene)\n";
	return ret;
}

wxString LuaPage::getCreateSceneFuncCode(const InterimData& interim) const
{
	wxString ret;
	ret += "local function createScene()\n";
	ret += "	local scene = CCLayer:node()\n";
	ret += "\n";
	ret += "	-- add sprites\n";
	for (size_t i = 0, n = interim.m_objects.size(); i < n; ++i)
	{
		InterimData::Entry entry = interim.m_objects[i];

		wxString variableName = entry.name;
		wxString fileName = entry.path.AfterLast('\\');
		wxString x = wxVariant(entry.x),
			y = wxVariant(entry.y);

		ret += "	local " + variableName + " = CCSprite:spriteWithFile(\"" + fileName + "\")\n";
		ret += "	" + variableName + ":setPosition(" + x + ", " + y + ")\n";
		ret += "	scene:addChild(" + variableName + ")\n";
		ret += "\n";
	}
	ret += "	return scene\n";
	ret += "end\n";
	return ret;
}