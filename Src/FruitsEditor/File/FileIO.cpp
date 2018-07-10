#include "FileIO.h"

using namespace FEDITOR;

void FileIO::readFromFile(std::vector<f2Vec2>& buf, std::ifstream& fin, bool isText/* = true*/, size_t num/* = 0*/)
{
	if (isText)
	{
		size_t count = 0;
		if (num == 0) fin >> count;
		else count = num;
		buf.reserve(count + buf.size());
		for (size_t i = 0; i < count; ++i)
		{
			f2Vec2 p;
			fin >> p;
			buf.push_back(p);
		}
	}
	else
	{
		size_t count = 0;
		if (num == 0) fin.read(reinterpret_cast<char*>(&count), sizeof(size_t));
		else count = num;
		buf.reserve(count + buf.size());
		for (size_t i = 0; i < count; ++i)
		{
			f2Vec2 p;
			fin.read(reinterpret_cast<char*>(&p.x), sizeof(float));
			fin.read(reinterpret_cast<char*>(&p.y), sizeof(float));
			buf.push_back(p);
		}
	}
}

void FileIO::writeToFile(const std::vector<f2Vec2>& buf, std::ofstream& fout, bool isText/* = true*/, size_t num/* = 0*/)
{
	if (isText)
	{
		const size_t count = buf.size();
		if (num == 0) fout << count << std::endl;
		for (size_t i = 0; i < count; ++i)
			fout << buf[i] << " ";
		fout << std::endl;
	}
	else
	{
		const size_t count = buf.size();
		if (num == 0) fout.write(reinterpret_cast<const char*>(&count), sizeof(size_t));
		for (size_t i = 0; i < count; ++i)
		{
			fout.write(reinterpret_cast<const char*>(&buf[i].x), sizeof(float));
			fout.write(reinterpret_cast<const char*>(&buf[i].y), sizeof(float));
		}
	}
}

void FileIO::readFromFile(std::vector<std::vector<f2Vec2> >& buf, std::ifstream& fin, bool isText/* = true*/, size_t num/* = 0*/)
{
	size_t count = 0;
	if (isText) fin >> count;
	else fin.read(reinterpret_cast<char*>(&count), sizeof(size_t));
	buf.reserve(buf.size() + count);
	for (size_t i = 0; i < count; ++i)
	{
		std::vector<f2Vec2> tmp;
		readFromFile(tmp, fin, isText, num);
		buf.push_back(tmp);
	}
}

void FileIO::writeToFile(const std::vector<std::vector<f2Vec2> >& buf, std::ofstream& fout, bool isText/* = true*/, size_t num/* = 0*/)
{
	size_t count = buf.size();
	if (isText) fout << count << std::endl;
	else fout.write(reinterpret_cast<const char*>(&count), sizeof(size_t));
	for (size_t i = 0; i < count; ++i)
	{
		writeToFile(buf[i], fout, isText, num);
	}
}
