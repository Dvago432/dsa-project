#include "Graph.h"
#include <iostream>

using namespace std;

// Constructor
Graph::Graph() {
    numDepartments = 0;
    for (int i = 0; i < MAX_DEPARTMENTS; i++) {
        departmentNames[i] = "";
        for (int j = 0; j < MAX_DEPARTMENTS; j++) {
            adjMatrix[i][j] = (i == j) ? 0 : GRAPH_INF;
        }
    }
}

// Find department index by name (-1 if not found)
int Graph::getDepartmentIndex(const string& name) const {
    for (int i = 0; i < numDepartments; i++) {
        if (departmentNames[i] == name) {
            return i;
        }
    }
    return -1;
}

bool Graph::hasDepartment(const string& name) const {
    return getDepartmentIndex(name) != -1;
}

int Graph::getDepartmentCount() const {
    return numDepartments;
}

string Graph::getDepartmentName(int index) const {
    if (index >= 0 && index < numDepartments) {
        return departmentNames[index];
    }
    return "";
}

// Add a new department node
int Graph::addDepartment(const string& name) {
    int existing = getDepartmentIndex(name);
    if (existing != -1) {
        return existing;
    }

    if (numDepartments >= MAX_DEPARTMENTS) {
        cout << "Maximum department capacity reached." << endl;
        return -1;
    }

    int newIndex = numDepartments++;
    departmentNames[newIndex] = name;
    return newIndex;
}

// Add an undirected corridor (edge) between two departments
bool Graph::addEdge(const string& dept1, const string& dept2, int distance) {
    int u = getDepartmentIndex(dept1);
    int v = getDepartmentIndex(dept2);

    if (u == -1) u = addDepartment(dept1);
    if (v == -1) v = addDepartment(dept2);

    if (u == -1 || v == -1) {
        return false;
    }

    adjMatrix[u][v] = distance;
    adjMatrix[v][u] = distance;
    return true;
}

// Load default 8 hospital departments and corridor pathways from project document
void Graph::loadDefaultHospitalMap() {
    numDepartments = 0;
    for (int i = 0; i < MAX_DEPARTMENTS; i++) {
        departmentNames[i] = "";
        for (int j = 0; j < MAX_DEPARTMENTS; j++) {
            adjMatrix[i][j] = (i == j) ? 0 : GRAPH_INF;
        }
    }

    // Departments from PDF Page 4
    addDepartment("Reception");
    addDepartment("Emergency");
    addDepartment("Triage");
    addDepartment("ICU");
    addDepartment("General Ward");
    addDepartment("Pharmacy");
    addDepartment("Laboratory");
    addDepartment("Radiology");

    // Corridors and distances (meters)
    addEdge("Reception", "Emergency", 20);
    addEdge("Emergency", "Triage", 15);
    addEdge("Emergency", "ICU", 30);
    addEdge("Triage", "General Ward", 25);
    addEdge("ICU", "Pharmacy", 35);
    addEdge("General Ward", "Laboratory", 20);
    addEdge("Pharmacy", "Laboratory", 25);
    addEdge("Pharmacy", "Radiology", 15);
}

// Display the department connections and visual map
void Graph::displayMap() const {
    cout << "\n============================================\n";
    cout << "         HOSPITAL CAMPUS MAP (GRAPH)        \n";
    cout << "============================================\n";
    cout << "  [Reception]\n";
    cout << "       |\n";
    cout << "  [Emergency] --------- [Triage]\n";
    cout << "       |                    |\n";
    cout << "     [ICU]            [General Ward]\n";
    cout << "       |                    |\n";
    cout << "  [Pharmacy] ---------- [Laboratory]\n";
    cout << "       |\n";
    cout << "  [Radiology]\n";
    cout << "--------------------------------------------\n";
    cout << "Department Corridors and Distances:\n";

    for (int i = 0; i < numDepartments; i++) {
        cout << departmentNames[i] << " is connected to:\n";
        bool hasConnection = false;
        for (int j = 0; j < numDepartments; j++) {
            if (i != j && adjMatrix[i][j] < GRAPH_INF) {
                cout << "   -> " << departmentNames[j] << " (" << adjMatrix[i][j] << " meters)\n";
                hasConnection = true;
            }
        }
        if (!hasConnection) {
            cout << "   -> (No direct corridors)\n";
        }
    }
    cout << "============================================\n";
}

// Breadth-First Search (BFS) using simple array queue (No STL)
void Graph::BFS(const string& startDept) const {
    int start = getDepartmentIndex(startDept);
    if (start == -1) {
        cout << "Department '" << startDept << "' not found." << endl;
        return;
    }

    bool visited[MAX_DEPARTMENTS];
    for (int i = 0; i < numDepartments; i++) {
        visited[i] = false;
    }

    int queueArr[MAX_DEPARTMENTS];
    int front = 0;
    int rear = 0;

    visited[start] = true;
    queueArr[rear++] = start;

    cout << "\n--- BFS Reachable Departments starting from '" << startDept << "' ---\n";
    int step = 1;
    while (front < rear) {
        int u = queueArr[front++];
        cout << step++ << ". " << departmentNames[u] << endl;

        for (int v = 0; v < numDepartments; v++) {
            if (adjMatrix[u][v] < GRAPH_INF && u != v && !visited[v]) {
                visited[v] = true;
                queueArr[rear++] = v;
            }
        }
    }
}

// Helper for DFS traversal
void Graph::dfsHelper(int u, bool visited[]) const {
    visited[u] = true;
    cout << " -> " << departmentNames[u];

    for (int v = 0; v < numDepartments; v++) {
        if (adjMatrix[u][v] < GRAPH_INF && u != v && !visited[v]) {
            dfsHelper(v, visited);
        }
    }
}

// Depth-First Search (DFS) for full hospital traversal
void Graph::DFS(const string& startDept) const {
    int start = getDepartmentIndex(startDept);
    if (start == -1) {
        cout << "Department '" << startDept << "' not found." << endl;
        return;
    }

    bool visited[MAX_DEPARTMENTS];
    for (int i = 0; i < numDepartments; i++) {
        visited[i] = false;
    }

    cout << "\n--- DFS Traversal starting from '" << startDept << "' ---\n";
    dfsHelper(start, visited);
    cout << endl;

    // Check for any unvisited disconnected departments
    for (int i = 0; i < numDepartments; i++) {
        if (!visited[i]) {
            cout << "(Remaining component):";
            dfsHelper(i, visited);
            cout << endl;
        }
    }
}

// Dijkstra's Algorithm for shortest path between two departments
void Graph::dijkstra(const string& startDept, const string& endDept) const {
    int src = getDepartmentIndex(startDept);
    int dest = getDepartmentIndex(endDept);

    if (src == -1) {
        cout << "Source department '" << startDept << "' not found." << endl;
        return;
    }
    if (dest == -1) {
        cout << "Destination department '" << endDept << "' not found." << endl;
        return;
    }

    int dist[MAX_DEPARTMENTS];
    bool visited[MAX_DEPARTMENTS];
    int parent[MAX_DEPARTMENTS];

    for (int i = 0; i < numDepartments; i++) {
        dist[i] = GRAPH_INF;
        visited[i] = false;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < numDepartments - 1; count++) {
        // Find vertex with minimum distance
        int minDist = GRAPH_INF;
        int u = -1;

        for (int v = 0; v < numDepartments; v++) {
            if (!visited[v] && dist[v] < minDist) {
                minDist = dist[v];
                u = v;
            }
        }

        if (u == -1 || dist[u] == GRAPH_INF) {
            break;
        }

        visited[u] = true;

        if (u == dest) {
            break;
        }

        // Relax adjacent vertices
        for (int v = 0; v < numDepartments; v++) {
            if (!visited[v] && adjMatrix[u][v] < GRAPH_INF && u != v) {
                if (dist[u] + adjMatrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + adjMatrix[u][v];
                    parent[v] = u;
                }
            }
        }
    }

    if (dist[dest] == GRAPH_INF) {
        cout << "No route found between '" << startDept << "' and '" << endDept << "'." << endl;
        return;
    }

    // Backtrack path
    int path[MAX_DEPARTMENTS];
    int pathLength = 0;
    int curr = dest;

    while (curr != -1) {
        path[pathLength++] = curr;
        curr = parent[curr];
    }

    cout << "\n============================================\n";
    cout << "       SHORTEST ROUTE (DIJKSTRA'S)          \n";
    cout << "============================================\n";
    cout << "From: " << startDept << "\n";
    cout << "To  : " << endDept << "\n";
    cout << "Total Distance: " << dist[dest] << " meters\n";
    cout << "Route:\n";

    for (int i = pathLength - 1; i >= 0; i--) {
        cout << departmentNames[path[i]];
        if (i > 0) {
            int fromIdx = path[i];
            int toIdx = path[i - 1];
            cout << " --(" << adjMatrix[fromIdx][toIdx] << "m)--> ";
        }
    }
    cout << "\n============================================\n";
}
