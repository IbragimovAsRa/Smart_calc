#include "linked_list.h"

void init_list(Node **head) { *head = NULL; }
Node *new_node(Data data, DataType dataType) {  // ssgsdg
    Node *node;
    node = malloc(sizeof(Node));
    node->dataType = dataType;
    node->data = data;
    node->next = NULL;
    return node;
}
Node get_last(Node *head) {
    while (head->next) {
        head = head->next;
    }
    return *head;
}
void add_node(Node **head, Data data, DataType dataType) {
    Node *current = *head;
    Node *node = new_node(data, dataType);
    if (current == NULL) {
        *head = node;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = node;
    }
}

void add_node_as_node(Node **head, Node newNode) {
    Node *current = *head;
    Node *node = new_node(newNode.data, newNode.dataType);
    if (current == NULL) {
        *head = node;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = node;
    }
}

// Node *get_by_index(Node *head, int index) {
//     Node *ptr = head;
//     int counter = 0;
//     while (ptr && counter != index) {
//         counter++;
//         ptr = ptr->next;
//     }
//     return ptr;
// }
void destroy(Node *head) {
    Node *prev = head;
    while (head != NULL) {
        head = head->next;
        free(prev);
        prev = head;
    }
}

// int is_equal(Node *head1, Node *head2) {
//     int result = 0;
//     int i = 0;
//     int j = 0;
//     while (head1 != NULL && head2 != NULL) {
//         if (is_equal_token(*head1, *head2) == 1) {
//             i++;
//         }
//         head1 = head1->next;
//         head2 = head2->next;
//         j++;
//     }
//     if (head1 == NULL && head1 == NULL) {
//         result = 1;
//     } else if (i == j) {
//         result = 1;
//     }
//     return result;
// }
// int is_equal_token(Node head1, Node head2) {
//     int result = 0;
//     if (head1.dataType == head2.dataType) {
//         switch (head1.dataType) {
//             case NUM:
//                 result =
//                     (fabs(head1.data.num - head2.data.num) < 10e-7) ? 1 : 0;
//                 break;
//             case SYMB:
//                 result = (head1.data.symb == head2.data.symb) ? 1 : 0;
//                 break;
//             case CMND:
//                 result =
//                     (strcmp(head1.data.cmnd, head2.data.cmnd) == 0) ? 1 : 0;
//                 break;
//             default:
//                 break;
//         }
//     }
//     return result;
// }

// void print_list(Node *head) {
//     printf("\nContent of list\n");
//     struct Node *ptr = head;
//     int i = 0;
//     while (ptr) {
//         switch (ptr->dataType) {
//             case NUM:
//                 printf("Elem %i: type = NUM, num = %f  ->\n", i,
//                 ptr->data.num); break;
//             case SYMB:
//                 printf("Elem %i: type = SYMB, symb = '%c'  ->\n", i,
//                        ptr->data.symb);
//                 break;
//             case CMND:
//                 printf("Elem %i: type = CMND, cmnd = %s  ->\n", i,
//                        ptr->data.cmnd);
//                 break;
//             case UNAR:
//                 printf("Elem %i: type = UNAR, unar = '%c'  ->\n", i,
//                        ptr->data.unar);
//                 break;
//             case X:
//                 printf("Elem %i: type = X, x  ->\n", i);
//                 break;
//             default:
//                 printf("Elem %i: XZ\n", i);
//         }
//         ptr = ptr->next;
//         i++;
//     }
//     printf("\n");
// }
