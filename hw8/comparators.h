/** @file comparators.h
 @brief Contains the class declarations and definitions for two comparator classes that we can use to set an ordering for the Point2D class.
 @author Sneha Belkhale
 @date Febuary 11th, 2016

	PointOrderx is a class that orders the Point2D objects based on x component, while PointOrdery orders based on y component
 */

#ifndef comparators_h
#define comparators_h
#include "iostream"
#include "Point2D.h"


/**@class PointOrderx
	@brief Class to order the Point2D objects based on the x component
 */

class PointOrderx
{
public:
    //overload comparison operator()
    bool operator()(Point2D& a, Point2D& b);
};

/**overloading the operator () so that we can compare two objects of type Point2D based on x component
 
 @param a is the first Point2D you want to compare
 @param b is the second Point2D you want to compare
 */
bool PointOrderx:: operator()(Point2D &a, Point2D &b)
{
    //return true if a.x is less than b.x
    return (a.getx()<b.getx());
}



/**@class PointOrdery
	@brief Class to order the Point2D objects based on the y component
 */
class PointOrdery
{
public:
    bool operator()(Point2D& a, Point2D& b);
};

/**overloading the operator () so that we can compare two objects of type Point2D based on y component
 
 @param a is the first Point2D you want to compare
 @param b is the second Point2D you want to compare
 */
bool PointOrdery:: operator()(Point2D &a, Point2D &b)

{
    //return true if a.y is less than b.y
    return (a.gety()<b.gety());
}

#endif /* comparators_h */
