#include <iostream>
#include "CreateAndSearchCatalog.h"
#include "issueBook.h"
#include "User.h"


int main()
{
	std::tuple<std::vector<std::string>, std::vector<int>> catalog;
	std::tuple<std::vector<std::string>, std::vector<std::string>> searchResult;
	std::tuple<std::string, unsigned long long> userData;
	char userResponse;
	bool registered = false;
	bool alreadyIssued;
	bool isEmpty;
	bool repeat = true;
	int bookIndex;
	unsigned long long userId{ 0 };
	std::string search;
	std::string bookToIssue;
	std::string group;
	std::string userFirst;
	std::string userLast;

	std::cout << "Is it your first time running this program?" << '\n' << "Y : Yes" << '\n' << "N : No"
		<< std::endl;
	std::cin >> userResponse;

	if (userResponse == 'Y' || userResponse == 'y')
	{
		catalog = CreateAndSearchCatalog::checkData(true);
	}
	else if (userResponse == 'N' || userResponse == 'n')
	{
		catalog = CreateAndSearchCatalog::checkData(false);
	}
	std::string discard;
	std::cout << "Enter the name of the book you would like to search: " << std::endl;
	std::getline(std::cin, discard); // to remove the \n which was still in the input buffer and not letting me take input
	std::getline(std::cin, search);  // get line reads till it finds the \n character
	

	CreateAndSearchCatalog user = CreateAndSearchCatalog(search);
	searchResult = user.searchBook(&catalog);
	isEmpty = user.displaySearchResults(&searchResult);
	
	while (repeat)
	{
		if (isEmpty)
		{
			std::cout << "Would you like to search another book ?" << std::endl << "Y: For yes" << std::endl
				<< "N: For no" << std::endl;
			std::cin >> userResponse;
			if (userResponse == 'Y' || userResponse == 'y')
			{
				std::string discard;
				std::cout << "Enter the name of the book you would like to search: " << std::endl;
				std::getline(std::cin, discard); // to remove the \n which was still in the input buffer and not letting me take input
				std::getline(std::cin, search);  // get line reads till it finds the \n character


				CreateAndSearchCatalog user = CreateAndSearchCatalog(search);
				searchResult = user.searchBook(&catalog);
				isEmpty = user.displaySearchResults(&searchResult);
				repeat = true;
			}
			else if (userResponse == 'N' || userResponse == 'n')
			{
				repeat = false;
				continue;
			}

		}
		else
		{
			repeat = false;
			break;
		}
	}
	if (isEmpty)
	{
		std::cout << "Have a good day";
	}
	else
	{
		std::cout << '\n' << "Enter the initials of the group followed by the index number of the book you want to issue " << '\n'
			<< "Pe for perfect" << '\n' << "Pa for partial: ";
		std::cin >> group >> bookIndex;

		bookToIssue = user.finalizeBook(&searchResult, group, bookIndex);

		std::cout << "Are you registered with this library?" << std::endl << "Y for Yes" << std::endl << "N for No: ";
		std::cin >> userResponse;

		if (userResponse == 'Y' || userResponse == 'y')
		{
			registered = true;
			std::cout << "Please enter your full name: ";
			std::cin >> userFirst >> userLast;
			std::cout << "Please enter your user id: ";
			std::cin >> userId;
		}
		else if (userResponse == 'N' || userResponse == 'n')
		{
			std::cout << "Please enter your full name: ";
			std::cin >> userFirst >> userLast;
			registered = false;
		}

		User mate = User(registered, userFirst, userLast, userId);
		if (registered)
		{
			userData = mate.findUserInDatabase();
		}
		else if (!registered)
		{
			mate.addUserToDatabase();
			userData = mate.findUserInDatabase();
		}
		IssueBook final = IssueBook();
		alreadyIssued = final.finalizeProcess(&userData, bookToIssue);
		if (alreadyIssued)
		{
			std::cout << "Would you like to return your issued book ?" << std::endl;
			std::cout << "Y for yes" << '\n' << "N for no" << '\n';
			std::cin >> userResponse;
			if (userResponse == 'Y' || userResponse == 'y')
			{
				final.returnBook(&userData);
			}
			else if (userResponse == 'N' || userResponse == 'n')
			{
				std::cout << "You will not be able to issue another book without returning the book first";
				std::cout << "Good bye";
			}
		}
	}
	

	
	return 0;
}
