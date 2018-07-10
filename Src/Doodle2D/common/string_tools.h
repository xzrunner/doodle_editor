#ifndef _D2D_STRING_TOOLS_H_
#define _D2D_STRING_TOOLS_H_

#include <sstream>

namespace d2d
{
	inline std::string int2String(int i)
	{
		std::stringstream ss;
		ss << i;
		return ss.str();
	}
}

#endif // _D2D_STRING_TOOLS_H_