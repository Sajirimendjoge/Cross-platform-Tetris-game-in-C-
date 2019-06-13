#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>

#include "Player.h"

#define CREDENTIAL_FILENAME "Player_Credentials"

bool display_menu(class Player* user)
{
	unsigned int choice = 0;
	bool result = true;

	while(1)
	{
		std::system(OS_DEP_CLEAR);
		std::cout<<"-----------------------"<<std::endl;
		std::cout<<"    Selection Menu     "<<std::endl;
		std::cout<<"-----------------------"<<std::endl;
		std::cout<<"1 - Player registration"<<std::endl;
		std::cout<<"2 - Player login	   "<<std::endl;
		std::cout<<"3 - Exit               "<<std::endl;
		std::cout<<"-----------------------"<<std::endl;
		std::cout<<"Enter you choice: ";
		std::cin>>choice;

		if(choice > 3)
		{
			std::cout<<"Invalid choice provided\n"<<std::endl;
			std::cout<<"Press enter to retry";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		switch(choice)
		{
			case 1:
				result = user->register_player();
				break;
			case 2:
				result = user->verify_player_cred();
				break;
			case 3:
				result = false;
				break;
		}
		break;
	}

	return result;
}

bool Player::register_player()
{
	std::ofstream credFile (CREDENTIAL_FILENAME, std::ios::out | std::ios::app);
	
	if(!credFile.is_open())
	{
		std::cout<<"Failed to open credentials file."<<std::endl;
		return false;
	}

	get_credentials();	

	credFile << username << " " << password << " " << 0 << std::endl;

	std::cout << "Player successfully registered.\n" << "Press enter to continue." << std::endl;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return true;
}

bool Player::verify_player_cred()
{
	std::string name, passwd;
	unsigned int score;
	bool result = false;
	std::string line;

	std::ifstream credFile (CREDENTIAL_FILENAME, std::ios::in);

	if(!credFile.is_open())
	{
		std::cout<<"Failed to open credentials file."<<std::endl;
		return false;
	}

	get_credentials();

	while(getline(credFile, line))
	{
		std::istringstream buf(line);
		buf>>name>>passwd>>score;
		if(name == username && passwd == password)
		{
			result = true;
			max_score = score;
			std::cout<<"Login successfull."<<std::endl;
			break;
		}
	}

	if(result == false)
		std::cout<<"Login failed."<<std::endl;

	return result;
}

void Player::get_credentials()
{
	std::cout<<"Enter username: ";
	std::cin>>username;
	std::cout<<std::endl<<"Enter password: ";
	std::cin>>password;
	std::cout<<std::endl;
}

std::string Player::get_name()
{
    return username;
}

unsigned int Player::get_max_score()
{
    return max_score;
}

void Player::set_max_score(unsigned int maxScore)
{
    max_score = maxScore;
}

Player::Player()
{
    max_score = 0;
}

Player::~Player()
{
    //write back to the file.
}

