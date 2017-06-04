#include <stdio.h>
#include <stdlib.h>

struct student
{
    char name[10];
    float score;
    struct student *next;
};

struct student * create(int n)
{
    struct student *head, *pnew, *ptail;
    int i;
    pnew=(struct student *)malloc(sizeof(struct student));
    scanf("%s%f", pnew->name, &pnew->score);
    head=ptail=pnew;
    for (i = 0; i < n; i++) {
        pnew = (struct student *)malloc(sizeof(struct student));
        scanf("%s%f", pnew->name, &pnew->score);
        ptail->next=pnew;
        ptail=pnew;
    }
    ptail->next=NULL;
    return head;
}

void print(struct student * head)
{
    struct student *p=head;
    while (p != NULL) {
        printf("%s  %.1f\n", p->name, p->score);
        p=p->next;
    }
}

struct student * insert(struct student * head)
{
    struct student *p, *pnew, *pold;
    pnew=(struct student *)malloc(sizeof(struct student));
    scanf("%s%f", pnew->name, &pnew->score);
    p=head;
    if(pnew->score > head->score) {
        pnew->next=head;
        head=pnew;
    } else {
        while(p != NULL && pnew->score < p->score) {
            pold=p;
            p=p->next;
        }
        pnew->next=p;
        pold->next=pnew;
    }
    return head;
}

struct student * pdelete(struct student * head, int grade)
{
    struct student *p, *pold;
    p=head;
    while(head != NULL && head->score >= grade) {
        head=head->next;
        free(p);
        p=head;
    }
    if(head == NULL)
        return head;

    p=head->next;
    pold=head;
    while(p != NULL) {
        if(p->score >= grade) {
            pold->next=p->next;
            free(p);
            p=plod->next;
        } else {
            pold=p;
            p=p->next;
        }
    }
    return head;
}