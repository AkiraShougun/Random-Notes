#include <iostream>
#include "Eigen/Dense"
#include <optional>
#include <map>

typedef std::vector<int> Point;
typedef std::vector<std::pair<int, int>> Line;
typedef std::optional<std::vector<std::tuple<int, int, int>>> Triangle;
typedef std::optional<std::vector<std::tuple<int, int, int, int>>> Tetrahedron;

struct Simplicial
{
    Point point;
    Line line;
    Triangle triangle;
    Tetrahedron tetrahedron;

    Simplicial(Point point, Line line, Triangle triangle, Tetrahedron tetrahedron) : point(point), line(line), triangle(triangle), tetrahedron(tetrahedron) {}

    Eigen::MatrixXf boundaryOne()
    {
        std::map<int, int> pointToCol;
        for (int i = 0; i < int(point.size()); ++i)
        {
            pointToCol[point[i]] = i;
        }

        // Matrix dimensions
        int R = line.size();  // Number of lines
        int C = point.size(); // Number of points
        Eigen::MatrixXf mtx(R, C);
        mtx.setZero();

        // Update the matrix based on lines
        for (int stair = 0; stair < int(line.size()); ++stair)
        {
            const auto &p1 = line[stair].first;
            const auto &p2 = line[stair].second;

            auto it1 = pointToCol.find(p1);
            auto it2 = pointToCol.find(p2);

            if (it1 != pointToCol.end() && it2 != pointToCol.end())
            {
                int col1 = it1->second;
                int col2 = it2->second;

                mtx(stair, col1) = -1;
                mtx(stair, col2) = 1;
            }
        }
        return mtx;
    }

    void homologyZero()
    {
        Eigen::MatrixXf mtx = boundaryOne();
        Eigen::FullPivLU<Eigen::MatrixXf> lu_decomp(mtx);
        int rank = lu_decomp.rank();
        std::cout << (point.size() - rank) << "\n";
    }
};

int main()
{
    Point myPoint = {1, 2, 3};
    Line myLine{{1, 2}, {1, 3}, {2, 3}};
    Simplicial torus(myPoint, myLine, std::nullopt, std::nullopt);
    torus.homologyZero();
    return 0;
}

// G

/*
    1
   / \
  2 - 3
*/

// [1], [2], [3], [4], [5]
// [1,2], [1,3], [2,3], [4,5]

// boundary([1,2]) = [2]-[1]
// boundary ([1,3]) = [3]-[1]
// boundary([2,3]) = [3]-[2]
// boundary([4,5]) = [4]-[5]

// [[1,2,3], [3,4,5]]
// R=2
// [1,2,3] -> [1,2], [1,3], [2,3]
// [3,4,5] -> [3,4], [3,5], [4,5]

/*     [1]  [2]  [3]
[1,2]  -1    1   0
[1,3]  -1   0    1
[2,3]   0   -1   1

[1,2]  -1    1   0
[2,3]   0   -1   1
[1,3]  -1   0    1
*/

/*       [1,2]   [1,3]   [2,3]
[1,2,3]   1       -1      1
*/

// dim(H_n) = nullity(d_n) - rank(d_(n+1))

// dim(H_1) = nullity(d_1) - rank(d_(2))
//          =     1        -     0 = 1

// dim (H_1) = 1 - 1 = 0

// [1,2,3]
// []

// C_0 <- C_1 <- C_2 <- C_3