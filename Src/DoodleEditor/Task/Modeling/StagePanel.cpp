#include "StagePanel.h"
#include "StageCanvas.h"
#include "BodyData.h"
#include "JointData.h"
#include "FixtureData.h"
#include "Shape.h"

using namespace deditor::modeling;

StagePanel::StagePanel(wxWindow* parent, wxgui::PropertySettingPanel* propertyPanel,
					   wxgui::LibraryPanel* libraryPanel)
	: wxgui::EditPanel(parent)
	, wxgui::SpritesPanelImpl(this, libraryPanel)
{
	m_canvas = new StageCanvas(this);
}

StagePanel::~StagePanel()
{
	clear();
}

void StagePanel::removeSprite(wxgui::ISprite* sprite)
{
	for (size_t i = 0, n = m_bodies.size(); i < n; ++i)
	{
		if (m_bodies[i]->m_sprite == sprite)
		{
			delete m_bodies[i];
			m_bodies.erase(m_bodies.begin() + i);
			break;
		}
	}

	wxgui::SpritesPanelImpl::removeSprite(sprite);
}

void StagePanel::insertSprite(wxgui::ISprite* sprite)
{
	wxgui::SpritesPanelImpl::insertSprite(sprite);
	
	if (sprite->getUserData())
	{
		BodyData* data = static_cast<BodyData*>(sprite->getUserData());
		m_bodies.push_back(data);
	}
	else
	{
		wxString path = wxgui::FilenameTools::getFilePathExceptExtension(sprite->getSymbol().getFilepath());
		wxString polygonPath = path + "_" + wxgui::FileNameParser::getFileTag(wxgui::FileNameParser::e_polyline) + ".txt";
		wxString circlePath = path + "_" + wxgui::FileNameParser::getFileTag(wxgui::FileNameParser::e_circle) + ".txt";
		BodyData* data = new BodyData; 
		if (wxgui::FilenameTools::isExist(polygonPath))
			loadPolygonBody(polygonPath, *data);
		else if (wxgui::FilenameTools::isExist(circlePath))
			loadCircleBody(circlePath, *data);
		else
			assert(0);

		data->m_sprite = sprite;
		sprite->setUserData(data);

		m_bodies.push_back(data);
	}
}

void StagePanel::clear()
{
	wxgui::EditPanel::clear();
	wxgui::SpritesPanelImpl::clear();

	for_each(m_bodies.begin(), m_bodies.end(), DeletePointerFunctor<BodyData>());
	m_bodies.clear();
	for_each(m_joints.begin(), m_joints.end(), DeletePointerFunctor<JointData>());
	m_joints.clear();
}

wxgui::ISprite* StagePanel::querySpriteByPos(const f2Vec2& pos) const
{
	wxgui::ISprite* result = NULL;
	traverseSprites(PointQueryVisitor(pos, &result), wxgui::e_editable, false);
	return result;
}

void StagePanel::querySpritesByAABB(const f2AABB& aabb, std::vector<wxgui::ISprite*>& result) const
{
	traverseSprites(RectQueryVisitor(aabb, result), wxgui::e_editable);
}

JointData* StagePanel::queryJointByPos(const f2Vec2& pos) const
{
	for (size_t i = 0, n = m_joints.size(); i < n; ++i)
		if (m_joints[i]->isContain(pos))
			return m_joints[i];
	return NULL;
}

void StagePanel::removeJoint(JointData* joint)
{
	for (size_t i = 0, n = m_joints.size(); i < n; ++i)
	{
		if (m_joints[i] == joint)
		{
			delete m_joints[i];
			m_joints.erase(m_joints.begin() + i);
			break;
		}
	}
}

void StagePanel::traverseBodies(IVisitor& visitor) const
{
	std::vector<BodyData*>::const_iterator itr = m_bodies.begin();
	for ( ; itr != m_bodies.end(); ++itr)
	{
		bool hasNext;
		visitor.visit(*itr, hasNext);
		if (!hasNext) break;
	}
}

void StagePanel::traverseJoints(IVisitor& visitor) const
{
	std::vector<JointData*>::const_iterator itr = m_joints.begin();
	for ( ; itr != m_joints.end(); ++itr)
	{
		bool hasNext;
		visitor.visit(*itr, hasNext);
		if (!hasNext) break;
	}
}

void StagePanel::loadCircleBody(const wxString& filepath, BodyData& body) const
{
	wxgui::CircleFileAdapter fa;
	fa.load(filepath);

	FixtureData* fixture = new FixtureData;
	fixture->body = &body;
	CircleShape* circle = new CircleShape;
	circle->m_radius = fa.m_width * 0.5f;
	fixture->shape = circle;
	body.m_fixtures.push_back(fixture);
}

void StagePanel::loadPolygonBody(const wxString& filepath, BodyData& body) const
{
	std::vector<wxgui::ChainShape*> chains;
	wxgui::PolylineFileAdapter fileAdapter(chains);
	fileAdapter.load(filepath.c_str());

	for (size_t i = 0, n = chains.size(); i < n; ++i)
	{
		FixtureData* fixture = new FixtureData;
		fixture->body = &body;
		PolygonShape* shape = new PolygonShape;
		shape->m_vertices = chains[i]->getVertices();
		fixture->shape = shape;
		body.m_fixtures.push_back(fixture);
	}

	for_each(chains.begin(), chains.end(), DeletePointerFunctor<wxgui::ChainShape>());
}

//////////////////////////////////////////////////////////////////////////
// class MultiSpritesImpl::PointQueryVisitor
//////////////////////////////////////////////////////////////////////////

StagePanel::PointQueryVisitor::
PointQueryVisitor(const f2Vec2& pos, wxgui::ISprite** pResult)
	: m_pos(pos)
{
	m_pResult = pResult;
	*m_pResult = NULL;
}

void StagePanel::PointQueryVisitor::
visit(IObject* object, bool& bFetchNext)
{
	wxgui::ISprite* sprite = static_cast<wxgui::ISprite*>(object);
	BodyData* data = static_cast<BodyData*>(sprite->getUserData());
	if (data->isContain(m_pos))
	{
		*m_pResult = sprite;
		bFetchNext = false;
	}
	else
	{
		bFetchNext = true;
	}
}

//////////////////////////////////////////////////////////////////////////
// class MultiSpritesImpl::RectQueryVisitor
//////////////////////////////////////////////////////////////////////////

StagePanel::RectQueryVisitor::
RectQueryVisitor(const f2AABB& aabb, std::vector<wxgui::ISprite*>& result)
	: m_aabb(aabb), m_result(result)
{
}

void StagePanel::RectQueryVisitor::
visit(IObject* object, bool& bFetchNext)
{
	wxgui::ISprite* sprite = static_cast<wxgui::ISprite*>(object);
	BodyData* data = static_cast<BodyData*>(sprite->getUserData());
	if (data->isIntersect(m_aabb))
		m_result.push_back(sprite);
	bFetchNext = true;
}
