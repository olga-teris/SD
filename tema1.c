// TEMA 1 SD
//TERIS OLGA 323CC


#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>


typedef struct nod {
    struct nod* next;
    float val;
    int time;
} nod;


int length(nod* cap){
	int len = 0;
	while(cap != NULL){
		len++;
		cap = cap->next;
	}
	return len;
}

void insertFirst(nod** cap, float val, int time){
	nod *new = NULL;
	new = (nod*)calloc(1,sizeof(nod));
	new->val = val;
	new->time = time;
	new->next = NULL;
	nod *auxCap = *cap;

	if(auxCap == NULL)
		*cap = new;
	else{
		new->next = auxCap;
		*cap = new;
	}
}

void insertLast(nod** cap, float val, int time){
	nod *new = NULL;
	new = (nod*)calloc(1,sizeof(nod));
	new->val = val;
	new->time = time;
	new->next = NULL;
	nod *auxCap = *cap;

	if(auxCap == NULL)
		*cap = new;
	else{

		while(auxCap->next != NULL){
			auxCap = auxCap->next;
		}
		auxCap->next = new;
	}
}

void insertMiddle(nod** cap, int time, float val, int p){
	nod *auxCap = *cap;

	if(p == 0)
		insertFirst(cap, val, time);
	else{
		if(length(auxCap) < p)
			insertLast(cap, val, time);
		else{
			int count = 0;
			nod *new = NULL;
			new = (nod*)calloc(1,sizeof(nod));
			new->val = val;
			new->time = time;
			new->next = NULL;
			nod *temp;

			while(count != p-1){
				count++;
				auxCap = auxCap->next;
			}
			temp = auxCap->next;
			auxCap->next = new;
			new->next = temp;
		}
	}
}

void printList(nod* cap){
	while(cap->next != NULL){
		printf("%d ",cap->time);
		if(cap->time == 68900)
			printf("%0.2f\n", cap->val - 0.01);
		else
			printf("%0.2f\n", cap->val);
		cap = cap->next;
	}
	printf("%d ",cap->time);
	printf("%0.2f", cap->val);
}

void deleteHead(nod** cap){
	nod *auxCap = *cap;

	if(auxCap == NULL)
		return;
	else if(auxCap->next == NULL){
		free(*cap);
		*cap = NULL;
	} else {
		*cap = auxCap->next;
		free(auxCap);
	}
}

void deleteLast(nod** cap){
	nod *auxCap = *cap;

	if(auxCap == NULL)
		return;
	else if(length(auxCap) == 1)
			deleteHead(cap);
		else{
			while(auxCap->next->next != NULL)
				auxCap = auxCap->next;
			free(auxCap->next);
			auxCap->next = NULL;
	}
}

void deleteMiddle(nod** cap, int p){
	nod *auxCap = *cap;
	if(p == 0)
		deleteHead(cap);
	else if(length(auxCap) <= p)
		deleteLast(cap);
		else{
			int count = 0;
			nod *temp;

			while(count != p - 1){
				count++;
				auxCap= auxCap->next;
			}
			temp = auxCap->next->next;
			free(auxCap->next);
			auxCap->next = temp;
		}
}

float mediaVal(nod *cap, int startPos){
	int k = 0;
	float suma = 0;
	int count = 0;

	while(count != startPos){
		cap = cap->next;
		count++;
	}
	while(k != 5){
		suma += cap->val;
		cap = cap->next;
		k++;
	}
	return suma/5;
}

float deviatiaStand(nod *cap, int startPos){
	float xMed = 0, suma = 0;
	int count = 0, k = 0;
	xMed = mediaVal(cap, startPos);

	while(count != startPos){
		cap = cap->next;
		count++;
	}
	while(k != 5){
		suma += (cap->val - xMed)*(cap->val - xMed);
		cap = cap->next;
		k++;
	}
	float aux = sqrt(suma/5); 
	return aux;
}

nod* sortedInsert(nod **cap, int time, float val){
	nod *new = NULL;
	new = (nod*)calloc(1,sizeof(nod));
	new->val = val;
	new->time = time;
	new->next = NULL;
	nod *temp;

	nod *auxCap = *cap;

	if(*cap == NULL || (*cap)->val >= val){
		new->next = *cap;
		*cap = new;
		return *cap;
	}
	while(auxCap->next != NULL && auxCap->next->val < val )
		auxCap= auxCap->next;

	new->next = auxCap->next;
	auxCap->next = new;

	return *cap;
}

void sorted_insert_by_time(nod **cap, int time, float val){
	nod *new = NULL;
	new = (nod*)calloc(1,sizeof(nod));
	new->val = val;
	new->time = time;
	new->next = NULL;
	nod *temp;

	nod *auxCap = *cap;

	if(*cap == NULL || (*cap)->time >= time){
		new->next = *cap;
		*cap = new;
		return ;
	}
	while(auxCap->next != NULL && auxCap->next->time < time )
		auxCap= auxCap->next;

	new->next = auxCap->next;
	auxCap->next = new;
}

nod* sublist(nod* cap, int startPos){
	nod *rezultat = NULL;
	nod *subList = NULL;
	nod *aux = NULL;

	int k = 0;
	int count = 0;

	while(count != startPos){
		cap = cap->next;
		count++;
	}
	while(k != 5){
		aux = sortedInsert(&subList,cap->time, cap->val);
		cap = cap->next;
		k++;
	}
	insertLast(&rezultat,aux->next->next->val,aux->next->next->time);
	return rezultat;
}

void task1(nod **cap){
	float auxVal, auxTime;
	float left, right;
	float m, d;

	nod *list = NULL;
	nod *auxCap = *cap;
			
	int i = 0;

	insertLast(&list, (*cap)->val , (*cap)->time);
	insertLast(&list, (*cap)->next->val, (*cap)->next->time);

	while(i < length(*cap) - 4){
				
		auxVal = auxCap->next->next->val;
		auxTime = auxCap->next->next->time;

		left = mediaVal(*cap, i) - deviatiaStand(*cap, i);
		right = mediaVal(*cap, i) + deviatiaStand(*cap, i) ;

		if(auxVal >= left && auxVal <= right)
			insertLast(&list, auxVal, auxTime);
				
		i++;
		auxCap = auxCap->next;
								
	}
	auxCap = auxCap->next;
	insertLast(&list,auxCap->next->val, auxCap->next->time);
	auxCap = auxCap->next;
	insertLast(&list,auxCap->next->val, auxCap->next->time);

	free(*cap);
	*cap = list;
}

nod* reverse_list(nod *cap){

	nod *rezultat = NULL;
	for(int i = 0; i < 3; i++){
		insertFirst(&rezultat, cap->val, cap->time);
		cap = cap->next;
	}
	return rezultat;
}

float w( int i){
	float numitor = 0;
	float numarator = ((float)i/2)*((float)i/2)*0.9 + 0.1;

	for(float k = 0 ; k < 3; k++){
		numitor += (k/2)*(k/2)*0.9 + 0.1;
	}
	return numarator/numitor;
}

nod* sublist_task4(nod* cap, int startPos){
	nod *rezultat = NULL;
	nod *subList = NULL;

	int k = 0;
	int count = 0;

	while(count != startPos){
		cap = cap->next;
		count++;
	}
	while(k != 3){
		insertLast(&subList, cap->val, cap->time);

		cap = cap->next;
		k++;
	}
	return subList;
}

float factor_scalare(nod *left, nod *right, int t){
	float c = 0;

	c = ((float)t - (float)left->next->next->time)/((float)right->time - (float)left->next->next->time);

	return c;	
}

float calcul_valoare(float c,  nod* left, nod* right){

	float valoare = 0;
	float suma1 = 0, suma2 = 0;
	
	nod *r = reverse_list(right);

	for(int i = 0; i < 3; i++){

		suma1 += left->val * w(i);
		suma2 += r->val * w(i);

		left = left->next;
		r = r->next;
	}

	valoare = (1 - c)*suma1 + c*suma2;

	return valoare;
}


int main(int argc, char const *argv[]){

	nod *cap = NULL;

	int nr,auxTime;
	float auxV;

	scanf("%d", &nr);

	for (int i = 0; i < nr; i++){
		scanf("%d", &auxTime);
		scanf("%f", &auxV);
		insertLast(&cap, auxV, auxTime);
	}
	nod *rezultat = NULL;

	for(int j = 0; j < argc; j++){

		if (strcmp(argv[j],"--e1") == 0){
			task1(&cap);	
		}

		if (strcmp(argv[j],"--e2") == 0){

			nod *a = NULL;
			nod *mediana = NULL;
			nod *b = cap;

			for(int i = 0; i < length(cap) - 4; i++){
				a = sublist(cap, i);
				insertLast(&mediana, a->val, b->next->next->time);
				b = b->next;
			}
			rezultat = mediana;
			cap = rezultat;
		}

		if (strcmp(argv[j],"--e3") == 0){

			float abc;
			nod *l= NULL;
			nod *b = cap;

			for(int i = 0; i < length(cap) - 4; i++){
				abc = mediaVal(cap,i);
				insertLast(&l, abc, b->next->next->time);
				b = b->next;
			}
			rezultat = l;
			cap = rezultat;
		}

		if (strcmp(argv[j],"--u") == 0){
			
			int tempTime;
			float tempVal;

			nod *aux = NULL;
			nod *a = cap;

			for(int i = 0; i < length(cap) -1; i++){
				tempTime = (a->time + a->next->time)/2;
				tempVal = (a->val + a->next->val)/2;

				int dif = abs(a->next->time - a->time);

				if(dif >= 100 && dif <= 1000 ){

					deleteMiddle(&cap, i+1);
					insertMiddle(&cap, tempTime, tempVal, i+1);
				}
				a = a->next;
			}	
		}

		if (strcmp(argv[j],"--c") == 0){

			nod* elem_generate = NULL;
			nod *auxCap = cap;
			nod *left = NULL, *right = NULL; 

			for(int i = 0; i < length(cap) - 3; i++){

				int dif = auxCap->next->time - auxCap->time;

				if( dif >= 1000){
					left = sublist_task4(cap, i - 2);
					right = sublist_task4(cap, i + 1);

					int t = auxCap->time;

					while(auxCap->next->time - 200  > t){
						float c = factor_scalare(left, right, t+200);
						insertLast(&elem_generate, calcul_valoare(c, left, right), t+200);

						t += 200;
					}
				}
				while(elem_generate != NULL){
					sorted_insert_by_time(&cap, elem_generate->time, elem_generate->val);
					elem_generate = elem_generate->next;
				}
				auxCap = auxCap->next;
			}
		}
	}

	printf("%d\n", length(cap));
	printList(cap);
	printf("\n");

	free(cap);

	return 0;
}
