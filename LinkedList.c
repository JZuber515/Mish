/// 
/// $Id: LinkedList.c,v 1.1 2014/05/06 18:01:21 csci243 Exp $ 
/// File: LinkedList.c 
/// An implementation of a linked list that holds char*
/// 
/// @author jxz5746: Jacob Zuber
///
/// // // // // // // // // // // // // // // // // // // // // // // //


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>


/// Struct of the linked list of ints
/// Holds the length of the list,
/// the first Node in the list,
/// and the last Node int the list.
struct list
{
	int size;
	struct Node* head;
	struct Node* tail;
};

/// Define what a Node is
/// A Node holds data of an char* type
/// and the next Node in the list.
typedef struct Node
{
	struct Node* next;
	char* data;
} Node;

typedef struct list *LList_T;

#define _LL_IMPL_
#include "LinkedList.h"

/// creates an instance of an empty linked list
LList_T ll_create( void )
{
	LList_T new;
	
	new = (LList_T) malloc( sizeof(struct list) );
	if( new != NULL )
	{
		new->size = 0;
		new->head = NULL;
		new->tail = NULL;
	}
	return new;
}

/// Clears and frees the passed linked list
void ll_destroy( LList_T lst )
{
	assert( lst != NULL );
	ll_clear( lst );
	free( lst );
}

/// Empties passed linked list
void ll_clear( LList_T lst )
{
	assert( lst != NULL );
	
	while( ll_size( lst ) != 0 )
	{
		char* data = ll_pop( lst );
		free( data );
	}
}

/// Returns the number of elements in the passed linked list
int ll_size( LList_T lst )
{
	return lst->size;
}

/// Adds data to the end of the list
void ll_append( LList_T lst, char* data )
{
	assert( lst != NULL );
	
	struct Node* new = (struct Node*) malloc( sizeof(struct Node) );
	new->data = data;
	
	// IF LIST IS EMPTY
	if( lst->tail == NULL )
	{
		lst->head = new;
		lst->tail = new;
	}
	else
	{
		lst->tail->next = new;
		lst->tail = new;
	}
	
	lst->size++;
}

/// Returns element at passed index
char* ll_get( LList_T lst, int index )
{
	assert( lst != NULL );
	assert( index >= 0 && index < lst->size );
	
	if( index == 0 )
		return lst->head->data;
	
	else if( index == lst->size-1 )
		return lst->tail->data;
	else
	{
		struct Node* temp;
		temp = lst->head;
		for( int i = 0; i < index; i++ )
		{
			temp = temp->next;
		}
		return temp->data;
	}
}

/// Removes element at first index
char* ll_pop( LList_T lst )
{
	assert( lst != NULL );
	assert( lst->size != 0 );
	
	char* data = lst->head->data;
	
	if( lst->size == 1 )
	{
		free( lst->head );
		lst->head = NULL;
		lst->tail = NULL;
	}
	else
	{
		struct Node* head = NULL;
		struct Node* newHead = NULL;
		
		head = lst->head;
		newHead = head->next;
		free( head );
		lst->head = newHead;
	}
	lst->size--;
	
	return data;
}


/// Revisions:
///	$Log: LinkedList.c,v $
/// Revision 1.1  2014/05/06 18:01:21  csci243
/// Initial Revision
/// 








