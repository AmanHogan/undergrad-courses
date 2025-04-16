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
	struct node *head = (struct node*)malloc(sizeof(struct node));
	head->next = NULL;
	head->data = 0;

	
	printf("How many nodes do you want? ");
	scanf("%d", &N);

	
	create_list(head, N);
	print_list(head, N);
	
	
	
	
}
void create_list(struct node *head, int N)
{
    
	struct node *temp, *new;
	
	
	printf("\nEnter the data for this node: ");
	scanf("%d", &head->data);
	
	temp = head;

	int i = 1;
	
		while(i < N)
		{
			new = (struct node* )malloc(sizeof(struct node));
			int data = 0;
			
	
			
			printf("\nEnter the data for this node: ");
			scanf("%d", &data);
			new->data = data;
			new->next = NULL;
			
				
			temp->next = new;
			temp = temp->next;
			
			
			i++;
		}
		
}
void print_list(struct node *head, int N)
{
    struct node *temp = NULL;
    temp = head;
    
int i = 0;
    
    while(temp != NULL)
    {
        printf("\nNode #%d has data: %d\n", i, temp->data);
        temp = temp->next;
		  i++;
    }
    
    
    
    
    
    
}



