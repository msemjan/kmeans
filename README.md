# K-Means clustering algorithm in C++

This is a simple implementation of K-means algorithm in C++. 

## What is K-Means clustering algorithm and how does it work?

K-means clustering is an algorithm that partitions *n* observations $x_1$, $x_2$, ..., $x_n$ into *k* clusters in which each observation belongs to the cluster with the closest mean.

The algorithm first assigns each point to a random cluster. 

In each iteration $t$ the algorithm performs two steps: 

1) The center of each cluster is calculated, for $i$-th cluster $S_i^t$ is the formula as follows:
    $m_i^{(t)} = \frac{1}{|S_i^t|}\sum_{x_j\in S_i^t} x_j$

2) We assign each point to the closest centroid (based on the Euclidian distance).

The algorithm converges, when the assignments no longer change. However, K-Means is not guaranteed to find the optimum. 

![Clustering obtained using my implementation of K-means algorithm](clusters.png)
