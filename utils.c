#include "utils.h"

// return the length of a list, excluding the head
int list_head_length(struct list_head *head){
    int length = 0;
    struct list_head *pos = head->next;
    while(pos != head){
        length++;
        pos = pos->next;
    }
    return length;
}

// return the pointer of the node at th position, excluding the head
struct list_head *list_head_at(struct list_head *head, int th){
    if(th <= 0 || th > list_head_length(head))
        return NULL;

    struct list_head *pos = head;
    for(int i = 0; i < th; i++)
        pos = pos->next;
    return pos;
}

