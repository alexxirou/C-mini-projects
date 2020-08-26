#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>



static void drawLine(int n, char symbol)
{
	for (int i = 0; i < n; i++)
		std::cout << symbol;
	std::cout << "\n";

}

class Player {
public:
	std::string playerName;
	int balance;
	int bettingAmount;
	int guess;
	int dice;

	Player() {
		playerName = "Player";
		static int balance = 0;
		bettingAmount = 0;
		guess = 0;
		dice = 0;
		createProfile();
	}


	void createProfile() {
		std::cout << "Please enter a player name: ";
		std::cin >> playerName;
	
	}


};



class Menu : public Player {

public:
	int choice;

	Menu() {
	 static	int choice = 1;
	 int *ptrguess = &guess;
	 int *ptrdice = &dice;
	 //std::cout << *ptrguess;
	 //std::cout << *ptrdice;
		while (choice == 1) {

			rules();
			std::cout << "\n";
			std::cout << "Choose 1 to read the rules again, 2 to play the game, or 3 to quit: ";
			std::cin >> choice;

			while (choice !=1 && choice != 2 && choice != 3) {
				std::cout << "Choose 1 to read the rules again, 2 to play the game, or 3 to quit: ";
				std::cin >> choice;
			}
		}
		while (choice == 2) {
			while (balance <= 0) {
				std::cout << "Please enter a balance amount larger than 0: ";
				std::cin >> balance;
			}
			
			while (bettingAmount <= 0 || bettingAmount > balance) {
				std::cout << "Choose a valid betting ammount, less or equal to your balance: ";
				std::cin >> bettingAmount;
			}
			
			*ptrdice = rand() % 10 + 1; // Will hold the randomly generated integer between 1 and 10
			//std::cout << *ptrdice;
			while (*ptrguess <= 0 || *ptrguess > 10) {
				std::cout << "Pick a valid number to bet on between 1 to 10 : ";
				std::cin >> *ptrguess;
				//std::cout << *ptrguess;
			}
			if (*ptrdice == *ptrguess) {
				balance = balance + (10 * bettingAmount);
				bettingAmount = 0;
				std::cout << "You win! Your current balance is: " << balance << std::endl;
				std::cout << "\n";
			}
			else {
				balance = balance - bettingAmount;
				bettingAmount = 0;
				std::cout << "Wrong you lose your betting amount. Your current balance is: " << balance << std::endl;
				std::cout << "\n";
				if (balance == 0) {
					std::cout << "You lost all your munny, get out... "<< std::endl;
					std::cout << "\n";
					return;
				}
			}
			*ptrguess = 0;
			std::cout << "Choose 2 to keep playing, or 3 to grab your munny and run away: ";
			std::cin >> choice;
			//std::cout << *ptrguess;


			while (choice != 2 && choice != 3) {
				std::cout << "Choose 2 to keep playing, or 3 to grab your munny and run away: ";
				std::cin >> choice;
			}
		}	

		if (choice == 3) {
			std::cout << "Thank you for playing " << playerName <<"!" << std::endl;
			std::cout << "\n";
			return;
		}
	
	}

private:
	void rules()
	{
		system("cls");
		std::cout << "\n\n";
		drawLine(80, '-');
		std::cout << "\t\tRULES OF THE GAME\n";
		drawLine(80, '-');
		std::cout << "\t1. Choose any number between 1 to 10\n";
		std::cout << "\t2. If you win you will get 10 times of money you bet\n";
		std::cout << "\t3. If you bet on wrong number you will lose your betting amount\n\n";
		drawLine(80, '-');
	}
};



int main() {
	drawLine(60, '_');
	std:: cout << "\n\n\n\t\tCASINO GAME\n\n\n\n";
	drawLine(60, '_');
	std::cout << "Player1"<<"\n";
	Menu Player1;
	std::cout << "Player2" << "\n";
	Menu Player2;
	
}
