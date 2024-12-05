#ifndef POLAIRE_HPP
#define POLAIRE_HPP

class Polaire
{
private:
    double angle;
    double distance;

public:
    Polaire() : angle(0), distance(0) {};
    Polaire(double angle_val, double distance_val) : angle(angle_val), distance(distance_val) {};

    double getAngle() const { return angle; };
    double getDistance() const { return distance; };
    void setAngle(double angle_val) { this->angle = angle_val; };
    void setDistance(double distance_val) { this->distance = distance_val; };
};

#endif