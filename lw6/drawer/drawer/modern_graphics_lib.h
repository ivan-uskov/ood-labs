#pragma once

// ѕространство имен современной графической библиотеки (недоступно дл€ изменени€)
namespace modern_graphics_lib
{
    class CPoint
    {
    public:
        CPoint(int x, int y)
            : x(x)
            , y(y)
        {}

        int x;
        int y;
    };

    class CRGBAColor
    {
    public:
        CRGBAColor(float r, float g, float b, float a) 
            : r(r)
            , g(g)
            , b(b)
            , a(a)
        {}

        float r, g, b, a;
    };


    //  ласс дл€ современного рисовани€ графики
    class CModernGraphicsRenderer
    {
    public:
        CModernGraphicsRenderer(std::ostream & strm)
            : m_out(strm)
        {
        }

        ~CModernGraphicsRenderer()
        {
            if (m_drawing) // «авершаем рисование, если оно было начато
            {
                EndDraw();
            }
        }

        // Ётот метод должен быть вызван в начале рисовани€
        void BeginDraw()
        {
            if (m_drawing)
            {
                throw std::logic_error("Drawing has already begun");
            }
            m_out << "<draw>" << std::endl;
            m_drawing = true;
        }

        // ¬ыполн€ет рисование линии
        void DrawLine(const CPoint & start, const CPoint & end, const CRGBAColor & color)
        {
            if (!m_drawing)
            {
                throw std::logic_error("DrawLine is allowed between BeginDraw()/EndDraw() only");
            }

            m_out << "<line fromX=\"" << start.x << "\" fromY=\"" << start.y << "\" toX=\"" << end.x << " toY=\"" << end.y << "\">" << std::endl
                  << "  <color r=\"" << color.r << "\" g=\"" << color.g << "\" b=\"" << color.b << "\" a=\"" << color.a << "\" />" << std::endl
                  << "</line>" << std::endl;
        }

        // Ётот метод должен быть вызван в конце рисовани€
        void EndDraw()
        {
            if (!m_drawing)
            {
                throw std::logic_error("Drawing has not been started");
            }
            m_out << "</draw>" << std::endl;
            m_drawing = false;
        }
    private:
        std::ostream & m_out;
        bool m_drawing = false;
    };
}
