#ifndef __BOAT_H__
#define __BOAT_H__

#include <vector>
#include <string>
#include <iostream> 
#include <cmath>
#include <tubex.h>



class Boat
{
    public:
        Boat(double x, double y, double theta);

        double x() const;
        double y() const;
        double theta() const;

        void getTraj(std::vector<vector<double>> &traj) const;

        void set(double x, double y, double theta);
        void move(double dx, double dy, double dtheta);

    private:

        double m_x, m_y, m_theta;
        std::vector<double> m_X;
        std::vector<double> m_Y;

};

#endif