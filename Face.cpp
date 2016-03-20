#include "Face.h"
#include "FrameBuffer.cpp"

Face::Face() {

}

Face::Face(map<string, vector<Point> > curves) {
	int d = 0.01;
	vector<Point> temp;

	//0
	temp = curves.find("head")->second;
	head = Curve(temp, d);
	face.push_back(head);
	normal_exp.push_back(head);
	
	//1
	temp.clear();
	temp = curves.find("nose")->second;
	nose = Curve(temp, d);
	face.push_back(nose);
	normal_exp.push_back(nose);
	
	//2
	temp.clear();
	temp = curves.find("right_eyebrow")->second;
	eyebrows.push_back(Curve(temp, d));
	face.push_back(Curve(temp, d));
	normal_exp.push_back(Curve(temp, d));

	//3
	temp.clear();
	temp = curves.find("left_eyebrow")->second;
	eyebrows.push_back(Curve(temp, d));
	face.push_back(Curve(temp, d));
	normal_exp.push_back(Curve(temp, d));

	//4
	temp.clear();
	temp = curves.find("right_upper_eyelid")->second;
	eyes.push_back(Curve(temp, d));
	face.push_back(Curve(temp, d));
	normal_exp.push_back(Curve(temp, d));

	//5
	temp.clear();
	temp = curves.find("right_lower_eyelid")->second;
	eyes.push_back(Curve(temp, d));
	face.push_back(Curve(temp, d));
	normal_exp.push_back(Curve(temp, d));

	//6
	temp.clear();
	temp = curves.find("left_upper_eyelid")->second;
	eyes.push_back(Curve(temp, d));
	face.push_back(Curve(temp, d));
	normal_exp.push_back(Curve(temp, d));

	//7
	temp.clear();
	temp = curves.find("left_lower_eyelid")->second;
	eyes.push_back(Curve(temp, d));
	face.push_back(Curve(temp, d));
	normal_exp.push_back(Curve(temp, d));

	//8
	temp.clear();
	temp = curves.find("upper_lip")->second;
	lips.push_back(Curve(temp, d));
	face.push_back(Curve(temp, d));
	normal_exp.push_back(Curve(temp, d));

	//9
	temp.clear();
	temp = curves.find("lower_lip")->second;
	lips.push_back(Curve(temp, d));
	face.push_back(Curve(temp, d));
	normal_exp.push_back(Curve(temp, d));
	
	temp.clear();
	temp = curves.find("hair")->second;
	lips.push_back(Curve(temp, d));
	face.push_back(Curve(temp, d));
	normal_exp.push_back(Curve(temp, d));

	temp.clear();
	temp = curves.find("lip_tag")->second;
	tags.insert(std::pair<std::string, vector<Point> >("lipTag", temp));


	temp.clear();
	temp = curves.find("laugh_tag")->second;
	tags.insert(std::pair<std::string, vector<Point> >("laughTag", temp));


	temp.clear();
	temp = curves.find("eye_tag")->second;
	tags.insert(std::pair<std::string, vector<Point> >("eyeTag", temp));
}

Face::Face(const Face& f) {
	this->head = f.head;
	this->nose = f.nose;
	this->face = f.face;
	this->lips = f.lips;
    this->eyes = f.eyes;
    this->eyebrows = f.eyebrows;
    this->eyeballs = f.eyeballs;
    this->normal_exp = f.normal_exp;
   	this->tags = f.tags;
}

Face& Face::operator=(const Face& f) {
	this->head = f.head;
	this->nose = f.nose;
	this->face = f.face;
	this->lips = f.lips;
    this->eyes = f.eyes;
    this->eyebrows = f.eyebrows;
    this->eyeballs = f.eyeballs;
   	this->normal_exp = f.normal_exp;
   	this->tags = f.tags;

    return *this;
}

void Face::moveHead(string dir, float d) {
	if (dir.compare("up")==0) {
		head.moveUp(d);
	} else if (dir.compare("down")==0) {
		head.moveDown(d);
	} else if (dir.compare("right")==0) {
		head.moveRight(d);
	} else if (dir.compare("left")==0) {
		head.moveLeft(d);
	}
}

void Face::moveNose(string dir, float d) {
	if (dir.compare("up")==0) {
		nose.moveUp(d);
	} else if (dir.compare("down")==0) {
		nose.moveDown(d);
	} else if (dir.compare("right")==0) {
		nose.moveRight(d);
	} else if (dir.compare("left")==0) {
		nose.moveLeft(d);
	}
}

void Face::smile(float dy) {
	face.clear();

	face.push_back(normal_exp.at(0));
	face.push_back(normal_exp.at(1));
	face.push_back(normal_exp.at(2));
	face.push_back(normal_exp.at(3));
	face.push_back(normal_exp.at(4));
	face.push_back(normal_exp.at(5));
	face.push_back(normal_exp.at(6));
	face.push_back(normal_exp.at(7));
	face.push_back(normal_exp.at(10));
	
	vector<Point> temp;
	temp = tags.find("lipTag")->second;
	for (int x=0; x<2; x++) {
		Curve curve = lips.at(x);
		for (int i=0; i<temp.size(); i++) {
			for (int j=0; j<curve.points.size(); j++) {
				if (temp.at(i).x == curve.points.at(j).x &&
					temp.at(i).x == curve.points.at(j).x) {
						curve.points.at(j).y -= dy;
				}
			}
		}
		curve.computeFinals();
		face.push_back(curve);
	}
}

void Face::laugh(float dy) {
	face.clear();

	face.push_back(normal_exp.at(0));
	face.push_back(normal_exp.at(1));
	face.push_back(normal_exp.at(2));
	face.push_back(normal_exp.at(3));
	face.push_back(normal_exp.at(4));
	face.push_back(normal_exp.at(5));
	face.push_back(normal_exp.at(6));
	face.push_back(normal_exp.at(7));
	face.push_back(normal_exp.at(10));
	//yang berubah mulutnya	
	vector<Point> temp;
	temp = tags.find("laughTag")->second;
	Curve curve = lips.at(1);
	for (int i=0; i<temp.size(); i++) {
		for (int j=0; j<curve.points.size(); j++) {
			if (temp.at(i).x == curve.points.at(j).x &&
				temp.at(i).x == curve.points.at(j).x) {
					curve.points.at(j).y += dy;
			}
		}
	}
	curve.computeFinals();
	face.push_back(curve);
}

void Face::cry(float eye, float mouth) {
	face.clear();

	face.push_back(normal_exp.at(0));
	face.push_back(normal_exp.at(1));
	face.push_back(normal_exp.at(2));
	face.push_back(normal_exp.at(3));
	face.push_back(normal_exp.at(10));

	//yang berubah mulut dan mata; eyeball diilangin

	vector<Point> temp;
	temp = tags.find("lipTag")->second;
	for (int x=0; x<2; x++) {
		Curve curve = lips.at(x);
		for (int i=0; i<temp.size(); i++) {
			for (int j=0; j<curve.points.size(); j++) {
				if (temp.at(i).x == curve.points.at(j).x &&
					temp.at(i).x == curve.points.at(j).x) {
						curve.points.at(j).y += mouth;
				}
			}
		}
		curve.computeFinals();
		face.push_back(curve);
	}

	temp = tags.find("eyeTag")->second;
	for (int x=0; x<4; x++) {
		Curve curve = eyes.at(x);
		for (int i=0; i<temp.size(); i++) {
			for (int j=0; j<curve.points.size(); j++) {
				if (temp.at(i).x == curve.points.at(j).x &&
					temp.at(i).x == curve.points.at(j).x) {
						curve.points.at(j).y += eye;
				}
			}
		}

		curve.computeFinals();
		face.push_back(curve);
	}
}

void Face::eyesClosed() {
	face.clear();

	face.push_back(normal_exp.at(0));
	face.push_back(normal_exp.at(1));
	face.push_back(normal_exp.at(2));
	face.push_back(normal_exp.at(3));
	face.push_back(normal_exp.at(5));
	face.push_back(normal_exp.at(7));
	face.push_back(normal_exp.at(8));
	face.push_back(normal_exp.at(9));
	face.push_back(normal_exp.at(10));

	//yang berubah matanya; eyeball diilangin
}

void Face::wink() {
	face.clear();

	face.push_back(normal_exp.at(0));
	face.push_back(normal_exp.at(1));
	face.push_back(normal_exp.at(2));
	face.push_back(normal_exp.at(3));
	face.push_back(normal_exp.at(4));
	face.push_back(normal_exp.at(5));
	face.push_back(normal_exp.at(6));
	face.push_back(normal_exp.at(8));
	face.push_back(normal_exp.at(9));
	face.push_back(normal_exp.at(10));
}

void Face::normalExpression() {
	face.clear();

	for(int i=0;i<normal_exp.size();i++) {
		face.push_back(normal_exp.at(i));	
	}

}

void Face::drawFace() {
	FrameBuffer FB;
	for(int i=0; i< face.size(); i++) {
		FB.drawCurve(face.at(i), 0, 0, 0, 0);
	}
}