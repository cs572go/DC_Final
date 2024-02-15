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
    bool response;

    Node() : id(nextId++), isAlive(true), hasStartedElection(false), coordinator(-1), response(false) {}

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

    if(startingNode == nodes.end()){
        return;
    }

    // is node alive and not started election
    if (startingNode->isAlive && startingNode->hasStartedElection==false)
    {
        // cout<<startingNode->id<<endl;
        auto temp=startingNode;
        ++temp;
        for (auto it = temp; it!=nodes.end(); it++)
        {
            cout<< startingNode->id << " sends election to " << it->id<<endl;
            if(it->isAlive)
            {
                cout<< it->id << " sends OK."<<endl;
                startingNode->response=true;
            }

        }

        if(startingNode->response==false)
        {
            cout<<"No response, "<<startingNode->id<<" is coordinator."<<endl;
            for (auto it = nodes.begin(); it != nodes.end(); ++it)
            {
                it->coordinator=startingNode->id;
            }
            return;
        }
    }
    startBullyElection(nodes, startingNodeId+1);
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
                for(auto &node : nodes)
                {
                    node.hasStartedElection=false;
                    node.response=false;
                }
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
