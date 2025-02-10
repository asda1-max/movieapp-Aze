#include <iostream>
#include <fstream>
#include "interfaces.h"

using namespace std;

void addM();
void manageM();
void delM();
void searchU();
void changenames(int changes, string tempo,string old);
void writeSynopsis(string mvsName);


void loginadmin()
{
	checkmovies();
	system("cls");
	int pil;
	cout << "Admin Menu :\n1.Add Movie\n2.Manage Movie\n3.Delete Movie\n4.search user\n5.Log Out\n=>";
	cin >> pil; system("cls");
	switch (pil)
	{
		case 1: addM(); break;
		case 2: manageM(); break;
		case 3: delM(); break;
		case 4: searchU(); break;
		case 5: cout << "Logging off : \n"; loading(); main();
		default : system("cls"); loginadmin();
		break;
	}
}

void addM()
{
	string mvsName;
	string mvsSchedule;
	int duration;
	cout << "\t +-------------------------+\n";	
	cout << "\t +       Add a Movie       |\n";
	cout << "\t +-------------------------+\n";	
	cout << "Movie Name                      : "; 
	getline (cin >> ws, mvsName);
		
	for (int i = 0; i < movieCount; i++)
	{
		if (mvsName == movies[i].name)
		{
			cout << "\nMovie with that name is already existed\n";
			system("pause"); system("cls");
			addM();
		}	
	}
	
			
	cout << "Movie Schedule                  : "; getline (cin >> ws, mvsSchedule);
	cout << "Movie Duration (int in minutes) : "; cin >> duration;
	writes.open("./movies/movielist.txt", ios::app);
		writes << mvsName << endl;
		writes << mvsSchedule << endl;
		writes << duration << endl;
	writes.close();
	cout << "\n\t\t<WRITE THE SYNOPSIS>" << endl;
	writeSynopsis(mvsName);
	system("pause"); system("cls");
	loginadmin();
	
}

void manageM()
{
	system("cls");
	string old_name;
	cout << "\t +-------------------------+\n";	
	cout << "\t +      Manage a Movie     |\n";
	cout << "\t +-------------------------+\n";	
	string temporaryVal;
	string movienam;
    cout << "Movies List:\n============================\n";
        for (int i = 0; i < movieCount; i++) {
        cout << i + 1 << ". " << movies[i].name << endl;
        }
    cout << "============================\n";
    cout << "Enter the Name of the movie to manage: ";
    getline(cin >> ws, movienam);

    int movieId = -1; 
    for (int i = 0; i < movieCount; i++) {
        if (movies[i].name == movienam) {
            movieId = i; 
            break;
        }
    }

    if (movieId != -1) { 
        cout << "Managing Movie: " << movies[movieId].name << endl;
        cout << "1. Edit Name\n2. Edit movie schedule\n3. Edit Duration\n4. Edit Synopsis\n=> ";
        int choice;
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1:
                cout << "Enter new name: ";
                getline(cin >>ws, temporaryVal);
                old_name = movies[movieId].name;
                changenames(movieId, temporaryVal, old_name);
                movies[movieId].name = temporaryVal;
                break;
            case 2:
				cout << "Enter new schedule: ";
                getline (cin >> ws, movies[movieId].schedule);
                break;
            case 3:
                cout << "Enter new duration: ";
                cin >> movies[movieId].duration;
                break;
            case 4:
                cout << "Enter new synopsis: ";
                writeSynopsis(movies[movieId].name                                                                                                                                                                                                                                                                                                                                                                                                                                        );
                break;
            default:
                cout << "Invalid choice!\n";
                break;
        }
        cout << "Movie details updated successfully!\n";
         
    } 
    else 
    {
        cout << "Movie not found!\n\n";
        system("pause"); system("cls");
        loginadmin();
    }
    
    remove("./movies/movielist.txt");
    for (int i = 0; i < movieCount; i++)
	{
		writes.open("./movies/movielist.txt",ios::app);
			writes << movies[i].name << endl;
			writes << movies[i].schedule << endl;
			writes << movies[i].duration << endl;
		writes.close();
	}
    system("pause"); system("cls");
    loginadmin();
}


void delM()
{  
	cout << "\t +-------------------------+\n";	
	cout << "\t +      Delete a Movie     |\n";
	cout << "\t +-------------------------+\n\n";	
	cout << "Movies List:\n============================\n";
        for (int z = 0; z < movieCount; z++) {
        cout << z + 1 << ". " << movies[z].name << endl;
        }
    cout << "============================\n";
    string movienam;
    cout << "Enter the Name of the movie to manage: ";
    getline(cin >> ws, movienam);

    int movieId = -1; 
    for (int i = 0; i < movieCount; i++) {
        if (movies[i].name == movienam) {
            movieId = i; 
            break;
        }
    }
    if (movieId != -1)
    {
		remove("./movies/movielist.txt");
		remove(("./movies/reviews/" + movies[movieId].name + " review.txt").c_str());
		remove(("./movies/synopsis/" + movies[movieId].name + ".txt").c_str());
		remove(("./movies/seat/" + movies[movieId].name + " seat.txt").c_str());
		for (int i = 0; i < movieCount; i++)
		{
			if(movies[i].name != movies[movieId].name)
			{
				writes.open("./movies/movielist.txt",ios::app);
					writes << movies[i].name << endl;
					writes << movies[i].schedule << endl;
					writes << movies[i].duration << endl;
				writes.close();
			}
		}
        cout << "Movie deleted successfully!\n";
    } 
    else 
    {
        cout << "Movie not found!\n";
    }
    system("pause"); system("cls");
    loginadmin();
}

void writeSynopsis(string mvsName)
{
	string mvsSyn;
	bool looping = true;
	writes.open(("./movies/synopsis/" + mvsName + ".txt").c_str());
		cout << "Write a synopsis for movie : " << mvsName << "!\n";
		while(looping == true)
		{
			cout << "\t";
			getline (cin >> ws, mvsSyn);
			if(mvsSyn != "---")
			{
				writes << mvsSyn << endl;
			}
			else
			{
				looping = false;
			}
		}
	writes.close();
}

void changenames(int changes, string tempo, string old)
{
	int loops = 0, lups = 0, total_lines;
	string ratex[100], commentY[100], users[100],synopsis[100];
	checkseat(changes);
	writes.open(("./movies/seat/" + tempo + " seat.txt").c_str(),ios::app);
		for (int i = 0; i < 161; i++)
		{
			if ( movies[changes].bioskop[i].terpesan == true)
			{
				writes << i << endl;
				writes << movies[changes].bioskop[i].kursi  << endl;
				writes << movies[changes].bioskop[i].whobook << endl;
			}
		}
	writes.close();
	
	reads.open(("./movies/synopsis/" + old + ".txt").c_str());
		while(!reads.eof())
		{
			getline(reads >> ws, synopsis[lups]);
			lups++;
		}
	reads.close();
	
	total_lines = lups -1;
	
	writes.open(("./movies/synopsis/" + tempo + ".txt").c_str(), ios::app);
	{
		for (int i = 0; i < total_lines; i++)
		{
			writes << synopsis[i] << endl;
		}
	}
	writes.close();
	
	reads.open(("./movies/reviews/" + old + " review.txt").c_str());
		if(reads.is_open())
		{
			while(!reads.eof())
			{
				getline (reads >> ws, ratex[loops]);
				getline (reads >> ws, commentY[loops]);
				getline (reads >> ws, users[loops]);
				loops++;
			}
		}
		movies[changes].totalreview = loops -1;
		reads.close();
	
	writes.open(("./movies/reviews/" + tempo + " review.txt").c_str(),ios::app);
		for (int i = 0; i < movies[changes].totalreview; i++)
		{
			writes << ratex[i] << endl;
			writes << commentY[i]  << endl;
			writes << users[i] << endl;
		}
	writes.close();
	
	remove(("./movies/reviews/" + old + " review.txt").c_str());
	remove(("./movies/synopsis/" + old + ".txt").c_str());
	remove(("./movies/seat/" + movies[changes].name + " seat.txt").c_str());
}

int searchname(string searchs, int par)
{
    if(par >= usercount) 
    {
        return -1;
    }

    if(searchs == users[par].username)
    {
        return par;
    }
    else
    {
        return searchname(searchs, par + 1);
    }
}


void searchU()
{
	loadUserData();
	string searchs;
	int parameters;
	cout << "\t +-------------------------+\n";	
	cout << "\t +        Search User      |\n";
	cout << "\t +-------------------------+\n";	
	cout << "Search user (by username) : "; cin >> searchs;
	parameters = searchname(searchs, 0);
	
		if (parameters != -1)
		{
			cout << "Account with username " << users[parameters].username << " has found\n";
			
		int loops = 1;
		cout << "List of booked ticket owned by " << users[parameters].username << " (sorted (A-Z) based on film title) \n";
		
		//checking all booked seat
		for(int g = 0; g < movieCount; g++)
		{
			checkseat(g);
		}
		
		//copy all movies into sort
		for (int a = 0; a < movieCount; a++ )
		{
			sortedmov[a]= movies[a];
		}
		sort();

		for (int I = 0; I < movieCount; I++)
		{
			for (int A = 1; A <= 160; A++)
			{
				if (users[parameters].username == sortedmov[I].bioskop[A].whobook && sortedmov[I].bioskop[A].terpesan == true)
				{
					cout << "Ticket [" << loops  << "] : \n";
					cout << "Movies Name : " << sortedmov[I].name << endl;
					cout << "Schedule    : " << movies[I].schedule << endl;
					cout << "Seat        : " << sortedmov[I].bioskop[A].kursi << endl << endl;
					loops++;
				}
				
			}
		}
		system("pause");
		resetstruct();
		loginadmin();
		}
		else
		{
			cout << "\nAccount Name is not found\n";
			system("pause");
			system("cls");
			loginadmin();
		}
	
}
