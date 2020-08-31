#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>

// https://www.tutorialspoint.com/Closest-Pair-of-Points-Problem
typedef struct {
	int x;
	int y;
} Point;

typedef struct {
	Point a;
	Point b;
	double dist;
} Pair;

typedef std::vector<Point>::iterator It;
double calcDist(Point a, Point b);
Pair bruteClosest(const std::vector<Point>& v);
Pair bruteClosest(It start, It End);
void printPoints(std::vector<Point> v);
Pair minimalDistance(It SxStart, It SxEnd, It SyStart, It SyEnd, double d);
double minimalDistance(std::vector<Point> points); 


// Consider d to be infinity if d == -1
Pair minimalDistance(It SxStart, It SxEnd, It SyStart, It SyEnd, double d)
{
	// Determine limits
	auto size = std::distance(SxStart, SxEnd);
	auto median = std::next(SxStart, size / 2);
	if (size < 3) {
		return bruteClosest(SxStart, SxEnd);
	}
	std::cout << "(" << median->x << ", " << median->y << ")\n";
	return bruteClosest(SxStart, SxEnd);
	// Partition
	
	// Merge

}


double minimalDistance(std::vector<Point> points) 
{
//	Pair closest = bruteClosest(points);
	sort(points.begin(), points.end(), [](const Point& a, const Point& b) { return a.x < b.x; });
	std::vector<Point> Sx = points;
	sort(points.begin(), points.end(), [](const Point& a, const Point& b) { return a.y < b.y; });
	std::vector<Point> Sy = points;
	
	Pair closest = minimalDistance(Sx.begin(), Sx.end(), Sy.begin(), Sy.end(), -1);
	return closest.dist;
}

int main() {
	size_t n;
	std::cin >> n;
	std::vector<Point> points(n);
	for (size_t i = 0; i < n; i++) {
		std::cin >> points[i].x >> points[i].y;
	}
	std::cout << std::fixed;
	std::cout << std::setprecision(9) << minimalDistance(points) << "\n";
}

Pair bruteClosest(It start, It end)
{
	Pair closest = {};
	double minDist = -1;
	for (It i = start; i != end; i++) {
		for (It j = i + 1; j != end; j++) {
			double currentDist = calcDist(*i, *j);
			if (currentDist < minDist || minDist == -1) {
				closest.a = *i;
				closest.b = *j;
				closest.dist = currentDist;
				minDist = currentDist;
			}
		}	
	}
	return closest;
}

Pair bruteClosest(const std::vector<Point>& v)
{
	Pair closest = {};
	double minDist = -1;
	for (size_t i = 0; i < v.size(); i++) {
		for (size_t j = i + 1; j < v.size(); j++) {
			double currentDist = calcDist(v[i], v[j]);
			if (currentDist < minDist || minDist == -1) {
				closest.a = v[i];
				closest.b = v[j];
				closest.dist = currentDist;
				minDist = currentDist;
			}
		}
	}
	return closest;
}

double calcDist(Point a, Point b)
{
	return pow(pow(a.x - b.x, 2) + pow(a.y - b.y, 2), 0.5);
}

void printPoints(std::vector<Point> v)
{
	for (auto& el : v) {
		std::cout << "( " << el.x << ", " << el.y << " )\n";
	}
}
