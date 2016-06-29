#include "stdafx.h"
#include "../libpainter/Designer.h"
#include "../libpainter/ShapeFactory.h"
#include "../libpainter/SvgCanvas.h"
#include "../libpainter/Painter.h"

using namespace std;

int main()
{
    auto canvas = make_shared<CSvgCanvas>();
    CShapeFactory factory;
    CDesigner designer(factory);
    CPainter painter;

    auto draft = designer.CreateDraft(cin);

    draft.Draw(*canvas);
    canvas->Flush("test-draw-method.svg");
    canvas->Clear();

    painter.Draw(canvas, draft);
    canvas->Flush("test-painter.svg");
    canvas->Clear();

    return 0;
}

