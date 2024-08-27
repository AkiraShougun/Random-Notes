#include <iostream>
#include "Eigen/Dense"
#include <optional>
#include <map>
#include <algorithm>
#include <tuple>

typedef std::vector<int> Point;
typedef std::vector<std::pair<int, int>> Line;
typedef std::vector<std::tuple<int, int, int>> Triangle;
typedef std::vector<std::tuple<int, int, int, int>> Tetrahedron;

struct Simplicial
{
    Point point;
    Line line;
    std::optional<Triangle> triangle;
    std::optional<Tetrahedron> tetrahedron;

    Simplicial(Point point, Line line, std::optional<Triangle> triangle, std::optional<Tetrahedron> tetrahedron) : point(point), line(line), triangle(triangle), tetrahedron(tetrahedron)
    {
        std::sort(this->point.begin(), this->point.end());
        std::sort(this->line.begin(), this->line.end());
        if (this->triangle.has_value())
        {
            std::sort(this->triangle->begin(), this->triangle->end());
        }
        if (this->tetrahedron.has_value())
        {
            std::sort(this->tetrahedron->begin(), this->tetrahedron->end());
        }
    }

    Eigen::MatrixXf boundaryOne()
    {
        std::map<int, int> pointToRow;
        for (int i = 0; i < int(point.size()); ++i)
        {
            pointToRow[point[i]] = i;
        }

        // Matrix dimensions
        int R = point.size(); // Number of points
        int C = line.size();  // Number of lines
        Eigen::MatrixXf mtx(R, C);
        mtx.setZero();

        // Update the matrix based on lines
        for (int stair = 0; stair < C; ++stair)
        {
            const auto &p1 = line[stair].first;
            const auto &p2 = line[stair].second;

            auto it1 = pointToRow.find(p1);
            auto it2 = pointToRow.find(p2);

            if (it1 != pointToRow.end() && it2 != pointToRow.end())
            {
                int row1 = it1->second;
                int row2 = it2->second;

                mtx(row1, stair) = -1;
                mtx(row2, stair) = 1;
            }
        }
        return mtx;
    }

    Eigen::MatrixXf BoundaryTwo()
    {
        int R = line.size();
        int C;
        if (triangle.has_value())
        {
            C = triangle->size();
        }
        Eigen::MatrixXf mtx(R, C);
        mtx.setZero();

        return mtx;
    }

    void homologyZero()
    {
        Eigen::MatrixXf mtx = boundaryOne();
        Eigen::FullPivLU<Eigen::MatrixXf> lu_decomp(mtx);
        int rank = lu_decomp.rank();
        std::cout << (point.size() - rank) << "\n";
    }

    // Second homology group
};

int main()
{
    Point myPoint{1, 2, 3, 4};
    Line myLine{{1, 3}, {1, 2}, {2, 3}, {2, 4}, {3, 4}};
    Triangle myTriangle = {{1, 2, 3}};
    Simplicial torus(myPoint, myLine, myTriangle, std::nullopt);
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