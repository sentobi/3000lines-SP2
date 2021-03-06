/******************************************************************************/
/*!
\file	Item.cpp
\author 3000 Lines Studio
\brief
Functions for items and gifts
*/
/******************************************************************************/

#include "Item.h"

//Item abstract class
/******************************************************************************/
/*!
\brief	Item default constructor
*/
/******************************************************************************/
Item::Item() : name_("")
{
}

/******************************************************************************/
/*!
\brief	Item default constructor
\param name
name of item
*/
/******************************************************************************/
Item::Item(std::string name) : name_(name)
{
}

/******************************************************************************/
/*!
\brief	Item default destructor
*/
/******************************************************************************/
Item::~Item()
{
}

std::string Item::getName()
{
	return name_;
}

//Gift item
/******************************************************************************/
/*!
\brief	Gift default constructor
*/
/******************************************************************************/
Gift::Gift() : Item()
{
}

/******************************************************************************/
/*!
\brief	Gift default constructor
\param name
name of gift
\param value
price of gift
*/
/******************************************************************************/
Gift::Gift(std::string name, int value) : Item(name), value_(value)
{

}

/******************************************************************************/
/*!
\brief	Gift default destructor
*/
/******************************************************************************/
Gift::~Gift()
{
}
/******************************************************************************/
/*!
\brief	Getting value of gift item
*/
/******************************************************************************/
float Gift::getValue()
{
	return value_;
}