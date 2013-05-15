/* 
 * File:   Light.h
 * Author: John
 *
 * Created on May 14, 2013, 7:36 PM
 */

#ifndef LIGHT_H
#define	LIGHT_H

class Light {
public:
    Light(double xpos, double ypos, double zpos, 
            double r, double g, double b);
    virtual ~Light();
    double xpos;
    double ypos;
    double zpos;
    double r;
    double g;
    double b;
private:

};

#endif	/* LIGHT_H */

