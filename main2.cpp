#include "FrameBuffer.cpp"
#include <cstring>
#include <termios.h>
#include <fstream>
#include "assets.h"

using namespace std;

FrameBuffer FB;
bool quit = false;
vector<Polygon> peta;
Window window;
int key;

int main() {
	vector < vector <Point> > polygon;
	vector < Point > poly1;
	vector < Point > poly2;

	poly1.push_back(Point(1,1));
	poly1.push_back(Point(100,100));
	poly1.push_back(Point(1,100));
	poly1.push_back(Point(1,1));

	poly2.push_back(Point(0,0));
	poly2.push_back(Point(0,100));
	poly2.push_back(Point(100,100));
	poly2.push_back(Point(100,0));
	poly2.push_back(Point(0,0));

	polygon.push_back(poly1);
	polygon.push_back(poly2);

	vector< vector<int> > color;

	int rgb1[] = {255,255,255,0};
	int rgb2[] = {0,255,0,0};
	color.push_back(vector<int>(rgb1, rgb1 + sizeof rgb1 / sizeof rgb1[0]));
	color.push_back(vector<int>(rgb2, rgb2 + sizeof rgb2 / sizeof rgb2[0]));

	FrameBuffer FB;
	FB.clearscreen();

	FB.scanLine3D(polygon,color);
}