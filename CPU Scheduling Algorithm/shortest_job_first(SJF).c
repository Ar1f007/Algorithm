#include<stdio.h>
#include<stdlib.h>

#define P_NORMAL 5
#define P_HIGH 1
#define P_LOW 10
int PID = 1, CLOCK = 0, TotalWaitingTime = 0, TotalProcessExecuted=0;
typedef struct a{
    int pid, priority, bt,at,wt,tt;
    struct a *next, *prev;
}PCB;

typedef struct{
    PCB *head,*tail;
}Queue;

void printQueue(Queue *q){
    PCB *pn = q->head;

    printf("\n\nPID\t BurstTime\t ArrivalTime\t WatingTime\t NodeLocation\n");
    while(pn!=0){
        printf("%3d %8d %15d %15d \t\t@%d\n", pn->pid, pn->bt, pn->at, pn->wt, pn);
        pn = pn->next;
    }

}

void insertProcess(Queue *q, int burst, int priority){
    PCB *newProcess = (PCB *) malloc(sizeof(PCB));
    newProcess->next = newProcess->prev = 0;


    newProcess->pid = PID++;
    newProcess->priority = priority;
    newProcess->bt = burst;
    newProcess->at = CLOCK;
    newProcess->wt= -1; //uninitialized
    newProcess->tt= -1; //uninitialized

    if(q->head ==0){
        q->head = q->tail = newProcess;
    } else {
        q->tail->next = newProcess;
        newProcess->prev = q->tail;
        q->tail = newProcess;
    }
}

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

void executeProcess (Queue *rq){
    while(!rq->head == 0){
        PCB r = deQueue(rq);
        printf("\n\nProcess %d is being processed", r.pid);
        r.wt = CLOCK - r.at;
        TotalWaitingTime += r.wt;
        CLOCK += r.bt;
        printf("\nWaiting time for process %d is %d", r.pid, r.wt);
        printf("\nAfter Completion, CLOCK = %d", CLOCK);
        TotalProcessExecuted++;
    }

}

void sort(Queue *list){
    PCB *q = list->head;
    int swapped, i, temp;
    PCB *ptr1;
    PCB *lptr = NULL;

    if(q == NULL){
        return;
    }

    do{
        swapped = 0;
        ptr1 = q;

        while(ptr1->next != lptr){
            if(ptr1->bt > ptr1->next->bt){
                temp = ptr1->bt;
                ptr1->bt = ptr1->next->bt;
                ptr1->next->bt = temp;


                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while(swapped);


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

    sort(readyQ);

    printQueue(readyQ);

    executeProcess(readyQ);
    //deQueue(readyQ);
   // printQueue(readyQ);


   printf("\n\nTotal Waiting Time: %d\n" ,  TotalWaitingTime);
   printf("\nAverage waiting time: %f \n\n", (float)(TotalWaitingTime / TotalProcessExecuted));
}

