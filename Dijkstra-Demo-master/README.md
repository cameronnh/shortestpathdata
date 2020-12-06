# CS-312 Project 2 - Dijkstra's Algorithm

### Cameron Jewett, Marissa Kulz, and Chris Sousa

---

## The Algorithm

### Implementation

We implemented this algorithm to run on a **Weighted Digraph**.  While the only strict requirement is that the algorithm is intended for weighted graphs with no negative-weight edges, allowing it to run on a digraph will by nature include the ability to run on an undirected graph, at least using an adjacency matrix.  While this inflates runtimes, it is negligible on a basic demo application like this.

Our `Weighted_Digraph` Class contains a collection of `std::vector` objects in order to store all the necessary data.  The graph itself is stored as a `std::vector<std::vector<int>>`, which gives us a dynamically allocated two-dimensional array to hold the adjacency matrix.  The shortest paths calculated by Dijkstra's algorithm are recorded in a `std::vector<int>`, while the paths are stored in a `std::vector<std::string>`.  Additionally there is a `std::queue<int>`, which contains the indices of any nodes which have been reached, but not yet searched *from*.

In order to generate our internal graph, it must be read from a file.  The file contains whitespace separated data in the form of a matrix.  Each line is one row of the matrix, each entry an integer.  The integers represent the weight of an edge going from the node on that row, to the node on that column.  That is, position *(i, j)* in the matrix represents the edge weight **From** node **i** **to** node **j**.  If there is no edge, it should be set to -1.