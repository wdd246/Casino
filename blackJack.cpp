#include "functions.cpp"
#include "blackJack.h"
#include <ctime>
#include <iostream>
#include <cstdlib>

using namespace std;

		int sumPlayer=0;
		int sumCpu=0;
		int * player = new int[21];
		int * cpu = new int[21];
		int count=0;
		int bet;
		int next;
		
		
		blackJack::blackJack(){
			blackStart();
		}
		
		void blackJack::setBet(){
			srand(time(NULL));
			cout<<"Stan konta, wynosi "<<salary<<"$\n";
			cout<<"Wprowadz stawke\n";
			cin.ignore();
			cin.clear();
			cin>>bet;
			while(!cin.good() || bet>salary || bet<=0){
				system("cls");
				cout<<"Wprowadz stawke, stawka nie moze byc wieksza od stanu konta, ktory wynosi "<<salary<<"$\n";
				cin.clear();
				cin.ignore();
				cin>>bet;
			}
		}
		
		void blackJack::stay(){
			cout<<"Wartosc gracza: "<<sumPlayer<<"\n";
			cout<<"Wartosc cpu: "<<sumCpu<<"\n";
			if((sumPlayer>sumCpu && sumPlayer<=21) || sumCpu>21){
				Game::win();
			}
			if((sumPlayer<sumCpu && sumCpu<=21) || sumPlayer>21){
				Game::lose();
			}
			if(sumPlayer==21 && sumCpu>21){
				Game::draw();
			}
		}
		
		void blackJack::hit(){
			cpu[count+1] = (rand()%13 )+2;
			player[count+1] = (rand()%13 )+2;
			if(player[count+1]==11){
				player[count+1]=2;
			}
			if(player[count+1]==12){
				player[count+1]=3;
			}
			if(player[count+1]==13){
				player[count+1]=4;
			}
			if(player[count+1]==14){
				player[count+1]=11;
			}
			if(cpu[count+1]==11){
				cpu[count+1]=2;
			}
			if(cpu[count+1]==12){
				cpu[count+1]=3;
			}
			if(cpu[count+1]==13){
				cpu[count+1]=4;
			}
			if(cpu[count+1]==14){
				cpu[count+1]=11;
			}
			cout<<"Karta "<<count+1<<": "<<player[count+1]<<"\n";
					
			sumPlayer+=player[count+1];
			sumCpu+=cpu[count+1];
					
			cout<<"Wartosc: "<<sumPlayer<<"\n";
			count++;
		}
		
		void blackJack::firstRand(){
			srand(time(NULL));
			for(int i=1;i<3;i++){
				player[i] = (rand()%13 )+2;
				cpu[i] = (rand()%13 )+2;

				if(player[i]==11){
					player[i]=2;
				}
				if(player[i]==12){
					player[i]=3;
				}
				if(player[i]==13){
					player[i]=4;
				}
				if(player[i]==14){
					player[i]=11;
				}
				if(cpu[i]==11){
					cpu[i]=2;
				}
				if(cpu[i]==12){
					cpu[i]=3;
				}
				if(cpu[i]==13){
					cpu[i]=4;
				}
				if(cpu[i]==14){
					cpu[i]=11;
				}
				sumPlayer+=player[i];
				sumCpu+=cpu[i];
				cout<<"Karta "<<i<<": "<<player[i]<<"\n";
				count++;
			}
			cout<<"Wartosc: "<<sumPlayer<<"\n";
		}
		
		void blackJack::blackStart(){
			system("cls");
			setBet();
			system("cls");
			firstRand();
			
			while(true){			
				cout<<"1. Dobierz\n2. Czekaj/Sprawdz\n";
				cin.ignore();
				cin.clear();
				cin>>next;
				while(!cin.good()){
					cin.ignore();
					cin.clear();
					cout<<"1. Dobierz\n2. Czekaj/Sprawdz\n";
					cin>>next;
				}
				if(next==1){
					hit();
				}
				if(next==2){
					stay();
					break;
				}
				if(sumCpu==21 || sumPlayer>21){
					cout<<"Wartosc gracza: "<<sumPlayer<<"\n";
					cout<<"Wartosc cpu: "<<sumCpu<<"\n";
					Game::lose();
					break;
				}
				if(sumPlayer==21 || sumCpu>21){
					cout<<"Wartosc gracza: "<<sumPlayer<<"\n";
					cout<<"Wartosc cpu: "<<sumCpu<<"\n";
					Game::win();
					break;
				}
				if(sumPlayer==21 && sumCpu==21){
					cout<<"Wartosc gracza: "<<sumPlayer<<"\n";
					cout<<"Wartosc cpu: "<<sumCpu<<"\n";
					Game::draw();
					break;
				}
			}
		}
		

		
		void blackJack::instrukcja(){
			cout<<bet;
		}
