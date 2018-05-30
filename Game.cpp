#include "Game.h"
#include <iostream>
#include "functions.cpp"

using namespace std;

void Game::win(){
			cout<<"Wygrales\n";
			update(bet);
			cout<<"Zagraj jeszcze raz!\n";
			wait();
			//return;
		}
		
		void Game::lose(){
			cout<<"Przegrales\n";
			update(-bet);	
			cout<<"Zagraj jeszcze raz!\n";
			wait();
			//return;
		}
		
		void Game::draw(){
			cout<<"Remis\n";
			cout<<"Zagraj jeszcze raz!\n";
			wait();
			//return;
		}
