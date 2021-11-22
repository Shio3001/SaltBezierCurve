

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
        int count = 0;

        for (int yd = 0; yd < size; yd++)
        {
            int ydp = m_y_hight - (y - (size / 2) + yd);
            for (int xd = 0; xd < size; xd++)
            {
                int xdp = x - (size / 2) + xd;
                int ipx = ydp * m_x_width + xdp;

                if (0 < ipx && ipx < m_y_hight * m_x_width && 0 <= xdp && 0 <= ydp && xdp < m_x_width && ydp < m_y_hight) 
                {
                    m_draw[ipx] = 255;
                    count++;
                }
            }
        }
        std::cout << count << std::endl;
    }

public:
    Integration()
    {
    }
    ~Integration()
    {
        delete[] m_draw;
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

    float BezierFunction(float t, float xy1, float xy2, float xy3, float xy4)
    {
        float bezier_result = pow((1 - t), 3) * xy1 + 3 * pow((1 - t), 2) * t * xy2 + 3 * (1 - t) * pow(t, 2) * xy3 + pow(t, 3) * xy4;
        return bezier_result;
    }

    void CalculationSetup(float send_x1, float send_y1, float send_x2, float send_y2) // 0 < x < 100 , 0 < y < 100
    {
        std::cout << send_x1 << " " << send_y1 << " " << send_x2 << " " << send_y2 << std::endl;

        m_x1 = send_x1;
        m_y1 = send_y1;

        m_x2 = send_x2;
        m_y2 = send_y2;
    }

    std::vector<float> CalculationSpecific(float ratio) // 0 - 1
    {
        float BrX = BezierFunction(ratio, 0, m_x1, m_x2, m_maximum);
        float BrY = BezierFunction(ratio, 0, m_y1, m_y2, m_maximum);

        float f_x_width = m_x_width;
        float f_maximum = m_maximum;

        float BrXs = BrX * f_x_width / f_maximum;
        float BrYs = BrY * f_x_width / f_maximum;

        std::vector<float> result = {BrXs, BrYs};
        return result;
    }

    void CalculationView()
    {
        for (float ri = 0; ri < m_x_width; ri++)
        {
            float ratio = (ri / m_x_width);
            std::vector<float> result = CalculationSpecific(ratio);
            draw_point(result[0], result[1], 5);
        }
    }

    int *GetView()
    {
        return m_draw;
    }
};

#endif
