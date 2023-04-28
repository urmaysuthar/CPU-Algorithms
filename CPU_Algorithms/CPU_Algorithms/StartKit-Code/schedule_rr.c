// EECS 3221 CPU PROJECT
// 
// Urmay Suthar
// EECS 3221 Section M
// 218491555
//
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "task.h"
#include "list.h"
#include "schedulers.h"
#include "cpu.h"

struct node *head = NULL;
struct node *last = NULL;
struct node *new_node = NULL;
struct node* final = NULL;
int num_tasks = 0;

void add(char *name, int priority, int burst) {
num_tasks = num_tasks + 1;
if (head == NULL) {
 head = malloc(sizeof(struct node)) ;
 last = malloc(sizeof(struct node)) ;

 
head->task = malloc(sizeof(struct task));
head->task->name = name;
head->task->burst = burst;
head->task->priority = priority;

head->next = NULL;
last = head;
}	

else {
	
new_node =  malloc(sizeof(struct node));	
last->next = new_node;
new_node->task = malloc(sizeof(struct task));
new_node->task->name = name;
new_node->task->burst = burst;
new_node->task->priority = priority;
new_node->next = NULL;	
last = new_node;
	
}

}

// invoke the scheduler
void schedule() {

struct node* current = head;
struct node* current_node = head;
struct node* vis = NULL;

vis = malloc(sizeof(struct node) );
vis = head;

int new_node_burst = 0;
int total_burst_time = 0;
float total_turnaround_time = 0;
float total_response_time = 0;
float total_wait_time = 0;
int check = 1;

while (current_node !=NULL) {

if (current_node->task->burst >= 10) {	


new_node_burst = current_node->task->burst-10; 


if (current!=head) {
while(vis!=current) {
if (strcmp(current->task->name ,vis->task->name) == 0) {	
check = 0;
break;	
}	
vis = vis->next;
}
vis = head;
}	

if (current_node->task->burst >10 && current_node!=head) {
if (current_node->next !=NULL) {
	if (check == 1){
total_response_time += total_burst_time;
	}
}
}

if (current_node->task->burst ==10 ) {

if (check == 1){
total_response_time += total_burst_time;
//printf("debug");
}
	
}	

total_burst_time = total_burst_time + 10; 
if (current_node->task->burst == 10) {
	
//printf("debug");
total_turnaround_time = total_burst_time +  total_turnaround_time; 
}	


current_node->task->burst = 10;

run(current_node->task,10);	
}
else if (current_node-> task-> burst  < 10 ) {
new_node_burst = 0;
	if (check == 1) {
	total_response_time += total_burst_time;
	}

	total_burst_time += current_node->task->burst; 
	total_turnaround_time += total_burst_time; 
	//printf("debug");

	run(current_node->task,current_node->task->burst);	
}	
 
while(1) {	
if (current->next != NULL) { 
	current = current->next;
if (current->next == NULL) { 
	if (new_node_burst != 0) {
	struct node* new_nodenode = malloc(sizeof(struct node));
	new_nodenode->task = malloc(sizeof(struct task));	
	new_nodenode->task->name = current_node->task->name ;
	new_nodenode->task->burst = new_node_burst;
	new_nodenode->task->priority = current_node->task->priority;
	current_node = current_node->next ; 
	current->next = new_nodenode;	
	new_nodenode->next = NULL;
	current = current_node;    
	break;	
	}

else if (new_node_burst == 0) {
	current_node = current_node->next;	
	current = current_node;
   break;
}	

	
}
}
else { 

if (new_node_burst !=0) {
	struct node * new_node = malloc(sizeof(struct node));
	new_node->task = malloc(sizeof(struct task));	
	new_node->task->name = current_node->task->name ;
	new_node->task->priority = current_node->task->priority;
	new_node->task->burst = new_node_burst;
	current_node->next = new_node;
	current_node = current_node->next;
	new_node->next = NULL;
	current = new_node;
}
else {
	current_node = current_node->next;
}
break;	
}	
}

}
//printf("debug");
total_wait_time = total_turnaround_time - total_burst_time;
printf("\nAverage wait time = %.2f \n" , total_wait_time/num_tasks);
printf("Average turnaround time = %.2f \n" , total_turnaround_time/num_tasks);  	
printf("Average response time = %.2f \n" , total_response_time/num_tasks);
}