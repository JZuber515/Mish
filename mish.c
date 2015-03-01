/// 
/// $Id: mish.c,v 1.2 2014/05/12 23:12:21 csci243 Exp $ 
/// File: mish.c 
/// An interactive shell program
/// 
/// @author jxz5746: Jacob Zuber
///
/// // // // // // // // // // // // // // // // // // // // // // // //



#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#include "LinkedList.h"

///
/// getWordCount returns the number of words in
///  the passed char pointer based on number of spaces
/// @param str char* to get the number of words of
/// @return the number of words in str
static int getWordCount( const char* str )
{
	int count = 0;
	
	for( ; ; )
	{
		while( *str == ' ' )
			str++;
		
		if( *str == 0 )
			break;
		
		count++;
		
		while( *str != 0 && *str != ' ' )
			str++;
	}
	return count;
}


///
/// printArray prints the passed array
/// @param arr the array of char* to print
/// @param num the number of elements to print out of arr
static void printArray( char** arr )
{
	int i = 0;
	while( arr[i] != NULL )
	{
		printf( "\t%d: %s\n", i, arr[i] );
		i++;
	}
}

///
/// printHistory prints the passed linked list of
/// char pointers, numbering them 1 to size of history
/// @param history a linked list of char pointers
///         that holds the history to print
static void printHistory( LList_T history )
{
	
	for( int i = 0; i < ll_size( history ); i++ )
	{
		printf( "%d: %s\n", i+1, ll_get( history, i ) );
	}
}

///
/// printHelp prints a list of internal commands of mish
static void printHelp( void )
{
	printf( "verbose [on|off]- Turns verbose on or off based on argument.\n"
				"\tIf on, prints the command, a list of tokenized arguments,\n"
				"\tprocess ID being waited for, and the command that exec is\n"
				"\tcalling and the command status\n"
			"help- Prints a list of internal commands and a description of each\n"
			"history- Prints a list of the previous 10 commands\n"
			"quit- terminates mish\n" );
}

///
/// verboseSwitch changes the verbose option of the program
/// @param arr array of char* that give the command to call verbose
/// @param num the number of elements in arr
/// @param isVerbose the current state of verbose in the program
///   true=on, false=off
/// @return the new state of verbose the program should be in.
///   prints a usage message and returns the current state of
///   verbose if parameters are incorrect
static bool verboseSwitch( char** arr, int num, bool isVerbose )
{	
	if( num != 2 )
	{
		printf( "usage: verbose [on|off]\n" );
		return isVerbose;
	}
	else
	{
		if( strcmp( arr[1], "on" ) == 0 )
		{
			return true;
		}
		else if( strcmp( arr[1], "off" ) == 0 )
		{
			return false;
		}
		else
		{
			printf( "usage: verbose [on|off]\n" );
			return isVerbose;
		}
	}
}

///
/// prepend adds a character to the front of the passed char pointer
/// @param in the char pointer to prepend to
/// @param p the char to prepend
/// @return the resulting prepended char pointer
static char* prepend( const char* in, char p )
{
	int size = strlen( in );
	char* result = (char*) malloc(size+2);
	result[0] = p;
	strcpy( result+1, in );
	return result;
}


/// Main method to run the mish program
int main( int argc, char *argv[] )
{
	char *str = NULL;
	char *original = NULL;
	ssize_t read;	// used for testing reasons
	size_t len = 100;
	bool isVerbose = false;
	LList_T history = ll_create();
	
	if( argc == 2 )
	{	
		int num = atoi( argv[1] );
		if( num != 0 )
			isVerbose = true;
	}
	
	
	// INFINITE LOOP START
	for( int i = 1; ; i++ )
	{
		printf( "mish[%d]> ", i );

		if( (read = getline( &str, &len, stdin )) == -1 )
		{
			break;
		}
		if( str == NULL )
		{
			perror( "ERROR: Could not get input" );
			break;
		}
		
		// if only enter is pressed, don't let i increment and
		//  restart infinite loop
		if( strcmp( str, "\n" ) == 0 )
		{
			i--;
			continue;
		}
		
		int wordCount = getWordCount( str );
		
		// Save original line to add to history later
		int allocSize = sizeof(char) * strlen(str)+1;
		original = (char*) malloc( allocSize );
		strcpy( original, str );
		if( original[strlen( original+1 )] == '\n' )
		{
			original[strlen( original+1 )] = '\0';
		}		
		
		if( isVerbose )
		{
			printf( "\tcommand: %s\n\n", original );
		}
		
		
		
		
		
		// ADD WORDS INTO ARGS
		char **args = (char**) malloc( sizeof(char*) );
		int index = 0;
		char *token;
		
		// used to detect quotes
		bool isQuote = false;
		
		//start tokenizing
		token = strtok( str, " " );
		
		
		while( token != NULL )
		{
			// get rid of nextline for null terminator
			if( token[strlen( token ) - 1] == '\n' )
			{
				token[strlen( token ) - 1] = '\0';
			}
			
			// set isQuote
			if( token[0] == '\'' || token[0] == '\"' )
			{
				if( token[ strlen(token)-1 ] != '\'' )
				{
					isQuote = true;
				}
				else if( token[ strlen(token)-1 ] != '\"' )
				{
					isQuote = true;
				}
			}
			
			
			if( isQuote )
			{
				
				char *temp;
				char* temp2;
				
				// While a closing quote is not found
				while( token[ strlen(token)-1 ] != '\"' && token[ strlen(token)-1 ] != '\'' )
				{
					// get the next token
					temp = strtok( NULL, " " );
					
					// get rid of nextline for null terminator
					if( temp[strlen( temp ) - 1] == '\n' )
					{
						temp[strlen( temp ) - 1] = '\0';
					}
					
					// add a space between them and put them together
					temp2 = prepend( temp, ' ' );
					token = strcat( token, temp2 );
				}
				free( temp2 );
			}
			
			// add token to args
			args[index] = (char*) malloc( sizeof(char) * strlen(token)+1 );
			strcpy( args[index], token );
			
			// next token
			token = strtok( NULL, " " );
			
			// increment
			index++;
			
			// allocate more mem for next token
			args = (char**) realloc( args, sizeof(char*) * (index+1) );
		}
		
		// set last args to null
		args[index] = NULL;
		free( token );
		
		
		
		
		if( isVerbose )
		{
			printf( "\tinput command tokens:\n" );
			printArray( args );
		}
		
		
		// internal command VERBOSE
		if( strcmp( args[0], "verbose" ) == 0 )
		{
			isVerbose = verboseSwitch( args, wordCount, isVerbose );
		}
		// internal command HISTORY
		else if( strcmp( args[0], "history" ) == 0 && wordCount == 1 )
		{
			printHistory( history );
		}
		// internal command QUIT
		else if( strcmp( args[0], "quit" ) == 0 && wordCount == 1 )
		{
			break;
		}
		// internal command HELP
		else if( strcmp( args[0], "help" ) == 0 && wordCount == 1 )
		{
			printHelp();
		}
		// for and exec
		else
		{
			pid_t id, my_id;
			int status;
		
			my_id = getpid();
		
			id = fork();
			
			switch( id )
			{
				case -1: // the fork() failed
					perror( "fork() failed\n" );
					exit( 1 );
				
				case 0: // in child process
					
					// get identity
					my_id = getpid();
					
					if( isVerbose )
					{
						printf( "\twait for pid %d: %s\n", my_id, args[0] );
						printf( "\texecvp: %s\n", args[0] );
					}
					
					execvp( args[0], args );
					
					// Failed if gets here
					perror( "" );
					exit( 1 );
				
				default: // is parent
					break;
			}
			
			
			
			// wait for child to exit
			id = wait( &status );
			
			printf( "command status: %d\n", status );
		
		}
		
		// add original to history
		ll_append( history, original );
		
		// keep size of history limited to 10
		while( ll_size( history ) > 10 )
		{
			ll_pop( history );
		}
		
		// free all arguments and args itself
		for( int f = 0; args[f] != NULL; f++ )
		{
			free( args[f] );
		}
		free( args );
	}
	// END INFINITE LOOP
	
	
	// infinite loop was broken, free memory of history
	ll_destroy( history );
	free( str );
	printf( "\n" );
	return 0;
}

/// Revisions:
///	$Log: LinkedList.c,v $
/// Revision 1.2  2014/05/12 23:12:21  csci243
/// Quoted input now groups together in tokenizing
/// 
/// Revision 1.1  2014/05/11 21:11:31  csci243
/// Initial Revision
/// 

