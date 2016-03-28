/** @file Point2D.h
 @brief Contains the class declarations and definitions for the Point2D class
 
 @author Sneha Belkhale
 @date Febuary 11th, 2016
 
 The Point2D is a simple class that holds integer variables for the x and y coordinates of the point, and getter functions.
 
 */


#ifndef Point2D_h
#define Point2D_h

#include <stdio.h>
#include <iostream>

class Point2D
{
public:
    //constructors
    Point2D(){};
    Point2D(int x, int y):x(x), y(y){};
    //getters
    int getx();
    int gety();
    
private:
    //x position
    int x;
    //y position
    int y;

};

/** Overloading the << operator for the Point2D class so that we can print out the x and y coordinates
 
 @param os is the ostream value that we want to update 
 @param x is the Point2D object we want to print
 @return reference to the ostream value with the string (x,y) included
 
 */

std::ostream& operator<<(std::ostream&os, Point2D x)
{
    //feed the ostream the coordinates
    os<<"("<<x.getx()<<" "<<x.gety()<<")";
    return os;

}


/** Definition of the getx function
 
 @return value of the Point2D's x position
 
 */
int Point2D::getx()
{
    return x;
}
/** Definition of the gety function
 
 @return value of the Point2D's y position
 
 */
int Point2D::gety()
{
    return y;
}


#endif /* Point2D_h */
