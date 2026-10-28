// Lab 5 - Task 2: Circular Photo Album using Circular Doubly Linked List

#include <iostream>
#include <string>
using namespace std;

struct Photo
{
    int id;
    string name, date, location;
    Photo *next, *prev;

    Photo(int i, string n, string d, string l) : id(i), name(n), date(d),
        location(l), next(this), prev(this) {}
};

class Album
{
    Photo *head, *current;

public:
    Album() : head(nullptr), current(nullptr) {}

    ~Album()
    {
        if (!head) return;
        head->prev->next = nullptr;
        while (head)
        {
            Photo* t = head;
            head = head->next;
            delete t;
        }
    }

    void addPhoto(int id, string n, string d, string l) // insert at end
    {
        Photo* p = new Photo(id, n, d, l);
        if (!head) { head = current = p; return; }
        Photo* tail = head->prev;
        p->next = head;
        p->prev = tail;
        tail->next = p;
        head->prev = p;
    }

    void insertAfterCurrent(int id, string n, string d, string l)
    {
        if (!current) { addPhoto(id, n, d, l); return; }
        Photo* p = new Photo(id, n, d, l);
        p->next = current->next;
        p->prev = current;
        current->next->prev = p;
        current->next = p;
    }

    void removeNode(Photo* del)
    {
        if (del->next == del) { head = current = nullptr; }
        else
        {
            del->prev->next = del->next;
            del->next->prev = del->prev;
            if (head == del) head = del->next;
            if (current == del) current = del->next;
        }
        delete del;
    }

    void removeById(int id)
    {
        if (!head) { cout << "Album is empty.\n"; return; }
        Photo* t = head;
        do
        {
            if (t->id == id) { removeNode(t); cout << "Photo removed.\n"; return; }
            t = t->next;
        } while (t != head);
        cout << "Photo not found.\n";
    }

    void removeCurrent()
    {
        if (!current) { cout << "Album is empty.\n"; return; }
        removeNode(current);
        cout << "Current photo removed.\n";
    }

    void moveNext() { if (current) current = current->next; else cout << "Album is empty.\n"; }
    void movePrev() { if (current) current = current->prev; else cout << "Album is empty.\n"; }

    void show(Photo* p)
    {
        cout << "ID: " << p->id << " | Name: " << p->name << " | Date: " << p->date
             << " | Location: " << p->location << (p == current ? " <-- current" : "") << "\n";
    }

    void displayForward()
    {
        if (!current) { cout << "Album is empty.\n"; return; }
        Photo* t = current;
        do { show(t); t = t->next; } while (t != current);
    }

    void displayBackward()
    {
        if (!current) { cout << "Album is empty.\n"; return; }
        Photo* t = current;
        do { show(t); t = t->prev; } while (t != current);
    }

    void search(int id)
    {
        if (!head) { cout << "Album is empty.\n"; return; }
        Photo* t = head;
        do
        {
            if (t->id == id) { show(t); return; }
            t = t->next;
        } while (t != head);
        cout << "Photo not found.\n";
    }

    void count()
    {
        int c = 0;
        if (head)
        {
            Photo* t = head;
            do { c++; t = t->next; } while (t != head);
        }
        cout << "Total photos: " << c << "\n";
    }
};

void readPhoto(int& id, string& n, string& d, string& l)
{
    cout << "Photo ID: "; cin >> id; cin.ignore();
    cout << "Name: "; getline(cin, n);
    cout << "Date Taken: "; getline(cin, d);
    cout << "Location: "; getline(cin, l);
}

int main()
{
    Album a;
    int n;
    cout << "Number of photos: "; cin >> n;

    for (int i = 0; i < n; i++)
    {
        int id; string nm, d, l;
        cout << "\nPhoto " << i + 1 << ":\n";
        readPhoto(id, nm, d, l);
        a.addPhoto(id, nm, d, l);
    }

    int ch;
    do
    {
        cout << "\n--- Circular Photo Album ---\n"
             << "1. Add Photo\n2. Insert Photo After Current\n3. Remove Photo (by ID)\n"
             << "4. Remove Current Photo\n5. Move Next\n6. Move Previous\n"
             << "7. Display Forward\n8. Display Backward\n9. Search Photo\n"
             << "10. Count Photos\n0. Exit\nChoice: ";
        cin >> ch;

        int id; string nm, d, l;
        switch (ch)
        {
        case 1: readPhoto(id, nm, d, l); a.addPhoto(id, nm, d, l); break;
        case 2: readPhoto(id, nm, d, l); a.insertAfterCurrent(id, nm, d, l); break;
        case 3: cout << "Photo ID: "; cin >> id; a.removeById(id); break;
        case 4: a.removeCurrent(); break;
        case 5: a.moveNext(); break;
        case 6: a.movePrev(); break;
        case 7: a.displayForward(); break;
        case 8: a.displayBackward(); break;
        case 9: cout << "Photo ID: "; cin >> id; a.search(id); break;
        case 10: a.count(); break;
        case 0: cout << "Bye!\n"; break;
        default: cout << "Invalid choice.\n";
        }
    } while (ch != 0);

    return 0;
}
