#include <iostream>
#include <list>

#define max_msgs 10

using namespace std;

class Message
{
public:
    int sid;
    int rid;
    int se;
    int re;
    int C;
    bool sent;
    bool recieved;

    Message(int se, int re, int sid, int rid)
    {
        this->se = se;
        this->re = re;
        this->sid = sid;
        this->rid = rid;
        this->C = 0;
        this->sent = false;
        this->recieved = false;
    }

    void displayMessage()
    {
        cout << "Sender " << this->sid << "," << this->se << "," << this->C << ", ; Reciever " << this->rid << "," << this->re << "; Status " << this->sent << "," << this->recieved << endl;
    }
};

class Process
{
private:
    static int nextId;

public:
    int id;
    int d;
    int localC;
    int event;

    Process(int d = 1)
    {
        this->id = nextId++;
        this->d = d;
        this->localC = 0;
        this->event = 0;
    }

    void displayProcess()
    {
        cout << "Process " << this->id << ", d " << this->d << ", localC " << this->localC << ", event " << this->event << endl;
    }
};

int Process::nextId = 1;

int main()
{
    list<Process> processes;
    list<Message> messages;

    int np = 0;
    cout << "Enter number of processes: ";
    cin >> np;

    for (int i = 0; i < np; ++i)
    {
        int d = 0;
        cout << "Enter d for process " << (i + 1) << ": ";
        cin >> d;
        processes.push_back(Process(d));
    }

    int nm = 0;
    cout << "Enter number of messages: ";
    cin >> nm;

    for (int i = 0; i < nm; ++i)
    {
        int sid = 0, rid = 0;
        int se = 0, re = 0;
        cout << "Enter sender id for message " << (i + 1) << ": ";
        cin >> sid;
        cout << "Event number: ";
        cin >> se;
        cout << "Enter reciever id for message " << (i + 1) << ": ";
        cin >> rid;
        cout << "Event number: ";
        cin >> re;
        messages.push_back(Message(se, re, sid, rid));
    }

    for (auto &p : processes)
    {
        p.displayProcess();
    }

    for (auto &m : messages)
    {
        m.displayMessage();
    }

    cout<<"Event\t";
    for (int i=0; i<np; i++)
    {
        cout<<i+1<<"\t";
    }
    cout<<endl;

    for (int i = 1; i <= max_msgs; i++)
    {
        cout<<"p"<<i<<"\t";
        for (auto &p : processes)
        {
            p.event += 1;
            p.localC += p.d;

            // send
            for (auto &m : messages)
            {
                if (m.sid == p.id && m.se == p.event)
                {                   
                    m.C = p.localC; // piggyback sender time
                    m.sent = true;                
                }
            }
            
            // rec
            for (auto &m : messages)
            {
                if (m.rid == p.id && m.re == p.event)
                {                                      
                    p.localC = max(p.localC, m.C); // set receiver time
                    m.recieved = true;
                }
            }
            cout<<p.localC<<"\t";
        }
        cout<<endl;
    }

    // for (auto &p : processes)
    // {
    //     p.displayProcess();
    // }

    for (auto &m : messages)
    {
        m.displayMessage();
    }

    return 0;
}