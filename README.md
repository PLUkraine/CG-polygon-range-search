# CG-polygon-range-search
Convex Polygon range search implementation

## What is the problem?
Given a set S of points on a plane find subset of S (let's call it K) of points that are placed inside of the convex polygon P.
The polygon P is NOT changing from query to query, only the set S does. 

## What is the main idea?
The main idea is to preprocess the polygon P. We split it using some point inside of it into k sectors 
(k is the number of vertices in the P). Then for each point s from S we can determine using binary search the sector it 
belongs to (by polar angle). Than we need to check if the point is inside of the triangle formed by the sector and side of the polygon.

## Screenshots
Coming soon...
