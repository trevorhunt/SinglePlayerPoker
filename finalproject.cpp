/* Trevor Hunt
Lab 10
April 22 2020
CECS 130-02
This is single player poker*/

#include<iostream>
#include<ctype.h>
#include<cstdlib>
#include<ctime>
#include<string>

using namespace std;

class CardClass{
	public:
		int num[4];
		int temp1;
		string suit[4], temp2;
		int fourofkind, straightflush, flush, straight, threeofkind, twopair, pear, bubkiss;
		int balance, bet;
		
		void newhand(){
			temp1 = 0; temp2 = "";
			suit[0] = ""; suit[1] = ""; suit[2] = ""; suit[3] = "";
			for(int i = 0; i <= 3; i++){
				do{		//generate a unique card
					temp1 = ((rand() % 13) + 1);		//random number
					temp2 = (rand() % 4) + 49;		//random suit
					if(temp2.compare("1") == 0){		//assign suits
						temp2 = "C";
					}
					else if(temp2.compare("2") == 0){
						temp2 = "S";
					}
					else if(temp2.compare("3") == 0){
						temp2 = "D";
					}
					else if(temp2.compare("4") == 0){
						temp2 = "H";
					}
				}while((temp1 == num[1] && temp2.compare(suit[1]) == 0) && (temp1 == num[2] && temp2.compare(suit[2]) == 0) && (temp1 == num[3] && temp2.compare(suit[3]) == 0));
				
				num[i] = temp1;
				suit[i] = temp2;
			}
			for(int x = 0; x <= 3; x++){		//sorting cards
				for(int counter = 0; counter <= 3 - x; counter++){
					if(num[counter] > num[counter + 1]){
						temp1 = num[counter];
						num[counter] = num[counter + 1];
						num[counter + 1] = temp1;
						swap(suit[counter], suit[counter + 1]);
					}
				}
			}
			printhand();
		}
		void printhand(){		//print the outcome
			for(int w; w <= 3; w++){
				if(num[w] == 1){cout << "A";}
				else if(num[w] == 11){cout << "J";}
				else if(num[w] == 12){cout << "Q";}
				else if(num[w] == 13){cout << "K";}
				else{cout << num[w];}
				cout << suit[w] << " ";
			}
			cout << endl;
		}
		void checkhand(){		//check for wins and losses
			if(num[0] == num[1] && num[1] == num[2] && num[2] == num[3]){
				fourofkind++;
				balance = balance + 401 * bet;
				cout << "Congragulations! You got a four of a kind to win $" << bet * 400 << endl;
				
			}
			else if((suit[0] == suit[1] && suit[1] == suit[2] && suit[2] == suit[3]) && (num[0] == num[1] - 1 && num[1] == num[2] - 1 && num[2] == num[3] - 1)){
				straightflush++;
				balance = balance + 301 * bet;
				cout << "Congragulations! You got a straight flush to win $" << bet * 300 << endl;
			}
			else if(suit[0] == suit[1] && suit[1] == suit[2] && suit[2] == suit[3]){
				flush++;
				balance = balance + 251 * bet;
				cout << "Congragulations! You got a flush to win $" << bet * 250 << endl;
				
			}
			else if(num[0] == num[1] - 1 && num[1] == num[2] - 1 && num[2] == num[3] - 1){
				straight++;
				balance = balance + 201 * bet;
				cout << "Congragulations! You got a straight to win $" << bet * 200 << endl;
				
			}
			else if((num[0] == num[1] && num[1] == num[2]) || (num[1] == num[2] && num[2] == num[3])){
				threeofkind++;
				balance = balance + 151 * bet;
				cout << "Congragulations! You got a three of a kind to win $" << bet * 150 << endl;
				
			}
			else if((num[0] == num[1] && num[2] == num[3])){
				twopair++;
				balance = balance + 101 * bet;
				cout << "Congragulations! You got a two pair to win $" << bet * 100 << endl;
				
			}
			else if(num[0] == num[1] || num[1] == num[2] || num[2] == num[3]){
				pear++;
				balance = balance + 2 * bet;
				cout << "Congragulations! You got a pair to win $" << bet << endl;
				
			}
			else{
				bubkiss++;
				cout << "Sorry, you got bubkiss. You losing your bet of $" << bet << endl;
			}
		}
		void report(){		//print wins and losses
			cout << "You have played " << fourofkind + straightflush + flush + straight + threeofkind + twopair + pear + bubkiss << " hands:" << endl;
			cout << "Wins: " << fourofkind + straightflush + flush + straight + threeofkind + twopair + pear << endl;
			cout << "\tFour of a Kind: " << fourofkind << endl;
			cout << "\tStraight Flush: " << straightflush<< endl;
			cout << "\tFlush: " << flush << endl;
			cout << "\tStraight: " << straight << endl;
			cout << "\tThree of a Kind: " << threeofkind << endl;
			cout << "\tTwo Pair: " << twopair << endl;
			cout << "\tPair: " << pear << endl;
			cout << "Losses: " << bubkiss << endl << endl;
			cout << "Current profit $" << balance - 100 << endl << endl;
		}
		
};

int main(){
	
	string replay = "yes";
	CardClass poker;
	poker.balance = 100;
	poker.pear = 0;
	int stop = 0;
	
	cout << "Welcome to Single Player Poker\nYour starting balance is $100\n" << endl;
	
	do{
		if(poker.balance == 0){		//only while player has chips
			cout << "\nYou are out of chips\n\tBetter luck next time" << endl << endl;
			replay = "No";
		}
		else{
			if(replay == "Yes" || replay == "yes" || replay == "y"){		//asks for bets and generates hands
				srand(time(0));
				cout << "Shuffling Deck\nPlace your bet[1, " << poker.balance <<"]: ";
				cin >> poker.bet;
				while(poker.bet > poker.balance){
					cout << "You only can bet what you have\nPlace your bet[1, " << poker.balance <<"]" << endl;
					cin >> poker.bet;
				}
				poker.balance = poker.balance - poker.bet;
				poker.newhand();
				poker.checkhand();
				if(poker.balance == 0){
					replay = "Yes";
				}
				else{
					cout << "Play again? (yes, no, or report): ";
					cin >> replay;
					cout << endl;	
				}
			}
			else if(replay == "No" || replay == "no" || replay == "n"){
				return 0;
			}
			else if(replay == "report" || replay == "Report"){		//gives report
				poker.report();
				cout << "Play again? (yes, no, or report): ";
				cin >> replay;
				cout << endl;
			}
			else{		//if the player gives an invalid response
				cout << "Please enter a valid input" << endl;
				cout << "Play again? (yes, no, or report): ";
				cin >> replay;
				cout << endl;
			}
		}
	}while((replay != "No") && (replay != "no") && (replay != "n"));
	cout << "Thank you for playing" << endl;
	poker.report();		//final report
	cout << "You leave $" << poker.balance - 100 << " richer";
	return 0;
}

