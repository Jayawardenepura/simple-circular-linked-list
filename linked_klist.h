#ifndef LINKED_KLIST_H
#define LINKED_KLIST_H

 /* This file based on Linux Kernel (include/linux/list.h) 
  */

/*
 * Simple doubly linked list implementation.
 *
 * Some of the internal functions ("__xxx") are useful when
 * manipulating whole lists rather than single entries, as
 * sometimes we already know the next/prev entries and we can
 * generate better code by using them directly rather than
 * using the generic single-entry routines.
 */

struct list_head {
	struct list_head *prev,*next;
};


#define INIT_LIST_HEAD(ptr) do { 		  \
	(ptr)->next = (ptr); (ptr)->prev = (ptr); \
} while (0)


/**
 * list_entry - get the struct for this entry
 * @ptr:	the &struct list_head pointer.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_struct within the struct.
 */
#define list_entry(ptr, type, member) \
	((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))


/**
 * list_for_each - iterate over a list
 * @pos:	the &struct list_head to use as a loop counter.
 * @head:	the head for your list.
 */
#define list_for_each(pos, head) \
	for (pos = (head)->next; pos != (head); \
        	pos = pos->next)


/**
 * list_for_each_reverse - iterate over a list at reverse order
 * @pos:	the &struct list_head to use as a loop counter.
 * @head:	the head for your list.
 */
#define list_for_each_reverse(pos, head) \
	for (pos = (head)->prev; pos != (head); \
        	pos = pos->prev)


/**
 * list_insert_node - redistribution pointers by position
 * @pos:	the &struct list_head to use as a loop counter.
 * @new:	pointer for a new node.
 */
#define list_insert_node(pos, new)	\
		new->next = pos->next;  \
		new->prev = pos;	\
		pos->next->prev = new;  \
		pos->next = new;


/**
 * list_traverse_ - iterate over a list with return pointer of current node
 * @pos:	the &struct list_head to use as a loop counter.
 * @head:	the head for your list.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_struct within the struct.
 * @node:	user's node. 
 *
 * Note: Usefull for print all nodes of list
 */
#define list_traverse_(pos, head, type, member, node) 		 	       \
		for (pos = (head)->next, 				       \
		    node = list_entry(pos, type, member);		       \
		pos != (head); 						       \
        	pos = pos->next, 				       	       \
		    node = list_entry(pos, type, member))
		
/**
 * list_reverse - iterate over a list with return pointer of current node
 *		in revers order
 * @pos:	the &struct list_head to use as a loop counter.
 * @head:	the head for your list.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_struct within the struct.
 * @node:	user's node. 
 *
 * Note: Usefull for print all nodes of list
 */
#define list_reverse(pos, head, type, member, node) 				\
		for (pos = (head)->prev,					\
		     node = list_entry(pos, type, member); 			\
		pos != (head); 							\
		pos = pos->prev, 						\
		     node = list_entry(pos, type, member))				
		

/*
 * Insert a new entry between two known consecutive entries. 
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static inline void __list_add(struct list_head *new,
			      struct list_head *prevNode,
			      struct list_head *nextNode)
{
	nextNode->prev = new;
	new->next = nextNode;
	new->prev = prevNode;
	prevNode->next = new;
}


/**
 * list_add - add a new entry
 * @new: new entry to be added.
 * @head: list head to add it after.
 *
 * Insert a new entry after the specified head
 * This is good for implementing stacks
 */
static inline void list_add(struct list_head *new, struct list_head *head)
{
	__list_add(new, head, head->next);
}


static inline void __list_del(struct list_head *prev, struct list_head *next)
{
	next->prev = prev; 
	prev->next = next;
}


/**
 * list_del - deletes entry from list.
 * @entry: the element to delete from the list.
 * Note: list_empty on entry does not return true after this, the entry is in an undefined state.
 */
static inline void list_del(struct list_head *entry)
{
	__list_del(entry->prev, entry->next);
	entry->next = (void *) 0;
	entry->prev = (void *) 0;
}


/**
 * insert_by_position - insert node in list by position by reverse order.
 * @pos:	the &struct list_head to use as a loop counter.
 * @head:	the head for your list.
 * @new:	pointer of struct by new node.
 * @index:	user's index for insert node.
 *
 * Note: Using list_insert_node() for redistribution of nodes' pointers. 
 */
static inline void insert_by_position(struct list_head *pos,
                                      struct list_head *head,
                                      struct list_head *new,
                                      unsigned int index)
{
	unsigned int 
	counter = 0;

	list_for_each_reverse(pos, head){
		if(index == counter){
		  list_insert_node(pos, new)	
		  break;
		}
	counter++;
	}
}


/**
 * list_remove_node - remove node by position from list.
 * @pos:	the &struct list_head to use as a loop counter.
 * @head:	the head for your list.
 * @index:	user's index for remove node.
 *
 * Return position pointer of list.
 * Note: Using list_for_each_reverse() for iterate by reverse order.
 * Note: Using list_del() for subsidence nodes' ponters.
 */
static inline 
struct list_head * list_remove_node(struct list_head *pos,
				    struct list_head *head,
				    unsigned int index)
{
	unsigned int 
	counter = 0;

	list_for_each_reverse(pos, head){
		if(index == counter){
			list_del(pos);
			break;
		}
	counter++;
	}

	return pos;
}


/**
 * list_bubble_sort - sorting nodes by size 
 * @pos_out:	the &struct list_head to use as an out loop counter.
 * @pos_in:	the &struct list_head to use as an in loop counter.
 * @head:	the head for your list.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_struct within the struct.
 * @prev_node:	the user's struct for save prev node by contatiner_of.
 * @next_node:	the user's struct for save next node by contatiner_of.
 * @field:	user's data field of struct
 *
 * Note: Using tradional bubble sort algorithm 
 * See https://en.wikipedia.org/wiki/Bubble_sort
 *
 */
#define list_bubble_sort(pos_out, pos_in, head, type, member, prev_node, next_node, field)     \
		for (pos_out = (head)->next; pos_out != (head);pos_out = pos_out->next){\
			for (pos_in = (head)->next; pos_in != (head); ){ 		\
			     prev_node = list_entry(pos_in, type, member); 		\
			     pos_in = pos_in->next;				        \
			     if(pos_in == (head)) break;         			\
			       next_node = list_entry(pos_in, type, member);		\
			     if((next_node->field) > (prev_node->field)) 		\
			    							        \
				list_swap(pos_in,pos_in->prev,(head));			\
			     								\
			}								\
		}
		

/**
 * list_swap - swap two pointers of list
 * @node_a:	node ready for swap with node_b.
 * @node_b:	node ready for swap with node_a.
 * @head:	the head for your list.
 *
 * Return position pointer of list.
 */
static inline 
struct list_head * list_swap(struct list_head *node_a,
			     struct list_head *node_b,
			     struct list_head *head)
{
	/* Returns the new list root */
struct list_head *prev_a, *prev_b, *next_a, *next_b;

 /* save points */
 prev_a = node_a->prev;			   	   /* preceding node for node_a */
 prev_b = node_b->prev;			  	  /* preceding node for node_b */
 next_a = node_a->next; 			 /* the node following node_a */
 next_b = node_b->next; 			/* the node following node_b */

	if (node_b == next_a)  			/* neighboring nodes are exchanged */
	{
	   node_b->next = node_a;
	   node_b->prev = prev_a;
	   node_a->next = next_b;
	   node_a->prev = node_b;
	   next_b->prev = node_a;
	   prev_a->next = node_b;
	}else if (node_a == next_b)  		/* neighboring nodes are exchanged */
		{
		 node_a->next = node_b;
		 node_a->prev = prev_b;
		 node_b->next = next_a;
		 node_b->prev = node_a;
		 next_a->prev = node_b;
		 prev_b->next = node_a;
		}else{  			/* exchanged between nodes */
		     prev_a->next = node_b;
		     node_b->next = next_a;
		     prev_b->next = node_a;
		     node_a->next = next_b;
		     node_b->prev = prev_a;
		     next_b->prev = node_a;
		     node_a->prev = prev_b;
		     next_a->prev = node_b;
		}

	if (node_a == head) return(node_b);
	if (node_b == head) return(node_a);

 return(head);
}

/**
 * list_clean - remove all nodes from list
 *		in revers order
 * @pos:	the &struct list_head to use as a loop counter.
 * @pos_n:	the &struct list_head to use as a second loop counter.
 * @head:	the head for your list.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_struct within the struct.
 * @node:	user's node. 
 *
 * Note: all memory will free
 */
#define list_clean(pos, pos_n, head, type, member, node) 			   \
	for (pos = (head)->next, pos_n = pos->next; 				   \
	     pos != (head); 							   \
	     pos = pos_n, pos_n = pos->next){ 					   \
		node = list_entry(pos, type, member);			   	   \
	        list_del(pos);							   \
	     	free(tmp);							   \
	}

#endif
