#include <bits/stdc++.h>

struct Node
{
    int data;
    Node *next;
    Node *sibling;
    Node(int data = 0, Node *next = nullptr, Node *sibling = nullptr) : data(data), next(next), sibling(sibling) {}
};

Node *Trim(Node *pHead)
{
    Node *pTmp = new Node();
    pTmp->next = nullptr;

    for (Node *p, *q = pHead, *ptr = pHead; ptr != nullptr; )
    {
        for (p = pHead; p != ptr && ptr->data != p->data; p = p->next) {}

        if (p != ptr)
        {
            q->next = ptr->next;
            ptr->next = pTmp->next;
            pTmp->next = ptr;

            ptr = q->next;
        }
        else
        {
            q = ptr;
            ptr = ptr->next;
        }
    }

    for (Node *p = pHead; p != nullptr; std::cout << p->data << std::endl, p = p->next) {}
    for (Node *p = pHead; p != nullptr; p = p->next)
    {
        for (Node *q = pTmp->next; q != nullptr; q = q->next)
        {
            if (p->sibling == q)
            {
                p->sibling = nullptr;
                break;
            }
        }
    }

    delete pTmp;

    return pHead;
}

int main()
{
    Node *root = new Node(1);
    root->next = new Node(3);
    root->next->next = new Node(1);
    root->next->next->next = new Node(2);
    root->next->next->next->next = new Node(5);

    root->sibling = root->next->next;
    root->next->next->next->sibling = root->sibling;

    for (Node *p = Trim(root); p != nullptr; std::cout << p->data << " : " << p->sibling << std::endl, p = p->next) {}
    return 0;
}
