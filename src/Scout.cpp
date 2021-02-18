#include "Scout.h"


using namespace std;


Scout::Scout(double x, double y, double theta, vector<Scout>* swarm, double dt)
{
    this->set(x, y, theta);
    
    m_swarm = swarm;
    m_dt = dt;
}

double Scout::x() const{return m_x;}
double Scout::y() const{return m_y;}
double Scout::theta() const{return m_theta;}
void Scout::give_pos(IntervalVector pos){m_pos_e.push_back(pos);}


void Scout::set(double x, double y, double theta)
{
    m_x = x;
    m_y = y;
    m_theta = theta;

    m_X.push_back(m_x);
    m_Y.push_back(m_y);

    m_pos_e.push_back(IntervalVector({{m_x},{m_y}}));
}

void Scout::move(double dx, double dy, double dtheta)
{
    m_x += dx;
    m_y += dy;
    m_theta += dtheta;

    m_X.push_back(m_x);
    m_Y.push_back(m_y);

}

void Scout::cmd(double u1, double u2)
{
    double dy = m_v*sin(m_theta)*m_dt;
    double dx = m_v*cos(m_theta)*m_dt;
    m_v += u1 - 0.1*m_dt*pow(m_v, 2);

    this->move(dx, dy, u2);

    m_v_e = Interval(m_v).inflate(m_dev_v);
    m_theta_e = Interval(m_theta).inflate(m_dev_theta);
    //cout << "vitesse et angle est : " << m_v_e << ", " << m_theta_e << endl;

}

void Scout::getTraj(std::vector<vector<double>> &traj) const
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

void Scout::drawTraj()
{
    for(int i=1; i < m_X.size(); i++)
        {
        vector<double> l_x = {m_X[i], m_X[i-1]};
        vector<double> l_y = {m_Y[i], m_Y[i-1]};
        vibes::drawLine(l_x, l_y);
        }
}

void Scout::draw()
{
    vibes::drawAUV(m_x, m_y, m_theta*180/pi, 2.5, "red");
    vibes::drawBox(m_pos_e.back(), "green");

    for(int i=0; i < m_pos_e.size(); i++)
    {
        if(i%7 == 0)
        {
           vibes::drawBox(m_pos_e[i], "green"); 
        }
    }
  

    
}

void Scout::draw_all()
{
    this->drawTraj();
    this->draw();
}




void Scout::estimate_pos()
{
    // estimation avec l'état :
    IntervalVector pos_e = m_pos_e.back();
    pos_e[0] += m_dt*m_v_e*cos(m_theta_e);
    pos_e[1] += m_dt*m_v_e*sin(m_theta_e);

    IntervalVector d = this->distances();
    tubex::CtcDist ctc_dist; 

    // for(int i=0; i < d.size(); i++)
    // {
    //     ctc_dist.contract(pos_e, )
    // }

    m_pos_e.push_back(pos_e);

    

}


IntervalVector Scout::distances()
{
    IntervalVector d(m_swarm->size()-1, Interval(0));
    int i = 0;
    for(int j=0; j < m_swarm->size(); j++)
    {
        if(this != &m_swarm->at(j))
        {
            double dist = sqrt((pow((m_x - m_swarm->at(j).x()), 2) + pow((m_y - m_swarm->at(j).y()), 2)));
            d[i] = Interval(dist).inflate(m_dev_dist);
            i++;
        }
    }
    return d;
} 