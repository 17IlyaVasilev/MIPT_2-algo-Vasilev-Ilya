#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

struct Point {
    long long x = 0;
    long long y = 0;

    Point(const long long& new_x, const long long& new_y) {
        x = new_x;
        y = new_y;
    }
};


double vector_length(const Point& start, const Point& end) {
    return sqrt(pow(abs(start.x - end.x), 2) + pow(abs(start.y - end.y), 2));
}


Point vector_sum(const std::vector<Point>& points) {
    return Point(points[1].x - points[0].x + points[3].x - points[2].x, points[1].y - points[0].y + points[3].y - points[2].y);
}


double scalar_product(const std::vector<Point>& points) {
    return (points[1].x - points[0].x) * (points[3].x - points[2].x) + (points[1].y - points[0].y) * (points[3].y - points[2].y);
}

double cross_product(const std::vector<Point>& points) {
    return (points[1].x - points[0].x) * (points[3].y - points[2].y) - (points[1].y - points[0].y) * (points[3].x - points[2].x);
}

double square(const std::vector<Point>& points) {
    return abs(cross_product(points)) / 2;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::vector<Point> points;
    for (size_t i = 0; i < 4; ++i) {
        long long tempx, tempy;
        std::cin >> tempx >> tempy;
        points.push_back(Point(tempx, tempy));
    }

    std::cout << std::setprecision(7) << vector_length({ points[0].x, points[0].y }, { points[1].x, points[1].y }) << " ";
    std::cout << vector_length({ points[2].x, points[2].y }, { points[3].x, points[3].y }) << std::endl;

    Point vecSum = vector_sum(points);
    std::cout << vecSum.x << " " << vecSum.y << std::endl;

    std::cout << scalar_product(points) << " " << cross_product(points) << std::endl;

    std::cout << square(points) << std::endl;

    return 0;
}