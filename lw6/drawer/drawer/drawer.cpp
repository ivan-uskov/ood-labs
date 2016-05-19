#include "stdafx.h"
#include "graphics_lib.h"
#include "shape_drawing_lib.h"
#include "modern_graphics_lib.h"
#include "ComposedCanvasAdapter.h"
#include "InheritedCanvasAdapter.h"

using namespace std;

namespace app
{
    void PaintPicture(shape_drawing_lib::CCanvasPainter & painter)
    {
        using namespace shape_drawing_lib;

        CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 }, 0x00FF00);
        CRectangle rectangle({ 30, 40 }, 18, 24, 0x0000FF);

        painter.Draw(triangle);
        painter.Draw(rectangle);
    }

    void PaintPictureOnCanvas()
    {
        graphics_lib::CCanvas simpleCanvas;
        shape_drawing_lib::CCanvasPainter painter(simpleCanvas);
        PaintPicture(painter);
    }

    void PaintPictureOnModernGraphicsRenderer()
    {
        modern_graphics_lib::CModernGraphicsRenderer renderer(cout);
        ComposedCanvasAdapter paintAdapter(move(renderer));
        shape_drawing_lib::CCanvasPainter painter(paintAdapter);
        PaintPicture(painter);
    }

    void PaintPictureOnModernGraphicsRendererByInheritedAdapter()
    {
        InheritedCanvasAdapter paintAdapter(cout);
        shape_drawing_lib::CCanvasPainter painter(paintAdapter);
        PaintPicture(painter);
    }
}

int main()
{
    app::PaintPictureOnCanvas();
    app::PaintPictureOnModernGraphicsRenderer();
    app::PaintPictureOnModernGraphicsRendererByInheritedAdapter();

    return 0;
}