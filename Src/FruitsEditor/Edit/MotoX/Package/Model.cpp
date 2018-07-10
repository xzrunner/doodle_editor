#include "Model.h"
#include "Blackboard.h"
#include "Dataset/ChainShape.h"
#include "File/FileNameParser.h"
#include "File/ChainsFileAdapter.h"
#include "File/LoopsFileAdapter.h"
#include "File/CircleFileAdapter.h"
#include "Edit/MotoX/Utility.h"

using namespace FEDITOR;
using namespace FEDITOR::MOTOX::PACKAGE;

Model::Model(const AbstractBlackboard* blackboard)
{
	m_blackboard = static_cast<Blackboard*>(const_cast<AbstractBlackboard*>(blackboard));
}

Model::~Model()
{
}

void Model::handleEvent(const Event& event)
{
	switch (event.getID())
	{
	case Blackboard::e_packTrackChains:
		packTrackChain(event.getInfo(), "track_chains.bin");
		break;
	case Blackboard::e_packActor:
		packActor(event.getInfo(), "actor.bin");
		break;
	}
}

void Model::packTrackChain(const std::string& src, const std::string& dst)
{
	if (!FileNameParser::isType(src, FileNameParser::e_chains)) return;

	ChainsFileAdapter fa;
	fa.load(src);
	
	std::ofstream fout(dst.c_str(), std::ios::out | std::ios::binary);
	if (fout.fail())
		throw IllegalArgumentException("Model::packTrackChain: cannot open file.");

	size_t size = fa.m_chains.size();
	fout.write(reinterpret_cast<const char*>(&size), sizeof(size_t));
	for (size_t i = 0, n = fa.m_chains.size(); i < n; ++i)
	{
		ChainShape* shape = fa.m_chains[i];
		size_t tmp = shape->m_vertices.size();
		fout.write(reinterpret_cast<const char*>(&tmp), sizeof(size_t));
		for (size_t j = 0; j < tmp; ++j)
		{
			f2Vec2 pos = shape->m_vertices[j];
			pos *= 100.0f;
			fout.write(reinterpret_cast<const char*>(&pos.x), sizeof(float));
			fout.write(reinterpret_cast<const char*>(&pos.y), sizeof(float));
		}
	}

	fout.close();
}

void Model::packActor(const std::string& src, const std::string& dst)
{
	std::ifstream finTex("composed_png.txt"), 
		finSrc(src.c_str());
	if (finTex.fail() || finSrc.fail())
		throw IllegalArgumentException("Model::packActor: cannot open file.");

	std::map<std::string, Region*> lookupTable;
	buildTexturesLookupTable(finTex, lookupTable);
	finTex.close();

	std::ofstream fout(dst.c_str(), std::ios::out | std::ios::binary);
	if (fout.fail())
		throw IllegalArgumentException("Model::packActor: cannot open file.");
	storeActorToFile(finSrc, fout, lookupTable);
	finSrc.close();
	fout.close();

	std::map<std::string, Region*>::iterator itr = lookupTable.begin();
	for ( ; itr != lookupTable.end(); ++itr)
		delete itr->second;
	lookupTable.clear();
}

void Model::buildTexturesLookupTable(std::ifstream& fin, std::map<std::string, Region*>& lookup)
{
	size_t size;
	fin >> size;
	for (size_t i = 0; i < size; ++i)
	{
		std::string name;
		Region* region = new Region;
		fin >> name >> region->left >> region->top >> region->width >> region->height;
		lookup.insert(std::make_pair(name, region));
	}
}

void Model::storeActorToFile(std::ifstream& src, std::ofstream& dst, std::map<std::string, Region*>& lookup)
{
	for (size_t i = 0; i < 13; ++i)
	{
		std::string filename;
		float x, y, angle;
		src >> filename >> x >> y >> angle;
		if (i == 3 || i == 5 || i == 7 || i == 9) continue;

		x *= MOTOX::SCALE_PHYSICS_TO_SCREEN;
		y *= MOTOX::SCALE_PHYSICS_TO_SCREEN;

		std::ifstream finShape(filename.c_str());
		std::string imgName;
		finShape >> imgName;
		finShape.close();

		std::map<std::string, Region*>::iterator itr = lookup.find(imgName);
		if (itr == lookup.end())
			throw IllegalStateException("Model::storeActorToFile: not find.");

		dst.write(reinterpret_cast<const char*>(&itr->second->left), sizeof(int));
		dst.write(reinterpret_cast<const char*>(&itr->second->top), sizeof(int));
		dst.write(reinterpret_cast<const char*>(&itr->second->width), sizeof(int));
		dst.write(reinterpret_cast<const char*>(&itr->second->height), sizeof(int));

		if (FileNameParser::isType(filename, FileNameParser::e_loops))
		{
			LoopsFileAdapter lfa;
			lfa.load(filename);

			size_t size = lfa.m_loops.size();
			dst.write(reinterpret_cast<const char*>(&size), sizeof(size_t));
			for (size_t i = 0; i < size; ++i)
			{
				ChainShape* chain = lfa.m_loops[i];
				size_t c = chain->m_vertices.size();
				dst.write(reinterpret_cast<const char*>(&c), sizeof(size_t));
				for (size_t j = 0; j < c; ++j)
				{
					dst.write(reinterpret_cast<const char*>(&chain->m_vertices[j].x), sizeof(float));
					dst.write(reinterpret_cast<const char*>(&chain->m_vertices[j].y), sizeof(float));
				}
			}
		}
		else
		{
			assert(FileNameParser::isType(filename, FileNameParser::e_circle));
			CircleFileAdapter cfa;
			cfa.load(filename);

			dst.write(reinterpret_cast<const char*>(&cfa.m_width), sizeof(int));
		}

		dst.write(reinterpret_cast<const char*>(&x), sizeof(float));
		dst.write(reinterpret_cast<const char*>(&y), sizeof(float));
		dst.write(reinterpret_cast<const char*>(&angle), sizeof(float));
	}
}