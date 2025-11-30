#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

static Node *push_front(Node *head, int value) {
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    node->data = value;
    node->next = head;
    return node;
}

static void print_list(const char *label, const Node *head) {
    printf("%s: ", label);
    while (head != NULL) {
        printf("%d", head->data);
        head = head->next;
        if (head != NULL) {
            printf(" -> ");
        }
    }
    printf("\n");
}

static Node *reverse_list(Node *head) {
    Node *prev = NULL;
    Node *curr = head;

    puts("Reversing the linked list step by step:");
    while (curr != NULL) {
        Node *next = curr->next;
        printf("  visiting node %d: next now points to %s\n",
               curr->data, prev ? "previous node" : "NULL");
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    puts("All nodes processed; list reversed.\n");

    return prev;
}

static void free_list(Node *head) {
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

int main(void) {
    Node *head = NULL;

    for (int value = 5; value >= 1; --value) {
        head = push_front(head, value);
    }

    print_list("Original list", head);
    head = reverse_list(head);
    print_list("Reversed list", head);

    free_list(head);
    return 0;
}
