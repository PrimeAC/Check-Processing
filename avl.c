#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "avl.h"

extern path root;

path avl_NEW(Client client, path l, path r){
/*aloca espaco para o novo elemento da avl*/

	path x =(path) malloc(sizeof(struct node1));
	x->client = client;
	x->l=l;
	x->r=r;
	x->height=0;
	return x;	
}

int avl_count(path h){
/*conta os elementos da avl*/
	if (h==NULL) return 0;
 	else return avl_count(h->r)+avl_count(h->l)+1;
}

int height(path h)
{
	if (h==NULL) 
		return -1;
	return h->height;
}



path freeR(path h)
{
	if (h==NULL)
		return h;
	h->l=freeR(h->l);
	h->r=freeR(h->r);
	return deleteR(h,(h->client->reference));
}
void avl_free(path h){
	/*liberta a memoria da arvore*/
	h=freeR(h);
}

/*rotacoes para o balanco da arvore binaria*/
path rotL(path h)
{
	int height_left, height_right;
	path x = h->r;
	h->r = x->l;
	x->l = h;

	height_left = height(h->l); height_right = height(h->r);
	h->height = height_left > height_right ? height_left + 1 :
	height_right + 1;
	height_left = height(x->l); height_right = height(x->r);
	x->height = height_left > height_right ? height_left + 1 :
	height_right + 1;
	return x;
}

path rotR(path h)
{
	int height_left, height_right;
	path x = h->l;
	h->l = x->r;
	x->r = h;

	height_left = height(h->l); height_right = height(h->r);
	h->height = height_left > height_right ? height_left + 1 :
	height_right + 1;
	height_left = height(x->l); height_right = height(x->r);
	x->height = height_left > height_right ? height_left + 1 :
	height_right + 1;
	return x;
}

path rotLR(path h) {
 /*rotação dupla esquerda direita*/

	if (h==NULL) 
		return h;
	h->l=rotL(h->l);
	return rotR(h);
}


path rotRL(path h) {
/*rotação dupla direita esquerda*/
	if (h==NULL) 
		return h;
	h->r=rotR(h->r);
	return rotL(h);
}

int Balance(path h) {
/*Balance factor*/
	if(h==NULL) 
		return 0;
	return height(h->l)-height(h->r);
}

path AVLbalance(path h) {
	/*faz as rotacoes necessarias da arvore para atingir o balanco da mesma*/
	int balanceFactor;
	if (h==NULL) 
		return h;
	balanceFactor= Balance(h);
	if(balanceFactor>1) {
		if (Balance(h->l)>0) 
			h=rotR(h);
		else
			h=rotLR(h);
	}
	else if(balanceFactor<-1){
		if (Balance(h->r)<0) 
			h=rotL(h);
		else
			h=rotRL(h);
	}
	else{
		int height_left = height(h->l); int height_right = height(h->r);
		h->height = height_left > height_right ? height_left + 1 :
		height_right + 1;
		}

	return h;
}


path search(path h, long ref){
	/*procura na avl o cliente com a referencia introduzida*/

	if (h==NULL)
		return NULL;
	if (ref==(h->client->reference))
		return h; 			
	if (ref<(h->client->reference))
		return search(h->l, ref);
	else
		return search(h->r, ref);
}


path insert(path h,Client client){
	/*insere na avl a estrutura cliente*/

	Client v = client;
	if (h == NULL) {
		return avl_NEW(client, NULL, NULL);
	}
	if ((v->reference)<(h->client->reference)) {
		h->l = insert(h->l,client);
	}
	else {
		h->r = insert(h->r,client);
		}	
	h=AVLbalance(h);
	return h;
}

void sort(path h,void (*visit)(Client))
{
	if (h == NULL)
		return;
	sort(h->l,visit);
	visit(h->client);
	sort (h->r,visit);		
}

void avl_sort (path root,void (*visit)(Client)){
	/*ordena por ordem crescente as referencias da avl*/

	sort(root,visit);
}


path max(path h) {
	if (h==NULL || h->r==NULL) 
		return h;
	else return max(h->r);
}

path deleteR(path h, long int k){
	/*elimina o elemento com a referencia introduzida na avl*/

	if (h==NULL) 
		return h;
	else if (k<(h->client->reference)) 
		h->l=deleteR(h->l,k); /*chama recursivamente para o filho esquerdo*/
	else if ((h->client->reference)< k) 
		h->r=deleteR(h->r,k) ; /*chama recursivamente para o filho esquerdo*/
	else {
		if (h->l !=NULL && h->r !=NULL){ /*testa se atingimos as folhas da avl*/
			path aux=max(h->l);
			{Client x; x=h->client; h->client=aux->client; aux->client=x; }
			h->l= deleteR(h->l, (aux->client->reference));
			}
		else { 
			path aux=h; 
			if ( h->l == NULL && h->r == NULL ) 
				h=NULL;	
			else if (h->l==NULL) 
				h=h->r;	
			else 
				h=h->l;	
			free(aux->client);
			free(aux);
			}
		}
	h=AVLbalance(h); /* garante o balanco da arvore apos ser eliminado o elemento*/
	return h;
}

void traverse(path h){
	/* percorre a avl e posteriormente imprime os elementos da estrutura */

	if (h == NULL){
		return;}
	traverse(h->l);
	visit(h->client);
	traverse(h->r);
}


void visit(Client i)
{
	printf("*%ld %d %d %d %d\n", i->reference, i->nche, i->vche, i->nchb, i->vchb);
}