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

  Node* current = *head;
  while (current->next != next_node) { // go through the list from the front
    current = current->next;
  }

  current->next = node; // then insert the node where the next_node used to be

};


void list_delete(Node** head, int data){

};


Node* list_search(Node** head, int data){

};


void list_display(Node** head){

};


void list_display_range(Node** head, Node* start_node, Node* end_node){

};


int list_count_nodes(Node** head){

};


void list_cleanup(Node** head){

};
