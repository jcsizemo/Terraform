/* 
 * File:   MeshTriangle.cpp
 * Author: John
 * 
 * Created on May 1, 2013, 8:28 PM
 */

#include "MeshTriangle.h"
#include "Flame.h"

MeshTriangle::MeshTriangle(Mesh *parent, int inV0, int inV1, int inV2) {
    this->parent = parent;
    this->v0 = inV0;
    this->v1 = inV1;
    this->v2 = inV2;
    this->ctX = 0;
    this->ctY = 0;
    this->ctZ = 0;
    this->ctSpd = 0;
    this->collided = false;

    this->x0 = this->parent->verts.at(3 * v0);
    this->y0 = this->parent->verts.at(3 * v0 + 1);
    this->z0 = this->parent->verts.at(3 * v0 + 2);
    this->x1 = this->parent->verts.at(3 * v1);
    this->y1 = this->parent->verts.at(3 * v1 + 1);
    this->z1 = this->parent->verts.at(3 * v1 + 2);
    this->x2 = this->parent->verts.at(3 * v2);
    this->y2 = this->parent->verts.at(3 * v2 + 1);
    this->z2 = this->parent->verts.at(3 * v2 + 2);
    
    // Compute elements of the triangle ray matrix
    this->A = x0 - x1;
    this->B = y0 - y1;
    this->C = z0 - z1;
    this->D = x0 - x2;
    this->E = y0 - y2;
    this->F = z0 - z2;

    this->nX = B * F - C * E;
    this->nY = C * D - A * F;
    this->nZ = A * E - B * D;
    
    double mag = sqrt(nX * nX + nY * nY + nZ * nZ);
    this->nX /= mag;
    this->nY /= mag;
    this->nZ /= mag;
}

MeshTriangle::MeshTriangle(const MeshTriangle& orig) {
}

MeshTriangle::~MeshTriangle() {
}

bool MeshTriangle::intersect(double xpos, double ypos, double zpos,
        double xcam, double ycam, double zcam) {

    // Rename the components of each vertex for convienience (and save many
    // field access computations)

    // Rename ray directions for clarity and convenience
    double G = xcam;
    double H = ycam;
    double I = zcam;

    // Compute the factors in the numerator of the beta coordinate
    double EIHF = E * I - H * F;
    double GFDI = G * F - D * I;
    double DHEG = D * H - E * G;

    // Try and minimize divides (they are expensive). Compute inverse of the
    // denominator factor
    double inv_denom = 1.0 / (A * EIHF + B * GFDI + C * DHEG);

    // Compute the direction from the ray origin to the first vertex
    double J = x0 - xpos;
    double K = y0 - ypos;
    double L = z0 - zpos;

    // Compute the beta coordinate
    double beta = inv_denom * (J * EIHF + K * GFDI + L * DHEG);

    // If the intersection is out of this range it doesn't fall on the triangle
    if (beta < 0 || beta > 1 || (beta != beta))
        return false;

    // Compute the factors of the numerator of the gamma coordinate
    double AKJB = A * K - J * B;
    double JCAL = J * C - A * L;
    double BLKC = B * L - K * C;

    // Calculate the other barycentric coordinate
    double gamma = inv_denom * (I * AKJB + H * JCAL + G * BLKC);

    // If the intersection is out of this range it doesn't fall on the triangle
    if (gamma < 0 || beta + gamma > 1 || (gamma != gamma))
        return false;

    // Calculate the ray t value
    double t = -inv_denom * (F * AKJB + E * JCAL + D * BLKC);

    // Check that we are on the corrent half line of the ray
    // ray.start is 0 in this case
    // ray.end is 1. Want to check if the intersection is right in front of the player
    // t != t will be false if t is NaN
    // increase the value is t > 1 to expand influence of collision
    if (t < 0 || t > 1 || (t != t))
        return false;

    // Faster to compute location using barycentric coordinates than
    // computations using Vector3
    double weight0 = 1 - beta - gamma; // Barycentric coordinates total 1

    if (nY > 0.2 && !this->collided) {
            double oX = weight0 * this->x0 + beta * this->x1 + gamma * this->x2;
            double oY = weight0 * this->y0 + beta * this->y1 + gamma * this->y2;
            double oZ = weight0 * this->z0 + beta * this->z1 + gamma * this->z2;
            Flame *f = new Flame(oX, oY, oZ);
            if (this->parent->particles.size() < 10) {
                this->parent->particles.push_back(f);
            }
            else {
                ParticleMachine *pm = this->parent->particles.at(0);
                this->parent->particles.erase(this->parent->particles.begin());
                delete pm;
                this->parent->particles.push_back(f);
            }
    }

    this->collided = true;
    return true;

}

