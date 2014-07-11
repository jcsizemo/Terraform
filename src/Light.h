/* 
 * File:   Light.h
 * Author: John
 * 
 * Light class used in Phong shading.
 *
 * Created on May 14, 2013, 7:36 PM
 */

#ifndef LIGHT_H
#define	LIGHT_H

class Light {
public:
    Light(double xpos, double ypos, double zpos, 
            double r, double g, double b); // init light with rgb values and position
    virtual ~Light();
    double xpos; // position
    double ypos;
    double zpos;
    double r; // rgb values
    double g;
    double b;
private:

};

#endif	/* LIGHT_H */

