/***************************************************************************
    CSC209 Assignment 2 C and Pointers -> testhelper.h
    Start: Febuary 9th, 2015
    By: Joshua Fung
**************************************************************************/
/* Include gard for the header file, defineing TESTHELPER_H */
# ifndef TESTHELPER_H
# define TESTHELPER_H

/****************************************************************************/
/* Implemented in testhelpers.c */
/* The remaining functions are for testing purposes*/

/* prints the list of allocated blocks */
void print_allocated();

/* prints the list of free blocks */
void print_free();

/* A function that writes to the memory allocacted by smalloc */
void write_to_mem(int size, char *ptr, char value);

/* prints the contents of allocated memory */
void print_mem();

# endif
