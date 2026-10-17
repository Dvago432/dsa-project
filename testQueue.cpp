#include <iostream>
#include "Request.h"
#include "Queue.h"

using namespace std;

int main() {
    Queue q;

    Request r1(
        "R001", "P001", "John",
        "Admission", "10:00",
        "Pending", 4, "Normal admission"
    );

    Request r2(
        "R002", "P002", "Mary",
        "Admission", "10:05",
        "Pending", 4, "Normal admission"
    );

    Request r3(
        "R003", "P003", "Peter",
        "Admission", "10:10",
        "Pending", 4, "Normal admission"
    );

    // Add requests
    q.enqueue(r1);
    q.enqueue(r2);
    q.enqueue(r3);

    // Display the queue
    q.display();

    cout << "\nNumber of requests: " << q.size() << endl;

    // Process the first request
    Request processedRequest;

    if (q.dequeue(processedRequest)) {
        cout << "\nProcessed request:" << endl;
        processedRequest.displayRequest();
    }

    // Display the remaining requests
    cout << "\nRemaining requests:" << endl;
    q.display();

    return 0;
}