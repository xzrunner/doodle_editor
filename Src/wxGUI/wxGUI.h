#ifndef _WX_GUI_H_
#define _WX_GUI_H_

#include "Interface.h"

#include "Dataset/Bitmap.h"
#include "Dataset/Image.h"
#include "Dataset/RawPixels.h"
#include "Dataset/ISymbol.h"
#include "Dataset/SymbolFactory.h"
#include "Dataset/SymbolMgr.h"
#include "Dataset/ImageSymbol.h"
#include "Dataset/ShapeSymbol.h"
#include "Dataset/MeshSymbol.h"
#include "Dataset/CombinationSymbol.h"
#include "Dataset/ISprite.h"
#include "Dataset/SpriteFactory.h"
#include "Dataset/ImageSprite.h"
#include "Dataset/ShapeSprite.h"
#include "Dataset/MeshSprite.h"
#include "Dataset/CombinationSprite.h"
#include "Dataset/ChainShape.h"
#include "Dataset/CurveShape.h"
#include "Dataset/PolygonShape.h"
#include "Dataset/PolygonBody.h"
#include "Dataset/CircleBody.h"
#include "Dataset/ChainBody.h"
#include "Dataset/BodyData.h"
#include "Dataset/BodyFactory.h"
#include "Dataset/JointDef.h"
#include "Dataset/Joint.h"
#include "Dataset/Layer.h"

#include "View/GLCanvas.h"
#include "View/Camera.h"
#include "View/LibraryPanel.h"
#include "View/ILibraryPage.h"
#include "View/LibraryList.h"
#include "View/LibraryImagePage.h"
#include "View/LibraryShapePage.h"
#include "View/LibraryMeshPage.h"
#include "View/LibraryCombinationPage.h"
#include "View/PropertySettingPanel.h"
#include "View/IPropertySetting.h"
#include "View/SpritePropertySetting.h"
#include "View/SpriteStageCanvas.h"
#include "View/ShapeStageCanvas.h"
#include "View/ShapesPanelImpl.h"
#include "View/SpritesPanelImpl.h"
#include "View/MultiShapesImpl.h"
#include "View/MultiSpritesImpl.h"
#include "View/PhysicsPanelImpl.h"
#include "View/ToolbarPanel.h"

#include "Edit/AbstractEditOP.h"
#include "Edit/NullEditOP.h"
#include "Edit/ZoomViewOP.h"
#include "Edit/ArrangeSpriteOP.h"
#include "Edit/ArrangeSpriteFixOP.h"
#include "Edit/DragPhysicsOP.h"
#include "Edit/UniversalArrangeOP.h"
#include "Edit/SelectSpritesOP.h"
#include "Edit/SelectPixelsOP.h"
#include "Edit/SelectShapesOP.h"
#include "Edit/DrawRectangleOP.h"
#include "Edit/DrawPolylineOP.h"
#include "Edit/DrawPolygonEdgeOP.h"
#include "Edit/DrawCurveOP.h"
#include "Edit/PasteSymbolOP.h"
#include "Edit/PasteSymbolRandomOP.h"
#include "Edit/PasteSymbolCaptureOP.h"
#include "Edit/PasteSymbolPhysicsOP.h"
#include "Edit/PasteSymbolPhysicsRandomOP.h"
#include "Edit/PasteSpriteOP.h"
#include "Edit/DrawPencilLineOP.h"
#include "Edit/DrawPenLineOP.h"
#include "Edit/EditPolylineOP.h"
#include "Edit/EditPolylinesOP.h"

#include "Atomic/AbstractAtomicOP.h"

#include "Component/AbstractEditCMPT.h"
#include "Component/UniversalCMPT.h"
#include "Component/PasteSymbolScaleCMPT.h"
#include "Component/PasteSymbolRandomCMPT.h"
#include "Component/PasteSymbolCaptureCMPT.h"
#include "Component/PasteSymbolPhysicsCMPT.h"
#include "Component/PasteSpriteCMPT.h"
#include "Component/DrawPolylineCMPT.h"
#include "Component/DrawPencilLineCMPT.h"
#include "Component/DrawLineCMPT.h"
#include "Component/DrawPolylineCMPT.h"
#include "Component/DrawPolygonCMPT.h"
#include "Component/EditNodesCMPT.h"
#include "Component/EditPolylinesCMPT.h"
#include "Component/LayersMgrCMPT.h"
#include "Component/MousePositionCMPT.h"
#include "Component/UniversalArrangeCMPT.h"

#include "Widgets/SetValueDialog.h"
#include "Widgets/ListItem.h"
#include "Widgets/VerticalImageList.h"
#include "Widgets/DragTargetNull.h"
#include "Widgets/SelectDrawTypeWidget.h"
#include "Widgets/LayersMgrWidget.h"
#include "Widgets/PasteSymbolRandomWidget.h"

#include "Tools/LibJpeg.h"
#include "Tools/log.h"
#include "Tools/FileNameParser.h"
#include "Tools/FilenameTools.h"
#include "Tools/PolylineFileAdapter.h"
#include "Tools/CircleFileAdapter.h"
#include "Tools/CombinationFileAdapter.h"
#include "Tools/MeshFileAdapter.h"
#include "Tools/ShapeFileAdapter.h"
#include "Tools/Settings.h"
#include "Tools/Math.h"
#include "Tools/visitors.h"

#include "Render/b2Render.h"
#include "Render/PrimitiveDraw.h"
#include "Render/DrawSelectedShapeVisitor.h"
#include "Render/DrawShapesVisitor.h"
#include "Render/DrawSelectedSpriteVisitor.h"
#include "Render/DrawSpritesVisitor.h"
#include "Render/SpriteDraw.h"
#include "Render/SpriteBatch.h"

#endif // _WX_GUI_H_