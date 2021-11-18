
class Integration
{
    int x_width;
    int y_hight;

    int x1;
    int y1;
    int x2;
    int y2;

    int *draw;

public:
    Integration()
    {
    }
    ~Integration()
    {
    }

    void Setup(int send_x, int send_y)
    {
        x_width = send_x;
        y_hight = send_y;
        fs::create_directory("BezierCurvetemp");

        draw = new int[y_hight * x_width];
        for (int i = 0; i < y_hight * x_width; i++)
        {
            draw[i] = 0;
        }
    }
    void DeleteDraw()
    {
        delete[] draw;
    }

    void Calculation(int send_x1, int send_y1, int send_x2, int send_y2)
    {
        x1 = send_x1;
        y1 = send_y1;
        x2 = send_x2;
        y2 = send_y2;
    }

    int *GetView()
    {
        return draw;
    }
};
