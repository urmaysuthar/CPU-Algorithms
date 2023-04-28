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

struct node* head = NULL;
struct node* last = NULL;
struct node* new_node = NULL;
struct node* current = NULL;

void add(char* name, int priority, int burst) {
if (head == NULL) {
    head = malloc(sizeof(struct node));

    head->task = malloc(sizeof(struct task));
    head->task->name = name;
    head->task->burst = burst;
    head->task->priority = priority;
    
    head->next = NULL;
    current = head;
  
  } else {

    new_node = malloc(sizeof(struct node));

    new_node->task = malloc(sizeof(struct task));
    new_node->task->burst = burst;
    new_node->task->name = name;
    new_node->task->priority = priority;
    
    if (!(current -> next)) {
      if (((new_node->task->priority) < (current->task->priority)) || ((new_node->task->priority) == (current->task->priority))) {
        current->next = new_node; 
        new_node->next = NULL;
      } 

	  else {
		 
	  new_node->next = current; 	
	  head = new_node;
      current = new_node;	  
	
      }	   
    }
		else {
    	  
	  while(1) {
      if ((new_node->task->priority > current->next->task->priority) ) {
	  
	  if (new_node->task->priority < current->task->priority) {
	  new_node->next = current->next;
	  current->next = new_node ;
	  current = head; 
	  break;
	  }
	  else if (new_node->task->priority > current->task->priority) {

		head = new_node;
		new_node->next = current;
		current = head;
		break;
	  }
	  
	  else if(new_node->task->priority == current->task->priority) {
		new_node->next = current->next;
        current->next = new_node;	
       break;		  
	  }  
	  
	  }	  
	   
	  else if (new_node -> task -> priority == current -> next -> task -> priority) {
	   current = current -> next ;
	   
	   if (current->next == NULL) {
        new_node->next = NULL;
	   }
	   
	   
	   else if ((new_node-> task->priority) == (current->next->task->priority)) {
		current = current -> next ;   
		new_node->next = current->next;     
	   }   
	   
	   else {  
	   new_node->next = current->next;	     
	   }   
	   
	    current->next = new_node;   
	    current = head;		    
		break;  
	  }  

	  else if ((new_node->task->priority) < (current->next->task->priority)) {
	  current = current->next;
	  
	  if ( current->next == NULL) {
	  current->next = new_node;  
	  new_node->next = NULL;
	  current = head;
	  break;
	  }	  
	   
      }	  
	   	    
	  }
    }
  }
}
// invoke the scheduler
void schedule() {
int num = 0;
float total_response_time = 0;
float total_turnaround_time = 0;
float total_wait_time = 0;
int burst = 0;

current = head;
struct node* current_node = head;	
struct node* beginning = malloc(sizeof(struct node));
int newburst = 0;
while (current_node != NULL) {


if (current_node->next ==NULL) {
run(current_node->task, current_node->task->burst);
break;	
}
else {

if ((current_node->task->priority != current_node->next->task->priority)) {	

run(current_node->task,current_node->task->burst);
current_node = current_node->next;
}


else {

	
if (current_node->next !=NULL) {
	
if ((current_node->task->priority == current_node->next->task->priority)) {
		
current = current_node ;  

while (current->next != NULL) {
	
current = current->next; 	

if (current->task->priority != current->next->task->priority) {	

beginning = current->next;


current->next = NULL;
current = current_node; 
break;
}
else {

}
}

while (current_node != NULL) {
if (current_node->task->burst >= 10) {
newburst = current_node->task->burst-10;
current_node->task->burst = 10;
num++;
run(current_node->task,10);	
}
else if (current_node->task->burst  < 10) {
newburst = 0;
total_turnaround_time += burst ; 
//printf("debug");
run(current_node->task,current_node->task->burst);	

}	
 
while(1) {	
if (current->next !=NULL) { 
current = current->next;	
if (current->next == NULL) { 
if (newburst != 0) {
struct node* new_node = malloc(sizeof(struct node));
new_node->task = malloc(sizeof(struct task));	
new_node->task->name = current_node->task->name ;
new_node->task->burst = newburst;
new_node->task->priority = current_node->task->priority;
current_node = current_node->next ;
current->next = new_node;	
new_node->next = NULL;
current = current_node;

break;	
}

else if (newburst == 0) {
current_node = current_node->next;
current = current_node; 
//printf("debug");
break;
}	

	
}
}
else {
	
current_node = current_node->next; 
current = beginning;

break;	
}	
}	
}

current_node = beginning;

}	

}
}
}

} 
//printf("debug");
//I give up. you win.
total_wait_time = total_turnaround_time - burst;
printf("\nAverage wait time = %.2f time units\n" , total_wait_time/num);
printf("Average turnaround time = %.2f time units \n" , total_turnaround_time/num);    
printf("Average response time = %.2f time units \n" , total_response_time/num);

}