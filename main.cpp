#include "FrameBuffer.cpp"
#include <cstring>
#include <termios.h>
#include <fstream>
#include "assets.h"
#include "ThreeDimension.h"

using namespace std;

FrameBuffer FB;
bool quit = false;
vector<ThreeDimension> peta;
vector<Curve> kontur;
Window window;
int key;
bool showPins = false;
bool showName = false;

int kbhit(void);
Polygon matrixToPolygon(int object[][2], int col);
ThreeDimension matrixToVectorOfPoints(int object[][2], int col);
Curve matrixToCurve(int object[][2], int col);
void printLetter(int font[][2], int col, float size, int x, int y);
void printLetterCounter(int font1[][2], int col1, int font2[][2], int col2, float size, int x, int y);
void drawMap();
void redraw();
void move(int key);
void initDraw();
void launchScreen();
void drawCredits();
void initMap();
void drawPin(int x, int y);
void placePin();
void placeProvinceName(string str, int x, int y);
void drawCompass();

// ANTI CLIPPING
vector < vector <Point> > polygons;
vector < vector <int> > colors;

View view;
Polygon map_border = matrixToPolygon(border,sizeof(border)/sizeof(*border));
ThreeDimension p_sumatra = matrixToVectorOfPoints(sumatra,sizeof(sumatra)/sizeof(*sumatra));
ThreeDimension p_kalimantan = matrixToVectorOfPoints(kalimantan,sizeof(kalimantan)/sizeof(*kalimantan));
ThreeDimension p_sulawesi = matrixToVectorOfPoints(sulawesi,sizeof(sulawesi)/sizeof(*sulawesi));
ThreeDimension p_papua = matrixToVectorOfPoints(papua,sizeof(papua)/sizeof(*papua));
ThreeDimension p_jawa = matrixToVectorOfPoints(jawa,sizeof(jawa)/sizeof(*jawa));
Curve c_papua_1_1 = matrixToCurve(papua_1,sizeof(papua_1)/sizeof(*papua_1));
Curve c_papua_1_2 = matrixToCurve(papua_1,sizeof(papua_1)/sizeof(*papua_1));
Curve c_papua_1_3 = matrixToCurve(papua_1,sizeof(papua_1)/sizeof(*papua_1));
Curve c_papua_2_1 = matrixToCurve(papua_1,sizeof(papua_1)/sizeof(*papua_1));
Curve c_papua_2_2 = matrixToCurve(papua_1,sizeof(papua_1)/sizeof(*papua_1));
Curve c_papua_3_1 = matrixToCurve(papua_3,sizeof(papua_3)/sizeof(*papua_3));
Curve c_papua_3_2 = matrixToCurve(papua_3,sizeof(papua_3)/sizeof(*papua_3));
Curve c_papua_3_3 = matrixToCurve(papua_3,sizeof(papua_3)/sizeof(*papua_3));
Curve c_papua_4_1 = matrixToCurve(papua_4,sizeof(papua_4)/sizeof(*papua_4));

Polygon c_sulawesi_1_1 = matrixToPolygon(sulawesi_1_1,sizeof(sulawesi_1_1)/sizeof(*sulawesi_1_1));
Polygon c_sulawesi_1_2 = matrixToPolygon(sulawesi_1_2,sizeof(sulawesi_1_2)/sizeof(*sulawesi_1_2));
Polygon c_sulawesi_1_3 = matrixToPolygon(sulawesi_1_3,sizeof(sulawesi_1_3)/sizeof(*sulawesi_1_3));
Polygon c_sulawesi_1_4 = matrixToPolygon(sulawesi_1_3,sizeof(sulawesi_1_3)/sizeof(*sulawesi_1_3));
Curve c_sulawesi_2_1 = matrixToCurve(sulawesi_2,sizeof(sulawesi_2)/sizeof(*sulawesi_2));
Curve c_sulawesi_2_2 = matrixToCurve(sulawesi_2,sizeof(sulawesi_2)/sizeof(*sulawesi_2));
Curve c_sulawesi_2_3 = matrixToCurve(sulawesi_2,sizeof(sulawesi_2)/sizeof(*sulawesi_2));

Curve c_sumatra_1_1 = matrixToCurve(sumatra_1,sizeof(sumatra_1)/sizeof(*sumatra_1));
Curve c_sumatra_1_2 = matrixToCurve(sumatra_1,sizeof(sumatra_1)/sizeof(*sumatra_1));
Curve c_sumatra_1_3 = matrixToCurve(sumatra_1,sizeof(sumatra_1)/sizeof(*sumatra_1));
Curve c_sumatra_2_1 = matrixToCurve(sumatra_2,sizeof(sumatra_2)/sizeof(*sumatra_2));
Curve c_sumatra_2_2 = matrixToCurve(sumatra_2,sizeof(sumatra_2)/sizeof(*sumatra_2));
Curve c_sumatra_2_3 = matrixToCurve(sumatra_2,sizeof(sumatra_2)/sizeof(*sumatra_2));
Curve c_sumatra_3_1 = matrixToCurve(sumatra_3,sizeof(sumatra_3)/sizeof(*sumatra_3));
Curve c_sumatra_3_2 = matrixToCurve(sumatra_3,sizeof(sumatra_3)/sizeof(*sumatra_3));
Curve c_sumatra_3_3 = matrixToCurve(sumatra_3,sizeof(sumatra_3)/sizeof(*sumatra_3));
Curve c_sumatra_4_1 = matrixToCurve(sumatra_4,sizeof(sumatra_4)/sizeof(*sumatra_4));
Curve c_sumatra_4_2 = matrixToCurve(sumatra_4,sizeof(sumatra_4)/sizeof(*sumatra_4));
Curve c_sumatra_4_3 = matrixToCurve(sumatra_4,sizeof(sumatra_4)/sizeof(*sumatra_4));
Curve c_sumatra_5_1 = matrixToCurve(sumatra_5,sizeof(sumatra_5)/sizeof(*sumatra_5));
Curve c_sumatra_5_2 = matrixToCurve(sumatra_5,sizeof(sumatra_5)/sizeof(*sumatra_5));
Curve c_jawa_1_1 = matrixToCurve(jawa_1,sizeof(jawa_1)/sizeof(*jawa_1));
Curve c_jawa_1_2 = matrixToCurve(jawa_1,sizeof(jawa_1)/sizeof(*jawa_1));
Curve c_jawa_1_3 = matrixToCurve(jawa_1,sizeof(jawa_1)/sizeof(*jawa_1));
Curve c_jawa_2_1 = matrixToCurve(jawa_2,sizeof(jawa_2)/sizeof(*jawa_2));
Curve c_jawa_2_2 = matrixToCurve(jawa_2,sizeof(jawa_2)/sizeof(*jawa_2));
Curve c_jawa_2_3 = matrixToCurve(jawa_2,sizeof(jawa_2)/sizeof(*jawa_2));
Curve c_kalimantan_1_1 = matrixToCurve(kalimantan_1,sizeof(kalimantan_1)/sizeof(*kalimantan_1));
Curve c_kalimantan_1_2 = matrixToCurve(kalimantan_1,sizeof(kalimantan_1)/sizeof(*kalimantan_1));
Curve c_kalimantan_1_3 = matrixToCurve(kalimantan_1,sizeof(kalimantan_1)/sizeof(*kalimantan_1));
Curve c_kalimantan_2_1 = matrixToCurve(kalimantan_2,sizeof(kalimantan_2)/sizeof(*kalimantan_2));
Curve c_kalimantan_2_2 = matrixToCurve(kalimantan_2,sizeof(kalimantan_2)/sizeof(*kalimantan_2));

Polygon p_compass_top= matrixToPolygon(compass_top,sizeof(compass_top)/sizeof(*compass_top));
Polygon p_compass= matrixToPolygon(compass_top,sizeof(compass_top)/sizeof(*compass_top));


int main() {
	// Adjust positions of the islands
	initMap();
	system("clear");

	launchScreen();
	sleep(2);

	FB.clearscreen();
	initDraw();
	drawMap();

	FB.cleararea(view.P1.x,view.P1.y,view.P2.x,view.P2.y);
	FB.drawPolygon(view.pol,255,255,255,0);
	FB.drawWindow(window,255,255,255,0);
	
	redraw();
	drawCompass();
	
	while(!quit){
		if(kbhit()){
			key=getchar();
			//PANGGIL FUNGSI UNTUK REDRAW MOVEMENT
			move(key);
		}
	}
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

ThreeDimension matrixToVectorOfPoints(int object[][2], int col) {
	vector<Point> points;
	points.clear();
	for(int i=0;i<col;i++) {
		points.push_back(Point(object[i][0],object[i][1]));
	}
	return ThreeDimension(points);
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
	FB.drawThreeDimension(peta);
	FB.scanLine3D(polygons,colors);
	printLetter(font_U, sizeof(font_U)/sizeof(*font_U), 0.2, 2865, 35);
	FB.rasterScan(p_compass,255, 0, 0, 0, 20, 40);
	

	FB.rasterScan(c_papua_1_1, r2, g2, b2, 0, c_papua_1_1.getMinY(), c_papua_1_1.getMaxY());
	FB.rasterScan(c_papua_1_2, r3, g3, b3, 0, c_papua_1_2.getMinY(), c_papua_1_2.getMaxY());
	FB.rasterScan(c_papua_1_3, r4, g4, b4, 0, c_papua_1_3.getMinY(), c_papua_1_3.getMaxY());
	
	FB.rasterScan(c_jawa_2_2, r3, g3, b3, 0, c_jawa_2_2.getMinY(), c_jawa_2_2.getMaxY());
	FB.rasterScan(c_jawa_2_3, r4, g4, b4, 0, c_jawa_2_3.getMinY(), c_jawa_2_3.getMaxY());

	FB.rasterScan(c_sulawesi_1_2, r2, g2, b2, 0, c_sulawesi_1_2.getMinY(), c_sulawesi_1_2.getMaxY());
	FB.rasterScan(c_sulawesi_1_3, r2, g2, b2, 0, c_sulawesi_1_3.getMinY(), c_sulawesi_1_3.getMaxY());
	
	if (showPins){
		placePin();
	}
	
	if (showName){
		placeProvinceName("sumatra",20,150);
		placeProvinceName("sulawesi",315,123);
		placeProvinceName("jawa",250,300);
		placeProvinceName("papua",497,180);
		placeProvinceName("kalimantan", 140, 60);
	}
}

void redraw() { //untuk redraw view
	vector<Polygon> temp;
	for(int i=0;i<peta.size();i++) {
		int j=0;
		bool found = false;
		while(j<peta[i].frontside.e.size() && !found) {
			if(not(peta[i].frontside.e[j].x<window.getTopLeft().x || peta[i].frontside.e[j].y<window.getTopLeft().y 
				|| peta[i].frontside.e[j].y>window.getBottomRight().y || peta[i].frontside.e[j].x>window.getBottomRight().x)) {
				found = true;
				temp.push_back(peta[i].frontside);
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
		int i = 0;
		if(key==65){
			while(i < 10 && window.square.getMinY() > 0) {
				window.moveUp(1);
				i++;
			}
		}
		else if(key==68){
			while(i < 10 && window.square.getMinX() > 0) {
				window.moveLeft(1);
				i++;
			}
		}
		else if(key==67){
			while(i < 10 && window.square.getMaxX() < 599) {
				window.moveRight(1);
				i++;
			}
		}
		else if(key==66){
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
				window.rotateCW(5.0);
		}
		else if(key=='j') {
				window.rotateCW(-5.0);
		}
		else if(key=='n'){ //nama pulau
			showName = true;
		}
		else if(key=='i'){ //nama pulau
			showPins = true;
		}
		else if(key=='c') { //creadits
			FB.cleararea(0,0,599,400);
			drawCredits();
			quit=true;
			system("clear");
		}
		else if(key=='q') {
			// OTHER KEYS
			quit=true;
			system("clear");
		}

		if (key==65 || key==66 || key==67 || key==68 || key=='k' || key=='m' || key=='l' || key=='j' || key=='n' || key=='i'){
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
	int rgb5[] = {100,100,100,0};

	polygons.push_back(c_jawa_2_1.finals);
	colors.push_back(vector<int>(rgb2, rgb2 + sizeof rgb2 / sizeof rgb2[0]));
	polygons.push_back(c_jawa_1_3.finals);
	colors.push_back(vector<int>(rgb4, rgb4 + sizeof rgb4 / sizeof rgb4[0]));
	polygons.push_back(c_jawa_1_2.finals);
	colors.push_back(vector<int>(rgb3, rgb3 + sizeof rgb3 / sizeof rgb3[0]));
	polygons.push_back(c_jawa_1_1.finals);
	colors.push_back(vector<int>(rgb2, rgb2 + sizeof rgb2 / sizeof rgb2[0]));

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

	polygons.push_back(c_sumatra_1_3.finals);
	colors.push_back(vector<int>(rgb4, rgb4 + sizeof rgb4 / sizeof rgb4[0]));
	polygons.push_back(c_sumatra_1_2.finals);
	colors.push_back(vector<int>(rgb3, rgb3 + sizeof rgb3 / sizeof rgb3[0]));
	polygons.push_back(c_sumatra_1_1.finals);
	colors.push_back(vector<int>(rgb2, rgb2 + sizeof rgb2 / sizeof rgb2[0]));
	polygons.push_back(c_sumatra_2_3.finals);
	colors.push_back(vector<int>(rgb4, rgb4 + sizeof rgb4 / sizeof rgb4[0]));
	polygons.push_back(c_sumatra_2_2.finals);
	colors.push_back(vector<int>(rgb3, rgb3 + sizeof rgb3 / sizeof rgb3[0]));
	polygons.push_back(c_sumatra_2_1.finals);
	colors.push_back(vector<int>(rgb2, rgb2 + sizeof rgb2 / sizeof rgb2[0]));
	polygons.push_back(c_sumatra_3_3.finals);
	colors.push_back(vector<int>(rgb4, rgb4 + sizeof rgb4 / sizeof rgb4[0]));
	polygons.push_back(c_sumatra_3_2.finals);
	colors.push_back(vector<int>(rgb3, rgb3 + sizeof rgb3 / sizeof rgb3[0]));
	polygons.push_back(c_sumatra_3_1.finals);
	colors.push_back(vector<int>(rgb2, rgb2 + sizeof rgb2 / sizeof rgb2[0]));
	polygons.push_back(c_sumatra_4_3.finals);
	colors.push_back(vector<int>(rgb4, rgb4 + sizeof rgb4 / sizeof rgb4[0]));
	polygons.push_back(c_sumatra_4_2.finals);
	colors.push_back(vector<int>(rgb3, rgb3 + sizeof rgb3 / sizeof rgb3[0]));
	polygons.push_back(c_sumatra_4_1.finals);
	colors.push_back(vector<int>(rgb2, rgb2 + sizeof rgb2 / sizeof rgb2[0]));
	polygons.push_back(c_sumatra_5_1.finals);
	colors.push_back(vector<int>(rgb2, rgb2 + sizeof rgb2 / sizeof rgb2[0]));

	polygons.push_back(c_kalimantan_1_3.finals);
	colors.push_back(vector<int>(rgb4, rgb4 + sizeof rgb4 / sizeof rgb4[0]));
	polygons.push_back(c_kalimantan_1_2.finals);
	colors.push_back(vector<int>(rgb3, rgb3 + sizeof rgb3 / sizeof rgb3[0]));
	polygons.push_back(c_kalimantan_1_1.finals);
	colors.push_back(vector<int>(rgb2, rgb2 + sizeof rgb2 / sizeof rgb2[0]));
	polygons.push_back(c_kalimantan_2_2.finals);
	colors.push_back(vector<int>(rgb3, rgb3 + sizeof rgb3 / sizeof rgb3[0]));
	polygons.push_back(c_kalimantan_2_1.finals);
	colors.push_back(vector<int>(rgb2, rgb2 + sizeof rgb2 / sizeof rgb2[0]));

	polygons.push_back(c_sulawesi_2_3.finals);
	colors.push_back(vector<int>(rgb4, rgb4 + sizeof rgb4 / sizeof rgb4[0]));
	polygons.push_back(c_sulawesi_2_2.finals);
	colors.push_back(vector<int>(rgb3, rgb3 + sizeof rgb3 / sizeof rgb3[0]));
	polygons.push_back(c_sulawesi_2_1.finals);
	colors.push_back(vector<int>(rgb2, rgb2 + sizeof rgb2 / sizeof rgb2[0]));
	polygons.push_back(c_sulawesi_1_4.e);
	colors.push_back(vector<int>(rgb2, rgb2 + sizeof rgb2 / sizeof rgb2[0]));
	polygons.push_back(c_sulawesi_1_1.e);
	colors.push_back(vector<int>(rgb2, rgb2 + sizeof rgb2 / sizeof rgb2[0]));

	for (int i=0; i<peta.size(); i++) {
		polygons.push_back(peta[i].frontside.e);
		colors.push_back(vector<int>(rgb1, rgb1 + sizeof rgb1 / sizeof rgb1[0]));
	}
}

void printLetter(int font[][2], int col, float size, int x, int y) {
		vector<Point> points;
		points.clear();
		for(int i=0;i<col-1;i++) {
			points.push_back(Point((float)(font[i][0]*size)+(float)size*x,(float)(font[i][1]*size)+(float)size*y));
		}

		Polygon Poly(points);
		Poly.firePoint = Point(font[col-1][0]*size+size*x,font[col-1][1]*size+size*y);
		FB.drawPolygon(Poly.e,25,25,122,0);
		FB.rasterScan(Poly, 10, 10, 10, 0, Poly.getMinY(), Poly.getMaxY());
}

void printLetterCounter(int font1[][2], int col1, int font2[][2], int col2, float size, int x, int y) {
	vector<Point> points;
	vector<Point> points2;

	points.clear();
	for(int i=0;i<col1-1;i++) {
		points.push_back(Point((float)(font1[i][0]*size)+(float)size*x,(float)(font1[i][1]*size)+(float)size*y));
	}
	Polygon Poly1(points);
	FB.drawPolygon(Poly1.e,25,25,122,0);
	FB.rasterScan(Poly1, 10, 10, 10, 0, Poly1.getMinY(), Poly1.getMaxY());

	points2.clear();
	for(int i=0;i<col2-1;i++) {
		points2.push_back(Point((float)(font2[i][0]*size)+(float)size*x,(float)(font2[i][1]*size)+(float)size*y));
	}
	Polygon Poly2(points2);

	FB.drawPolygon(Poly2.e,25,25,122,0);
	
	FB.rasterScan(Poly2, 135, 206, 235, 0, Poly2.getMinY(), Poly2.getMaxY());
}

void launchScreen() {
	float size = 5;
	int y_peta = 25;
	int margin_left = 80;

	FB.cleararea(0,0,1366,512);
    
	printLetterCounter(font_P_out, sizeof(font_P_out)/sizeof(*font_P_out), font_P_in, sizeof(font_P_in)/sizeof(*font_P_in), size/2, 5*2+margin_left*2, y_peta*2);
	printLetter(font_E, sizeof(font_E)/sizeof(*font_E), size, 23+margin_left, y_peta);
	printLetter(font_T, sizeof(font_T)/sizeof(*font_T), size, 38+margin_left, y_peta);
	printLetterCounter(font_A_out, sizeof(font_A_out)/sizeof(*font_A_out), font_A_in, sizeof(font_A_in)/sizeof(*font_A_in), size, 55+margin_left, y_peta);
}


void drawCredits() {
	float size = 1.5;
	
	int y_vanya = 25;
	int y_venny = 50;
	int y_pipin = 75;
	int y_azwar = 100;
	int y_jessica = 125;	

	while(y_jessica > 0) {
		printLetter(font_V, sizeof(font_V)/sizeof(*font_V), size, 5, y_vanya);
		printLetterCounter(font_A_out, sizeof(font_A_out)/sizeof(*font_A_out), font_A_in, sizeof(font_A_in)/sizeof(*font_A_in), size, 20, y_vanya);
		printLetter(font_N, sizeof(font_N)/sizeof(*font_N), size, 40, y_vanya);
		printLetter(font_Y, sizeof(font_Y)/sizeof(*font_Y), size, 58, y_vanya);
		printLetterCounter(font_A_out, sizeof(font_A_out)/sizeof(*font_A_out), font_A_in, sizeof(font_A_in)/sizeof(*font_A_in), size, 72, y_vanya);

		printLetter(font_V, sizeof(font_V)/sizeof(*font_V), size, 5, y_venny);
		printLetter(font_E, sizeof(font_E)/sizeof(*font_E), size, 25, y_venny);
		printLetter(font_N, sizeof(font_N)/sizeof(*font_N), size, 40, y_venny);
		printLetter(font_N, sizeof(font_N)/sizeof(*font_N), size, 60, y_venny);
		printLetter(font_Y, sizeof(font_Y)/sizeof(*font_Y), size, 78, y_venny);

		printLetterCounter(font_P_out, sizeof(font_P_out)/sizeof(*font_P_out), font_P_in, sizeof(font_P_in)/sizeof(*font_P_in), size/2, 5*2, y_pipin*2);
		printLetter(font_I, sizeof(font_I)/sizeof(*font_I), size, 22, y_pipin);
		printLetterCounter(font_P_out, sizeof(font_P_out)/sizeof(*font_P_out), font_P_in, sizeof(font_P_in)/sizeof(*font_P_in), size/2, 30*2, y_pipin*2);
		printLetter(font_I, sizeof(font_I)/sizeof(*font_I), size, 47, y_pipin);
		printLetter(font_N, sizeof(font_N)/sizeof(*font_N), size, 52, y_pipin);

		printLetterCounter(font_A_out, sizeof(font_A_out)/sizeof(*font_A_out), font_A_in, sizeof(font_A_in)/sizeof(*font_A_in), size, 5, y_azwar);
		printLetter(font_Z, sizeof(font_Z)/sizeof(*font_Z), size, 25, y_azwar);
		printLetter(font_W, sizeof(font_W)/sizeof(*font_W), size, 39, y_azwar);
		printLetterCounter(font_A_out, sizeof(font_A_out)/sizeof(*font_A_out), font_A_in, sizeof(font_A_in)/sizeof(*font_A_in), size, 62, y_azwar);
		printLetterCounter(font_R_out, sizeof(font_R_out)/sizeof(*font_R_out), font_R_in, sizeof(font_R_in)/sizeof(*font_R_in), size/2,  82*2, y_azwar*2);

		printLetter(font_J, sizeof(font_J)/sizeof(*font_J), size/2, 5*2, y_jessica*2);
		printLetter(font_E, sizeof(font_E)/sizeof(*font_E), size, 20, y_jessica);
		printLetter(font_S, sizeof(font_S)/sizeof(*font_S), size/2, 35*2, y_jessica*2);
		printLetter(font_S, sizeof(font_S)/sizeof(*font_S), size/2, 52*2, y_jessica*2);
		printLetter(font_I, sizeof(font_I)/sizeof(*font_I), size, 70, y_jessica);
		printLetter(font_C, sizeof(font_C)/sizeof(*font_C), size/2, 78*2, y_jessica*2);
		printLetterCounter(font_A_out, sizeof(font_A_out)/sizeof(*font_A_out), font_A_in, sizeof(font_A_in)/sizeof(*font_A_in), size, 98, y_jessica);

		y_vanya-=2; y_venny-=2; y_pipin-=2; y_azwar-=2; y_jessica-=2;
        usleep(10000);
        FB.cleararea(0,0,300,400);
	}
}

void initMap() {
	p_sumatra.moveDown(10);
	p_sumatra.moveRight(5);
	p_jawa.scale(1.8);
	p_jawa.moveDown(265);
	p_jawa.moveRight(170);
	p_kalimantan.scale(1.55);
	p_kalimantan.moveRight(155);
	p_kalimantan.moveDown(50);
	p_sulawesi.scale(1.25);
	p_sulawesi.moveRight(320);
	p_sulawesi.moveDown(100);
	p_papua.scale(2);
	p_papua.moveRight(430);
	p_papua.moveDown(160);

	peta.push_back(p_papua);
	peta.push_back(p_jawa);
	peta.push_back(p_kalimantan);
	peta.push_back(p_sulawesi);
	peta.push_back(p_sumatra);

	//Adjust positions of the contour
	c_jawa_1_1.rotate(195);
	c_jawa_1_1.scale(0.9);
	c_jawa_1_1.moveRight(340);
	c_jawa_1_1.moveDown(240);
	c_jawa_1_2.rotate(193);
	c_jawa_1_2.scale(0.6);
	c_jawa_1_2.moveRight(330);
	c_jawa_1_2.moveDown(270);
	c_jawa_1_3.rotate(192);
	c_jawa_1_3.scale(0.3);
	c_jawa_1_3.moveRight(322);
	c_jawa_1_3.moveDown(301);

	c_jawa_2_1.rotate(30);
	c_jawa_2_1.scale(2);
	c_jawa_2_1.moveRight(210);
	c_jawa_2_1.moveDown(255);
	c_jawa_2_2.rotate(30);
	c_jawa_2_2.scale(1.3);
	c_jawa_2_2.moveRight(220);
	c_jawa_2_2.moveDown(275);
	c_jawa_2_3.rotate(30);
	c_jawa_2_3.scale(0.8);
	c_jawa_2_3.moveRight(230);
	c_jawa_2_3.moveDown(287);

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

	c_sulawesi_1_1.scale(0.5);
	c_sulawesi_1_1.moveRight(386);
	c_sulawesi_1_1.moveDown(106);
	c_sulawesi_1_2.scale(0.5);
	c_sulawesi_1_2.moveRight(382);
	c_sulawesi_1_2.moveDown(102);
	c_sulawesi_1_3.scale(0.7);
	c_sulawesi_1_3.moveRight(346);
	c_sulawesi_1_3.moveDown(140);
	c_sulawesi_1_4.scale(0.6);
	c_sulawesi_1_4.moveRight(320);
	c_sulawesi_1_4.moveDown(155);

	c_sulawesi_2_1.scale(1.2);
	c_sulawesi_2_1.moveRight(336);
	c_sulawesi_2_1.moveDown(152);
	c_sulawesi_2_2.scale(0.9);
	c_sulawesi_2_2.moveRight(340);
	c_sulawesi_2_2.moveDown(154);
	c_sulawesi_2_3.scale(0.5);
	c_sulawesi_2_3.moveRight(345);
	c_sulawesi_2_3.moveDown(160);

	c_sumatra_1_1.rotate(20);
	c_sumatra_1_1.scale(0.6);
	c_sumatra_1_1.moveRight(19);
	c_sumatra_1_1.moveDown(57);
	c_sumatra_1_2.rotate(20);
	c_sumatra_1_2.scale(0.5);
	c_sumatra_1_2.moveRight(23);
	c_sumatra_1_2.moveDown(64);
	c_sumatra_1_3.rotate(20);
	c_sumatra_1_3.scale(0.3);
	c_sumatra_1_3.moveRight(29);
	c_sumatra_1_3.moveDown(77);

	c_sumatra_2_1.rotate(-117);
	c_sumatra_2_1.scale(0.8);
	c_sumatra_2_1.moveRight(100);
	c_sumatra_2_1.moveDown(118);
	c_sumatra_2_2.rotate(-117);
	c_sumatra_2_2.scale(0.7);
	c_sumatra_2_2.moveRight(97);
	c_sumatra_2_2.moveDown(123);
	c_sumatra_2_3.rotate(-117);
	c_sumatra_2_3.scale(0.4);
	c_sumatra_2_3.moveRight(92);
	c_sumatra_2_3.moveDown(149);

	c_sumatra_3_1.rotate(5);
	c_sumatra_3_1.scale(0.55);
	c_sumatra_3_1.moveRight(92);
	c_sumatra_3_1.moveDown(195);
	c_sumatra_3_2.rotate(5);
	c_sumatra_3_2.scale(0.45);
	c_sumatra_3_2.moveRight(95);
	c_sumatra_3_2.moveDown(198);
	c_sumatra_3_3.rotate(5);
	c_sumatra_3_3.scale(0.25);
	c_sumatra_3_3.moveRight(99);
	c_sumatra_3_3.moveDown(203);

	c_sumatra_4_1.rotate(2);
	c_sumatra_4_1.scale(0.5);
	c_sumatra_4_1.moveRight(88);
	c_sumatra_4_1.moveDown(198);
	c_sumatra_4_2.rotate(2);
	c_sumatra_4_2.scale(0.3);
	c_sumatra_4_2.moveRight(105);
	c_sumatra_4_2.moveDown(225);
	c_sumatra_4_3.rotate(2);
	c_sumatra_4_3.scale(0.23);
	c_sumatra_4_3.moveRight(112);
	c_sumatra_4_3.moveDown(232);

	c_sumatra_5_1.rotate(88);
	c_sumatra_5_1.scale(1.5);
	c_sumatra_5_1.moveRight(116);
	c_sumatra_5_1.moveDown(190);

	c_kalimantan_1_1.rotate(120);
	c_kalimantan_1_1.scale(0.7);
	c_kalimantan_1_1.moveRight(272);
	c_kalimantan_1_1.moveDown(97);
	c_kalimantan_1_2.rotate(120);
	c_kalimantan_1_2.scale(0.5);
	c_kalimantan_1_2.moveRight(260);
	c_kalimantan_1_2.moveDown(110);
	c_kalimantan_1_3.rotate(120);
	c_kalimantan_1_3.scale(0.3);
	c_kalimantan_1_3.moveRight(255);
	c_kalimantan_1_3.moveDown(123);
	c_kalimantan_2_1.rotate(140);
	c_kalimantan_2_1.scale(0.4);
	c_kalimantan_2_1.moveRight(270);
	c_kalimantan_2_1.moveDown(124);
	c_kalimantan_2_2.rotate(140);
	c_kalimantan_2_2.scale(0.25);
	c_kalimantan_2_2.moveRight(267);
	c_kalimantan_2_2.moveDown(145);
}

void drawPin(int x, int y) {
	int radius = 4;
	vector<Point> pin;
	pin.push_back(Point(x-radius,y));
	pin.push_back(Point(x,y-radius));
	pin.push_back(Point(x+radius,y));
	pin.push_back(Point(x,y+radius));
	FB.rasterScan(pin,130,0,0,0,y-radius,y+radius);
}

void placePin() {
	// SUMATERA
	drawPin(27,70); // Aceh
	drawPin(60,100); // Medan
	drawPin(100,150); // Pekanbaru
	drawPin(75,170); // Padang
	drawPin(118,202); // Jambi
	drawPin(137,285); // Lampung

	// JAWA
	drawPin(190,287); // Banten
	drawPin(205,280); // Jakarta
	drawPin(220,300); // Bandung
	drawPin(274,305); // Semarang
	drawPin(278,320); // Jogja
	drawPin(340,312); // Surabaya

	//PAPUA
	drawPin(480,187); //irian barat
	drawPin(590,222); //irian timur
	drawPin(547,255); //irian tengah

	// KALIMANTAN
	drawPin(260,130); // Kalimantan timur
	drawPin(245,200); // Kalimantan selatan
	drawPin(215,175); // Kalimantan tengah
	drawPin(180,150); // Kalimantan barat

	//SULAWESI
	drawPin(342,150); // Sulawesi Tengah
	drawPin(333,180); // Sulawesi Barat
	drawPin(340,220); // Sulawesi Selatan
	drawPin(389,200); // Sulawesi Tenggara
	drawPin(390,155); // Sulawesi Timur
	drawPin(400,120); // Sulawesi Gorontalo
	drawPin(430,104); // Sulawesi Utara
	
	}

void placeProvinceName(string str, int x, int y) {
	float size = 1;
	if(str.compare("sumatra")==0) {
		printLetter(font_S, sizeof(font_S)/sizeof(*font_S), size/2, x*2, y*2);
		printLetter(font_U, sizeof(font_U)/sizeof(*font_U), size/2, (x+20)*2, y*2);
		printLetter(font_M, sizeof(font_M)/sizeof(*font_M), size, x+35,y);
		printLetterCounter(font_A_out, sizeof(font_A_out)/sizeof(*font_A_out), font_A_in, sizeof(font_A_in)/sizeof(*font_A_in), size, x+55, y);
		printLetter(font_T, sizeof(font_T)/sizeof(*font_T), size, x+70,y);
		printLetterCounter(font_R_out, sizeof(font_R_out)/sizeof(*font_R_out), font_R_in, sizeof(font_R_in)/sizeof(*font_R_in), size/2, (x+91)*2, y*2);
		printLetterCounter(font_A_out, sizeof(font_A_out)/sizeof(*font_A_out), font_A_in, sizeof(font_A_in)/sizeof(*font_A_in), size, x+107, y);
	}
	else if(str.compare("jawa")==0) {
		printLetter(font_J, sizeof(font_J)/sizeof(*font_J), size/2, x*2, y*2);
		printLetterCounter(font_A_out, sizeof(font_A_out)/sizeof(*font_A_out), font_A_in, sizeof(font_A_in)/sizeof(*font_A_in), size, x+15, y);
		printLetter(font_W, sizeof(font_W)/sizeof(*font_W), size, x+31,y);
		printLetterCounter(font_A_out, sizeof(font_A_out)/sizeof(*font_A_out), font_A_in, sizeof(font_A_in)/sizeof(*font_A_in), size, x+55, y);
	}
	else if(str.compare("papua")==0) {
		printLetterCounter(font_P_out, sizeof(font_P_out)/sizeof(*font_P_out), font_R_in, sizeof(font_P_in)/sizeof(*font_P_in), size/2, x*2, y*2);
		printLetterCounter(font_A_out, sizeof(font_A_out)/sizeof(*font_A_out), font_A_in, sizeof(font_A_in)/sizeof(*font_A_in), size, x+14, y);
		printLetterCounter(font_P_out, sizeof(font_P_out)/sizeof(*font_P_out), font_R_in, sizeof(font_P_in)/sizeof(*font_P_in), size/2, (x+34)*2, y*2);
		printLetter(font_U, sizeof(font_U)/sizeof(*font_U), size/2, (x+52)*2, y*2);
		printLetterCounter(font_A_out, sizeof(font_A_out)/sizeof(*font_A_out), font_A_in, sizeof(font_A_in)/sizeof(*font_A_in), size, x+65, y);
	}
	else if(str.compare("kalimantan")==0){
		printLetter(font_K, sizeof(font_K)/sizeof(*font_K), size, x, y);
		printLetterCounter(font_A_out, sizeof(font_A_out)/sizeof(*font_A_out), font_A_in, sizeof(font_A_in)/sizeof(*font_A_in), size, x+20, y);
		printLetter(font_L, sizeof(font_L)/sizeof(*font_L), size, x+43, y);
		printLetter(font_I, sizeof(font_I)/sizeof(*font_I), size, x+60, y);
		printLetter(font_M, sizeof(font_M)/sizeof(*font_M), size, x+68, y);
		printLetterCounter(font_A_out, sizeof(font_A_out)/sizeof(*font_A_out), font_A_in, sizeof(font_A_in)/sizeof(*font_A_in), size, x+90, y);
		printLetter(font_N, sizeof(font_N)/sizeof(*font_N), size, x+112, y);
		printLetter(font_T, sizeof(font_T)/sizeof(*font_T), size, x+130, y);
		printLetterCounter(font_A_out, sizeof(font_A_out)/sizeof(*font_A_out), font_A_in, sizeof(font_A_in)/sizeof(*font_A_in), size, x+148, y);
		printLetter(font_N, sizeof(font_N)/sizeof(*font_N), size, x+171, y);
	}

	else if(str.compare("sulawesi")==0) {
		printLetter(font_S, sizeof(font_S)/sizeof(*font_S), size/2, x*2, y*2);
		printLetter(font_U, sizeof(font_U)/sizeof(*font_U), size/2, (x+18)*2, y*2);
		printLetter(font_L, sizeof(font_L)/sizeof(*font_L), size, x+33,y);
		printLetterCounter(font_A_out, sizeof(font_A_out)/sizeof(*font_A_out), font_A_in, sizeof(font_A_in)/sizeof(*font_A_in), size, x+51, y);
		printLetter(font_W, sizeof(font_W)/sizeof(*font_W), size, x+66,y);
		printLetter(font_E, sizeof(font_E)/sizeof(*font_E), size, x+94, y);
		printLetter(font_S, sizeof(font_S)/sizeof(*font_S), size/2, (x+109)*2, y*2);
		printLetter(font_I, sizeof(font_I)/sizeof(*font_I), size, x+129,y);
	}
}

void drawCompass(){
	printLetter(font_U, sizeof(font_U)/sizeof(*font_U), 0.2, 2865, 35);
	for(int i=0; i<3; i++){
		FB.rasterScan(p_compass_top,255, 0, 0, 0, 20, 40);
		p_compass_top.rotateCenter(2);
		usleep(300000);
		FB.cleararea(555, 18, 595, 62);
	}
	for(int i=0; i<3; i++){
		FB.rasterScan(p_compass_top,255, 0, 0, 0, 20, 40);
		p_compass_top.rotateCenter(-5);
		usleep(300000);
		FB.cleararea(555, 18, 595, 62);
	}
	FB.rasterScan(p_compass,255, 0, 0, 0, 20, 40);
}