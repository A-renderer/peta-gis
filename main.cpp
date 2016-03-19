#include "FrameBuffer.cpp"
#include <cstring>
#include <termios.h>
#include <fstream>
#include "assets.h"

using namespace std;

FrameBuffer FB;
bool quit = false;
vector<Polygon> peta;
vector<Curve> kontur;
Window window;
int key;

int kbhit(void);
Polygon matrixToPolygon(int object[][2], int col);
Curve matrixToCurve(int object[][2], int col);
void drawMap();
void redraw();
void move(int key);
void initDraw();

// ANTI CLIPPING
vector < vector <Point> > polygons;
vector < vector <int> > colors;

View view;
Polygon map_border = matrixToPolygon(border,sizeof(border)/sizeof(*border));
Polygon p_sumatra = matrixToPolygon(sumatra,sizeof(sumatra)/sizeof(*sumatra));
Polygon p_kalimantan = matrixToPolygon(kalimantan,sizeof(kalimantan)/sizeof(*kalimantan));
Polygon p_sulawesi = matrixToPolygon(sulawesi,sizeof(sulawesi)/sizeof(*sulawesi));
Polygon p_papua = matrixToPolygon(papua,sizeof(papua)/sizeof(*papua));
Polygon p_jawa = matrixToPolygon(jawa,sizeof(jawa)/sizeof(*jawa));
Curve c_papua_1_1 = matrixToCurve(papua_1,sizeof(papua_1)/sizeof(*papua_1));
Curve c_papua_1_2 = matrixToCurve(papua_1,sizeof(papua_1)/sizeof(*papua_1));
Curve c_papua_1_3 = matrixToCurve(papua_1,sizeof(papua_1)/sizeof(*papua_1));
Curve c_papua_2_1 = matrixToCurve(papua_1,sizeof(papua_1)/sizeof(*papua_1));
Curve c_papua_2_2 = matrixToCurve(papua_1,sizeof(papua_1)/sizeof(*papua_1));
Curve c_papua_3_1 = matrixToCurve(papua_3,sizeof(papua_3)/sizeof(*papua_3));
Curve c_papua_3_2 = matrixToCurve(papua_3,sizeof(papua_3)/sizeof(*papua_3));
Curve c_papua_3_3 = matrixToCurve(papua_3,sizeof(papua_3)/sizeof(*papua_3));
Curve c_papua_4_1 = matrixToCurve(papua_4,sizeof(papua_4)/sizeof(*papua_4));
Curve c_sulawesi_1_1 = matrixToCurve(sulawesi_1,sizeof(sulawesi_1)/sizeof(*sulawesi_1));
Curve c_sulawesi_1_2 = matrixToCurve(sulawesi_1,sizeof(sulawesi_1)/sizeof(*sulawesi_1));

int main() {
	// Adjust positions of the islands
	p_sumatra.moveDown(10);
	p_jawa.scale(1.8);
	p_jawa.moveDown(265);
	p_jawa.moveRight(170);
	p_kalimantan.scale(1.55);
	p_kalimantan.moveRight(150);
	p_kalimantan.moveDown(50);
	p_sulawesi.scale(1.25);
	p_sulawesi.moveRight(320);
	p_sulawesi.moveDown(100);
	p_papua.scale(2);
	p_papua.moveRight(430);
	p_papua.moveDown(160);

	peta.push_back(p_sumatra);
	peta.push_back(p_jawa);
	peta.push_back(p_kalimantan);
	peta.push_back(p_sulawesi);
	peta.push_back(p_papua);

	//Adjust positions of the contour
	c_papua_1_1.rotate(20);
	c_papua_1_1.scale(0.6);
	c_papua_1_1.moveRight(520);
	c_papua_1_1.moveDown(174);
	c_papua_1_2.rotate(20);
	c_papua_1_2.scale(0.45);
	c_papua_1_2.moveRight(530);
	c_papua_1_2.moveDown(190);
	c_papua_1_3.rotate(20);
	c_papua_1_3.scale(0.3);
	c_papua_1_3.moveRight(540);
	c_papua_1_3.moveDown(205);
	
	c_papua_2_1.rotate(10);
	c_papua_2_1.scale(0.3);
	c_papua_2_1.moveRight(540);
	c_papua_2_1.moveDown(187);
	c_papua_2_2.rotate(10);
	c_papua_2_2.scale(0.15);
	c_papua_2_2.moveRight(550);
	c_papua_2_2.moveDown(201);

	c_papua_3_1.scale(0.7);
	c_papua_3_1.moveRight(462);
	c_papua_3_1.moveDown(172);
	c_papua_3_2.scale(0.5);
	c_papua_3_2.moveRight(465);
	c_papua_3_2.moveDown(175);
	c_papua_3_3.scale(0.3);
	c_papua_3_3.moveRight(470);
	c_papua_3_3.moveDown(180);

	c_papua_4_1.scale(0.55);
	c_papua_4_1.moveRight(491);
	c_papua_4_1.moveDown(216);

	c_sulawesi_1_1.scale(1.1);
	c_sulawesi_1_1.moveRight(336);
	c_sulawesi_1_1.moveDown(152);

	c_sulawesi_1_2.scale(0.8);
	c_sulawesi_1_2.moveRight(340);
	c_sulawesi_1_2.moveDown(154);

	kontur.push_back(c_papua_1_1);
	kontur.push_back(c_papua_1_2);
	kontur.push_back(c_papua_1_3);
	kontur.push_back(c_papua_2_1);
	kontur.push_back(c_papua_2_2);
	kontur.push_back(c_papua_3_1);
	kontur.push_back(c_papua_3_2);
	kontur.push_back(c_papua_3_3);
	kontur.push_back(c_papua_4_1);

	system("clear");

	initDraw();
	drawMap();
	
	FB.cleararea(view.P1.x,view.P1.y,view.P2.x,view.P2.y);
	FB.drawPolygon(view.pol,255,255,255,0);
	FB.drawWindow(window,255,255,255,0);

	redraw();

	while(!quit){
		if(kbhit()){
			key=getchar();
			//PANGGIL FUNGSI UNTUK REDRAW MOVEMENT
			move(key);
		}
	}

	//system("clear");

	return 0;
}

int kbhit(void) {
	struct termios oldt, newt;
	int ch;
	int oldf;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	if(ch != EOF) {
		ungetc(ch, stdin);
		return 1;
	}

	return 0;
}

Polygon matrixToPolygon(int object[][2], int col) {
	vector<Point> points;
	points.clear();
	for(int i=0;i<col;i++) {
		points.push_back(Point(object[i][0],object[i][1]));
	}
	return Polygon(points);
}

Curve matrixToCurve(int object[][2], int col) {
	vector<Point> p;
	p.clear();
	for(int i=0;i<col;i++) {
		p.push_back(Point(object[i][0],object[i][1]));
	}
	return Curve(p,0.05);
}

void drawMap() {
	int r1 = 50, g1 = 205, b1 = 50; // warna pulau
	int r2 = 124, g2 = 255, b2 = 0; // warna kontur 1
	int r3 = 255, g3 = 255, b3 = 0; // warna kontur 2
	int r4 = 255, g4 = 165, b4 = 0; // warna kontur 3
	
	FB.rasterScan(map_border,135, 206, 235, 0, 0, 599);

	FB.rasterScan(p_sumatra, r1, g1, b1, 0, p_sumatra.getMinY(), p_sumatra.getMaxY());
	FB.rasterScan(p_jawa, r1, g1, b1, 0, p_jawa.getMinY(), p_jawa.getMaxY());
	FB.rasterScan(p_kalimantan, r1, g1, b1, 0, p_kalimantan.getMinY(), p_kalimantan.getMaxY());
	FB.rasterScan(p_sulawesi, r1, g1, b1, 0, p_sulawesi.getMinY(), p_sulawesi.getMaxY());

	FB.rasterScan(p_papua, r1, g1, b1, 0, p_papua.getMinY(), p_papua.getMaxY());

	FB.rasterScan(c_papua_2_1, r2, g2, b2,0, c_papua_2_1.getMinY(), c_papua_2_1.getMaxY());
	FB.rasterScan(c_papua_2_2, r3, g3, b3,0, c_papua_2_2.getMinY(), c_papua_2_2.getMaxY());
	FB.rasterScan(c_papua_3_1, r2, g2, b2,0, c_papua_3_1.getMinY(), c_papua_3_1.getMaxY());
	FB.rasterScan(c_papua_3_2, r3, g3, b3,0, c_papua_3_2.getMinY(), c_papua_3_2.getMaxY());
	FB.rasterScan(c_papua_3_3, r4, g4, b4,0, c_papua_3_3.getMinY(), c_papua_3_3.getMaxY());
	FB.rasterScan(c_papua_4_1, r2, g2, b2,0, c_papua_4_1.getMinY(), c_papua_4_1.getMaxY());

	FB.scanLine3D(polygons,colors);
<<<<<<< HEAD
	FB.rasterScan(c_sulawesi_1_1,r2,g2,b2,0,c_sulawesi_1_1.getMinY(), c_sulawesi_1_1.getMaxY());
	FB.rasterScan(c_sulawesi_1_2,r3,g3,b3,0,c_sulawesi_1_1.getMinY(), c_sulawesi_1_1.getMaxY());
=======

	FB.rasterScan(c_papua_1_1, r2, g2, b2,0, c_papua_1_1.getMinY(), c_papua_1_1.getMaxY());
	FB.rasterScan(c_papua_1_2, r3, g3, b3,0, c_papua_1_2.getMinY(), c_papua_1_2.getMaxY());
	FB.rasterScan(c_papua_1_3, r4, g4, b4,0, c_papua_1_3.getMinY(), c_papua_1_3.getMaxY());
>>>>>>> b977b1473aa92769e57830c519a6308232719e6f
}

void redraw() { //untuk redraw view
	vector<Polygon> temp;
	for(int i=0;i<peta.size();i++) {
		int j=0;
		bool found = false;
		while(j<peta[i].e.size() && !found) {
			if(not(peta[i].e[j].x<window.getTopLeft().x || peta[i].e[j].y<window.getTopLeft().y 
				|| peta[i].e[j].y>window.getBottomRight().y || peta[i].e[j].x>window.getBottomRight().x)) {
				found = true;
				temp.push_back(peta[i]);
			}
			j++;
		}
	}

	if(!window.lines.empty()) {
		FB.cleararea(view.P1.x,view.P1.y,view.P2.x,view.P2.y);
	}

	if(!temp.empty()) {
		window.clipAllPolygon(temp);
		if(!window.lines.empty()) {
			view.setViewLines(window);
			FB.renderView(window,view);
			//FB.rasterView(view,0,100,0,0,1,401);	
			view.lines.clear();
			window.lines.clear();
			temp.clear();
		}	
	}
}

void move(int key) {
	//system("clear");
	//int border[][2]={{0,0},{599,0},{599,400},{0,400}};
	int i = 0;
	if(key=='w'){
		while(i < 10 && window.square.getMinY() > 0) {
			window.moveUp(1);
			i++;
		}
	}
	else if(key=='a'){
		while(i < 10 && window.square.getMinX() > 0) {
			window.moveLeft(1);
			i++;
		}
	}
	else if(key=='d'){
		while(i < 10 && window.square.getMaxX() < 599) {
			window.moveRight(1);
			i++;
		}
	}
	else if(key=='s'){
		while(i < 10 && window.square.getMaxY() < 400) {
			window.moveDown(1);
			i++;
		}
	}
	else if(key=='m') {
		if (window.square.getMinY()>0 && window.square.getMinX() > 0 && window.square.getMaxX() < 599 && window.square.getMaxY() < 400)
			window.zoomOut(1.01);
	}
	else if(key=='k') {
		if (window.square.getMinY()>0 && window.square.getMinX() > 0 && window.square.getMaxX() < 599 && window.square.getMaxY() < 400)
			window.zoomIn(1.01);
	}
	else if(key=='l') {
		//if (window.square.getMinY()>0 && window.square.getMinX() > 0 && window.square.getMaxX() < 599 && window.square.getMaxY() < 400)
			window.rotateCW(5.0);
	}
	else if(key=='j') {
		//if (window.square.getMinY()>0 && window.square.getMinX() > 0 && window.square.getMaxX() < 599 && window.square.getMaxY() < 400)
			window.rotateCW(-5.0);
	}
	else if(key=='q') {
		// OTHER KEYS
		quit=true;
		system("clear");
	}

	if (key=='a' || key=='s' || key=='d' || key=='w' || key=='k' || key=='m' || key=='l' || key=='j'){
		//menggambar ulang peta
		drawMap();

		//menggambar ulang window & view
		FB.cleararea(view.P1.x,view.P1.y,view.P2.x,view.P2.y);
		FB.drawPolygon(view.pol,255,255,255,0);	
		FB.drawWindow(window,255,255,255,0);
		redraw();
	}
}

void initDraw() {
	int rgb1[] = {50,205,50,0};
	int rgb2[] = {124,255,0,0};
	int rgb3[] = {255,255,0,0};
	int rgb4[] = {255,165,0,0};

	polygons.push_back(c_papua_4_1.finals);
	colors.push_back(vector<int>(rgb2, rgb2 + sizeof rgb2 / sizeof rgb2[0]));
	polygons.push_back(c_papua_3_3.finals);
	colors.push_back(vector<int>(rgb4, rgb4 + sizeof rgb4 / sizeof rgb4[0]));
	polygons.push_back(c_papua_3_2.finals);
	colors.push_back(vector<int>(rgb3, rgb3 + sizeof rgb3 / sizeof rgb3[0]));
	polygons.push_back(c_papua_3_1.finals);
	colors.push_back(vector<int>(rgb2, rgb2 + sizeof rgb2 / sizeof rgb2[0]));
	polygons.push_back(c_papua_2_2.finals);
	colors.push_back(vector<int>(rgb3, rgb3 + sizeof rgb3 / sizeof rgb3[0]));
	polygons.push_back(c_papua_2_1.finals);
	colors.push_back(vector<int>(rgb2, rgb2 + sizeof rgb2 / sizeof rgb2[0]));
	//polygons.push_back(c_papua_1_3.finals);
	//colors.push_back(vector<int>(rgb3, rgb3 + sizeof rgb3 / sizeof rgb3[0]));
	//polygons.push_back(c_papua_1_2.finals);
	//colors.push_back(vector<int>(rgb3, rgb3 + sizeof rgb3 / sizeof rgb3[0]));
	//polygons.push_back(c_papua_1_1.finals);
	//colors.push_back(vector<int>(rgb2, rgb2 + sizeof rgb2 / sizeof rgb2[0]));
	
	polygons.push_back(p_papua.e);
	colors.push_back(vector<int>(rgb1, rgb1 + sizeof rgb1 / sizeof rgb1[0]));

	polygons.push_back(p_jawa.e);
	colors.push_back(vector<int>(rgb1, rgb1 + sizeof rgb1 / sizeof rgb1[0]));

	polygons.push_back(p_kalimantan.e);
	colors.push_back(vector<int>(rgb1, rgb1 + sizeof rgb1 / sizeof rgb1[0]));

	polygons.push_back(p_sulawesi.e);
	colors.push_back(vector<int>(rgb1, rgb1 + sizeof rgb1 / sizeof rgb1[0]));

	polygons.push_back(p_sumatra.e);
	colors.push_back(vector<int>(rgb1, rgb1 + sizeof rgb1 / sizeof rgb1[0]));
}