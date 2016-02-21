 #ifndef _POOL_
#define _POOL_ 

typedef struct node *link;
typedef struct check *Check;

struct check {
	int value;
	long int refe;
	long int refb;
	long int refc;
};
struct node {
	Check check;
	link next;
};

link Pool_NEW(Check, link);
int Pool_empty();
void Pool_insert(Check);
void Pool_get_FO();
int Pool_search(long int);

#endif /*termina o ficheiro*/
