

## Overview

- Technical details about the build system and computational machine used: [Section Technical details](#technical-details)

- Additional information to the mathematics behind the optimization problem [Section Some mathematics](#some-mathematics)

- <a href="https://resistor10k1.github.io/santa-challenge/doxygen/html/index.html">Code documentation</a>

- <a href="https://resistor10k1.github.io/santa-challenge/figures/map.html" target="_blank">Interactive map</a>


## Technical details

- Compiler:  GNU 11.4.0 
- Optimization:  -O3
- CPU: Intel(R) Core(TM) i7-4790K CPU @ 4.00GHz with 8 Cores (physical + virtual)


## Some mathematics

Recall the goal to help Santa distribute the gifts all over the world. Therefore, the overall weighted-reindeer-weariness ($WRW$) must be minimized. All sleigh trips start at the North-Pole (Lat=90, Long=0), then head to each gift in a specified order, and finally head back to the North-Pole. Santa's sleigh has a base weight of 10 and a weight limit of 1000 (excluding the sleigh base weight).

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

