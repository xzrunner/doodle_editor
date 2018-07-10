#include "PackageMotorbike.h"
#include "LibraryActorItem.h"

#include "Task/AutomaticMerge/PackageFileIO.h"
#include "Task/Modeling/FileAdapter.h"
#include "Task/Modeling/PackageToBytes.h"

using namespace deditor::motox;

const wxString PackageMotorbike::MERGE_FILE = wxT("D:\\MyProject\\svn 2\\FruitsEditor\\MotoX\\MotoX\\editor\\发布打包\\actor_automatic.txt");
const wxString PackageMotorbike::OUTPUT_FILE = wxT("D:\\MyProject\\svn 2\\FruitsEditor\\MotoX\\MotoX\\editor\\发布打包\\actor.bin");
const wxString PackageMotorbike::ACTOR_FILE = wxT("D:\\MyProject\\svn 2\\FruitsEditor\\MotoX\\MotoX\\editor\\人车_actor.txt");

const wxString PackageMotorbike::IMAGE_FILE_PATH[] = {
	"D:\\MyProject\\svn 2\\FruitsEditor\\MotoX\\MotoX\\editor\\人1.png",
	"D:\\MyProject\\svn 2\\FruitsEditor\\MotoX\\MotoX\\editor\\人2.png",
	"D:\\MyProject\\svn 2\\FruitsEditor\\MotoX\\MotoX\\editor\\人4.png",
	"D:\\MyProject\\svn 2\\FruitsEditor\\MotoX\\MotoX\\editor\\人5.png",
	"D:\\MyProject\\svn 2\\FruitsEditor\\MotoX\\MotoX\\editor\\人3.png",
	"D:\\MyProject\\svn 2\\FruitsEditor\\MotoX\\MotoX\\editor\\人6.png",
	"D:\\MyProject\\svn 2\\FruitsEditor\\MotoX\\MotoX\\editor\\车2.png",
	"D:\\MyProject\\svn 2\\FruitsEditor\\MotoX\\MotoX\\editor\\车3.png",
	"D:\\MyProject\\svn 2\\FruitsEditor\\MotoX\\MotoX\\editor\\车1.png",
	"D:\\MyProject\\svn 2\\FruitsEditor\\MotoX\\MotoX\\editor\\车4.png",
	"D:\\MyProject\\svn 2\\FruitsEditor\\MotoX\\MotoX\\editor\\车5.png"
};

void PackageMotorbike::package(const wxString& modelingPath) const
{
 	std::ofstream fout(OUTPUT_FILE.fn_str(), std::ios::out | std::ios::binary);
	packMergedAndBounding(fout);
	packPlayerInfo(fout);
	packMotorbikeInfo(fout, modelingPath);
 	fout.close();
}

void PackageMotorbike::packMergedAndBounding(std::ofstream& fout) const
{
	deditor::automatic_merge::PackageFileIO package(false);
	package.loadFromTextFile(MERGE_FILE);

	std::vector<wxString> orderPath;
	for (size_t i = 0; i < 11; ++i)
		orderPath.push_back(IMAGE_FILE_PATH[i]);
	package.storeToFileOrder(fout, orderPath);
}

void PackageMotorbike::packPlayerInfo(std::ofstream& fout) const
{
	std::ifstream fin(ACTOR_FILE.fn_str());

	LibraryActorItem params;
	params.loadFromTextFile(fin);

	fin.close();

	// only need body's pos & angle, no 2 wheels
	for (size_t i = 0; i < PARTS_COUNT - 2; ++i)
	{
		const LibraryActorItem::PartDef& part = params.m_parts[i];
		fout.write(reinterpret_cast<const char*>(&part.pos.x), sizeof(float));
		fout.write(reinterpret_cast<const char*>(&part.pos.y), sizeof(float));
		fout.write(reinterpret_cast<const char*>(&part.angle), sizeof(float));
	}
	for (size_t i = 0; i < JOINTS_TYPE_COUNT; ++i)
	{
		const LibraryActorItem::JointDef& joint = params.m_joints[i];

		fout.write(reinterpret_cast<const char*>(&joint.positive_speed), sizeof(float));
		fout.write(reinterpret_cast<const char*>(&joint.negative_speed), sizeof(float));

		fout.write(reinterpret_cast<const char*>(&joint.left_angle_small), sizeof(float));
		fout.write(reinterpret_cast<const char*>(&joint.left_angle_large), sizeof(float));
		fout.write(reinterpret_cast<const char*>(&joint.right_angle_small), sizeof(float));
		fout.write(reinterpret_cast<const char*>(&joint.right_angle_large), sizeof(float));

		fout.write(reinterpret_cast<const char*>(&joint.max_torque), sizeof(float));

		fout.write(reinterpret_cast<const char*>(&joint.anchor.x), sizeof(float));
		fout.write(reinterpret_cast<const char*>(&joint.anchor.y), sizeof(float));
	}
}

void PackageMotorbike::packMotorbikeInfo(std::ofstream& fout,
										 const wxString& modelingPath) const
{
 	deditor::modeling::FileApapter adapter;
 	adapter.resolve(modelingPath);

	std::vector<deditor::modeling::BodyData*> bodies;
	bodies.push_back(adapter.queryBody(wxT("back_wheel")));
	bodies.push_back(adapter.queryBody(wxT("front_wheel")));
	bodies.push_back(adapter.queryBody(wxT("body")));
	bodies.push_back(adapter.queryBody(wxT("back_damping")));
	bodies.push_back(adapter.queryBody(wxT("front_damping")));

	size_t size = bodies.size();
	fout.write(reinterpret_cast<const char*>(&size), sizeof(size_t));
	for (size_t i = 0, n = bodies.size(); i < n; ++i)
		deditor::modeling::PaskageToBytes::packBody(*bodies[i], fout);

	size = 4;
	fout.write(reinterpret_cast<const char*>(&size), sizeof(size_t));
	deditor::modeling::PaskageToBytes::packJoint(*adapter.queryJoint(wxT("front_joint")), fout, bodies);
	deditor::modeling::PaskageToBytes::packJoint(*adapter.queryJoint(wxT("back_joint")), fout, bodies);
	deditor::modeling::PaskageToBytes::packJoint(*adapter.queryJoint(wxT("joint3")), fout, bodies);
	deditor::modeling::PaskageToBytes::packJoint(*adapter.queryJoint(wxT("joint4")), fout, bodies);
}