#include <iostream>
#include <iomanip>

//object class for the nodes
class Node {
    //data fields
    int value;
    Node* next;

public:
    //user-defined constructor
    Node (int value) {
        this->value = value;
        next = NULL;
    }

    //accessors
    int getValue () {
        return this->value;
    }
    Node* getNext () {
        return this->next;
    }

    //mutators
    void setValue (int value) {
        this->value = value;
    }
    void setNext (Node* next) {
        this->next = next;
    }

};

//object class for the list
class SingleLinkedList {
    //private data fields
    int length;
    Node* head;
    Node* tail;

public:
    //user-defined constructor for a list
    SingleLinkedList() {
        length = 0;
        this->head = NULL;
        this->tail = NULL;
    }

    //functions for the thirteen API list functions

    //PushFront(key)
    void PushFront(int key) {
        Node* front = new Node(key);

        if (this->length == 0) {
            //makes head and tail the one node
            this->tail = front;
            front->setNext(this->tail);
        } else {
            //links node to the original head
            front->setNext(this->head);
        }
        this->head = front;
        this->length++;
    }

    //PushBack(key)
    void PushBack(int key) {
        Node* back = new Node(key);

        if (this->length == 0) {
            //makes head and tail the one node
            this->head = back;
            (this->head)->setNext(this->tail);
        } else {
            Node* temp1 = this->head; //reference node

            //finds the item before tail
            for(int i = 0; i < this->length; i++)
            {
                //tail (and only tail!) will always point to NULL
                if (temp1->getNext() == NULL) {
                    break;
                }
                temp1 = temp1->getNext();
            }
            
            //point the item to back instead of tail
            temp1->setNext(back);
        }
        
        this->tail = back;
        this->length++;
    }

    //PopFront
    void PopFront() {
        //doeesn't run for empty sets
        if (this->length <= 0) {
            std::cout << "There are no elements to remove!" << std::endl;
        } else {
            //creates a new node that has the information of head
            Node* temp = this->head;
            //change the original head to whatever comes after it
            this->head = temp->getNext();
            //delete the temp node with the original info
            delete temp;
            this->length--;
        }
    }

    //PopBack
    void PopBack() {
        //doesn't run for empty sets
        if (this->length <= 0) {
            std::cout << "There are no elements to remove!" << std::endl;
        } else if (this->length == 1) {
            this->head = NULL;
            this->tail = NULL;
            this->length--;
        } else {
            Node* temp1 = this->head; //reference node
            Node* temp2 = this->tail;

            //finds the item before tail
            for(int i = 0; i < this->length; i++)
            {
                //tail (and only tail!) will always point to NULL
                if (temp1->getNext() == temp2) {
                    break;
                }
                temp1 = temp1->getNext();
            }

            //have the item behave like a tail
            temp1->setNext(NULL);
            //replace the original tail with the item
            this->tail = temp1;
            //delete the temp node with the original info
            delete temp2;
            this->length--;
        }
    }

    //AddBefore(node, key)
    void AddBefore(int node, int key) {
        if (this->length <= 0) {
            //doeesn't run for empty sets
            std::cout << "There are no elements to add before!" << std::endl;
            return;
        } else if (node > this->length || node <= 0) {
            //doesn't run for nodes that aren't in the list
            std::cout << "The node number \"" << node << "\" is out of range!" << std::endl;
            return;
        } else {
            Node* before = new Node(key);
            Node* temp = this->head; //node before "before" node
            int i = 1;
            
            
            if (node == 1) { //special case: node happens to be head
                before->setNext(temp);
                this->head = before;
            } else {
                //moves temp from head if needed
                while (i < node - 1) {
                    temp = temp->getNext();
                    i++;
                }
                
                //point new node to previous node's "next"
                before->setNext(temp->getNext());
                //point previous node to new node
                temp->setNext(before);
            }
            this->length++;
            return;
        }
    }

    //AddAfter(node, key)
    void AddAfter(int node, int key) {
        if (this->length <= 0) {
            //doeesn't run for empty sets
            std::cout << "There are no elements to add before!" << std::endl;
            return;
        } else if (node > this->length || node <= 0) {
            //doesn't run for nodes that aren't in the list
            std::cout << "The node number \"" << node << "\" is out of range!" << std::endl;
            return;
        } else {
            Node* after = new Node(key);
            Node* temp1 = this->head; //node after "after" node
            int i = 1;

            //moves forward if needed
            while (i < node) {
                temp1 = temp1->getNext();
                i++;
            }

            if (temp1 == this->tail) { //special case: node happens to be tail
                after->setNext(NULL);
                this->tail = after;
            } else {
                //point new node to current node's "next"
                after->setNext(temp1->getNext());
            }
            //point current node to new node
            temp1->setNext(after);
            this->length++;
            return;
        }
    }

    //Erase(key)
    void Erase(int key) {
        if (Find(key) == 0) {
            std::cout << "There is no key \"" << key << "\" to remove!" << std::endl;
        } else {
            Node* temp1 = this->head;
            Node* temp2 = temp1->getNext();
            
            //assuming that node #1 has an index of 0
            for (int i = 0; i < (this->length); i++) {
                //special cases
                if (temp1->getValue() == key && temp1 == this->head) {
                    this->head = temp2;
                    this->length--;
                } else if (temp2->getValue() == key) {
                    if (temp2 == this->tail) {
                        this->tail = temp1;
                        (this->tail)->setNext(NULL);
                    } else {
                        temp1->setNext(temp2->getNext());
                    }
                    this->length--;
                }
                
                temp1 = temp2;
                temp2 = temp2->getNext();
            }

            //if there are any duplicates, they will all be deleted
            return;
        }
    }

    //Key TopFront()
    int TopFront() {
        return (this->head)->getValue();
    }

    //Key TopBack()
    int TopBack() {
        return (this->tail)->getValue();
    }

    //Size()
    int Size() {
        return this->length;
    }

    //Boolean Empty()
    bool Empty() {
        if (this->length <= 0) {
            return 1;
        } else {
            return 0;
        }
    }

    //Boolean Find(key)
    bool Find(int key) {
        Node* temp = this->head;

        while (temp != NULL) {
            if (temp->getValue() == key) {
                return 1;
            } else {
                temp = temp->getNext();
            }
        }

        return 0;
    }

    //DisplayAll()
    void DisplayAll() {
        Node* display = this->head;

        std::cout << std::endl;

        //empty list
        if (this->length == 0) {
            for (int i = 0; i < 18; i++) {
                std::cout << "-";
            }
            std::cout << std::endl << "|   EMPTY  SET   |" << std::endl;
            for (int i = 0; i < 18; i++) {
                std::cout << "-";
            }
            std::cout << std::endl;
            return;
        }
        
        //top border
        for (int i = 0; i < this->length * 9; i++) {
            std::cout << "-";
        }
        std::cout << std::endl;

        //display
        for (int i = 0; i < this->length; i++) {
            //so that every number is spaced evenly
            std::cout << "|  " << std::setfill('0') << std::setw(3) << display->getValue() << "  |";
            display = display->getNext();
        }
        std::cout << std::endl;
        
        //bottom border
        for (int i = 0; i < this->length * 9; i++) {
            std::cout << "-";
        }
        std::cout << std::endl;
    }
};

void mainMenu(SingleLinkedList &list) {
    int ans, node, key;
    static int count = 0;
    
    std::cout << "Answer: ";
    std::cin >> ans;

    switch (ans) {
        case 1:
            std::cout << "Input Key: ";
            std::cin >> key;
            list.PushFront(key);
            break;
        case 2:
            std::cout << "Input Key: ";
            std::cin >> key;
            list.PushBack(key);
            break;
        case 3:
            list.PopFront();
            break;
        case 4:
            list.PopBack();
            break;
        case 5:
            std::cout << "Input Key: ";
            std::cin >> key;
            std::cout << "Input Node (starting from 1): ";
            std::cin >> node;
            list.AddBefore(node, key);
            break;
        case 6:
            std::cout << "Input Key: ";
            std::cin >> key;
            std::cout << "Input Node (starting from 1): ";
            std::cin >> node;
            list.AddAfter(node, key);
            break;
        case 7:
            std::cout << "Input Key: ";
            std::cin >> key;
            list.Erase(key);
            break;
        case 8:
            std::cout << "Front Key: " << list.TopFront() << std::endl;
            break;
        case 9:
            std::cout << "Back Key: " << list.TopBack() << std::endl;
            break;
        case 10:
            std::cout << "Size: " << list.Size() << std::endl;
            break;
        case 11:
            std::cout << "The list is ";
            if (list.Empty() == 0) {
                std::cout << "not empty.\n";
            } else if (list.Empty() == 1) {
                std::cout << "empty.\n";
            }
            break;
        case 12:
            std::cout << "Input Key: ";
            std::cin >> key;
            std::cout << key << " is ";
            if (list.Find(key) == 0) {
                std::cout << "not ";
            }
            std::cout << "in the list.\n";
            break;
        case 13:    
            list.DisplayAll();
            break;
        case 14:
            //when done with the decisions, returns to main and ends the program
            return;
            break;
        default:
            break;
    }

    std::cout << std::endl;
    mainMenu(list);
    return;
}

int main() {

    //introduction
    std::cout << "Hello! Please select an operation:" << std::endl;
    std::cout << " (1) PushFront \n (2) PushBack \n (3) PopFront \n (4) PopBack \n (5) AddBefore \n (6) AddAfter \n (7) Erase \n (8) TopFront \n (9) TopBack \n (10) Size \n (11) Empty \n (12) Find \n (13) DisplayAll \n (14) Exit Program " << std::endl;

    //creates a list on the first run
    SingleLinkedList list;
    
    //begins the menu loop to allow for multiple commands in one session
    mainMenu(list);
    return 0;
}