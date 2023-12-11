# Santa Challenge

![](https://github.com/Resistor10k1/santa-challenge/actions/workflows/santa-challenge-unit-tests.yml/badge.svg)

## Introduction

In the context of a algorithms course, the santa challenge could be solved as a voluntary exercise. This repository contains the code and a short description on how the exercise is solved.
This challenge has originally been uploaded to <a href="https://www.kaggle.com/competitions/santas-stolen-sleigh" target="_blank">kaggle.com</a> in 2016.

See [Goal](#goal-of-the-challenge) for the description of the problem, which is basically just the description found on <a href="https://www.kaggle.com/competitions/santas-stolen-sleigh" target="_blank">kaggle.com</a>.

See [Result](#result) for the result achieved with the code in this repository.

Refer to the <a href="https://resistor10k1.github.io/santa-challenge/" target="_blank">wiki</a> for additional information.

## Setup

### Build

First, clone the git repository. Afterwards, configure CMake and build the project.
```
git clone https://github.com/Resistor10k1/santa-challenge.git
cd santa-challenge
mkdir build && cd build
cmake ..
cmake --build . --target all
```

### Run

Jump into to build folder (`cd build`) and run the program. The program takes the relative path to the data file as an argument. If no argument is given, a small example data file is taken to show the program's functionality.
```
./santa-challenge "../data/gifts.csv"
```



## Goal of the challenge

Help Santa distribute the gifts all over the world. Therefore, the overall weighted-reindeer-weariness ($WRW$) must be minimized. All sleigh trips start at the North-Pole (Lat=90, Long=0), then head to each gift in a specified order, and finally head back to the North-Pole. Santa's sleigh has a base weight of 10 and a weight limit of 1000 (excluding the sleigh base weight).

The weighted-reindeer-weariness is calculated with the following folmula:

$$WRW = \sum_{j=1}^m \sum_{i=1}^{n_j} \sum_{k=i}^{n_j} w_{kj} * Dist(Loc_i, Loc_{i-1})$$

Where $m$ is the number of trips, $n_j =$(#gifts for trip $j$)$+1$, $w_{ij}$ is the weight of the $i$-th gift at trip $j$, $Loc_i$ is the location of gift $i$. $Loc_0$ and $Loc_{n_j}$ are the North-Pole, and $w_{n_{j},j}$ (the last leg of each trip) is always the base weight of the sleigh.

The $Dist(Loc_i, Loc_{i-1})$ function returns the Haversine distance $d$ between location $i$ and $i-1$.

$\varphi_1, \varphi_2$ : Latitude of $Loc_1$ resp. $Loc_2$ in radians<br>
$\lambda_1, \lambda_2$ : Longitude of $Loc_1$ resp. $Loc_2$ in radians<br>
$r$ : Radius of the earth (6371.0087714km)

$$ d = 2r \arcsin \left( \sqrt {\sin^2 ({\frac{\varphi_2-\varphi_1}{2}}) + \cos(\varphi_1)\cos(\varphi_2) \sin^2 ({\frac{\lambda_2-\lambda_1}{2}})} \right) $$

#### Example

Two gifts $A$ and $B$ are delivered in a trip. Then the $WRW$ is calculated as follows:

$$
\begin{aligned}
&Dist(NorthPole \rightarrow A) &&* (base\_weight + weight(B) + weight(A))&& \\
&Dist(A \rightarrow B) &&* (base\_weight + weight(B))&& \\
&Dist(B \rightarrow NorthPole) &&* (base\_weight)&&
\end{aligned}
$$

## Solution approach

In a first step, all gifts are sorted by the distance to the North-Pole in ascending order. Starting with the closest gift, the tours are built with Nearest-Neighbour approach. For each tour, a Simulated Annealing algorithm is run, to improve the tour.

## Result

For verifing the solution a Jupyter notebook provided by the lecturer is used. The achieved weighted-reindeer-weariness is
13'485'852'013.1237 in 1430 trips.

## Code

All code is written in C++. For a detailed code documentation refer to this <a href="https://resistor10k1.github.io/santa-challenge/docs/doxygen/html/index.html" target="_blank">Link</a> (Link does not work out of the repository!).

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



