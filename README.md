# Milestone 2 - Solving Problems Using Advanced Algorithms
In this project we created a server that by a given problem (i.e. finding cheapest path from on node to another) solves it using sophisticated algorithms (Astar, Best First Search, BFS, DFS), and saving the path.
After solving a problem the program saves the solution in case you'll want to solve the same problem again (using the same algorithm again). We save the solution both in a local cache manager and in local files in your pc.
The server we run can be a serial server (one client connects -> the server solves his problem, another client connect and so on), and can be a parallel server (multiple clients connect -> solve each of their problem separately.


# How to compile
You should run the following command in your terminal:
```
g++ -std=c++14 *.cpp */*.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread
```
# Github
[Link](https://github.com/eladg7/Milestone_2) to our Github
