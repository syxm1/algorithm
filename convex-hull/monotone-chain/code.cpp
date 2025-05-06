#include <vector>
#include <algorithm>

struct pt {
	int x, y;
	bool operator<(const pt &p) const { return x == p.x ? y < p.y : x < p.x; }
	bool operator==(const pt &p) const { return x == p.x && y == p.y; }
};

int cross_product(pt a, pt b, pt c) {
	return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
}

int orientation(pt a, pt b, pt c) {
	int cross = cross_product(a, b, c);
	if (cross < 0) return -1; // clockwise
	if (cross > 0) return 1; // counter-clockwise
	return 0;
}

std::vector<pt> build_lower_hull(std::vector<pt> &V) {
  std::vector<pt> lower;
	for (int i = 0; i < (int)V.size(); i++) {
		while (lower.size() >= 2 && orientation(lower[lower.size() - 2], lower[lower.size() - 1], V[i]) <= 0)
			lower.pop_back();
		lower.push_back(V[i]);
	}
	return lower;
}

std::vector<pt> build_upper_hull(std::vector<pt> &V) {
  std::vector<pt> upper;
	for (int i = (int)V.size() - 1; i >= 0; i--) {
		while (upper.size() >= 2 && orientation(upper[upper.size() - 2], upper[upper.size() - 1], V[i]) <= 0)
			upper.pop_back();
		upper.push_back(V[i]);
	}
	return upper;
}

std::vector<pt> build_convex_hull(std::vector<pt> &V) {
  std::sort(V.begin(), V.end());
	V.erase(std::unique(V.begin(), V.end()), V.end());
	if (V.size() < 3) return V;
  std::vector<pt> lower = build_lower_hull(V);
  std::vector<pt> upper = build_upper_hull(V);
	lower.insert(lower.end(), upper.begin() + 1, upper.end() - 1); // Avoid duplicating the endpoints
	return lower;
}
