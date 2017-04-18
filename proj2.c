/*
 ============================================================================
 Name        : Proj2Schulte.c
 Author      : Greg Climer
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
typedef struct {
	char value[1024];
	int count;
	struct Leaf *left;
	struct Leaf *right;
}Leaf;


void format(char *);
void newLeaf(char *, Leaf **);
void insert(Leaf**, Leaf**);
void printTree(Leaf*, FILE *);
void killTree(Leaf*);


void newLeaf(char * word, Leaf ** root){
	Leaf *compare = *root;
	Leaf *node = (Leaf*) malloc(sizeof(Leaf));
	strcpy((node -> value), word);
	node->left = NULL;
	node->right = NULL;
	node->count = 1;

	if (compare == 0)
		*root = node;
	else
		insert(&compare, &node);
}

void insert(Leaf ** compare, Leaf ** newNode){
	if (*compare == NULL){
		*compare = *newNode;
		return;
	}
	int k = strcmp((*compare)->value, (*newNode)->value);
	if (k == 0){
		(*compare)->count++;
		free(*newNode);
	}
	else if (k > 0){
		insert(&(*compare)->left, newNode);
	}
	else if (k < 0){
		insert(&(*compare)->right, newNode);
	}
}

void printTree(Leaf * node, FILE * out_file){
	if (node){
		printTree(node->left, out_file);
		fprintf(out_file, "%-17s: %i\n", node->value, node->count);
		printTree(node->right, out_file);
	}
}

void killTree(Leaf * node){
	if (node !=0){
		killTree(node->left);
		killTree(node->right);
		free(node);
	}
}

void format(char * word){
	char * scan = word, * write = word;
	if (ispunct((unsigned char)*scan)){
		scan++;
		while (*scan){
			*write++ = tolower((unsigned char)*scan);
			scan++;
		}
		*write = '\0';
	}
	else{
		while (*scan){
			*write++ = tolower((unsigned char)*scan);
			scan++;
		}
	}
	write--;
	if (((unsigned char)*write < 'a') || ((unsigned char)*write > 'z')){
		*write = '\0';
		write--;
	}
}


int main(int argc, char*argv[]) {
	FILE *ptr_file;
	FILE *out_file;
	out_file =fopen(argv[2], "w");
	ptr_file =fopen(argv[1], "r");
	Leaf *root = 0;

	char buff[1024];

	while (fscanf(ptr_file, " %1023s", buff) == 1){
		format(buff);
		newLeaf(buff, &root);
	}
	printTree(root, out_file);
	killTree(root);
	fclose (out_file);
	fclose (ptr_file);
	return EXIT_SUCCESS;
}


