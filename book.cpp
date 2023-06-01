//Books 
#include<iostream>
#include<string>
using namespace std;

struct node 
{
    string label;
    int ch_count;
    struct node* child[10];
} *book;

class GT 
{
public:
    void create_tree();
    void display(node* r1);
    GT() 
    {
        book = NULL;
    }
};

void GT::create_tree() 
{
    int tchapters, i, j;
    book = new node;
    cin.ignore();
    cout << "Enter the name of the book: ";
    getline(cin, book->label);
    cout << "Enter the number of chapters in the book: ";
    cin >> tchapters;
    book->ch_count = tchapters;
    cin.ignore();
    for (i = 0; i < tchapters; i++) 
    {
        book->child[i] = new node;
        cout << "Enter the name of Chapter " << i + 1 << ": ";
        getline(cin, book->child[i]->label);
        cout << "Enter the number of sections in Chapter " << book->child[i]->label << ": ";
        cin >> book->child[i]->ch_count;
        cin.ignore();
        for (j = 0; j < book->child[i]->ch_count; j++) 
        {
            book->child[i]->child[j] = new node;
            cout << "Enter the name of Section " << j + 1 << ": ";
            getline(cin, book->child[i]->child[j]->label);
        }
    }
}

void GT::display(node* r1)
{
    int i, j;
    if (r1 != NULL) 
    {
        cout << "\n----- Book Hierarchy -----\n";
        cout << "Book Title: " << r1->label << endl;
        for (i = 0; i < r1->ch_count; i++) {
            cout << "Chapter " << i + 1 << ": " << r1->child[i]->label << endl;
            cout << "Sections: ";
            for (j = 0; j < r1->child[i]->ch_count; j++) 
            {
                cout << r1->child[i]->child[j]->label << " ";
            }
            cout << endl;
        }
    }
    cout << endl;
}

int main() 
{
    int choice;
    GT gt;
    while (true) {
        cout << "-----------------" << endl;
        cout << "Book Tree Creation" << endl;
        cout << "-----------------" << endl;
        cout << "1. Create" << endl;
        cout << "2. Display" << endl;
        cout << "3. Quit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice) 
        {
            case 1:
                gt.create_tree();
                break;
            case 2:
                gt.display(book);
                break;
            case 3:
                exit(1);
            default:
                cout << "Wrong choice!!!" << endl;
        }
    }
    return 0;
}

