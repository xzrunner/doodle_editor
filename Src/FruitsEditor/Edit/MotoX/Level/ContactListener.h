#ifndef _FEDITOR_MOTOX_LEVEL_CONTACT_LISTENER_H_
#define _FEDITOR_MOTOX_LEVEL_CONTACT_LISTENER_H_
#include <Box2D/Box2D.h>
#include <Fruits2D/Fruits2D.h>

namespace FEDITOR
{
	namespace MOTOX
	{
		namespace LEVEL
		{
			class Model;
			class Blackboard;

			class ContactListener : public b2ContactListener
			{
			public:
				ContactListener(Model* model, Blackboard* blackboard);

				virtual void BeginContact(b2Contact* contact);

				void deletePhysics();

			private:
				void deleteBody(b2Body* body);

			private:
				Model* m_model;
				Blackboard* m_blackboard;

				std::vector<b2Body*> m_buffer;

			}; // ContactListener
		}
	}
}

#endif // _FEDITOR_MOTOX_LEVEL_CONTACT_LISTENER_H_