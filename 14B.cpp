#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

const double zero = 1e-20;

struct Point {
    double x = 0;
    double y = 0;

    Point(const double& new_x, const double& new_y) {
        x = new_x;
        y = new_y;
    }
};

Point direct_vector(const std::vector<double>& cf) {
    return Point(cf[0], cf[1]);
}

std::vector<double> pointcross_dist(const std::vector<double>& cf1, const std::vector<double>& cf2) {
    if (abs(cf1[0]) <= zero && abs(cf2[0]) <= zero) {
        return { abs(cf1[2] / cf1[1] - cf2[2] / cf2[1]) };
    }
    if (abs(cf1[1]) <= zero && abs(cf2[1]) <= zero) {
        return { abs(cf1[2] / cf1[0] - cf2[2] / cf2[0]) };
    }
    if (abs(cf1[0] * cf2[1] - cf2[0] * cf1[1]) <= zero) {
        return { abs((cf2[1] * (-cf1[2] / cf1[1]) + cf2[2]) / sqrt(cf2[0] * cf2[0] + cf2[1] * cf2[1])) };
    }
    else {
        if (abs(cf1[0]) <= zero) {
            double coord_y = -1 * cf1[2] / cf1[1];
            double coord_x = -1 * (cf2[2] + cf2[1] * coord_y) / cf2[0];
            return { coord_x, coord_y };
        }
        if (abs(cf2[0]) <= zero) {
            double coord_y = -1 * cf2[2] / cf2[1];
            double coord_x = -1 * (cf1[2] + cf1[1] * coord_y) / cf1[0];
            return { coord_x, coord_y };
        }
        if (abs(cf1[1]) <= zero) {
            double coord_x = -1 * cf1[2] / cf1[0];
            double coord_y = -1 * (cf2[2] + cf2[0] * coord_x) / cf2[1];
            return { coord_x, coord_y };
        }
        if (abs(cf2[1]) <= zero) {
            double coord_x = -1 * cf2[2] / cf2[0];
            double coord_y = -1 * (cf1[2] + cf1[0] * coord_x) / cf1[1];
            return { coord_x, coord_y };
        }
        double coord_y = (cf2[0] * cf1[2] - cf1[0] * cf2[2]) / (cf1[0] * cf2[1] - cf2[0] * cf1[1]);
        double coord_x = -1 * (cf1[2] + cf1[1] * coord_y) / cf1[0];
        return { coord_x, coord_y };
    }
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::vector<double> equation1(3);
    std::vector<double> equation2(3);
    for (size_t i = 0; i < 3; ++i) {
        std::cin >> equation1[i];
    }
    for (size_t i = 0; i < 3; ++i) {
        std::cin >> equation2[i];
    }

    Point dir_vec1 = direct_vector(equation1);
    Point dir_vec2 = direct_vector(equation2);

    std::cout << -1 * dir_vec1.y << " " << dir_vec1.x << std::endl;
    std::cout << -1 * dir_vec2.y << " " << dir_vec2.x << std::endl;

    std::vector<double> pointcross_dist_vec = pointcross_dist(equation1, equation2);
    for (size_t i = 0; i < pointcross_dist_vec.size(); ++i) {
        std::cout << std::setprecision(7) << pointcross_dist_vec[i] << " ";
    }

    return 0;
}