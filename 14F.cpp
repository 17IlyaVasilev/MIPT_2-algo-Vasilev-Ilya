#include <iostream>
#include <vector>
#include <algorithm>
#include <vector>

struct Point {
  long long x = 0;
  long long y = 0;

  Point(long long new_x, long long new_y) : x(new_x), y(new_y) {}
  double len2() const { return x * x + y * y; }
};

Point operator+(Point a, Point b) { return Point(a.x + b.x, a.y + b.y); }

Point operator-(Point a, Point b) { return Point(a.x - b.x, a.y - b.y); }

int TurnLeft(Point a, Point b, Point c) {
  Point p = b - a;
  Point q = c - b;
  return p.x * q.y > q.x * p.y;
}

std::vector<Point> convex_hull(const std::vector<Point>& points) {
  size_t sz = points.size();
  std::vector<Point> hull = points;
  std::vector<Point>::iterator iter_min =
      std::min_element(hull.begin(), hull.end(), [](Point a, Point b) {
        if (a.x < b.x) {
          return true;
        }
        if ((a.x == b.x) && (a.y < b.y)) {
          return true;
        }
        return false;
      });
  hull[0] = *iter_min;
  *iter_min = points[0];

  for (size_t i = 1; i < sz; ++i) {
    hull[i] = hull[i] - hull[0];
  }
  std::sort(hull.begin() + 1, hull.end(), [](Point a, Point b) {
    long long ax_m_by = a.x * b.y;
    long long bx_m_ay = b.x * a.y;
    if (ax_m_by == bx_m_ay) {
      return a.len2() < b.len2();
    }
    return ax_m_by > bx_m_ay;
  });

  for (size_t i = 1; i < sz; ++i) {
    hull[i] = hull[i] + hull[0];
  }
  hull.emplace_back(hull[0]);
  ++sz;

  size_t cur = 1;
  for (size_t i = 2; i < sz; ++i) {
    while ((cur > 0) && !TurnLeft(hull[cur - 1], hull[cur], hull[i])) {
      --cur;
    }
    hull[++cur] = hull[i];
  }

  while (hull.size() > cur) {
    hull.pop_back();
  }

  return hull;
}

std::vector<Point> read(std::istream& in = std::cin) {
  in.tie(nullptr);
  long long num;
  in >> num;
  std::vector<Point> points;
  for (size_t i = 0; i < num; ++i) {
    long long tempx, tempy;
    in >> tempx >> tempy;
    points.emplace_back(Point(tempx, tempy));
  }

  return points;
}

void print(const std::vector<Point>& hull, std::ostream& out = std::cout) {
  out.tie(nullptr);
  out << hull.size() << std::endl;
  for (size_t i = 0; i < hull.size(); ++i) {
    out << hull[i].x << ' ' << hull[i].y << std::endl;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::vector<Point> points = read();
  std::vector<Point> hull = convex_hull(points);
  print(hull);

  return 0;
}
