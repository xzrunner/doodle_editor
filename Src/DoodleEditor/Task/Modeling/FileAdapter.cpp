#include "FileAdapter.h"
#include "FileIO.h"
#include "BodyData.h"
#include "JointData.h"

using namespace deditor::modeling;

FileApapter::~FileApapter()
{
	clear();
}

void FileApapter::resolve(const wxString& filepath)
{
	clear();

	Json::Value value;
	Json::Reader reader;
	std::ifstream fin(filepath.fn_str());
	reader.parse(fin, value);
	fin.close();

	int i = 0;
	Json::Value bodyValue = value["body"][i++];
	while (!bodyValue.isNull()) {
		BodyData* body = FileIO::j2bBody(bodyValue);
		m_nameBodyMap.insert(std::make_pair(body->m_name, body));
		m_bodies.push_back(body);

		bodyValue = value["body"][i++];
	}

	i = 0;
	Json::Value jointValue = value["joint"][i++];
	while (!jointValue.isNull()) {
		JointData* joint = FileIO::j2bJoint(jointValue, m_bodies);
		m_nameJointMap.insert(std::make_pair(joint->m_name, joint));

		jointValue = value["joint"][i++];
	}
}

BodyData* FileApapter::queryBody(size_t index) const
{
	if (index >= 0 && index < m_bodies.size())
		return m_bodies[index];
	else
		return NULL;
}

BodyData* FileApapter::queryBody(const wxString& name) const
{
	std::map<wxString, BodyData*>::const_iterator itr
		= m_nameBodyMap.find(name);
	if (itr != m_nameBodyMap.end())
		return itr->second;
	else
		return NULL;
}

JointData* FileApapter::queryJoint(const wxString& name) const
{
	std::map<wxString, JointData*>::const_iterator itr
		= m_nameJointMap.find(name);
	if (itr != m_nameJointMap.end())
		return itr->second;
	else
		return NULL;
}

void FileApapter::clear()
{
	std::map<wxString, BodyData*>::iterator itr = m_nameBodyMap.begin();
	for ( ; itr != m_nameBodyMap.end(); ++itr)
		delete itr->second;
	m_nameBodyMap.clear();

	std::map<wxString, JointData*>::iterator itr2 = m_nameJointMap.begin();
	for ( ; itr2 != m_nameJointMap.end(); ++itr2)
		delete itr2->second;
	m_nameJointMap.clear();
}