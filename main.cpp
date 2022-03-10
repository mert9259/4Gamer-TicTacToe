#include <iostream>
#include <conio.h>
 
using namespace std;

/*
Board Shape
- - - -
- - - -
- - - -
- - - -

The order of indices required to translate the number
 0  1  2  3
 4  5  6  7
 8  9 10 11
12 13 14 15

The descending order of the numbers entered by the user
 1  2  3  4
 5  6  7  8
 9 10 11 12
13 14 15 16
*/



class Player{
	private:
		int playerId;
		char player;
		
		void changePlayerId (){
			playerId++;
			
		    if(playerId == 5)
				playerId=1;
		}
	public:
		Player(){playerId=1;player='X';}
		int getPlayerId(){return playerId;}
		char getPlayer(){return player;}
		void togglePlayer (){
		    if(player == 'X')
			player='O';
		    else if (player == 'O')
			player='x';
		    else if (player == 'x')
			player='o';
		    else if (player == 'o')
			player='X';
			
			changePlayerId();
		}
};

class Board: private Player{
	private:
		double useX;
		double useO;
		double useDiagX;
		double useDiagO;
	protected:
		char matrix[4][4];
	public:
		Board(){
			for(int i=0;i<4;i++){
				for(int j=0;j<4;j++)
					matrix[i][j]='-';
			}
			useX=0;useO=0;useDiagX=0;useDiagO=0;
		}
		void newBoard(){
			for(int i=0;i<4;i++){
				for(int j=0;j<4;j++)
					matrix[i][j]='-';
			}
		}
		double getUseX (){return useX;}
		double getUseO (){return useO;}
		double getUseDiagX (){return useDiagX;}
		double getUseDiagO (){return useDiagO;}
		void draw(int i,int j){
			if(matrix[i][j]=='-'){
				matrix[i][j]=Player::getPlayer();
				
				if(Player::getPlayer() == 'X' || Player::getPlayer() == 'x')
					useX++;
			    else if (Player::getPlayer() == 'O' || Player::getPlayer() == 'o')
					useO++;
				if(i==j || (i==0 && j==3) || (i==2 && j==1) || (i==1 && j==2) || (i==3 && j==0))
					if(Player::getPlayer() == 'X' || Player::getPlayer() == 'x')
						useDiagX++;
				    else if (Player::getPlayer() == 'O' || Player::getPlayer() == 'o')
						useDiagO++;
				/*
				Board+Player::getPlayer();
				if(i==j)
					Board*Player::getPlayer();*/
				Player::togglePlayer();
			}else
				cout<<"You cannot make this move. The field you want to mark is full.";
			
		}
		void printBoard(){
			cout<<endl<<"Playing now/ "<<Player::getPlayerId()<<".Gamer:"<<Player::getPlayer()<<endl;
			for(int i=0;i<4;i++){
				for(int j=0;j<4;j++)
					cout<<matrix[i][j]<<" ";
				cout<<endl;
			}
		}
		bool checkForMove(){
			bool isFull=true;
			
			for(int i=0;i<4;i++)
				for(int j=0;j<4;j++)
					if(matrix[i][j] == '-')
						isFull=false;
			return isFull;
		}
		void operator+(char player){
			if(player == 'X' || player == 'x')
				useX++;
		    else if (player == 'O' || player == 'o')
				useO++;
		}
		void operator*(char player){
			if(player == 'X' || player == 'x')
				useDiagX++;
		    else if (player == 'O' || player == 'o')
				useDiagO++;
		}
};


class Game:private Board{
	private:
		char winner;
	public:
		bool isWinner(){
			int countX=0;
			int countO=0;
			
			for(int j=0;j<4;j++){
				for(int i=0;i<3;i++)
					if(matrix[i][j] == 'X' && matrix[i+1][j] == 'x' || matrix[i][j] == 'x' && matrix[i+1][j] == 'X' || matrix[i][j] == 'x' && matrix[i+1][j] == 'x' || matrix[i][j] == 'X' && matrix[i+1][j] == 'X')
						countX++;
				if(countX<3)
					countX=0;
				else{
					winner='X';
					return true;
				}
			}
			for(int j=0;j<4;j++){
				for(int i=0;i<3;i++)
					if(matrix[i][j] == 'O' && matrix[i+1][j] == 'o' || matrix[i][j] == 'o' && matrix[i+1][j] == 'O' || matrix[i][j] == 'o' && matrix[i+1][j] == 'o' || matrix[i][j] == 'O' && matrix[i+1][j] == 'O')
						countO++;
				if(countO<3)
					countO=0;
				else{
					winner='O';
					return true;
				}
			}
			
			for(int i=0;i<4;i++){
				for(int j=0;j<3;j++)
					if(matrix[i][j] == 'X' && matrix[i][j+1] == 'x' || matrix[i][j] == 'x' && matrix[i][j+1] == 'X' || matrix[i][j] == 'x' && matrix[i][j+1] == 'x' || matrix[i][j] == 'X' && matrix[i][j+1] == 'X')
						countX++;
				if(countX<3)
					countX=0;
				else{
					winner='X';
					return true;
				}
			}
					
			for(int i=0;i<4;i++){
				for(int j=0;j<3;j++)
					if(matrix[i][j] == 'O' && matrix[i][j+1] == 'o' || matrix[i][j] == 'o' && matrix[i][j+1] == 'O' || matrix[i][j] == 'o' && matrix[i][j+1] == 'o' || matrix[i][j] == 'O' && matrix[i][j+1] == 'O')
						countO++;
				if(countO<3)
					countO=0;
				else{
					winner='O';
					return true;
				}
			}
			
			if((matrix[0][0]=='x' || matrix[0][0]=='X') && (matrix[1][1]=='x' || matrix[1][1]=='X')&& (matrix[2][2]=='x' || matrix[2][2]=='X') && (matrix[3][3]=='x' || matrix[3][3]=='X')){
				winner='X';
				return true;
			}else if((matrix[0][0]=='o' || matrix[0][0]=='O') && (matrix[1][1]=='o' || matrix[1][1]=='O') && (matrix[2][2]=='o' || matrix[2][2]=='O') && (matrix[3][3]=='o' || matrix[3][3]=='O')){
				winner='O';
				return true;
			}else if((matrix[0][3]=='x' || matrix[0][3]=='X') && (matrix[1][2]=='x' || matrix[1][2]=='X') && (matrix[2][1]=='x' || matrix[2][1]=='X') && (matrix[3][0]=='x' || matrix[3][0]=='X')){
				winner='X';
				return true;
			}else if((matrix[0][3]=='o' || matrix[0][3]=='O') && (matrix[1][2]=='o' || matrix[1][2]=='O') && (matrix[2][1]=='o' || matrix[2][1]=='O') && (matrix[3][0]=='o' || matrix[3][0]=='O')){
				winner='O';
				return true;
			}
			
			return false;
		}
		bool isFinised(){
			if(isWinner()){
				cout<<"Game Finish. Winner:"<<winner<<" Team";
				return true;
			}
			else if(Board::checkForMove()){
				cout<<"Game ended in a draw";
				return true;
			}
			else
				return false;
				
		}
		int calculateIndexRow(int index){return index/4;} 
		int calculateIndexCol(int index){return index%4;}
		void  drawBoard(int index){
			Board::draw(calculateIndexRow(index-1),calculateIndexCol(index-1));
		}
		void printBoard(){Board::printBoard();}
		bool play (int index){
			
			drawBoard(index);
			
			if(isFinised()){
				Board::printBoard();
				return false;
			}else{
				Board::printBoard();
				return true;
			}
		}
		void reset (){
			Board::newBoard();
		}
		
		void analysis(){
			system("CLS");
			cout<<"Team\t\%Row\t\t\%Column\t\t\%Diagonal"<<endl;
			cout<<"Xx   \t"<<(Board::getUseX()*100)/16<<"\t\t"<<(Board::getUseX()*100/16)<<"\t\t"<<(Board::getUseDiagX()*100)/8<<endl;
			cout<<"Oo   \t"<<(Board::getUseO()*100)/16<<"\t\t"<<(Board::getUseO()*100/16)<<"\t\t"<<(Board::getUseDiagO()*100)/8<<endl;
			cout<<"Xx   \t"<<Board::getUseX()<<"\t\t"<<Board::getUseX()<<"\t\t"<<Board::getUseDiagX()<<endl;
			cout<<"Oo   \t"<<Board::getUseO()<<"\t\t"<<Board::getUseO()<<"\t\t"<<Board::getUseDiagO()<<endl;
			
		}
		
		
};

/*statistics
100*number of lines/16
100*number of columns/16
100*number of diagonals/8
*/
/*
get the move
Check the space it puts
put the move
Check if the game is over
press the board to the screen.
*/


int getMove(){
	int sayi;
	
	cout<<"Enter number:"<<endl;
	cin>>sayi;
	system("CLS");
	
	return sayi;
}

int printMenu(){
	int index;
	cout<<"Welcome to TicTacToe Game."<<endl<<endl;
	cout<<"1)Start Game"<<endl;
	cout<<"2)See analysis of last game"<<endl;
	cout<<"3)See the board for the last game"<<endl;
	cout<<"4)Reset the game to play again"<<endl;
	cout<<"5)Get out of the game"<<endl;
	cout<<"Please what you wanted. Enter the number of the option.:";
	cin>>index;
	system("CLS");
	return index;
}

void waitForEnter(){
	cout<<endl<<"Press a key to continue.";
	getch();
	system("CLS");	
}



int main(void)
{
	Game Game;
	int sayi,menu;
	
	

	while(1){
		
		menu=printMenu();
		
		switch(menu){
			case 1:
				Game.printBoard();
				do{
					sayi=getMove();
				}while(Game.play(sayi));
				waitForEnter();			
				break;
			case 2:
				Game.analysis();
				waitForEnter();
				break;
			case 3:
				Game.printBoard();
				waitForEnter();
				break;
			case 4:
				Game.reset();
				cout<<"The game has been reset, restart it."<<endl;
				waitForEnter();
				break;
			case 5:
				return 0;
				break;
			default:
				cout<<"Please enter a valid number.";
				break;
		}
	}

	
	
	return 0;
}













