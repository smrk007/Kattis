#include <cmath>
#include <iostream>

long double lengthOfLeg2 (long double x, long double y) {
	// Finds the length of the other leg
	long double a = x*x;
	long double b = y*y;
	return sqrt(a+b);
}

long double getAngle (long double x, long double y) {
	// Returns the desired angle given the initial x and y
	long double numerator = x*x + y*y - 1;
	numerator = sqrt(numerator);
	long double denominator = x*x + y*y;
	denominator = sqrt(denominator);
	return asin(numerator/denominator);
}

class Vector {
private:
	long double x;
	long double y;
public:
	// Initializer
	Vector (long double x, long double y);
	// Mutators
	void setX (long double x);
	void setY (long double y);
	// Accessors
	long double getX();
	long double getY();
	Vector cw_rot (long double angle);
	Vector ccw_rot (long double angle);
	long double length();
	Vector normalized();
	long double getSlope();
	void print();
	// Operators
	Vector operator+ (Vector u);
	Vector operator- (Vector u);
	Vector operator/ (long double s);
};

int main() {

	int N;
	std::cin >> N;

	for (int n = 0; n < N; n++) {
		int x, y;
		std::cin >> x >> y;

		Vector point(x,y);
		long double angle = getAngle(x,y);
		
		// Case 1
		Vector case1 = point.cw_rot(angle);
		case1 = case1.normalized();
		Vector difference1 = point - case1;
		long double slope1 = difference1.getSlope();
		long double a1 = -slope1;
		long double b1 = 1;
		long double c1 = point.getX()*a1 + point.getY()*b1;

		// Case 2
		Vector case2 = point.ccw_rot(angle);
		case2 = case2.normalized();
		Vector difference2 = point - case2;
		long double slope2 = difference2.getSlope();
		long double a2 = -slope2;
		long double b2 = 1;
		long double c2 = point.getX()*a2 + point.getY()*b2;

		// Output
		std::cout << "(" << a1 << ",";
		std::cout << b1 << ",";
		std::cout << c1 << ",";
		std::cout << a2 << ",";
		std::cout << b2 << ",";
		std::cout << c2 << ")" << std::endl;
	}

	return 0;
}

// Initializer
Vector::Vector (long double x, long double y) {
	setX(x);
	setY(y);
}

// Mutators
void Vector::setX (long double x) {
	this->x = x;
}

void Vector::setY (long double y) {
	this->y = y;
}

// Accessors

long double Vector::getX() {
	return x;
}

long double Vector::getY() {
	return y;
}

Vector Vector::cw_rot (long double angle) {
	long double x = cos(angle)*getX() - sin(angle)*getY();
	long double y = sin(angle)*getX() + cos(angle)*getY();
	return Vector(x,y);
}

Vector Vector::ccw_rot (long double angle) {
	long double x = cos(-angle)*getX() - sin(-angle)*getY();
	long double y = sin(-angle)*getX() + cos(-angle)*getY();
	return Vector(x,y);
}

long double Vector::length() {
	return sqrt(x*x + y*y);
}

Vector Vector::normalized() {
	return operator/(length());
}

long double Vector::getSlope() {
	// Is -a/b
	return getY() / getX();
}

void Vector::print() {
	std::cout << "(" << getX() << "," << getY() << ")" << std::endl;
}

// Operators
Vector Vector::operator+ (Vector u) {
	return Vector(getX()+u.getX(),getY()+u.getY());
}

Vector Vector::operator- (Vector u) {
	return Vector(getX()-u.getX(),getY()-u.getY());
}

Vector Vector::operator/ (long double s) {
	return Vector(getX()/s,getY()/s);
}
