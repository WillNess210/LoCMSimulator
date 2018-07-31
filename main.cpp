#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Windows.h>
#include <iostream>
#include <list>
#include <fstream>
#include<stdio.h>
#include <cstdlib>
#include <sstream>
#include <vector>
#include "AIOne.cpp"

using namespace std;
class Card {
public:
	int cardNumber, instanceId, location, cardType, cost, attack, defense, myhealthChange, opponentHealthChange, cardDraw;
	vector<Card> itemsOn;
	bool canAttack, shield, breakthrough, charge, drain, guard, lethal, ward;
	Card() {
		cardNumber = -1;
		instanceId = -1;
		location = -1;
		cardType = -1;
		cost = -1;
		attack = -1;
		defense = -1;
		myhealthChange = -1;
		opponentHealthChange = -1;
		cardDraw = -1;
		canAttack = false;
		shield = false;
		breakthrough = false;
		charge = false;
		drain = false;
		guard = false;
		lethal = false;
		ward = false;
	}
	string getAbilities() {
		string abilities = "";
		if (breakthrough) {
			abilities += "B";
		}else{
			abilities += "-";
		}
		if (charge) {
			abilities += "C";
		}
		else {
			abilities += "-";
		}
		if (drain) {
			abilities += "D";
		}
		else {
			abilities += "-";
		}
		if (guard) {
			abilities += "G";
		}
		else {
			abilities += "-";
		}
		if (lethal) {
			abilities += "L";
		}
		else {
			abilities += "-";
		}
		if (ward) {
			abilities += "W";
		}
		else {
			abilities += "-";
		}
		return abilities;
	}
};
class Player {
public:
	vector<Card> hand;
	vector<Card> deck;
	vector<Card> board;
	int runes[5] = { 25, 20, 15, 10, 5 };
	int health, mana, nextCardDraw;
	Player() {
		mana = 0;
		health = 30;
		nextCardDraw = 0;
	}
	void loseNextRune() {
		int numRunesLeft = 0;
		bool lostRune = false;
		for (int i = 0; i < 5 && lostRune == false; i++) {
			if (runes[i] >= 5) {// must lose this rune
				lostRune = true;
				health = runes[i];
				runes[i] = -100;
				nextCardDraw++;
			}
			if (runes[i] >= 5) {
				numRunesLeft++;
			}
		}
		if (numRunesLeft == 0 && deck.size() == 0) {
			health = 0;
		}
	}
	void checkRunes() {
		int numRunesLeft = 0;
		for (int i = 0; i < 5; i++) {
			if (health < runes[i]) {
				// LOSE THIS RUNE
				runes[i] = -100;
				nextCardDraw++;
			}
			if (runes[i] >= 5) {
				numRunesLeft++;
			}
		}
		if (numRunesLeft == 0 && deck.size() == 0) {
			health = 0;
		}
	}
};
enum CardType
{
	creature, itemGreen, itemRed, itemBlue
};
struct CardInfo {
	int cardNumber;
	string name;
	CardType type;
	int cost;
	int attack;
	int defense;
	struct {
		int B, C, D, G, L, W;
	};
	int myhealthChange;
	int opponentHealthChange;
	int cardDraw;
	string textDesc;
	Card getCard() {
		Card a = Card();
		a.cardNumber = cardNumber;
		a.cost = cost;
		a.attack = attack;
		a.defense = defense;
		a.myhealthChange = myhealthChange;
		a.opponentHealthChange = opponentHealthChange;
		a.cardDraw = cardDraw;
		if (type == creature) {
			a.cardType = 0;
		}
		else if (type == itemGreen) {
			a.cardType = 1;
		}
		else if (type == itemRed) {
			a.cardType = 2;
		}
		else if (type == itemBlue) {
			a.cardType = 3;
		}
		if (B == 1) {
			a.breakthrough = true;
		}
		if (C == 1) {
			a.charge = true;
		}
		if (D == 1) {
			a.drain = true;
		}
		if (G == 1) {
			a.guard = true;
		}
		if (L == 1) {
			a.lethal = true;
		}
		if (W == 1) {
			a.ward = true;
		}
		return a;
	}
};
CardInfo cardlist[160] = {
	{ 1 , "Slimer" , creature , 1 , 2 , 1 ,{ 0, 0, 0, 0, 0, 0 }, +1 , 0 , 0 , "Summon: You gain 1 health. " },
{ 2 , "Scuttler" , creature , 1 , 1 , 2 ,{ 0, 0, 0, 0, 0, 0 }, 0 , -1 , 0 , "Summon: Deal 1 damage to your opponent.  " },
{ 3 , "Beavrat" , creature , 1 , 2 , 2 ,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , " " },
{ 4 , "Plated Toad" , creature , 2 , 1 , 5 ,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , " " },
{ 5 , "Grime Gnasher" , creature , 2 , 4 , 1 ,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , " " },
{ 6 , "Murgling" , creature , 2 , 3 , 2 ,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , " " },
{ 7 , "Rootkin Sapling" , creature , 2 , 2 , 2 ,{ 0, 0, 0, 0, 0, 1 }, 0 , 0 , 0 , " " },
{ 8 , "Psyshroom" , creature , 2 , 2 , 3 ,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , " " },
{ 9 , "Corrupted Beavrat" , creature , 3 , 3 , 4 ,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , " " },
{ 10 , "Carnivorous Bush" , creature , 3 , 3 , 1 ,{ 0, 0, 1, 0, 0, 0 }, 0 , 0 , 0 , " " },
{ 11 , "Snowsaur" , creature , 3 , 5 , 2 ,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , " " },
{ 12 , "Woodshroom", creature , 3 , 2 , 5 ,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , " " },
{ 13 , "Swamp Terror" , creature , 4 , 5 , 3 ,{ 0, 0, 0, 0, 0, 0 }, +1 , -1 , 0 , "Summon: You gain 1 health and deal\n1 damage to your opponent.  " },
{ 14 , "Fanged Lunger" , creature , 4 , 9 , 1 ,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , " " },
{ 15 , "Pouncing Flailmouth" , creature , 4 , 4 , 5 ,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , " " },
{ 16 , "Wrangler Fish" , creature , 4 , 6 , 2 ,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , " " },
{ 17 , "Ash Walker" , creature , 4 , 4 , 5 ,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , " " },
{ 18 , "Acid Golem" , creature , 4 , 7 , 4 ,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , " " },
{ 19 , "Foulbeast" , creature , 5 , 5 , 6 ,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , " " },
{ 20 , "Hedge Demon" , creature , 5 , 8 , 2 ,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , " " },
{ 21 , "Crested Scuttler" , creature , 5 , 6 , 5 ,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , " " },
{ 22 , "Sigbovak" , creature , 6 , 7 , 5 ,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , " " },
{ 23 , "Titan Cave Hog" , creature , 7 , 8 , 8 ,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , " " },
{ 24 , "Exploding Skitterbug" , creature , 1 , 1 , 1 ,{ 0, 0, 0, 0, 0, 0 }, 0 , -1 , 0 , "Summon: Deal 1 damage to your opponent.  " },
{ 25 , "Spiney Chompleaf" , creature , 2 , 3 , 1 ,{ 0, 0, 0, 0, 0, 0 }, -2 , -2 ,0 , "Summon: Deal 2 damage to each player.  " },
{ 26 , "Razor Crab" , creature , 2 , 3 , 2 ,{ 0, 0, 0, 0, 0, 0 }, 0 , -1 , 0 , "Summon: Deal 1 damage to your opponent.  " },
{ 27 , "Nut Gatherer" , creature , 2 , 2 , 2 ,{ 0, 0, 0, 0, 0, 0 }, +2 , 0 , 0 , "Summon: You gain 2 health.  " },
{ 28 , "Infested Toad" , creature , 2 , 1 , 2 ,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , +1 , "Summon: Draw a card.  " },
{ 29 , "Steelplume Nestling" , creature , 2 , 2 , 1 ,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , +1 , "Summon: Draw a card.  " },
{ 30 , "Venomous Bog Hopper" , creature , 3 , 4 , 2 ,{ 0, 0, 0, 0, 0, 0 }, 0 , -2 , 0 , "Summon: Deal 2 damage to your opponent.  " },
{ 31 , "Woodland Hunter" , creature , 3 , 3 , 1 ,{ 0, 0, 0, 0, 0, 0 }, 0 , -1 , 0 , "Summon: Deal 1 damage to your opponent.  " },
{ 32 , "Sandsplat" , creature , 3 , 3 , 2 ,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , +1 , "Summon: Draw a card.  " },
{ 33 , "Chameleskulk" , creature , 4 , 4 , 3 ,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , +1 , "Summon: Draw a card.  " },
{ 34 , "Eldritch Cyclops" , creature , 5 , 3 , 5 ,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , +1 , "Summon: Draw a card.  " },
{ 35 , "Snail-eyed Hulker" , creature , 6 , 5 , 2 ,{ 1, 0, 0, 0, 0, 0 }, 0 , 0 , +1 , "Summon: Draw a card.  " },
{ 36 , "Possessed Skull" , creature , 6 , 4 , 4 ,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , +2 , "Summon: Draw two cards.  " },
{ 37 , "Eldritch Multiclops" , creature , 6 , 5 , 7 ,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , +1 , "Summon: Draw a card.  " },
{ 38 , "Imp" , creature , 1 , 1 , 3 ,{ 0, 0, 1, 0, 0, 0 }, 0 , 0 , 0 , " " },
{ 39 , "Voracious Imp" , creature , 1 , 2 , 1 ,{ 0, 0, 1, 0, 0, 0 }, 0 , 0 , 0 , " " },
{ 40 , "Rock Gobbler" , creature , 3 , 2 , 3 ,{ 0, 0, 1, 1, 0, 0 }, 0 , 0 , 0 , " " },
{ 41 , "Blizzard Demon" , creature , 3 , 2 , 2 ,{ 0, 1, 1, 0, 0, 0 }, 0 , 0 , 0 , " " },
{ 42 , "Flying Leech" , creature , 4 , 4 , 2 ,{ 0, 0, 1, 0, 0, 0 }, 0 , 0 , 0 , " " },
{ 43 , "Screeching Nightmare" , creature , 6 , 5 , 5 ,{ 0, 0, 1, 0, 0, 0 }, 0 , 0 , 0 , " " },
{ 44 , "Deathstalker" , creature , 6 , 3 , 7 ,{ 0, 0, 1, 0, 1, 0 }, 0 , 0 , 0 , " " },
{ 45 , "Night Howler" , creature , 6 , 6 , 5 ,{ 1, 0, 1, 0, 0, 0 }, -3 , 0 , 0 , " " },
{ 46 , "Soul Devourer" , creature , 9 , 7 , 7 ,{ 0, 0, 1, 0, 0, 0 }, 0 , 0 , 0 , " " },
{ 47 , "Gnipper" , creature , 2 , 1 , 5 ,{ 0, 0, 1, 0, 0, 0 }, 0 , 0 , 0 , " " },
{ 48 , "Venom Hedgehog" , creature , 1 , 1 , 1 ,{ 0, 0, 0, 0, 1, 0 }, 0 , 0 , 0 , " " },
{ 49 , "Shiny Prowler" , creature , 2 , 1 , 2 ,{ 0, 0, 0, 1, 1, 0 }, 0 , 0 , 0 , " " },
{ 50 , "Puff Biter" , creature , 3 , 3 , 2 ,{ 0, 0, 0, 0, 1, 0 }, 0 , 0 , 0 , " " },
{ 51 , "Elite Bilespitter" , creature , 4 , 3 , 5 ,{ 0, 0, 0, 0, 1, 0 }, 0 , 0 , 0 , " " },
{ 52 , "Bilespitter" , creature , 4 , 2 , 4 ,{ 0, 0, 0, 0, 1, 0 }, 0 , 0 , 0 , " " },
{ 53 , "Possessed Abomination" , creature , 4 , 1 , 1 ,{ 0, 1, 0, 0, 1, 0 }, 0 , 0 , 0 , " " },
{ 54 , "Shadow Biter" , creature , 3 , 2 , 2 ,{ 0, 0, 0, 0, 1, 0 }, 0 , 0 , 0 , " " },
{ 55 , "Hermit Slime" , creature , 2 , 0 , 5 ,{ 0, 0, 0, 1, 0, 0 }, 0 , 0 , 0 , " " },
{ 56 , "Giant Louse" , creature , 4 , 2 , 7 ,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , " " },
{ 57 , "Dream-Eater" , creature , 4 , 1 , 8 ,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , " " },
{ 58 , "Darkscale Predator" , creature , 6 , 5 , 6 ,{ 1, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , " " },
{ 59 , "Sea Ghost" , creature , 7 , 7 , 7 ,{ 0, 0, 0, 0, 0, 0 }, +1 , -1 , 0 , "Summon: You gain 1 health and deal\n1 damage to your opponent.  " },
{ 60 , "Gritsuck Troll" , creature , 7 , 4 , 8 ,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , " " },
{ 61 , "Alpha Troll" , creature , 9 , 10 , 10 ,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , " " },
{ 62 , "Mutant Troll" , creature , 12 , 12 , 12 ,{ 1, 0, 0, 1, 0, 0 }, 0 , 0 ,0 , " " },
{ 63 , "Rootkin Drone" , creature , 2 , 0 , 4 ,{ 0, 0, 0, 1, 0, 1 }, 0 , 0 , 0 , " " },
{ 64 , "Coppershell Tortoise" , creature , 2 , 1 , 1 ,{ 0, 0, 0, 1, 0, 1 }, 0 , 0 , 0 , " " },
{ 65 , "Steelplume Defender" , creature , 2 , 2 , 2 ,{ 0, 0, 0, 0, 0, 1 }, 0 , 0 , 0 , " " },
{ 66 , "Staring Wickerbeast" , creature , 5 , 5 , 1 ,{ 0, 0, 0, 0, 0, 1 }, 0 , 0 , 0 , " " },
{ 67 , "Flailing Hammerhead" , creature , 6 , 5 , 5 ,{ 0, 0, 0, 0, 0, 1 }, 0 , -2 , 0, "Summon: Deal 2 damage to your opponent.  " },
{ 68 , "Giant Squid" , creature , 6 , 7 , 5 ,{ 0, 0, 0, 0, 0, 1 }, 0 , 0 , 0 , " " },
{ 69 , "Charging Boarhound" , creature , 3 , 4 , 4 ,{ 1, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , " " },
{ 70 , "Murglord" , creature , 4 , 6 , 3 ,{ 1, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , " " },
{ 71 , "Flying Murgling" , creature , 4 , 3 , 2 ,{ 1, 1, 0, 0, 0, 0 }, 0 , 0 , 0 , " " },
{ 72 , "Shuffling Nightmare" , creature , 4 , 5 , 3 ,{ 1, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , " " },
{ 73 , "Bog Bounder" , creature , 4 , 4 , 4 ,{ 1, 0, 0, 0, 0, 0 }, +4 , 0 , 0, "Summon: You gain 4 health.  " },
{ 74 , "Crusher" , creature , 5 , 5 , 4 ,{ 1, 0, 0, 1, 0, 0 }, 0 , 0 , 0 , " " },
{ 75 , "Titan Prowler" , creature , 5 , 6 , 5 ,{ 1, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , " " },
{ 76 , "Crested Chomper" , creature , 6 , 5 , 5 ,{ 1, 0, 1, 0, 0, 0 }, 0 , 0 , 0 , " " },
{ 77 , "Lumbering Giant" , creature , 7 , 7 , 7 ,{ 1, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , " " },
{ 78 , "Shambler" , creature , 8 , 5 , 5 ,{ 1, 0, 0, 0, 0, 0 }, 0 , -5 , 0, "Summon: Deal 5 damage to your opponent.  " },
{ 79 , "Scarlet Colossus" , creature , 8 , 8 , 8 ,{ 1, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , " " },
{ 80 , "Corpse Guzzler" , creature , 8 , 8 , 8 ,{ 1, 0, 0, 1, 0, 0 }, 0 , 0 , +1, "Summon: Draw a card.  " },
{ 81 , "Flying Corpse Guzzler" , creature , 9 , 6 , 6 ,{ 1, 1, 0, 0, 0, 0 }, 0 , 0 , 0 , " " },
{ 82 , "Slithering Nightmare" , creature , 7 , 5 , 5 ,{ 1, 0, 1, 0, 0, 1 }, 0 , 0 , 0 , " " },
{ 83 , "Restless Owl" , creature , 0 , 1 , 1 ,{ 0, 1, 0, 0, 0, 0 }, 0 , 0 , 0 , " " },
{ 84 , "Fighter Tick" , creature , 2 , 1 , 1 ,{ 0, 1, 1, 0, 0, 1 }, 0 , 0 , 0 , " " },
{ 85 , "Heartless Crow" , creature , 3 , 2 , 3 ,{ 0, 1, 0, 0, 0, 0 }, 0 , 0 , 0 , " " },
{ 86 , "Crazed Nose-pincher" , creature , 3 , 1 , 5 ,{ 0, 1, 0, 0, 0, 0 }, 0 , 0 , 0 , " " },
{ 87 , "Bloat Demon" , creature , 4 , 2 , 5 ,{ 0, 1, 0, 1, 0, 0 }, 0 , 0 , 0 , " " },
{ 88 , "Abyss Nightmare" , creature , 5 , 4 , 4 ,{ 0, 1, 0, 0, 0, 0 }, 0 , 0 , 0 , " " },
{ 89 , "Boombeak" , creature , 5 , 4 , 1 ,{ 0, 1, 0, 0, 0, 0 }, 2 , 0 , 0 , " " },
{ 90 , "Eldritch Swooper" , creature , 8 , 5 , 5 ,{ 0, 1, 0, 0, 0, 0 }, 0 , 0 , 0 , " " },
{ 91 , "Flumpy" , creature , 0 , 1 , 2 ,{ 0, 0, 0, 1, 0, 0 }, 0 , +1 , 0 , "Summon: Your opponent gains 1 health  " },
{ 92 , "Wurm" , creature , 1 , 0 , 1 ,{ 0, 0, 0, 1, 0, 0 }, +2 , 0 , 0, "Summon: You gain 2 health.  " },
{ 93 , "Spinekid" , creature , 1 , 2 , 1 ,{ 0, 0, 0, 1, 0, 0 }, 0 , 0 , 0 , " " },
{ 94 , "Rootkin Defender" , creature , 2 , 1 , 4 ,{ 0, 0, 0, 1, 0, 0 }, 0 , 0 , 0 , " " },
{ 95 , "Wildum" , creature , 2 , 2 , 3 ,{ 0, 0, 0, 1, 0, 0 }, 0 , 0 , 0 , " " },
{ 96 , "Prairie Protector" , creature , 2 , 3 , 2 ,{ 0, 0, 0, 1, 0, 0 }, 0 , 0 , 0 , " " },
{ 97 , "Turta" , creature , 3 , 3 , 3 ,{ 0, 0, 0, 1, 0, 0 }, 0 , 0 , 0 , " " },
{ 98 , "Lilly Hopper" , creature , 3 , 2 , 4 ,{ 0, 0, 0, 1, 0, 0 }, 0 , 0 , 0 , " " },
{ 99 , "Cave Crab" , creature , 3 , 2 , 5 ,{ 0, 0, 0, 1, 0, 0 }, 0 , 0 , 0 , " " },
{ 100 , "Stalagopod" , creature , 3 , 1 , 6 ,{ 0, 0, 0, 1, 0, 0 }, 0 , 0 , 0 , " " },
{ 101 , "Engulfer" , creature , 4 , 3 , 4 ,{ 0, 0, 0, 1, 0, 0 }, 0 , 0 , 0 , " " },
{ 102 , "Mole Demon" , creature , 4 , 3 , 3 ,{ 0, 0, 0, 1, 0, 0 }, 0 , -1 , 0, "Summon: Deal 1 damage to your opponent.  " },
{ 103 , "Mutating Rootkin" , creature , 4 , 3 , 6 ,{ 0, 0, 0, 1, 0, 0 }, 0 , 0 , 0 , " " },
{ 104 , "Deepwater Shellcrab" , creature , 4 , 4 , 4 ,{ 0, 0, 0, 1, 0, 0 }, 0 , 0 , 0 , " " },
{ 105 , "King Shellcrab" , creature , 5 , 4 , 6 ,{ 0, 0, 0, 1, 0, 0 }, 0 , 0 , 0 , " " },
{ 106 , "Far-reaching Nightmare" , creature , 5 , 5 , 5 ,{ 0, 0, 0, 1, 0, 0 }, 0 , 0 , 0 , " " },
{ 107 , "Worker Shellcrab" , creature , 5 , 3 , 3 ,{ 0, 0, 0, 1, 0, 0 }, +3 , 0 , 0, "Summon: You gain 3 health.  " },
{ 108 , "Rootkin Elder" , creature , 5 , 2 , 6 ,{ 0, 0, 0, 1, 0, 0 }, 0 , 0 , 0 , " " },
{ 109 , "Elder Engulfer" , creature , 5 , 5 , 6 ,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , " " },
{ 110 , "Gargoyle" , creature , 5 , 0 , 9 ,{ 0, 0, 0, 1, 0, 0 }, 0 , 0 , 0 , " " },
{ 111 , "Turta Knight" , creature , 6 , 6 , 6 ,{ 0, 0, 0, 1, 0, 0 }, 0 , 0 , 0 , " " },
{ 112 , "Rootkin Leader" , creature , 6 , 4 , 7 ,{ 0, 0, 0, 1, 0, 0 }, 0 , 0 , 0 , " " },
{ 113 , "Tamed Bilespitter" , creature , 6 , 2 , 4 ,{ 0, 0, 0, 1, 0, 0 }, +4 , 0 , 0, "Summon: You gain 4 health.  " },
{ 114 , "Gargantua" , creature , 7 , 7 , 7 ,{ 0, 0, 0, 1, 0, 0 }, 0 , 0 , 0 , " " },
{ 115 , "Rootkin Warchief" , creature , 8 , 5 , 5 ,{ 0, 0, 0, 1, 0, 1 }, 0 , 0 , 0 , " " },
{ 116 , "Emperor Nightmare" , creature , 12 , 8 , 8 ,{ 1, 1, 1, 1, 1, 1 }, 0 , 0 , 0, " " },
{ 117 , "Protein" , itemGreen , 1 , +1 , +1 ,{ 1, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , "Give a friendly creature +1/+1 and Breakthrough.  " },
{ 118 , "Royal Helm" , itemGreen , 0 , 0 , +3 ,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , "Give a friendly creature +0/+3.  " },
{ 119 , "Serrated Shield" , itemGreen , 1 , +1 , +2 ,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , "Give a friendly creature +1/+2.  " },
{ 120 , "Venomfruit" , itemGreen , 2 , +1 , 0 ,{ 0, 0, 0, 0, 1, 0 }, 0 , 0 , 0 , "Give a friendly creature +1/+0 and Lethal.  " },
{ 121 , "Enchanted Hat" , itemGreen , 2 , 0 , +3 ,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , +1 , "Give a friendly creature +0/+3.\nDraw a card.  " },
{ 122 , "Bolstering Bread" , itemGreen , 2 , +1 , +3 ,{ 0, 0, 0, 1, 0, 0 }, 0 , 0 , 0 , "Give a friendly creature +1/+3 and Guard.  " },
{ 123 , "Wristguards" , itemGreen , 2 , +4 , 0 ,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , "Give a friendly creature +4/+0.  " },
{ 124 , "Blood Grapes" , itemGreen , 3 , +2 , +1 ,{ 0, 0, 1, 0, 0, 0 }, 0 , 0 , 0 , "Give a friendly creature +2/+1 and Drain.  " },
{ 125 , "Healthy Veggies" , itemGreen , 3 , +1 , +4 ,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , "Give a friendly creature +1/+4.  " },
{ 126 , "Heavy Shield" , itemGreen , 3 , +2 , +3 ,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , "Give a friendly creature +2/+3.  " },
{ 127 , "Imperial Helm" , itemGreen , 3 , 0 , +6 ,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , "Give a friendly creature +0/+6.  " },
{ 128 , "Enchanted Cloth" , itemGreen , 4 , +4 , +3 ,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , "Give a friendly creature +4/+3.  " },
{ 129 , "Enchanted Leather" , itemGreen , 4 , +2 , +5 ,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , "Give a friendly creature +2/+5.  " },
{ 130 , "Helm of Remedy" , itemGreen , 4 , 0 , +6 ,{ 0, 0, 0, 0, 0, 0 }, +4 , 0 , 0 , "Give a friendly creature +0/+6.\nYou gain 4 health.  " },
{ 131 , "Heavy Gauntlet" , itemGreen , 4 , +4 , +1 ,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , "Give a friendly creature +4/+1.  " },
{ 132 , "High Protein" , itemGreen , 5 , +3 , +3 ,{ 1, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , "Give a friendly creature +3/+3 and Breakthrough.  " },
{ 133 , "Pie of Power" , itemGreen , 5 , +4 , 0 ,{ 0, 0, 0, 0, 0, 1 }, 0 , 0 , 0 , "Give a friendly creature +4/+0 and Ward.  " },
{ 134 , "Light The Way" , itemGreen , 4 , +2 , +2 ,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , +1, "Give a friendly creature +2/+2.\nDraw a card.  " },
{ 135 , "Imperial Armour" , itemGreen , 6 , +5 , +5 ,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , "Give a friendly creature +5/+5.  " },
{ 136 , "Buckler" , itemGreen , 0 , +1 , +1 ,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , "Give a friendly creature +1/+1.  " },
{ 137 , "Ward" , itemGreen , 2 , 0 , 0 ,{ 0, 0, 0, 0, 0, 1 }, 0 , 0 , 0 , "Give a friendly creature Ward.  " },
{ 138 , "Grow Horns" , itemGreen , 2 , 0 , 0 ,{ 0, 0, 0, 1, 0, 0 }, 0 , 0 , +1 , "Give a friendly creature Guard.\nDraw a card.  " },
{ 139 , "Grow Stingers" , itemGreen , 4 , 0 , 0 ,{ 0, 0, 0, 0, 1, 1 }, 0 , 0 , 0 , "Give a friendly creature Lethal and Ward.  " },
{ 140 , "Grow Wings" , itemGreen , 2 , 0 , 0 ,{ 0, 1, 0, 0, 0, 0 }, 0 , 0 , 0 , "Give a friendly creature Charge.  " },
{ 141 , "Throwing Knife" , itemRed , 0 , -1 , -1,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , "Give an enemy creature -1/-1.  " },
{ 142 , "Staff of Suppression" , itemRed , 0 , 0 , 0,{ 1, 1, 1, 1, 1, 1 }, 0 , 0 , 0 , "Remove all abilities from an enemy creature.  " },
{ 143 , "Pierce Armour" , itemRed , 0 , 0 , 0,{ 0, 0, 0, 1, 0, 0 }, 0 , 0 , 0 , "Remove Guard from an enemy creature.  " },
{ 144 , "Rune Axe" , itemRed , 1 , 0 , -2,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , "Deal 2 damage to an enemy creature.  " },
{ 145 , "Cursed Sword" , itemRed , 3 , -2 , -2,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , "Give an enemy creature -2/-2.  " },
{ 146 , "Cursed Scimitar" , itemRed , 4 , -2 , -2,{ 0, 0, 0, 0, 0, 0 }, 0 , -2 , 0 , "Give an enemy creature -2/-2.\nDeal 2 damage to your opponent.  " },
{ 147 , "Quick Shot" , itemRed , 2 , 0 , -1,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , +1 , "Deal 1 damage to an enemy creature.\nDraw a card.  " },
{ 148 , "Helm Crusher" , itemRed , 2 , 0 , -2,{ 1, 1, 1, 1, 1, 1 }, 0 , 0 , 0 , "Remove all abilities from an enemy creature,\nthen deal 2 damage to it.  " },
{ 149 , "Rootkin Ritual" , itemRed , 3 , 0 , 0,{ 1, 1, 1, 1, 1, 1 }, 0 , 0 , +1 , "Remove all abilities from an enemy creature.\nDraw a card.  " },
{ 150 , "Throwing Axe" , itemRed , 2 , 0 , -3,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , "Deal 3 damage to an enemy creature.  " },
{ 151 , "Decimate" , itemRed , 5 , 0 , -99,{ 1, 1, 1, 1, 1, 1 }, 0 , 0 , 0 , "Remove all abilities from an enemy creature,\nthen deal 99 damage to it.  " },
{ 152 , "Mighty Throwing Axe" , itemRed , 7 , 0 , -7,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , +1 , "Deal 7 damage to an enemy creature.\nDraw a card.  " },
{ 153 , "Healing Potion" , itemBlue , 2 , 0 , 0,{ 0, 0, 0, 0, 0, 0 }, +5 , 0 , 0 , "Gain 5 health.  " },
{ 154 , "Poison" , itemBlue , 2 , 0 , 0,{ 0, 0, 0, 0, 0, 0 }, 0 , -2 , +1 , "Deal 2 damage to your opponent.\nDraw a card  " },
{ 155 , "Scroll of Firebolt" , itemBlue , 3 , 0, -3,{ 0, 0, 0, 0, 0, 0 }, 0 , -1 , 0 , "Deal 3 damage.\nDeal 1 damage to your opponent  " },
{ 156 , "Major Life Steal Potion" , itemBlue , 3 , 0 , 0,{ 0, 0, 0, 0, 0, 0 }, +3 , -3 , 0 , "Deal 3 damage to your opponent and gain 3 health.  " },
{ 157 , "Life Sap Drop" , itemBlue , 3 , 0 , -1,{ 0, 0, 0, 0, 0, 0 }, +1 , 0 , +1, "Deal 1 damage, gain 1 health, and draw a card.  " },
{ 158 , "Tome of Thunder" , itemBlue , 3 , 0 , -4,{ 0, 0, 0, 0, 0, 0 }, 0 , 0 , 0 , "Deal 4 damage.  " },
{ 159 , "Vial of Soul Drain" , itemBlue , 4 , 0 , -3,{ 0, 0, 0, 0, 0, 0 }, +3 , 0 , 0 , "Deal 3 damage and gain 3 health.  " },
{ 160 , "Minor Life Steal Potion" , itemBlue , 2 , 0 , 0,{ 0, 0, 0, 0, 0, 0 }, +2 , -2 , 0 , "Deal 2 damage to your opponent and gain 2 health.  " }
};
sf::Texture* backs = new sf::Texture();
sf::Sprite getBackground() {
	sf::Sprite sprite;
	sprite.setTexture(*backs);
	return sprite;
}
sf::Texture* cards = new sf::Texture();
sf::Sprite getCard(int id) {
	id--;
	int cardsPerRow = 10;
	int cardWidth = 150;
	int cardHeight = 185;
	int row = round(id / cardsPerRow);
	int column = id % cardsPerRow;
	int minX = column * cardWidth;
	int minY = row * cardHeight;
	sf::Sprite sprite;
	sprite.setTexture(*cards);
	sprite.setTextureRect(sf::IntRect(minX, minY, cardWidth, cardHeight));
	sprite.setScale(2.0f, 2.0f);
	return sprite;
}
sf::Sprite getCardHand(int id) {
	id--;
	int cardsPerRow = 10;
	int cardWidth = 150;
	int cardHeight = 185;
	int row = round(id / cardsPerRow);
	int column = id % cardsPerRow;
	int minX = column * cardWidth;
	int minY = row * cardHeight;
	sf::Sprite sprite;
	sprite.setTexture(*cards);
	sprite.setTextureRect(sf::IntRect(minX, minY, cardWidth, cardHeight));
	//sprite.setScale(1.0f, 1.0f);
	return sprite;
}
sf::Sprite getCardDrafted(int id) {
	id--;
	int cardsPerRow = 10;
	int cardWidth = 150;
	int cardHeight = 185;
	int row = round(id / cardsPerRow);
	int column = id % cardsPerRow;
	int minX = column * cardWidth;
	int minY = row * cardHeight;
	sf::Sprite sprite;
	sprite.setTexture(*cards);
	sprite.setTextureRect(sf::IntRect(minX, minY, cardWidth, cardHeight));
	sprite.setScale(0.7f, 0.7f);
	return sprite;
}
sf::Sprite getCardBoard(int id) {
	id--;
	int cardsPerRow = 10;
	int cardWidth = 150;
	int cardHeight = 185;
	int row = round(id / cardsPerRow);
	int column = id % cardsPerRow;
	int minX = column * cardWidth;
	int minY = row * cardHeight;
	sf::Sprite sprite;
	sprite.setTexture(*cards);
	sprite.setTextureRect(sf::IntRect(minX, minY, cardWidth, cardHeight));
	sprite.setScale(1.3f, 1.3f);
	return sprite;
}
string strip(string in) {
	int first = -1;
	int end = -1;
	for (int i = 0; i < in.length() && first == -1; i++) {
		if (in[i] != ' ') {
			first = i;
		}
	}
	for (int i = in.length() - 1; i >= 0 && end == -1; i--) {
		if (in[i] != ' ') {
			end = i;
		}
	}
	if (first == -1 || end == -1) {
		return in;
	}
	return in.substr(first, end - first + 1);
}
class Game {
public:
	int turn, cardIds;
	AI AIs[2];
	Player players[2];
	Card toDraft[3];
	Game() {
		turn = 0;
		cardIds = 1;
		for (int i = 0; i < 2; i++) {
			AIs[i] = AI();
			players[i] = Player();
		}
	}
	void render(sf::RenderWindow &window) {
		window.clear(sf::Color(100, 149, 237));
		window.draw(getBackground());
		sf::Font font;
		font.loadFromFile("C:/Users/WillN/Documents/Visual Studio 2017/LoCM/resources/GOTHIC.TTF");
		sf::Text text;
		text.setFont(font);
		if (turn < 30) { // DRAFT STAGE
			// DRAW AVAILABLE CARDS TO DRAFT
			text.setCharacterSize(40);
			for (int i = 0; i < 3; i++) {
				sf::Sprite cardOne = getCard(toDraft[i].cardNumber);
				cardOne.setPosition(650 + i*400, 350);
				window.draw(cardOne);
				text.setString(to_string(toDraft[i].attack));
				text.setPosition(670 + i*400, 530);
				window.draw(text);
				text.setString(to_string(toDraft[i].cost));
				text.setPosition(790 + i * 400, 545);
				window.draw(text);
				text.setString(to_string(toDraft[i].defense));
				text.setPosition(910 + i * 400, 530);
				window.draw(text);
				text.setString(toDraft[i].getAbilities());
				text.setPosition(720 + i * 400, 630);
				window.draw(text);
			}
			// DRAW DRAFTED CARDS
			sf::Sprite draftedOne = getCardDrafted(players[0].deck.back().cardNumber);
			draftedOne.setPosition(325, 310);
			sf::Sprite draftedTwo = getCardDrafted(players[1].deck.back().cardNumber);
			draftedTwo.setPosition(325, 910);
			window.draw(draftedOne);
			window.draw(draftedTwo);
		} 
		else { // ATTACK STAGE
			// HAND
			int startX = 500;
			int ys[2] = { 875, 25 };
			int spaceBetween = 177;
			for (int j = 0; j < 2; j++) {
				for (int i = 0; i < players[j].hand.size(); i++) {
					sf::Sprite thisCard = getCardHand(players[j].hand[i].cardNumber);
					thisCard.setPosition(startX + i * spaceBetween, ys[j]);
					window.draw(thisCard);
					text.setCharacterSize(40);
					text.setString(to_string(players[j].hand[i].instanceId));
					text.setPosition(startX + 10 + i * spaceBetween, ys[j] + 5);
					window.draw(text);
					text.setCharacterSize(30);
					text.setString(to_string(players[j].hand[i].attack));
					text.setPosition(startX + 5 + i * spaceBetween, ys[j] + 83);
					window.draw(text);
					text.setString(to_string(players[j].hand[i].cost));
					text.setPosition(startX + 63 + i * spaceBetween, ys[j] + 90);
					window.draw(text);
					text.setString(to_string(players[j].hand[i].defense));
					text.setPosition(startX + 115 + i * spaceBetween, ys[j] + 83);
					window.draw(text);
					text.setString(players[j].hand[i].getAbilities());
					text.setPosition(startX + 10 + i * spaceBetween, ys[j] + 140);
					window.draw(text);
				}
			}
			// BOARD
			
			startX = 500;
			int bys[2] = { 575, 275 };
			spaceBetween = 240;
			for (int j = 0; j < 2; j++) {
				for (int i = 0; i < players[j].board.size(); i++) {
					sf::Sprite thisCard = getCardBoard(players[j].board[i].cardNumber);
					thisCard.setPosition(startX + i * spaceBetween, bys[j]);
					window.draw(thisCard);
					text.setCharacterSize(60);
					text.setString(to_string(players[j].board[i].instanceId));
					text.setPosition(startX + 10 + i * spaceBetween, bys[j] + 5);
					window.draw(text);
					text.setCharacterSize(40);
					text.setString(to_string(players[j].board[i].attack));
					text.setPosition(startX + 10 + i * spaceBetween, bys[j] + 100);
					window.draw(text);
					text.setString(to_string(players[j].board[i].cost));
					text.setPosition(startX + 85 + i * spaceBetween, bys[j] + 120);
					window.draw(text);
					text.setString(to_string(players[j].board[i].defense));
					text.setPosition(startX + 160 + i * spaceBetween, bys[j] + 100);
					window.draw(text);
					text.setString(players[j].board[i].getAbilities());
					text.setPosition(startX + 40 + i * spaceBetween, bys[j] + 170);
					window.draw(text);
				}
			}
			// PLAYER ONE HEALTH
			text.setCharacterSize(60);
			text.setString(to_string(players[0].health));
			text.setPosition(60, 940);
			window.draw(text);
			// PLAYER ONE MANA
			text.setString(to_string(players[0].mana));
			text.setPosition(210, 940);
			window.draw(text);
			// PLAYER TWO HEALTH
			text.setString(to_string(players[1].health));
			text.setPosition(60, 335);
			window.draw(text);
			// PLAYER TWO MANA
			text.setString(to_string(players[1].mana));
			text.setPosition(210, 335);
			window.draw(text);
		}
		window.display();
	}
	void play() {
		bool cardUsed[160];
		for (int i = 0; i < 160; i++) {
			cardUsed[i] = false;
		}
		if (turn < 30) { // DRAFT PHASE
			// CHOOSE 3 RANDOM CARDS
			cout << "DRAFT: " << turn << endl;
			for (int i = 0; i < 3; i++) {
				int suggestedCard = rand() % 160;
				while (cardUsed[suggestedCard]) {
					suggestedCard = rand() % 160;
				}
				cardUsed[suggestedCard] = true;
				toDraft[i] = cardlist[suggestedCard].getCard();
				cout << toDraft[i].cardNumber << endl;
			}
			// PUT CARDS ON BOARD
			for (int i = 0; i < 2; i++) {
				// GIVE INFORMATION TO AI
				// GET RESPONSE FROM AI
				string action = AIs[i].getAction();
				stringstream ss;
				ss << action;
				string sChoice = "";
				int choice = -1;
				ss >> sChoice;
				if (sChoice == "PASS") {
					choice = 0;
				}else if (sChoice == "PICK") {
					ss >> choice;
				}
				// UPDATE BOARD
				players[i].deck.push_back(toDraft[choice]);
			}
		}
		else { // ATTACK PHASE
			cout << "ATTACK: " << turn << endl;
			for (int i = 0; i < 2; i++) {
				// DRAW CARDS
				players[i].nextCardDraw += 1;
				if (turn == 30) { // assign cards, 4 to player 1, 5 to player 2
					players[i].nextCardDraw = 5;
					if (i == 0) {
						players[i].nextCardDraw = 4;
					}
				}
				for (int j = 0; j < players[i].nextCardDraw; j++) {
					if (players[i].hand.size() < 8) {
						if (players[i].deck.size() > 0) {
							int randCard = rand() % players[i].deck.size();
							players[i].deck[randCard].instanceId = cardIds++;
							players[i].hand.push_back(players[i].deck[randCard]);
							players[i].deck.erase(players[i].deck.begin() + randCard);
						}
						else {
							players[i].loseNextRune();
						}
					}
				}
				players[i].nextCardDraw = 0;
				// MANA
				if (players[i].mana < 12) {
					players[i].mana++;
				}
				// SET ALL CREATURES ON BOARD TO CAN ATTACK
				for (int j = 0; j < players[i].board.size(); j++) {
					players[i].board[j].canAttack = true;
				}
				// GIVE INFORMATION TO PLAYER
				// GET ACTION FROM PLAYER
				string action = AIs[i].getAttackAction();
				action = strip(action);
				vector<string> actions;
				stringstream ss;
				ss << action;
				string str;
				while (getline(ss, str, ';')) {
					str = strip(str);
					actions.push_back(str);
				}
				// COMPLETE ACTIONS
				int opInd = (i + 1) % 2;
				for (int j = 0; j < actions.size(); j++) {
					string action = actions[j];
					vector<string> actionParts;
					stringstream ss;
					ss << action;
					string str;
					while (getline(ss, str, ' ') && actionParts.size() < 3) {
						actionParts.push_back(str);
					}
					string type = actionParts[0];
					if (type == "SUMMON") {
						int IDToSummon = stoi(actionParts[1]);
						int handPos = -1;
						Card toSummon;
						for (int k = 0; k < players[i].hand.size(); k++) {
							if (players[i].hand[k].instanceId == IDToSummon) {
								toSummon = players[i].hand[k];
								handPos = k;
							}
						}
						if (handPos >= 0 && players[i].board.size() < 6 && players[i].mana >= toSummon.cost && toSummon.cardType == 0) {
							players[i].mana -= toSummon.cost;
							if (players[i].hand[handPos].charge) {
								players[i].hand[handPos].canAttack = true;
							}
							if (players[i].hand[handPos].ward) {
								players[i].hand[handPos].shield = true;
							}
							players[i].board.push_back(players[i].hand[handPos]);
							players[i].hand.erase(players[i].hand.begin() + handPos);
							players[i].health += toSummon.myhealthChange;
							players[opInd].health += toSummon.opponentHealthChange;
							cout << action << ";";
						}
						else {
							//cout << action << " IS INVALID. " << endl;
						}
					}else if (type == "ATTACK") {
						int IDOfAttacker = stoi(actionParts[1]);
						int IDOfOpponent = stoi(actionParts[2]);
						// FINDING ATTACKER
						int attackerPos = -1;
						for (int k = 0; k < players[i].board.size(); k++) {
							if (players[i].board[k].instanceId == IDOfAttacker) {
								attackerPos = k;
							}
						}
						if (IDOfOpponent >= 1 && attackerPos >= 0) { // CREATURE ON CREATURE ATTACK
							// FINDING OPPONENT
							int opponentPos = -1;
							for (int k = 0; k < players[opInd].board.size(); k++) {
								if (players[opInd].board[k].instanceId == IDOfOpponent) {
									opponentPos = k;
								}
							}
							if (opponentPos >= 0) {
								if (players[i].board[attackerPos].canAttack) {
									players[i].board[attackerPos].canAttack = false;
									// APPLYING ATTACKS TO CARDS and including Ward
									int extraDmg = players[opInd].board[opponentPos].defense - players[i].board[attackerPos].attack; // will be negative or 0 if opp dies
									bool defenderShielded = false;
									if (players[opInd].board[opponentPos].shield) {
										defenderShielded = true;
										players[opInd].board[opponentPos].shield = false;
										extraDmg = 0;
									}else {
										players[opInd].board[opponentPos].defense -= players[i].board[attackerPos].attack;
									}
									bool attackerShielded = false;
									if (players[i].board[attackerPos].shield) {
										attackerShielded = true;
										players[i].board[attackerPos].shield = false;
									}else {
										players[i].board[attackerPos].defense -= players[opInd].board[opponentPos].attack;
									}
									// CHECKING FOR DRAIN
									if (players[i].board[attackerPos].drain && defenderShielded == false) {
										players[i].health += players[i].board[attackerPos].attack;
									}
									// CHECKING FOR DEATHS
									if (players[opInd].board[opponentPos].defense <= 0) {
										players[opInd].board.erase(players[opInd].board.begin() + opponentPos);
										// CHECK FOR BREAKTHROUGH AND APPLY DAMAGE TO OPPONENT
										if (players[i].board[attackerPos].breakthrough) {
											players[opInd].health += extraDmg;
										}
									}else if (players[i].board[attackerPos].lethal && defenderShielded == false) { // CHECKING FOR LETHAL ATTACKER
										players[opInd].board[opponentPos].defense = 0;
										players[opInd].board.erase(players[opInd].board.begin() + opponentPos);
									}
									if (players[i].board[attackerPos].defense <= 0) {
										players[i].board.erase(players[i].board.begin() + attackerPos);
									}
									else if (players[opInd].board[opponentPos].lethal && attackerShielded == false) { // CHECKING FOR LETHAL DEFENDER
										players[i].board[attackerPos].defense = 0;
										players[attackerPos].board.erase(players[attackerPos].board.begin() + attackerPos);
									}
									cout << action << ";";
								}
							}
						}else if(IDOfOpponent == -1 && attackerPos >= 0){ // CREATURE ON OPPONENT ATTACK
							//CHECKING FOR GUARD CREATURE
							bool guardCreature = false;
							for (int j = 0; j < players[opInd].board.size(); j++) {
								if (players[opInd].board[j].guard) {
									guardCreature = true;
								}
							}
							if (guardCreature == false) {
								if (players[i].board[attackerPos].canAttack) {
									players[i].board[attackerPos].canAttack = false;
									// APPLYING ATTACK TO OPPONENT
									players[opInd].health -= players[i].board[attackerPos].attack;
								}
							}
						}

					}else if (type == "USE") {
						int IDOfItem = stoi(actionParts[1]);
						int IDOfTarget = stoi(actionParts[2]);
						int posOfItem = -1;
						for (int k = 0; k < players[i].hand.size() && posOfItem == -1; k++) {
							if (players[i].hand[k].instanceId == IDOfItem) {
								posOfItem = k;
							}
						}
						if (posOfItem >= 0) { //ITEM EXISTS
							if (IDOfTarget >= 1) {// ITEM ON CREATURE
								int indOfPlayer = -1;
								int posOfTarget = -1;
								for (int k = 0; k < 2; k++) {
									for (int l = 0; l < players[k].board.size() && indOfPlayer == -1; l++) {
										if (players[k].hand[l].instanceId == IDOfTarget) {
											indOfPlayer = k;
											posOfTarget = l;
										}
									}
								}
								if (indOfPlayer >= 0 && players[i].mana >= players[i].hand[posOfItem].cost) {
									Card theItem = players[i].hand[posOfItem];
									players[i].mana -= players[i].hand[posOfItem].cost;
									players[indOfPlayer].board[posOfTarget].itemsOn.push_back(players[i].hand[posOfItem]);
									players[i].hand.erase(players[i].hand.begin() + posOfItem);
									// PUTTING EFFECTS OF ITEM ON
									players[indOfPlayer].board[posOfTarget].attack += theItem.attack;
									players[indOfPlayer].board[posOfTarget].attack += theItem.defense;
									players[i].health += theItem.myhealthChange;
									players[opInd].health += theItem.opponentHealthChange;
									players[i].nextCardDraw += theItem.cardDraw;
									// PUT ABILITIES ON CARD
									if (theItem.breakthrough) {
										players[indOfPlayer].board[posOfTarget].breakthrough = true;
										// not sure if this will refresh attack abiliy or not
									}
									if (theItem.charge) {
										players[indOfPlayer].board[posOfTarget].charge = true;
									}
									if (theItem.drain) {
										players[indOfPlayer].board[posOfTarget].drain = true;
									}
									if (theItem.guard) {
										players[indOfPlayer].board[posOfTarget].guard = true;
									}
									if (theItem.lethal) {
										players[indOfPlayer].board[posOfTarget].lethal = true;
									}
									if (theItem.ward && players[indOfPlayer].board[posOfTarget].ward == false) {
										players[indOfPlayer].board[posOfTarget].ward = true;
										players[indOfPlayer].board[posOfItem].shield = true;
									}
								}
							}
							else if (IDOfTarget == -1) { // ITEM ON OPPONENT
								if (players[i].mana >= players[i].hand[posOfItem].cost) {
									Card theItem = players[i].hand[posOfItem];
									players[i].hand.erase(players[i].hand.begin() + posOfItem);
									players[i].mana -= theItem.cost;
									players[i].health += theItem.myhealthChange;
									players[opInd].health += theItem.opponentHealthChange;
									players[i].nextCardDraw += theItem.cardDraw;
								}
							}
						}
					}else if (type == "PASS") {

					}
				}
				cout << endl;
			}
		}
		// RUNE STUFF
		for (int i = 0; i < 2; i++) {
			players[i].checkRunes();
		}
	}
	void turnUp() {
		turn++;
	}
	bool isOver() {
		return players[0].health <= 0 || players[1].health <= 0;
	}
	int getWinner() {
		if (players[0].health > 0) {
			return 0;
		}else if (players[1].health > 0) {
			return 1;
		}
		return -1;
	}
};
int main() {
	bool showGame = true;
	srand(time(NULL));
	cards->loadFromFile("C:/Users/WillN/Documents/Visual Studio 2017/LoCM/resources/cards.png");
	backs->loadFromFile("C:/Users/WillN/Documents/Visual Studio 2017/LoCM/resources/background.jpg");

	// something like
	CreateProcess()

	Game myGame = Game();
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Legends of Code & Simus");
	window.setFramerateLimit(60);
	window.setSize(sf::Vector2u(800, 450));
	while (window.isOpen()) {
		for (int i = 0; i < 200 && myGame.isOver() == false; i++) {
			// TICK
			myGame.play();
			// RENDER
			if (showGame) {
				sf::Event event;
				while (window.pollEvent(event)) {
					if (event.type == sf::Event::Closed) {
						window.close();
					}
				}
				myGame.render(window); // i don't think I set up the tick/render up prefrectly since you can't set up the window but it works lol
				sf::Clock clock;
				float timeToWait = i < 29 ? 1 : 1;
				while (clock.getElapsedTime().asSeconds() < timeToWait) {
				}
			}
			myGame.turnUp();
		}
		cout << "Winner: " << myGame.getWinner() + 1 << " Turns: " << myGame.turn << endl;
	}
	return 0;
}