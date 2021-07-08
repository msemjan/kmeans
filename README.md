# K-Means clustering algorithm in C++

This is a simple implementation of K-means algorithm in C++. 

## What is K-Means clustering algorithm and how does it work?

K-means clustering is an algorithm that partitions *n* observations <a href="https://www.codecogs.com/eqnedit.php?latex=x_1,&space;x_2,&space;...,&space;x_n" target="_blank"><img src="https://latex.codecogs.com/gif.latex?x_1,&space;x_2,&space;...,&space;x_n" title="x_1, x_2, ..., x_n" /></a> into *k* clusters in which each observation belongs to the cluster with the closest mean.

*k* is a user defined parameter that has to be provided beforehand. 

1) The algorithm first assigns each point to a random cluster. 

2) The center of each cluster is calculated, for *i*-th cluster <a href="https://www.codecogs.com/eqnedit.php?latex=S_i^t" target="_blank"><img src="https://latex.codecogs.com/gif.latex?S_i^t" title="S_i^t" /></a> is the formula as follows:

    <a href="https://www.codecogs.com/eqnedit.php?latex=m_i^{(t)}&space;=&space;\frac{1}{|S_i^t|}\sum_{x_j\in&space;S_i^t}&space;x_j" target="_blank"><img src="https://latex.codecogs.com/gif.latex?m_i^{(t)}&space;=&space;\frac{1}{|S_i^t|}\sum_{x_j\in&space;S_i^t}&space;x_j" title="m_i^{(t)} = \frac{1}{|S_i^t|}\sum_{x_j\in S_i^t} x_j" /></a>

3) We assign each point to the closest centroid (based on the Euclidian distance).

4) The algorithm performs steps 2) and 3) in each iteration *t*. 
5) The algorithm converges, when the assignments no longer change. 
 
However, the K-Means algorithm is not guaranteed to find the optimum. 

![Clustering obtained using my implementation of K-means algorithm](clusters.png)

## Compilation

Just run:
`g++ src/main.cpp -o kmeans.out`

Execute with:
`./kmeans.out`

The algorithm takes data from `data_train.csv` and `data_test.csv`. This version supports three-dimensional data points.

Tested on Linux.
