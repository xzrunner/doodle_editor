#include "AEPackageImpl.h"
#include "LibraryActorItem.h"

#include <Fruits2D/Fruits2D.h>

using namespace deditor::motox;

AEPackageImpl::AEPackageImpl(const LibraryActorItem& params)
	: m_params(params)
	, m_imgsPackage(true)
{
}

void AEPackageImpl::loadFromTextFile(const wxString& filepath)
{
	m_imgsPackage.loadFromTextFile(filepath);
}

void AEPackageImpl::storeToBinaryFile(const wxString& filepath) const
{
	std::ofstream fout(filepath.fn_str(), std::ios::out | std::ios::binary);
	m_imgsPackage.storeToFile(fout);
	storeActorInfo(fout);
	fout.close();
}

void AEPackageImpl::storeActorInfo(std::ofstream& fout) const
{
	for (size_t i = 0; i < PARTS_COUNT; ++i)
	{
		const LibraryActorItem::PartDef& part = m_params.m_parts[i];
		fout.write(reinterpret_cast<const char*>(&part.pos.x), sizeof(float));
		fout.write(reinterpret_cast<const char*>(&part.pos.y), sizeof(float));
		fout.write(reinterpret_cast<const char*>(&part.angle), sizeof(float));
	}
	for (size_t i = 0; i < JOINTS_TYPE_COUNT; ++i)
	{
		const LibraryActorItem::JointDef& joint = m_params.m_joints[i];

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