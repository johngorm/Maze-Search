#include <iostream>
#include "maze_io.h"
using namespace std;

// Prototype for maze_search
int maze_search(char *, int, int);

int main(int argc, char *argv[])
{
  int rows, cols, result;
  char *mymaze;

  if(argc < 3){
    cerr << "Usage: ./maze in_filename out_filename" << endl;
    return 1;
  }

  mymaze = read_maze(argv[1], &rows, &cols);
  result = maze_search(mymaze, rows, cols);

  if( result == 1 ){
    cout << "Path successfully found!" << endl;
    print_maze(mymaze,rows,cols);
    write_maze(argv[2],mymaze,rows,cols);
  }
  else if (result == 0) {
    cout << "No path could be found!" << endl;
  }
  else {
    cout << "Error occurred during search!" << endl;
  }

  delete [] mymaze;
	
  return 0;
}

/**************************************************
 * Attempt to find shortest path and return:
 *  1 if successful
 *  0 if no path exists
 * -1 if an error occurred (no start of finish
 *     cell present in the maze)
 *
 * If path is found fill it in with '*' characters
 *  but don't overwrite the 'S' and 'F' cells
 *************************************************/
int maze_search(char *maze, int rows, int cols)
{	//Initialze predecessor array of appropriate size and
	//fill each index with -1;
	int *Pred = new int [rows*cols];
	int *BFSQ = new int [rows*cols];
	//Assume worst-case scenario of all squares in queue
	int head = 0;										
	int tail = 0;
	for(int i = 0; i< rows*cols; i++){
		Pred[i] = -1;
	}
	bool Fflag = false;
	bool Sflag = false;
	for(int i = 0; i < rows*cols; i++){
		if ((maze[i] == 'S') && (!Sflag)){
			Pred[i] = -2; 		//Indicates the start position in 
			Sflag = true; 		// Predecessor array
			BFSQ[0] = i; 
			tail++;
		}
		if((maze[i] == 'F') && (!Fflag))
			Fflag = true;		//There is an exit to the maze
	}
	if(!Sflag || !Fflag) 	//Ends program if maze doesn't have 
		return -1;					//start or finish'	
	int b;
	int l;
	bool exitFound = false;

	while(head != tail){	
		b = BFSQ[head];
		//Checking Northern index
		if(((b - cols) >= 0) && (Pred[(b-cols)] == -1)){			
			if(maze[(b-cols)] != '#'){
				Pred[b-cols] = b;
				if((maze[(b-cols)] == 'F')){
					l = (b-cols);
					exitFound = true;
					break;
				}
				BFSQ[tail] = (b - cols);
				tail++;
			}
		}
		//Checking Western Index
		if (((b-1) >= 0) &&  ((Pred[(b-1)]) == -1) && ((b/cols) <= ((b-1)/cols))){
			if(maze[(b - 1)] != '#'){
				Pred[b - 1] = b;
				if(maze[(b - 1)] == 'F'){
					l = (b-1);
					exitFound = true;
					break;
				}
				BFSQ[tail] = (b - 1);
				tail++;
			}
		}
		//Checking Southern Index
		if(((b + cols) < (rows*cols)) && (Pred[(b + cols)] == -1)){
			if(maze[(b+cols)] != '#'){
				Pred[b+cols] = b;
				if(maze[(b + cols)] == 'F'){
					l = (b+cols);
					exitFound = true;
					break;
				}
				BFSQ[tail]= (b + cols);
				tail++;
			}
		}
		//Checking Eastern Index
		if(((b +1) < (rows*cols)) && (Pred[(b + 1)] == -1) && ((b/cols)>=((b+1)/cols))){
			if(maze[(b + 1)] != '#'){
				Pred[b+1] = b;
				if(maze[(b + 1)] == 'F'){
					l = (b+1);
					exitFound = true;	
					break;
				}
				BFSQ[tail] = (b +1);
				tail++;
			}	
		}
		head++;
	}
	if(!exitFound) //There is no route from start to finish
		return 0;
	while(maze[Pred[l]] != 'S'){
		maze[(Pred[l])] = '*';
		l = Pred[l];	
	}	
	
	delete [] BFSQ;
	delete [] Pred; 
  return 1;
}
