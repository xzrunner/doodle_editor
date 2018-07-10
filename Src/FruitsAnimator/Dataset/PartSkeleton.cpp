#include "PartSkeleton.h"
#include "Tools/Render.h"

using namespace FRUITS_ANIMATOR;

const float PartSkeleton::JOINT_RADIUS = 1.0f;
const float PartSkeleton::NODE_RADIUS = 0.5f;
const float PartSkeleton::WIDTH_LENGTH_RATIO = 0.1f;

PartSkeleton::PartSkeleton(float width, float height)
{
	m_halfWidth = width * 0.5f;
	m_halfHeight = height * 0.5f;
}

PartSkeleton::PartSkeleton(const PartSkeleton& skeleton)
{
	m_halfWidth = skeleton.m_halfWidth;
	m_halfHeight = skeleton.m_halfHeight;

	PartSkeleton::Joint* last = NULL;
 	for (size_t i = 0, n = skeleton.m_joints.size(); i < n; ++i)
 	{
		PartSkeleton::Joint* sJoint = skeleton.m_joints[i];
		PartSkeleton::Joint* dJoint = new PartSkeleton::Joint(*sJoint);

		if (last && last->m_to)
		{
			last->m_to->m_end = dJoint;
			dJoint->m_from = last->m_to;
		}
		if (sJoint->m_to)
		{
			Bone* bone = new PartSkeleton::Bone(*sJoint->m_to);
			bone->m_start = dJoint;
			dJoint->m_to = bone;
		}

		last = dJoint;
		m_joints.push_back(dJoint);
 	}
}

PartSkeleton::~PartSkeleton()
{
	clear();
}

PartSkeleton* PartSkeleton::clone()
{
	return new PartSkeleton(*this);
}

void PartSkeleton::loadFromTextFile(std::ifstream& fin)
{
	clear();

	size_t size;
	std::string flag;
	fin >> flag >> size;
	PartSkeleton::Joint* last = NULL;
	for (size_t i = 0; i < size; ++i)
	{
		Joint* curr = new Joint;
		curr->loadFromTextFile(fin);

		if (last && last->m_to)
		{
			last->m_to->m_end = curr;
			curr->m_from = last->m_to;
		}
		if (i != size - 1)
		{
			Bone* bone = new Bone;
			bone->loadFromTextFile(fin);
			bone->m_start = curr;
			curr->m_to = bone;
		}

		last = curr;
		m_joints.push_back(curr);
	}
}

void PartSkeleton::storeToTextFile(std::ofstream& fout) const
{
	fout << "joints " << m_joints.size() << '\n';
	for (size_t i = 0, n = m_joints.size(); i < n; ++i)
	{
		Joint* joint = m_joints[i];
		joint->storeToTextFile(fout);
		fout << '\n';
		assert(i != m_joints.size() - 1 && joint->m_to
			|| i == m_joints.size() - 1 && !joint->m_to);
		if (joint->m_to) 
		{
			joint->m_to->storeToTextFile(fout);
			fout << '\n';
		}
	}
}

void PartSkeleton::pushJoint(const f2Vec2& pos)
{
	m_joints.push_back(new Joint(pos, m_halfWidth, m_halfHeight));

	if (m_joints.size() > 1)
	{
		PartSkeleton::Joint *start = m_joints[m_joints.size() - 2],
			*end = m_joints[m_joints.size() - 1];
		float len = f2Math::getDistance(start->projCoords, end->projCoords);
		PartSkeleton::Bone* bone = new PartSkeleton::Bone(start, end, len, m_halfWidth, m_halfHeight);
		start->m_to = bone;
		end->m_from = bone;
		end->initNodesLocalCoords(len);
		if (m_joints.size() == 2) start->initNodesLocalCoords(len);

		if (m_joints.size() > 2)
		{
			Joint* last = m_joints[m_joints.size() - 2];
			f2Vec2 pLeft, pRight;
			last->getNodesPos(pLeft, pRight);
			last->m_left.initCoords(pLeft, m_halfWidth, m_halfHeight);
			last->m_right.initCoords(pRight, m_halfWidth, m_halfHeight);
		}
	}
}

void PartSkeleton::popJoint()
{
	if (m_joints.size() > 2)
	{
		PartSkeleton::Joint* last = m_joints[m_joints.size() - 2];
		delete last->m_to->m_end;
		delete last->m_to, last->m_to = NULL;
		m_joints.pop_back();
	}
}

f2Vec2 PartSkeleton::topJoint() const
{
	if (m_joints.empty())
	{
		f2Vec2 p;
		p.setInvalid();
		return p;
	}
	else
	{
		return m_joints[m_joints.size() - 1]->projCoords;
	}
}

PartSkeleton::Joint* PartSkeleton::queryJointByPos(const f2Vec2& pos)
{
	PartSkeleton::Joint* nearest = NULL;
	float nearestDis = FLOAT_MAX;

	for (size_t i = 0, n = m_joints.size(); i < n; ++i)
	{
		float dis = f2Math::getDistance(pos, m_joints[i]->projCoords);
		if (dis < nearestDis) 
		{
			nearest = m_joints[i];
			nearestDis = dis;
		}
	}

	return nearestDis < JOINT_RADIUS ? nearest : NULL;
}

PartSkeleton::Node* PartSkeleton::queryNodeByPos(const f2Vec2& pos)
{
	PartSkeleton::Node* nearest = NULL;
	float nearestDis = FLOAT_MAX;

	for (size_t i = 0, n = m_joints.size(); i < n; ++i)
	{
		PartSkeleton::Joint* joint = m_joints[i];
		PartSkeleton::Bone* bone = joint->m_to;
		if (!bone) continue;

		float dis;

		f2Vec2 pLeft, pRight;
		bone->getNodesPos(pLeft, pRight);
		dis = f2Math::getDistance(pLeft, pos);
		if (dis < nearestDis)
		{
			nearest = &bone->m_left;
			nearestDis = dis;
		}
		dis = f2Math::getDistance(pRight, pos);
		if (dis < nearestDis)
		{
			nearest = &bone->m_right;
			nearestDis = dis;
		}

		if (i != 0)
		{
			joint->getNodesPos(pLeft, pRight);
			dis = f2Math::getDistance(pLeft, pos);
			if (dis < nearestDis)
			{
				nearest = &joint->m_left;
				nearestDis = dis;
			}
			dis = f2Math::getDistance(pRight, pos);
			if (dis < nearestDis)
			{
				nearest = &joint->m_right;
				nearestDis = dis;
			}
		}
	}

	return nearest;
}

void PartSkeleton::translateJoint(Joint* joint, const f2Vec2& newPos)
{
	joint->initConnectedCoords(newPos, m_halfWidth, m_halfHeight);
}

void PartSkeleton::translateNode(Node* node, const f2Vec2& newPos)
{
	for (size_t i = 0, n = m_joints.size(); i < n; ++i)
	{
		PartSkeleton::Joint* joint = m_joints[i];
		PartSkeleton::Bone* bone = joint->m_to;
		if (!bone) continue;

		f2Vec2 center = bone->getCenter();
		f2Vec2 vector = bone->getVector();
		if (&bone->m_left == node)
		{
			bone->m_left.local = f2Math::transCoordsWorldToLocal(center, vector, newPos);
			bone->m_left.initCoords(newPos, m_halfWidth, m_halfHeight);
		}
		else if (&bone->m_right == node)
		{
			bone->m_right.local = f2Math::transCoordsWorldToLocal(center, vector, newPos);
			bone->m_right.initCoords(newPos, m_halfWidth, m_halfHeight);
		}

		if (i != 0)
		{
			f2Vec2 center = joint->projCoords;
			f2Vec2 vector = (joint->m_from->getVector() + joint->m_to->getVector()) * 0.5f;
			if (&joint->m_left == node)
			{
				joint->m_left.local = f2Math::transCoordsWorldToLocal(center, vector, newPos);
				joint->m_left.initCoords(newPos, m_halfWidth, m_halfHeight);
			}
			else if (&joint->m_right == node)
			{
				joint->m_right.local = f2Math::transCoordsWorldToLocal(center, vector, newPos);
				joint->m_right.initCoords(newPos, m_halfWidth, m_halfHeight);
			}
		}
	}
}

void PartSkeleton::rotateJoint(PartSkeleton::Joint* joint, const f2Vec2& newPos)
{
	if (!joint->m_from) return;

	float oldLen = joint->m_from->getLength();
	const f2Vec2& start = joint->m_from->m_start->projCoords;
	float newLen = f2Math::getDistance(start, newPos);
	f2Vec2 dest = start + (newPos - start) * oldLen / newLen;

	f2Vec2 offset = dest - joint->projCoords;
	while (true)
	{
		joint->projCoords += offset;
		if (joint->m_to) joint = joint->m_to->m_end;
		else break;
	}
}

void PartSkeleton::onDraw() const
{
	// Bones
	glLineWidth(2.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	for (size_t i = 0, n = m_joints.size(); i < n; ++i)
	{
		PartSkeleton::Joint* joint = m_joints[i];
		if (joint->m_to)
		{
			PartSkeleton::Bone* bone = joint->m_to;
			const f2Vec2& s = bone->m_start->projCoords,
				&e = bone->m_end->projCoords;

			f2Vec2 offset = (e - s) * WIDTH_LENGTH_RATIO;
			f2Vec2 pLeft = s + f2Math::rotateVectorRightAngle(offset, true),
				pRight = s + f2Math::rotateVectorRightAngle(offset, false);
			glBegin(GL_LINE_LOOP);
				glVertex2f(pLeft.x, pLeft.y);
				glVertex2f(pRight.x, pRight.y);
				glVertex2f(e.x, e.y);
			glEnd();
		}
	}
	glLineWidth(1.0f);

	// Joints
	glColor3f(0.0f, 1.0f, 0.0f);
	for (size_t i = 0, n = m_joints.size(); i < n; ++i)
	{
		Render::drawPos(m_joints[i]->projCoords, JOINT_RADIUS);
	}

	// Nodes
	glColor3f(0.0f, 0.0f, 1.0f);
	for (size_t i = 0, n = m_joints.size(); i < n; ++i)
	{
		PartSkeleton::Joint* joint = m_joints[i];
		PartSkeleton::Bone* bone = joint->m_to;
		if (!bone) continue;

		f2Vec2 pLeft, pRight;
		bone->getNodesPos(pLeft, pRight);
		Render::drawPos(pLeft, NODE_RADIUS);
		Render::drawPos(pRight, NODE_RADIUS);

		if (i != 0)
		{
			joint->getNodesPos(pLeft, pRight);
			Render::drawPos(pLeft, NODE_RADIUS);
			Render::drawPos(pRight, NODE_RADIUS);
		}
	}

	// Meshes
	glColor3f(0.0f, 0.6f, 0.8f);
	for (size_t i = 0, n = m_joints.size(); i < n; ++i)
	{
		PartSkeleton::Joint* joint = m_joints[i];
		PartSkeleton::Bone* bone = joint->m_to;
		if (!bone) continue;

		f2Vec2 pLeft, pRight;
		bone->getNodesPos(pLeft, pRight);
		drawTriangle(bone->m_start->projCoords, bone->m_end->projCoords, pLeft);
		drawTriangle(bone->m_start->projCoords, bone->m_end->projCoords, pRight);

		if (i != 0)
		{
			PartSkeleton::Bone* fBone = joint->m_from;

			f2Vec2 fbLeft, fbRight;
			fBone->getNodesPos(fbLeft, fbRight);

			f2Vec2 nLeft, nRight;
			joint->getNodesPos(nLeft, nRight);

			drawTriangle(fbLeft, joint->projCoords, nLeft);
			drawTriangle(nLeft, joint->projCoords, pLeft);
			drawTriangle(fbRight, joint->projCoords, nRight);
			drawTriangle(nRight, joint->projCoords, pRight);
		}
	}
}

void PartSkeleton::drawMeshes() const
{
	for (size_t i = 0, n = m_joints.size(); i < n; ++i)
	{
		PartSkeleton::Joint* joint = m_joints[i];
		PartSkeleton::Bone* bone = joint->m_to;
		if (!bone) continue;

		f2Vec2 pLeft, pRight;
		bone->getNodesPos(pLeft, pRight);
		drawTriangle(bone->m_start->projCoords, bone->m_end->projCoords, pLeft,
			bone->m_start->texCoords, bone->m_end->texCoords, bone->m_left.texCoords);
		drawTriangle(bone->m_start->projCoords, bone->m_end->projCoords, pRight,
			bone->m_start->texCoords, bone->m_end->texCoords, bone->m_right.texCoords);

		if (i != 0)
		{
			PartSkeleton::Bone* fBone = joint->m_from;

			f2Vec2 fbLeft, fbRight;
			fBone->getNodesPos(fbLeft, fbRight);

			f2Vec2 nLeft, nRight;
			joint->getNodesPos(nLeft, nRight);

			drawTriangle(fbLeft, joint->projCoords, nLeft,
				fBone->m_left.texCoords, joint->texCoords, joint->m_left.texCoords);
			drawTriangle(nLeft, joint->projCoords, pLeft, 
				joint->m_left.texCoords, joint->texCoords, bone->m_left.texCoords);
			drawTriangle(fbRight, joint->projCoords, nRight,
				fBone->m_right.texCoords, joint->texCoords, joint->m_right.texCoords);
			drawTriangle(nRight, joint->projCoords, pRight, 
				joint->m_right.texCoords, joint->texCoords, bone->m_right.texCoords);
		}
	}
}

void PartSkeleton::tween(const PartSkeleton& start, const PartSkeleton& end, float process)
{
	for (size_t i = 0, n = m_joints.size(); i < n; ++i)
	{
		f2Vec2 offset = (end.m_joints[i]->projCoords - start.m_joints[i]->projCoords) * process;
		m_joints[i]->projCoords = start.m_joints[i]->projCoords + offset;
	}
}

void PartSkeleton::clear()
{
	for (size_t i = 0, n = m_joints.size(); i < n; ++i)
	{
		if (m_joints[i]->m_to) delete m_joints[i]->m_to;
		delete m_joints[i];
	}
	m_joints.clear();
}

void PartSkeleton::drawTriangle(const f2Vec2& p0, const f2Vec2& p1, const f2Vec2& p2) const
{
	glBegin(GL_LINE_LOOP);
		glVertex2f(p0.x, p0.y);
		glVertex2f(p1.x, p1.y);
		glVertex2f(p2.x, p2.y);
	glEnd();
}

void PartSkeleton::drawTriangle(const f2Vec2& p0, const f2Vec2& p1, const f2Vec2& p2,
							const f2Vec2& c0, const f2Vec2& c1, const f2Vec2& c2) const
{
	glBegin(GL_TRIANGLES);
		glTexCoord2f(c0.x, c0.y);	glVertex2f(p0.x, p0.y);
		glTexCoord2f(c1.x, c1.y);	glVertex2f(p1.x, p1.y);
		glTexCoord2f(c2.x, c2.y);	glVertex2f(p2.x, p2.y);
	glEnd();
}

//////////////////////////////////////////////////////////////////////////
// class PartSkeleton::Node
//////////////////////////////////////////////////////////////////////////

PartSkeleton::Node::Node(const Node& node)
	: MeshNode(node)
{
	local = node.local;
}

void PartSkeleton::Node::loadFromTextFile(std::ifstream& fin)
{
	MeshNode::loadFromTextFile(fin);
	fin >> local;
}

void PartSkeleton::Node::storeToTextFile(std::ofstream& fout) const
{
	MeshNode::storeToTextFile(fout);
	fout << " " << local;
}

//////////////////////////////////////////////////////////////////////////
// class PartSkeleton::Joint
//////////////////////////////////////////////////////////////////////////

PartSkeleton::Joint::Joint()
{
	m_from = m_to = NULL;
}

PartSkeleton::Joint::Joint(const f2Vec2& p, float hWidth, float hHeight)
{
	initCoords(p, hWidth, hHeight);
	m_from = m_to = NULL;
}

PartSkeleton::Joint::Joint(const Joint& joint)
	: MeshNode(joint), m_left(joint.m_left), m_right(joint.m_right)
{
	m_from = m_to = NULL;
}

void PartSkeleton::Joint::loadFromTextFile(std::ifstream& fin)
{
	MeshNode::loadFromTextFile(fin);
	m_left.loadFromTextFile(fin);
	m_right.loadFromTextFile(fin);
}

void PartSkeleton::Joint::storeToTextFile(std::ofstream& fout) const
{
	MeshNode::storeToTextFile(fout);
	fout << " ";
	m_left.storeToTextFile(fout);
	fout << " ";
	m_right.storeToTextFile(fout);
}

void PartSkeleton::Joint::initNodesLocalCoords(float length)
{
	m_left.local.x = m_right.local.y = 0;
	m_left.local.y = length * 0.5f;
	m_right.local.y = - length * 0.5f;
}

void PartSkeleton::Joint::initConnectedCoords(const f2Vec2& pos, float hWidth, float hHeight)
{
	initCoords(pos, hWidth, hHeight);

	if (m_from && m_to)
	{
		f2Vec2 pLeft, pRight;
		getNodesPos(pLeft, pRight);
		m_left.initCoords(pLeft, hWidth, hHeight);
		m_right.initCoords(pRight, hWidth, hHeight);
	}

	if (m_from) m_from->initCoords(hWidth, hHeight, this);
	if (m_to) m_to->initCoords(hWidth, hHeight, this);
}

void PartSkeleton::Joint::getNodesPos(f2Vec2& left, f2Vec2& right) const
{
	f2Vec2 center = projCoords;
	f2Vec2 vector = (m_from->getVector() + m_to->getVector()) * 0.5f;
	left = f2Math::transCoordsLocalToWorld(center, vector, m_left.local);
	right = f2Math::transCoordsLocalToWorld(center, vector, m_right.local);
}

//////////////////////////////////////////////////////////////////////////
// class PartSkeleton::Bone
//////////////////////////////////////////////////////////////////////////

PartSkeleton::Bone::Bone()
{
	m_start = m_end = NULL;
}

PartSkeleton::Bone::Bone(Joint* start, Joint* end, float length, float hWidth, float hHeight)
{
	m_start = start;
	m_end = end;

	initNodesLocalCoords(length);

	f2Vec2 pLeft, pRight;
	getNodesPos(pLeft, pRight);
	m_left.initCoords(pLeft, hWidth, hHeight);
	m_right.initCoords(pRight, hWidth, hHeight);
}

PartSkeleton::Bone::Bone(const Bone& bone)
	: m_left(bone.m_left), m_right(bone.m_right)
{
	m_start = m_end = NULL;
}

void PartSkeleton::Bone::loadFromTextFile(std::ifstream& fin)
{
	m_left.loadFromTextFile(fin);
	m_right.loadFromTextFile(fin);
}

void PartSkeleton::Bone::storeToTextFile(std::ofstream& fout) const
{
	m_left.storeToTextFile(fout);
	fout << '\n';
	m_right.storeToTextFile(fout);
}

float PartSkeleton::Bone::getLength() const
{
	return f2Math::getDistance(m_start->projCoords, m_end->projCoords);
}

f2Vec2 PartSkeleton::Bone::getCenter() const
{
	return (m_start->projCoords + m_end->projCoords) * 0.5f;
}

f2Vec2 PartSkeleton::Bone::getVector() const
{
	return m_end->projCoords - m_start->projCoords;
}

void PartSkeleton::Bone::getNodesPos(f2Vec2& left, f2Vec2& right) const
{
	f2Vec2 center = getCenter();
	f2Vec2 vector = getVector();
	left = f2Math::transCoordsLocalToWorld(center, vector, m_left.local);
	right= f2Math::transCoordsLocalToWorld(center, vector, m_right.local);
}

void PartSkeleton::Bone::initNodesLocalCoords(float length)
{
	m_left.local.x = 0;
	m_left.local.y = length * 0.5f;

	m_right.local.x = 0;
	m_right.local.y = - length * 0.5f;
}

void PartSkeleton::Bone::initCoords(float hWidth, float hHeight, Joint* except)
{
	f2Vec2 pLeft, pRight;
	getNodesPos(pLeft, pRight);
	m_left.initCoords(pLeft, hWidth, hHeight);
	m_right.initCoords(pRight, hWidth, hHeight);

	if (m_start != except && m_start->m_from)
	{
		m_start->getNodesPos(pLeft, pRight);
		m_start->m_left.initCoords(pLeft, hWidth, hHeight);
		m_start->m_right.initCoords(pRight, hWidth, hHeight);
	}
	if (m_end != except && m_end->m_to)
	{
		m_end->getNodesPos(pLeft, pRight);
		m_end->m_left.initCoords(pLeft, hWidth, hHeight);
		m_end->m_right.initCoords(pRight, hWidth, hHeight);
	}
}