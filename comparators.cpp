#include "iostream"
#include "Point2D.h"

class PointOrderx
{

private:
    bool operator()(Point2D& a, Point2D& b){
        return (a.getx()<b.getx());
    }

};

class PointOrdery
{
    
private:
    
    bool operator()(Point2D& a, Point2D& b){
        return (a.gety()<b.gety());
    }
    
    
    
};