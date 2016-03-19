#include "Curve.h"


Curve::Curve(){

}

Curve::Curve(vector<Point> p, float delta){
	for (int i = 0; i< p.size(); i++){
		points.push_back(p.at(i));
	}
	d = delta;
	computeFinals();
}

Curve& Curve::operator=(const Curve& c){
	this->d = c.d;
	this->pFinal = c.pFinal;
	this->points = c.points;
	this->finals = c.finals;

	return *this;
}

Curve::~Curve(){
	points.clear();
	finals.clear();
}

int Curve::getMinX() {
	int i=1;
	int minX=points[0].x;
	while(i<points.size()) {
		if(points[i].x<minX) {
			minX=points[i].x;
		}
		i++;
	}
	return minX;
}

int Curve::getMaxX() {
	int i=1;
	int maxX=points[0].x;
	while(i<points.size()) {
		if(points[i].x>maxX) {
			maxX=points[i].x;
		}
		i++;
	}
	return maxX;
}

int Curve::getMinY() {
	int i=1;
	int minY=points[0].y;
	while(i<points.size()) {
		if(points[i].y<minY) {
			minY=points[i].y;
		}
		i++;
	}
	return minY;
}

int Curve::getMaxY() {
	int i=1;
	int maxY=points[0].y;
	while(i<points.size()) {
		if(points[i].y>maxY) {
			maxY=points[i].y;
		}
		i++;
	}
	return maxY;
}

int Curve::getMidX() {
	return (getMaxX() + getMinX())/2;
}

int Curve::getMidY() {
	return (getMaxY() + getMinY())/2;
}

void Curve::moveRight(float dx) {
	int i=0;
	while(i < points.size()) {
		points[i].x+=dx;
		i++;
	}
	computeFinals();
}

void Curve::moveLeft(float dx) {
	int i=0;
	while(i < points.size()) {
		points[i].x-=dx;
		i++;
	}
	computeFinals();
}


void Curve::moveUp(float dy) {
	int i=0;
	while(i < points.size()) {
		points[i].y-=dy;
		i++;
	}
	computeFinals();
}

void Curve::moveDown(float dy) {
	int i=0;
	while(i < points.size()) {
		points[i].y+=dy;
		i++;
	}
	computeFinals();
}

void Curve::scale(float k) {
	for (int i=0;i<points.size();i++) {
        points[i].x = points[i].x*k;
        points[i].y = points[i].y*k;
    }
    computeFinals();
}

void Curve::rotate(double deg) {
	int i=0;
	double cons=0.0174532925; double tempx,tempy;

	while(i < points.size()) {
		tempx= ((cos(deg*cons)*(points[i].x - points[0].x)) - (sin(deg*cons)*(points[i].y - points[0].y)) + points[0].x)+0.5;
		tempy= ((sin(deg*cons)*(points[i].x - points[0].x)) + (cos(deg*cons)*(points[i].y - points[0].y)) + points[0].y)+0.5;
		points[i].x = tempx;
		points[i].y = tempy;
		i++;
	}
	computeFinals();
}

void Curve::rotateCenter(double deg) {
	int i=0;
	double cons=0.0174532925; double tempx,tempy;

	int centerX=getMidX(), centerY=getMidY();

	while(i < points.size()) {
		tempx= ((cos(deg*cons)*(points[i].x - centerX)) - (sin(deg*cons)*(points[i].y - centerY)) + centerX) + 0.5;
		tempy= ((sin(deg*cons)*(points[i].x - centerX)) + (cos(deg*cons)*(points[i].y - centerY)) + centerY) + 0.5;
		points[i].x = tempx;
		points[i].y = tempy;
		i++;
	}
}

void Curve::computeFinals(){
	float t=0;
	finals.clear();
	finals.push_back(points.at(0));
	pFinal.x = points.at(0).x;
	pFinal.y = points.at(0).y;

	while (t<1){
		pFinal = bezierCurve(t);
		finals.push_back(pFinal);
		t+=d;
	}

	finals.push_back(points.at(points.size()-1));
}

Point Curve::quadraticBezier(float t){ 
	// Buat quadratic curve p0: source; p1: control; p2: destination
	// Masih nggak ngerti caranya kalo curvenya lebih dr quadratic
	Point p;
	p.x = (int) (1 * pow (1 - t, 2) * pow (t,0) * points.at(0).x + 
				2 * pow (1 - t, 1) * pow (t,1) * points.at(1).x + 
				1 * pow (1 - t, 0) * pow (t,2) * points.at(2).x);
	p.y = (int) (1 * pow (1 - t, 2) * pow (t,0) * points.at(0).y + 
				2 * pow (1 - t, 1) * pow (t,1) * points.at(1).y + 
				1 * pow (1 - t, 0) * pow (t,2) * points.at(2).y);
	return p;
}

Point Curve::cubicBezier(float t){
	Point p;
	p.x = (int) (1 * pow(1 - t, 3) * pow (t,0) * points.at(0).x + 
				3 * pow(1 - t, 2) * pow (t,1) * points.at(1).x + 
				3 * pow(1 - t, 1) * pow (t,2) * points.at(2).x + 
				1 * pow(1 - t, 0) * pow (t,3) * points.at(3).x);
	p.y = (int) (1 * pow(1 - t, 3) * pow (t,0) * points.at(0).y + 
				3 * pow(1 - t, 2) * pow (t,1) * points.at(1).y + 
				3 * pow(1 - t, 1) * pow (t,2) * points.at(2).y + 
				1 * pow(1 - t, 0) * pow (t,3) * points.at(3).y);
	return p;
}

Point Curve::fourBezier(float t){
	Point p;
	p.x = (int) (1* pow(1 - t, 4) * pow (t,0)* points.at(0).x + 
				4 * pow(1 - t, 3) * pow(t,1) * points.at(1).x + 
				6 * pow(1 - t, 2) * pow(t,2) * points.at(2).x + 
				4 * pow(1 - t, 1) * pow(t,3) * points.at(3).x +
				1 * pow(1 - t, 0) * pow(t,4) * points.at(4).x);
	p.y = (int) (1* pow(1 - t, 4) * pow (t,0)* points.at(0).y + 
				4 * pow(1 - t, 3) * pow(t,1) * points.at(1).y + 
				6 * pow(1 - t, 2) * pow(t,2) * points.at(2).y + 
				4 * pow(1 - t, 1) * pow(t,3) * points.at(3).y +
				1 * pow(1 - t, 0) * pow(t,4) * points.at(4).y);
	return p;
}

Point Curve::bezierCurve(float t){
	Point p;
	p.x = 0;
	p.y = 0;

	vector<int> coef = pascalTriangle(points.size()-1);

	for (int i=0; i < points.size(); i++){
		p.x += coef.at(i) * pow(1 - t, (points.size()-1-i)) * pow(t, i)* points.at(i).x;
		p.y += coef.at(i) * pow(1 - t, (points.size()-1-i)) * pow(t, i)* points.at(i).y;
	}

	return p;
}

vector<int> Curve::pascalTriangle(int n) {
	vector<int> temp;
	for(int i = 0; i <= n; i++) {
		int x=1;
		for(int k = 0; k <= i; k++) {
			if (i == n) temp.push_back(x);
			x = x * (i - k) / (k + 1);
		}
	}
	return temp;
}

