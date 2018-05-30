#ifndef BLACKJACK_H
#define BLACKJACK_H
#include "Game.h"


class blackJack : public Game{
	public:	
		void setBet();
		
		void stay();
		
		void hit();
		
		void firstRand();
		
		void blackStart();
		
		blackJack();
		
		void instrukcja();
};

#endif
