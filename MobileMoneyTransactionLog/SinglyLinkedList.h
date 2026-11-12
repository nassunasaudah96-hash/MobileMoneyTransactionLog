#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include <stdexcept>

template <typename T>
class SinglyLinkedList
{
private:
    struct Node
    {
        T data;
        Node *next;

        Node(const T &value) : data(value), next(nullptr) {}
    };

    Node *head;
    Node *tail;
    int count;

public:
    // Constructor
    SinglyLinkedList()
        : head(nullptr), tail(nullptr), count(0) {}

    // Deep copy constructor
    SinglyLinkedList(const SinglyLinkedList &other)
        : head(nullptr), tail(nullptr), count(0)
    {
        Node *current = other.head;

        while (current != nullptr)
        {
            append(current->data);
            current = current->next;
        }
    }

    // Copy assignment operator
    SinglyLinkedList &operator=(const SinglyLinkedList &other)
    {
        if (this != &other)
        {
            SinglyLinkedList temporary(other);
            swap(temporary);
        }
        return *this;
    }

    // Swap two lists
    void swap(SinglyLinkedList &other)
    {
        Node *tempHead = head;
        head = other.head;
        other.head = tempHead;

        Node *tempTail = tail;
        tail = other.tail;
        other.tail = tempTail;

        int tempCount = count;
        count = other.count;
        other.count = tempCount;
    }

    // Destructor
    ~SinglyLinkedList()
    {
        clear();
    }

    // Add a node at the end
    void append(const T &value)
    {
        Node *newNode = new Node(value);

        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }

        count++;
    }

    // Remove a node by position
    bool removeAt(int index)
    {
        if (index < 0 || index >= count)
        {
            return false;
        }

        Node *current = head;

        if (index == 0)
        {
            head = head->next;
            delete current;
            count--;

            if (count == 0)
            {
                tail = nullptr;
            }

            return true;
        }

        Node *previous = nullptr;

        for (int i = 0; i < index; i++)
        {
            previous = current;
            current = current->next;
        }

        previous->next = current->next;

        if (current == tail)
        {
            tail = previous;
        }

        delete current;
        count--;

        return true;
    }

    // Update a node by position
    bool updateAt(int index, const T &value)
    {
        if (index < 0 || index >= count)
        {
            return false;
        }

        Node *current = head;

        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }

        current->data = value;
        return true;
    }

    // Retrieve a record by position
    T getAt(int index) const
    {
        if (index < 0 || index >= count)
        {
            throw std::out_of_range("Invalid list index");
        }

        Node *current = head;

        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }

        return current->data;
    }

    // Find transaction by ID
    int findIndexById(int id) const
    {
        Node *current = head;
        int index = 0;

        while (current != nullptr)
        {
            if (current->data.transactionId == id)
            {
                return index;
            }

            current = current->next;
            index++;
        }

        return -1;
    }

    // Return number of records
    int size() const
    {
        return count;
    }

    // Check if list is empty
    bool isEmpty() const
    {
        return head == nullptr;
    }

    // Convert list into a dynamic array for sorting/searching
    T *toArray() const
    {
        if (count == 0)
        {
            return nullptr;
        }

        T *array = new T[count];
        Node *current = head;

        for (int i = 0; i < count; i++)
        {
            array[i] = current->data;
            current = current->next;
        }

        return array;
    }

    // Delete every node
    void clear()
    {
        Node *current = head;

        while (current != nullptr)
        {
            Node *nextNode = current->next;
            delete current;
            current = nextNode;
        }

        head = nullptr;
        tail = nullptr;
        count = 0;
    }
};

#endif