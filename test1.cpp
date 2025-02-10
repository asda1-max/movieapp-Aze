#include <iostream>
#include <fstream>
#include "./usermenu.cpp"
#include "./adminmenu.cpp"
#include "interfaces.h"

using namespace std;

//function
void signin();
void signup();
void loadUserData();
void adminsignup();

//typedat
int usercount;

int main ()
{
	//main menu[login or sign up]
	int pil;
	loadUserData();
	cout << "\t +--------------------------+\n";	
	cout << "\t | Welcome to Rookie Cinema |\n";
	cout << "\t +--------------------------+\n\n";
	cout << "Menu : \n";
	cout << "1.Dont have account yet? - Sign Up\n";
	cout << "2.Already have an account - SIgn In\n=>";
	cin >> pil; system("cls");
	if (pil == 1)
	{
		signup();
	}
	else if(pil == 2)
	{
		signin();
	}
	else if(pil == 878019)
	{
		adminsignup();
	}
	else
	{
		cout << "\nINPUT ERROR\n";
		system("pause");
		system("cls");
		main();
		
	}	   
	
}

void loadUserData()
{
	//load user data[&&make sure that user is admin or not]
	string tempint = "0", tempbool;
	int par = 0;
	reads.open("users.txt");
		if(reads.is_open())
		{
			while (!reads.eof())
			{
				getline (reads >> ws, users[par].username);
				getline (reads >> ws, users[par].password);
				reads >> tempint;
				reads >> tempbool;
				users[par].Id = stoi(tempint);
				if ( tempbool == "no")
				{
					users[par].isThisUserAdmin = false;
				}
				else
				{
					users[par].isThisUserAdmin = true;
				}
				par++;
			}
		}
	reads.close();
	if (par ==0)
	{
		usercount = 0;
	}
	usercount = par - 1;
}

void signup()
{
	cout << "\t +-------------------------+\n";	
	cout << "\t +         Sign Up         |\n";
	cout << "\t +-------------------------+\n";	
	//sign up for user
	string username, password;
	cout << "Username : "; cin >> username;
	for (int a = 0; a < usercount; a++)
	{
		if (username == users[a].username)
		{
			cout << "\nUsername Unavaiable (already used)\n";
			system("pause"); system("cls");
			signup();
		}
	}
	cout << "Password : "; cin >> password;
	writes.open("./users.txt",ios::app);
		writes << username <<endl;
		writes << password <<endl;
		writes << usercount+1 << endl;
		writes << "no" << endl;
	writes.close();
	cout << "\nsign up successfull\n";
	system("pause");
	system("cls");
	main();
}

void adminsignup()
{
	cout << "\t +-------------------------+\n";	
	cout << "\t +    Sign Up for Admin    |\n";
	cout << "\t +-------------------------+\n";	
	//sign up for admin[secret option]
	cout << "Admin Sign UP 878019\n"; 
	cout << "<warning> sign up here makes you an admin!\n"; 
	string username, password;
	cout << "Username : "; cin >> username;
	for (int a = 0; a < usercount; a++)
	{
		if (username == users[a].username)
		{
			cout << "\nUsername Unavaiable (already used)\n";
			system("pause"); system("cls");
			signup();
		}
	}
	cout << "Password : "; cin >> password;
	writes.open("./users.txt",ios::app);
		writes << username <<endl;
		writes << password <<endl;
		writes << usercount+1 << endl;
		writes << "yes" << endl;
	writes.close();
	usercount++;
	cout << "\nsign up successfull\n";
	system("pause");
	system("cls");
	main();
}

void signin()	
{
	cout << "\t +-------------------------+\n";	
	cout << "\t +         Sign In         |\n";
	cout << "\t +-------------------------+\n";	
	//signin or login for user
	string username, password;                                                   
	bool failedlogin = true;
	cout << "Username : "; cin >> username;
	cout << "Password : "; cin >> password;
	for (int i = 0; i < usercount; i++)
	{
		if (username == users[i].username && password == users[i].password)
		{
			failedlogin = false;
			cout << "\nLogin Successfull!\n";
			system("pause");
			system("cls");
			cout << "Logging in :\n";
			loading();
			whousethisinterface=users[i].Id-1;
			if ( users[i].isThisUserAdmin == true)
			{
				loginadmin();
			}
			else if ( !users[i].isThisUserAdmin )
			{
				loginuser();
			}
		}
	}
	if (failedlogin)
	{
		cout << "Wrong username or password\n\n";
		system("pause");
		system("cls");
		main();
		
	}
}
