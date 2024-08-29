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

    Eigen::MatrixXf boundaryTwo()
    {
        int R = line.size();
        int C = triangle.has_value() ? triangle->size() : 0;
        Eigen::MatrixXf mtx(R, C);
        mtx.setZero();
        if (C != 0)
        {
            for (int j = 0; j < C; ++j)
            {
                const auto &[a, b, c] = (*triangle)[j];
                std::vector<std::pair<int, int>> edges = {{a, b}, {b, c}, {a, c}};

                for (int i = 0; i < R; ++i)
                {
                    const auto &line_pair = line[i];

                    if (line_pair == edges[0])
                    {
                        mtx(i, j) = 1;
                    }
                    else if (line_pair == edges[1])
                    {
                        mtx(i, j) = 1;
                    }
                    else if (line_pair == edges[2])
                    {
                        mtx(i, j) = -1;
                    }
                }
            }
        }

        return mtx;
    }

    int homologyZero()
    {
        Eigen::MatrixXf mtx = boundaryOne();
        Eigen::FullPivLU<Eigen::MatrixXf> lu_decomp(mtx);
        int rank = lu_decomp.rank();
        return (point.size() - rank);
    }

    int homologyOne()
    {
        // boundaries
        Eigen::MatrixXf d1 = boundaryOne();
        Eigen::MatrixXf d2 = boundaryTwo();
        int col_d1 = line.size();

        // rank
        Eigen::FullPivLU<Eigen::MatrixXf> lu_decompd1(d1);
        int rank_d1 = lu_decompd1.rank();
        int kernel = col_d1 - rank_d1;
        if (d2.rows() == 0 || d2.cols() == 0)
        {
            return kernel;
        }
        Eigen::FullPivLU<Eigen::MatrixXf> lu_decompd2(d2);
        int rank_d2 = lu_decompd2.rank();

        return kernel - (rank_d2);
    }

    // Second homology group.
};

int main()
{
    Point myPoint{1, 2, 3};
    Line myLine{{1, 2}, {2, 3}, {1, 3}};
    Triangle myTriangle{{1, 2, 3}};
    Simplicial circle(myPoint, myLine, myTriangle, std::nullopt);
    std::cout << circle.homologyOne();
    return 0;
}

//[1,2,3]

//[1,2],[2,3],[1,3]
//    1     1   -1

/*
      [1,2,3] []
[1,2]   1
[2,3]   1
[1,3]   -1

*/

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