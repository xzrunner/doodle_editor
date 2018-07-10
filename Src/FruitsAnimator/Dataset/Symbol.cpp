#include "Symbol.h"
#include "Mesh.h"
#include "PartSkeleton.h"

#include <SOIL/SOIL.h>
#include <SOIL/stb_image_write.h>

using namespace FRUITS_ANIMATOR;

Symbol::Symbol()
{
	m_pixelData = NULL;
	m_mesh = NULL;
	m_skeleton = NULL;
	m_skeletonBody = NULL;
}

Symbol::Symbol(const wxString& filepath)
	: wxgui::Symbol(filepath)
{
 	m_pixelData = new wxgui::RawPixels;
	m_pixelData->loadFromFile(m_filepath.c_str());

	m_mesh = NULL;
	m_skeleton = NULL;
	m_skeletonBody = NULL;
}

Symbol::~Symbol()
{
	clear();
}

void Symbol::loadFromTextFile(std::ifstream& fin)
{
	clear();

	wxgui::Symbol::loadFromTextFile(fin);
	m_pixelData = new wxgui::RawPixels;
	reloadResources();

	std::string flag;
	fin >> flag;
	if (flag == "mesh")
	{
		m_mesh = new Mesh(m_width, m_height);
		m_mesh->loadFromTextFile(fin);
	}

	fin >> flag;
	if (flag == "part_skeleton")
	{
		m_skeleton = new PartSkeleton(m_width, m_height);
		m_skeleton->loadFromTextFile(fin);
	}

	fin >> flag;
	if (flag == "whole_skeleton")
	{
		m_skeletonBody = new WholeSkeleton::Body(this);
		m_skeletonBody->loadFromTextFile(fin);
	}
}

void Symbol::storeToTextFile(std::ofstream& fout) const
{
	wxgui::Symbol::storeToTextFile(fout);

	if (m_mesh)
	{
		fout << "mesh" << '\n';
		m_mesh->storeToTextFile(fout);
	}
	else
	{
		fout << "no_mesh" << '\n';
	}

	if (m_skeleton)
	{
		fout << "part_skeleton" << '\n';
		m_skeleton->storeToTextFile(fout);
	}
	else
	{
		fout << "no_part_skeleton" << '\n';
	}

	if (m_skeletonBody)
	{
		fout << "whole_skeleton" << '\n';
		m_skeletonBody->storeToTextFile(fout);
	}
	else
	{
		fout << "no_whole_skeleton" << '\n';
	}
}
 
// void Symbol::loadFromModifiedData()
// {
// 	m_textureID = m_pixelData->storeToTexture(m_textureID);
// 	m_pixelData->getSize(m_width, m_height);
// 
// 	wxBitmap* init = BmpContainer::getBitmap(m_filepath);
// 	if (m_bitmap != init) delete m_bitmap;
// 	unsigned char* data = (unsigned char*)malloc(m_width * m_height * 3);
// 	int iFrom = 0, iTo = 0;
// 	for (int i = 0; i < m_height; ++i)
// 		for (int j = 0; j < m_width; ++j)
// 		{
// 			for (int k = 0; k < 4; ++k)
// 			{
// 				data[iTo++] = m_pixelData->getPixelData()[iFrom++];
// 				if (k == 3) --iTo;
// 			}
// 		}
// //	wxImage img(m_width, m_height, m_pixelData->getPixelData());
// 	wxImage img(m_width, m_height, data);
// 	m_bitmap = new wxBitmap(img);
// }

void Symbol::replaceBySelectedPixels(const wxgui::RawPixels::PixelBuf& selected)
{
	m_pixelData->replaceBySelected(selected);

	const unsigned char* buffer = m_pixelData->getPixelData();
	m_pixelData->getSize(m_width, m_height);
	int channels = m_pixelData->getChannels();

//	glDeleteTextures(1, &m_textureID);
// 	m_textureID = SOIL_internal_create_OGL_texture(buffer, m_width, m_height, channels,
// 		++m_textureID, 0/*SOIL_FLAG_INVERT_Y*/, GL_TEXTURE_2D, GL_TEXTURE_2D, GL_MAX_TEXTURE_SIZE);

//	m_textureID = SOIL_create_OGL_texture(buffer, m_width, m_height, channels, ++m_textureID, SOIL_FLAG_INVERT_Y);

	stbi_write_png("D://zz.png", m_width, m_height, channels, buffer, 0);
	m_textureID = SOIL_load_OGL_texture
		(
		"D://zz.png",
		SOIL_LOAD_AUTO,
		++m_textureID,
		SOIL_FLAG_INVERT_Y
		);
}

wxgui::RawPixels* Symbol::getRawPixels()
{
	return m_pixelData;
}

Mesh* Symbol::getMesh()
{
	return m_mesh;
}

Mesh* Symbol::createMesh()
{
	if (!m_mesh)
		m_mesh = new Mesh(m_width, m_height);
	return m_mesh;
}

PartSkeleton* Symbol::getSkeleton()
{
	return m_skeleton;
}

PartSkeleton* Symbol::createSkeleton()
{
	if (!m_skeleton)
		m_skeleton = new PartSkeleton(m_width, m_height);
	return m_skeleton;
}

WholeSkeleton::Body* Symbol::getSkeletonBody()
{
	return m_skeletonBody;
}

WholeSkeleton::Body* Symbol::createSkeletonBody()
{
	if (!m_skeletonBody)
		m_skeletonBody = new WholeSkeleton::Body(this);
	return m_skeletonBody;
}

void Symbol::clear()
{
	delete m_pixelData, m_pixelData = NULL;
	delete m_mesh, m_mesh = NULL;
	delete m_skeleton, m_skeleton = NULL;
	delete m_skeletonBody, m_skeletonBody = NULL;
}