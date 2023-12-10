# Santa Challenge

![](https://github.com/Resistor10k1/santa-challenge/actions/workflows/santa-challenge-unit-tests.yml/badge.svg)

## Introduction

Help Santa distribute the gifts all over the world.
In 2016, a challenge to help Santa to distribute his gifts was uploaded to *kaggle.com*.

### Goal

The goal is to minimize the overall weighted-reindeer-weariness ($WRW$). This weariness is calculated with the following folmula:

$$WRW = \sum_{j=1}^m \sum_{i=1}^{n_j} \sum_{k=i}^{n_j} w_{kj} * Dist(Loc_i, Loc_{i-1})$$

The $Dist(Loc_i, Loc_j)$ function returns the Haversine distance $d$ between location $i$ and $j$.

$\phi_1, \phi_2$ : Latitude of $Loc_1$ resp. $Loc_2$ in radians<br>
$\lambda_1, \lambda_2$ : Longitude of $Loc_1$ resp. $Loc_2$ in radians<br>
$r$ : Radius of the earth (6371.0087714km)

$$ d = 2r \arcsin \left( \sqrt {\sin^2 ({\frac{\phi_2-\phi_1}{2}}) + \cos(\phi_1)\cos(\phi_2) \sin^2 ({\frac{\lambda_2-\lambda_1}{2}})} \right) $$

## Solution approach

In a first step, all gifts are sorted by the distance to the north pole in ascending order. Starting with the closest gift the tours are built with Nearest-Neighbour. For each tour a Simulated Annealing algorithm is run, to improve the tour.

## Result

For verifing the solution the Jupyter notebook provided by Mr. Beer is used. The achieved weighted-reindeer-weariness is
13'485'852'013.1237 in 1430 trips.

## Code

All code is written in C++. For a detailed code documentation refer to this [Link](/docs/doxygen/html/index.html){:target="_blank"}.

## Some other ideas

In general, just find 'a' solution and then try to improve it with local improvements such as *k-opt Neighbourhood*, *Randomized Local Search* or *Simulated Annealing*.

### How to find 'a' solution

1. Fill the sleigh with knapsack and the closest locations and optimize with some TSP algorithm.
2. K-means clustering to group the locations which are close to each other. Apply some threshold (heuristics) for maximum distance within the group and also check that the sleigh weight is not exceeded. Start with the locations furthest away and optimize with some TSP algorithm.

### Just some idea for the algorithm
*How to cluster:*<br>
1. *Take the closest point p0 and add it to the sleigh.*
2. *Check if the sleigh still has space and add the closest point to p0 to the sleigh. Repeat.*
3. *Solve TSP locally in the found point subset. The two closest point to the pole are the start resp. end points.*
4. *Restart*



