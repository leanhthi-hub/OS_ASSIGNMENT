#include <stdio.h>
#include <stdlib.h>
#include "queue.h"






int empty(struct queue_t * q) {
	return (q->size == 0);
}
#define MAX_PRIO 5
void enqueue(struct queue_t * q, struct pcb_t * proc) {
	/* TODO: put a new process to queue [q] */	
	struct pcb_t* new_item =NULL;
	new_item=proc;
	if(q->size>=MAX_QUEUE_SIZE-1){

		return;
	}
	q->proc[q->size]=new_item;
	q->size++;
	return;
}

struct pcb_t * dequeue(struct queue_t * q) {
	/* TODO: return a pcb whose priority is the highest
	 * in the queue [q] and remember to remove it from q
	 * */
	if(empty(q)){return NULL;}
	// 	if(proc->priority>=MAX_PRIO){
	// 	return NULL;
	// }
	struct pcb_t* new_item =NULL;
	new_item=q->proc[0];
	if(new_item==NULL)return NULL;
	if(q->size==1){
		// new_item = q->pr
		q->size=0;
		return new_item;
	}
	int max=new_item->priority;
	int pos = 0;
	for(int i =0;i<q->size;i++){
		if(q->proc[i]->priority>max){
			new_item=q->proc[i];
			max=q->proc[i]->priority;
			pos=i;
		}
	}
	
	q->proc[pos]=NULL;
	for(int i=pos;i<q->size;i++){
		q->proc[i]=q->proc[i+1];}
	q->proc[q->size]=NULL;
	q->size--;
	q->proc[q->size]=NULL;
	return new_item;
}
