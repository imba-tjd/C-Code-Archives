// 头结点单独处理的实现
// 返回指针的函数已考虑返回NULL的情况
// 如果一开始head = head->next，那head就是当前结点，否则就相当于prev结点
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

void Node_init(Node* n, int data) {
    n->data = data;
    n->next = NULL;
}

Node* Node_new(int data) {
    Node* n = malloc(sizeof(Node));
    Node_init(n, data);
    return n;
}

void Node_append(Node* head, Node* n) {
    while (head->next)
        head = head->next;
    head->next = n;
}

void Node_insert(Node* head, Node* n, int ndx) {
    while (--ndx >= 0)
        head = head->next;
    n->next = head->next;
    head->next = n;
}

Node* Node_find(Node* head, int data) {
    head = head->next;
    while (head && head->data != data)
        head = head->next;
    return head;
}

Node* Node_find_at(Node* head, int ndx) {
    while (--ndx >= 0)
        head = head->next;
    return head->next;
}

Node* Node_remove(Node* head, int data) {
    Node* prev = head;
    head = head->next;

    while (head && head->data != data)
        prev = head, head = head->next;

    if (head)
        prev->next = head->next;
    return head;
}

Node* Node_remove_at(Node* head, int ndx) {
    while (--ndx >= 0)
        head = head->next;

    Node* toberemoved = head->next;
    if (toberemoved)
        head->next = toberemoved->next;
    return toberemoved;
}

void Node_reverse(Node* head) {
    Node new_head;
    Node_init(&new_head, 0);

    while (head->next) {
        Node* t = head->next;
        head->next = t->next;
        t->next = NULL;
        Node_insert(&new_head, t, 0);
    }

    head->next = new_head.next;
}

int main(void) {
    Node head;
    Node_init(&head, 0);

    Node_append(&head, Node_new(2));
    Node_append(&head, Node_new(3));
    assert(head.next->data == 2);
    Node_insert(&head, Node_new(1), 0);
    assert(head.next->data == 1);
    assert(Node_remove(&head, 2)->data == 2);
    assert(Node_find(&head, 2) == NULL);
    assert(Node_remove(&head, 2) == NULL);
    Node_reverse(&head);
    assert(head.next->data == 3);
    assert(Node_find_at(&head, 1)->data == 1);
    assert(Node_remove_at(&head, 0)->data == 3);
    assert(head.next->data == 1);
    assert(Node_find_at(&head, 1) == NULL);
    assert(Node_remove_at(&head, 1) == NULL);
}
