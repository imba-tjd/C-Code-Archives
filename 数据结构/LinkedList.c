// 头结点单独处理的实现
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
    while (head->next != NULL)
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
    while ((head = head->next) != NULL)
        if (head->data == data)
            return head;
    return NULL;
}

Node* Node_find_at(Node* head, int ndx) {
    while (--ndx >= 0)
        head = head->next;
    return head->next;
}

// 必须要在前一个结点检查
Node* Node_remove(Node* head, int data) {
    while (head->next != NULL)
        if (head->next->data != data)
            head = head->next;
        else {
            Node* t = head->next;
            head->next = head->next->next;
            return t;
        }
    return NULL;
}

Node* Node_remove_at(Node* head, int ndx) {
    while (--ndx >= 0)
        head = head->next;

    Node* t = head->next;
    if (t != NULL)
        head->next = t->next;
    return t;  // 包含t==NULL
}

void Node_reverse(Node* head) {
    Node new_head;
    Node_init(&new_head, 0);

    while (head->next != NULL) {
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
