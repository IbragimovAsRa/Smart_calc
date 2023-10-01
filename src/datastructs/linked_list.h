#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#define STRMAX 256
#define CMNDMAX 5

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum DataType {
    NUM,
    SYMB,  // + - / * ^ ( )
    CMND,
    UNAR,
    X
} DataType;

typedef union Data {
    double num;
    char symb;
    char cmnd[CMNDMAX];
    char unar;
} Data;

typedef struct Node {
    DataType dataType;
    Data data;
    struct Node *next;
} Node;

void init_list(Node **head);

Node *new_node(Data data, DataType dataType);
void add_node(Node **head, Data data, DataType dataType);
void add_node_as_node(Node **head, Node newNode);
void destroy(Node *head);
Node *get_by_index(Node *head, int index);
void print_list(Node *head);
int is_equal(Node *head1, Node *head2);
int is_equal_token(Node head1, Node head2);
Node get_last(Node *head);

#endif  // LINKED_LIST_H