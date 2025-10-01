#include<stdio.h>
#include<stdlib.h>
#include"solution.h"
 
struct LinkList* gennode(int x){
    struct LinkList *node = (struct LinkList*)malloc(sizeof(struct LinkList));
    node->val = x;
    node->next = NULL;
}
 
int main(void){
    //第一行輸入總共有n個node
    //第二行輸入以第幾個作為入口節點
    //接下來第i行都代表第i節的值
    int n , intersect , value;
    struct LinkList *intersect_node , *head , *ptr;
 
    scanf("%d%d" , &n , &intersect);
    scanf("%d" , &value);
    head = gennode(value);
    ptr = head;
    if(intersect == 0)
        intersect_node = ptr;
 
    for(int i = 1 ; i < n ; i++){
        scanf("%d" , &value);
        struct LinkList* temp = gennode(value);
        ptr->next = temp;
        ptr = temp;
        if(i == intersect)
            intersect_node = ptr;
    }
    ptr->next = intersect_node;
 
    struct LinkList *res = solution(head);
    if(res == intersect_node)
        printf("1\n");
    else
        printf("0\n");
    return 0;
}
