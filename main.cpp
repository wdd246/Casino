#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

void logOut();
string intToStr(int n);
int strToInt(string s);
void sortRank();
void update(int bet);
void gameMenu();
bool exist(string name);
void logIn();
void deleteSpaces();
void signIn();
void ranking();
void mainMenu();

int main() {
	mainMenu();
}

/* Player structure 

string name -your name -> signIn()
int salary -random salary -> signIn()

*/
struct Player 
{
	string name;
	int salary;	
};

/*  initialization Player*/
Player player;

/* Game class
	bet - your bet
	win()
	lose()
	draw()
	setBet() -> insert your bet to each round in game
	getBet() - getter
 */
class Game{
	private:
		int bet;
	public:
		void win(int x);
		void lose(int x);
		void draw();
        void setBet();
        int getBet();
};

int Game::getBet(){
	return bet;
}

void Game::win(int x){
	cout<<"Wygrales\n\n";
	update(bet*x); //update salary by bet * multiplier
	cout<<"Zagraj jeszcze raz!\n\n";
	system("pause");
}

void Game::lose(int x){
	cout<<"Przegrales\n\n";
	update(-bet*x); //update salary by -bet * multiplier
	cout<<"Zagraj jeszcze raz!\n\n";
	system("pause");
}

void Game::draw(){
	cout<<"Remis\n\n";
	cout<<"Zagraj jeszcze raz!\n\n";
	system("pause");
}

void Game::setBet(){
	cout<<"Stan twojego konta wynosi "<<player.salary<<"$\n\n";
	cout<<"Wprowadz stawke\n>>";
	cin.ignore();
	cin.clear();
	cin>>bet;
	while(!cin.good() || bet>player.salary || bet<=0){
        system("cls");
		cout<<"Wprowadz stawke\nStawka musi byæ wiêksza od 0 oraz nie moze byc wieksza od stanu konta, ktory wynosi "<<player.salary<<"$\n>>";
		cin.clear();
		cin.ignore();
		cin>>bet;
	}
}
/* -- end Game class -- */

/* blackJack class

	inheritance by Game class

	sumPlayer - sum of player cards value
	sumCpu - sum of cpu cards value
	int * player - array of player cards
	int * cpu - array of cpu cards
	int count - number of cards you have
	int next - your next desision hit/stay/quit
	
	void stay() - check cards both of players
	void hit() - get next card
	void firstRand() - get first 2 cards
	void hitOrStay() - hit() or stay()
	blackJack() - constructor
	void instruction() - instruction
*/
class blackJack : Game{
	public:
		int sumPlayer=0;
		int sumCpu=0;
		int * player = new int[21];
		int * cpu = new int[21];
		int count=0;
		int next;
		void stay();
		void hit();
		void firstRand();
		void hitOrStay();
		blackJack();
		void instruction();
};

void blackJack::stay(){
	cout<<"\nWartosc gracza: "<<sumPlayer<<"\n";
	cout<<"Wartosc cpu: "<<sumCpu<<"\n\n";
	if((sumPlayer>sumCpu && sumPlayer<=21) || sumCpu>21){
		Game::win(1);
	}
	if((sumPlayer<sumCpu && sumCpu<=21) || sumPlayer>21){
		Game::lose(1);
	}
	if(sumPlayer==21 && sumCpu==21){
		Game::draw();
	}
}

void blackJack::hit(){
	cout<<"Black Jack\n__________\n\n";
    if(sumCpu<15){
        cpu[count+1] = (rand()%13 )+2; //if cpu cards <15, hit by cpu
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
        sumCpu+=cpu[count+1];
    }
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
	cout<<"Karta "<<count+1<<": "<<player[count+1]<<"\n";
	sumPlayer+=player[count+1];
	cout<<"Wartosc: "<<sumPlayer<<"\n\n";
	count++;
}

void blackJack::firstRand(){
	cout<<"Black Jack\n__________\n\n";
	srand(time(NULL));
	for(int i=1;i<3;i++){
		player[i] = (rand()%13 )+2; // give 2 cards to player
		cpu[i] = (rand()%13 )+2; // give 2 cards to cpu
	
		if(player[i]==11){ //jack = 2
			player[i]=2;
		}
		if(player[i]==12){ //lady = 3
			player[i]=3;
		}
		if(player[i]==13){ //king = 4 
			player[i]=4;
		}
		if(player[i]==14){ //as = 11
			player[i]=11;
		}
		if(cpu[i]==11){ //jack = 2
			cpu[i]=2;
		}
		if(cpu[i]==12){ //lady = 3
			cpu[i]=3;
		}
		if(cpu[i]==13){ //king = 4 
			cpu[i]=4;
		}
		if(cpu[i]==14){ //as = 11
			cpu[i]=11;
		}
		sumPlayer+=player[i];
		sumCpu+=cpu[i];
		cout<<"Karta "<<i<<": "<<player[i]<<"\n";
		count++;
	}
	cout<<"Wartosc: "<<sumPlayer<<"\n\n";
}

void blackJack::hitOrStay(){
	while(true){
		cout<<"1. Dobierz\n2. Czekaj/Sprawdz\n>>";
		cin.ignore();
		cin.clear();
		cin>>next;
		if(next==1){
			system("cls");
			hit();
		}
		if(next==2){
			stay();
			break;
		}
		if(!cin.good()){
			cin.ignore();
			cin.clear();
			system("cls");
		}
		if(sumCpu==21 || sumPlayer>21){
			cout<<"Wartosc gracza: "<<sumPlayer<<"\n";
			cout<<"Wartosc cpu: "<<sumCpu<<"\n\n";
			Game::lose(1);
			break;
		}
		if(sumPlayer==21 || sumCpu>21){
			cout<<"Wartosc gracza: "<<sumPlayer<<"\n";
			cout<<"Wartosc cpu: "<<sumCpu<<"\n\n";
			Game::win(1);
			break;
		}
		if(sumPlayer==21 && sumCpu==21){
			cout<<"Wartosc gracza: "<<sumPlayer<<"\n";
			cout<<"Wartosc cpu: "<<sumCpu<<"\n\n";
			Game::draw();
			break;
		}
	}
}
		
blackJack::blackJack(){
	system("cls");
	instruction();
	system("cls");
	Game::setBet();
	system("cls");
	firstRand();
	hitOrStay();
}

void blackJack::instruction(){
	cout<<"Instrukcja\n__________\n\n";
	cout<<"1. Wprowadz stawke\n2. Na poczatku dostajesz 2 karty o wartosci 2-11 \n3. Mozesz dobrac karty lub zatrzymac to co masz\n4. Jezeli przekroczysz sume kart 21 - przegrywasz.\n   Jezeli przeciwnik przekroczy sume kart 21 wygrywasz.\n   Wygrywa ten ktorego suma kart jest blizsza 21\n\n";
	system("pause");
}
/* -- end blackJack class -- */

/* fruitMachine class

	inheritance by Game class

	int next - next step: once more or qiut
    void fruitGo() - random 3 variables and check it
	void fruitGame() - menu start/quit
	fruitMachine() - constructor
	void instruction() - instruction
*/
class fruitMachine : Game{
	public:
		int next;
        void fruitGo();
		void fruitGame();
		fruitMachine();
		void instruction();
};

void fruitMachine::fruitGo(){
	int first=(rand()%10 )+1;
	int secound=(rand()%10 )+1;
	int third=(rand()%10 )+1;
	int count =0;
	bool fs=false; //first and secound the same
	bool st=false; //secound and third the same
	bool ft=false; //first and third the same
	float tab[9][3]={{1,1.3,1.5},{2,1.6,1.9},{3, 2.1,2.2},{4,2.5,2.8},{5,3,3.25},{6,3.5,4},{7,5,6},{8,10,15},{9,20,30}}; //multiplies on each number
	
	cout<<"Jednoreki bandyta\n_________________\n\n";
	cout<<"Losowanie\n\n| "<<first<<" | "<<secound<<" | "<<third<<" |\n";

	if(first == secound){
	    fs=true;
	}
	if(secound == third){
	    st=true;
	}
	if(first == third){
	    ft=true;
	}
	if(fs==false && st==false  && ft==false){ //if nothing the same
		cout<<"\n-"<<Game::getBet()<<"$\n";
	    Game::lose(1);
	}
	if((first==10 && secound==10)||(secound==10 && third==10)||(first==10 && third==10)){ // if 2x10
		cout<<"\n+"<<5*Game::getBet()<<"$\n";
	    Game::win(5);
	}
	if(first==10 && secound ==10 && third ==10){ // if 3x10
		cout<<"\n+"<<40*Game::getBet()<<"$\n";
	    Game::win(40);
	}
	if(fs==true && st==false && ft==false && third==10 && first!=10){ //if 1x10 and 2xY -> make 3xY
	    for(int i=0;i<=8;i++){
	        for(int j=0;j<=2;j++){
	            if(first==tab[i][0]){
	            	cout<<"\n+"<<tab[i][2]*Game::getBet()<<"$\n";
	                Game::win(tab[i][2]);
	                break;
	            }
	        }
	    }
	
	}
	if(st==true  && fs==false && ft==false && first==10 && third!=10){ //if 1x10 and 2xY -> make 3xY
	    for(int i=0;i<=8;i++){
	        for(int j=0;j<=2;j++){
	            if(secound==tab[i][0]){
	            	cout<<"\n+"<<tab[i][2]*Game::getBet()<<"$\n";
	                Game::win(tab[i][2]);
	                break;
	            }
	        }
	    }
	}
	if(ft==true  && fs==false && st==false && secound==10 && first!=10){ //if 1x10 and 2xY -> make 3xY
	    for(int i=0;i<=8;i++){
	        for(int j=0;j<=2;j++){
	            if(first==tab[i][0]){
	            	cout<<"\n+"<<tab[i][2]*Game::getBet()<<"$\n";
	                Game::win(tab[i][2]);
	                break;
	            }
	        }
	    }
	}
	if(fs==true && st==true && ft==true && first!=10){ //if 3xY
	    for(int i=0;i<=8;i++){
	        for(int j=0;j<=2;j++){
	            if(first==tab[i][0]){
	            	cout<<"\n+"<<tab[i][2]*Game::getBet()<<"$\n";
	                Game::win(tab[i][2]);
	                break;
	            }
	        }
	    }
	}
	if(fs==true && st==false && ft==false ){ //if 2xY
	    for(int i=0;i<=8;i++){
	        for(int j=0;j<=2;j++){
	            if(first==tab[i][0]){
	            	cout<<"\n+"<<tab[i][1]*Game::getBet()<<"$\n";
	                Game::win(tab[i][1]);
	                break;
	            }
	        }
	    }
	}
	if(st==true  && fs==false && ft==false){ //if 2xY
	    for(int i=0;i<=8;i++){
	        for(int j=0;j<=2;j++){
	            if(secound==tab[i][0]){
	            	cout<<"\n+"<<tab[i][1]*Game::getBet()<<"$\n";
	                Game::win(tab[i][1]);
	                break;
	            }
	        }
	    }
	}
	if(ft==true  && fs==false && st==false){ //if 2xY
	    for(int i=0;i<=8;i++){
	        for(int j=0;j<=2;j++){
	            if(first==tab[i][0]){
	            	cout<<"\n+"<<tab[i][1]*Game::getBet()<<"$\n";
	                Game::win(tab[i][1]);
	                break;
	            }
	        }
	    }
	}
	system("cls");
	cout<<"\nStan twojego konta "<<player.salary<<"$\n\n";
}

void fruitMachine::fruitGame(){
	system("cls");
	while(true){
	    system("cls");
	    cout<<"Jednoreki bandyta\n_________________\n\n";
	    cout<<"Twoj bet "<<Game::getBet()<<"$\n\n";
	    cout<<"Stan twojego konta wynosi "<<player.salary<<"$\n\n";
		cout<<"1. Start\n2. Wstecz\n>>";
		cin.ignore();
		cin.clear();
		cin>>next;
		if(next==1){
	        system("cls");
	        cout<<"Stan twojego konta wynosi"<<player.salary<<"$\n\n";
	        if(player.salary<Game::getBet()){
	            cout<<"Niemasz wystarczajacej ilosci pieniedzy\n";
	            system("pause");
	            break;
	        }
	        if(player.salary>=Game::getBet()){
	            system("cls");
	            fruitGo();
	        }
		}
		if(next==2){
		    system("cls");
			break;
		}
		if(!cin.good()){
			cin.ignore();
			cin.clear();
		}
	}
}

fruitMachine::fruitMachine(){
	system("cls");
	instruction();
	system("cls");
	Game::setBet();
	system("cls");
	fruitGame();
}

void fruitMachine::instruction(){
	cout<<"Instrukcja\n__________\n\n";
	cout<<"1. Wprowadz stawke\n2. Nastepuje losowanie 3 liczb \n3. Wygrywaja 3 lub 2 te same liczby\n";
	cout<<"4. Mnoznik\nJaka liczba | Mnoznik za dwie | Mnoznik za trzy\n";
	cout<<"1 | 1.3 | 1.5\n2 | 1.6 | 1.9\n3 | 2.1 | 2.2\n4 | 2.5 | 2.8\n5 | 3   | 3.25\n6 | 3.5 | 4\n7 | 5   | 6\n8 | 10  | 15\n9 | 20  | 30 \n";
	cout<<"5. Jezeli wypadnie 10 zastepuje dolwolna liczbe o ile pozostale dwie sa identyczne\n   Jezeli wypadnie 2 razy 10 oraz jakis znak, mnoznik wynosi 5\n   Jezeli wypadnie 3 razy 10 mnoznik wynosi 40\n\n";
	system("pause");
}
/* -- end fruitMachine class -- */

/* roulette class

	inheritance by Game class

	int next - check bet : color, number etc.
    void rouletteArr(int select) - random number and check if you win ( color, %2, 1:12 ... etc )
	void rouletteNum(int number) - random number and check if you win ( number )
	void rouletteStart() - menu
	roulette() - constructor 
	void instruction() - instruction
*/
class roulette : Game{
	public:
		int next; 
		void rouletteArr(int select);
		void rouletteNum(int number);
		void rouletteStart();
		roulette();
		void instruction();
};

void roulette::rouletteArr(int select){	
	system("cls");
	int num=(rand()%37); //random number
	int black[18]={2,4,6,8,10,11,13,15,17,20,22,24,26,28,29,31,33,35}; //black array
	int red[18]={1,3,5,7,9,12,14,16,18,19,21,23,25,27,30,32,34,36}; //red array
	cout<<"Wylosowana liczba: "<<num<<"\n";
	/* check red, bet x2 */
	if(select==1){ 
		bool redExist=false;
		for(int i=0;i<=17;i++){
			if(num==red[i]){
				redExist=true;
			}
		}
		if(redExist==true){
			cout<<"\n+"<<Game::getBet()<<"$\n";
			Game::win(1);
		}
		if(redExist==false){
			cout<<"\n-"<<Game::getBet()<<"$\n";
			Game::lose(1);
		}
	}
	/* check black, bet x2 */
	if(select==2){
		bool blackExist=false;
		for(int i=0;i<=17;i++){
			if(num==black[i]){
				blackExist=true;
			}
		}
		if(blackExist==true){
			cout<<"\n+"<<Game::getBet()<<"$\n";
			Game::win(1);
		}
		if(blackExist==false){
			cout<<"\n-"<<Game::getBet()<<"$\n";
			Game::lose(1);
		}
	}
	/* check %2==0, bet x2 */
	if(select==3){
		if(num%2==0){
			cout<<"\n+"<<Game::getBet()<<"$\n";
			Game::win(1);
		}
		if(num%2==1){
			cout<<"\n-"<<Game::getBet()<<"$\n";
			Game::lose(1);
		}
	}
	/* check %2==1, bet x2 */
	if(select==4){
		if(num%2==1){
			cout<<"\n+"<<Game::getBet()<<"$\n";
			Game::win(1);
		}
		if(num%2==0){
			cout<<"\n-"<<Game::getBet()<<"$\n";
			Game::lose(1);
		}
	}
	/* check 1:18*/
	if(select==5){
		if(num>=1 && num<=18){
			cout<<"\n+"<<Game::getBet()<<"$\n";
			Game::win(1);
		}
		if(num<1 || num>18){
			cout<<"\n-"<<Game::getBet()<<"$\n";
			Game::lose(1);
		}
	}
	/* check 19:36, bet x2 */
	if(select==6){
		if(num>=19 && num<=36){
			cout<<"\n+"<<Game::getBet()<<"$\n";
			Game::win(1);
		}
		if(num<19 || num>36){
			cout<<"\n-"<<Game::getBet()<<"$\n";
			Game::lose(1);
		}
	}
	/* check 1:12, bet x4 */
	if(select==7){
		if(num>=1 && num<=12){
			cout<<"\n+"<<2*Game::getBet()<<"$\n";
			Game::win(2);
		}
		if(num<1 || num>12){
			cout<<"\n-"<<Game::getBet()<<"$\n";
			Game::lose(1);
		}
	}
	/* check 13:24, bet x4 */
	if(select==8){
		if(num>=13 && num<=24){
			cout<<"\n+"<<2*Game::getBet()<<"$\n";
			Game::win(2);
		}
		if(num<13 || num>24){
			cout<<"\n-"<<Game::getBet()<<"$\n";
			Game::lose(1);
		}
	}
	/* check 25:36, bet x4 */
	if(select==9){
		if(num>=25 && num<=36){
			cout<<"\n+"<<2*Game::getBet()<<"$\n";
			Game::win(2);
		}
		if(num<25 || num>36){
			cout<<"\n-"<<Game::getBet()<<"$\n";
			Game::lose(1);
		}
	}
return;
}
		
void roulette::rouletteNum(int number){
	int num=(rand()%37); //random number
	cout<<"Wylosowana liczba: "<<num<<"\n";
	/* if bet == random number, bet x16 */
	if(number==num){
		cout<<"\n+"<<16*Game::getBet()<<"$\n";
		Game::win(16);
	}
	if(number!=num){
		cout<<"\n-"<<Game::getBet()<<"$\n";
		Game::lose(1);
	}
	return;
}
		
void roulette::rouletteStart(){
	while(true){
        system("cls");
        cout<<"Ruletka\n_______\n\n";
        cout<<"Twoj bet "<<Game::getBet()<<"$\n\n";
        cout<<"Stan twojego konta "<<player.salary<<"$\n\n";
        cout<<"Postaw na: \n";
		cout<<"1. Czerwony\n2. Czarny\n3. Parzyste\n4. Nieparzyste\n5. 1:18\n6. 19:36\n7. 1:12\n8. 13:24\n9. 25:36\n10. Liczba\n---------\n11. Wstecz\n\n>>";
		cin.ignore();
		cin.clear();
		cin>>next;
		if(next==1 || next==2 || next==3 || next==4 || next==5 || next==6 || next==7 || next==8 || next==9){
			rouletteArr(next);
			return;
		}
		if(next==10){
			while(true){
				system("cls");
				cout<<"Wpisz liczbe jaka wybierasz 0-36\n>>";
				int number;
				cin.ignore();
				cin.clear();
				cin>>number;
				if(cin.good() && number<=36 && number>=0){
					rouletteNum(number);	
					return;
				}
				if(!cin.good()){
					cin.ignore();
					cin.clear();
				}	
			}
		}
		if(next==11){
			return; //quit
		}
		if(!cin.good()){
			cin.ignore();
			cin.clear();
		}
	}		
}
		
roulette::roulette(){
	system("cls");
	instruction();
	system("cls");
	Game::setBet();
	system("cls");
	rouletteStart();
}
		
void roulette::instruction(){
	cout<<"Instrukcja\n__________\n\n";
	cout<<"1. Wprowadz stawke\n2. Wybierasz na co chcesz postawic \n3. Nastepuje losowanie liczby\n";
	cout<<"4. Wyplaty\n";
	cout<<"   Kolor x2\n   Numer x35\n   Parzystosc x2\n   1:18 / 19:36 x2\n   1:12 / 13:24 / 25:36 x4\n\n";
	system("pause");
}
/* -- end roulette class -- */

void logOut(){
	cout<<"\nDziekujemy za wizyte\n\n";
	system("pause");
	exit(0);
}

/* convert int to string not using C++11 */
string intToStr(int n){ 
     string tmp, ret;
     if(n < 0){
      	ret = "-";
      	n = -n;
     }
     do{
      	tmp += n % 10 + 48;
      	n -= n % 10;
     }
     while(n /= 10);
     for(int i = tmp.size()-1; i >= 0; i--)
      	ret += tmp[i];
     return ret;
}

/* convert string to int not using C++11 */
int strToInt(string s){
    bool m=false;
    int tmp=0;
    int i=0;
    if(s[0]=='-'){
		i++;
    	m = true;
    }
    while(i<s.size()){
      	tmp = 10*tmp+s[i]-48;
      	i++;
    }
    return m ? -tmp : tmp;
}

/* sorting array by salary */
void sortRank(){
	int count=0; //number of users
	string * uname=new string[1000];
	string * usalary=new string[1000];
	fstream usersRead;
	usersRead.open("users.txt", ios::in);
	fstream usersWrite;
	usersWrite.open("users.txt", ios::out | ios::app);

	while(!usersRead.eof()){
        usersRead>>uname[count]; //get name
        usersRead>>usalary[count]; //get salary
        count++;
    }

	for(int i=0;i<count-1;i++) {
		for(int j=i+1;j<count;j++) {
			if(strToInt(usalary[j])>strToInt(usalary[i])) { // sorting in array
				string tempName = uname[i];
				string tempSalary = usalary[i];
				uname[i] = uname[j];
				usalary[i] = usalary[j];
				uname[j] = tempName;
				usalary[j] = tempSalary;
			}
		}
	}

    fopen("users.txt","w"); //clear file

    for(int j=0; j<=count; j++){
	    usersWrite<<uname[j]<<" "<<usalary[j]<<"\n"; //rewrite sorted file
	}
	
	usersRead.close();
	usersWrite.close();
	delete [] uname;
	delete [] usalary;
}

/* updating salary in file by bet 
	if salary < 0 , get 10$
*/
void update(int bet){
	fstream usersRead;
	usersRead.open("users.txt", ios::in);
	fstream usersWrite;
	usersWrite.open("users.txt", ios::out | ios::app);
	int count=0; //number of users
	string * uname=new string[1000];
	string * usalary=new string[1000];

	while(!usersRead.eof()){
        usersRead>>uname[count];
        usersRead>>usalary[count];
        if(uname[count]==player.name){
        	player.salary+=bet;
			if(player.salary<=0){ //if salary <0 get 10$
				player.salary=10;
			}
        	usalary[count]=intToStr(player.salary);
		}
        count++;
    }
	sortRank(); //sort ranking

    fopen("users.txt","w"); //clear file

    for(int j=0; j<=count; j++){
	    usersWrite<<uname[j]<<" "<<usalary[j]<<"\n"; //rewrite file
	}
	usersRead.close();
	usersWrite.close();
	delete [] uname;
	delete [] usalary;
}

/* menu with games */
void gameMenu(){
	system("cls");
	cout<<"******************\n*                *\n*   ADAM VEGAS   *\n*                *\n******************\n\n";
	cout<<"Witamy "<<player.name<<" w Adam Vegas.\nTwoje saldo to "<<player.salary<<"$\n\n";
	cout<<"1. Jednoreki bandyta\n2. Ruletka\n3. Black Jack\n-------------\n4. Wstecz\n5. Wyjdz\n>>";
	int j;
	cin>>j;
	if(j==1){
		system("cls");
        fruitMachine Fruit; //fruit machine
	}
	if(j==2){
	    system("cls");
	    roulette Roul; //roulette
	}
	if(j==3){
		system("cls");
	   	blackJack Jack; //blackJack
	}
	if(j==4){
		return; //back
	}
	if(j==5){
		logOut(); //quit
	}
	else{
		cin.clear();
		cin.ignore();
		system("cls");
		gameMenu();
	}
}

/* check if name in signIn() exist */
bool exist(string name){
	fstream users;
	users.open("users.txt", ios::in);
	string line;
	while(!users.eof()){
        users>>line;
        users>>player.salary;
        if(line==name){
        	return true;
		}
    }
    return false;
    users.close();
}

/* logIn() */
void logIn(){
	fstream users;
	users.open("users.txt", ios::in);
	system("cls");
	cout<<"LOGOWANIE\n_________\n\n";
	cout<<"Podaj nazwe\n--Aby wyjsc wpisz exit\n>>";
	cin>>player.name;
	if(player.name=="exit"){ //if name == exit -> quit
		return;
	}
	while(!cin.good() || !exist(player.name)){
		cin.clear();
		cin.ignore();
		system("cls");
		cout<<"Podana nazwa nie istnieje lub jest nieprawidlowa\n\nProsze podac inna\n";
		cout<<"--Aby wyjsc wpisz exit\n>>";
		cin>>player.name;
		if(player.name=="exit"){ //if name == exit -> quit
			return;
		}
	}
	cout<<"\nZalogowales sie pomyslnie\nTwoje saldo to: "<<player.salary<<"$\n\n";
	users.close();
	system("pause");
	gameMenu();
}

/* if in signIn() in the name are spaces -> change it to '_'*/
void deleteSpaces(){
	int k=0;

	while (player.name[k] != '\0'){
        if (isspace(player.name[k])){
        	player.name[k]='_';
		}
        k++;
	}
}

/* signIn() */
void signIn(){
	srand(time(NULL));
	fstream users;
	users.open("users.txt", ios::out | ios::app );
	system("cls");
	cout<<"REJESTRACJA\n___________\n\n";
	cout<<"Podaj nazwe\n--Aby wyjsc wpisz exit\n>>";
	cin.clear();
	cin.ignore();
	getline(cin, player.name); //get name
	if(player.name=="exit"){
		return;
	}
	deleteSpaces();
    cout<<"\nNazwa zostala zmieniona na "<<player.name<<"\n";

	while(exist(player.name)){ // if name exist
		cin.clear();
		cin.ignore();
		system("cls");
		cout<<"Podana nazwa juz istnieje lub jest nieprawidlowa\n\nProsze podac inna nazwe\n";
		cout<<"---Aby wyjsc wpisz exit\n>>";
		getline(cin,player.name);
		if(player.name=="exit"){
			return;	
		}
		deleteSpaces(); // change spaces into '_'
		cout<<"\nNazwa zostala zmieniona na "<<player.name<<"\n";
	}
	player.salary = (rand()%1000 );
	cout<<endl;
	cout<<"Stan konta: "<<player.salary<<"$\n";
	cout<<"\nZarejestrowales sie pomyslnie\n\n";
	users<<player.name<<" "<<intToStr(player.salary)<<"\n";
	update(0);
	users.close();
	system("pause");
	gameMenu();
}

/* ranking */
void ranking(){
	system("cls");
	cout<<"RANKING TOP 100\n_______________\n\n";
	fstream users;
	users.open("users.txt", ios::in);
	string topName;
	int top=1; //counter
	sortRank();
	while(top>=100 || !users.eof()){ //show top100
		getline(users,topName);
		if(topName.empty()|| topName==" ")
			continue;
		cout<<top<<". "<<topName<<"$\n";
		top++;
	}
	cout<<endl;
	users.close();
	system("pause");
}

/* main menu */
void mainMenu(){
	int i;
	cout<<"******************\n*                *\n*   ADAM VEGAS   *\n*                *\n******************\n\n";
	cout<<"\nMENU\n____\n\n1. Zapisz sie\n2. Mam juz konto\n3. Ranking\n4. Wyjdz\n>>";
	cin>>i;
	if(i==1){
	   signIn();
	}
	if(i==2){
	    logIn();
	}
	if(i==3){
		ranking();
	}
	if(i==4){
		logOut();
	}
	else{
		cin.clear();
		cin.ignore();
		system("cls");
		mainMenu();
	}
}


