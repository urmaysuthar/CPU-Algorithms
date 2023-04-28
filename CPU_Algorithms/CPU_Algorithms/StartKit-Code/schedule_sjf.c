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
struct node* current = NULL;
struct node* new_node = NULL;
struct node* final = NULL;
int num_tasks = 0;

void add(char * name, int priority, int burst) {
	
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
      if (((new_node->task->burst) > (current->task->burst)) || ((new_node->task->burst) == (current->task->burst))) {
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
    
	 	  
      if ((new_node->task->burst < current->next->task->burst)) {
	  
	  if (new_node->task->burst > current->task->burst) {
	  new_node->next = current->next;
	  current->next = new_node ;
	  current = head;
	  break;
	  }
	  else if (new_node->task->burst < current->task->burst) {

	  head = new_node;
      new_node->next = current;
	  current = head;
	  break;
	   
	  }	  
	   
      }
	  
	  else if (new_node->task->burst == current->next->task->burst) {
	   current = current->next ;
	   
	   if (current->next == NULL) {
       new_node->next = NULL;
	   
	   }
	   
	   
	   else if (new_node->task->burst == current->next->task->burst) {  
		current = current->next ;   
		new_node->next = current->next;      
	   }   
	   
	   else {   
	   new_node->next = current->next;	    
	   }   
	   
	    current->next = new_node;
	  	   
	    current = head;		    
		break;  
	  }  
	  
	  
	  else if ((new_node->task->burst) > (current->next->task->burst)) {
	  current = current -> next;
	  
	  if (current->next == NULL) {
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
 int total_burst_time = 0;
 float total_turnaround_time = 0;
 float total_response_time = 0;
 float total_wait_time = 0;
 
  struct node* current_node = head;

  while (current_node != NULL) {
	 num_tasks++;

    run(current_node->task, current_node->task->burst);

    total_burst_time += current_node->task->burst;
	total_turnaround_time += total_burst_time; 
	//printf("debug");

	if (current_node->next != NULL) {
	total_response_time += total_burst_time;
	}

	current_node = current_node->next;

}
//printf("debug");
total_wait_time = total_turnaround_time - total_burst_time;
printf("\nAverage wait time = %.2f \n" , (total_wait_time/num_tasks));
printf("Average turnaround time = %.2f  \n" , (total_turnaround_time/num_tasks));    
printf("Average response time = %.2f  \n" , (total_response_time/num_tasks));

}