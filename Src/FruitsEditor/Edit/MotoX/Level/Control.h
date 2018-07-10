#ifndef _FEDITOR_MOTOX_LEVEL_CONTROL_H_
#define _FEDITOR_MOTOX_LEVEL_CONTROL_H_
#include "../../AbstractPhysCtrl.h"

namespace FEDITOR
{
	class LayersMgrCmpt;
	class LayersIOCmpt;
	class NodeCaptureCmpt;
	class AbstractEditOpCB;

	namespace MOTOX
	{
		namespace LEVEL
		{
			class ContactListener;

			class Control : public AbstractPhysCtrl
			{
			public:
				Control();
				virtual ~Control();

				static AbstractControl* Create()
				{
					return new Control;
				}

			protected:
				virtual void onKeyboard(unsigned char key, int x, int y);
				virtual void onMouseLeftDown(int x, int y);
				virtual void onMouseRightDown(int x, int y);

				virtual void handleStep();
				virtual void handleUIEvent();

				virtual void createEditCmpt();

				virtual void update();
				virtual void display() const;

			private:
				void openTile(const std::string& filename);

				void setArrangeSpriteOp();

			private:
				b2World* m_worldReverse;

				LayersMgrCmpt* m_layersMgrCmpt;
//				LayersIOCmpt* m_layersIOCmpt;
				NodeCaptureCmpt* m_captureCmpt;

				ContactListener* m_lsn;

			}; // Control
		}
	}
}

#endif // _FEDITOR_MOTOX_LEVEL_CONTROL_H_