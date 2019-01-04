
/* The sample, see code in linked_klist.h */


#include "linked_klist.h"

#include <stdlib.h>
#include <stdio.h>

/** User's struct **/
struct kool_list{
	int data; 		/* user can choose type of data. F.e. char */
	struct list_head list;  /* add list_head list for create linked_list */
};

int main(void) /* we needn't command arguments */
{

/* Create list */
struct kool_list mylist; 

/* Temporary struct pointers */
struct list_head *position;
struct kool_list *tmp;

	/* Create head*/
	/* head->next = head->prev; */
	INIT_LIST_HEAD(&(mylist.list));


	/* filling list by 10 nodes */
	for(int i = 10; i != 0; --i){ 

	tmp = malloc(sizeof*tmp);
	
	printf("Node: ");
	if(1 == scanf("%d", &(tmp->data)))

	/* add the new item 'tmp' to the list of items in mylist */
	list_add(&(tmp->list), &(mylist.list));
	}

	/* Return all nodes,print list */
	list_traverse_(position,&(mylist.list),struct kool_list,list,tmp){
		       printf(" (%i) ",tmp->data);
	}

	/* temporary data for new node */
	struct kool_list *tmp_2 = malloc(sizeof*tmp_2);
	
	printf("Node: \n");
	if(1 == scanf("%i",&(tmp_2->data)))

	insert_by_position(position,&(mylist.list),&(tmp_2->list),1); /* 1 - position */
	
	/* Return all nodes,print list */
	list_traverse_(position,&(mylist.list),struct kool_list, list, tmp){
		       printf(" (%i) ",tmp->data);
	}

	struct kool_list *node_a, *node_b; /* temporary structs for bubble loop */
	struct list_head *position_in;

	list_bubble_sort(position,position_in,&(mylist.list), struct kool_list, list, node_a, node_b, data)

	printf("Sorted\n");
	putchar('\n');

	/* Return all nodes,print list */
	list_traverse_(position, &(mylist.list), struct kool_list, list, tmp){
		printf(" (%i) ",tmp->data);
	}
	
	/* Return all nodes by reverse order,print list */
	printf("Reversed:\n");
	list_reverse(position, &(mylist.list), struct kool_list, list, tmp){
		printf(" (%i) ",tmp->data);
	}
	
	putchar('\n');

	/* Return all nodes,print list */
	list_traverse_(position, &(mylist.list), struct kool_list, list, tmp){
		printf(" (%i) ",tmp->data);
	}

	struct kool_list *temp_data = malloc(sizeof *temp_data);

	/** Return node for remove by position. 
	* 2 - position in list
	*/
	temp_data = list_entry( list_remove_node(position,&(mylist.list),2)  , struct kool_list,list);
	printf("Deleted data:%i\n",temp_data->data);
	free(temp_data); /* free node */

	putchar('\n');
	
	/* Return all nodes,print list */
	list_traverse_(position,&(mylist.list), struct kool_list,list,tmp){
		       printf(" (%i) ",tmp->data);
	}

	struct list_head *position_next;/* temporary structs for get next position in loop */

	list_clean(position,position_next,&(mylist.list), struct kool_list,list,tmp)
	printf("\nAll nodes removed\n");

	/* Return all nodes,print list */
	list_traverse_(position,&(mylist.list), struct kool_list,list,tmp){
		       printf(" (%i) ",tmp->data);
	}

	return 0;
}