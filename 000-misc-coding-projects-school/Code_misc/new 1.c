#include <stdio.h>
#include <stdlib.h>


struct node
{
   int data;
	struct node * next;
};


void create_list(struct node *head, int N);
void print_list(struct node *head, int N);


int main()
{
	int N = 0;
	struct node *head;

	
	printf("How many nodes do you want? ");
	scanf("%d", &N);

	
	create_list(head, N);
	print_list(head, N);
	
	
	
	
}
void create_list(struct node *head, int N)
{
    
	struct node *temp, *new;
	temp = head;

	int i = 0;
	
		while(i < N)
		{
			new = (struct node* )malloc(sizeof(struct node));
		
			
	
			
			printf("\nEnter the data for this node: ");
			scanf("%d", &new->data);
			new->next = NULL;
			
				
			temp->next = new;
			temp = temp->next;
			
			i++;
		}
		
}
void print_list(struct node *head, int N)
{
    struct node *temp;
    temp = head;
    

    
    while(temp != NULL)
    {
        
        printf("%d\n", temp->data);
        temp = temp->next;
    }
    
    
    
    
    
    
}



