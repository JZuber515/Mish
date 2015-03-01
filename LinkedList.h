/// 
/// $Id: LinkedList.h,v 1.1 2014/05/06 18:01:21 csci243 Exp $ 
/// File: LinkedList.h 
/// A linked list of char*
/// 
/// @author jxz5746: Jacob Zuber
///
/// // // // // // // // // // // // // // // // // // // // // // // //


#ifndef _LINKEDLIST_ADT_H_
#define _LINKEDLIST_ADT_H_

#include <stdbool.h>

#ifndef _LL_IMPL_

typedef struct { } * LList_T;

#endif


/// ll_create constructs an instance of an empty linked list
///   that can add the char* type dynamically.
/// @return instance of linked list (this is a pointer).
LList_T ll_create( void );



/// ll_destroy clears all storage associated with the
///   linked list data structure
void ll_destroy( LList_T lst );


/// ll_clear clears the list content, making the list empty.
/// @param lst linked list to clear
/// lst is now empty
void ll_clear( LList_T lst );


/// ll_size returns the size of the list.
/// @param lst the list to get the size of
/// @return the count of ints in the list
int ll_size( LList_T lst );


/// ll_append appends a char* to the end of the list
/// @param lst the list to append to
/// @param data the char* to add to list
/// @post lst size grows by one.
void ll_append( LList_T lst, char* data );


/// ll_get returns the char* at index; char* remains in list.
/// @param lst the list to search through
/// @param index the 0-based position
/// @return char* requested
/// @pre index must be in the range of [0... ll_size(lst)].
/// @post lst size and contents do not change.
char* ll_get( LList_T lst, int index );


/// ll_pop removes the first element in the passed list
/// @param lst the list to remove from
/// @return the removed element
/// @post lst size has decreased by one.
char* ll_pop( LList_T lst );


#endif


/// Revisions:
///	$Log: LinkedList.h,v $
/// Revision 1.1  2014/05/06 18:01:21  csci243
/// Initial Revision
/// 







