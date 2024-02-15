#include <iostream>
#include <list>

using namespace std;

class Node
{
private:
    // Static variable for ID
    static int nextId;

public:
    int id;
    bool isAlive;
    bool hasStartedElection;
    int coordinator;

    Node() : id(nextId++), isAlive(true), hasStartedElection(false), coordinator(-1) {}

    void disableNode()
    {
        this->isAlive = false;
        this->hasStartedElection = false;
        cout << "Node " << this->id << " disabled." << endl;
    }

    void displayNode() const
    {
        cout << "Node ID: " << this->id << ", Alive: " << this->isAlive << ", Election Started: " << this->hasStartedElection << ", Coordinator: " << this->coordinator << endl;
    }
};

// init static variable
int Node::nextId = 1;

// bully algo
void startBullyElection(list<Node> &nodes, int startingNodeId)
{
    // Find the starting node
    auto startingNode = nodes.end();

    for (auto it = nodes.begin(); it != nodes.end(); ++it)
    {
        if (it->id == startingNodeId)
        {
            startingNode = it;
            break;
        }
    }

    // is node valid and alive?
    if (startingNode != nodes.end() && startingNode->isAlive)
    {
        // has the node already started election?
        if (startingNode->hasStartedElection)
        {
            cout << "Node " << startingNodeId << " has already started an election. Cannot start another one." << endl;
            return;
        }

        // Set hasStartedElection to true for the starting node
        startingNode->hasStartedElection = true;
        cout << "Node " << startingNodeId << " initiates election." << endl;

        // Flag to track if any higher node responds
        bool higherNodeResponded = false;

        // Find the higher nodes
        list<Node> higherNodes;
        for (auto it = next(startingNode); it != nodes.end(); ++it)
        {
            if (it->id > startingNodeId && it->isAlive)
            {
                higherNodes.push_back(*it);
            }
        }

        // If there are higher nodes, send election messages to them
        if (!higherNodes.empty())
        {
            cout << "Sending election messages to higher nodes..." << endl;
            for (const auto &higherNode : higherNodes)
            {
                cout << "Node " << startingNodeId << " sends election message to node " << higherNode.id << endl;
                higherNodeResponded = true; // Assume higher node responded
                // Recursive call to start election at higher node
                startBullyElection(nodes, higherNode.id);
            }
        }

        // If no higher node responds, announce as coordinator
        if (!higherNodeResponded)
        {
            cout << "No higher nodes responded. Node " << startingNodeId << " wins the election and becomes the coordinator." << endl;
            startingNode->coordinator = startingNodeId;

            // Reset hasStartedElection to false for all nodes and update coordinator ID
            for (auto &node : nodes)
            {
                node.hasStartedElection = false;
                node.coordinator = startingNodeId;
            }
        }
    }
    else
    {
        cout << "Invalid or non-alive starting node ID. Please enter a valid node ID." << endl;
    }
}

int main()
{
    list<Node> nodes;

    int choice;
    do
    {
        // Display the menu
        cout << "\nMenu:\n"
             << "1. Add nodes\n"
             << "2. Disable node\n"
             << "3. Display nodes\n"
             << "4. Start election\n"
             << "5. Exit\n"
             << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            // Add nodes
            int n;
            cout << "Enter the number of nodes to add: ";
            cin >> n;
            for (int i = 0; i < n; ++i)
            {
                nodes.push_back(Node());
                cout << "Node " << nodes.back().id << " added successfully." << endl;
            }
            break;
        }
        case 2:
        {
            // Disable a node
            int nodeId;
            cout << "Enter ID of the node to disable: ";
            cin >> nodeId;
            bool found = false;
            for (auto &node : nodes)
            {
                if (node.id == nodeId)
                {
                    node.disableNode();
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                cout << "Node not found." << endl;
            }
            break;
        }
        case 3:

            // Display all nodes
            if (nodes.empty())
            {
                cout << "No nodes added yet." << endl;
            }
            else
            {
                cout << "Nodes:\n";
                for (const auto &node : nodes)
                {
                    node.displayNode();
                }
            }
            break;

        case 4:
        {
            // Start election
            cout << "Choose election algorithm:\n"
                 << "1. Bully election algorithm\n"
                 << "2. Ring election algorithm\n"
                 << "Enter your choice: ";
            int algoChoice;
            cin >> algoChoice;
            switch (algoChoice)
            {
            case 1:
            {
                // Bully election algorithm
                int startingNode;
                cout << "Enter the starting node ID for the election: ";
                cin >> startingNode;
                startBullyElection(nodes, startingNode);
                break;
            }
            case 2:
                // Implement Ring election algorithm
                cout << "Ring election algorithm not implemented yet." << endl;
                break;
            default:
                cout << "Invalid choice." << endl;
                break;
            }
            break;
        }

        case 5:
            // Exit
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
            break;
        }
    } while (choice != 5);

    return 0;
}
