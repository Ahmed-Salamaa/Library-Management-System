#ifndef FILE_LINKED_LIST
#define FILE_LINKED_LIST

#include <vector>
#include <string>
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
    LinkedList() : head(nullptr), size(0) {}
    
    std::vector<t> searchAllByPredicate(std::function<bool(const t &)> condition)
    {
        std::vector<t> result;
        node *curr = head;

        while (curr != nullptr)
        {
            if (condition(curr->data))
                result.push_back(curr->data);

            curr = curr->next;
        }

        return result;
    }

    void insert(t obj)
    {
        node *newNode = new node(obj);

        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            newNode->next = head;
            head = newNode;
        }

        size++;
    }

    t search(int id)
    {
        node *curr = head;

        if (curr == nullptr)
            throw "There is no data";

        while (curr != nullptr)
        {
            if (curr->data.getId() == id)
                return curr->data;

            curr = curr->next;
        }

        throw "The data does not exist";
    }

    t search(string name)
    {
        node *curr = head;

        if (curr == nullptr)
            throw "There is no data";

        while (curr != nullptr)
        {
            if (curr == name)
                return curr->data;

            curr = curr->next;
        }

        throw "The data does not exist";
    }

    void erase(t obj)
    {
        if (size == 0)
            return;

        node *curr = head;
        if (head->data == obj)
        {
            head = head->next;
            delete curr;
            size--;
            return;
        }
        node *prev = nullptr;
        curr = head;

        while (curr != nullptr)
        {
            if (curr->data == obj)
            {
                prev->next = curr->next;
                delete curr;
                size--;
                return;
            }

            prev = curr;
            curr = curr->next;
        }
    }

    void erase(int id)
    {
        t obj = search(id);
        erase(obj);
    }
};

#endif
