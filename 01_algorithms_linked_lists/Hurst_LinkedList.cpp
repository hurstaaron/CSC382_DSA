/*
    Assignment 1 - Linked List: Browser Bookmark Manager
    Student: Aaron Hurst
    Course:  CSC382, Prof. Habib
    Date:    June 2026

    What this program does:
    Manages a list of 20 bookmarked websites using a doubly linked list.
    You can move forward and backward through the list, add new sites,
    delete sites, find a site by name, and display the whole list.

    Why a doubly linked list?
    Each node points to both the next site AND the previous site, so we
    can travel in either direction. This is the same idea used in real
    browser history tabs and also in AI pipeline graphs where you need
    to walk data sources forward and backward.
*/

#include <iostream>
#include <string>
using namespace std;

// ------------------ NODE STRUCT -----------------------------------------
// Each node holds one bookmark and two pointers:
//   prev = points to the site before this one
//   next = points to the site after this one
// -----------------------------------------------------------------------
struct Node {
    string siteName;    // friendly label like "OpenAI"
    string url;         // the actual web address
    Node* prev;         // pointer to the previous node in the list
    Node* next;         // pointer to the next node in the list
};


// ------------------ CLASS: LINKED LIST ---------------------------------
// Keeps track of the head, tail, and current position.
// All the list operations live here.
// -----------------------------------------------------------------------
class BookmarkList {

private:
    Node* head;     // first node 
    Node* tail;     // last node
    Node* current;  // where the user is at int he browser right now

public:
    // Constructor sets everything to null for a clean start
    BookmarkList() {
        head    = nullptr;
        tail    = nullptr;
        current = nullptr;
    }

    // Destructor traverses the list and frees up every node when the program ends
    ~BookmarkList() {
        Node* temp = head;
        while (temp != nullptr) {
            Node* next = temp->next;
            delete temp;
            temp = next;
        }
    }


    // ------------------ BOOKMARK END OF LIST ---------------------------
    // Creates a new node, hooks it onto the tail, and updates tail.
    // -------------------------------------------------------------------
    void addBookmark(string name, string url) {
        // New node and fill it in
        Node* newNode   = new Node();
        newNode->siteName = name;
        newNode->url      = url;
        newNode->prev     = nullptr;
        newNode->next     = nullptr;

        // If the list is empty, this node is both head and tail
        if (head == nullptr) {
            head    = newNode;
            tail    = newNode;
            current = newNode;   // start browsing here
        }
        else {
            // Hook the new node onto the end
            newNode->prev = tail;   // new node looks back at old tail
            tail->next    = newNode; // old tail looks forward to new node
            tail          = newNode; // update tail to the new node
        }

        cout << "Bookmark added: " << name << endl;
    }

    // ------------------ DELETE A BOOKMARK BY NAME ------------------------
    // Searches for the name, then links the surrounding nodes around it.
    // ---------------------------------------------------------------------
    void deleteBookmark(string name) {
        // Prevent deleteing from an empty list
        if (head == nullptr) {
            cout << "The list is empty, nothing to delete." << endl;
            return;
        }

        // Walk through the list looking for a match
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->siteName == name) {
                // If there is a node before this one, point it forward past this node
                if (temp->prev != nullptr)
                    temp->prev->next = temp->next;
                else
                    head = temp->next;  // this was the head, so update head

                // If there is a node after this one, point it backward past this node
                if (temp->next != nullptr)
                    temp->next->prev = temp->prev;
                else
                    tail = temp->prev;  // this was the tail, so update tail

                // If we are deleting the node we are currently on, move current
                if (current == temp) {
                    if (temp->next != nullptr)
                        current = temp->next;
                    else
                        current = temp->prev;
                }

                delete temp;
                cout << "Bookmark deleted: " << name << endl;
                return;
            }
            temp = temp->next;
        }

        cout << "Bookmark not found: " << name << endl;
    }


    // ------------------ FIND A BOOKMARK BY NAME ------------------------
    // Traverse the list and prints the url if found.
    // -------------------------------------------------------------------
    void findBookmark(string name) {
        if (head == nullptr) {
            cout << "The list is empty." << endl;
            return;
        }

        Node* temp = head;
        while (temp != nullptr) {
            if (temp->siteName == name) {
                cout << "Found: " << temp->siteName << " -> " << temp->url << endl;
                return;
            }
            temp = temp->next;
        }

        cout << "Bookmark not found: " << name << endl;
    }


    // ------------------ GO FORWARD ONE BOOKMARK ------------------------
    // Move the current node to the next node
    // If we are already at the end, tell the user.
    // -------------------------------------------------------------------
    void goForward() {
        if (current == nullptr) {
            cout << "The lis tis empty." << endl;
            return;
        }
        if (current->next == nullptr) {
            cout << "You are at the END of the list. No more bookmarks forward." << endl;
            cout << "Currently on: " << current->siteName << " -> " << current->url << endl;
        }
        else {
            current = current->next;
            cout << "Moving forward..." << endl;
            cout << "Now on: " << current->siteName << " -> " << current->url << endl;
        }
    }

    // ------------------ GO BACKWARD ONE BOOKMARK -----------------------
    // Moves current nod ot the previous node.
    // If we are at the beginning, tell the user.
    // -------------------------------------------------------------------
    void goBackward() {
        if (current == nullptr) {
            cout << "The list is empty." << endl;
            return;
        }
        if (current->prev == nullptr) {
            cout << "You are at the BEGINNING of the list. No more bookmarks backward." << endl;
            cout << "Currently on: " << current->siteName << " -> " << current->url << endl;
        }
        else {
            current = current->prev;
            cout << "Moving backward..." << endl;
            cout << "Now on: " << current->siteName << " -> " << current->url << endl;
        }
    }

    // ------------------ DISPLAY ALL BOOKMARKS ----------------------------
    // Travese the list and prints each one with a number for each.
    // Marks which one is the current position.
    // -------------------------------------------------------------------
    void displayAll() {
        if (head == nullptr) {
            cout << "The list is empty." << endl;
            return;
        }

        cout << "\n--- Bookmark List ---" << endl;

        Node* temp = head;
        int count = 1;

        while (temp != nullptr) {
            // Put a little arrow next to whichever one is current
            if (temp == current)
                cout << count << ". [CURRENT] " << temp->siteName << " -> " << temp->url << endl;
            else
                cout << count << ". " << temp->siteName << " -> " << temp->url << endl;

            count++;
            temp = temp->next;
        }

        cout << "---------------------\n" << endl;
    }

};  // end BookmarkList class


// ------------------ LOAD THE  BOOKMARKS --------------------------------
// Adds 20 starting bookmarks to the list
// -----------------------------------------------------------------------
void loadDefaultBookmarks(BookmarkList& list) {
    list.addBookmark("OpenAI",            "https://www.openai.com");
    list.addBookmark("Anthropic",         "https://www.anthropic.com");
    list.addBookmark("HuggingFace",       "https://huggingface.co");
    list.addBookmark("Google AI",         "https://ai.google");
    list.addBookmark("DeepMind",          "https://deepmind.google");
    list.addBookmark("Arxiv ML",          "https://arxiv.org/list/cs.LG/recent");
    list.addBookmark("PyTorch",           "https://pytorch.org");
    list.addBookmark("TensorFlow",        "https://www.tensorflow.org");
    list.addBookmark("Kaggle",            "https://www.kaggle.com");
    list.addBookmark("Papers With Code",  "https://paperswithcode.com");
    list.addBookmark("Fast.ai",           "https://www.fast.ai");
    list.addBookmark("LangChain Docs",    "https://docs.langchain.com");
    list.addBookmark("Stack Overflow",    "https://stackoverflow.com");
    list.addBookmark("GitHub",            "https://github.com");
    list.addBookmark("NVIDIA Developer",  "https://developer.nvidia.com");
    list.addBookmark("MLflow",            "https://mlflow.org");
    list.addBookmark("Weights & Biases",  "https://wandb.ai");
    list.addBookmark("Towards Data Sci",  "https://towardsdatascience.com");
    list.addBookmark("UAT",               "https://www.uat.edu");
    list.addBookmark("CPP Reference",     "https://en.cppreference.com");
}


// ------------------------ MAIN -----------------------------------------
// MAIN will the menu and handles user input 
// using a while loop for this until user exits the lsit
// -----------------------------------------------------------------------
int main() {

    BookmarkList myList;

    cout << "Loading default bookmarks..." << endl;
    loadDefaultBookmarks(myList);
    cout << "\nAll bookmarks loaded.\n" << endl;

    int choice = 0;

    // Keep shoing the menu until the user picks 7 to exit
    while (choice != 7) {

        cout << "=== Bookmark Manager Menu ===" << endl;
        cout << "1. Display all bookmarks"       << endl;
        cout << "2. Go forward"                  << endl;
        cout << "3. Go backward"                 << endl;
        cout << "4. Add a bookmark"              << endl;
        cout << "5. Delete a bookmark"           << endl;
        cout << "6. Find a bookmark"             << endl;
        cout << "7. Exit"                        << endl;
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();  // clear thebuffer after cin takes in the user's choice
        cout << endl;

        // traversing the list
        if (choice == 1) {
            myList.displayAll();
        }
        else if (choice == 2) {
            myList.goForward();
        }
        else if (choice == 3) {
            myList.goBackward();
        }
        else if (choice == 4) {
            string name, url;
            cout << "Enter a name for the bookmark: ";
            getline(cin, name);
            cout << "Enter the URL: ";
            getline(cin, url);
            myList.addBookmark(name, url);
        }
        else if (choice == 5) {
            string name;
            cout << "Enter the bookmark name to delete: ";
            getline(cin, name);
            myList.deleteBookmark(name);
        }
        else if (choice == 6) {
            string name;
            cout << "Enter the bookmark name to find: ";
            getline(cin, name);
            myList.findBookmark(name);
        }
        else if (choice == 7) {
            cout << "Exiting. Goodbye." << endl;
        }
        else {
            cout << "Invalid choice, please enter 1-7." << endl;
        }

        cout << endl;
    }

    return 0;
}