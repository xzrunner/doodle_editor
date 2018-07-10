#ifndef _FEDITOR_BODY_DATA_H_
#define _FEDITOR_BODY_DATA_H_
#include "../Tools/ResourcesMgr.h"
#include <Box2D/Box2D.h>

namespace FEDITOR
{
	class BodyData;
	typedef ResourcesMgr<BodyData> BodyDataMgr;

	class BodyData
	{
	public:
		enum Type
		{
			e_chain		= 0,
			e_polygon	= 1,
			e_circle	= 2
		};

		Type type() const;

		struct FixtureData
		{
			std::vector<f2Vec2> vertices;
			float density, friction, restitution;

			FixtureData() {
				density = 1;
				friction = 0.5f;
				restitution = 0.7f;
			}

			void setFixtureDef(b2FixtureDef& fixtureDef) const {
				fixtureDef.density = density;
				fixtureDef.friction = friction;
				fixtureDef.restitution = restitution;
			}
  
		}; // FixtureData

		const std::vector<FixtureData*>& getAllFixturesData() const;

		const std::string& getFilename() const;

	private:
		BodyData();
		~BodyData();

		void clear();

		bool loadFromFile(const std::string& filename);

		void loadFromLoopsFile(const std::string& filename);
		void loadFromChainsFile(const std::string& filename);
		void loadFromCircleFile(const std::string& filename);

	private:
		std::string m_filename;

		Type m_type;

		std::vector<FixtureData*> m_fixtures;

		friend class ResourcesMgr<BodyData>;

	}; // BodyData

	inline BodyData::Type BodyData::type() const
	{	
		return m_type;
	}

	inline const std::vector<BodyData::FixtureData*>& BodyData::getAllFixturesData() const
	{
		return m_fixtures;
	}

	inline const std::string& BodyData::getFilename() const
	{
		return m_filename;
	}
}

#endif // _FEDITOR_BODY_DATA_H_