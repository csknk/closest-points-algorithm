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

typedef std::vector<Point>::iterator It;
double calcDist(Point a, Point b);
double bruteClosest(const std::vector<Point>& v);
double bruteClosest(It start, It End);
void printPoints(std::vector<Point> v);
double minimalDistance(It SxStart, It SxEnd, std::vector<Point>& Sy);
double minimalSplitDistance(std::vector<Point>& Sy, double delta, double midPoint);
double minimalDistance(std::vector<Point> points); 

#ifdef STRESS_TEST
#include "stress-test.h"
#endif

double minimalSplitDistance(std::vector<Point>& Sy, double delta, double midPoint)
{
	double minDist = -1;
	std::vector<Point> strip;
	for (size_t i = 0; i < Sy.size(); i++) {
		if (abs(Sy[i].x - midPoint) > delta) {
			continue;
		}
		strip.push_back(Sy[i]);		
	}
	if (strip.size() < 2) {
		return minDist;
	}
	
	for (size_t i = 0; i < strip.size(); i++) {
		for (size_t j = i + 1; j <= i + 7 && j < strip.size(); j++) {
			double currentDist = calcDist(Sy[i], Sy[j]);
			if (currentDist < minDist || minDist == -1) {
				minDist = currentDist;
			}
		} 
	}
	return minDist;
}

double minimalDistance(It SxStart, It SxEnd, std::vector<Point>& Sy)
{
	// Base case
	auto size = std::distance(SxStart, SxEnd);
	if (size == 1) {
		return -1; 
	}
	if (size < 3) {
		return calcDist(*SxStart, *std::next(SxStart));
	}
//	if (size <= 4) {
//		return bruteClosest(SxStart, SxEnd); 
//	}

	// Determine limits
	auto median = std::next(SxStart, size / 2);
	double midPoint = ((double)std::prev(median)->x + (double)median->x) / 2;

	// Partition
	auto dl = minimalDistance(SxStart, median, Sy);
	auto dr = minimalDistance(median, SxEnd, Sy);

	double delta;
	if (dl == -1 && dr != -1) {
		delta = dr;
	} else if (dr == -1 && dl != -1) {
		delta = dl;
	} else {
		delta = dl < dr ? dl : dr;
	}
	auto ds = minimalSplitDistance(Sy, delta, midPoint);

	// Merge
	if (ds == -1) {
		return delta;
	} 
	auto result = delta < ds ? delta : ds; 
	return result;
}

double minimalDistance(std::vector<Point> points) 
{
	sort(points.begin(), points.end(), [](const Point& a, const Point& b) { return a.x < b.x; });
//	const bool hasAdjacent = std::adjacent_find(points.begin(), points.end()) != points.end();
//	if (hasAdjacent) {
//		return .0;
//	}
	std::vector<Point> Sx = points;
	sort(points.begin(), points.end(), [](const Point& a, const Point& b) { return a.y < b.y; });
	return minimalDistance(Sx.begin(), Sx.end(), points);
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

double bruteClosest(It start, It end)
{
	double minDist = -1;
	for (It i = start; i != end; i++) {
		for (It j = i + 1; j != end; j++) {
			double currentDist = calcDist(*i, *j);
			if (currentDist < minDist || minDist == -1) {
				minDist = currentDist;
			}
		}	
	}
	return minDist;
}

double bruteClosest(const std::vector<Point>& v)
{
	double minDist = -1;
	for (size_t i = 0; i < v.size(); i++) {
		for (size_t j = i + 1; j < v.size(); j++) {
			double currentDist = calcDist(v[i], v[j]);
			if (currentDist < minDist || minDist == -1) {
				minDist = currentDist;
			}
		}
	}
	return minDist;
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
