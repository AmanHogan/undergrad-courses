/*
	Aman Hogan-Bailey
	1001830469

*/

#include "mavalloc.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

// Decides whether a block is freed or not
enum TYPE
{
	FREE = 0, USED
};

struct Node {
   size_t size;
   enum TYPE type;
   void * arena;
   struct Node * next;
   struct Node * prev;
};

struct Node *alloc_list;
struct Node *previous_node;


void * arena;
enum ALGORITHM allocation_algorithm = FIRST_FIT;

/*
	Function allocates a specified amount of bytes into heap
*/
int mavalloc_init( size_t size, enum ALGORITHM algorithm )
{
	// Initializining the areana memory pool using the specified umber of bytes
	arena = malloc( ALIGN4( size ) );
  
	// Decides which algortithm will be used
	allocation_algorithm = algorithm;
	
	// Initializing the head of linked list that will
	// point to the arena and memory block
	alloc_list = ( struct Node * )malloc( sizeof( struct Node ));
	alloc_list -> arena = arena;
	alloc_list -> size  = ALIGN4(size);
	alloc_list -> type  = FREE;
	alloc_list -> next  = NULL;
	alloc_list -> prev  = NULL;
	previous_node  = alloc_list;
	
	return 0;
}

// Function free the earean memory pool after use, from memory
void mavalloc_destroy( )
{
	// Free the arena
	free(arena);
	
	// Free the linked list by traversing
	struct Node *temp;
	temp = alloc_list;
	while(temp != NULL)
	{
		free(temp);
		temp = temp->next;
	}
	
  return;
}

// Function allocates and manages space using the algorithms specified
void * mavalloc_alloc( size_t size )
{
	struct Node * node;

	// If the algorithm is not next fit, then set the node equal to head
	if( allocation_algorithm != NEXT_FIT )
		node = alloc_list;
	
	// If the algorithm is next fit, set node qual to the previous node
	else if ( allocation_algorithm == NEXT_FIT )
		node = previous_node;
  
	// An Error occured
	else
   {
		printf("ERROR: Unknown allocation algorithm!\n");
		exit(0);
   }
	size_t aligned_size = ALIGN4( size );
	
	// Perform First Fit algorithm on memory space
	if( allocation_algorithm == FIRST_FIT )
	{
		// While the node is not NULL .... 
		while( node )
		{
			// If the node is free and the node is greater than the size ....
			if( node -> size >= aligned_size  && node -> type == FREE )
			{
				// Find the leftover when inserting node into memeory
				int leftover_size = 0;
				node -> type  = USED;
				leftover_size = node -> size - aligned_size;
				node -> size =  aligned_size;
  
				// If the leftover space is greater than 0, the insert th enode into memory
				if( leftover_size > 0 )
				{
					struct Node * previous_next = node -> next;
					struct Node * leftover_node = ( struct Node * ) malloc ( sizeof( struct Node ));
  
					leftover_node -> arena = node -> arena + size;
					leftover_node -> type  = FREE;
					leftover_node -> size  = leftover_size;
					leftover_node -> next  = previous_next;
  
					node -> next = leftover_node;
				}
				
				previous_node = node;
				return ( void * ) node -> arena;
			}
			// Traverse List
			node = node -> next;
		}
	}

	// Perform NExt Fit algorithm
	if(allocation_algorithm == NEXT_FIT)
	{	
		// If the previous node was at the end of the list, set it to 
		// the begining of the list
		if(previous_node == NULL)
			previous_node = alloc_list;
			
		// Keep track of the node you started on,so you know where to break
		struct Node *break_node = previous_node;
		
		// COPY FIRST FIT ALGORITHM
		while( node )
		{
			if( node -> size >= aligned_size  && node -> type == FREE )
			{
				// Find the leftover when inserting node into memeory
				int leftover_size = 0;
				node -> type  = USED;
				leftover_size = node -> size - aligned_size;
				node -> size =  aligned_size;

				// If the leftover space is greater than 0, the insert th enode into memory
				if( leftover_size > 0 )
				{
					struct Node * previous_next = node -> next;
					struct Node * leftover_node = ( struct Node * ) malloc ( sizeof( struct Node ));
  
					leftover_node -> arena = node -> arena + size;
					leftover_node -> type  = FREE;
					leftover_node -> size  = leftover_size;
					leftover_node -> next  = previous_next;
  
					node -> next = leftover_node;
				}
				previous_node = node;
				return ( void * ) node -> arena;
			}
			
			// Traverse to the next node
			node = node -> next;
			
			// If node loops back to the node you startde at, break
			if(node == break_node)
			{
				break;
			}
			
			// Loop back to the start of the list
			else if(node == NULL)
			{
				node = alloc_list;
			}
		}
   }

	// Initializing Winning size and nodes
	int win_size = 0;
	struct Node * winning_node = NULL;
  
  // Perform Worst Fit Algortithm
  if(allocation_algorithm == WORST_FIT)
	{
		while( node )
		{
			if( node -> size >= aligned_size  && node -> type == FREE )
			{
				int leftover_size = 0;
				node -> type  = USED;
				leftover_size = node -> size - aligned_size;
				node -> size =  aligned_size;
  
				if( (leftover_size > 0) && (leftover_size > win_size ))
				{
					winning_node = node;
					win_size = node -> size - aligned_size;
					
					struct Node * previous_next = node -> next;
					struct Node * leftover_node = ( struct Node * ) malloc ( sizeof( struct Node ));
  
					leftover_node -> arena = node -> arena + size;
					leftover_node -> type  = FREE;
					leftover_node -> size  = leftover_size;
					leftover_node -> next  = previous_next;
  
					node -> next = leftover_node;
					
				}
				previous_node = node;
				if(winning_node != NULL)
		{
			return ( void * ) winning_node -> arena;
		}
		
		else
		{
			return NULL;
		}

				
			}
			
			node = node -> next;
		}
		
		
	}
	
	
	
	win_size = 1000000;
	winning_node = NULL;
	// Perofrm Best Fit Algorithm
	if(allocation_algorithm == BEST_FIT)
	{
		while( node )
		{
			if( node -> size >= aligned_size  && node -> type == FREE )
			{
				int leftover_size = 0;
				node -> type  = USED;
				leftover_size = node -> size - aligned_size;
				node -> size =  aligned_size;
  
				if( (leftover_size > 0) && (leftover_size < win_size ))
				{
					winning_node = node;
					win_size = node -> size - aligned_size;
					
					struct Node * previous_next = node -> next;
					struct Node * leftover_node = ( struct Node * ) malloc ( sizeof( struct Node ));
  
					leftover_node -> arena = node -> arena + size;
					leftover_node -> type  = FREE;
					leftover_node -> size  = leftover_size;
					leftover_node -> next  = previous_next;
  
					node -> next = leftover_node;
					
				}
				previous_node = node;
				if(winning_node != NULL)
		{
			return ( void * ) winning_node -> arena;
		}
		
		else
		{
			return NULL;
		}

				
			}
			
			node = node -> next;
		}
		
		
		
		

	}

  return NULL;
}

// Function frees the allocated memory space
void mavalloc_free( void * ptr )
{
	struct Node *temp;
	temp = alloc_list;
	
	// Traverse List and set the node type to free
	while(temp != NULL)
	{
		if(temp->arena == ptr)
		{
			temp->type = FREE;
		}
		
		temp = temp->next;
	}
	
	return;
}

// Function returns the size of the mavalloced space 
int mavalloc_size( )
{
	int number_of_nodes = 0;
	struct Node * ptr = alloc_list;

	// Traverse List
	while( ptr )
	{
		number_of_nodes ++;
		ptr = ptr -> next; 
	}

  return number_of_nodes;
}
