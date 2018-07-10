#ifndef _FEDITOR_MOTOX_LEVEL_BLACKBOARD_H_
#define _FEDITOR_MOTOX_LEVEL_BLACKBOARD_H_
#include "../../AbstractBlackboard.h"

class GLUI_Spinner;
class GLUI_Checkbox;

namespace FEDITOR
{
	namespace MOTOX
	{
		namespace LEVEL
		{
			class Blackboard : public AbstractBlackboard
			{
			public:
				Blackboard();

			public:
				enum
				{
					e_SetGravity = EVENT_ID_BASE_PRIVATE_BLACKBOARD,
					e_SetMouseDrag,

					e_OpenBgTexture,
					e_OpenBgShapes,
					e_OpenTrackChain,
					e_OpenTileSprite,
					e_OpenMotorbike,
					e_OpenAllSprites,

					e_DrawTrackChain,
					e_EditTrackChain,
					e_SaveTrackChain,
					e_SetTrackFriction,

					e_SetGravityDir,

					e_UpdateActor,

					e_SetMotoFriction,
					e_SetMotoDensity,
					e_SetPlayerDensity,
					e_SetMotoSpeed,
					e_SetMotoAcc,
					e_SetMotoTorque,
					e_SetMotoDamping,
					e_SetMotoHz,
					e_SetMotoMaxMotorTorque,

					e_ResetScale,
					e_SaveSprites
				};

			public:
				int m_cameraFocusMoto;
				float m_gravity;

				int m_chooseWorldType;

				float m_trackFriction;

				float m_motoFriction, m_motoDensity,
					m_motoSpeed, m_motoAcc, m_motoTorque,
					m_motoDamping, m_motoHz, m_motoMaxMotorTorque;

				float m_spriteScale;
				GLUI_Spinner* m_scaleSpinner;
				int m_flagSpriteMirror;
				GLUI_Checkbox* m_mirrorCheckbox;

				int m_batchState;
				int m_batchNum;
				int m_batchRandomRadius;
				int m_stopInstant;

			}; // Blackboard

			inline Blackboard::Blackboard()
			{
				m_cameraFocusMoto = 0;
				m_gravity = 10.0f;

				m_chooseWorldType = 0;

				m_motoFriction = 1.0f;
				m_motoDensity = 1.0f;
				m_motoSpeed = 30;
				m_motoAcc = 10;
				m_motoTorque = 8.0f;
				m_motoDamping = 0.7f;
				m_motoHz = 20.0f;
				m_motoMaxMotorTorque = 80;

				m_spriteScale = 1.0f;
				m_scaleSpinner = NULL;
				m_flagSpriteMirror = 0;
				m_mirrorCheckbox = NULL;

				m_batchState = 0;
				m_batchNum = 2;
				m_batchRandomRadius = 20;
				m_stopInstant = 0;
			}
		}
	}
}

#endif // _FEDITOR_MOTOX_LEVEL_BLACKBOARD_H_