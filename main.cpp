/* DO A MOVE FROM EACH SIDE */

#include <iostream>
using namespace std;

int
main (int argc, char ** argv)
{

  //Official dimension of a checkerboard is 8 by 8
  const int dimension = 8;
  char checkerboard[dimension][dimension];
  bool moveComplete = false;  
  unsigned int fromRow, fromCol;
  unsigned int toRow, toCol;
  bool jumpDone = false;
  unsigned numBlackCheckers=(dimension/2)*3, numWhiteCheckers=(dimension/2)*3;

  //set up the game to start
  for (int row = 0; row< dimension; row++){
    for (int col = 0; col < dimension; col++){
      
      char piece;

      if (row <= 2){
	piece = 'b';
      } else if ( row >=5){
	piece = 'w';
      } else {
	piece = 'X';
      }

      if (( row %2 == 0) && (col %2 ==0)){
	checkerboard[row][col] = piece;
      } else if (( row %2 == 0) && (col %2 !=0)){
	checkerboard[row][col] = ' ';
      } else if (( row %2 != 0) && (col %2 !=0)){
	checkerboard[row][col] = piece;
      }  else if (( row %2 != 0) && (col %2 ==0)){
	checkerboard[row][col] = ' ';
      }
    }
    
  }
  



    
    /* print out the current checkerboard */
    //Print col numbers across the top
    cout << "  ";
    for (int col=0; col < dimension; col ++){
       cout << col << " ";
    }
    cout << endl;
    for (int row = 0; row< dimension; row++){
      //print out row number along the left
      cout << row << " ";
      for (int col = 0; col < dimension; col++){
	cout << checkerboard[row][col] << " " ;
      }
      cout << "\n";
    }

    while (1) {

      cout << numBlackCheckers << " black checkers\n";
      cout << numWhiteCheckers << " white checkers\n";

      cout << "Blacks move!\n";
      
      jumpDone = false;
      
      do { /* Blacks whole move */
	
	moveComplete = false;
	if (jumpDone){
	  char answer;
	  
	  cout << "Can you jump again? [y/n] ";
	  cin >> answer;
	  
	  if ((answer == 'n') || (answer == 'N')){
	    cout << "No more jumps then move over\n";
	    moveComplete = true;
	  } else {
	    fromRow = toRow;
	    fromCol = toCol;
	    cout << "Jump from (" << fromRow << "," << fromCol << ")\n";
	  }
	} else { /* jump not done so need to query user for from location */
	  do { /* Valid From Move */
	    
	    do { /* Valid From Row */
	      cout << "From row [0-" << dimension-1 <<"]: ";
	      cin >> fromRow;
	    } while (fromRow > dimension-1);
	    
	    do { /* Valid From Col */
	      cout << "From column [0-" << dimension-1 <<"]: ";
	      cin >> fromCol;
	    } while (fromCol > dimension-1);
	    
	    if ((checkerboard[fromRow][fromCol] != 'b') && (checkerboard[fromRow][fromCol] != 'B')){
	      cout << "No black checker at (" << fromRow << "," << fromCol << ")\n";
	      cout << "Try again\n";
	    }
	  } while (checkerboard[fromRow][fromCol] != 'b');
	} 
	
	
	if (!moveComplete){
	
	  
	  do { /* Valid to Row*/
	    cout << "To row [0-" << dimension-1 <<"]: ";
	    cin >> toRow;
	  } while (toRow > dimension-1);
	  
	  do { /*Valid to Col */
	    cout << "To column [0-" << dimension-1 <<"]: ";
	    cin >> toCol;
	  } while (toCol > dimension-1);
	  
	  
	  cout << "Evaluating move from (" << fromRow << "," << fromCol << ") to ";
	  cout << "(" << toRow << "," << toCol << ")\n";
	  
	  if (checkerboard[toRow][toCol] != 'X'){
	    cout << "(" << toRow << "," << toCol << ") is not empty\n";
	    cout << "Try again\n";
	  } else  if (checkerboard[fromRow][fromCol] == 'b'){
	    
	    cout << "Moving non king checker\n";	 
	    //Move for a non-king checker
	    if (!jumpDone && ((toRow == fromRow+1) && ((toCol ==fromCol+1) || (toCol == fromCol-1)))){
	      //move forward - only ok if not following a jump
	      if (toRow == dimension-1){
		//king me
		checkerboard[toRow][toCol] = 'B';
	      } else{
		checkerboard[toRow][toCol] = 	  checkerboard[fromRow][fromCol];
	      }
	      checkerboard[fromRow][fromCol] = 'X';
	      
	      moveComplete = true;
	    }
	    
	    //try to jump one checker	
	    if ((toRow == fromRow+2) && (toCol ==fromCol+2) && 
	       ((checkerboard[fromRow+1][fromCol+1] == 'w') || (checkerboard[fromRow+1][fromCol+1] == 'W')))
	    {
		
		if (toRow == dimension-1){
		  //king me
		  checkerboard[toRow][toCol] = 'B';
		  moveComplete = true;  /* even if jumped here can't jump back? */
		  
		} else{
		  checkerboard[toRow][toCol] = 	  checkerboard[fromRow][fromCol];
		}
		checkerboard[fromRow][fromCol] = 'X';
		checkerboard[fromRow+1][fromCol+1] = 'X';
		numWhiteCheckers--;
		jumpDone = true;
	    } else if ((toRow == fromRow+2) && (toCol ==fromCol-2) && 
		       ((checkerboard[fromRow+1][fromCol-1] == 'w') || (checkerboard[fromRow+1][fromCol-1] == 'W')))    {	
	      if (toRow == dimension-1){
		//king me
		checkerboard[toRow][toCol] = 'B';
		moveComplete = true;  /* even if jumped here can't jump back? */
	      } else{
		checkerboard[toRow][toCol] = 	  checkerboard[fromRow][fromCol];
	      }
	      checkerboard[fromRow][fromCol] = 'X';
	      checkerboard[fromRow+1][fromCol-1] = 'X';
	      numWhiteCheckers--;
	      jumpDone = true;
	    }
	  } else {    //move for a king checker
	    cout << "Moving king checker\n";
	    //Move for a non-king checker
	    if (!jumpDone){
	      if (((toRow == fromRow-1) && ((toCol ==fromCol+1) || (toCol == fromCol-1))) ||
		  ((toRow == fromRow+1) && ((toCol ==fromCol+1) || (toCol == fromCol-1)))){
		//move forward or backward - only ok if not following a jump
		
		checkerboard[toRow][toCol] = checkerboard[fromRow][fromCol];
		checkerboard[fromRow][fromCol] = 'X';
		
		moveComplete = true;
		
	      }
	    } else {
	    
	      //try to jump one checker forward
	      if ((toRow == fromRow-2) && (toCol ==fromCol-2) && 
		  ((checkerboard[fromRow-1][fromCol-1] == 'w') || (checkerboard[fromRow-1][fromCol-1] == 'W')))
		{
		  
		  checkerboard[toRow][toCol] = 	  checkerboard[fromRow][fromCol];
		  checkerboard[fromRow][fromCol] = 'X';
		  checkerboard[fromRow-1][fromCol-1] = 'X';
		  jumpDone = true;
		  numWhiteCheckers--;
		} else if ((toRow == fromRow-2) && (toCol ==fromCol+2) && 
			   ((checkerboard[fromRow-1][fromCol+1] == 'w') || (checkerboard[fromRow-1][fromCol+1] == 'W')))
		{	
		  
		  checkerboard[toRow][toCol] = 	  checkerboard[fromRow][fromCol];
		  checkerboard[fromRow][fromCol] = 'X';
		  checkerboard[fromRow-1][fromCol+1] = 'X';
		  jumpDone = true;
		  numWhiteCheckers--;
		} else 	if ((toRow == fromRow+2) && (toCol ==fromCol-2) && 
			    ((checkerboard[fromRow+1][fromCol-1] == 'w') || (checkerboard[fromRow+1][fromCol-1] == 'W')))
		{
		  
		  checkerboard[toRow][toCol] = 	  checkerboard[fromRow][fromCol];
		  checkerboard[fromRow][fromCol] = 'X';
		  checkerboard[fromRow+1][fromCol-1] = 'X';
		  jumpDone = true;
		  numWhiteCheckers--;
		} else if ((toRow == fromRow+2) && (toCol ==fromCol+2) && 
			   ((checkerboard[fromRow+1][fromCol+1] == 'w') || (checkerboard[fromRow+1][fromCol+1] == 'W')))
		{	
		  
		  checkerboard[toRow][toCol] = 	  checkerboard[fromRow][fromCol];
		  checkerboard[fromRow][fromCol] = 'X';
		  checkerboard[fromRow+1][fromCol+1] = 'X';
		  jumpDone = true;
		  numWhiteCheckers--;
		}
	    }
	    
	  } //Move for king checker?
      
      
	} //if move complete

	
	/* print out the board for reference */
	//Print col numbers across the top
	cout << "  ";
	for (int col=0; col < dimension; col ++){
	  cout << col << " ";
	}
	cout << endl;
	for (int row = 0; row< dimension; row++){
	  //print out row number along the left
	  cout << row << " ";
	  for (int col = 0; col < dimension; col++){
	    cout << checkerboard[row][col] << " " ;
	  }
	  cout << "\n";
	}

      } while (!moveComplete);

      if (numWhiteCheckers ==0){
	cout << "Black wins!\n";
	exit(0);
      }    

      cout << "White move!\n";
    
      jumpDone = false;
      
      do { /* Whites whole move */
	
	moveComplete = false;
	if (jumpDone){
	  char answer;
	  
	  cout << "Can you jump again? [y/n] ";
	  cin >> answer;
	  
	  if ((answer == 'n') || (answer == 'N')){
	    cout << "No more jumps then move over\n";
	    moveComplete = true;
	  } else {
	    fromRow = toRow;
	    fromCol = toCol;
	    cout << "Jump from (" << fromRow << "," << fromCol << ")\n";
	  }
	} else { /* jump not done so need to query user for from location */
	  do { /* Valid From Move */
	    
	    do { /* Valid From Row */
	      cout << "From row [0-" << dimension-1 <<"]: ";
	      cin >> fromRow;
	    } while (fromRow > dimension-1);
	    
	    do { /* Valid From Col */
	      cout << "From column [0-" << dimension-1 <<"]: ";
	      cin >> fromCol;
	    } while (fromCol > dimension-1);
	    
	    if ((checkerboard[fromRow][fromCol] != 'w') && (checkerboard[fromRow][fromCol] != 'W')){
	      cout << "No black checker at (" << fromRow << "," << fromCol << ")\n";
	      cout << "Try again\n";
	    }
	  } while (checkerboard[fromRow][fromCol] != 'w');
	} 
	
	
	if (!moveComplete){
	  
	  
	  do { /* Valid to Row*/
	    cout << "To row [0-" << dimension-1 <<"]: ";
	    cin >> toRow;
	  } while (toRow > dimension-1);
	  
	  do { /*Valid to Col */
	    cout << "To column [0-" << dimension-1 <<"]: ";
	    cin >> toCol;
	  } while (toCol > dimension-1);
	  
	  
	  cout << "Evaluating move from (" << fromRow << "," << fromCol << ") to ";
	  cout << "(" << toRow << "," << toCol << ")\n";
	  
	  if (checkerboard[toRow][toCol] != 'X'){
	    cout << "(" << toRow << "," << toCol << ") invalid - can only move to dark,  empty squares\n";
	    cout << "Try again\n";
	  } else  if (checkerboard[fromRow][fromCol] == 'w'){
	    
	    cout << "Moving non king checker\n";
	    //Move for a non-king checker
	    if (!jumpDone && ((toRow == fromRow-1) && ((toCol ==fromCol+1) || (toCol == fromCol-1)))){
	      //move forward - only ok if not following a jump
	      if (toRow == dimension-1){
		//king me
		checkerboard[toRow][toCol] = 'W';
	      } else{
		checkerboard[toRow][toCol] = 	  checkerboard[fromRow][fromCol];
	      }
	      checkerboard[fromRow][fromCol] = 'X';
	      
	      moveComplete = true;
	    }
	    
	    //try to jump one checker	
	    if ((toRow == fromRow+2) && (toCol ==fromCol+2) && 
		((checkerboard[fromRow+1][fromCol+1] == 'b') || (checkerboard[fromRow+1][fromCol+1] == 'B')))
	      {
		
		if (toRow == dimension-1){
		  //king me
		  checkerboard[toRow][toCol] = 'W';
		  moveComplete = true;  /* even if jumped here can't jump back? */
		  
		} else{
		  checkerboard[toRow][toCol] = 	  checkerboard[fromRow][fromCol];
		}
		checkerboard[fromRow][fromCol] = 'X';
		checkerboard[fromRow+1][fromCol+1] = 'X';
		jumpDone = true;
		numBlackCheckers--;
	      } else if ((toRow == fromRow+2) && (toCol ==fromCol-2) && 
			 ((checkerboard[fromRow+1][fromCol-1] == 'b') || (checkerboard[fromRow+1][fromCol-1] == 'B')))
		{	
		  if (toRow == dimension-1){
		    //king me
		    checkerboard[toRow][toCol] = 'W';
		    moveComplete = true;  /* even if jumped here can't jump back? */
		  } else{
		    checkerboard[toRow][toCol] = 	  checkerboard[fromRow][fromCol];
		  }
		  checkerboard[fromRow][fromCol] = 'X';
		  checkerboard[fromRow+1][fromCol-1] = 'X';
		  jumpDone = true;
		  numBlackCheckers--;
		}
	  } else {
	    //move for a king checker
	    cout << "Moving king checker\n";
	    //Move for a non-king checker
	    if (!jumpDone){
	      if (((toRow == fromRow-1) && ((toCol ==fromCol+1) || (toCol == fromCol-1))) ||
	      ((toRow == fromRow+1) && ((toCol ==fromCol+1) || (toCol == fromCol-1)))){
		//move forward or backward - only ok if not following a jump
		
		checkerboard[toRow][toCol] = checkerboard[fromRow][fromCol];
		checkerboard[fromRow][fromCol] = 'X';
		
		moveComplete = true;
		
	      }
	    }
	    
	    //try to jump one checker forward
	    if ((toRow == fromRow-2) && (toCol ==fromCol-2) && 
		((checkerboard[fromRow-1][fromCol-1] == 'b') || (checkerboard[fromRow-1][fromCol-1] == 'B')))
	      {
		
		checkerboard[toRow][toCol] = 	  checkerboard[fromRow][fromCol];
		checkerboard[fromRow][fromCol] = 'X';
		checkerboard[fromRow-1][fromCol-1] = 'X';
		jumpDone = true;
		numBlackCheckers--;
	      } else if ((toRow == fromRow-2) && (toCol ==fromCol+2) && 
			 ((checkerboard[fromRow-1][fromCol+1] == 'b') || (checkerboard[fromRow-1][fromCol+1] == 'B')))
		{	
		  
		  checkerboard[toRow][toCol] = 	  checkerboard[fromRow][fromCol];
		  checkerboard[fromRow][fromCol] = 'X';
		  checkerboard[fromRow-1][fromCol+1] = 'X';
		  jumpDone = true;
		  numBlackCheckers--;
		} else 	if ((toRow == fromRow+2) && (toCol ==fromCol-2) && 
			    ((checkerboard[fromRow+1][fromCol-1] == 'b') || (checkerboard[fromRow+1][fromCol-1] == 'B')))
		  {
		    
		    checkerboard[toRow][toCol] = 	  checkerboard[fromRow][fromCol];
		    checkerboard[fromRow][fromCol] = 'X';
		    checkerboard[fromRow+1][fromCol-1] = 'X';
		    jumpDone = true;
		    numBlackCheckers--;
		  } else if ((toRow == fromRow+2) && (toCol ==fromCol+2) && 
		   ((checkerboard[fromRow+1][fromCol+1] == 'b') || (checkerboard[fromRow+1][fromCol+1] == 'B')))
		    {	
		      
		      checkerboard[toRow][toCol] = 	  checkerboard[fromRow][fromCol];
		      checkerboard[fromRow][fromCol] = 'X';
		      checkerboard[fromRow+1][fromCol+1] = 'X';
		      jumpDone = true;
		      numBlackCheckers--;
		    }
	    
	  }
	  
	} //if move complete

       
       
       /* print out the board for reference */
	//Print col numbers across the top
	cout << "  ";
	for (int col=0; col < dimension; col ++){
	  cout << col << " ";
	}
	cout << endl;
       for (int row = 0; row< dimension; row++){
	 //print out row number along the left
	 cout << row << " ";
	 
	 for (int col = 0; col < dimension; col++){
	   cout << checkerboard[row][col] << " " ;
	 }
	 cout << "\n";
       }
       
      } while (!moveComplete);
      
      if (numBlackCheckers ==0){
	cout << "White wins!\n";
	exit(0);
      }    

    }
    

return 0;
}
