
#include<iostream>
#include<string>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
#define random(x) (rand()%x)

using namespace std;

string  player[2] = { "PlayerA","PlayerB" };
int map[100];
int playerPos[2] = { 0,0 };
int gamePlayer = 0;
bool isGameOver = false;
int winer = -1;
int pausePlayer = -1;
//0□ Normal 1☆ Wheel of Fortune 2◎ Mine 3△ Suspended 4 Swastika Time Tunnel
string getLogo(int pos) {

	string res = "□";
	if ((playerPos[0] == pos) && (playerPos[1] == pos)) {
		res = "<>";
	}
	else if (playerPos[0] == pos) {
		res = "Ａ";
	}
	else if (playerPos[1] == pos) {
		res = "Ｂ";
	}
	else {
		switch (map[pos]) {
		case 1:
			res = "☆"; // Wheel of fortune
			break;
		case 2:
			res = "◎"; // landmine 
			break;
		case 3:
			res = "△"; // Pause 
			break;
		case 4:
			res = "卍"; // Space-time tunnel 
			break;
		}
	}
	return res;
}
void drowMap() { //map

	for (int i = 0; i <= 29; ++i) {
		cout << getLogo(i);
	}
	cout << endl;
	for (int i = 30; i <= 34; ++i) {
		for (int j = 0; j <= 28; j++) {
			cout << "  ";
		}
		cout << getLogo(i) << endl;;
	}
	for (int i = 64; i >= 35; i--) {
		cout << getLogo(i);
	}
	cout << endl;
	for (int i = 65; i <= 69; ++i) {
		cout << getLogo(i) << endl;
	}
	for (int i = 70; i <= 99; i++) {
		cout << getLogo(i);
	}
	cout << endl;
	cout << "Map description: 【☆ Wheel of Fortune Swastika Time Tunnel ◎ Mine △ pause <>Player in the same position 】" << endl;
}
void gameOver() { //Game Over 
	isGameOver = true;
	winer = gamePlayer;
	playerPos[gamePlayer] = 99;
	system("cls");
	drowMap();
	cout << "***Game Over ！congratulations[" << player[gamePlayer] << "]Come to victory！" << endl;
	system("PAUSE");
}
void initMap() { //Initialize map 
	int luckyTurn[] = { 6,23,40,55,69,83 };//Wheel of fortune1 
	int landMine[] = { 5,13,17,33,38,50,64,80,94 };//landmine2 
	int pause[] = { 9,27,60,93 };//Pause3 
	int timeTunnel[] = { 20,25,45,63,72,88,90 };//Space-time tunnel4 
	int i;
	for (i = 0; i < 6; ++i) {
		int pos = luckyTurn[i];
		map[pos] = 1;
	}
	for (i = 0; i < 9; ++i) {
		int pos = landMine[i];
		map[pos] = 2;
	}
	for (i = 0; i < 4; ++i) {
		int pos = pause[i];
		map[pos] = 3;
	}
	for (i = 0; i < 7; ++i) {
		int pos = timeTunnel[i];
		map[pos] = 4;
	}
}
void initUI() { //Initialization interface 

	cout << "*******************mini-games*****************" << endl;
	cout << "*                                        *" << endl;
	cout << "*                Aeroplane chess              *" << endl;
	cout << "*                                        *" << endl;
}
void joinPlayer() {	//Join Player

	string tmpStr = "";
	cout << "Please enter PlayerA's name___" << endl;
	cin >> tmpStr;
	while (tmpStr == "") {
		cout << "Player name cannot be empty Please re-enter___" << endl;
		cin >> tmpStr;
	}
	player[0] = "A" + tmpStr;

	cout << "Please enter PlayerB's name___" << endl;
	cin >> tmpStr;
	while (tmpStr == "") {
		cout << "Player name cannot be empty Please re-enter___" << endl;
		cin >> tmpStr;
	}
	while (tmpStr == player[0]) {
		cout << "Player name must be unique. Please enter a new player name___" << endl;
		cin >> tmpStr;
	}
	player[1] = "B" + tmpStr;
	system("cls");
	cout << "***Player Join successfully..." << endl;
	cout << "***[A] in the map indicates the location of Player[" << player[0] << "]..." << endl;
	cout << "***The [B] in the map indicates the location of the Player[" << player[1] << "]..." << endl;
}
void yaoYiYao() { //Throw dice 

	short number = 0;
	while (!isGameOver) {
		char a;
		cout << "***Please[" << player[gamePlayer] << "]Enter g to roll the dice..." << endl;
		cin >> a;
		if (a == 'g') {
			system("cls");
			number = random(6) + 1;
			cout << "***Player[" << player[gamePlayer] << "]The number of dice thrown is：" << number << endl;
			playerPos[gamePlayer] += number;
			int pos = playerPos[gamePlayer];
			if (pos >= 99) {
				gameOver();
			}
			else {
				switch (map[pos]) {
				case 0:
					if (pausePlayer = -1) {
						gamePlayer = !gamePlayer;
					}
					else if (pausePlayer = 0) {
						pausePlayer++;
					}
					else if (pausePlayer = 1) {
						pausePlayer = -1;
					}
					break;
				case 1:
					int cnumber;
					cout << "***Woo！Player[" << player[gamePlayer] << "]A chance to get lucky for a change..." << endl;
					cout << "***Please enter a number to select the operation to be performed...." << endl;
					cout << "1--Switch places with each other" << endl << "2--Bomb each other" << endl;
					cin >> cnumber;
					if (cnumber == 1) {
						int t = 0;
						t = playerPos[gamePlayer];
						playerPos[gamePlayer] = playerPos[!gamePlayer];
						playerPos[!gamePlayer] = t;
					}
					else if (cnumber == 2) {
						playerPos[!gamePlayer] -= 6;
					}
					else {
						cout << "Enter a non-specified number! Lost opportunity。" << endl;
					}
					gamePlayer = !gamePlayer;
					break;
				case 2:
					cout << "***Woo！Player[" << player[gamePlayer] << "]You stepped on a mine. Take six steps back..." << endl;
					playerPos[gamePlayer] -= 6;
					gamePlayer = !gamePlayer;
					break;
				case 3:
					cout << "***What a tragedy!！Player[" << player[gamePlayer] << "]Pause a throw..." << endl;
					pausePlayer = 0;
					gamePlayer = !gamePlayer;
					break;
				case 4:
					cout << "***Nice！Player[" << player[gamePlayer] << "]Through the time tunnel..." << endl;
					playerPos[gamePlayer] += 10;
					if (playerPos[gamePlayer] >= 99) {
						gameOver();
					}
					gamePlayer = !gamePlayer;
					break;
				}
			}
		}
		else if (a == 'a') {
			winer = 0;
			gameOver();
		}
		else if (a == 'b') {
			winer = 1;
			gameOver();
		}
		for (int i = 0; i <= 1; i++) {
			if (playerPos[i] < 0)
				playerPos[i] = 0;
		}
		if (!isGameOver) {
			drowMap();
		}
	}
}

int main() {
	srand((unsigned)time(NULL));

	initUI();
	cout << "***Begins to initialize the Player Settings..." << endl;
	joinPlayer();
	initMap();
	drowMap();
	cout << "***This game begins：[" << player[0] << "] VS [" << player[1] << "]" << endl;
	gamePlayer = random(2);
	yaoYiYao();
	return 0;
}