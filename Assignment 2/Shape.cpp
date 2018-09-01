
#include "Shape.hpp"
#include <cmath>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#elif defined(WIN32)
#include <Windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif


Shape::Shape() {
	x = y = z = 0.0;
	rotation = 0.0;
	red = green = blue = 1.0;
};

Shape::Shape(double x_, double y_, double z_) {
	x = x_;
	y = y_;
	z = z_;

	rotation = 0.0;
	red = green = blue = 1.0;
};

Shape::Shape(double x_, double y_, double z_, double rotation_) {

	x = x_;
	y = y_;
	z = z_;

	rotation = rotation_;
	red = green = blue = 1.0;
};

Shape::~Shape() {
}

double Shape::getX() {
	return x;
};

double Shape::getY() {
	return y;
};

double Shape::getZ() {
	return z;
};

double Shape::getRotation() {
	return rotation;
};

void Shape::setX(double x_) {
	x = x_;
};

void Shape::setY(double y_) {
	y = y_;
};

void Shape::setZ(double z_) {
	z = z_;
};

void Shape::setRotation(double rotation_) {
	rotation = rotation_;
};


void Shape::setPosition(double x_, double y_, double z_) {
	x = x_;
	y = y_;
	z = z_;
};

void Shape::positionInGL() {
	glTranslated(x, y, z);
	glRotated(-rotation, 0, 1, 0);
};

void Shape::setColorInGL() {
	glColor3f(red, green, blue);
};

double Shape::getRed() {
	return red;
};

double Shape::getGreen() {
	return green;
};

double Shape::getBlue() {
	return blue;
};

void Shape::setColor(float red_, float green_, float blue_) {
	red = red_;
	green = green_;
	blue = blue_;
};

//Draw command for a rectangular prism, rotation is about the initial point
void rectangularprism::draw() {
	//convert degrees to radians and find cosine and sine

		double rc = cos(3.141592765*rotation / 180);
		double rs = sin(3.141592765*rotation / 180);
	//define all vertexes
	xp[0] = x;
	xp[1] = xp[0] + xlength * rc;
	xp[3] = xp[0] - zlength * rs;
	xp[2] = (xp[1] + xp[3]) - xp[0];
	xp[4] = xp[0];
	xp[5] = xp[1];
	xp[6] = xp[2];
	xp[7] = xp[3];
	yp[0] = y;
	yp[1] = yp[0];
	yp[2] = yp[0];
	yp[3] = yp[0];
	yp[4] = yp[0] + ylength;
	yp[5] = yp[0] + ylength;
	yp[6] = yp[0] + ylength;
	yp[7] = yp[0] + ylength;
	zp[0] = z;
	zp[1] = zp[0] + xlength * rs;
	zp[3] = zp[0] + zlength * rc;
	zp[2] = zp[1] + zp[3] - zp[0];
	zp[4] = zp[0];
	zp[5] = zp[1];
	zp[6] = zp[2];
	zp[7] = zp[3];
	glBegin(GL_QUAD_STRIP);
	glVertex3d(xp[0], yp[0], zp[0]);
	glVertex3d(xp[1], yp[1], zp[1]);
	glVertex3d(xp[3], yp[3], zp[3]);
	glVertex3d(xp[2], yp[2], zp[2]);
	glVertex3d(xp[7], yp[7], zp[7]);
	glVertex3d(xp[6], yp[6], zp[6]);
	glVertex3d(xp[4], yp[4], zp[4]);
	glVertex3d(xp[5], yp[5], zp[5]);
	glVertex3d(xp[0], yp[0], zp[0]);
	glVertex3d(xp[1], yp[1], zp[1]);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3d(xp[0], yp[0], zp[0]);
	glVertex3d(xp[3], yp[3], zp[3]);
	glVertex3d(xp[7], yp[7], zp[7]);
	glVertex3d(xp[5], yp[5], zp[5]);
	glVertex3d(xp[1], yp[1], zp[1]);
	glVertex3d(xp[2], yp[2], zp[2]);
	glVertex3d(xp[6], yp[6], zp[6]);
	glVertex3d(xp[4], yp[4], zp[4]);
	glEnd();
}
//dimension settings for a rectangular prism
void rectangularprism::setdimensions(double xlength_, double ylength_, double zlength_) {
	xlength = xlength_;
	ylength = ylength_;
	zlength = zlength_;
}
//dimension settings for a triangular prism
void triangularprism::setdimensions(double base_, double height_, double offset_, double length_) {
	base = base_;
	height = height_;
	length = length_;
	offset = offset_;

}
void triangularprism::draw() {
	double rc = cos(3.141592765*rotation / 180);
	double rs = sin(3.141592765*rotation / 180);
	double x1 = x;
	double y1 = y;
	double y2 = y + height;
	double x2 = x1 + base * rc;
	double x3 = x1 + offset * rc;
	double z1 = z;
	double z2 = z1 + base * rs;
	double z3 = z1 + offset * rs;
	double x4 = x1 - length * rs;
	double z4 = z1 + length * rc;
	double x5 = x2 - length * rs;
	double z5 = z2 + length * rc;
	double x6 = x3 - length * rs;
	double z6 = z3 + length * rc;
	glBegin(GL_POLYGON);
	glVertex3d(x1, y1, z1);
	glVertex3d(x2, y1, z2);
	glVertex3d(x3, y2, z3);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3d(x4, y1, z4);
	glVertex3d(x5, y1, z5);
	glVertex3d(x6, y2, z6);
	glEnd();
	glBegin(GL_QUAD_STRIP);
	glVertex3d(x1, y1, z1);
	glVertex3d(x4, y1, z4);
	glVertex3d(x2, y1, z2);
	glVertex3d(x5, y1, z5);
	glVertex3d(x3, y2, z3);
	glVertex3d(x6, y2, z6);
	glVertex3d(x1, y1, z1);
	glVertex3d(x4, y1, z4);
	glEnd();

}


//dimension settings for a trapezoidal prism
void trapezoid::setdimensions(double base_, double height_, double offset_, double length_, double topwidth_) {
	base = base_;
	height = height_;
	length = length_;
	offset = offset_;
	topwidth = topwidth_;
}

//draw a trapezoidal prism
void trapezoid::draw() {

	double rc = cos(3.141592765*rotation / 180);
	double rs = sin(3.141592765*rotation / 180);
	xp[0] = x;
	yp[0] = y;
	yp[1] = y;
	yp[2] = y + height;
	yp[3] = y + height;
	yp[4] = y;
	yp[5] = y;
	yp[6] = y + height;
	yp[7] = y + height;
	xp[1] = xp[0] + base * rc;
	xp[2] = xp[0] + (offset + topwidth)*rc;
	xp[3] = xp[0] + offset * rc;
	zp[0] = z;
	zp[1] = zp[0] + base * rs;
	zp[2] = zp[0] + (offset + topwidth)*rs;
	zp[3] = zp[0] + offset * rs;
	xp[4] = xp[0] - length * rs;
	zp[4] = zp[0] + length * rc;
	xp[5] = xp[1] - length * rs;
	zp[5] = zp[1] + length * rc;
	xp[6] = xp[2] - length * rs;
	zp[6] = zp[2] + length * rc;
	xp[7] = xp[3] - length * rs;
	zp[7] = zp[3] + length * rc;

	glBegin(GL_POLYGON);
	glVertex3d(xp[0], yp[0], zp[0]);
	glVertex3d(xp[1], yp[1], zp[1]);
	glVertex3d(xp[2], yp[2], zp[2]);
	glVertex3d(xp[3], yp[3], zp[3]);

	glEnd();
	glBegin(GL_POLYGON);
	glVertex3d(xp[4], yp[4], zp[4]);
	glVertex3d(xp[5], yp[5], zp[5]);
	glVertex3d(xp[6], yp[6], zp[6]);
	glVertex3d(xp[7], yp[7], zp[7]);

	glEnd();
	glBegin(GL_QUAD_STRIP);
	glVertex3d(xp[0], yp[0], zp[0]);
	glVertex3d(xp[4], yp[4], zp[4]);
	glVertex3d(xp[1], yp[1], zp[1]);
	glVertex3d(xp[5], yp[5], zp[5]);
	glVertex3d(xp[2], yp[2], zp[2]);
	glVertex3d(xp[6], yp[6], zp[6]);
	glVertex3d(xp[3], yp[3], zp[3]);
	glVertex3d(xp[7], yp[7], zp[7]);
	glVertex3d(xp[0], yp[0], zp[0]);
	glVertex3d(xp[4], yp[4], zp[4]);
	glEnd();

}
void cylinder::setdimensions(double baseRadius_, double topRadius_, double height_, double innerRadius_, double outerRadius_, int slices_, int stacks_, int loops_) {

	baseRadius = baseRadius_;
	topRadius = topRadius_;
	height = height_;
	innerRadius = innerRadius_;
	outerRadius = outerRadius_;
	slices = slices_;
	stacks = stacks_;
	loops = loops_;

}

void cylinder::draw() {

	glMatrixMode(GL_MODELVIEW);
	glRotated(rotation,0,1,0); // to rotate the shape about y axis
	glTranslated(0, baseRadius, -(height)/2);

	glColor3f(1, 0, 0); // give red color to the surface
	gluCylinder(gluNewQuadric(), baseRadius, topRadius, height, slices, stacks); // draw the surface of cylinder

	glColor3f(0, 0, 1);
	gluDisk(gluNewQuadric(), innerRadius, outerRadius, slices, loops);

	glTranslated(0, 0, height);
	glColor3f(0, 1, 0); // give green color to the circle
	gluDisk(gluNewQuadric(), innerRadius, outerRadius, slices, loops); // draw the circle

}

