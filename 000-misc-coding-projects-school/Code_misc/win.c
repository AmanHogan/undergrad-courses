#include <stdio.h>
#include <stdlib.h>

struct node
{
	int data;
	struct node *next;
};

void create(struct node *curr);
void delete(struct node *curr);
void print(struct node *curr);


int main()
{
	int choice = 0;
	
	struct node *head = (struct node *)malloc(sizeof(struct node));
	head->next = NULL;
	head->data = 0;
	
	struct node *temp;
	temp = head;
	
	while(choice !=3 )
	{
		printf("Enter 0 to add to linked list\n");
		printf("Enter 1 to delete linked list\n");
		printf("Enter 2 to print  linked list\n");
		printf("Enter 3 to exit...\n");


		scanf("%d", &choice);
	
		switch(choice)
		{
			case 0:
				add(temp);
				break;
			case 1:
				delete(temp);
				break;
			case 2:
				print(temp);
				break;
			defalut
				printf("Invalid Choice\n");
		}
	}
	
	return 0;

}



void create(struct node *curr)
{
	struct node *temp, *new;
	
	new = (struct node *)malloc(sizeof(struct node));
	new->next = NULL;
	new->data = 0;
	
	
	printf("\nWhat data do you want in the node: ");
	scanf("%d", &new->data);
	
	temp->next = new;
	temp = next;
	temp->next = NULL;
	
}

void delete(struct node *curr)
{
	struct node *temp;
	temp = curr;
	
	while(temp->next != NULL)
	{
		temp = temp->next;
	}
	
	free(temp);
}


void print(struct node *curr)
{
	struct node *temp;
	temp = curr;
	
	while(temp != NULL)
	{
		printf("\nData: %d", temp->data);
		temp = temp->next;		
	}
}

