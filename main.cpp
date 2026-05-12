#include <iostream>
#include <string>
using namespace std;



struct ItemNode {
    int id;
    string name;
    int quantity;
    ItemNode* left;
    ItemNode* right;
};

ItemNode* createItem(int id, string name, int quantity) {
    ItemNode* newItem = new ItemNode;
    newItem->id = id;
    newItem->name = name;
    newItem->quantity = quantity;
    newItem->left = nullptr;
    newItem->right = nullptr;
    return newItem;
}

ItemNode* insertItem(ItemNode* root, int id, string name, int quantity) {
    if (root == nullptr) {
        return createItem(id, name, quantity);
    }

    if (id < root->id) {
        root->left = insertItem(root->left, id, name, quantity);
    }
    else if (id > root->id) {
        root->right = insertItem(root->right, id, name, quantity);
    }
    else {
        cout << "Item ID already exists.\n";
    }

    return root;
}

ItemNode* searchItem(ItemNode* root, int id) {
    if (root == nullptr || root->id == id) {
        return root;
    }

    if (id < root->id) {
        return searchItem(root->left, id);
    }

    return searchItem(root->right, id);
}

void displayInventory(ItemNode* root) {
    if (root == nullptr) {
        return;
    }

    displayInventory(root->left);

    cout << "ID: " << root->id
         << " | Name: " << root->name
         << " | Quantity: " << root->quantity << endl;

    displayInventory(root->right);
}

// ---------- CUSTOM PRIORITY QUEUE ----------

struct Delivery {
    int orderId;
    string address;
    int priority;
};

struct DeliveryQueue {
    Delivery data[50];
    int size = 0;
};

void addDelivery(DeliveryQueue& queue, int orderId, string address, int priority) {
    if (queue.size == 50) {
        cout << "Delivery queue is full.\n";
        return;
    }

    Delivery newDelivery;
    newDelivery.orderId = orderId;
    newDelivery.address = address;
    newDelivery.priority = priority;

    int i = queue.size - 1;

    while (i >= 0 && queue.data[i].priority < priority) {
        queue.data[i + 1] = queue.data[i];
        i--;
    }

    queue.data[i + 1] = newDelivery;
    queue.size++;

    cout << "Delivery added successfully.\n";
}

void processDelivery(DeliveryQueue& queue) {
    if (queue.size == 0) {
        cout << "No deliveries available.\n";
        return;
    }

    Delivery next = queue.data[0];

    cout << "Processing delivery:\n";
    cout << "Order ID: " << next.orderId << endl;
    cout << "Address: " << next.address << endl;
    cout << "Priority: " << next.priority << endl;

    for (int i = 1; i < queue.size; i++) {
        queue.data[i - 1] = queue.data[i];
    }

    queue.size--;
}

void displayDeliveries(DeliveryQueue queue) {
    if (queue.size == 0) {
        cout << "No pending deliveries.\n";
        return;
    }

    cout << "\n--- Pending Deliveries ---\n";

    for (int i = 0; i < queue.size; i++) {
        cout << "Order ID: " << queue.data[i].orderId
             << " | Address: " << queue.data[i].address
             << " | Priority: " << queue.data[i].priority << endl;
    }
}

// ---------- MAIN PROGRAM ----------

int main() {
    ItemNode* inventoryRoot = nullptr;
    DeliveryQueue deliveryQueue;

    int choice;

    do {
        cout << "\n===== Warehouse Delivery System =====\n";
        cout << "1. Add Item to Inventory\n";
        cout << "2. Search Item\n";
        cout << "3. Display Inventory\n";
        cout << "4. Add Delivery Order\n";
        cout << "5. Process Delivery\n";
        cout << "6. Display Deliveries\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int id, quantity;
            string name;

            cout << "Enter item ID: ";
            cin >> id;

            cout << "Enter item name: ";
            cin >> name;

            cout << "Enter quantity: ";
            cin >> quantity;

            inventoryRoot = insertItem(inventoryRoot, id, name, quantity);
        }

        else if (choice == 2) {
            int id;

            cout << "Enter item ID to search: ";
            cin >> id;

            ItemNode* found = searchItem(inventoryRoot, id);

            if (found != nullptr) {
                cout << "Item found!\n";
                cout << "ID: " << found->id << endl;
                cout << "Name: " << found->name << endl;
                cout << "Quantity: " << found->quantity << endl;
            }
            else {
                cout << "Item not found.\n";
            }
        }

        else if (choice == 3) {
            cout << "\n--- Inventory List ---\n";
            displayInventory(inventoryRoot);
        }

        else if (choice == 4) {
            int orderId;
            string address;
            int priority;

            cout << "Enter order ID: ";
            cin >> orderId;

            cout << "Enter delivery address: ";
            cin.ignore();
            getline(cin, address);

            cout << "Enter priority 1-5: ";
            cin >> priority;

            addDelivery(deliveryQueue, orderId, address, priority);
        }

        else if (choice == 5) {
            processDelivery(deliveryQueue);
        }

        else if (choice == 6) {
            displayDeliveries(deliveryQueue);
        }

        else if (choice == 0) {
            cout << "Exiting system...\n";
        }

        else {
            cout << "Invalid choice.\n";
        }

    } while (choice != 0);

    return 0;
}
