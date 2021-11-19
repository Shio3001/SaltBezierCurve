

#ifndef integration_include
#define integration_include

#include "stdload.hpp"

class Integration
{
private:
    int m_x_width;
    int m_y_hight;

    float m_x1;
    float m_y1;
    float m_x2;
    float m_y2;

    int m_complement_time;

    int *m_draw;
    int *m_points;

    float m_a1;
    float m_a2;
    float m_b1;
    float m_b2;

    int m_maximum = 100;

    float LinearFunction(int x, float a, float b)
    {
        float y = a * x + b;
        return y;
    }

    void draw_point(int x, int y, int size)
    {
        for (int yd = 0; yd < size; yd++)
        {
            int ydp = y - (size / 2) + yd;
            for (int xd = 0; xd < size; xd++)
            {
                int xdp = x - (size / 2) + xd;
                int ipx = ydp * m_x_width + xdp;

                if (ipx < m_y_hight * m_x_width)
                {
                    m_draw[ipx] = 255;
                }
            }
        }
    }

public:
    Integration()
    {
    }
    ~Integration()
    {
    }

    void Setup(int send_x, int send_y)
    {
        m_x_width = send_x;
        m_y_hight = send_y;
        fs::create_directory("BezierCurvetemp");

        m_draw = new int[m_y_hight * m_x_width];
        for (int i = 0; i < m_y_hight * m_x_width; i++)
        {
            m_draw[i] = 0;
        }
        m_complement_time = m_x_width; //標本回数

        m_points = new int[m_complement_time * 2];
        for (int j = 0; j < m_complement_time * 2; j++)
        {
            m_points[j] = 0;
        }
    }
    void DeleteDraw()
    {
        delete[] m_draw;
    }

    void CalculationSetup(float send_x1, float send_y1, float send_x2, float send_y2) // 0 < x < 100 , 0 < y < 100
    {
        m_x1 = send_x1;
        m_y1 = send_y1;

        m_x2 = send_x2;
        m_y2 = send_y2;

        m_a1 = m_y1 / m_x1;
        m_a2 = (m_maximum - m_y2) / (m_maximum - m_x2);

        m_b1 = 0;
        m_b2 = m_y2 - (m_a2 * m_x2);
    }

    std::vector<float> CalculationSpecific(float ratio) // 0 - 1
    {

        float now_xA = m_x1 * ratio;
        float now_xC = (m_maximum - m_x2) * ratio + m_maximum;

        float yA = LinearFunction(now_xA, m_a1, m_b1);
        float yC = LinearFunction(now_xC, m_a2, m_b2);

        float cfA = (yC - yA) / (now_xC - now_xA);
        float cfB = yC - (cfA * now_xC);
        float cfX = (yC - yA) * ratio + yA;

        float yB = LinearFunction(cfX, cfA, cfB);

        std::vector<float> result = {cfX, yB};
        return result;
    }

    void CalculationView()
    {
        for (float ri = 0; ri < m_x_width; ri++)
        {
            float ratio = (ri / m_x_width);
            std::vector<float> result = CalculationSpecific(ratio);
            draw_point(result[0], result[1], 20);
        }
    }

    int *GetView()
    {
        return m_draw;
    }
};

#endif
