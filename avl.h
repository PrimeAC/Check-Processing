#ifndef _AVL_
#define _AVL_

#include "Pool.h"
typedef struct node1 *path;
typedef struct client *Client; 

struct client {
	long int reference;
	int nche;
	int vche;
	int nchb;
	int vchb;
};
struct node1{
	Client client;
	path l;
	path r;
	int height;
};



path avl_NEW(Client ,path ,path);
int avl_count(path);
path search(path, long);
int height(path);
path insert(path ,Client );
path deleteR(path,long int);/**/
path max(path);/**/
path freeR(path);/**/
void avl_free(path);/**/
path rotL(path);
path rotR(path);
path rotLR(path);
path rotRL(path);
int Balance(path);
path AVLbalance(path);  
void sort(path ,void (*visit)(Client));
void avl_sort ( path,void (*visit)(Client));
void traverse(path);/**/
void visit(Client);/**/



#endif
