#ifndef FILE_LINKED_LIST
#define FILE_LINKED_LIST

#include <bits/stdc++.h>
using namespace std;

template <typename t>
class LinkedList
{
private:
    struct node
    {
        t data;
        node *next;

        node() : data(), next(nullptr) {}
        node(t val) : data(val), next(nullptr) {}

        bool operator==(const node &rhs) { return data == rhs.data; }
        bool operator!=(const node &rhs) { return data != rhs.data; }
    };
    node *head;
    int size;

public:
    // Initializes an empty linked list.
    // @return: A new LinkedList instance with no elements.
    LinkedList() : head(nullptr), size(0) {}

    // Inserts a new element at the beginning of the linked list.
    // @param obj: The element of type 't' to be inserted.
    void insert(t obj)
    {
        node *newNode = new node(obj);

        if (head == nullptr)
            head = newNode;
        else
        {
            newNode->next = head;
            head = newNode;
        }

        size++;
    }

    // Searches the linked list for all elements that satisfy a given condition.
    // @param condition: A function or lambda that takes a const reference to an element of type 't'
    //                    and returns true if the element matches the desired condition.
    // @return: A vector containing all elements in the list that satisfy the condition.
    //          If no elements match, returns an empty vector.
    vector<t> searchAllByPredicate(function<bool(const t &)> condition)
    {
        vector<t> result;
        node *curr = head;

        while (curr != nullptr)
        {
            if (condition(curr->data))
                result.push_back(curr->data);

            curr = curr->next;
        }

        return result;
    }

    // Searches the linked list for the first element that satisfies a given condition.
    // @param condition: A function or lambda that takes a const reference to an element of type 't'
    //                    and returns true if the element matches the desired condition.
    // @return: The first element in the list that satisfies the condition.
    // @throws runtime_error: If the list is empty or no element satisfies the condition.
    t search(function<bool(const t &)> condition)
    {
        node *curr = head;

        if (size == 0)
            throw runtime_error("There is no data");

        while (curr != nullptr)
        {
            if (condition(curr->data))
                return curr->data;

            curr = curr->next;
        }

        throw runtime_error("The data does not exist");
    }

    // Erases the first element in the linked list that satisfies the given condition.
    // @param condition: A function or lambda that takes a const reference to an element of type 't'
    //                    and returns true if the element should be erased.
    // @throws runtime_error: If the list is empty or no element satisfies the condition.
    void erase(function<bool(const t &)> condition)
    {
        if (size == 0)
            throw runtime_error("There is no data");

        node *curr = head;

        if (condition(curr->data))
        {
            head = head->next;
            delete curr;
            size--;
            return;
        }

        node *prev = nullptr;

        while (curr != nullptr)
        {
            if (condition(curr->data))
            {
                prev->next = curr->next;
                delete curr;
                size--;
                return;
            }

            prev = curr;
            curr = curr->next;
        }

        throw runtime_error("The data does not exist");
    }
};

#endif
