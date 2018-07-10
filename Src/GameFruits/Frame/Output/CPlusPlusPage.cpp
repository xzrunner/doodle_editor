#include "CPlusPlusPage.h"
#include "Dataset/InterimData.h"
#include <wx/notebook.h>
#include <wx/stc/stc.h>

using namespace GAME_FRUITS;
using namespace GAME_FRUITS::OUTPUT;

CPlusPlusPage::CPlusPlusPage(wxWindow* parent)
	: wxPanel(parent)
{
	initTabPages();
}

void CPlusPlusPage::storeToInterimData(InterimData& interim) const
{
//	wxString totText = GetText();
}

void CPlusPlusPage::loadFromInterimData(const InterimData& interim)
{
	m_hFile->SetText(getHeaderCode(interim));

	wxString cppText;
	cppText += getCPPHeaderCode(interim);
	cppText += "\n";
	cppText += getFuncSceneCode(interim);
	cppText += "\n";
	cppText += getFuncInitCode(interim);
	if (!interim.m_buttons.empty())
	{
		cppText += "\n";
		cppText += getFuncCallbackCode(interim);
	}
	m_cppFile->SetText(cppText);
}

void CPlusPlusPage::initTabPages()
{
	m_notebook = new wxNotebook(this, wxID_ANY);

	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	sizer->Add(m_notebook, 1, wxEXPAND);
	SetSizer(sizer);

	m_hFile = new wxStyledTextCtrl(m_notebook);
	m_cppFile = new wxStyledTextCtrl(m_notebook);
	m_notebook->AddPage(m_hFile, wxT("h"));
	m_notebook->AddPage(m_cppFile, wxT("cpp"));
}

wxString CPlusPlusPage::getHeaderCode(const InterimData& interim) const
{
	wxString ret;

	std::string nameUpper(interim.m_sceneName);
	StringTools::toUpper(nameUpper);
	ret += "#ifndef _" + nameUpper + "_SCENE_H_\n";
	ret += "#define _" + nameUpper + "_SCENE_H_\n";
	ret += "\n";
	ret += "#include \"cocos2d.h\"\n";
	ret += "\n";

	std::string className(interim.m_sceneName);
	if (className != "") className[0] = toupper(className[0]);
	ret += "class " + className + " : public cocos2d::CCLayer\n";
	ret += "{\n";
	ret += "public:\n";
	ret += "\n";
	ret += "\tvirtual bool init();\n";
	ret += "\n";
	ret += "\tstatic cocos2d::CCScene* scene();\n";
	ret += "\n";
	if (!interim.m_buttons.empty())
	{
		ret += "\tvoid buttonCallback(CCObject* pSender);\n";
		ret += "\n";
	}
	ret += "\tLAYER_CREATE_FUNC(" + className + ");\n";
	ret += "};\n";

	ret += "\n";
	ret += "#endif // _" + nameUpper + "_SCENE_H_\n";

	return ret;
}

wxString CPlusPlusPage::getCPPHeaderCode(const InterimData& interim) const
{
	wxString ret;
	std::string className(interim.m_sceneName);
	if (className != "") className[0] = toupper(className[0]);
	ret += "#include \"" + className + ".h\"\n";
	ret += "\n";
	ret += "USING_NS_CC;\n";
	ret += "\n";
	return ret;
}

wxString CPlusPlusPage::getFuncSceneCode(const InterimData& interim) const
{
	wxString ret;

	std::string className(interim.m_sceneName);
	if (className != "") className[0] = toupper(className[0]);

	ret += "CCScene* " + className + "::scene()\n";
	ret += "{\n";
	ret += "\tCCScene *scene = CCScene::create();\n";
	ret += "\n";
	ret += "\t" + className + " *layer = " + className + "::create();\n";
	ret += "\n";
	ret += "\tscene->addChild(layer);\n";
	ret += "\n";
	ret += "\treturn scene;\n";
	ret += "}\n";

	return ret;
}

wxString CPlusPlusPage::getFuncInitCode(const InterimData& interim) const
{
	wxString ret;

	std::string className(interim.m_sceneName);
	if (className != "") className[0] = toupper(className[0]);

	ret += "bool " + className + "::init()\n";
	ret += "{\n";

	ret += "\tif (!CCLayer::init())\n";
	ret += "\t{\n";
	ret += "\t\treturn false;\n";
	ret += "\t}\n";

	ret += "\n";
	for (size_t i = 0, n = interim.m_objects.size(); i < n; ++i)
	{
		InterimData::Entry entry = interim.m_objects[i];

		wxString variableName = entry.name;
		if (variableName != "") variableName[0] = tolower(variableName[0]);
		wxString fileName = entry.path.AfterLast('\\');
		wxString x = wxVariant(entry.x),
			y = wxVariant(entry.y);

		ret += "\tCCSprite* " + variableName + " = CCSprite::create(\"" + fileName + "\");\n";
		ret += "\t" + variableName + "->setPosition(ccp(" + x + ", " + y + "));\n";
		ret += "\tthis->addChild(" + variableName + ", 0);\n";
		ret += "\n";
	}

	ret += "\treturn true;\n";

	ret += "}\n";

	return ret;
}

wxString CPlusPlusPage::getFuncCallbackCode(const InterimData& interim) const
{
	wxString ret;

	std::string className(interim.m_sceneName);
	if (className != "") className[0] = toupper(className[0]);

	ret += "void " + className + "::buttonCallback(CCObject* pSender)\n";
	ret += "{\n";
	ret += "\n";
	ret += "}\n";

	return ret;
}