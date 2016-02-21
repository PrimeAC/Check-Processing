/*
8888888b.                   d8b          888                  .d8888b.                        8888888        d8888 8888888888 8888888b.  
888   Y88b                  Y8P          888                 d88P  Y88b                         888         d88888 888        888  "Y88b 
888    888                               888                        888                         888        d88P888 888        888    888 
888   d88P 888d888 .d88b.  8888  .d88b.  888888 .d88b.            .d88P                         888       d88P 888 8888888    888    888 
8888888P"  888P"  d88""88b "888 d8P  Y8b 888   d88""88b       .od888P"                          888      d88P  888 888        888    888 
888        888    888  888  888 88888888 888   888  888      d88P"           888888      888888 888     d88P   888 888        888    888 
888        888    Y88..88P  888 Y8b.     Y88b. Y88..88P      888"                               888    d8888888888 888        888  .d88P 
888        888     "Y88P"   888  "Y8888   "Y888 "Y88P"       888888888                        8888888 d88P     888 8888888888 8888888P"  
                            888                                                                                                          
                           d88P                                                                                                          
                         888P"                                                                                                
Afonso Caetano 82539
Bruno Santos 82053
Diogo Barradas 81975
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Pool.h"
#include "avl.h"

/*Variaveis*/
link head=NULL, tail=NULL;
path root=NULL;
long int check_total=0, check_value=0;


/*Prototipos*/
void cheque();
void atualiza_cliente(long int,int,int,int);
void cria_cliente(long int, int, int);
void processaR();
void processa();
void sair();
void infocheque(long int);
void infocliente(path);
void info();
void Pool_delete();

/*Funcao principal*/
int main(){

	int value;
	long int ref, refe, refb, refc;

	char *c= (char*) malloc(sizeof(c));
	while(1){
		scanf("%s",c); /*le o comando inserido pelo utilizador*/
		while(1){
			
			if (strcmp(c,"cheque")==0) {
				scanf("%d",&value);
				scanf("%ld",&refe);
				scanf("%ld",&refb);
				scanf("%ld",&refc);
				
				if (search(root,refe)==NULL){
					cria_cliente(refe, value, 0);
				}
				else atualiza_cliente(refe, value, 0, 1);
				
				if(search(root,refb)==NULL){
					cria_cliente(refb, value, 1);
				}
				else atualiza_cliente(refb, value,1,1);
				cheque(value, refe, refb, refc);
				break;
				
			}
			if (strcmp(c,"processa")==0){
				processa();
				break;
				
			}
			if (strcmp(c,"processaR")==0){
				scanf("%ld",&refc);
				processaR(refc);
				break;
				
			}
			if (strcmp(c,"infocheque")==0){
				scanf("%ld",&refc);
				infocheque(refc);
				break;
				
				
			}
			if (strcmp(c,"infocliente")==0){
				scanf("%ld",&ref);
				infocliente(search(root,ref));
				break;
				
			}
			if (strcmp(c,"info")==0){
				info();
				break;
			}
			if (strcmp(c,"sair")==0){
				sair();
				return 0;
			}
			else {
				printf("ERRO: Comando [%s] desconhecido\n",c);
				break;
			}
		}
	 
	}
	free(c);
}

void cria_cliente(long int ref, int value, int eb){
	/* funcao que cria um cliente novo*/
		Client w=NULL;       
		w= (Client) malloc(sizeof(struct client)); /*aloca memoria para o novo cliente*/
		
		w->reference=ref;
		if (eb==1){ /*beneficiario*/
			w->nche=0;
			w->nchb=1;
			w->vche=0;
			w->vchb=value;
		}
		else {
			w->nche=1;
			w->nchb=0;
			w->vche=value;
			w->vchb=0;
		}
		root=insert(root,w); /*atualiza o valor da raiz da arvore*/
}
void cheque(int value, long int refe, long int refb, long int refc) {
	/* funcao que cria um novo cheque*/
	Check x;
	x= (Check) malloc(sizeof(struct check)); /*aloca memoria para um novo cheque*/
	
	x->value=value;
	x->refe=refe;
	x->refb=refb;
	x->refc=refc;
	Pool_insert(x); /*insere o novo cheque na lista de cheques*/
	check_total++; 
	check_value+=value;
			
	
	
}

void atualiza_cliente(long int ref, int value, int eb, int ad){
	path x= search(root, ref);
	if(ad==0){ /*estou a apagar um cheque*/
		if (eb==0){/*emissor*/
			x->client->nche--;
			x->client->vche-=value;
		}
		else {
			x->client->nchb--;
			x->client->vchb-=value;
		}

	}
	else {
		if (eb==0){/*emissor*/
			x->client->nche++;
			x->client->vche+=value;
		}
		else {
			x->client->nchb++;
			x->client->vchb+=value;
		}
	}
}
void processa(){
	/*processa o cheque mais antigo da lista de cheques*/
	long int refe, refb;
	path w;
	if (Pool_empty()!=0){
		refe=head->check->refe;
		refb=head->check->refb;
		atualiza_cliente(refe,head->check->value,0,0);
		atualiza_cliente(refb,head->check->value,1,0);
		check_value-=head->check->value;
		Pool_get_FO(); /*elimina o elemento mais antigo da lista de cheques*/
		w=search(root, refe);
		if(w!=NULL){
			if (w->client->nche<=0 && w->client->nchb<=0){ /*verifica se o cliente ja nao e beneficiario nem emissor em 
			 												nenhum outro cheque por processar*/
				root=deleteR(root,refe);
			}
		}
		w=search(root, refb);
		if(w!=NULL){
			if (w->client->nche<=0 && w->client->nchb<=0){
				root=deleteR(root,refb);
			}
		}
		check_total--;
		return;
	}
	printf("Nothing to process\n");
}

void processaR(long int refc){
	/*processa o cheque com a referencia introduzida*/
	link w, prev;
	long int refe, refb;
	path y;
	if (head==NULL){ 
		printf("Nothing to process\n");
		return;
	}
	else{
		for(w=head, prev=NULL; w!=NULL; prev = w, w = w->next){
			if((w->check->refc)==refc){ /*encontra o cheque na lista de cheques*/
				if(w==head){ 
					processa();
					return;
				}
				else {
					refe=w->check->refe;
					refb=w->check->refb;
					atualiza_cliente(refe,w->check->value,0,0);
					atualiza_cliente(refb,w->check->value,1,0);
					y=search(root, w->check->refe);
					if (y!=NULL){
						if (y->client->nche<=0 && y->client->nchb<=0){
							root=deleteR(root,w->check->refe);
						}
					}
					y=search(root, w->check->refb);
					if (y!=NULL){
						if (y->client->nche<=0 && y->client->nchb<=0){
							root=deleteR(root,w->check->refb);
						}
					}
					if (w->next==NULL){
						tail=prev; /*no caso do elemento a eliminar ser o mais recente da lista de cheques*/
					} 
					prev->next=w->next;	
					check_value-=w->check->value;
					free(w->check);				
					free(w);
					check_total--;
					return;
				}	
			}
		}
		printf("Cheque %ld does not exist\n",refc);
	}
}

void sair(){
	printf("%d %ld %ld\n", avl_count(root), check_total, check_value);
	if (root!=NULL){
		/*liberta a memoria referente a lista e a avl*/
		Pool_delete(); 
		avl_free(root);
	}

}

void infocheque(long int refc){
	/*imprime as informacoes referentes a um dado cheque*/
	link x;
	for(x=head;x!=NULL;x=x->next){ 
		if(refc==(x->check->refc)){
			printf("Cheque-info: %ld %d %ld --> %ld\n", refc, (x->check->value),(x->check->refe),(x->check->refb));
		}
	}

}

void infocliente(path h){
	/*imprime as informacoes referentes a um dado cliente*/
	printf("Cliente-info: %ld %d %d %d %d\n", h->client->reference, h->client->nche, h->client->vche, h->client->nchb, h->client->vchb);
}

void info(){
	/*imprime por ordem crescente de referencia a informacao sobre os clientes*/
	if (root==NULL) printf("No active clients\n");
	traverse(root);
}

void Pool_delete(){
	/*liberta a memoria da lista de cheques na sua totalidade*/
	link w;
	while (head==NULL){
		w=head->next;
		free(head->check);
		free(head);
		if (head!=NULL)
			head=w;
	}
}




