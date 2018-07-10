#ifndef _D2D_TOOLS_H_
#define _D2D_TOOLS_H_

#include <algorithm>

template<class T>
struct DeletePointerFunctor
{
	void operator()(const T* pT) const
	{
		delete pT, pT = NULL;
	}
};

#endif // _D2D_TOOLS_H_