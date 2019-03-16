struct Node { 
    // Any data type can be stored in this node 
    void  *data; 
  
    struct Node *next; 
}; 
  

/* Function to add a node at the beginning of Linked List. 
   This function expects a pointer to the data to be added 
   and size of the data type */
void push(struct Node** head_ref, void *new_data, size_t data_size);
  
/* Function to print nodes in a given linked list. fpitr is used 
   to access the function to be used for printing current node data. 
   Note that different data types need different specifier in printf() */
void printList(struct Node *node, void (*fptr)(void *));

// Function to print an integer 
void printInt(void *n);
  
// Function to print a float 
void printFloat(void *f);
