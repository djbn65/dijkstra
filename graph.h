#ifndef GRAPH_H
#define GRAPH_H

#include <limits>
#include <iostream>
#include "MyList.h"
#include <stdexcept>
#include <sstream>
#include "MyHeap.h"

using std::string;
using std::stof;
using std::stringstream;

const float UNVISITED = 0;
const float VISITED = 1;
const float INFINITY = std::numeric_limits<float>::infinity();
const float NO_VAL = -1;
const string EMPTY = "EMPTY";

//Used in Dijstra's algorithm to hold the distance to a specific node
//for priority queue purposes
struct DijkElem {
  float vertex, weight;
  DijkElem() { vertex = -1; weight = -1; }
  DijkElem(float v, float w) { vertex = v; weight = w; }
};

//comparison class for struct DijkElem
struct DDComp {
  static bool prior(DijkElem x, DijkElem y)
  {
    return x.weight < y.weight;
  }
};

//holds the currency name and value (bribe cost)
struct Currency {
  Currency() {}
  Currency(string n, float v) { name = n; value = v; }
  string name;
  float value;
};

//Graph class implementation using a doubly linked list to store adjacency
//values
class Graph {
  private:
    int vertices, edges;
    MyList<MyList<float>> adjMatr;
    MyList<float> markArr;
    MyList<Currency> nodeCurrencies;

  public:
    Graph() {}

    Graph(const int numVert) {
      vertices = numVert;
      edges = 0;
      for (int i = 0; i < numVert; i++)
        markArr.push_back(UNVISITED);

      for (int i = 0; i < numVert; i++)
        adjMatr.push_back(MyList<float>());

      for (int i = 0; i < numVert; i++)
        for (int j = 0; j < numVert; j++)
          adjMatr[i].push_back(0);

      for (int i = 0; i < numVert; i++)
        nodeCurrencies.push_back(Currency(EMPTY, NO_VAL));
    }

    int numVert() const { return vertices; }
    int numEdges() const { return edges; }

    int firstNeighbor(const int v) {
      for (int i = 0; i < vertices; i++)
        if (isEdge(v, i))
          return i;
      return vertices;
    }

    int nextNeighbor(const int v, const int w) {
      for (int i = w+1; i < vertices; i++)
        if (isEdge(v, i))
          return i;
      return vertices;
    }

    void setEdge(const int v1, const int v2, const float wt) {
      if (v1 < vertices && v2 < vertices && v1 >= 0 && v2 >= 0 && wt >= 0)
      {
        if (adjMatr[v1][v2] == 0 && wt != 0)
          edges++;
        else if (adjMatr[v1][v2] != 0 && wt == 0)
          edges--;
        adjMatr[v1][v2] = wt;
      }
      else
        throw std::out_of_range("Graph::setEdge");
    }

    void delEdge(int v1, int v2) {
      if (v1 < vertices && v2 < vertices && v1 >= 0 && v2 >= 0)
      {
        if (isEdge(v1,v2))
          edges--;
        adjMatr[v1][v2] = 0;
      }
      else
        throw std::out_of_range("Graph::delEdge");
    }

    bool isEdge(const int v1, const int v2) {
      if (v1 < vertices && v2 < vertices && v1 >= 0 && v2 >= 0)
        return adjMatr[v1][v2] != 0;
      else
        throw std::out_of_range("Graph::isEdge");
    }

    float weight(const int v1, const int v2) {
      if (v1 < vertices && v2 < vertices && v1 >= 0 && v2 >= 0)
        return adjMatr[v1][v2];
      else
        throw std::out_of_range("Graph::weight");
    }

    int getMark(const int v) {
      if (v < vertices && v >= 0)
        return markArr[v];
      else
        throw std::out_of_range("Graph::getMark");
    }

    string getCurrency(const int v) {
      if (v < vertices && v >= 0)
        return nodeCurrencies[v].name;
      else
        throw std::out_of_range("Graph::getCurrency");
    }

    float getCurrencyVal(const int v) {
      if (v < vertices && v >= 0)
        return nodeCurrencies[v].value;
      else
        throw std::out_of_range("Graph::getCurrencyVal");
    }

    int iToCurrName(string& name) {
      for (int i = 0; i < numVert(); i++)
        if (getCurrency(i) == name)
          return i;
      return vertices;
    }

    void setCurrency(const int v, const float bribe, const string& currency) {
      if (v < vertices && v >= 0)
      {
        nodeCurrencies[v].name = currency;
        nodeCurrencies[v].value = bribe;
      }
      else
        throw std::out_of_range("Graph::setCurrency");
    }

    void setMark(const int v, const int val) { markArr[v] = val; }

    void clearMarks() {
      for (int i = 0; i < markArr.size(); i++)
        markArr[i] = UNVISITED;
    }

    void print() {
      for (int i = 0; i < vertices; i++)
      {
        for (int j = 0; j < vertices; j++)
        {
          cout << adjMatr[i][j] << " ";
        }
        cout << endl;
      }
    }
};

//via STDIN a graph is created based on a csv file setup
Graph makeGraph() {
  MyList<string> names;
  MyList<string> values;
  string temp;
  char tempChar;
  int i;

  cin.get(tempChar);
  while (tempChar == ',') {
    cin >> temp;
    names.push_back(temp);
    cin.get(tempChar);
    getline(cin, temp, ')');
    temp = temp.substr(1, temp.length()-1);
    values.push_back(temp);
    cin.get(tempChar);
  }

  Graph G(names.size());

  for (int i = 0; i < names.size(); i++)
    G.setCurrency(i, stof(values[i]), names[i]);

  string end = "";

  for (int i = 0; i < G.numVert(); i++)
    end += ",";

  cin >> temp;
  do {
    i = G.iToCurrName(temp);

    getline(cin, temp, ',');
    for (int j = 0; j < names.size()-1; j++)
    {
      getline(cin, temp, ',');
      G.setEdge(i, j, stof(temp));
    }
    cin >> temp;
    G.setEdge(i, names.size()-1, stof(temp));

    cin >> temp;
  } while (temp != end);

  return G;
}

//via STDIN the start and end are found through string parsing
void findStartEnd(string& start, string& end) {
  char tmp;
  for (int i = 0; i < 7; i++)
    cin >> start;
  start = start.substr(0, start.length()-1);
  cin >> end;
  cin.get(tmp);
  getline(cin, end, '?');
  end = end.substr(0, end.length()-1);
}

//Implementation of Dijkstra's algoritm with a priority queue that
//also takes node weights into consideration in the instance
//of a tie happening between shortest paths
void Dijkstra(Graph& G, MyList<float>& D, MyList<float>& V, MyList<float>& N, int s) {
  G.clearMarks();
  int i, v, w;
  DijkElem temp;
  DijkElem E[G.numEdges()];
  temp.weight = 0; temp.vertex = s;
  E[0] = temp;
  MyHeap<DijkElem, DDComp> H(E, 1);
  for (i = 0; i < G.numVert(); i++)
  {
    D[i] = INFINITY;
    V[i] = -1;
    N[i] = INFINITY;
  }
  D[s] = 0;
  N[s] = 0;
  for (i = 0; i < G.numVert(); i++) {
    do {
      if (H.size() == 0) return;
      temp = H.top();
      H.pop();
      v = temp.vertex;
    } while (G.getMark(v) == VISITED);
    G.setMark(v, VISITED);
    if (D[v] == INFINITY) return;
    for (w=G.firstNeighbor(v); w < G.numVert(); w = G.nextNeighbor(v, w))
    {
      if (D[w] > (D[v] + G.weight(v, w))) {
        D[w] = D[v] + G.weight(v,w);
        N[w] = N[v] + G.getCurrencyVal(v);
        V[w] = v;
        temp.weight = D[w]; temp.vertex = w;
        H.push(temp);
      }
      else if (D[w] == (D[v] + G.weight(v, w)) && N[w] > (N[v] + G.getCurrencyVal(v)))
      {
        N[w] = N[v] + G.getCurrencyVal(v);
        V[w] = v;
      }
    }
  }
}

//Recursive function that takes the V list which contains node
//visitations and outputs the correct path when indexes
//are converted to currency names
string pathTrace(Graph& G, MyList<float>& V, const int start, const int end) {
  if (V[end] == start)
  {
    return G.getCurrency(start) + "," + G.getCurrency(end) + ",";
  }
  else
  {
    return pathTrace(G, V, start, V[end]) + G.getCurrency(end) + ",";
  }
}

//Finds the shortest path in a graph based on STDIN input and
//uses Dijkstra's algorithm to do so
void shortestPath(Graph& G) {
  std::string start, end;
  findStartEnd(start, end);

  int i, j;
  MyList<float> D, V, N;
  for (int i = 0; i < G.numVert(); i++)
  {
    D.push_back(0);
    V.push_back(0);
    N.push_back(0);
  }

  i = G.iToCurrName(start);

  j = G.iToCurrName(end);

  Dijkstra(G, D, V, N, i);

  if (start == end)
  {
    cout << "The shortest path from " << start << "s to " << end << "s is:" << endl;
    cout << start << "s, " << "with sum exchange cost of 0 and bribe cost of 0." << endl;
  }
  else if (D[j] != INFINITY)
  {
    string paths = pathTrace(G, V, i, j);
    stringstream ss(paths);
    MyList<string> result;
    float bribeTotal = 0;

    cout << "The shortest path from " << start << "s to " << end << "s is:" << endl;
    while (ss.good())
    {
      string substr;
      getline(ss, substr, ',');
      result.push_back(substr);
    }

    for (int i = 0; i < result.size()-2; i++)
      for (int j = 0; j < G.numVert(); j++)
        if (result[i] == G.getCurrency(j))
        {
          bribeTotal+=G.getCurrencyVal(j);
          break;
        }

    for (int i = 0; i < result.size()-2; i++)
      cout << result[i] << "s, ";
    cout << result[result.size()-2] << "s, with sum exchange cost of " << D[j];
    cout << " and bribe cost of " << N[j] << "." << endl;
  }
  else
  {
    cout << "There is no path from " << start << "s to " << end << "s." << endl;
  }
}

#endif
