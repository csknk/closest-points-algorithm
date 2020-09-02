#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>

// https://www.tutorialspoint.com/Closest-Pair-of-Points-Problem
struct Point {
	int x;
	int y;
};
bool operator==(const Point& lhs, const Point& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y ? true : false;
}

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
Pair minimalDistance(It SxStart, It SxEnd, std::vector<Point>& Sy);
Pair minimalSplitDistance(std::vector<Point>& Sy, double delta, double midPoint);
double minimalDistance(std::vector<Point> points); 

#ifdef STRESS_TEST
#include "stress-test.h"
#endif

Pair minimalSplitDistance(std::vector<Point>& Sy, double delta, double midPoint)
{
	std::vector<Point> lessThanDelta;
	for (size_t i = 0, j = 0; i < Sy.size(); i++) {
		if (abs(Sy[i].x - midPoint) > delta) {
			continue;
		}
		lessThanDelta.push_back(Sy[i]);
	}
	if (lessThanDelta.size() <= 1) {
		return Pair {{0,0}, {0,0}, -1};
	} 
	double minDist = -1;
	Pair closest;
	for (size_t i = 0; i < lessThanDelta.size(); i++) {
		for (size_t j = i + 1; j < i + 7 && j < lessThanDelta.size(); j++) {
			double currentDist = calcDist(lessThanDelta[i], lessThanDelta[j]);
			if (currentDist < minDist || minDist == -1) {
				closest.a = lessThanDelta[i];
				closest.b = lessThanDelta[j];
				closest.dist = currentDist;
				minDist = currentDist;
			}
		} 
	}
	return closest;
}

Pair minimalDistance(It SxStart, It SxEnd, std::vector<Point>& Sy)
{
	// Base case
	auto size = std::distance(SxStart, SxEnd);
	if (size == 1) {
		return Pair {*SxStart, Point{999, 999}, -1}; 
	}
	if (size < 3) {
		double d = calcDist(*SxStart, *std::next(SxStart));
		return Pair {*SxStart, *std::next(SxStart), d};
	}
	if (size <= 4) {
		return bruteClosest(SxStart, SxEnd); 
	}

	// Determine limits
	auto median = std::next(SxStart, size / 2);
	double midPoint = ((double)std::prev(median)->x + (double)median->x) / 2;

	// Partition
	auto dl = minimalDistance(SxStart, median, Sy);
	auto dr = minimalDistance(median, SxEnd, Sy);

	Pair closestIntermediate;
	if (dl.dist == -1 && dr.dist != -1) {
		closestIntermediate = dr;
	} else if (dr.dist == -1 && dl.dist != -1) {
		closestIntermediate = dl;
	} else {
		closestIntermediate = dl.dist < dr.dist ? dl : dr;
	}
	auto delta = closestIntermediate.dist;
	auto ds = minimalSplitDistance(Sy, delta, midPoint);

	// Merge
	if (ds.dist == -1) {
		return closestIntermediate;
	} 
	auto result = delta < ds.dist ? closestIntermediate : ds; 
	return result;
}

double minimalDistance(std::vector<Point> points) 
{
	sort(points.begin(), points.end(), [](const Point& a, const Point& b) { return a.x < b.x; });
	const bool hasAdjacent = std::adjacent_find(points.begin(), points.end()) != points.end();
	if (hasAdjacent) {
		return .0;
	}
//	It i = std::adjacent_find(points.begin(), points.end());
//	if (i != points.end()) {
//		return .0;
//	}
	std::vector<Point> Sx = points;
	sort(points.begin(), points.end(), [](const Point& a, const Point& b) { return a.y < b.y; });
	std::vector<Point> Sy = points;
	Pair closest = minimalDistance(Sx.begin(), Sx.end(), Sy);
	//	std::cout << "Closest Pair: ";
	//	std::cout << "(" << closest.a.x << ", " << closest.a.y << "), ";
	//	std::cout << "(" << closest.b.x << ", " << closest.b.y << ")\n";

	return closest.dist;
}

int main() {
#ifdef STRESS_TEST
	stressTest(static_cast<double (*)(std::vector<Point>)>(&minimalDistance), false);
#else
	size_t n;
	std::cin >> n;
	std::vector<Point> points(n);
	for (size_t i = 0; i < n; i++) {
		std::cin >> points[i].x >> points[i].y;
	}
	std::cout << std::fixed;
	std::cout << std::setprecision(9) << minimalDistance(points) << "\n";
#endif
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
