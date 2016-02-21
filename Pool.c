#include <stdio.h>
#include <stdlib.h>

#include "Pool.h" 

extern link head, tail;


int Pool_empty(){
	/*verifica se a lista de cheques se encontra vazia*/
	if (head==NULL){
		return 0;
	}
	else return 1;
	
}

link Pool_NEW(Check check, link next){
	/* aloca memoria para um novo elemento da lista de cheques*/
	link x;
	x=(link) malloc(sizeof(struct node));

	x->check=check;
	x->next=next;
	return x;

}
void Pool_insert(Check check){
	/* inseres um novo cheque na lista de cheques*/
	if(head==NULL){
		head=(tail=Pool_NEW(check, head));
		return;
	}
	else{
		tail->next=Pool_NEW(check, NULL);
		tail=tail->next;
	}
}

void Pool_get_FO(){
	/* remove o elemento mais antigo da lista*/
	if (Pool_empty()!=0){
		link x=head->next;
		free(head);
		head=x;

	}
	else{
		printf("Nothing to process\n");
		
	}
}

int Pool_search(long int ref){
	/*procura um dado cheque atraves da referencia de um emissor ou beneficiario*/
	 link t;
	 int cnt=0;
	 for(t = head; t != NULL; t = t->next){
	 	if((t->check->refe)==ref || (t->check->refb)==ref){
	 		cnt++;
	 	}
	 }
	 if(cnt>=2) return 0;
	 else return -1;
} 