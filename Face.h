#ifndef FACE
#define FACE

#include "Point.h"
#include "Polygon.h"
#include "Curve.h"
#include <vector>
#include <map>
#include <string>

using namespace std;

class Face {
	public:
		Curve head;
		Curve nose;
		Curve hair;
		vector<Curve> face; // the whole thing
		vector<Curve> lips; // upper_lip and lower_lip
		vector<Curve> eyebrows; // right_eyebrows and left_eyebrows
		vector<Curve> eyes; // right_upper_eyelid, right_lower_eyelid, left_upper_eyelid and left_lower_eyelid
		vector<Curve> eyeballs; // right_eyeball and left_eyeball
		vector<Curve> normal_exp; // the whole thing when it's normal
		map<string, vector<Point> > tags;

		Face();
		Face(map<string, vector<Point> > curves);
		Face(const Face& f);
		Face& operator=(const Face& f);
		
		void drawFace();
		void moveHead(string dir, float d);
		void moveNose(string dir, float d);
		void smile(float dy);
		void laugh(float dy);
		void cry(float eye, float mouth);
		void eyesClosed();
		void wink();
		void normalExpression();

};

#endif