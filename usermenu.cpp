#include <iostream>
#include <fstream>
#include "interfaces.h"

using namespace std;

////void or function
void sort();
void bookT();
void movieL();
void checkT(); 
void cancelT();
void reviewMovie();
void checkreview(); 
void tampilkanKursi(int pilihan);
void resetstruct();

void loginuser()
{
	int pil;
	checkmovies(); //checking movie from movielist.txt
	system("cls");
	cout << "\t +--------------------------+\n";	
	cout << "\t | Welcome to Rookie Cinema |\n";
	cout << "\t +--------------------------+\n";
	cout << "Welcome " << users[whousethisinterface].username << "!!\n\n";	
	cout << "Menu :\n";
	cout << "------------------------\n";
	cout << "1.Book a ticket online\n";
	cout << "2.Check Ticket\n";
	cout << "3.Cancel a ticket\n";
	cout << "4.Movies list\n";
	cout << "5.Add a movie review!\n";
	cout << "6.Check movie review\n";
	cout << "7.Log off\n";
	cout << "------------------------\n=>";
	cin >> pil; system("cls");//menu
	switch (pil)
	{
		//switch to function based on selection
		case 1: bookT(); break;
		case 2: checkT(); break;
		case 3: cancelT(); break;
		case 4: movieL(); break;
		case 5: reviewMovie(); break;
		case 6: checkreview(); break;
		case 7: cout << "Logging off : \n"; loading(); main(); 
		default : system("cls"); loginuser();
		break;
		
	}
	
}

void bookT()
{
	//local declared variable
	int pil; 
	int nomor;
	int hmTick;
	int barisIndex;
	int koersi[160];
	char baris;
	string impParameter;
	
	cout << "\t +-------------------------+\n";	
	cout << "\t +       Book Ticket       |\n";
	cout << "\t +-------------------------+\n";	
	
	//cout movie list
	cout << "movie list : \n";
	for ( int a = 0; a < movieCount; a++)
	{
		cout << "\t" << a+1 << ". " << movies[a].name <<endl;
	}
	
	cout << "\n\nwhich movie you wanted to Book ( 1 - " << movieCount << ") : "; cin >> pil;
	
	if (pil < 1 or pil > movieCount)
	{
		cout << "\nMovie is not avaiable\n";
		system("pause");
		system("cls");
		bookT();
	}
	
	cout << "You Are Choosing : " << movies[pil-1].name;//cout movie selected
	cout <<"\n\n";
	//checking booked seat from "seat" folder
	checkseat(pil-1);
	//cout seat floor plan
	tampilkanKursi(pil-1);
	cout <<"\n\n";
	cout << "\nHow many ticket? : "; cin >> hmTick;
	
	for (int i = 0; i < hmTick; i++)
	{
		rewrite:
		cout << "Ticket [#" << i+1 << "] : \n";
		cout << "LINE   [A-H]  : "; cin >> baris; //input seat line
		cout << "NUMBER [1-20] : "; cin >> nomor; //input seat order
		
		if (nomor < 1 || nomor > 20 || (baris < 'A' || baris > 'H'))
        {
            cout << "SEAT IS NOT VALID \n"; //if the input is invalid
            goto rewrite; //go to rewrite
        }
        
        //convert line and number to a valid seat address
        barisIndex = baris - 'A';
        koersi[i] = barisIndex * 20 + nomor;
        checkseat(pil-1);
        
		if (movies[pil-1].bioskop[koersi[i]].terpesan == true)
		{
			cout << "\nseat already taken \n"; //if the seat is already taken
			goto rewrite;
		}
		
		impParameter = to_string(koersi[i]);
		
		//saving the booked seat to the folder "seat"
		writes.open(("./movies/seat/" + movies[pil - 1].name + " seat.txt").c_str(),ios::app);
			writes << impParameter << endl;
			writes << baris << nomor << endl;
		writes << users[whousethisinterface].username << endl;
		writes.close();
		
		
	}
	int harga;
	reinput:
	cout << "\nAll Ticket will be : Rp." << hmTick * 25000 <<",00\n";
	cout << "PAY##>"; cin >> harga;
	if (harga < hmTick * 25000)
	{
		cout << "\nNot Enough Money\n";
		goto reinput;
	}
	else if (harga > hmTick * 25000)
	{
		cout << "Change : " << harga - (hmTick *25000) << endl;
	}
	
	cout << "\n\n\tTHANKYOU -- YOUR TICKET IS REGISTERED\n\n";
	
	system("pause");
	loginuser() ;
	
}

void checkT()
{
	int loops = 1;
	cout << "List of booked ticket owned : (sorted (A-Z) based on film title) \n";
	
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

	for (int i = 0; i < movieCount; i++)
	{
		for (int A = 1; A <= 160; A++)
		{
			if (users[whousethisinterface].username == sortedmov[i].bioskop[A].whobook && sortedmov[i].bioskop[A].terpesan == true)
			{
				cout << "Ticket [" << loops  << "] : \n";
				cout << "Movies Name : " << sortedmov[i].name << endl;
				cout << "Schedule    : " << sortedmov[i].schedule << endl;
				cout << "Seat        : " << sortedmov[i].bioskop[A].kursi << endl << endl;
				loops++;
			}
			
		}
	}
	system("pause");
	resetstruct();
	loginuser();
}

void cancelT()
{
	int pil;
	int nomor;
	int kursi;
	int loops = 1;
	int barisIndex;
	char baris;
	string impParameter;
	bool haveticket = false;
	
	cout << "\t +-------------------------+\n";	
	cout << "\t |    Ticket Cancelation   |\n";
	cout << "\t +-------------------------+\n";	
	
	for ( int a = 0; a < movieCount; a++)
	{
		cout << "\t" << a+1 << ". " << movies[a].name <<endl;
	}
	
	cout << "which movie that you want to cancel : ( 1 - " << movieCount << " ) \n";
	cin >> pil;
	
	if (pil < 1 or pil > movieCount)
	{
		cout << "\nMovie is not avaiable\n";
		system("pause");
		system("cls");
		loginuser();
	}
	
	system("cls");
	checkseat(pil-1);
	tampilkanKursi(pil-1);
	
	cout << "List of booked ticket on movie : " << movies[pil-1].name << endl;
	
	for (int A = 1; A <= 161; A++)
	{
		if (users[whousethisinterface].username == movies[pil-1].bioskop[A].whobook && movies[pil-1].bioskop[A].terpesan == true)
		{
			cout << "Ticket [" << loops  << "] : \n";
			cout << "Movies Name : " << movies[pil-1].name << endl;
			cout << "Seat        : " << movies[pil-1].bioskop[A].kursi << endl << endl;
			haveticket = true;
			loops++;
		}
	}
	
	if (haveticket == false)
	{
		cout << "\nyou dont have any ticket \n";
		system("pause"); system("cls");
		loginuser();
	}
	
	cout << "Which ticket you want to cancel : \n"; 
	cout << "LINE   [A-H]  : "; cin >> baris;
	cout << "NUMBER [1-20] : "; cin >> nomor;
	
	if (nomor < 1 || nomor > 20 || (baris < 'A' || baris > 'H'))
        {
            cout << "SEAT IS NOT VALID \n"; //if the input is invalid
			system("pause");
			system("cls");
			loginuser();
        }
	
	barisIndex = baris - 'A';
    kursi = barisIndex * 20 + nomor;
    
    if (movies[pil-1].bioskop[kursi].terpesan == false)
    {
		cout << "that seat is not owned yet \n\n";
		system("pause");system("cls");
		cancelT();
	}
	
	if (movies[pil-1].bioskop[kursi].terpesan == true && movies[pil-1].bioskop[kursi].whobook != users[whousethisinterface].username)
	{
		cout << "that is not your seat \n\n";
		system("pause");system("cls");
		cancelT();
	}
	
	impParameter = to_string(kursi);
	remove(("./movies/seat/" + movies[pil-1].name + " seat.txt").c_str());
	writes.open(("./movies/seat/" + movies[pil - 1].name + " seat.txt").c_str(),ios::app);
	for (int i = 1; i <= 161; i++)
	{
		if (movies[pil-1].bioskop[i].terpesan == true)
		{
			if ( i != kursi )
			{
				writes << i << endl;
				writes << movies[pil-1].bioskop[i].kursi << endl;
				writes << movies[pil-1].bioskop[i].whobook << endl;
				
			}
			else if ( i == kursi)
			{
				movies[pil-1].bioskop[i].terpesan = false;
			}
		}
	}
	writes.close();
	
	cout << "\n\n\tSUCCESSFULLY REFUNDED Rp.25000,00 TO YOUR ACCOUNT\n\n";
	
	system("pause");
	loginuser();
        
	
	
}

void movieL()
{
	string synospsis;
	int pil;
	cout << "\t +-------------------------+\n";	
	cout << "\t +        Movie List       |\n";
	cout << "\t +-------------------------+\n";	
	for ( int a = 0; a < movieCount; a++)
	{
		cout << "\t" << a+1 << ". " << movies[a].name << endl;
	}
	cout << "\nwhich movie you wanted to check ( 1 - " << movieCount << ") : "; cin >> pil;
	if (pil < 1 or pil > movieCount)
	{
		cout << "\nMovie is not avaiable\n";
		system("pause");
		system("cls");
		loginuser();
	}
	system("cls");
	cout << "Movie Name : " << movies[pil-1].name <<endl;
	cout << "Schedule   : " << movies[pil-1].schedule << endl;
	cout << "Duration   : " << movies[pil-1].duration << " Minutes"<<endl;
	cout << "Synopsis   : " << endl;
	
	reads.open(("./movies/synopsis/" + movies[pil-1].name + ".txt").c_str());
		while(!reads.eof())
		{
			getline(reads >> ws, synospsis);
			cout << "\t" << synospsis << endl;
		}
		cout << "\033[A";
		cout << "\r              ---                                                                                                                                                                                                                                                   ";
	reads.close();
	
	cout << "\nBooked Seat : \n";
	checkseat(pil-1);
	tampilkanKursi(pil-1);
	system("pause");
	loginuser();
}

void reviewMovie()
{
	int pil;
	int revstar;
	string ratess;
	string commentY;
	string blank;
	string userss;
	bool isthisuseralr = false;
	
	cout << "\t +-------------------------+\n";	
	cout << "\t |    Add a Movie Review   |\n";
	cout << "\t +-------------------------+\n";	
	
	for ( int a = 0; a < movieCount; a++)
	{
		cout << "\t" << a+1 << ". " << movies[a].name << endl;
	}
	cout << "which movie you wanted to rate ( 1 - " << movieCount << " ) : "; cin >> pil;
	
	if (pil < 1 or pil > movieCount)
	{
		cout << "\nMovie is not avaiable\n";
		system("pause");
		system("cls");
		reviewMovie();
	}
	
	reads.open(("./movies/reviews/" + movies[pil - 1].name + " review.txt").c_str());
		while(!reads.eof())
		{
			getline (reads >> ws, blank);
			getline (reads >> ws, blank);
			getline (reads >> ws, userss);
			if(users[whousethisinterface].username == userss)
			{
				cout << "\nyou already rate this movie\n\n";
				isthisuseralr = true;
				break;
			}
		}
	reads.close();
	
	if (isthisuseralr == true)
	{
		system("pause");system("cls");
		loginuser();
	}
	re:
	cout << "+-------------------------------+\n";
	cout << "|1 Star : Dissapointed          |\n";
	cout << "|2 Star : Not Satisfied         |\n";
	cout << "|3 Star : Slightly Satisfied    |\n";
	cout << "|4 Star : Satisfied             |\n";
	cout << "|5 Star : Very Satisfied        |\n";
	cout << "|Choose (1-5) star :            |\n";
	cout << "+-------------------------------+\n";
	cout << "=>";
	cin >> revstar;
	switch (revstar)
	{
		case 1: ratess = "one"; break;
		case 2: ratess = "two"; break;
		case 3: ratess = "three"; break;
		case 4: ratess = "four"; break;
		case 5: ratess = "five"; break;
		default : system("cls"); goto re;
	}
	cout << "comment \t\t : "; getline(cin >> ws, commentY);
	
	writes.open(("./movies/reviews/" + movies[pil - 1].name + " review.txt").c_str(),ios::app);
		writes << ratess << endl;
		writes << commentY << endl;
		writes << users[whousethisinterface].username << endl;
	writes.close();
	system("pause");
	loginuser();
}


void tampilkanKursi(int pilihan) 
{
	bool kursiuser = false,kursilainuser = false;
	
    cout << "\t\t\t=============== Screen ===============\n";
    for (int i = 1; i <= 160; i++) {
        if (i % 20 == 1)
            cout << endl;
        if (i % 40 == 1)
            cout << endl;
        
        if (movies[pilihan].bioskop[i].terpesan == true)
        {
			
			if (users[whousethisinterface].username == movies[pilihan].bioskop[i].whobook)
			{
				kursiuser = true;
				if (i % 20 < 10)
				{
					if (i  % 20 == 0)
					{
						cout << "\033[36mXXX \033[0m";
					}
					else
					{
						cout << "\033[36mXX \033[0m";
					}
				}
				else
				{
					cout << "\033[36mXXX \033[0m";
				}
			}
			
			
			else
			{
				kursilainuser = true;
				if (i % 20 < 10)
				{
					if (i  % 20 == 0)
					{
						cout << "\033[31mXXX \033[0m";
					}
					else
					{
						cout << "\033[31mXX \033[0m";
					}
				}
				else
				{
					cout << "\033[31mXXX \033[0m";
				}
			}
		}
        else if (i <= 20)
            cout << "A" << i << " ";
        else if (i > 20 && i <= 40)
            cout << "B" << i - 20 << " ";
        else if (i > 40 && i <= 60)
            cout << "C" << i - 40 << " ";
        else if (i > 60 && i <= 80)
            cout << "D" << i - 60 << " ";
        else if (i > 80 && i <= 100)
            cout << "E" << i - 80 << " ";
        else if (i > 100 && i <= 120)
            cout << "F" << i - 100 << " ";
        else if (i > 120 && i <= 140)
            cout << "G" << i - 120 << " ";
        else if (i > 140 && i <= 160)
            cout << "H" << i - 140 << " ";
        
        if ((i % 20 == 3) || (i % 20 == 18)) {
            cout << "| - |";
        }
    }
    cout <<"\n";
    if (kursilainuser)
	{
		cout << "\n\033[47m\033[31mRED  : \033[30mSeat that already booked \033[40m\033[0m \n";
	}
    if (kursiuser)
	{
		cout << "\033[47m\033[36mBLUE : \033[30mbooked by you \033[40m\033[0m\n\n";
	}
}


void sort()
{
	mov sementara;
	for (int i = 0; i < movieCount; i++)
	{
		for (int j = 0; j < movieCount; j++)
		{
			if ( sortedmov[i].name < sortedmov[j].name)
			{
				sementara = sortedmov[i];
				sortedmov[i] = sortedmov[j];
				sortedmov[j] = sementara;
			}
		}

	}
}

void checkreview()
{
	int pil, loops = 0,totscore = 0, rateinint[100];
	string ratess[100], commentY[100], users[100], ratex;
	cout << "\t +-------------------------+\n";	
	cout << "\t +       Movie Review      |\n";
	cout << "\t +-------------------------+\n";	
	cout << "Which movie you want to check the review \n ";
	for ( int a = 0; a < movieCount; a++)
	{
		cout << "\t" << a+1 << ". " << movies[a].name << endl;
	}
	cin >> pil;
	
	reads.open(("./movies/reviews/" + movies[pil - 1].name + " review.txt").c_str());
		if(reads.is_open())
		{
			while(!reads.eof())
			{
				getline (reads >> ws, ratex);
				if (ratex == "one")
				{
					ratess[loops] = "1/5 | Dissapointed\n";
					rateinint[loops] = 1;
				}
				if (ratex == "two")
				{
					ratess[loops] = "2/5 | Not Satisfied\n";
					rateinint[loops] = 2;
				}
				if (ratex == "three")
				{
					ratess[loops] = "3/5 | Slightly Satisfied\n";
					rateinint[loops] = 3;
				}
				if (ratex == "four")
				{
					ratess[loops] = "4/5 | Satisfied\n";
					rateinint[loops] = 4;
				}
				if (ratex == "five")
				{
					ratess[loops] = "5/5 | Very Satisfied\n";
					rateinint[loops] = 5;
				}
				getline (reads >> ws, commentY[loops]);
				getline (reads >> ws, users[loops]);
				loops++;
			}
		}
		else
		{
			cout << "\nNo Review Yet\n";
			system("pause");
			system("cls");
			loginuser();
		}
	reads.close();
	movies[pil-1].totalreview = loops-1;
	for (int a = 0; a < movies[pil-1].totalreview; a++)
	{
		cout << "\n[REVIEW #" << a+1 << "]\n";
		cout << "RATING  : " << ratess[a];
		cout << "Comment : " << commentY[a] << "\n";
		cout << "User    : " << users[a] << "\n";
		totscore += rateinint[a];
	}
	movies[pil-1].average_score = totscore * 0.1 / movies[pil-1].totalreview;
	
	cout << "\n< Average Score : " << movies[pil-1].average_score / 0.1 << " / 5 >\n\n";
	system("pause"); system("cls");
	loginuser();
	
}

void resetstruct()
{
	for (int i = 0; i < movieCount; i++)
	{
		
		for (int a = 1; a < 161; a++)
		{
			sortedmov[i].bioskop[a].kursi = "";
			sortedmov[i].bioskop[a].terpesan = false;
			sortedmov[i].bioskop[a].whobook = "";
		}
		
	}
	
}
