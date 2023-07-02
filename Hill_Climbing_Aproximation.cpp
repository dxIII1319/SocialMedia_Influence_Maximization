#include<iostream>
#include<fstream>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<random>
#include<queue>
#include<cmath>
#include "Graph_Formation.cpp"

namespace Hill_Climbing_Approximation //Greedy
{
    double objectiveFunction(double x) 
    {
    return sin(x) + 0.5 * sin(2 * x);
    }

    double hillClimbingApproximation(double initialGuess, double stepSize, int maxIterations) {}
}