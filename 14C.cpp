#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>


struct Point {
    long long x = 0;
    long long y = 0;

    Point(const long long& new_x, const long long& new_y) {
        x = new_x;
        y = new_y;
    }
};

long long cross_product(const Point first, const Point second) {
    return first.x * second.y - first.y * second.x;
}

long long side(const Point& first, const Point& second, const Point& pnt) {
    Point first_vec = Point(first.x - pnt.x, first.y - pnt.y);
    Point second_vec = Point(second.x - pnt.x, second.y - pnt.y);
    if (cross_product(first_vec, second_vec) == 0)
        return 0;
    if (cross_product(first_vec, second_vec) > 0)
        return 1;
    if (cross_product(first_vec, second_vec) < 0)
        return -1;
}

bool cross(const std::vector<Point>& points) {
    if (points[0].x == points[2].x && points[0].y == points[2].y) {
        return true;
    }
    if (points[0].x == points[3].x && points[0].y == points[3].y) {
        return true;
    }
    if (points[1].x == points[2].x && points[1].y == points[2].y) {
        return true;
    }
    if (points[1].x == points[3].x && points[1].y == points[3].y) {
        return true;
    }
    if (side(points[0], points[1], points[2]) == 0 && side(points[0], points[1], points[3]) == 0 && side(points[2], points[3], points[0]) == 0 && side(points[2], points[3], points[1]) == 0) {
        std::vector<std::pair<std::pair<long long, long long>, long long>> forsort = { { {points[0].x, points[0].y}, 0 }, { {points[1].x, points[1].y}, 0 }, { {points[2].x, points[2].y}, 1 }, { {points[3].x, points[3].y}, 1 } };
        std::sort(forsort.begin(), forsort.end());
        if (forsort[0].second != forsort[1].second) {
            return true;
        }
        return false;
    }
    if (abs(side(points[0], points[1], points[2]) + side(points[0], points[1], points[3])) != 2) {
        if (abs(side(points[2], points[3], points[0]) + side(points[2], points[3], points[1])) != 2) {
            return true;
        }
    }
    return false;
}



int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::vector<Point> points;
    for (long long i = 0; i < 4; ++i) {
        long long tempx, tempy;
        std::cin >> tempx >> tempy;
        points.push_back(Point(tempx, tempy));
    }

    if (cross(points)) {
        std::cout << "YES";
    }
    else {
        std::cout << "NO";
    }

    return 0;
}