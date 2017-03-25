#include <windows.h>
#include <gl/Gl.h>
#include <gl/Glu.h>
#include <iostream>
#include "glut.h"
#include <cmath>
#include <math.h>
#include <fstream>
#include <vector>
#include <algorithm>

#define PI 3.14159265
#define deltat 0.0001
using namespace std;
void Display();
vector<double> readFile();
void Init(void);
void myKeyboard(unsigned char key, int x, int y);

/*
""""""""""""""""""""""DATA FILE NAME"""""""

"""""""""""""""""""""""""""""""""""""""""""
*/
string file_name = "cancer_wisconsin_origional.txt";

double w = 1000.0;
double h = 900.0;
double R = w/h;
int data_dimensions = 0;

struct GLintPoint{
	double x, y;
};


void setWindow(float left, float right, float bottom, float top)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);
}


void drawDotsLines(double x, double y){
	//draw single point
	glBegin(GL_POINTS);
	glColor3f(0.0/255,0.0/255,0.0/255);//black
		glVertex2d(x, y);
	glEnd();
	glFlush();
}


void drawPointOnLine(double x, int point_flag){
	glBegin(GL_POINTS);
		if(point_flag == 1){
			glColor3f(206.0/255,77.0/255,77.0/255);//red
			glVertex2d(x, h/2 +15); 
		}else{
			glColor3f(9.0/255,38.0/255,249.0/255);//blue
			glVertex2d(x, h/2 -15); 
		}
	glEnd();
	glFlush();
}



vector<double> readFile(string filename){
	fstream inStream;
	inStream.open(filename, ios::in);
	if(inStream.fail()){
		cout<<"FAILED TO GET THE FILE";
	} 
	inStream >>data_dimensions;
	double data;
	vector<double> data_array;
	while(inStream >> data){
		data_array.push_back(data);
		//cout<<"fromfile: "<<data<<endl;
	}
	inStream.close();
	return data_array;
}


void drawAxis(){
	glColor3f(0.0/255,0.0/255,0.0/255);//black
	//drawing the first line
	glBegin(GL_LINES);
		glVertex2d(0, h/2 +15);
		glVertex2d(w, h/2 +15);
	glEnd();

	//drawing the second line
	glBegin(GL_LINES);
		glVertex2d(0, h/2 -15);
		glVertex2d(w, h/2 -15);
	glEnd();
	glFlush();
}


double calculateAngle(double coefficient){
	return (acos(coefficient)*180 / PI);
}


void driver(){
	vector<double> data = readFile(file_name);
	//coefficients are normolized from an equation
	double coefficients[9];
	coefficients[0] = 0.9;
	coefficients[1] = 0.5;
	coefficients[2] = 0.8;
	coefficients[3] = 0.9;
	coefficients[4] = 0.7;
	coefficients[5] = 0.9;
	coefficients[6] = 0.3;
	coefficients[7] = 0.7;
	coefficients[8] = 0.6;
	
	//this for oop goes through the rows in the file
	int k = 0;
	for(int i=0; i<data.size()/(data_dimensions); i++){
		int start_x = 0;
		int start_y = h/2 -15;
		int class_label = data[k+(data_dimensions-1)];

		if (class_label == 1){
			start_y = h/2 +15;
			glColor3f(206.0/255,77.0/255,77.0/255);//red
		}else{
			glColor3f(9.0/255,38.0/255,249.0/255);//blue
		}

		vector<GLintPoint> dots;
		
		glBegin(GL_LINE_STRIP);
		glVertex2f(start_x, start_y); //first point always the same
		//this for loop goes through a single row in the file
		for(int x=0; x<data_dimensions-1; x++){
			int radius = (data[k+x])*7; //7 pixel padding
			double angle = calculateAngle(coefficients[x]);
			double radians = PI * (angle/180.0);
			double new_x = start_x + radius*cos(radians);
			double new_y = start_y + radius*sin(radians);

			if(class_label == 1){ //draw above
				new_y = start_y + radius*sin(radians);
			}else{ //draw below
				new_y = start_y - radius*sin(radians);
			}

			glVertex2f(new_x, new_y);
			GLintPoint one_point;
			one_point.x = new_x;
			one_point.y = new_y;
			dots.push_back(one_point);
			start_x = new_x;
			start_y = new_y;
		}
		glEnd(); // for line strip
		k += data_dimensions;
		glFlush();

		//this for loop draws the dots for a single line strip
		for(int j=0; j<data_dimensions-1; j++){
			GLintPoint single_point = dots[j];
			drawDotsLines(single_point.x, single_point.y);
		}

		//draws a dot on the axis line
		if(class_label == 1){
			drawPointOnLine(start_x, 1);
		}else{
			drawPointOnLine(start_x, -1);
		}
	}
	glFlush();
}


void Display(){
	glClear(GL_COLOR_BUFFER_BIT);
	drawAxis();
	driver();
	//left, right, bottom, top
	glViewport(50, 50,  w-100, h-100);
}


void myKeyboard(unsigned char key, int x, int y) {
	switch(key) {
		case 't':
			glClear(GL_COLOR_BUFFER_BIT);
			cout<<"t"<<endl;
			driver();
			break;
	}
}
	

void Init()
{
	glClearColor(1.0,1.0,1.0,0.0);
   glColor3f(0.0f,0.0f,0.0f);
   glPointSize(5.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0.0,w,0.0,h);
}


void main (int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(w, h);
	glutInitWindowPosition(100,150);
	glutCreateWindow("Data Visualization");
	glutKeyboardFunc(myKeyboard);
	glutDisplayFunc(Display);
   Init();
	glutMainLoop();
}