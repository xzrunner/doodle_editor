#ifndef _DEDITOR_MOTOX_TRACK_CHAIN_H_
#define _DEDITOR_MOTOX_TRACK_CHAIN_H_

#include <wxGUI/wxGUI.h>

class b2World;

namespace deditor
{
	namespace motox
	{
		class TrackChain : public wxgui::ChainShape
		{
		public:
			TrackChain(b2World* world, b2World* worldReverse,
				const std::vector<f2Vec2>& vertices);
			virtual ~TrackChain();
			
			//
			// wxgui::ChainShape interface
			//
			virtual void insertVertices(size_t index, const f2Vec2& pos);
			virtual void removeVertices(const f2Vec2& pos);
			virtual void changeVertices(const f2Vec2& from, const f2Vec2& to);
			virtual void setVertices(const std::vector<f2Vec2>& vertices);
			virtual void refresh();

			void updateBody();

			void setFriction(float friction);

			void setScale(float scale);
			void setTranslation(const f2Vec2& offset);

			b2Body* getBody() { return m_body->getBody(); }

		private:
			void createBody();

		private:
			float m_scale;
			f2Vec2 m_offset;

			b2World *m_world, *m_worldReverse;
			wxgui::ChainBody *m_body, *m_bodyReverse;

		}; // TrackChain
	}
}

#endif // _DEDITOR_MOTOX_TRACK_CHAIN_H_