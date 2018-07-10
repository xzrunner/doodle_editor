#ifndef _FEDITOR_FILE_IO_H_
#define _FEDITOR_FILE_IO_H_
#include <Fruits2D/Fruits2D.h>

namespace FEDITOR
{
	class FileIO
	{
	public:
		static void readFromFile(std::vector<f2Vec2>& buf, std::ifstream& fin, bool isText = true, size_t num = 0);
		static void writeToFile(const std::vector<f2Vec2>& buf, std::ofstream& fout, bool isText = true, size_t num = 0);

		static void readFromFile(std::vector<std::vector<f2Vec2> >& buf, std::ifstream& fin, bool isText = true, size_t num = 0);
		static void writeToFile(const std::vector<std::vector<f2Vec2> >& buf, std::ofstream& fout, bool isText = true, size_t num = 0);

	}; // FileIO
}

#endif // _FEDITOR_FILE_IO_H_