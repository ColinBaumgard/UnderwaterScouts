#include "Boat.h"


using namespace std;


Boat::Boat(double x, double y, double theta)
{
    this->set(x, y, theta);
}


double Boat::x() const{return m_x;}
double Boat::y() const{return m_y;}
double Boat::theta() const{return m_theta;}

void Boat::set(double x, double y, double theta)
{
    m_x = x;
    m_y = y;
    m_theta = theta;

    m_X.push_back(m_x);
    m_Y.push_back(m_y);
}

void Boat::move(double dx, double dy, double dtheta)
{
    m_x = m_x + dx;
    m_y = m_y + dy;
    m_theta = m_theta + dtheta;

    m_X.push_back(m_x);
    m_Y.push_back(m_y);

}


void Boat::getTraj(std::vector<vector<double>> &traj) const
{
    /*
    * Cette methode copie la trajectoire du robot dans X et Y
    * 
    */

    traj[0].clear();
    traj[0].insert(traj[0].begin(), m_X.begin(), m_X.end());
    traj[1].clear();
    traj[1].insert(traj[1].begin(), m_Y.begin(), m_Y.end());
}
