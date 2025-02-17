#ifndef GRAPH_H
#define GRAPH_H
#include<vector>
#include<QString>
#include<Qhash>
#include <unordered_set>
#include <utility>


struct Transportation {
    QString name;
    int cost;

    Transportation(QString s, int n) : name(std::move(s)), cost(n) {}

    // Getter for name
    QString getName() const {
        return name;
    }

    // Setter for name
    void setName(const QString& newName) {
        name = newName;
    }

    // Getter for cost
    int getCost() const {
        return cost;
    }

    // Setter for cost
    void setCost(int newCost) {
        cost = newCost;
    }
};


struct Node {
    QString nodeName;
    float centerX;
    float centerY;
    int radius;
    Node() = default;

    Node(QString Name,float x,float y) : nodeName(std::move(Name)),centerX(x),centerY(y) {
        centerX=x;
        centerY=y;
        radius=20;
    }
    Node(QString Name) : nodeName(std::move(Name)) {
        centerX=50;
        centerY=50;
        radius=20;
    }
    Node(QString name,int cenX,int cenY,int rad):nodeName(name),centerX(cenX),centerY(cenY),radius(rad){

    }
    bool operator<(const Node& other) const {
        return nodeName < other.nodeName;
    }
    bool operator==(const Node& other) const {
        return nodeName == other.nodeName;
    }
    // Getter for nodeName
    QString getNodeName() const {
        return nodeName;
    }

    // Setter for nodeName
    void setNodeName(const QString& newName) {
        nodeName = newName;
    }
};

struct Edge {
    Node parent;
    Node destination;
    Transportation option;
    float startX;
    float startY;
    float endX;
    float endY;
    double getCost() const { return option.getCost(); } //ahmed sameh

    Edge(Node prnt, Node dest, Transportation opt)
        : parent(std::move(prnt)), destination(std::move(dest)), option(std::move(opt)) {
    startX=1;
    startY=1;
    endX=1;
    endY=1;
    }
    bool operator==(const Edge& other) const {
        return parent == other.parent && destination == other.destination && option.cost == other.option.cost && option.name == other.option.name;
    }
    // Getter for parent
    Node getParent() const {
        return parent;
    }

    // Setter for parent
    void setParent(const Node& newParent) {
        parent = newParent;
    }

    // Getter for destination
    Node getDestination() const {
        return destination;
    }

    // Setter for destination
    void setDestination(const Node& newDest) {
        destination = newDest;
    }

    // Getter for options
    Transportation getOption() const {
        return option;
    }

    // Setter for options
    void setOptions(const Transportation& newOption) {
        option = newOption;
    }
};
struct PairHash {
    std::size_t operator()(const std::pair<QString, QString>& pair) const {
        return qHash(pair.first) ^ qHash(pair.second);
    }
};
struct NodeHash {
    std::size_t operator()(const Node& node) const {

        return std::hash<QString>{}(node.nodeName) ^
               std::hash<float>{}(node.centerX) ^
               std::hash<float>{}(node.centerY) ^
               std::hash<int>{}(node.radius);
    }
};
class Graph
{

private: std::unordered_map<Node, std::vector<Edge>, NodeHash> adjcencyList;

public:
    Graph();

    Node back();
    Node front();

    bool readGraphFile( const QString&fileName);
    void printGraph();
    void addNode( const Node& newNode);
    void updateEdge(const Node& source, const Node& destination, const QString& oldTransportation, const QString& newTransportation, int newCost) ;
    std::vector<Edge>getEdges(Node Source);

    std::vector<Node> getNodes() ;
    std::vector<Node>& getNodesRef() const;
    std::vector<Node> getNodes() const;
    const std::vector<Edge>& getEdgesRef() const;
    std::vector<Edge>getEdges();
    std::vector<Edge> getEdges2(const QString& nodeName) const;
    const std::unordered_set<QString> getConnectedNodes(const Node& node) const;
    int size();
    int edgesLength(Node &node);
    void clear();

    std::vector<std::vector<Node>> findAllPaths(const Node& startNode, const Node& endNode);               //ahmed sameh
    Node getNodeByName(const QString& nodeName) const;                                                     //ahmed sameh
    std::vector<std::vector<Node>> findUniquePaths(const Node& startNode, const Node& endNode) const;      //ahmed sameh
    bool hasDuplicatePath(const std::vector<Node>& path) const;                                            //ahmed sameh

    bool empty();
    bool isValidNode(const QString& nodeName) const;
    bool isValidEdge(const QString& sourceNode, const QString& destinationNode, const QString& transportationName) const;
    void addEdge(Node From,Node dest,Transportation opt);                                         //{WAHDAN}==> THESE FUNCTIONS WILL BE IMPLEMENTED BY [RAHAF-RAWAN,BASMALA1]
    void deleteEdge(const Node& source, const Node& destination,const QString& transportationName);                                          //{WAHDAN}==> A GRAPH IS COMPLETE IF EVERY NODE HAS EDGES TO EVERY OTHER NODE IN THE GRAPH
    bool isCompleteGraph();     //{WAHDAN}==> SEARCH ON HOW TO DO IT USING AN ALGORITHM
    // void writeGraphToFile(const QString& fileName);
    void writeGraphToFile(const QString& fileName);
    bool hasEdge(const Node& source, const Node& destination)const;
    std::vector<Node> DFS(Node& StartNode);
    std::vector<Node> BFS(Node& startNode);
};
#endif // GRAPH_H

