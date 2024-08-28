#include <iostream>
#include <cmath>

template <typename T>
void bubbleSort(T a[], int len)
{
    for (int i = 0; i < len - 1; i++)
    {
        for (int j = 0; j < len - i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                std::swap(a[j], a[j + 1]);
            }
        }
    }
}

template <typename T>
struct Point
{
    T x, y, z;

    Point(T x, T y, T z) : x(x), y(y), z(z) {}
    void display()
    {
        std::cout << "Point(" << x << ", " << y << ", " << z << ")" << std::endl;
    }

    float distance()
    {
        return sqrt(x * x + y * y + z * z);
    }

    bool same()
    {
        return (x == y && x == z);
    }
};

template <typename T>
Point<T> add(Point<T> p1, Point<T> p2)
{
    return Point<T>(p1.x + p2.x, p1.y + p2.y, p1.z + p2.z);
}

int main()
{
    Point<float> p2(1.2, 1.2, 1.2);
    Point<float> p1(3.3, 3.3, 3.3);
    Point<float> result = add(p1, p2);
    result.display();
    return 0;
}