#include <iostream>
#include "game.h"

using namespace std;

tictactoe::tictactoe(){
	clean_board();
	int match_count = set_count();
	player1 = player2 = 0;
	if (match_count == 1){
		win_condition = 1;
	}
	else if (match_count == 3){
		win_condition = 2;
	}
	else if (match_count == 5){
		win_condition = 3;
	}
}

int tictactoe::set_count(){
	int match_count;
	cout << endl << "Kaç oyun oynamak istersin? (1, 3, 5)" << endl;
	cin >> match_count;
	while (match_count != 1 && match_count != 3 && match_count != 5){
		cout << endl << "Lütfen geçerli bir sayý gir (1, 3, 5)" << endl;
		cin >> match_count;
	}
	return match_count;
}

void tictactoe::print(){
	cout << " _ _ _" << endl;
	for (int i = 0; i < 3; i++){
		cout << "|";
		for (int j = 0; j < 3; j++){
			cout << game[i][j] << "|";
		}
		cout << endl << " - - -" << endl;
	}
}

bool tictactoe::is_over(){
	return (player1 == win_condition) || (player2 == win_condition);
}

void tictactoe::clean_board(){
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			game[i][j] = ' ';
		}
	}
}
bool tictactoe::is_won(){
	char c;
	if (turn)
		c = 'o';
	else
		c = 'x';
		
	if (((game[0][0] == game[0][1]) && (game[0][1] == game[0][2]) && (game[0][2] == c)) ||
		((game[1][0] == game[1][1]) && (game[1][1] == game[1][2]) && (game[1][2] == c)) ||
		((game[2][0] == game[2][1]) && (game[2][1] == game[2][2]) && (game[2][2] == c)) ||
		((game[0][0] == game[1][0]) && (game[1][0] == game[2][0]) && (game[2][0] == c)) ||
		((game[0][1] == game[1][1]) && (game[1][1] == game[2][1]) && (game[2][1] == c)) ||
		((game[0][2] == game[1][2]) && (game[1][2] == game[2][2]) && (game[2][2] == c)) ||
		((game[0][0] == game[1][1]) && (game[1][1] == game[2][2]) && (game[2][2] == c)) ||
		((game[0][2] == game[1][1]) && (game[1][1] == game[2][0]) && (game[2][0] == c))){
		if (turn){
			player2++;
			if (with_comp)
				cout << "Bilgisayar bu raundu kazandý!" << endl;
			else
				cout << "2. Oyuncu bu raundu kazandý!" << endl;
		}
		else{
			player1++;
			if (with_comp)
				cout << "Oyuncu bu raundu kazandý!" << endl;
			else
				cout << "1. oyuncu bu raundu kazandý!" << endl;
		}
		return true;
	}
	else return false;
}

void tictactoe::play(bool play_with_comp){
	with_comp = play_with_comp;
	system("cls");
	cout << "Oyun Baþladý!" << endl << endl;
	//round counter
	int counter = 0;
	while (!is_over()){
		counter++;
		if (win_condition != 1)
			cout << counter << ". Raund!" << endl << endl;
		clean_board();
		turn = true;
		int turn_counter = 1;
		print();
		while (!is_won()){
			//If noone was able to win, the game shuold end in a draw after 9 turns
			if (turn_counter == 10){
				cout << "Berabere!" << endl;
				cout << "Ýki taraf da kazanmayý baþaramadý." << endl << endl;
				break;
			}
			int x, y;
			if (turn){
				if (with_comp){
					cout << "Oyuncunun hamle sýrasý" << endl;
				}
				else{
					cout << "1. oyuncunun hamle sýrasý" << endl;
				}
				//P1 makes their move
				cout << "Taþýný nereye oynayacaksýn?" << endl;
				cout << "Sütun: ";
				cin >> y;
				cout << "Satýr: ";
				cin >> x;
				while (game[x - 1][y - 1] != ' ' || !validate(x, y)){
					if (validate(x, y)){
						cout << "Bu yer zaten dolu." << endl;
					}
					else{ cout << "Burasý oyun tahtasýnýn sýnýrýnýn dýþýnda." << endl; }
					cout << "Farklý bir yer seç." << endl;
					cout << "Sütun: ";
					cin >> y;
					cout << "Satýr: ";
					cin >> x;
				}
				game[x - 1][y - 1] = 'x';
				turn_counter++;
				turn = false;
			}
			else{
				if (with_comp){
					//AI makes its move
					cout << "Bilgisayarýn hamle sýrasý" << endl;
					bool better = false;
					//first, check if there is a winning move
					for (int i = 0; i < 3; i++){
						for (int j = 0; j < 3; j++){
							if (game[i][j] != 'x' && game[i][j] != 'o'){
								int column = 0, row = 0, crosswise1 = 0, crosswise2 = 0;
								for (int c = j - 2; c <= j + 2; c++){
									if (validate(i + 1, c + 1) && game[i][c] == 'o'){
										column++;
									}
								}
								for (int r = i - 2; r <= i + 2; r++){
									if (validate(r + 1, j + 1) && game[r][j] == 'o'){
										row++;
									}
								}
								int c1x = i - 2, c1y = j - 2;
								while ((c1x <= i + 2) && (c1y <= j + 2)){
									if (validate(c1x + 1, c1y + 1) && game[c1x][c1y] == 'o'){
										crosswise1++;
									}
									c1x++;
									c1y++;
								}
								int c2x = i + 2, c2y = j - 2;
								while ((c2x >= i - 2) && (c2y <= j + 2)){
									if (validate(c2x + 1, c2y + 1) && game[c2x][c2y] == 'o'){
										crosswise2++;
									}
									c2x++;
									c2y++;
								}
								if (column == 2 || row == 2 || crosswise1 == 2 || crosswise2 == 2){
									x = i + 1;
									y = j + 1;
									better = true;
								}
							}
							if (better) break;
						}
						if (better) break;
					}
					if (!better){
						//if a winning move doesn't exist, check if opponent has a winning move available for them
						//if they do, block it
						for (int i = 0; i < 3; i++){
							for (int j = 0; j < 3; j++){
								if (game[i][j] == ' '){
									int column = 0, row = 0, crosswise1 = 0, crosswise2 = 0;
									for (int c = j - 2; c <= j + 2; c++){
										if (validate(i + 1, c + 1) && game[i][c] == 'x'){
											column++;
										}
									}
									for (int r = i - 2; r <= i + 2; r++){
										if (validate(r + 1, j + 1) && game[r][j] == 'x'){
											row++;
										}
									}
									int c1x = i - 2, c1y = j - 2;
									while ((c1x <= i + 2) && (c1y <= j + 2)){
										if (validate(c1x + 1, c1y + 1) && game[c1x][c1y] == 'x'){
											crosswise1++;
										}
										c1x++;
										c1y++;
									}
									int c2x = i + 2, c2y = j - 2;
									while ((c2x >= i - 2) && (c2y <= j + 2)){
										if (validate(c2x + 1, c2y + 1) && game[c2x][c2y] == 'x'){
											crosswise2++;
										}
										c2x--;
										c2y++;
									}
									if (column == 2 || row == 2 || crosswise1 == 2 || crosswise2 == 2){
										x = i + 1;
										y = j + 1;
										better = true;
									}
								}
								if (better) break;
							}
							if (better) break;
						}
						if (!better){
							//if there are no better moves, make a random move
							x = rand() % 3 + 1;
							y = rand() % 3 + 1;
							while (game[x - 1][y - 1] != ' '){
								x = rand() % 3 + 1;
								y = rand() % 3 + 1;
							}
						}
					}
					game[x - 1][y - 1] = 'o';
					system("PAUSE");
				}
				else{
					cout << "2. oyuncunun hamle sýrasý" << endl;
					cout << "Taþýný nereye oynayacaksýn?" << endl;
					cout << "Sütun: ";
					cin >> y;
					cout << "Satýr: ";
					cin >> x;
					while (game[x - 1][y - 1] != ' ' || !validate(x, y)){
						if (validate(x, y)){
							cout << "Bu yer zaten dolu." << endl;
						}
						else{ cout << "Burasý oyun tahtasýnýn sýnýrýnýn dýþýnda." << endl; }
						cout << "Farklý bir yer seç." << endl;
						cout << "Sütun: ";
						cin >> y;
						cout << "Satýr: ";
						cin >> x;
					}
					game[x - 1][y - 1] = 'o';
				}
				turn_counter++;
				turn = true;
			}
			system("cls");
			print();
		}
		if (with_comp){
			cout << "Oyuncu: " << player1 << endl;
			cout << "Bilgisayar: " << player2 << endl << endl;
		}
		else{
			cout << "1. Oyuncu: " << player1 << endl;
			cout << "2. Oyuncu: " << player2 << endl << endl;
		}
		system("PAUSE");
		system("cls");
	}
	if (player1 == win_condition){
		if (with_comp)
			cout << "Oyuncu oyunu kazandý." << endl;
		else
			cout << "1. Oyuncu oyunu kazandý." << endl;
	}
	else{
		if (with_comp)
			cout << "Bilgisayar oyunu kazandý." << endl;
		else
			cout << "2. Oyuncu oyunu kazandý." << endl;
	}
	cout << "Tebrikler!" << endl << endl;
	system("PAUSE");
	system("cls");
}

bool tictactoe::validate(int x, int y){
	return (x > 0 && x < 4 && y > 0 && y < 4);
}