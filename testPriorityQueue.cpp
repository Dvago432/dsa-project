#include <iostream>
#include "Request.h"
#include "PriorityQueue.h"

using namespace std;

int main() {
    PriorityQueue pq;

    Request r1(
        "R001", "P001", "John",
        "Admission", "10:00",
        "Pending", 4, "Normal admission"
    );

    Request r2(
        "R002", "P002", "Mary",
        "Admission", "10:05",
        "Pending", 1, "Emergency admission"
    );

    Request r3(
        "R003", "P003", "Peter",
        "Admission", "10:10",
        "Pending", 3, "Urgent admission"
    );

    Request r4(
        "R004", "P004", "Sarah",
        "Admission", "10:15",
        "Pending", 2, "Critical admission"
    );

    // Insert requests
    pq.insert(r1);
    pq.insert(r2);
    pq.insert(r3);
    pq.insert(r4);

    cout << "\nNumber of requests: " << pq.size() << endl;

    // Display the heap
    pq.display();

    // Remove requests in priority order
    cout << "\n--- Processing Requests ---\n";

    Request processedRequest;

    while (pq.removeHighestPriority(processedRequest)) {
        cout << "Processing: "
             << processedRequest.getRequestID()
             << " | Patient: "
             << processedRequest.getPatientID()
             << " | Priority: "
             << processedRequest.getPriority()
             << endl;
    }

    cout << "\nPriority Queue empty: "
         << (pq.isEmpty() ? "Yes" : "No") << endl;

    return 0;
}