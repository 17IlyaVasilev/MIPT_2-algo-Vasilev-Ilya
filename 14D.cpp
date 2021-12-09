#include <iostream>
#include <vector>
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
    if (cross_product(first_vec, second_vec) == 0) {
        return 0;
    }
    if (cross_product(first_vec, second_vec) > 0) {
        return 1;
    }
    return -1;
}

bool convex(const std::vector<Point>& points) {
    Point prev = points[points.size() - 2];
    Point last = points[points.size() - 1];
    bool flag = true;
    int sign = 2;
    for (size_t i = 0; i < points.size(); ++i) {
        if (sign == 2) {
            long long temp = side(prev, last, points[i]);
            if (temp != 0) {
                sign = temp;
            }
        }
        else {
            long long temp = side(prev, last, points[i]);
            if (temp != 0 && temp != sign) {
                flag = false;
                break;
            }
        }
        prev = last;
        last = points[i];
    }

    return flag;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    long long num;
    std::cin >> num;
    std::vector<Point> points;
    for (size_t i = 0; i < num; ++i) {
        long long tempx, tempy;
        std::cin >> tempx >> tempy;
        points.push_back(Point(tempx, tempy));
    }

    if (convex(points)) {
        std::cout << "YES";
    }
    else {
        std::cout << "NO";
    }

    return 0;
}