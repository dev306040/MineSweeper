#include <iostream> 
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

//Size for the board rows and columns
const int SIZE = 10;

//Variables for the board 
enum MinePieces {mines ='@', cover = '*', burst = 'X', zero = '0', one, two, three, four, five,
	six, seven, eight};

struct Locate 
{
	int xrow;
	int ycol;
};

//Defines a new type of pointer VarArrPtr, for variables containing pointers to MinePieces
//varaiables. VarArrPtr points to all varaibles of type MinePieces inside the enum MinePieces.
typedef MinePieces* VarArrPtr;

//Function for displaying student info
void studentInfo();

//Function for displaying game info
void gameInfo(int& num);

//Function to initialize the field with the cover variable inside of the enum MinePieces
void initializeField(VarArrPtr*, int);

//Function place the mines in random position on the field
bool assignMines(VarArrPtr*);

//Function checks for mines and returns true or false.
bool checkMines(VarArrPtr*, Locate&);

//Function prints the minefield 
void printField(VarArrPtr*, int, bool);

int turn = 0;

int main()
{
	
	int num_of_mines;
	bool result;
	Locate coord;

	//Dynamic array representing the minefield
	VarArrPtr *minefield = new VarArrPtr[SIZE]; // rows
	for(int i = 0; i < SIZE; i++)
	{
		minefield[i] = new MinePieces[SIZE]; // columns
	}
	
	//Displays student informaiton		
	studentInfo();

	// Prompt user for number of mines to place on the board
	do
	{
		cout << setw(40) << "Welcome to Minesweeper!" << endl;
		cout << "Enter the number of mines to place on the field (15-25): ";
		cin >> num_of_mines;
		cout << endl;

	} while((num_of_mines < 15) || (num_of_mines > 25));
	
	//Displays game information
	gameInfo(num_of_mines);
	
	// Initializes the minefield with the asterisk in each row and column.
	initializeField(minefield, SIZE);

	// Assigns the mines in random places on the field
	srand(time(NULL));

	for(int i = 0; i < num_of_mines; i++)
	{
		result = assignMines(minefield);
		while(result == false)
		{
			result = assignMines(minefield);
		}
	}

	// Process for entering a position and testing it against the checkMine function. 
	// If the checkMine function detects that a mine is selected at the entered 
	// position, it will return true to the boolean result varialbe and displays 
	// a message that the game has ended 	
	do
	{
		cout << "Enter position for move #" << turn + 1 << "(row[0-9] col[0-9]): ";	
		cin >> coord.xrow >> coord.ycol;

		if((coord.xrow < 0) || (coord.xrow > 9) || (coord.ycol < 0) || (coord.ycol > 9))
		{
			cout << "Invalid position entered! Try again..." << endl;
			turn--;
		}
		// Process to end the game if result equals true	
		result = checkMines(minefield, coord);
		printField(minefield, SIZE, result);

	       	if(result == true)
		{
			cout << "You hit a mine!! Better luck next time!!" <<endl;
			break;
		}
			

	} while(turn < 15);
	if(turn == 15)
	{	
		result = true;
		cout << "Congrats!! You won!! Your prize is life itself!! Hooray! Hooray!" << endl;
		cout << "\n";
		
		printField(minefield,SIZE, result);
	}	

	//Delete dynamic array
	for(int i = 0; i < SIZE; i++)
	{
		delete [] minefield[i];
	}
	
	delete [] minefield;

	return 0;
}

/*
Function Name: studentInfo
Variables: VarrArrPtr* minefield, and int size.
Pre-Condition: Displays student information
Post-Condition: The same as the pre-condition.
*/
void studentInfo()
{
	cout <<"***********************************************************************\n";
        cout <<"******              Computer Science and Engineering             ******\n";
        cout <<"******                    Computer Sicence I                     ******\n";
        cout <<"****** 								 ******\n";
        cout <<"***********************************************************************\n";
        cout <<"\n";

        return;
}

/*
Function Name: gameInfo
Variables: int& num
Pre-Condition: Displays game information
Post-Condition: The same as the pre-condition.
*/
void gameInfo(int& num)
{
	cout << "This program will assign " << num << " mines to the 10 by 10 \n"
                << "board. Your objective will be to select ten sqaures on the \n"
                << "field that do not contain mines using the given information \n"
                << "from the adjacent sqaures. The game is over when you either \n"
                << "select 15 squares without hitting a mine or you select a square \n"
                << "containing a mine.\n";

        cout << endl;

        cout << "Initializing board...assigning mines...now let's begin...\n";
}
/*
Function Name: initializeField
Variables: VarrArrPtr* minefield, and int size.
Pre-Condition: The function will cover the field with an asterisk in each column and row
Post-Condition: The same as the pre-condition.
*/
void initializeField(VarArrPtr* minefield, int size)
{
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			(*(minefield[i] + j)) = cover;
		}
	}
}
/*
Function Name: assignMines
Variables:  VarArrPtr minefield
Pre-Condition: no mines are assigned to the field until the number of mines is selected 
Post-Condition: when the number of mines is selected the board will place mines at random 
		positions if the value returned is true.
*/ 
bool assignMines(VarArrPtr* minefield)
{
	int row = (rand() % 10) + 0;
	int col = (rand() % 10) + 0;

	if((*(minefield[row] + col)) == mines )
	{
		return false;
	}
	else
	{
		(*(minefield[row] + col)) = mines;

		return true;
	}


}

/*
Function Name: printField
Variables:  VarArrPtr minefield
Pre-Condition: Prints the minefield with all its initial values
Post-Condition: Updates minefield based on each turn the user takes 
*/ 
void printField(VarArrPtr* minefield, int size, bool reveal_mines)
{
	cout << "   0 1 2 3 4 5 6 7 8 9" << endl;
	cout << " +---------------------+" << endl;
	for(int i = 0; i < size; i++)
	{
		cout << i << "| ";
		for(int j = 0; j < size; j++)
		{
			if(reveal_mines == true) 
			{
				cout << static_cast<char>(minefield[i][j]) << ' ';
			}
			else if(minefield[i][j] == mines)
			{
				cout << static_cast<char>(cover) << ' ';
			}
			else
			{
				cout << static_cast<char>(*(minefield[i] + j)) << " ";
			}
		}	
		cout << "|";
		cout << endl;
	}
	cout << " +---------------------+" << endl;	
}
/*
Function Name: checkMines
Variables:  VarArrPtr minefield, Locate& find, int turn
Pre-Condition: Checks for  mines around the selected squares 
Post-Condition: If a mine is selected by the user then a 'X' is returned 
		and the game is over. If no mine is selected them the # of 
		mines is counted and printed in the selected square.
*/ 
bool checkMines(VarArrPtr* minefield, Locate& find)
{
	char count = '0';

	if(*(minefield[find.xrow] + find.ycol) == mines)
	{
		(*(minefield[find.xrow] + find.ycol)) = burst;

		return true;
	}
	if(*(minefield[find.xrow] + find.ycol) == cover)
	{
		for(int i = find.xrow - 1; (i <= find.xrow + 1) && (i <=9); i++)
		{
			if(i ==-1)
			{
				i = 0;
			}
			for (int j = find.ycol - 1; (j <= find.ycol + 1) && (j <=9); j++)
			{
				if(j == -1)
				{
					j = 0;
				}
				if(*(minefield[i] + j) == mines)
				{
					count++;
				}		
			}	
		}
		(*(minefield[find.xrow] + find.ycol)) = static_cast<MinePieces>(count);
		turn++;
		return false;
	}
	else 
	{
		cout << "Invalid entry! Re-enter position: " << endl;
		turn--;
		return false;
	}	
}
