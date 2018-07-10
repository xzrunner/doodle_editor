#ifndef _MOTOX_TRACK_CHAINS_H_
#define _MOTOX_TRACK_CHAINS_H_

#include <Doodle2D/doodle2d.h>

namespace motox
{
	class TrackChains
	{
	public:
		TrackChains(d2d::Context* pContext,
			int scene, int level);
		~TrackChains();

		void draw() const;

		d2d::Vector getActorStartPos() const;

	private:
		void loadFromFile(const std::string& filename);
		void loadShapes(const std::string& filename);
		void loadBodies();

	private:
		d2d::PhysicsService* m_physicsService;

		std::vector<std::vector<d2d::Vector> > m_chains;
		std::vector<b2Body*> m_bodies;

#ifdef D2D_ANDROID_NATIVE
		android_app* m_pApplication;
#endif

	}; // TrackChains
}

#endif // _MOTOX_TRACK_CHAINS_H_