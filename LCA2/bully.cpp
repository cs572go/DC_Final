#include <bits/stdc++.h>
using namespace std;

class processNode {
public:
    bool isAlive;
    bool hasStartedElection;
    int id;
    int coordinator;

    processNode(int idx) {
        this->isAlive = true; // Use true/false for boolean values.
        this->hasStartedElection = false;
        this->id = idx;
        this->coordinator = -1; // Initialize with an invalid value or 0, if no coordinator initially.
    }

    void disableNode() {
        this->isAlive = false;
        this->hasStartedElection = false;
        cout << "Disabled node: " << this->id << endl;
    }

    void displayNode() const {
        cout << "Node ID: " << this->id << ", alive: " << this->isAlive << ", elec_st?: " << this->hasStartedElection << ", boss: " << this->coordinator << endl;
    }
};

//jugad method not actual bully algo
void startElection(list<processNode>& nodes, int nodeId) {
    int maxId = -1;
    for (auto& node : nodes) {
        if (node.id > maxId && node.isAlive) {
            maxId = node.id;
        }
    }
    // Set the coordinator to the node with the maxId
    for (auto& node : nodes) {
        if (node.isAlive) {
            node.coordinator = maxId;
        }
    }
    cout << "Election completed. New coordinator is Node ID: " << maxId << endl;
}

int main() {
    cout << "Election Algo Simulation" << endl;
    list<processNode> nodes;
    int choice = 100;
    do {
        cout << "Menu" << endl;
        cout << "1. Add nodes" << endl;
        cout << "2. Disable a node" << endl;
        cout << "3. Display nodes" << endl;
        cout << "4. Start Election" << endl;
        cout << "0. Exit" << endl;
        cin >> choice;

        switch (choice) {
            case 1: {
                int nodestoadd;
                cout << "Enter number of nodes to add: ";
                cin >> nodestoadd;
                for (int i = 0; i < nodestoadd; i++) {
                    int idx;
                    cout << "Enter id: ";
                    cin >> idx;
                    processNode temp = processNode(idx);
                    nodes.push_back(temp);
                }
            } break;
            case 2: {
                int nodetodisable;
                cout << "Enter node id to disable: ";
                cin >> nodetodisable;
                for (auto& node : nodes) {
                    if (node.id == nodetodisable) {
                        node.disableNode();
                        break;
                    }
                }
            } break;
            case 3:
                for (const auto& node : nodes) {
                    node.displayNode();
                }
                break;
            case 4:
                int nodeId;
                cout << "Enter node id to start election: ";
                cin >> nodeId;
                startElection(nodes, nodeId);
                break;
            default:
                cout << "Enter valid choice." << endl;
                break;
        }
    } while (choice != 0);

    return 0;
}
