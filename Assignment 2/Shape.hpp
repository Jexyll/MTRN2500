
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

	//double xpoint, ypoint, zpoint; as above, unneccesary

protected:
	double x, y, z;               // position
	double rotation;              // heading of the object in the horizontal plane (degrees)
	float red, green, blue;       // colour of object
      // position of object relative to center of rotation of vehicle

};



class rectangularprism : public Shape{
public:
	rectangularprism(){}
	rectangularprism(double xlength_, double ylength_, double zlength_)
		: xlength(xlength_), ylength(ylength_), zlength(zlength_)
	{}
	void draw();
	void setdimensions(double xlength_, double ylength_, double zlength_);
protected:
	double xlength, ylength, zlength;

};

class triangularprism : public Shape {
public:
	triangularprism(double sidea_, double sideb_, double angle_, double length_)//constructor
		:sidea(sidea_), sideb(sideb_), angle(angle_), length(length_)	{}
	void draw();
	void setdimensions(double sidea_, double sideb_, double angle_, double length_);
protected:
	double sidea, sideb, angle, length;//offset is the distance along the x axis of the top point from the starting point
};

class trapezoid : public Shape {
public:
	trapezoid(double base_, double height_, double offset_, double length_, double topwidth_)
		:base(base_), height(height_), offset(offset_), length(length_), topwidth(topwidth_)
	{
	}
	void draw();
	void setdimensions(double base_, double height_, double offset_, double length_, double topwidth_);


protected:
	double base, height, offset, length, topwidth;//offset is the distance along the x axis of the top point from the starting point

};

class cylinder : public Shape {
public:
	//rectangularprism(double xlength_, double ylength_, double zlength_)
	//	: xlength(xlength_), ylength(ylength_), zlength(zlength_)
	//{};
	cylinder();
	cylinder(double baseRadius_, double topRadius_, double height_, int slices_, int stacks_, int loops_)
		:baseRadius(baseRadius_), topRadius(topRadius_), height(height_), slices(slices_), stacks(stacks_), loops(loops_)
	{};
	void draw();
	void setdimensions(double baseRadius_, double topRadius_, double height_, int slices_, int stacks_, int loops_);

protected:

	double baseRadius, topRadius, height;
	int slices, stacks, loops;
};

#endif // for MTRN3500_SHAPE_H