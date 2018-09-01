
#ifndef MTRN3500_SHAPE_H
#define MTRN3500_SHAPE_H

// Abstract class
class Shape {

public:
	Shape();
	Shape(double x_, double y_, double z_);
	Shape(double x_, double y_, double z_, double rotation_);
	virtual ~Shape();

	virtual void draw() = 0;

	double getX();
	double getY();
	double getZ();
	double getRotation();

	void setX(double x_);
	void setY(double y_);
	void setZ(double z_);
	void setRotation(double rotation_);

	void setPosition(double x_, double y_, double z_);

	void positionInGL();
	void setColorInGL();

	double getRed();
	double getGreen();
	double getBlue();
	void setColor(float red_, float green_, float blue_);

protected:
	double x, y, z;               // position
	double rotation;              // heading of the object in the horizontal plane (degrees)
	float red, green, blue;       // colour of object

};

class rectangularprism : public Shape {
public:

	void draw();
	void setdimensions(double xlength_, double ylength_, double zlength_);
protected:
	double xlength, ylength, zlength;

};

class triangularprism : public Shape {
public:
	void draw();
	void setdimensions(double base_, double height_, double offset_, double length);
protected:
	double base, height, offset, length;//offset is the distance along the x axis of the top point from the starting point
};

class cylinder : public Shape {
public:

	void draw();
	void setdimensions(double baseRadius_, double topRadius_, double height_, double innerRadius_, double outerRadius_, int slices_, int stacks_, int loops_);

protected:

	double baseRadius, topRadius, height, innerRadius, outerRadius;
	int slices, stacks, loops;
};

#endif // for MTRN3500_SHAPE_H
