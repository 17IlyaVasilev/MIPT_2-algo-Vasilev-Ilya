#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>


struct Point {
    int x = 0;
    int y = 0;

    Point(const int& new_x, const int& new_y) {
        x = new_x;
        y = new_y;
    }
};

double radius(const std::vector<Point> points) {
    int max_rad = 0;
    for (size_t first = 0; first < points.size(); ++first) {
        for (size_t second = first + 1; second < points.size(); ++second) {
            for (size_t third = second + 1; third < points.size(); ++third) {
                int temp = pow((points[first].x - points[second].x), 2) + pow((points[first].y - points[second].y), 2);
                if (temp < max_rad) {
                    break;
                }
                temp = std::min(temp, (points[third].x - points[second].x) * (points[third].x - points[second].x) + (points[third].y - points[second].y) * (points[third].y - points[second].y));
                temp = std::min(temp, (points[first].x - points[third].x) * (points[first].x - points[third].x) + (points[first].y - points[third].y) * (points[first].y - points[third].y));
                max_rad = std::max(max_rad, temp);
            }
        }
    }
    return sqrt(max_rad) / 2;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int num;
    std::cin >> num;
    std::vector<Point> points;
    for (size_t i = 0; i < num; ++i) {
        int tempx, tempy;
        std::cin >> tempx >> tempy;
        points.push_back(Point(tempx, tempy));
    }

    std::cout << std::setprecision(7) << radius(points);

    return 0;
}