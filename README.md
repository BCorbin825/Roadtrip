The Desperate Three
11/12/2021
Brandon Corbin, Francisco Sanchez, Zachary Webb
US Travel Guide 

Overview
  In this project we will be implementing Dijkstra’s algorithm and DFS  to traverse a graph. To make this more comprehensive we will be representing these algorithms graphically 
in order to demonstrate how they function. This representation will be through  a map of the United States and each vertex represents a city in the US.

Problem 
  We are trying to represent these algorithms graphically in order to improve understanding of how they work internally. In order to accomplish this we will be solving a common 
problem relating to GPS. That is finding the best path between two points. We will be building an adjacency list to represent the cities in the US and then implementing 
Dijkstra’s algorithm to find the shortest path between two cities and DFS to find the first path found between two cities. This will allow us to compare how Dijkstra’s and DFS 
compare in finding a path between nodes. The edges of the graph will be weighted and these weights will represent the distance in miles between each vertex (city). 

Motivation
	For many people it is hard to grasp new concepts simply by reading about them. Visuals are known to improve learning and understanding new concepts which is what we hope to do
with this project. We believe that this also helps us as the programmers better understand and solve real world problems in programming which will help us improve our knowledge 
and problem solving skills.

Features
  We have solved the problem when we have completed the graph data structure, the search algorithms, displayed these algorithms graphically, and implemented an interface to allow 
user intervention. 

Data
	Our data set will be cities in the US. Vertices are cities, and edges connect cities near each other and are weighted by the distance in miles. This data will be supported by 
the free database from https://simplemaps.com/data/us-cities. It has every incorporated city in the US. It tracks their longitude and latitude, which we can use to calculate 
the distance between them. 
  
Tools
	To complete this project we will be using C++ and the SFML graphical library.
  
Visuals
  The GUI will have two text boxes to accept the start and ending cities, as well as a random button to generate a start and end. It will also have a scroll menu to pick from 
all available cities, filtered based on what’s currently in the text box. The program will show the length between the cities  and time to complete for both algorithms. For 
visual clarity, only the top 100 or so cities will be displayed at all times, other vertices will be shown only if they are a part of either path. 

Strategy
	For this project we will be using an adjacency list to represent the graph. We will be performing Dijkstra’s algorithm and DFS on the adjacency list to find a path between two
points.

Distribution of Responsibility and Roles
	Brandon Corbin will be handling the graphical portion of the project which includes the interface and all components that come with it, Francisco Sanchez will handle 
Djikstra’s and DFS algorithms, Zachary Webb will handle managing the dataset and converting it into an adjacency list graph. 

