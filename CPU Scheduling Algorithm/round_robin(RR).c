#include<stdio.h>
#include<stdlib.h>

#define P_NORMAL 5
#define P_HIGH 1
#define P_LOW 10
#define QUANTUM 5
int PID = 1, CLOCK = 0, TotalWaitingTime = 0, TotalProcessExecuted=0;

//Queue item
typedef struct a{
    int pid, priority, bt,at,wt,tt, lastSeen;
    struct a *next, *prev;
}PCB;

// Ready Queue
typedef struct{
    PCB *head,*tail;
}Queue;

//Read the list
void printQueue(Queue *q){
    PCB *pn = q->head;

    printf("\n\nPID\t BurstTime\t ArrivalTime\t WatingTime\t NodeLocation\n");
    while(pn!=0){
        printf("%3d %8d %15d %15d \t\t@%d\n", pn->pid, pn->bt, pn->at, pn->wt, pn);
        pn = pn->next;
    }
}

// Add item
void insertProcess(Queue *q, int burst, int priority){
    PCB *newProcess = (PCB *) malloc(sizeof(PCB));
    newProcess->next = newProcess->prev = 0;


    newProcess->pid = PID++;
    newProcess->priority = priority;
    newProcess->bt = burst;
    newProcess->at = CLOCK;
    newProcess->wt= -1; //uninitialized
    newProcess->tt= -1; //uninitialized
    newProcess->lastSeen = -1;

    if(q->head ==0){
        q->head = q->tail = newProcess;
    } else {
        q->tail->next = newProcess;
        newProcess->prev = q->tail;
        q->tail = newProcess;
    }
}

// Pop item
PCB deQueue(Queue *list){
    PCB t;
    t.pid = 0;

    if(list->head == 0){
        printf("No process to dequeue");
        return t;
    }

    t = *list->head;
    list->head = list->head->next;

    return t;
}

// Re add an item to the ready queue
void re_Add_PCB(Queue *q, PCB r){
    PCB *p = (PCB *) malloc(sizeof(PCB));

    p->pid = r.pid;
    p->priority = r.priority;
    p->bt = r.bt;
    p->wt = r.wt;
    p->at = r.at;
    p->tt = r.tt;
    p->lastSeen = r.lastSeen;

    p->next = p->prev = 0;
    if(q->head == 0){
        q->head = q->tail = p;
    } else{
        q->tail->next = p;
        p->prev = q->tail;
        q->tail = p;
    }


}


void executeProcessRR (Queue *rq){
    while(!rq->head == 0){ // CPU execution until the ready queue is empty
        int waiting = 0;
        PCB r = deQueue(rq); //fetch a process from Ready Queue
        printf("\n\nProcess %d is being processed", r.pid);

        if(r.lastSeen == -1){
            waiting = CLOCK - r.at;
        } else{
            waiting = CLOCK - r.lastSeen;
        }
        r.wt = waiting;
        TotalWaitingTime += waiting;


        if(r.bt <= QUANTUM){
            CLOCK += r.bt;
            TotalProcessExecuted++;

            printf("\nProcess %d completed", r.pid);
        }else{
            CLOCK += QUANTUM;
            r.bt -= QUANTUM;
            r.lastSeen = CLOCK;

            re_Add_PCB(rq, r);
        }
        printf("\nWaiting time for process %d is %d", r.pid, r.wt);
        printf("\nAfter Time Slice/Quantum Completion, CLOCK = %d", CLOCK);
    }

}


int main(){
    Queue *readyQ = (Queue *) malloc(sizeof(Queue));

    readyQ->head = readyQ->tail = 0;

    insertProcess(readyQ, 10, P_NORMAL);
    insertProcess(readyQ, 5, P_NORMAL);
    insertProcess(readyQ, 20, P_NORMAL);
   // insertProcess(readyQ, 3, P_NORMAL);
    //insertProcess(readyQ, 5, P_NORMAL);

    printQueue(readyQ);

    //deQueue(readyQ);
   // printQueue(readyQ);

   executeProcessRR(readyQ);
   printf("\n\nTotal Waiting Time: %d\n" ,  TotalWaitingTime);
   printf("\nAverage waiting time: %f ", (float)(TotalWaitingTime / TotalProcessExecuted));
}

