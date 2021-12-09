#include<iostream>
#include <vector>
#include <algorithm>
#include<vector>

struct Point {
	long long x = 0;
	long long y = 0;

	Point(const long long& new_x, const long long& new_y) {
		x = new_x;
		y = new_y;
	}

	double len2() const { return x * x + y * y; }
};

Point operator+ (Point a, Point b) {
	return Point(a.x + b.x, a.y + b.y);
}

Point operator- (Point a, Point b) {
	return Point(a.x - b.x, a.y - b.y);
}

int TurnLeft(Point a, Point b, Point c) {
	Point p = b - a, q = c - b;
	return p.x * q.y > q.x * p.y;
}

bool cmp(Point a, Point b) {
	if (a.x * b.y == b.x * a.y) {
		return a.len2() < b.len2();
	}
	return a.x * b.y > b.x * a.y;
}

std::pair<size_t, std::vector<Point>> convex_hull(const std::vector<Point>& points) {
	size_t num = points.size();
	std::vector<Point> hull = points;
	for (size_t i = 1; i < num; ++i) {
		if (hull[i].x < hull[0].x) {
			std::swap(hull[i], hull[0]);
		}
		if ((hull[i].x == hull[0].x) && (hull[i].y < hull[0].y)) {
			std::swap(hull[i], hull[0]);
		}
	}
	for (size_t i = 1; i < hull.size(); ++i) {
		hull[i] = hull[i] - hull[0];
	}
	std::sort(hull.begin() + 1, hull.end(), cmp);
	for (size_t i = 1; i < num; ++i) {
		hull[i] = hull[i] + hull[0];
	}
	hull.push_back(hull[0]);
	++num;

	size_t cur = 1;
	for (size_t i = 2; i < num; ++i) {
		while ((cur > 0) && !TurnLeft(hull[cur - 1], hull[cur], hull[i])) {
			--cur;
		}
		hull[++cur] = hull[i];
	}

	return { cur, hull };
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

	std::pair<size_t, std::vector<Point>> hull = convex_hull(points);
	std::cout << hull.first << std::endl;
	for (size_t i = 0; i < hull.first; ++i) {
		std::cout << hull.second[i].x << ' ' << hull.second[i].y << std::endl;
	}

	return 0;
}