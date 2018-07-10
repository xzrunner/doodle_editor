#ifndef _WX_GUI_EDIT_NODES_ATOMIC_OP_H_
#define _WX_GUI_EDIT_NODES_ATOMIC_OP_H_

#include "AbstractAtomicOP.h"

namespace wxgui
{
	class ChainShape;

	namespace edit_nodes
	{
		class ModifyNodesAOP : public AbstractAtomicOP
		{
		public:
			ModifyNodesAOP(const std::vector<ChainShape*>& chains, 
				const std::vector<std::vector<f2Vec2> >& dstChains);

			virtual void undo();
			virtual void redo();

		private:
			std::vector<ChainShape*> m_chains;
			std::vector<std::vector<f2Vec2> > m_src, m_dst;

		}; // ModifyNodesAOP
	}
}

#endif // _WX_GUI_EDIT_NODES_ATOMIC_OP_H_