#include <iostream>
#include <list>

using namespace std;

// class to represent a single node
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
    bool response;

    // constructor makes nodes alive, sets ID and sets no coordinator
    Node() : id(nextId++), isAlive(true), hasStartedElection(false), coordinator(-1), response(false) {}

    void disableNode()
    {
        this->isAlive = false;
        cout << "Node " << this->id << " disabled." << endl;
    }

    void enableNode()
    {
        this->isAlive = true;
        cout << "Node " << this->id << " enabled." << endl;
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

    // if ahead of last node, return
    if (startingNode == nodes.end())
    {
        return;
    }

    // is node alive and not started election
    if (startingNode->isAlive && startingNode->hasStartedElection == false)
    {
        // cout<<startingNode->id<<endl;
        auto temp = startingNode;
        ++temp;
        for (auto it = temp; it != nodes.end(); it++)
        {
            cout << startingNode->id << " sends election to " << it->id << endl;
            if (it->isAlive)
            {
                cout << it->id << " sends OK." << endl;
                startingNode->response = true;
            }
        }

        // if no response, the sender is the coordinator
        if (startingNode->response == false)
        {
            cout << "No response, " << startingNode->id << " is coordinator." << endl;
            for (auto it = nodes.begin(); it != nodes.end(); ++it)
            {
                it->coordinator = startingNode->id;
            }
            return;
        }
    }

    // recursive call to next node
    startBullyElection(nodes, startingNodeId + 1);
}

// ring algo
void startRingElection(list<Node> &nodes, int startingNodeId)
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

    // if ahead of last node, return
    if (startingNode == nodes.end())
    {
        return;
    }

    int maxId = startingNodeId;
    bool foundHigher = false;
    auto currentIt = startingNode;

    do
    {
        // move to the next node, wrap to the beginning if at the end
        do
        {
            currentIt++;
            if (currentIt == nodes.end())
            {
                currentIt = nodes.begin();
            }
        } while (!currentIt->isAlive && currentIt->id != startingNodeId); // Skip dead nodes

        if (currentIt->id == startingNodeId && foundHigher)
        {
            // if made a full loop and found a higher ID, break
            break;
        }

        if (currentIt->id > maxId)
        {
            maxId = currentIt->id;
            foundHigher = true;
        }

        cout << "Node " << startingNode->id << " passes election to Node " << currentIt->id << endl;

        startingNode = currentIt; // move to next node

    } while (currentIt->id != startingNodeId); // loop back to the start

    // after completing the loop, maxId is the ID of the elected coordinator
    cout << "Node " << maxId << " is elected as coordinator." << endl;
    for (auto &node : nodes)
    {
        node.coordinator = maxId;
    }
}

int main()
{
    list<Node> nodes;

    int choice;
    do
    {
        // menu
        cout << "\nMenu:\n"
             << "1. Add nodes\n"
             << "2. Disable node\n"
             << "3. Enable node\n"
             << "4. Display nodes\n"
             << "5. Start election\n"
             << "6. Exit\n"
             << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            // add nodes
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
            // disable a node
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
        {
            // enable a node
            int nodeId;
            cout << "Enter ID of the node to enable: ";
            cin >> nodeId;
            bool found = false;
            for (auto &node : nodes)
            {
                if (node.id == nodeId)
                {
                    node.enableNode();
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
        case 4:

            // display all nodes
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

        case 5:
        {
            // start election
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
                // bully algo
                int startingNode;
                cout << "Enter the starting node ID for the election: ";
                cin >> startingNode;
                startBullyElection(nodes, startingNode);

                // reset the election flags after election is over
                for (auto &node : nodes)
                {
                    node.hasStartedElection = false;
                    node.response = false;
                }
                break;
            }
            case 2:
                // ring algo
                int startingNode;
                cout << "Enter the starting node ID for the election: ";
                cin >> startingNode;
                startRingElection(nodes, startingNode);

                // reset the election flags after election is over
                for (auto &node : nodes)
                {
                    node.hasStartedElection = false;
                    node.response = false;
                }
                break;

            default:
                cout << "Invalid choice." << endl;
                break;
            }
            break;
        }

        case 6:
            // Exit
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
            break;
        }
    } while (choice != 6);

    return 0;
}
