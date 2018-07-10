#ifndef _F2D_VISITORS_H_
#define _F2D_VISITORS_H_

#include "Tools.h"

namespace F2D
{
	template <typename T>
	class FetchAllVisitor : public IVisitor
	{
	public:
		FetchAllVisitor(std::vector<T*>& result) 
			: m_result(result) {}

		virtual void visit(IObject* object, bool& bFetchNext)
		{
			T* item = dynamic_cast<T*>(object);
			if (item)
				m_result.push_back(item);
			bFetchNext = true;
		}

	private:
		std::vector<T*>& m_result;

	}; // FetchAllVisitor

//	template <typename T>
	class CountVerifyVisitor : public IVisitor
	{
	public:
		CountVerifyVisitor(bool& valid, int num)
			: m_valid(valid), m_num(num), m_count(0) {}

		virtual ~CountVerifyVisitor() {
			m_valid = m_count == m_num;
		}

		void visit(IObject* object, bool& bFetchNext) {
			++m_count;
			bFetchNext = m_count <= m_num;
		}

	private:
		bool& m_valid;
		const int m_num;

		int m_count;

	}; // CountVerifyVisitor

	class EmptyVerifyVisitor : public IVisitor
	{
	public:
		EmptyVerifyVisitor(bool& valid) 
			: m_valid(valid) { m_valid = true; }

		void visit(IObject* object, bool& bFetchNext) {
			m_valid = false;
			bFetchNext = false;
		}

	private:
		bool& m_valid;

	}; // EmptyVerifyVisitor
}

#endif // _F2D_VISITORS_H_