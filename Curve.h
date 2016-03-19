#ifndef CURVE
#define CURVE

#include "Point.h"
#include "Line.h"
#include <math.h>

using namespace std;

class Curve {
	public:
		Curve();
		Curve(vector<Point> points, float d);
		Curve& operator=(const Curve& c);
		~Curve();

		int getMinX();
		int getMaxX();
		int getMinY();
		int getMaxY();
		int getMidX();
		int getMidY();

		void moveRight(float dx);
		void moveLeft (float dx);
		void moveUp (float dy);
		void moveDown (float dy);
		void scale(float k);
		void rotate(double deg);
		void rotateCenter(double deg);

		vector<Point> points;
		vector<Point> finals;
		Point pFinal;
		float d;

		void computeFinals();
		
	private:
		Point quadraticBezier(float t);
		Point cubicBezier(float t);
		Point fourBezier(float t);
		Point bezierCurve(float t);
		vector<int> pascalTriangle(int n);
		
};

#endif