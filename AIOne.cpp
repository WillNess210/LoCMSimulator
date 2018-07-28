#include <iostream>

using namespace std;
// USED IN MAIN:
// Card, Player, CardType, CardInfo, cardList, string strip(string), Game
class AI {
public:
	AI() {

	}
	string getAction() {
		return "PASS";
	}
	string getAttackAction() {
		string toReturn = "SUMMON 1";
		for (int i = 2; i < 60; i++) {
			toReturn = toReturn + "; SUMMON " + to_string(i);
		}
		for (int i = 1; i < 18; i++) {
			for (int j = -1; j < 18; j++) {
				toReturn = toReturn + "; ATTACK " + to_string(i) + " " + to_string(j);
				if (j == -1) {
					j++;
				}
			}
		}
		return toReturn;
	}
};
