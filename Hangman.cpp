#include <iostream>
#include <cstdlib>
#include<ctime>
#include <string>

const int MAX_TRIES = 5;

/* Take a one character guess and the secret word, and fill in the
 unfinished guessword. Returns number of characters matched.
 Also, returns zero if the character is already guessed. */

int letterFill(char guess, std::string secretword, std::string& guessword)
{
	int i;
	int matches = 0;
	size_t len = secretword.length();
	for (i = 0; i < len; i++)
	{
		// Did we already match this letter in a previous guess?
		if (guess == guessword[i])
			return 0;
		// Is the guess in the secret word?
		else if (guess == secretword[i])
		{
			guessword[i] = guess;
			matches++;
		}
	}
	return matches;
}

void welcome() {
	std::cout << "\n\nWelcome to hangman...Guess a country Name";
	std::cout << "\n\nEach letter is represented by a star.";
	std::cout << "\n\nYou have to type only one letter in one try";
	std::cout << "\n\nYou have " << MAX_TRIES << " tries to try and guess the word.";
	std::cout << "After you guess the first letter you have an option to guess the word. ";
	std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
}


int main()
{
	char choice = '1';
	std::string name;
	char letter;
	int num_of_wrong_guesses = 0;
	std::string word;
	std::string words[] =
	{
		"india",
		"pakistan",
		"nepal",
		"malaysia",
		"philippines",
		"australia",
		"iran",
		"ethiopia",
		"oman",
		"indonesia"
	};

	//choose and copy a word from array of words randomly
	srand(time(NULL));
	int n = rand() % 10;
	word = words[n];

	std::string hidden(word.length(), '*');
	welcome();

	while (num_of_wrong_guesses < MAX_TRIES)
	{
		
		std::cout << "\n\n" << hidden << std::endl;
		

		while (choice != '1' && choice != '2' )
		{
			
			std::cout << "\n" << "Choose 1 to guess a letter or 2 to guess the word. ";
			std::cin >> choice;
			
		}
		if (choice == '1')
		{
			std::cout << "\nGuess a letter: ";
			std::cin >> letter;
			// Fill secret word with letter if the guess is correct,
			// otherwise increment the number of wrong guesses.
			if (letterFill(letter, word, hidden) == 0)
			{
				std::cout << "Whoops! That letter isn't in there!" << std::endl;
				num_of_wrong_guesses++;
				if (num_of_wrong_guesses == MAX_TRIES)
				{
					std::cout << "\nSorry, you lose...you've been hanged." << std::endl;
					std::cout << "The word was : " << word << std::endl;
					return 0;
				}
				else
				{
					// Tell user how many guesses has left.
					std::cout << "You have " << MAX_TRIES - num_of_wrong_guesses;
					std::cout << " guesses left." << std::endl;

				}

			}
			else
			{
				std::cout << "You found a letter! Isn't that exciting!" << std::endl;
				
			}

			if (word == hidden)
			{
				std::cout << word << std::endl;
				std::cout << "That is correct! You win!" << std::endl;
				return 0;
			}
		}
		else if (choice == '2')
		{
			std::cout << "\n\nGuess the word: ";
			std::cin >> hidden;
			if (word == hidden)
			{
				
				std::cout <<"\nThat is correct! You win!";
				return 0;
			}
			else
			{
				std::cout << "\nWhoops! That is not the word!" << std::endl;
				num_of_wrong_guesses++;
				if (num_of_wrong_guesses == MAX_TRIES)
				{
					std::cout << "\nSorry, you lose...you've been hanged." << std::endl;
					std::cout << "The word was : " << word << std::endl;
					return 0;
				}
				else
				{

					std::cout << "You have " << MAX_TRIES - num_of_wrong_guesses;
					std::cout << " guesses left." << std::endl;

				}

			}
		}
		choice = '0';

	
	}
	
	std::cin.ignore();
	std::cin.get();
	return 0;
}


