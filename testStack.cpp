#include <iostream>
#include "Stack.h"

using namespace std;

int main() {
    Stack undoStack;

    UndoAction a1(
        "Patient Admission",
        "P001",
        "Not Admitted",
        "None"
    );

    UndoAction a2(
        "Ward Assignment",
        "P002",
        "Admitted",
        "W01"
    );

    UndoAction a3(
        "Patient Discharge",
        "P003",
        "Admitted",
        "W02"
    );

    // Push actions
    undoStack.push(a1);
    undoStack.push(a2);
    undoStack.push(a3);

    // Display stack
    undoStack.display();

    cout << "\nStack size: " << undoStack.size() << endl;

    // Undo the most recent action
    UndoAction lastAction;

    if (undoStack.pop(lastAction)) {
        cout << "\nLast action removed: "
             << lastAction.actionType << endl;

        cout << "Patient ID: "
             << lastAction.patientID << endl;
    }

    cout << "\nRemaining actions:" << endl;
    undoStack.display();

    return 0;
}