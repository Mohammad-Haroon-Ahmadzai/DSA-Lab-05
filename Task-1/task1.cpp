// Lab 5 - Task 1: Browser Tab Manager using Circular Doubly Linked List

#include <iostream>
#include <string>
using namespace std;

struct Tab
{
    int id;
    string title, url;
    Tab *next, *prev;

    Tab(int i, string t, string u) : id(i), title(t), url(u), next(this), prev(this) {}
};

class TabManager
{
    Tab* current;

public:
    TabManager() : current(nullptr) {}

    ~TabManager()
    {
        if (!current) return;
        current->prev->next = nullptr; // break the circle
        while (current)
        {
            Tab* t = current;
            current = current->next;
            delete t;
        }
    }

    void openTab(int id, string title, string url)
    {
        Tab* n = new Tab(id, title, url);
        if (!current) { current = n; return; }
        n->next = current->next;
        n->prev = current;
        current->next->prev = n;
        current->next = n;
        current = n; // new tab becomes active
    }

    void closeCurrent()
    {
        if (!current) { cout << "No tabs open.\n"; return; }
        Tab* del = current;
        if (current->next == current) current = nullptr;
        else
        {
            del->prev->next = del->next;
            del->next->prev = del->prev;
            current = del->next;
        }
        delete del;
        cout << "Tab closed.\n";
    }

    void moveNext() { if (current) current = current->next; else cout << "No tabs open.\n"; }
    void movePrev() { if (current) current = current->prev; else cout << "No tabs open.\n"; }

    void show(Tab* t) { cout << "ID: " << t->id << " | Title: " << t->title << " | URL: " << t->url << "\n"; }

    void displayCurrent() { if (current) show(current); else cout << "No tabs open.\n"; }

    void displayForward()
    {
        if (!current) { cout << "No tabs open.\n"; return; }
        Tab* t = current;
        do { show(t); t = t->next; } while (t != current);
    }

    void displayBackward()
    {
        if (!current) { cout << "No tabs open.\n"; return; }
        Tab* t = current;
        do { show(t); t = t->prev; } while (t != current);
    }

    void search(int id)
    {
        if (!current) { cout << "No tabs open.\n"; return; }
        Tab* t = current;
        do
        {
            if (t->id == id) { show(t); return; }
            t = t->next;
        } while (t != current);
        cout << "Tab not found.\n";
    }
};

int main()
{
    TabManager tm;
    int ch;

    do
    {
        cout << "\n--- Browser Tab Manager ---\n"
             << "1. Open New Tab\n2. Close Current Tab\n3. Move Next\n4. Move Previous\n"
             << "5. Display Current Tab\n6. Display All Forward\n7. Display All Backward\n"
             << "8. Search Tab\n0. Exit\nChoice: ";
        cin >> ch;

        switch (ch)
        {
        case 1:
        {
            int id; string title, url;
            cout << "Tab ID: "; cin >> id; cin.ignore();
            cout << "Title: "; getline(cin, title);
            cout << "URL: "; getline(cin, url);
            tm.openTab(id, title, url);
            break;
        }
        case 2: tm.closeCurrent(); break;
        case 3: tm.moveNext(); break;
        case 4: tm.movePrev(); break;
        case 5: tm.displayCurrent(); break;
        case 6: tm.displayForward(); break;
        case 7: tm.displayBackward(); break;
        case 8: { int id; cout << "Tab ID: "; cin >> id; tm.search(id); break; }
        case 0: cout << "Bye!\n"; break;
        default: cout << "Invalid choice.\n";
        }
    } while (ch != 0);

    return 0;
}
