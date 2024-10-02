#include "linked_list.h"


void list_init(Node** head, size_t size){
  mem_init(size); // initialize memory pool of size size
  *head = NULL; // sets pointer to pointer to head to null
};


void list_insert(Node** head, int data){
  Node* node = (Node*) mem_alloc(sizeof(Node));
 
  node->data = data;
  node->next = NULL;

  if (*head == NULL){ // if the list is empty set this as the first node
    *head = node;
  }
  else{ // if the list is not empty put the node last
    Node* current = *head;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = node;
  }
};


void list_insert_after(Node* prev_node, int data){
  Node* node = (Node*) mem_alloc(sizeof(Node));
  node->data = data;
  
  node->next = prev_node->next; // give the prev_node-> next to this node and then put this node as prev_node-> next
  prev_node->next = node;

};


void list_insert_before(Node** head, Node* next_node, int data){
  Node* node = (Node*) mem_alloc(sizeof(Node));
  node->data = data;

  node->next = next_node;

  if (*head == next_node){ // if next_node is the first node
    *head = node;
  }
  else {

    Node* current = *head;
    while (current->next != next_node) { // go through the list from the front
      current = current->next;
    }
    current->next = node; // then insert the node where the next_node used to be
  }
};


void list_delete(Node** head, int data){
  Node* current = *head;
  Node* prev_node = NULL;

  while (current != NULL){
    if (current->data == data){
      if (prev_node != NULL){
        prev_node->next = current->next;
      }
      mem_free(current);
      return;
    }
    prev_node = current;
    current = current->next;
  }
};


Node* list_search(Node** head, int data){
  Node* current = *head;

  while (current->data != data){
    if (current == NULL){
      printf("data not in list");
      return 0;
    }
    current = current->next;
  }
  return current;
};


void list_display_range(Node** head, Node* start_node, Node* end_node){
  if (start_node == NULL){
    start_node = *head;
  }

  printf("[");
  while (start_node->next != end_node){ // if end_node is NULL it will still just go to the last one
    printf("%d", start_node->data);
    printf(", ");
    start_node = start_node->next;
  }
  printf("%d", start_node->data);
  printf("]");
};


void list_display(Node** head){
  list_display_range(head, NULL, NULL);
};


int list_count_nodes(Node** head){
  Node* current = *head;
  int i = 0;
  while (current != NULL){
    i++;
    current = current->next;
  }
  return i;
};


void list_cleanup(Node** head){
  Node* current = *head;
  Node* next;

  while (current != NULL){
    next = current->next;
    mem_free(current);
    current = next;
  }
  
};
