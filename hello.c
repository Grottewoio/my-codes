#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *name;
    struct Node *next;
} Node;

static char *dup_string(const char *src) {
    size_t len = strlen(src) + 1;
    char *copy = malloc(len);
    if (copy == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    memcpy(copy, src, len);
    return copy;
}

static Node *push_front(Node *head, const char *name) {
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    node->name = dup_string(name);
    node->next = head;
    return node;
}

static void print_list(const char *label, const Node *head) {
    printf("%s: ", label);
    while (head != NULL) {
        printf("%s", head->name);
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
        printf("  visiting %s: next now points to %s\n",
               curr->name, prev ? prev->name : "NULL");
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
        free(head->name);
        free(head);
        head = next;
    }
}

int main(void) {
    Node *head = NULL;

    const char *people[] = {"Alice", "Bob", "Charlie", "Dana", "Eve"};
    size_t count = sizeof(people) / sizeof(people[0]);
    for (size_t i = count; i-- > 0;) {
        head = push_front(head, people[i]);
    }

    print_list("Original list", head);
    head = reverse_list(head);
    print_list("Reversed list", head);

    free_list(head);
    return 0;
}
