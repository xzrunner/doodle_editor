#include "EditNodesAtomicOP.h"

#include "Dataset/ChainShape.h"

using namespace wxgui;
using namespace wxgui::edit_nodes;

ModifyNodesAOP::ModifyNodesAOP(const std::vector<ChainShape*>& chains, 
							   const std::vector<std::vector<f2Vec2> >& dstChains)
{
	m_chains.reserve(chains.size());
	for (size_t i = 0, n = chains.size(); i < n; ++i)
	{
		chains[i]->retain();
		m_chains.push_back(chains[i]);

		m_src.push_back(chains[i]->getVertices());
		m_dst.push_back(dstChains[i]);
	}
}

void ModifyNodesAOP::undo()
{
	for (size_t i = 0, n = m_chains.size(); i< n; ++i)
		m_chains[i]->setVertices(m_src[i]);
}

void ModifyNodesAOP::redo()
{
	for (size_t i = 0, n = m_chains.size(); i< n; ++i)
		m_chains[i]->setVertices(m_dst[i]);
}