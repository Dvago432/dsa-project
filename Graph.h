#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <iostream>

using namespace std;

const int MAX_DEPARTMENTS = 25;
const int GRAPH_INF = 1000000000;

class Graph {
    private:
        string departmentNames[MAX_DEPARTMENTS];
        int adjMatrix[MAX_DEPARTMENTS][MAX_DEPARTMENTS];
        int numDepartments;

        int getDepartmentIndex(const string& name) const;
        void dfsHelper(int u, bool visited[]) const;

    public:
        Graph();

        int addDepartment(const string& name);
        bool addEdge(const string& dept1, const string& dept2, int distance);

        void loadDefaultHospitalMap();
        void displayMap() const;

        void BFS(const string& startDept) const;
        void DFS(const string& startDept) const;
        void dijkstra(const string& startDept, const string& endDept) const;

        int getDepartmentCount() const;
        string getDepartmentName(int index) const;
        bool hasDepartment(const string& name) const;
};

#endif
