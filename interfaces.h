#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
using namespace std;

#ifndef INTERFACES_H
#define INTERFACES_H

//universal variable
int whousethisinterface;
int movieCount;

//universal libraries
ifstream reads;
ofstream writes;

//universal struct
struct user
{
	int Id;
	string username, password;
	bool isThisUserAdmin;
}users[100];

struct projek {
    string kursi;
    string whobook;
    bool terpesan;
}bioskop;

struct mov
{
	string name;
	string duration;
	string schedule;
	int totalreview;
	int howmuchbooked;
	float average_score;
	projek bioskop[161];
}movies[100];

mov sortedmov[100];
//universal  function
void loading ()
{
	char load = 177;
	char load2 = 219;
	for ( int a = 0; a < 20; a++)
	cout << (char)load;
	cout << "\r";
    for (int a = 0; a < 20; a++)
    {
		cout << "\033[34m" << (char)load2;
		cout.flush();
		Sleep(30);
	}
	cout << "\e[0;37m";
	system("cls");
}


void checkmovies()
{
	int loops = 0;
	reads.open("./movies/movielist.txt");
		while (!reads.eof())
		{
			getline(reads >> ws,movies[loops].name);
			getline(reads >> ws, movies[loops].schedule);
			reads >> movies[loops].duration;
			loops++;
		}
	reads.close(); 
	movieCount = loops-1;
}

void checkseat(int pilihan)
{ 
	int parameter, loops = 0;
	reads.open(("./movies/seat/" + movies[pilihan].name + " seat.txt").c_str());
		while(!reads.eof())
		{
			reads >> parameter;
			reads >> movies[pilihan].bioskop[parameter].kursi;
			movies[pilihan].bioskop[parameter].terpesan = true;
			getline (reads >> ws, movies[pilihan].bioskop[parameter].whobook);
			loops++;
		}
	reads.close();
	movies[pilihan].howmuchbooked = loops -1;
}

//extern from file
extern int usercount;
extern int main();
extern void resetstruct();
extern void sort();
extern void loadUserData();
extern void checkreview();


#endif // INTERFACES_H
