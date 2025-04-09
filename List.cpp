#include <iostream>
struct Node
{
    int val;
    Node *next;
    Node *front;
    Node() : val(0), next(nullptr), front(nullptr) {}
    Node(int val) : val(val), next(nullptr), front(nullptr) {}
};

class List
{
private:
    Node *head;
    Node *tail;
    int size;

public:
    List();
    ~List();

    void push_back(int val);
    void push_front(int val);
    int getSize();
    void pop_back();
    void pop_front();
    void deleteNode(Node *cur);
    void deleteVal(int val);
    void clear();

    void print();

    int operator[](int idx);
    friend std::ostream &operator<<(std::ostream &os, const List &lst);
};

List::List() : head(nullptr), tail(nullptr), size(0) {}

List::~List()
{
    while (head)
    {
        Node *tmp = head;
        head = head->next;
        delete tmp;
    }
    head = tail = nullptr;
    size = 0;
}

void List::push_back(int val)
{
    if (!head)
    {
        head = new Node(val);
        tail = head;
    }
    else
    {
        Node *newNode = new Node(val);
        tail->next = newNode;
        newNode->front = tail;
        tail = tail->next;
    }
    size++;
}

void List::push_front(int val)
{
    if (!head)
    {
        head = new Node(val);
        tail = head;
    }
    else
    {
        Node *newNode = new Node(val);
        newNode->next = head;
        head->front = newNode;
        head = newNode;
    }
    size++;
}

int List::getSize()
{
    return size;
}

void List::pop_back()
{
    if (size == 0)
    {
        return;
    }
    else if (head == tail)
    {
        delete head;
        head = tail = nullptr;
    }

    else
    {
        Node *tmp = tail;
        tail = tail->front;
        delete tmp;
        tail->next = nullptr;
    }
    size--;
}

void List::pop_front()
{
    if (size == 0)
    {
        return;
    }
    else if (head == tail)
    {
        delete head;
        head = tail = nullptr;
    }
    else
    {
        Node *tmp = head;
        head = head->next;
        delete tmp;
        head->front = nullptr;
    }
    size--;
}

void List::deleteNode(Node *cur)
{
    if (cur == head)
    {
        pop_front();
    }
    else if (cur == tail)
    {
        pop_back();
    }
    else
    {
        Node *cur_front = cur->front;
        Node *cur_next = cur->next;
        cur->front->next = cur_next;
        cur->next->front = cur_front;
        delete cur;
        size--;
    }
}

void List::deleteVal(int val)
{
    Node *cur = head;
    while (cur)
    {
        if (cur->val == val)
        {
            Node *tmp = cur;
            cur = cur->next;
            deleteNode(tmp);
        }
        else
        {
            cur = cur->next;
        }
    }
}

void List::clear()
{
    while (head)
    {
        Node *tmp = head;
        head = head->next;
        delete tmp;
    }
    head = tail = nullptr;
    size = 0;
}

void List::print()
{
    if (size == 0)
    {
        std::cout << "empty" << std::endl;
        return;
    }

    Node *cur = head;
    while (cur)
    {
        std::cout << cur->val << " ";
        cur = cur->next;
    }
    std::cout << std::endl;
}

int List::operator[](int idx)
{
    if (idx < 0 || idx >= size)
    {
        return -1;
    }
    Node *cur = head;
    while (idx--)
    {
        cur = cur->next;
    }
    return cur->val;
}

std::ostream &operator<<(std::ostream &os, const List &lst)
{
    Node *cur = lst.head;
    while (cur)
    {
        os << cur->val;
        cur = cur->next;
    }
    return os;
}

int main()
{
    List list;
    int n;
    std::cin >> n;
    std::string command;
    while (n--)
    {
        std::cin >> command;
        if (command == "push_back")
        {
            int val;
            std::cin >> val;
            list.push_back(val);
        }
        else if (command == "push_front")
        {
            int val;
            std::cin >> val;
            list.push_front(val);
        }
        else if (command == "size")
        {
            std::cout << list.getSize() << std::endl;
        }
        else if (command == "print")
        {
            list.print();
        }
        else if (command == "get")
        {
            int idx;
            std::cin >> idx;
            std::cout << list[idx] << std::endl;
        }
        else if (command == "pop_back")
        {
            list.pop_back();
        }
        else if (command == "pop_front")
        {
            list.pop_front();
        }
        else if (command == "remove")
        {
            int val;
            std::cin >> val;
            list.deleteVal(val);
        }
        else if (command == "clear")
        {
            list.clear();
        }
    }
}
