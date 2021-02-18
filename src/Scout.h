#ifndef __SCOUT_H__
#define __SCOUT_H__

#include <vector>
#include <string>
#include <iostream> 
#include <cmath>
#include <tubex.h>



class Scout
{
    public:
        Scout(double x, double y, double theta, vector<Scout>* swarm, double dt);

        double x() const;
        double y() const;
        double theta() const;

        void getTraj(std::vector<vector<double>> &traj) const;
        void drawTraj();
        void draw();
        void draw_all();

        void set(double x, double y, double theta);
        void move(double dx, double dy, double dtheta);
        void cmd(double u1, double u2);

        void estimate_pos();
        void give_pos(IntervalVector pos);

    private:

        IntervalVector distances();

        double m_dev_v = 2;
        double m_dev_theta = pi/40;
        double m_dev_dist = 1;
        double m_dt;

        double m_x, m_y, m_theta, m_v;
        std::vector<IntervalVector> m_pos_e;
        Interval m_v_e, m_theta_e;
        vector<Scout>* m_swarm;
        std::vector<double> m_X;
        std::vector<double> m_Y;

};

#endif