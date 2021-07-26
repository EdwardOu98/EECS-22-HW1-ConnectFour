/********DO NOT MODIFY THIS SECTION************
 * 
 * EECS 22 : Advanced C Programming
 * Fall 2018, Prof. Quoc-Viet Dang
 * 
 * HW1  : ConnectFour game
 * Template file : ConnectFour.c
 * 
 * Created on September 26, 2018, 12:06 AM by Ali Nickparsa <anickpar@uci.edu>
 */
/**********************************************
 
// Enter your name, last name and UCInet ID below://
 * 
 * *****************************
 * First Name : Edward 
 * Last Name: Ou
 * UCInet ID: 15561434
 *
 */

#include <stdio.h>

/*Declare your function definitions in the section below*/
/*Mandatory Options : 1-DisplayMenu 2- RegularGame 3-AnvilGame 4-CheckConnect 5-PrintBoard*/
/*You may add other functions if needed*/
/*********************************************************/
void DisplayMenu();
void RegularGame(int c);
void AnvilGame(int c);
void PlaceAnvil(char bd[6][7], int col);
int CheckVertical(char bd[6][7]);
int CheckHorizontal(char bd[6][7]);
int CheckDiagonal(char bd[6][7]);
int CheckFull(char bd[6][7]);
void PrintBoard(char board[6][7], int c);
int CheckColumn(char bd[6][7], int cord);


/*********************************************************/

/*Declare your global variables below (if any)*/
/**************************************************/
char p1 = 'X';
char p2 = 'O';
char a = 'A';
char board[6][7];
char blank = ' ';


/**************************************************/

/*Colors (you can add or remove from this list*/
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"


/*Main function*/
int main(int argc, char** argv) {

    char ans;

    do{
        DisplayMenu();

        //Instruct the user about how to start a new game or quit
        //after he has finished one game
        printf("Please Enter 'n' for a new game, or 'q' to quit: ");
        scanf(" %c", &ans);
    }while(ans == 'n' || ans == 'N');

    return 0;
}

/*Display Menu Function*/
void DisplayMenu()
{
    char ans1, ans2;
    int modeG, modeC;  

    printf("\nWelcome to the Connect Four Game!\n\n");

    printf("Please Select the Type of Game You want to Play: \n");
    printf("(1)-R Regular \n");
    printf("(2)-A Anvil \n");
    printf("Please Enter \'R\' or \'A\': ");
    scanf(" %c", &ans1);


    if( ans1 == 'r' || ans1 == 'R')
    {
	printf("Regular mode selected\n\n");
	modeG = 1;
    }
    else if( ans1 == 'a' || ans1 == 'A')
    {
	printf("Anvil mode selected\n\n");
	modeG = 2;
    }

    printf("Please Enter: \n");
    printf("\'n\' for normal mode\n");
    printf("\'c\' for colored mode\n");
    scanf(" %c", &ans2);

    if(ans2 == 'n' || ans2 == 'N')
    {
	modeC = 1;
    }
    else if(ans2 == 'c' || ans2 == 'C')
    {
	modeC = 2;
    }

    switch(modeG)
    {
	case 1:
	    RegularGame(modeC);
	    break;
	case 2:
	    AnvilGame(modeC);
	    break;
    }
}

/*Print Board Function*/
void PrintBoard(char board[6][7], int c)
{
    int i, j, k;
    
    printf("  ***Connect Four*** \n");
    for(i = 0; i < 7; i++)
    {
	for(j = 0; j < 7; j++)
	{
            if(c == 1)
	    {
		printf("| %c", board[i][j]);
            }
	    else if(c == 2 && board[i][j] == p1)
	    {
		printf("| %s%c%s", KRED, board[i][j], KNRM);
	    }
	    else if(c == 2 && board[i][j] == p2)
	    {
		printf("| %s%c%s", KYEL, board[i][j], KNRM);
	    }
	    else if(c == 2 && board[i][j] == blank)
	    {
		printf("| %c", board[i][j]);
	    }
	    else if(c == 2 && board[i][j] == a)
	    {
		printf("| %c", board[i][j]);
	    }
	    if(j == 6)
	    {
	        printf("|\n");
	    }
	}
	printf("----------------------\n");
    }


    for(k = 0; k < 7; k++)
    {
	printf(" %d ", k+1);
	if(k == 6)
	{
	    printf("\n");
	}
    }
}

/*Regular Game Function*/
void RegularGame(int c)
{
    int i, j;
    int cord, row;
    int colflag;
    int v, h, d, f;
    int counter = 1;
    
    for(i = 0; i < 7; i++)
    {
	for(j = 0; j < 8; j++)
	{
	    board[i][j] = blank;
	}
    }


    do
    {
	    //After Placing 7 checkers, the program will check for win condition
	    //The first player who manages to connect four of his own checkers
	    //in horizontal, vertical, or diagonal direction will win the game
	    //If the board is full before any player can form a line, Player 2 
	    //will be the winner. 
	    if(counter > 7)
	    {
	        v = CheckVertical(board);
		h = CheckHorizontal(board);
		d = CheckDiagonal(board);
		f = CheckFull(board);
	    }

	    if( v == 1 || h == 1 || d == 1)
	    {
	        PrintBoard(board, c);	
	        printf("Player 1 is the winner!\n");
	        break;
	    }
	    else if(v == 2 || h == 2 || d == 2 || f == 1)
	    {
	        PrintBoard(board, c);
	        printf("Player 2 is the winner!\n");
	        break;
	    }
	do
	{
	    PrintBoard(board, c);
	    if(counter % 2 == 1)
	    {
		//instruct the user about how to place a checker
	        printf("Player1(X):\n");
	        printf("Please Enter number coordinate: ");
	        scanf("%d", &cord);
	    }
	    else
	    {
	        printf("Player2(O):\n");
	        printf("Please Enter number coordinate: ");
	        scanf("%d", &cord);
	    }
	    
            //Check if the column is available
	    row = CheckColumn(board, cord);
	    
	    if(row == -1)
	    {
		colflag = 0;
		//Display error message if the conlumn is full
		printf("Sorry,the column is full!\n");
		printf("Please Enter a New Coordinate!\n");
	    }
	    else
	    {
		colflag = 1; 
	    }
	
	}while(colflag == 0);

	//If the column is available, place a checker into the column
	if(counter % 2 == 1)
	{
	    board[row][cord-1] = p1;
	}	
	else
	{
	    board[row][cord-1] = p2;
	}
	
	counter++;
	
    }while(1);
}

/*Anvil Game Function*/
void AnvilGame(int c)
{
    int i, j;
    int k;
    int ac1 = 1, ac2 = 1;//Each player can use only one anvil per game
    int ac1f = 0, ac2f = 0;
    int cord, row;
    int colflag;
    int v, h, d, f;
    int counter = 1;
    
    for(i = 0; i < 7; i++)
    {
	for(j = 0; j < 8; j++)
	{
	    board[i][j] = blank;
	}
    }


    do
    {
	    //After Placing 7 checkers, the program will check for win condition
	    //The first player who manages to connect four of his own checkers
	    //in horizontal, vertical, or diagonal direction will win the game
	    //If the board is full before any player can form a line, Player 2 
	    //will be the winner. 
	    if(counter > 7)
	    {
	        v = CheckVertical(board);
		h = CheckHorizontal(board);
		d = CheckDiagonal(board);
		f = CheckFull(board);
	    }

	    if( v == 1 || h == 1 || d == 1)
	    {
	        PrintBoard(board, c);	
	        printf("Player 1 is the winner!\n");
	        break;
	    }
	    else if(v == 2 || h == 2 || d == 2 || f == 1)
	    {
	        PrintBoard(board, c);
	        printf("Player 2 is the winner!\n");
	        break;
	    }
	do
	{
	    PrintBoard(board, c);
	    if(counter % 2 == 1)
	    {
		do
		{
		    //Instruct the player about how to place a checker or an anvil
	            printf("Player1(X):\n");
	            printf("Please Enter number coordinate (enter 8 for anvil): ");
	            scanf("%d", &k);
		    if(k != 8)
		    {
		        cord = k;
			ac1f = 0;
		    }
		    else if(k == 8 && ac1 != 0)
		    {
		        printf("Anvil Selected! Now enter a number coordinate: ");
		        scanf("%d", &cord);
		        ac1--;		
		    }
		    else if(k == 8 && ac1 == 0)
		    {
			//Display message to the user when they have used up their anvil
		        printf("You have already used your anvil!!!\n");
		        ac1f = 1;
		    }
	        }while(ac1f == 1);
	    }
	    else
	    {
		do
		{
	            printf("Player2(O):\n");
	            printf("Please Enter number coordinate (enter 8 for anvil): ");
	            scanf("%d", &k);
		    if(k != 8)
		    {
		        cord = k;
			ac2f = 0;
		    }
		    else if(k == 8 && ac2 != 0)
		    {
		        printf("Anvil Selected! Now enter a number coordinate: ");
		        scanf("%d", &cord);
		        ac2--;		
		    }
		    else if(k == 8 && ac2 == 0)
		    {
		        printf("You have already used your anvil!!!\n");
		        ac2f = 1;
		    }
	        }while(ac2f == 1);
	    }
	    if(k == 8)
	    {
	        PlaceAnvil(board, cord);
	    }
	    else
	    {
		row = CheckColumn(board, cord);
		
		if(row == -1)
		{
		    colflag = 0;
		    printf("Sorry, the column is full!\n");
		    printf("Please Enter a New Coordinate!\n");
		}
		else
		{
		    colflag = 1;
		    if(counter % 2 == 1)
		    {
			board[row][cord-1] = p1;
		    }
		    else
		    {
			board[row][cord-1] = p2;
		    }
		}
	    }
	}while(colflag == 0);

	
    counter++;
	
    }while(1);
}

/*Place Anvil Function*/
void PlaceAnvil(char bd[6][7], int col)
{
    int i;

    //Knock out all the checkers at the column except the one on the last row
    for(i = 0; i < 6; i++)
    {
	bd[i][col-1] = blank;
    }

    //Check whether the object on the last row is an anvil or not
    //If it is an anvil, place the current anvil on top of it
    if(bd[6][col-1] == a)
    {
	bd[5][col-1] = a;
    }
    else
    {
	bd[6][col-1] = a;
    }
}

/*Check Column Function*/
int CheckColumn(char bd[6][7], int cord)
{
    int i, j = -2, k;

    //Check if there's any empty space on the board
    for(i = 6; i >= 0; i--)
    {
	if(bd[i][cord-1] == blank)
	{
	    j = i;
	    break;
	}
    } 
    
    if(j == -2)
    {
	k = -1;
	return k; 
    }
    else
    {
	return j;
    }
}

/*Check Vertical Connection Function*/
int CheckVertical(char bd[6][7])
{
    int i, j;
    int bflg = 0;
    
    for(i = 3; i >= 0; i--)
    {
	for(j = 0; j < 7; j++)
	{
	    //Check if Player 1 has a vertical win condition
	    if(board[i][j]==p1 && board[i+1][j]==p1 && board[i+2][j]==p1 && board[i+3][j]==p1)
	    {
		bflg = 1;
		break;
	    }
	    //Check if Player 2 has a vertical win condition
	    if(board[i][j]==p2 && board[i+1][j]==p2 && board[i+2][j]==p2 && board[i+3][j]==p2)
	    {
		bflg = 2;
		break;
	    }
	}
	
	if(bflg != 0)
	break;
    }

    return bflg;
}

/*Check Horizontal Connection Function*/
int CheckHorizontal(char bd[6][7])
{
    int i, j;
    int bflg = 0;
    
    for(i = 0; i < 7; i++)
    {
	for(j = 0; j < 4; j++)
	{
	    //On the left side of the center line, check if Player 1 has a horizontal win condition
	    if(board[i][j]==p1 && board[i][j+1]==p1 && board[i][j+2]==p1 && board[i][j+3]==p1)
	    {
		bflg = 1;	
		break;
	    }
	    //On the left side of the center line, check if Player 2 has a horizontal win condition
	    if(board[i][j]==p2 && board[i][j+1]==p2 && board[i][j+2]==p2 && board[i][j+3]==p2)
	    {
		bflg = 2;
		break;
	    }
	}
	for(j = 3; j < 7; j++)
	{
	    //On the right side of the center line, check if Player 1 has a horizontal win condition
	    if(board[i][j]==p1 && board[i][j-1]==p1 && board[i][j-2]==p1 && board[i][j-3]==p1)
	    {
		bflg = 1;
		break;
	    }
	    //On the right side of the center line, check if Player 2 has a horizontal win condition
	    if(board[i][j]==p2 && board[i][j-1]==p2 && board[i][j-2]==p2 && board[i][j-3]==p2)
	    {
		bflg = 2;
		break;
	    }
	}
	
	if(bflg != 0)
	break;
    }

    return bflg;
}

/*Check Diagonal Connection Function*/
int CheckDiagonal(char bd[6][7])
{
    int i, j;
    int bflg = 0;
    
    for(i = 3; i >= 0; i--)
    {
	for(j = 0; j < 4; j++)
	{
	    //On the left side of the center line, check if Player 1 has a diagonal win condition
	    if(board[i][j]==p1 && board[i+1][j+1]==p1 && board[i+2][j+2]==p1 && board[i+3][j+3]==p1)
	    {
		bflg = 1;	
		break;
	    }
	    //On the left side of the center line, check if Player 2 has a diagonal win condition
	    if(board[i][j]==p2 && board[i+1][j+1]==p2 && board[i+2][j+2]==p2 && board[i+3][j+3]==p2)
	    {
		bflg = 2;
		break;
	    }
	}
	for(j = 3; j < 7; j++)
	{
	    //On the right side of the center line, check if Player 1 has a diagonal win condition
	    if(board[i][j]==p1 && board[i+1][j-1]==p1 && board[i+2][j-2]==p1 && board[i+3][j-3]==p1)
	    {
		bflg = 1;
		break;
	    }
	    //On the right side of the center line, check if Player 2 has a diagonal win condition
	    if(board[i][j]==p2 && board[i+1][j-1]==p2 && board[i+2][j-2]==p2 && board[i+3][j-3]==p2)
	    {
		bflg = 2;
		break;
	    }
	}
	
	if(bflg != 0)
	break;
    }

    return bflg;
}

/*Check Full Function*/
int CheckFull(char bd[6][7])
{
    int i, j;
    int flag = 0, br = 0;

    //Check if the board is filled up
    for(i = 6; i >= 0; i--)
    {
	for(j = 0; j < 7; j++)
	{
	    if(bd[i][j] == blank)
	    {
		flag = 0;
		br = 1;
		break;
	    }
	    else
	    {
		flag = 1;
	    }
	}
	
	if(br == 1)
	break;
    }

    return flag;
}
