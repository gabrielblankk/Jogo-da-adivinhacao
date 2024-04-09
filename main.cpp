#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
using namespace std;

int randomNumber(int maxNumber) {
	srand(time(0));
	int randNum = rand() % maxNumber;
	
	if (randNum == 0) {
		randNum++;
	}
	return randNum;
}

bool guess(int maxNumber, int maxAttempts) {
	int guess, attempts = 1;
	
	cout << "Número entre 1 e " << maxNumber << "." << endl << endl;
	int randNum = randomNumber(maxNumber);
	
	while(true) {
		// cout << randNum;
		cout << "Tentativa " << attempts << endl;
		cout << "Insira seu chute: " << endl;
		if (!(cin >> guess) || guess > maxNumber || guess < 1) {
			cin.clear();
			cin.ignore(500, '\n');
			cout << "Insira um valor válido." << endl << endl;
		} else {
			attempts ++;
			
			if (guess == randNum) {
				system("clear");
				cout << "ACERTOU!" << endl << endl;
				return true;
				break;
			} else if (guess < randNum) {
				cout << "Errou ;-;" << endl << "Seu chute foi menor que o número." << endl << endl;
			} else if (guess > randNum) {
				cout << "Errou ;-;" << endl << "Seu chute foi maior que o número." << endl << endl;
			}

			if (attempts > maxAttempts) {
				return false;
				break;
			}
		}
	}
}

bool playAgain() {
	int playAgain;
			
	while (true) {
		cout << endl << "Você deseja jogar novamente?" << endl;
		cout << "1 - Sim" << endl;
		cout << "2 - Não" << endl;

		if (!(cin >> playAgain) || playAgain > 2 || playAgain < 1) {
			cin.clear();
			cin.ignore(500, '\n');
			system("clear");
			cout << "Insira uma opção válida." << endl << endl;
		} else {
			break;
		}
	}

	return playAgain == 1 ? true : false;
}

void showScoreboard(vector<int>& scores, vector<string>& players) {
	for (int i = 0; i < players.size(); i++) {
		for (int j = i + 1; j < players.size(); j++) {
			if (scores[i] < scores[j]) {
				int aux = scores[i];
				scores[i] = scores[j];
				scores[j] = aux;
				string aux2 = players[i];
				players[i] = players[j];
				players[j] = aux2;
			}
		}
	}
	
	cout << endl << "--- PLACAR ---" << endl;
	int quant;
	
	if (players.size() <= 10) {
		quant = players.size();
	} else {
		quant = 10;
	}
	
	for (int i = 0; i < quant; i++) {
		cout << i+1 << "° - " << players[i] << " - " << scores[i] << endl;
	}
}

int main() {
	int level = 1, difficulty, score = 0, increase, maxAttempts, maxNumber;
	bool start = true;
	string playername;
	vector<string> players;
	vector<int> playerScores;
	
	while (true) {
		while (start) {
			cout << "Insira o nome do jogador: ";
			getline(cin >> ws, playername);
			players.push_back(playername);
			system("clear");
			cout << "Escolha a dificuldade: " << endl;
			cout << "1 - Noob" << endl;
			cout << "2 - Fácil" << endl;
			cout << "3 - Médio" << endl;
			cout << "4 - Difícil" << endl;
			cout << "5 - Insano" << endl;
		
			if (!(cin >> difficulty) || difficulty > 5 || difficulty < 1) {
				cin.clear();
				cin.ignore(500, '\n');
				system("clear");
				cout << "Insira uma opção válida." << endl << endl;
			} else {
				system("clear");	
				start = false;
			}
		}

		switch (level) {
			case 1:
				maxNumber = 20;
				break;
			case 2:
				maxNumber = 40;
				break;
			case 3:
				maxNumber = 60; 
				break;
			case 4:
				maxNumber = 80;
				break;
			case 5:
				maxNumber = 100;
				break;
			default:
				break;
		}
		
		switch (difficulty) {
			case 1:
				maxAttempts = 5;
				increase = 1;
				break;
			case 2:
				maxAttempts = 4;
				increase = 2;
				break;
			case 3:
				maxAttempts = 3;
				increase = 3;
				break;
			case 4:
				maxAttempts = 2;
				increase = 4;
				break;
			case 5:
				maxAttempts = 1;
				increase = 5;
				break;
			default:
				break;
		}
		
		cout << "FASE " << level << endl;
		cout << "DIFICULDADE " << difficulty << endl << endl;
		
		if (guess(maxNumber, maxAttempts)) {
			level++;
			score += increase;
		} else {
			system("clear");
			cout << "Você errou tudo." << endl;
			cout << "JOGO ENCERRADO." << endl;
			playerScores.push_back(score);
			showScoreboard(playerScores, players);
			if (!playAgain()) {
				break;
			} else {
				system("clear");
				level = 1;
				score = 0;
				start = true;
			}
		}
		
		if (level > 5) {
			system("clear");
			cout << "Parabéns, você ganhou!" << endl;
			playerScores.push_back(score);
			showScoreboard(playerScores, players);
			if (!playAgain()) {
				break;
			} else {
				system("clear");
				level = 1;
				score = 0;
				start = true;
			}
		}
	}
}