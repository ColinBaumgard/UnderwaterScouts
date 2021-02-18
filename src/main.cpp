#include <cstdlib>
#include <iostream> 
#include <fstream>
#include <string>
#include <ctime>
#include <unistd.h>

#include <tubex.h>
#include <math.h>
#include <vector>

#include "Scout.h"

using namespace std;
using namespace tubex;

void draw_boat(vector<double> X, double l);


int main()
{
  vibes::beginDrawing();
  vibes::newFigure("Scout");
  vibes::setFigureProperties("Scout",
  vibesParams("x", 100, "y", 100, "width", 700, "height", 700));
  vibes::axisLimits(-100.,100.,-100.,100.);

  double dt = 0.1, t_max = 100;
  double l = 5, a = 50, b = 10;


  vector<double> xy(2, 0);
  vector<vector<double>> traj_Scout(2, xy);
  vector<vector<double>> traj_Boat(2, xy);

  vector<Scout> Swarm;

  Scout S1(0, 0, 0, &Swarm, dt);
  Swarm.push_back(S1);
  Scout S2(-30, 20, 0, &Swarm, dt);
  Swarm.push_back(S2);
  Scout S3(-30, -20, 0, &Swarm, dt);
  Swarm.push_back(S3);
 


  for(double t =0; t < t_max; t += dt){
    vibes::clearFigure("Scout");

    // Equation mouvement bateau
    // X[0] = a*cos(t/b);
    // X[1] = a*sin(2*t/b);
    // X[2] = atan2(a*2*cos(2*t/b)/b, a*2*cos(t/b)/b);
    Swarm[0].cmd(0, 0);
    Swarm[0].give_pos(IntervalVector{{0},{0}});
    Swarm[1].cmd(0.8, 0);
    Swarm[2].cmd(0.8, 0);

    Swarm[1].estimate_pos();
    Swarm[2].estimate_pos();

    // affichage

    for(int j=0; j < Swarm.size(); j++)
    {
      
      Swarm[j].draw_all();
      
    }
    
    




    usleep(dt*1e6);
  }


  vibes::endDrawing();

  return EXIT_SUCCESS;
}


void draw_boat(vector<double> X, double l)
{
  vector<double> A(2, 0), B(2, 0), C(2, 0);
  vector<vector<double>> AB, BC, CA;
  double L = l/4;

  A[0] = X[0] + L*cos(X[2] + pi/2) - l/3*cos(X[2]);
  A[1] = X[1] + L*sin(X[2] + pi/2) - l/3*sin(X[2]);

  B[0] = X[0] - L*cos(X[2] + pi/2) - l/3*cos(X[2]);
  B[1] = X[1] - L*sin(X[2] + pi/2) - l/3*sin(X[2]);

  C[0] = X[0] + l*cos(X[2]) - l/3*cos(X[2]);
  C[1] = X[1] + l*sin(X[2]) - l/3*sin(X[2]);

  AB.push_back(A);
  AB.push_back(B);

  BC.push_back(B);
  BC.push_back(C);

  CA.push_back(C);
  CA.push_back(A);

  vibes::drawLine(AB);
  vibes::drawLine(BC);
  vibes::drawLine(CA);

}