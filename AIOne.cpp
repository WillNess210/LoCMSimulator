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
		return "SUMMON 1; SUMMON 2; SUMMON 3; SUMMON 4; SUMMON 5; SUMMON 6; SUMMON 7; SUMMON 8; SUMMON 9; SUMMON 10; SUMMON 11; SUMMON 12;";
	}
};
