
#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>

class account
{
	int acnum;
	char acname[50];
	int deposit;
	char type;


public:

	void create_account() //function to get data from user
	{
		std::cout << "\nEnter The account No. :";
		std::cin >> acnum;
		std::cout << "\n\nEnter The Name of The account Holder : ";
		std::cin.ignore();
		std::cin.getline(acname, 50);
		std::cout << "\nEnter Type of The account (C/S) : ";
		std::cin >> type;
		type = toupper(type);
		std::cout << "\nEnter The Initial amount(>=500 for Saving and >=1000 for current ) : ";
		std::cin >> deposit;
		std::cout << "\n\n\nAccount Created..";
	}

	const void show_account() //function to show data on screen
	{
		std::cout << "\nAccount No. : " << acnum;
		std::cout << "\nAccount Holder Name : ";
		std::cout << acname;
		std::cout << "\nType of Account : " << type;
		std::cout << "\nBalance amount : " << deposit;
	}


	void modify() //function to add new data
	{
		std::cout << "\nAccount No. : " << acnum;
		std::cout << "\nModify Account Holder Name : ";
		std::cin.ignore();
		std::cin.getline(acname, 50);
		std::cout << "\nModify Type of Account : ";
		std::cin >> type;
		type = toupper(type);
		std::cout << "\nModify Balance amount : ";
		std::cin >> deposit;
	}

	void dep(int x) //function to accept amount and add to balance amount
	{
		deposit += x;
	}

	void draw(int x) //function to accept amount and add to balance amount
	{
		deposit -= x;
	}

	void report() const //function to show data in tabular format
	{
		std::cout << acnum << std::setw(10) << " " << acname << std::setw(10) << " " << type << std::setw(6) << deposit << std::endl;
	}


	int retacnum() const //function to return account number
	{
		return acnum;
	}

	int retdeposit() const //function to return balance amount
	{
		return deposit;
	}

	char rettype() const //function to return type of account
	{
		return type;
	}

};



void intro() // INTRODUCTION FUNCTION
{
	std::cout << "\n\n\n\t  BANK";
	std::cout << "\n\n\tMANAGEMENT";
	std::cout << "\n\n\t  SYSTEM";
	std::cout << "\n\n\n\nMADE BY : your name";
	std::cout << "\n\nSCHOOL : your school name";
	std::cin.get();
}




	void deposit_withdraw(int n, int option) // function to deposit and withdraw amounts
	{
		int amt;
		bool found = false;
		account ac;
				

		std::fstream File;
		File.open("account.dat", std::ios::binary | std::ios::in | std::ios::out);
		if (!File)
		{
			std::cout << "File could not be open !! Press any Key...";
			return;
		}
		while (!File.eof() && found == false)
		{
			File.read(reinterpret_cast<char*> (&ac), sizeof(account));
			if (ac.retacnum() == n)
			{
				ac.show_account();
				if (option == 1)
				{
					std::cout << "\n\n\tTO DEPOSITE AMOUNT ";
					std::cout << "\n\nEnter The amount to be deposited";
					std::cin >> amt;
					ac.dep(amt);
				}
				if (option == 2)
				{
					std::cout << "\n\n\tTO WITHDRAW AMOUNT ";
					std::cout << "\n\nEnter The amount to be withdraw";
					std::cin >> amt;
					int bal = ac.retdeposit() - amt;
					if ((bal < 500 && ac.rettype() == 'S') || (bal < 1000 && ac.rettype() == 'C'))
						std::cout << "Insufficience balance";
					else
						ac.draw(amt);
				}
				int pos = (-1) * static_cast<int>(sizeof(ac));
				File.seekp(pos, std::ios::cur);
				File.write(reinterpret_cast<char*> (&ac), sizeof(account));
				std::cout << "\n\n\t Record Updated";
				found = true;
			}
		}
		File.close();
		if (found == false)
			std::cout << "\n\n Record Not Found ";
	}



	void display_all() // function to display all accounts deposit list
	{
		account ac;
		std::ifstream inFile;
		inFile.open("account.dat", std::ios::binary);
		if (!inFile)
		{
			std::cout << "File could not be open !! Press any Key...";
			return;
		}
		std::cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
		std::cout << "====================================================\n";
		std::cout << "A/c no.      NAME           Type  Balance\n";
		std::cout << "====================================================\n";
		while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
		{
			ac.report();
		}
		inFile.close();
	}

	void delete_account(int n) //function to delete record of file
	{
		account ac;
		std::ifstream inFile;
		std::ofstream outFile;
		inFile.open("account.dat", std::ios::binary);
		if (!inFile)
		{
			std::cout << "File could not be open !! Press any Key...";
			return;
		}
		outFile.open("Temp.dat", std::ios::binary);
		inFile.seekg(0, std::ios::beg);
		while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
		{
			if (ac.retacnum() != n)
			{
				outFile.write(reinterpret_cast<char*> (&ac), sizeof(account));
			}
		}
		inFile.close();
		outFile.close();
		remove("account.dat");
		rename("Temp.dat", "account.dat");
		std::cout << "\n\n\tRecord Deleted ..";
	}

	void modify_account(int n)  // function to modify record of file
	{
		bool found = false;
		account ac;
		std::fstream File;
		File.open("account.dat", std::ios::binary | std::ios::in | std::ios::out);
		if (!File)
		{
			std::cout << "File could not be open !! Press any Key...";
			return;
		}
		while (!File.eof() && found == false)
		{
			File.read(reinterpret_cast<char*> (&ac), sizeof(account));
			if (ac.retacnum() == n)
			{
				ac.show_account();
				std::cout << "\n\nEnter The New Details of account" << std::endl;
				ac.modify();
				int pos = (-1) * static_cast<int>(sizeof(account));
				File.seekp(pos, std::ios::cur);
				File.write(reinterpret_cast<char*> (&ac), sizeof(account));
				std::cout << "\n\n\t Record Updated";
				found = true;
			}
		}
		File.close();
		if (found == false)
			std::cout << "\n\n Record Not Found ";
	}

	void display_sp(int n) //function to read specific record from file
	{ 
		account ac;
		bool flag = false;
		std::ifstream inFile;
		inFile.open("account.dat", std::ios::binary);
		if (!inFile)
		{
			std::cout << "File could not be open !! Press any Key...";
			return;
		}
		std::cout << "\nBALANCE DETAILS\n";

		while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
		{
			if (ac.retacnum() == n)
			{
				ac.show_account();
				flag = true;
			}
		}
		inFile.close();
		if (flag == false)
			std::cout << "\n\nAccount number does not exist";
	}


	void write_account() //function to write record in  file
	{
		account ac;
		std::ofstream outFile;
		outFile.open("account.dat", std::ios::binary | std::ios::app);
		ac.create_account();
		outFile.write(reinterpret_cast<char*> (&ac), sizeof(account));
		outFile.close();
	}

	int main()
	{
		char ch;
		int num;
		intro();
		do
		{
			system("cls");
			std::cout << "\n\n\n\tMAIN MENU";
			std::cout << "\n\n\t01. NEW ACCOUNT";
			std::cout << "\n\n\t02. DEPOSIT AMOUNT";
			std::cout << "\n\n\t03. WITHDRAW AMOUNT";
			std::cout << "\n\n\t04. BALANCE ENQUIRY";
			std::cout << "\n\n\t05. ALL ACCOUNT HOLDER LIST";
			std::cout << "\n\n\t06. CLOSE AN ACCOUNT";
			std::cout << "\n\n\t07. MODIFY AN ACCOUNT";
			std::cout << "\n\n\t08. EXIT";
			std::cout << "\n\n\tSelect Your Option (1-8) ";
			std::cin >> ch;
			system("cls");
			switch (ch)
			{
			case '1':
				write_account();
				break;
			case '2':
				std::cout << "\n\n\tEnter The account No. : "; std::cin >> num;
				deposit_withdraw(num, 1);
				break;
			case '3':
				std::cout << "\n\n\tEnter The account No. : "; std::cin >> num;
				deposit_withdraw(num, 2);
				break;
			case '4':
				std::cout << "\n\n\tEnter The account No. : "; std::cin >> num;
				display_sp(num);
				break;
			case '5':
				display_all();
				break;
			case '6':
				std::cout << "\n\n\tEnter The account No. : "; std::cin >> num;
				delete_account(num);
				break;
			case '7':
				std::cout << "\n\n\tEnter The account No. : "; std::cin >> num;
				modify_account(num);
				break;
			case '8':
				std::cout << "\n\n\tThanks for using bank managemnt system";
				break;
			default:std::cout << "\a";
			}
			std::cin.ignore();
			std::cin.get();
		} 
		while (ch != '8');
		return 0;
	}
