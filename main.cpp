#include <iostream>
#include <locale> 
#include "game.h"

using namespace std;

void print_menu();
bool menu_operation(char choice);



int main(){
	srand(time(NULL));
	setlocale(LC_ALL, "Turkish");
	char choice;
	bool end = false;
	while (!end){
		print_menu();
		cin >> choice;
		end = menu_operation(choice);
	}
}

void print_menu(){
	//Game information
	cout << endl << "TIC TAC TOE" << endl << endl;
	cout << "1. Oyuncunun taþý: x" << endl;
	cout << "2. Oyuncunun taþý: o" << endl << endl;
	//Playing against AI
	cout << "(B) Bilgisayara Karþý" << endl;
	//Local Player vs Player
	cout << "(K) Ýki oyunculu" << endl;
	//Exit the game
	cout << "(C) Oyundan çýk" << endl;
	cout << "Seçimini yap {B, K, C} :";
}

bool menu_operation(char choice){
	bool terminate = false;
	switch (choice) {
	case 'B': case 'b':
	{
		tictactoe comp_game;
		comp_game.play(true);
		break;
	}
	case 'K': case 'k':
	{
		tictactoe twop_game;
		twop_game.play(false);
		break;
	}
	case 'C': case 'c':
		cout << "Oyundan çýkmak istediðine emin misin? (E/H):";
		cin >> choice;
		while (choice != 'H' && choice != 'h'){
			if (choice == 'E' || choice == 'e'){
				terminate = true;
				break;
			}
			cin >> choice;
		}
		system("cls");
		break;
	default:
		cout << "Hata: Geçersiz bir seçim yaptýn." << endl;
		cout << "Lütfen tekrar dene {B, K, C} :";
		cin >> choice;
		terminate = menu_operation(choice);
		break;
	}
	return terminate;
}