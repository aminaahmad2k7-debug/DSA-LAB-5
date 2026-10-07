#include <iostream>
#include <string>
using namespace std;

// Node for print job
struct JobNode {
    int jobID;
    string documentName;
    int pages;
    JobNode* next;

    JobNode(int id, const string& name, int p)
        : jobID(id), documentName(name), pages(p), next(nullptr) {
    }
};

// Linked-node Queue for print jobs
class JobQueue {
private:
    JobNode* front;
    JobNode* rear;
    int count;

public:
    JobQueue() : front(nullptr), rear(nullptr), count(0) {}

    ~JobQueue() {
        clear();
    }

    // 1. Add Job ... Insert at rear
    void addJob(int id, const string& name, int pages) {
        JobNode* newNode = new JobNode(id, name, pages);
        if (isEmpty()) {
            front = rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }
        count++;
        cout << "Job added successfully!" << endl;
    }

    // 2. Process Job – Remove from front
    bool processJob() {
        if (isEmpty()) {
            cout << "Queue is empty. No job to process." << endl;
            return false;
        }
        JobNode* temp = front;
        cout << "Processing Job ID: " << temp->jobID
            << " - Document: " << temp->documentName
            << " (" << temp->pages << " pages)" << endl;

        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
        count--;
        return true;
    }

    // 3. View Next Job
    void viewNextJob() const {
        if (isEmpty()) {
            cout << "Queue is empty. No next job." << endl;
            return;
        }
        cout << "Next Job -> ID: " << front->jobID
            << ", Document: " << front->documentName
            << ", Pages: " << front->pages << endl;
    }

    // 4. Display Queue
    void displayQueue() const {
        if (isEmpty()) {
            cout << "Queue is empty." << endl;
            return;
        }
        cout << "\nCurrent Queue (Front to Rear):" << endl;
        cout << "----------------------------------------" << endl;
        JobNode* current = front;
        int pos = 1;
        while (current != nullptr) {
            cout << pos << ". Job ID: " << current->jobID
                << " | Document: " << current->documentName
                << " | Pages: " << current->pages << endl;
            current = current->next;
            pos++;
        }
        cout << "----------------------------------------" << endl;
    }

    // 5. Count Jobs
    int countJobs() const {
        return count;
    }

    // 6. IsEmpty
    bool isEmpty() const {
        return front == nullptr;
    }

    // 7. Clear Queue
    void clear() {
        while (!isEmpty()) {
            JobNode* temp = front;
            front = front->next;
            delete temp;
        }
        rear = nullptr;
        count = 0;
        cout << "Queue cleared. All memory released." << endl;
    }
};

int main() {
    JobQueue printer;
    int choice;

    cout << "=== Task 2: Printer Job Scheduling Using a Queue ===" << endl;
    cout << "Linked Queue Implementation" << endl;

    do {
        cout << "\n========== MENU ==========" << endl;
        cout << "1. Add Job" << endl;
        cout << "2. Process Job" << endl;
        cout << "3. View Next Job" << endl;
        cout << "4. Display Queue" << endl;
        cout << "5. Count Jobs" << endl;
        cout << "6. Check if Empty" << endl;
        cout << "7. Clear Queue" << endl;
        cout << "8. Exit" << endl;
        cout << "==========================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();   // clear buffer

        switch (choice) {
        case 1: {
            int id, pages;
            string name;

            cout << "Enter Job ID: ";
            cin >> id;
            cin.ignore();

            cout << "Enter Document Name: ";
            getline(cin, name);

            cout << "Enter Number of Pages: ";
            cin >> pages;
            cin.ignore();

            printer.addJob(id, name, pages);
            break;
        }
        case 2:
            printer.processJob();
            break;
        case 3:
            printer.viewNextJob();
            break;
        case 4:
            printer.displayQueue();
            break;
        case 5:
            cout << "Total jobs in queue: " << printer.countJobs() << endl;
            break;
        case 6:
            cout << "Is Queue Empty? " << (printer.isEmpty() ? "Yes" : "No") << endl;
            break;
        case 7:
            printer.clear();
            break;
        case 8:
            cout << "Exiting program..." << endl;
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }

    } while (choice != 8);

    return 0;
}