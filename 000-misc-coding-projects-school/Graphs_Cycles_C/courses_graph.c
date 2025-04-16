#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MAX_FILENAME 1000
#define MAX_CHAR 31


//No special Text//

//Initializing Type Definitions
typedef struct edge_classif
{
	int* array_of_edges;
	int size;
	int numb_edges;
}color;

typedef struct stack_struct
{
	int* items;
	int top;
	int capacity;
}Stack;

typedef struct struct_graph *graphPT;
struct struct_graph
{
	int nodes;
	int ** E;
};

int find_node_total(char* filename, char*** node_strs);
int** alloc2d(int R, int C);
graphPT newGraph(int nodes);
void dealloc_graph(graphPT g);
void addEdge(graphPT* g, int v1, int v2);
void Read(char* filename, graphPT* g, char** node_str);
void print_graph(graphPT graph);
void push(Stack* stack, int Item);
int pops(Stack* stack);
void free_matrix(int** arr, int N);
int locate_ind(char** node_strs, char* token, int N);
void free_words(char** letters, int N);
void Depth_First_Search(graphPT* g, Stack* s, color* black, color* white, color* grey,  int** d, int** f, int* E, int* t, int current, int* cycle);

int main()
{
	//Initializing Colors//
	color white;
	color grey;
	color black;

	//Initializing Graphs and Stacks//
	graphPT graph;
	Stack stack;
	char** str_nodes;
	char filename[MAX_CHAR];

	//Formatting//
	printf("This program will read, from a file, a list of courses and their prerequisites and will print the list in which to take cousres.\n");
	printf("Enter filename: ");
	scanf("%s", filename);
	
	int node_total = find_node_total(filename, &str_nodes) -1;
	
	//If there are negative nodes or no nodes, exit...
	if(node_total == 0 || node_total == -1 || node_total == -2 || node_total == -3 || node_total == -4)
	{
		printf("\nFailed to read from file. Program will terminate.\n"); 
		exit(0); 
	}

	//Initializing Stacks//
	stack.capacity = node_total + 1;
	stack.items = (int*) malloc(sizeof(int) * stack.capacity);
	stack.top = -1;

	//Allocating Space to the Colors//
	black.array_of_edges = (int*) malloc(sizeof(int) * node_total);
	black.numb_edges = node_total;
	black.size = node_total;
	grey.array_of_edges = (int*) malloc(sizeof(int) * node_total);
	grey.size = node_total;
	grey.numb_edges = node_total;
	white.array_of_edges = (int*) malloc(sizeof(int) * node_total);
	white.numb_edges = node_total;
	white.size = node_total;

	//Formatting//
	printf("Number of vertices in built graph: N = %d\n", node_total);
	printf("Vertex - coursename correspondence\n");
	for(int i = 0; i < node_total; i++)
	{
		printf("%d - %s\n", i, str_nodes[i]);
	}
	
	//Create and Print Graph Using Data from File//
	graph = newGraph(node_total);
	Read(filename, &graph, str_nodes);
	print_graph(graph);


	for (int i = 0; i < node_total; i++)
	{
		white.array_of_edges[i] = 1;
		grey.array_of_edges[i] = 0;
		black.array_of_edges[i] = 0;
	}
	
	//Initializing Variables//
	int* D = (int*) calloc(node_total, sizeof(int));
	int* F = (int*) calloc(node_total, sizeof(int));
	
	//Initializing the Time And Cycle Varibales//
	int t = 0;
	int c = 0;

	//Perform DFS while undiscovered AND less than node total...
	for(int i = 0; i < node_total && white.numb_edges > 0; i++)
	{	if(white.array_of_edges[i] == 1)
		{
			Depth_First_Search(&graph, &stack, &black, &white, &grey, &D, &F, graph->E[i], &t, i, &c);
		}
	}
	printf("\n");
	
	//If the Cycle is not 0, there wsa a cycle...
	if(c)
	{
		printf("There was at least one cycle. There is no possible ordering of the courses.\n");
	}
	
	//There was no Cycle//
	else
	{
		printf("Order in which to take courses:\n");
		for(int i = 0; i < node_total; i++)
		{
			int pop = pops(&stack);
			printf("%d. - %s (corresponds to graph vertex %d)\n", i+1, str_nodes[pop], pop);
		}
	}

	//Free All Variables, Edges, and Memory//
	free(stack.items);
	free(black.array_of_edges);
	free(grey.array_of_edges);
	free(white.array_of_edges);
	free(D);
	free(F);
	
	dealloc_graph(graph);
	free_words(str_nodes, node_total+1);
	printf("\n");

	return 0;
}

//////////////HELPER FUNCTIONS///////////////////////////////
//Creates new Matrix and Allocates space for it//
int** alloc2d(int R, int C)
{
	int** E = (int**) malloc(sizeof(int*) * R);
	for(int i = 0; i < R; i++)
	{
		E[i] = (int*) malloc(sizeof(int) * C);
	}
	return E;
}

//Function Creates a New Edge//
void addEdge(graphPT* g, int v1, int v2)
{
	(*g)->E[v1][v2] = 1;
}

//Function Creates a New Graph//
graphPT newGraph(int N)
{
	graphPT res = malloc(sizeof(*res));
	res->nodes = N;
	res->E = alloc2d(N, N);

	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			res->E[i][j] =0;
		}
	}
	return res;
}

//Function Frees the Memory of Graph//
void dealloc_graph(graphPT g)
{
	if(g == NULL)
	{
		return;
	} 
	free_matrix(g->E, g->nodes);
	free(g);
}

//Function Prints Graph / Adjacency Matrix//
void print_graph(graphPT graph)
{
	//Initialising Variables//
	int N = graph->nodes;
	printf("\n");
	printf("Adjacency matrix: \n");

	printf("   |");
	for (int i = 0; i < N; i++)
	{
		printf("%3d", i);
	}

	printf("\n");
	for(int i = 0; i < ((N)*3)+4; i++)
	{
		printf("-");
	}

	printf("\n");
	for(int i = 0; i < N; i++)
	{
		printf("%3d|", i);
		for(int j = 0; j < N; j++)
		{
			printf("%3d", (graph->E)[i][j] );
		}
		printf("\n");
	}
}

//Function Pushes the Stack//
void push(Stack* stack, int Item)
{
	//If the Stack is Full
	if (stack->top == (stack->capacity - 1) )
	{
		return;
	}
	//Increment Top of Stack
	stack->top+=1;
	stack->items[stack->top] = Item;
}

//Function Pops the Stack//
int pops(Stack* stack)
{
	int N;
	//If Stack is Empty
	if(stack->top == -1)
	{
		return -1;
	}
	//Subtrract the Top//
	else
	{
		N = stack->items[stack->top];
		stack->top= stack->top - 1;
		return N;
	}
}

//Function Frees memory allocated to Matrix//
void free_matrix(int** arr, int N)
{
	for(int i = 0; i < N; i++)
	{
		free(arr[i]);
	}
	free(arr);
}

//Function Finds the Index//
int locate_ind(char** node_strs, char* token, int N)
{

	//If Index is Found, Return the Index ....
	for(int index = 0; index < N; index++)
	{
		if( strcmp(node_strs[index], token) == 0 )
		{
			return index;
		}
	}
	return -1;
}

//Function Reads File//
void Read(char* filename, graphPT* g, char** node_str)
{
	//Initializing Variables//
	FILE* fp = fopen(filename, "r");
	int N = (*g)->nodes;
	char fileline[101];
	char *token;

	//While not End of File...
	for (int v2 = 0; !feof(fp); v2++)
	{
		fgets(fileline, sizeof(fileline), fp);
		token = strtok(fileline, " \n");
		while(token != NULL)
		{
			if( strcmp(node_str[v2], token) != 0 )
			{
				int v1 = locate_ind(node_str, token, N);
				addEdge(&(*g), v1, v2);
			}
			token = strtok(NULL, " \n");
		}
	}
	fclose(fp);
}

//Frees the memory allocated to words// 
void free_words(char** letters, int N)
{
	for(int i = 0; i < N; i++)
	{
		free(letters[i]);
	}
	free(letters);
}

int find_node_total(char* filename, char*** node_strs)
{
	//Initializing Variables//
	int node_total = 0;
	char* token;
	char fileline[101];
	
	//File Handling//
	FILE* fp = fopen(filename, "r");
	if(fp == NULL)
	{
		printf("Could not open file %s. Exit\n", filename); 
		return -1; 
	}

	//While the File is not at thee end, Find the number of Nodes//
	while (!feof(fp))
	{
		fgets(fileline, 101, fp);
		node_total++; 
	}
	
	*node_strs = (char**) malloc(sizeof(char*) * node_total);
	fseek(fp, 0 , SEEK_SET);
	for(int i = 0; i < node_total; i++)
	{
		(*node_strs)[i] = (char*) malloc(sizeof(char) * MAX_CHAR);
		strcpy( (*node_strs)[i], "" );
	}

	//Store the First Letters of the nodes//
	int index = 0;
	while(!feof(fp))
	{
		fgets(fileline, sizeof(fileline) - 1, fp);
		token = strtok(fileline, " \n");
		strcpy( (*node_strs)[index], token );
		index++;
	}
	fclose(fp);
	
	return node_total;
}

//Initiating Depth First Search//
void Depth_First_Search(graphPT* g, Stack* s, color* black, color* white, color* grey,  int** d, int** f, int* E, int* t, int c, int* cycle)
{

	//Initializing Varibales//
	int n = s->capacity - 1;
	int neighbor [n];
	int neighbor_size = 0;

	//Updateing T and D//
	*t = *t + 1;
	(*d)[c] = *t;

	//Updating Grey and White//
	grey->array_of_edges[c] = 1;
	white->array_of_edges[c] = 0;
	white->numb_edges = white->numb_edges - 1;

	//Find the size and Neighboors//
	for(int j = 0; j < n; j++)
	{
		if ( (*g)->E[c][j] == 1)
		{
			neighbor[neighbor_size] = j;
			
			neighbor_size += 1;
		}
	}
	
	//Assign a Grpah Classification to Eedges//
	for (int k = 0; k < neighbor_size; k++)
	{
		int next = neighbor[k];
		if (black->numb_edges > 0 && (black->array_of_edges[next] == 1))
		{
			continue;
		}

		if (grey->numb_edges > 0 && (grey->array_of_edges[next] == 1) )
		{
			*cycle = 1;
		}
		
		if(white->numb_edges > 0 && (white->array_of_edges[next] == 1))
		{
			Depth_First_Search(g,s,black,white,grey,d,f,(*g)->E[next],t,next,cycle);
		}
	}

	black->array_of_edges[c] = 1;
	grey->array_of_edges[c] = 0;
	
	*t = *t + 1;
	(*f)[c] = *t;


	//Push The Stack//
	push(s, c);
}
