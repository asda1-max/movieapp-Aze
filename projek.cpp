#include <iostream>
#include "interfaces.h"

using namespace std;


void tampilkanKursi() {
    cout << "\t\t=============== Screen ===============\n";
    for (int i = 1; i <= 160; i++) {
        if (i % 20 == 1)
            cout << endl;
        if (i % 40 == 1)
            cout << endl;
        
        if (bioskop[i-1].terpesan){
            if (i % 20 < 10){
                cout << "XX ";}
            else{
                cout << "XX  ";}
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
            cout << "|  |";
        }
    }
    cout << endl;
}

void pesanKursi(char baris, int nomor) {
    int barisIndex = baris - 'A'; 
    int index = barisIndex * 20 + nomor - 1;
    if (bioskop[index].terpesan) {
        cout << "Kursi " << baris << nomor << " sudah terpesan.\n";
    } else {
        bioskop[index].terpesan = true;
        cout << "Kursi " << baris << nomor << " berhasil dipesan.\n";
    }
}

void proyek_main() {
   

    int nomor;
    char baris, lagi;

    do {
        tampilkanKursi();
        pesan:
        cout << "Masukkan baris (A-H): ";
        cin >> baris;
        cout << "Masukkan nomor kursi (1-20): ";
        cin >> nomor;
        if (nomor < 1 || nomor > 20 || (baris < 'A' || baris > 'H'))
        {
            cout << "Kursi tidak valid\n";
            goto pesan;
        }
        pesanKursi(baris, nomor);
        cout << "Pesan lagi? (y/n): ";
        cin >> lagi;
    } while (lagi == 'y' || lagi == 'Y');
    

}
