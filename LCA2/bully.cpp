#include <bits/stdc++.h>

using namespace std;

class processNode
{
public:
    bool isAlive;
    bool hasStartedElection;
    int id;
    int coordinator;

    processNode(int idx)
    {
        this->isAlive = 1;
        this->hasStartedElection = 0;
        this->id = idx;
        this->coordinator = 10;
        // this->next = nullptr;
    }
    void disableNode()
    {
        this->isAlive = 0;
        this->hasStartedElection = 0;
        cout<<"Disabled node: "<<this->id;
    }

    void displayNode()
    {
        cout << "Node ID: " << this->id << ", alive: " << this->isAlive << " elec_st?: " << this->hasStartedElection << " boss: " << this->coordinator << endl;
    }
};

int main()
{
    cout << "Election Algo Simulation" << endl;
    list<processNode> nodes;
    int choice = 100;
    do
    {
        cout << "Menu" << endl;
        cout << "1. Add nodes" << endl;
        cout << "2. Disable a node" << endl;
        cout << "3. Display nodes" << endl;
        cout << "4. Election" << endl;
        cout << "0. Exit" << endl;
        cin >> choice;

        switch (choice)
        {
        case 1:
            int nodestoadd;
            cout<<"Enter number of nodes to add: ";
            cin>>nodestoadd;
            for (int i = 0; i < nodestoadd; i++)
            {
                int idx;
                cout<<"Enter id: ";
                cin>>idx;
                processNode temp = processNode(idx);
                nodes.push_back(temp);
            }
            break;
        case 2:
            int nodetodisable;
            cout<<"Enter node to disable: ";
            cin>>nodetodisable;
            break;
        case 3:
            for(auto it=nodes.begin(); it!=nodes.end(); ){
                it.displayNode;
            }
        default:
            cout<<"Enter valid choice"<<endl;
            break;
        }
    }while (choice != 0);

    return 0;
}
