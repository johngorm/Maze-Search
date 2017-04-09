#include <iostream>
#include <fstream>
#include "maze_io.h"

using namespace std;

/*************************************************
 * Open the file specified by filename, and read the 
 * maze into a dynamically allocated array.
 * 
 * Return the pointer to that array (don't delete it..
 * we'll do that in main() ).  Return NULL if
 * you are unable to open the file or can't read
 * the dimensions.
 *
 * We also pass in two pointers to integers. Fill 
 *  those values in with the number of rows and 
 *  columns read by from the file (first two value
 *  in the file)
 *
 *************************************************/

char * read_maze(char *filename, int *rows, int *cols ) //could change this with C++ references
{	ifstream myfile(filename);
	if(myfile.fail()){
		cout<< "Error. File failed to open."<<endl;
		return NULL;
	}
	
	char z; 
	myfile >> *rows >> *cols;//Get the dimensions of matrix
	if(myfile.fail()){
		cout << "Error. Couldn't read maze dimensions." << endl;
		return NULL;
	} 
	char * maze = new char[(*rows)*(*cols)];
	for(int i = 0; i <(*rows)*(*cols); i++ ){
		myfile >> z;
		maze[i] = z;
	}
	myfile.close();
	return maze;
}

/*************************************************
 * Print the maze contents in a 2D format to the
 * screen
 *
 *************************************************/
void print_maze(char *maze, int rows, int cols)
{
	for(int r = 0; r < rows; r++){
		for(int c = 0; c < cols; c++){ 
			cout<<maze[(r*cols)+c];
		}
		cout<<endl;
	}
}

/*************************************************
 * Write maze should open the file specified by 
 * filename and write the contents of the maze
 * array to the file with the dimensions on the first
 * line.
 *
 *************************************************/
void write_maze(char *filename, char *maze, int rows, int cols)
{
	
	ofstream ofile(filename);
	ofile<<rows<<" "<<cols<<endl;
	for(int r = 0; r < rows; r++){
		for(int c = 0; c < cols; c++){
			ofile << maze[(r*cols)+c];
		}
		ofile << endl;
	}
	ofile.close();
}
