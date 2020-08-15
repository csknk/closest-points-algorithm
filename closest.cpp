#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>

using std::vector;
using std::string;
using std::pair;
using std::min;

typedef struct {
	int x;
	int y;
	double distFromOrigin;
} Point;

double calcDist(Point a, Point b)
{
	return pow(pow(a.x - b.x, 2) + pow(a.y - b.y, 2), 0.5);
}

double minimal_distance(vector<int> x, vector<int> y) 
{
	std::vector<Point> points(x.size());

	for (size_t i = 0; i < x.size(); i++) {
		double d = pow(pow(x[i], 2) + pow(y[i], 2), 0.5);
		points[i] = {x[i], y[i], d};
	}

	sort(points.begin(), points.end(), [](const Point& a, const Point& b) { return a.x < b.x;});
	sort(points.begin(), points.end(), [](const Point& a, const Point& b) { return a.y < b.y;});

//	for (auto& el : points) {
//		std::cout << "( " << el.x << ", " << el.y << ", " << el.distFromOrigin << " )\n";
//	}

	// If the pair of points are separated by a dist < minDist update minDist
	double minDiff = calcDist(points[0], points[1]);
	double currentDiff = minDiff;
	std::vector<Point> closest(2);
	closest[0] = points[0];
	closest[1] = points[1];
	for (size_t i = 1; i < points.size() - 1; i++) {
		if (points[i].distFromOrigin == points[i + 1].distFromOrigin)
			return 0.;
		currentDiff = calcDist(points[i], points[i + 1]);
		if (currentDiff < minDiff) {
			closest[0] = points[i];
			closest[1] = points[i + 1];
			minDiff = currentDiff;
		}
	}

//	for (auto& el : closest) {
//		std::cout << "( " << el.x << ", " << el.y << ", " << el.distFromOrigin << " )\n";
//	}

	return calcDist(closest[0], closest[1]);//minDist;
}

int main() {
	size_t n;
	std::cin >> n;
	vector<int> x(n);
	vector<int> y(n);
	for (size_t i = 0; i < n; i++) {
		std::cin >> x[i] >> y[i];
	}
	std::cout << std::fixed;
	std::cout << std::setprecision(9) << minimal_distance(x, y) << "\n";
}
