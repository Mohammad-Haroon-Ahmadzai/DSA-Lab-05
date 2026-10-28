// Lab 5 - Task 3: Train Coach Navigation System using Circular Doubly Linked List

#include <iostream>
#include <string>
using namespace std;

struct Coach
{
    int number;
    string type;
    int capacity, passengers;
    Coach *next, *prev;

    Coach(int n, string t, int c, int p) : number(n), type(t), capacity(c), passengers(p), next(this), prev(this) {}
};

class Train
{
    Coach *head, *current;

    Coach* find(int num)
    {
        if (!head) return nullptr;
        Coach* t = head;
        do
        {
            if (t->number == num) return t;
            t = t->next;
        } while (t != head);
        return nullptr;
    }

public:
    Train() : head(nullptr), current(nullptr) {}

    ~Train()
    {
        if (!head) return;
        head->prev->next = nullptr;
        while (head)
        {
            Coach* t = head;
            head = head->next;
            delete t;
        }
    }

    void addCoach(int num, string type, int cap, int pas) // add at end
    {
        Coach* c = new Coach(num, type, cap, pas);
        if (!head) { head = current = c; return; }
        Coach* tail = head->prev;
        c->next = head;
        c->prev = tail;
        tail->next = c;
        head->prev = c;
    }

    void insertAfter(int after, int num, string type, int cap, int pas)
    {
        Coach* p = find(after);
        if (!p) { cout << "Coach " << after << " not found.\n"; return; }
        Coach* c = new Coach(num, type, cap, pas);
        c->next = p->next;
        c->prev = p;
        p->next->prev = c;
        p->next = c;
        cout << "Coach inserted.\n";
    }

    void removeCoach(int num)
    {
        Coach* del = find(num);
        if (!del) { cout << "Coach not found.\n"; return; }
        if (del->next == del) head = current = nullptr;
        else
        {
            del->prev->next = del->next;
            del->next->prev = del->prev;
            if (head == del) head = del->next;
            if (current == del) current = del->next;
        }
        delete del;
        cout << "Coach removed.\n";
    }

    void moveForward() { if (current) current = current->next; else cout << "Train is empty.\n"; }
    void moveBackward() { if (current) current = current->prev; else cout << "Train is empty.\n"; }

    void show(Coach* c)
    {
        cout << "Coach No: " << c->number << " | Type: " << c->type << " | Capacity: " << c->capacity
             << " | Passengers: " << c->passengers << " | Empty seats: " << c->capacity - c->passengers
             << (c == current ? " <-- current" : "") << "\n";
    }

    void displayClockwise()
    {
        if (!head) { cout << "Train is empty.\n"; return; }
        Coach* t = head;
        do { show(t); t = t->next; } while (t != head);
    }

    void displayAnticlockwise()
    {
        if (!head) { cout << "Train is empty.\n"; return; }
        Coach* t = head->prev;
        Coach* start = t;
        do { show(t); t = t->prev; } while (t != start);
    }

    void search(int num)
    {
        Coach* c = find(num);
        if (c) show(c); else cout << "Coach not found.\n";
    }

    void maxAvailable()
    {
        if (!head) { cout << "Train is empty.\n"; return; }
        Coach *best = head, *t = head->next;
        while (t != head)
        {
            if (t->capacity - t->passengers > best->capacity - best->passengers) best = t;
            t = t->next;
        }
        cout << "Coach with maximum available capacity:\n";
        show(best);
    }

    void displayCurrent() { if (current) show(current); else cout << "Train is empty.\n"; }

    void reverseTrain() // pointer manipulation only
    {
        if (!head) { cout << "Train is empty.\n"; return; }
        Coach* newHead = head->prev; // old tail becomes first
        Coach* t = head;
        do
        {
            Coach* nxt = t->next;
            t->next = t->prev;
            t->prev = nxt;
            t = nxt;
        } while (t != head);
        head = newHead;
        cout << "Train direction reversed.\n";
    }
};

void readCoach(int& n, string& t, int& c, int& p)
{
    cout << "Coach Number: "; cin >> n; cin.ignore();
    cout << "Coach Type: "; getline(cin, t);
    cout << "Passenger Capacity: "; cin >> c;
    cout << "Current Passengers: "; cin >> p;
}

int main()
{
    Train tr;
    int n;
    cout << "Number of coaches: "; cin >> n;

    for (int i = 0; i < n; i++)
    {
        int num, cap, pas; string type;
        cout << "\nCoach " << i + 1 << ":\n";
        readCoach(num, type, cap, pas);
        tr.addCoach(num, type, cap, pas);
    }

    int ch;
    do
    {
        cout << "\n--- Train Coach Navigation ---\n"
             << "1. Add Coach\n2. Insert Coach After\n3. Remove Coach\n4. Move Forward\n"
             << "5. Move Backward\n6. Display Clockwise\n7. Display Anti-clockwise\n"
             << "8. Search Coach\n9. Max Available Capacity\n10. Display Current Coach\n"
             << "11. Reverse Train Direction\n0. Exit\nChoice: ";
        cin >> ch;

        int num, cap, pas, after; string type;
        switch (ch)
        {
        case 1: readCoach(num, type, cap, pas); tr.addCoach(num, type, cap, pas); break;
        case 2:
            cout << "Insert after coach number: "; cin >> after;
            readCoach(num, type, cap, pas);
            tr.insertAfter(after, num, type, cap, pas);
            break;
        case 3: cout << "Coach number: "; cin >> num; tr.removeCoach(num); break;
        case 4: tr.moveForward(); break;
        case 5: tr.moveBackward(); break;
        case 6: tr.displayClockwise(); break;
        case 7: tr.displayAnticlockwise(); break;
        case 8: cout << "Coach number: "; cin >> num; tr.search(num); break;
        case 9: tr.maxAvailable(); break;
        case 10: tr.displayCurrent(); break;
        case 11: tr.reverseTrain(); break;
        case 0: cout << "Bye!\n"; break;
        default: cout << "Invalid choice.\n";
        }
    } while (ch != 0);

    return 0;
}
