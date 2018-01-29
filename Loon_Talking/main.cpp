/*
 Joshua Shewmaker
 CIS 350
 11/20/17
 
 Description: This program will take in a graph of loons that float high in the atomsphere in order to create fast temporary internet access. In order for the loons to save battery they can only talk to their two closest neighboors. If there is a tie in neighboors, the loon chooses the most western loon. If there is again, a tie, it defaults to the most southern neighbor. All the loons must be able to speak to each other. If they can not, the network will not work.  This program will allow you to see if the network you have set up will work correctly and all loons will beable to talk to each other from a parent loon.  
 
    It stores the loons and its neighboors in an adjacency matrix. Once the matrix is created with the neighbors set, it will search through the matrix and follow the path of neighbors and store the path in a vector as it goes. once the path hits a deadend it will compare the size of the path vecotr to the size of the vector that holds all of the loons. If the are equal the network will work, if the vectors are different, the network has a problem.
 */

#include<iostream>
#include<vector>
#include<cmath>
#include <climits>

using namespace std;

struct Node{
    int xCoord = 0;
    int yCoord = 0;
    int neighborA = -1;
    int neighborB = -1;
    double distanceToNeighborA = INT_MAX;
    double distanceToNeighborB = INT_MAX;
    
    Node(int x, int y){
        xCoord = x;
        yCoord = y;
    }
};

class Graph {
private:
    bool** adjacencyMatrix;
    int numberOfLoons;
public:
    /*
     Pre: This takes in the number of loons(verticies) that are going to be in the network.
     Post: Creates an adjacency matrix and sets all the values to a default of false
     */
    Graph(int vertexCount);
    /*
     Pre: Needs to know what parent node we are setting neighbors for, while the second value is the neighbor of that node.
     Post: After the function is ran, the index of the neighbor will be set to true in the adjacency matrix.
     */
    void addEdge(int i, int j);
    /*
     Pre: First value is the index of the parent loon, while the second value is a neighbor.
     Post: This function will go to the row in the adjacency matrix and search for that loons neighbor within that row. If found,
     it will return true and if its not found it will return false.
     */
    bool isEdge(int i, int j);
    /*
     Pre: Graph must be made by constructor for this function to work
     Post: Prints out graph for debugging. This allows you to see if the adjacency matrix is being created correctly and to make sure
            the neighbors are being set correctly.
     */
    void printGraph();
    /*
     Pre: Loons need to be set in the graph already and each loon needs to know its position.
     Post: This will take in a parent node(x) and any other node. This will then determine the distance between the two nodes
     */
    double findDistance(int x1, int x2, int y1, int y2);
    /*
     Pre: adajacency matrix must exist.
     Post: Deconstructs adjacency matrix inbetween graphs so the data does not interfere with the new graphs being input. It also 
        saves memory because once we run a graph through the program to get our answer we no longer need any of its data.
     */
    ~Graph();
};
Graph::Graph(int numberOfLoons) {
    this->numberOfLoons = numberOfLoons;
    adjacencyMatrix = new bool*[numberOfLoons];
    for (int i = 0; i < numberOfLoons; i++) {
        adjacencyMatrix[i] = new bool[numberOfLoons];
        for (int j = 0; j < numberOfLoons; j++)
            adjacencyMatrix[i][j] = false;
    }
}

void Graph::addEdge(int i, int j) {
    if (i >= 0 && i < numberOfLoons && j >= 0 && j < numberOfLoons) {
        adjacencyMatrix[i][j] = true;
    }
}
bool Graph::isEdge(int i, int j) {
    if (i >= 0 && i < numberOfLoons && j > 0 && j < numberOfLoons)
        return adjacencyMatrix[i][j];
    else
        return false;
}
void Graph::printGraph(){
    for(int i = 0; i < numberOfLoons; i++){
        for(int j = 0; j < numberOfLoons; j++){
            cout << adjacencyMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

double Graph::findDistance(int x1, int x2, int y1, int y2){
    double distance = 0, xDifference = 0, yDifference = 0;
    
    xDifference = x2 - x1;
    yDifference = y2 - y1;
    
    //Squares the values
    xDifference *= xDifference;
    yDifference *= yDifference;
    
    distance = sqrt(xDifference+yDifference);
    
    
    return distance;
}
Graph::~Graph() {
    for (int i = 0; i < numberOfLoons; i++){
        delete[] adjacencyMatrix[i];
        
            }
    
    delete[] adjacencyMatrix;
}


int main()
{
    int size = -1, xCoord = 0, yCoord = 0;
    double tempNeighborDistance = INT_MAX;
    vector<Node> nodeData;
    vector<int> connectedNodes;        //Saves all neighbors that can talk parent node
    
    cin >> size;
    while(size != 0){
        nodeData.clear();
        Graph map(size);
    
        //Fills vector of Nodes
        for(int i = 0; i < size; i++){
            cin >> xCoord >> yCoord;
            nodeData.push_back(Node(xCoord,yCoord));
        }
        //SETS NEIGHBORS
        for(int i = 0; i < nodeData.size(); i++){
            for(int j = 0; j < nodeData.size(); j++){
                if(i != j){
                    tempNeighborDistance =  map.findDistance(nodeData[i].xCoord, nodeData[j].xCoord, nodeData[i].yCoord, nodeData[j].yCoord);

                    if(tempNeighborDistance < nodeData[i].distanceToNeighborA){
                        if(nodeData[i].distanceToNeighborA < nodeData[i].distanceToNeighborB){
                            nodeData[i].distanceToNeighborB = nodeData[i].distanceToNeighborA;
                            nodeData[i].neighborB = nodeData[i].neighborA;
                        }
                        nodeData[i].distanceToNeighborA = tempNeighborDistance;
                        nodeData[i].neighborA = j;
                    }
                    else if(tempNeighborDistance < nodeData[i].distanceToNeighborB){
                        nodeData[i].distanceToNeighborB = tempNeighborDistance;
                        nodeData[i].neighborB = j;
                    }
                    else if(tempNeighborDistance == nodeData[i].distanceToNeighborA){
                        if(nodeData[nodeData[i].neighborA].xCoord > nodeData[j].xCoord){
                            if(nodeData[i].distanceToNeighborA < nodeData[i].distanceToNeighborB){
                                nodeData[i].neighborB = nodeData[i].neighborA;
                            }
                            else if(nodeData[i].distanceToNeighborA == nodeData[i].distanceToNeighborB){
                                if(nodeData[nodeData[i].neighborA].xCoord < nodeData[nodeData[i].neighborB].xCoord){
                                    nodeData[i].neighborB = nodeData[i].neighborA;
                                }
                            }
                            nodeData[i].neighborA = j;
                        }
                        else if(nodeData[nodeData[i].neighborA].xCoord == nodeData[j].xCoord){
                            if(nodeData[nodeData[i].neighborA].yCoord > nodeData[j].yCoord)
                                nodeData[i].neighborA = j;
                        }
                    }
                    else if( tempNeighborDistance == nodeData[i].distanceToNeighborB){
                        if(nodeData[nodeData[i].neighborB].xCoord > nodeData[j].xCoord){
                            if(nodeData[i].distanceToNeighborB < nodeData[i].distanceToNeighborA){
                                nodeData[i].neighborA = nodeData[i].neighborB;
                            }
                            else if(nodeData[i].distanceToNeighborA == nodeData[i].distanceToNeighborB){
                                if(nodeData[nodeData[i].neighborB].xCoord < nodeData[nodeData[i].neighborA].xCoord){
                                    nodeData[i].neighborA = nodeData[i].neighborB;
                                }
                            }
                            nodeData[i].neighborB = j;
                        }
                        else if(nodeData[nodeData[i].neighborB].xCoord == nodeData[j].xCoord){
                            if(nodeData[nodeData[i].neighborB].yCoord > nodeData[j].yCoord)
                                nodeData[i].neighborB = j;
                                }

                            }
                    }
            }
        }
    
    
        for(int i = 0; i < nodeData.size(); i++){
            map.addEdge(i, nodeData[i].neighborA);
            map.addEdge(i, nodeData[i].neighborB);
        }
        for(int i = 0; i < nodeData.size(); i++){
            if(map.isEdge(i, nodeData[i].neighborA) && find(connectedNodes.begin(), connectedNodes.end(), nodeData[i].neighborA) == connectedNodes.end()){
                connectedNodes.push_back(nodeData[i].neighborA);
            }
            if(map.isEdge(i, nodeData[i].neighborB) && find(connectedNodes.begin(), connectedNodes.end(), nodeData[i].neighborB) == connectedNodes.end()){
                connectedNodes.push_back(nodeData[i].neighborB);
            }
        }
    
        if(connectedNodes.size() == nodeData.size()-1)
            cout << "yes" << endl;
        else{
            cout << "no" << endl;
        }
        

        cin >> size;
    }
    return 0;
}
