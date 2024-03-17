#include "Color.h"

Color::Color() {
	this->r = 175;
	this->g = 122;
	this->b = 197;
}

Color::Color(std::string name) {
	if (name.compare("red") == 0)
	{
		this->r = 192;
		this->g = 57;
		this->b = 43;
	}
	else if (name.compare("blue") == 0)
	{
		this->r = 46;
		this->g = 134;
		this->b = 193;
	}
	else if (name.compare("green") == 0)
	{
		this->r = 46;
		this->g = 204;
		this->b = 113;
	}
	else if (name.compare("yellow") == 0)
	{
		this->r = 249;
		this->g = 231;
		this->b = 159;
	}
	else if (name.compare("orange") == 0)
	{
		this->r = 230;
		this->g = 126;
		this->b = 34;
	}
	else if (name.compare("purple") == 0)
	{
		this->r = 142;
		this->g = 68;
		this->b = 173;
	}
	else {
		this->r = 46;
		this->g = 134;
		this->b = 193;
	}
}