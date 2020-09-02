#ifndef STRESS_TEST_H
#define STRESS_TEST_H 

#include <algorithm>

void printVec(const std::vector<Point>& v, int tab);
//int bruteForce(const std::vector<int>& v);
int diff(int a, int b);

void makeTestVec(std::vector<Point>& v, int n, int maxNum)
{
		int x = 0, y = 0;
		for (int i = 0; i < n; ++i) {
			x = rand() % maxNum;
			y = rand() % maxNum;
			v[i].x = x;
			v[i].y = y;
		}
}

void stressTest(double(*driverFunc)(std::vector<Point> v), bool repeats)
{
	const int arrMaxLen = 50;
	const int maxNum = 10;	
	int count = 0;
	while (1) {
		std::string l (10, '-');
		std::cout << l << "\n";
		std::cout << "Test " << ++count << "\n";
		
		int n = rand() % (arrMaxLen - 1) + 2;
		std::cout << n << "\n";
		std::vector<Point> v(n);
		makeTestVec(v, n, maxNum);
		printVec(v, 0);

		double res = bruteClosest(v.begin(), v.end());
		double computedRes = driverFunc(v);
		if (computedRes != res) {
			std::cout << "Wrong answer:\n";
			std::cout << "TEST:\t";
			printVec(v, 0);
			std::cout << "Brute force result:\t" << res << "\n";
			std::cout << "Computed result:\t" << computedRes << "\n";

			break;
		}
		else {
			std::cout << "Answer: " << computedRes << "\tOK\n";
		}
		computedRes = -1;
	}
}

int diff(int a, int b)
{
	return (int)abs(a - b);
}

void printVec(const std::vector<Point>& v, int tab)
{
	std::string t ("\t", tab);
	std::cout << t << "[ ";
	bool first = true;
	for (const auto& el : v) {
		if (!first) {
			std::cout << ", ";
		}
		std::cout << "(" << el.x << ", " << el.y << ")";
		first = false;
	}
	std::cout << " ]\n";
}
#endif /* STRESS_TEST_H */
