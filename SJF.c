#include<stdio.h>
#include<stdlib.h>

typedef struct pro{
    int id;
    int r_time;   //remaining time
    int a_time;   //arrival time
    int priority;
    struct pro* next;
}process;


process* create_process(int id1,int r_time1,int a_time1,int priority1){
    process* NOUVEAU=(process*)malloc(sizeof(process));
    NOUVEAU->id=id1;
    NOUVEAU->a_time=a_time1;
    NOUVEAU->priority=priority1;
    NOUVEAU->r_time=r_time1;
    NOUVEAU->next=NULL;
    return NOUVEAU;
}

typedef struct {
    process *head;
    process *tail;
    int size;
    int quantum;  // UNTIL "TOURNIQET"
}queue;

queue* ini_queue(){
    queue* NB=(queue*)malloc(sizeof(queue));
    NB->head=NULL;
    NB->tail=NULL;
    NB->size=0;
    NB->quantum=0;
    return NB;
}

process* pop_process(queue* Lis){
    process* ND=NULL;
    if(Lis->head==NULL)exit(1);
    else if(Lis->head==Lis->tail){
    	ND=Lis->head;
        Lis->head=NULL;
	}
	else{
        ND=Lis->head;
        Lis->head=Lis->head->next;
    }
    
    ND->next==NULL;
    return ND;
}

void ECHANGE(process* pro1,process* pro2){
	process Y;
	Y.id=pro1->id;
    Y.a_time=pro1->a_time;
    Y.priority=pro1->priority;
    Y.r_time=pro1->r_time;
    pro1->id=pro2->id;
    pro1->a_time=pro2->a_time;
    pro1->priority=pro2->priority;
    pro1->r_time=pro2->r_time;
    pro2->id=Y.id;
    pro2->a_time=Y.a_time;
    pro2->priority=Y.priority;
    pro2->r_time=Y.r_time;
    
}


void push(queue* Lis,process* Aux){
    if(Lis->head==NULL){
        Lis->head=Lis->tail=Aux;
        Lis->size++;
    }
    else{
        Lis->tail->next=Aux;
        Lis->tail=Lis->tail->next;
        Lis->size++;
    }
}


//FIRST IN FIRST OUT 
  
queue* push_fifo(queue* Lis,process* Aux){
    int i;
    process* temp=Lis->head;
    if(Lis->head!=NULL){
        push(Lis,Aux);
        if(Aux->a_time<Lis->head->a_time){
        for(i=0;i<Lis->size-1;i++){
            temp=Lis->head;
            while(temp->next!=NULL){
            ECHANGE(temp,temp->next);
            temp=temp->next;
            }
        }
    }
    }
    else{
        push(Lis,Aux);
    }
    return Lis;
}


//END

queue* create_queue(){
    queue* Lis=ini_queue();
    int N,i,ID,A,R,P;
    printf("HOW MANY PROCESSES YOU WANNA ENTER IN THIS QUEUE ?: ");
    scanf("%d",&N);
    for(i=0;i<N;i++){
        printf("------------------PROCESS N.%d   ------------------:\n",i+1);
        printf("ID : ");
        scanf("%d",&ID);
        printf("ARRIVAL TIME : ");
        scanf("%d",&A);
        printf("REMAINING TIME : ");
        scanf("%d",&R);
        printf("PRIORITY : ");
        scanf("%d",&P);
        push_fifo(Lis,create_process(ID,R,A,P));
    }
    return Lis;
}

int EXECUTION(queue* Lis,int Y){
	int i;
	process* NB=NULL;
	for(i=0;i<Y;i++)
		printf(" ");
	while(Lis->head->r_time!=0){
		Lis->head->r_time--;
		Y++;
		printf("X");
	}
	NB=pop_process(Lis);
	return Y;
}

void GANTTDIAGRAMM(queue* Lis){
	int Y=0;
	int i=1;
	printf("\n\n********************GANTT DIAGRAMM********************\n\n");
	while(Lis->head!=NULL){
		printf("PROCESS ID°%d : ",Lis->head->id);
		Y=EXECUTION(Lis,Y);
		printf("\n");
		i++;
	}
}


void SJF(queue* Lis){
    int i;
	for(i=0;i<20;i++){
	process* Aux=Lis->head;
	while(Aux->next!=NULL){
		if(Aux->a_time==Aux->next->a_time){
			if(Aux->r_time>Aux->next->r_time)
			ECHANGE(Aux,Aux->next);
			if(Aux->next->next!=NULL)
			if(Aux->r_time+Aux->a_time>Aux->next->next->a_time)
			if(Aux->next->r_time>Aux->next->next->r_time)
			ECHANGE(Aux->next,Aux->next->next);
		}
		if(Aux->next->next!=NULL){
			if(Aux->a_time+Aux->r_time>Aux->next->next->a_time)
			if(Aux->r_time>Aux->next->a_time){
			if(Aux->next->r_time>Aux->next->next->r_time)
			ECHANGE(Aux->next,Aux->next->next);
		}
		}
        Aux=Aux->next;
	}
}
}

void GANTTDIAGRAMM_SJF(queue* Lis){
	int Y=0;
	int i=1;
	while(Lis->head!=NULL){
		SJF(Lis);
		printf("PROCESS ID° %d : ",Lis->head->id);
		Y=EXECUTION(Lis,Y);
		printf("\n");
		i++;
	}
}


void AFFICHAGE(queue* Lis){
    process* Aux=Lis->head;
    while(Aux!=NULL){
        printf("------------------PROCESS ID°%d   ------------------:\n",Aux->id);
        Aux=Aux->next;
    }
}

int main(){
    queue* Lis=create_queue();
    SJF(Lis);
    GANTTDIAGRAMM(Lis);
    return 0;
}