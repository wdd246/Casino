#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

int salary;
string name;


void logOut(){
	cout<<"\nDziekujemy za wizyte\n";
	system("pause");
	exit(0);
}

string intToStr(int n){
     string tmp, ret;
     if(n < 0) {
      	ret = "-";
      	n = -n;
     }
     do {
      	tmp += n % 10 + 48;
      	n -= n % 10;
     }
     while(n /= 10);
     for(int i = tmp.size()-1; i >= 0; i--)
      	ret += tmp[i];
     return ret;
}

int strToInt(string s){
    bool m=false;
    int tmp=0;
    int i=0;
    if(s[0]=='-')
    {
        i++;
    	m = true;
    }
    while(i<s.size())
    {
      	tmp = 10*tmp+s[i]-48;
      	i++;
    }
    return m ? -tmp : tmp;
}

void sortRank(){
	int count=0;
	string * uname=new string[100];
	string * usalary=new string[100];
	fstream usersRead;
	usersRead.open("users.txt", ios::in);
	fstream usersWrite;
	usersWrite.open("users.txt", ios::out | ios::app);

	while(!usersRead.eof()){
        usersRead>>uname[count];
        usersRead>>usalary[count];
        count++;
    }

	for(int i=0;i<count-1;i++) {
		for(int j=i+1;j<count;j++) {
			if(strToInt(usalary[j])>strToInt(usalary[i])) {
				string tempName = uname[i];
				string tempSalary = usalary[i];
				uname[i] = uname[j];
				usalary[i] = usalary[j];
				uname[j] = tempName;
				usalary[j] = tempSalary;
			}
		}
	}

    fopen("users.txt","w");

    for(int j=0; j<=count; j++){
	    usersWrite<<uname[j]<<" "<<usalary[j]<<"\n";
	}
	usersRead.close();
	usersWrite.close();
	delete [] uname;
	delete [] usalary;
}

void update(int bet){
	fstream usersRead;
	usersRead.open("users.txt", ios::in);
	fstream usersWrite;
	usersWrite.open("users.txt", ios::out | ios::app);
	int count=0;
	string * uname=new string[100];
	string * usalary=new string[100];

	while(!usersRead.eof()){
        usersRead>>uname[count];
        usersRead>>usalary[count];
        if(uname[count]==name){

        	salary+=bet;
			if(salary<=0){
				salary=10;
			}

        	usalary[count]=intToStr(salary);
		}
        count++;
    }

	for(int i=0;i<count-1;i++) {
		for(int j=i+1;j<count;j++) {
			if(strToInt(usalary[j])>strToInt(usalary[i])) {
				string tempName = uname[i];
				string tempSalary = usalary[i];
				uname[i] = uname[j];
				usalary[i] = usalary[j];
				uname[j] = tempName;
				usalary[j] = tempSalary;
			}
		}
	}

    fopen("users.txt","w");

    for(int j=0; j<=count; j++){
	    usersWrite<<uname[j]<<" "<<usalary[j]<<"\n";
	}
	usersRead.close();
	usersWrite.close();
	delete [] uname;
	delete [] usalary;
}
class Game{
	public:
		int bet;
		void win(int x){
			cout<<"Wygrales\n\n";
			update(bet*x);
			cout<<"Zagraj jeszcze raz!\n\n";
			system("pause");
			//return;
		}
		void lose(int x){
			cout<<"Przegrales\n\n";
			update(-bet*x);
			cout<<"Zagraj jeszcze raz!\n\n";
			system("pause");
			//return;
		}
		void draw(){
			cout<<"Remis\n\n";
			cout<<"Zagraj jeszcze raz!\n\n";
			system("pause");
			//return;
		}
        void setBet(){
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
};

class blackJack : Game{
	public:
		int sumPlayer=0;
		int sumCpu=0;
		string nazwa;
		int * player = new int[21];
		int * cpu = new int[21];
		int count=0;
		int next;

		void stay(){
			cout<<"Wartosc gracza: "<<sumPlayer<<"\n";
			cout<<"Wartosc cpu: "<<sumCpu<<"\n";
			if((sumPlayer>sumCpu && sumPlayer<=21) || sumCpu>21){
				Game::win(1);
			}
			if((sumPlayer<sumCpu && sumCpu<=21) || sumPlayer>21){
				Game::lose(1);
			}
			if(sumPlayer==21 && sumCpu>21){
				Game::draw();
			}
		}

		void hit(){
		    if(sumCpu<15){
                cpu[count+1] = (rand()%13 )+2;
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


			cout<<"Wartosc: "<<sumPlayer<<"\n";
			count++;
		}

		void firstRand(){
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

		blackJack(){
			system("cls");
			instruction();
			system("cls");
			Game::setBet();
			system("cls");
			firstRand();

			while(true){
				cout<<"1. Dobierz\n2. Czekaj/Sprawdz\n";
				cin.ignore();
				cin.clear();
				cin>>next;
				while(!cin.good()){
                    system("cls");
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
					Game::lose(1);
					break;
				}
				if(sumPlayer==21 || sumCpu>21){
					cout<<"Wartosc gracza: "<<sumPlayer<<"\n";
					cout<<"Wartosc cpu: "<<sumCpu<<"\n";
					Game::win(1);
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
		void instruction(){
			cout<<"Instrukcja\n";
			cout<<"1. Wprowadz stawke\n2. Na poczatku dostajesz 2 karty o wartosci 2-11 \n3. Mozesz dobrac karty lub zatrzymac to co masz\n4. Jezeli przekroczysz sume kart 21 - przegrywasz.\nJezeli przeciwnik przekroczy sume kart 21 wygrywasz.\nWygrywa ten ktorego suma kart jest blizsza 21\n\n";
			system("pause");
		}
};

class fruitMachine : Game{
	public:
		int sumPlayer=0;
		int next;

            void go(){

			    int first=(rand()%10 )+1;
			    int secound=(rand()%10 )+1;
			    int third=(rand()%10 )+1;
			    int count =0;
			    bool fs=false;
			    bool st=false;
			    bool ft=false;
			    float tab[9][3]={{1,1.3,1.5},{2,1.6,1.9},{3, 2.1,2.2},{4,2.5,2.8},{5,3,3.25},{6,3.5,4},{7,5,6},{8,10,15},{9,20,30}};

			    cout<<"Losowanie\n\n| "<<first<<" | "<<secound<<" | "<<third<<" |\n\n";

			    if(first == secound){
                    fs=true;
			    }
			    if(secound == third){
                    st=true;
			    }
			    if(first == third){
                    ft=true;
			    }
			    if(fs==false && st==false  && ft==false){
                    Game::lose(1);
			    }
			    if((first==10 && secound==10)||(secound==10 && third==10)||(first==10 && third==10)){
                    Game::win(5);
			    }
			    if(first==10 && secound ==10 && third ==10){
                    Game::win(40);
			    }
			    if(fs==true && st==false && ft==false && third==10 && first!=10){
                    for(int i=0;i<=8;i++){
                        for(int j=0;j<=2;j++){
                            if(first==tab[i][0]){
                                Game::win(tab[i][2]);
                                break;
                            }
                        }
                    }

			    }
			    if(st==true  && fs==false && ft==false && first==10 && third!=10){
                    for(int i=0;i<=8;i++){
                        for(int j=0;j<=2;j++){
                            if(secound==tab[i][0]){
                                Game::win(tab[i][2]);
                                break;
                            }
                        }
                    }
			    }
			    if(ft==true  && fs==false && st==false && secound==10 && first!=10){
                    for(int i=0;i<=8;i++){
                        for(int j=0;j<=2;j++){
                            if(first==tab[i][0]){
                                Game::win(tab[i][2]);
                                break;
                            }
                        }
                    }
			    }
			    if(fs==true && st==true && ft==true && first!=10){
                    for(int i=0;i<=8;i++){
                        for(int j=0;j<=2;j++){
                            if(first==tab[i][0]){
                                Game::win(tab[i][2]);
                                break;
                            }
                        }
                    }
			    }
			    if(fs==true && st==false && ft==false ){
                    for(int i=0;i<=8;i++){
                        for(int j=0;j<=2;j++){
                            if(first==tab[i][0]){
                                Game::win(tab[i][1]);
                                break;
                            }
                        }
                    }
			    }
                if(st==true  && fs==false && ft==false){
                    for(int i=0;i<=8;i++){
                        for(int j=0;j<=2;j++){
                            if(secound==tab[i][0]){
                                Game::win(tab[i][1]);
                                break;
                            }
                        }
                    }
			    }
			    if(ft==true  && fs==false && st==false){
                    for(int i=0;i<=8;i++){
                        for(int j=0;j<=2;j++){
                            if(first==tab[i][0]){
                                Game::win(tab[i][1]);
                                break;
                            }
                        }
                    }
			    }
			    system("cls");
			    cout<<"\nStan twojego konta "<<salary<<"$\n\n";
			}

		fruitMachine(){
			system("cls");
			instruction();
			system("cls");
			Game::setBet();
			system("cls");

			//(rand()%13 )+2;



			while(true){
                system("cls");
                cout<<"Twoj bet "<<bet<<"\n\n";
				cout<<"1. Start\n2. Wstecz\n";
				cin.ignore();
				cin.clear();
				cin>>next;
				while(!cin.good()){
                    system("cls");
					cin.ignore();
					cin.clear();
					cout<<"1. Start\n2. Wstecz\n";
					cin>>next;
				}
				if(next==1){
                    system("cls");
                    cout<<"Stan twojego konta "<<salary<<"$\n\n";
                    if(salary<bet){
                        cout<<"Niemasz wystarczajacej ilosci pieniedzy\n";
                        system("pause");
                        break;
                    }
                    if(salary>=bet){
                        system("cls");
                        go();
                    }
				}
				if(next==2){
				    system("cls");
					break;
				}
			}

		}
		void instruction(){
			cout<<"Instrukcja\n";
			cout<<"1. Wprowadz stawke\n2. Nastepuje losowanie 3 liczb \n3. Wygrywaja 3 lub 2 te same liczby\n";
			cout<<"4. Mnoznik\nJaka liczba | Mnoznik za dwie | Mnoznik za trzy\n";
			cout<<"1 | 1.3 | 1.5\n2 | 1.6 | 1.9\n3 | 2.1 | 2.2\n4 | 2.5 | 2.8\n5 | 3   | 3.25\n6 | 3.5 | 4\n7 | 5   | 6\n8 | 10  | 15\n9 | 20  | 30 \n";
			cout<<"5. Jezeli wypadnie 10 zastepuje dolwolna liczbe o ile pozostale dwie sa identyczne\nJezeli wypadnie 2 razy 10 oraz jakis znak, mnoznik wynosi 5\nJezeli wypadnie 3 razy 10 mnoznik wynosi 40\n";
			system("pause");
		}
};


void gameMenu(){
	system("cls");
	cout<<"Witamy "<<name<<" w Kasynie. Twoje saldo to "<<salary<<"$\n\n";
	cout<<"1. Jednoreki bandyta\n2. Ruletka\n3. Black Jack\n4. Wstecz\n5. Wyjdz\n";
	int j;
	cin>>j;
	if(j==1){
		system("cls");
        fruitMachine Fruit;
	}
	if(j==2){
	    //logIn();
	}
	if(j==3){
		system("cls");
	   	blackJack Jack;
	}
	if(j==4){
		return;
	}
	if(j==5){
		logOut();
	}
	else{
		cin.clear();
		cin.ignore();
		system("cls");
		cout<<"Wpisz jeszcze raz\n";
		gameMenu();
	}
}

bool exist(string name){
	fstream users;
	users.open("users.txt", ios::in);
	string line;
	while(!users.eof()){
        users>>line;
        users>>salary;
        if(line==name){
        	return true;
		}
    }
    return false;
    users.close();
}

void logIn(){
	fstream users;
	users.open("users.txt", ios::in);
	system("cls");
	cout<<"LOGOWANIE\n";
	cout<<"Podaj nazwe\nAby wyjsc wpisz exit\n";
	cin>>name;
	if(name=="exit"){
		return;
	}
	while(!cin.good() || !exist(name)){
		cin.clear();
		cin.ignore();
		system("cls");
		cout<<"Podana nazwa nie istnieje lub jest nieprawidlowa\nProsze podac inna\n";
		cout<<"Podaj nazwe\nAby wyjsc wpisz exit\n";
		cin>>name;
		if(name=="exit"){
			return;
		}
	}
	cout<<"\nZalogowales sie pomyslnie\nTwoje saldo to: "<<salary<<"\n";
	users.close();
	system("pause");
	gameMenu();
}

void deleteSpaces(){
	int k=0;

	while (name[k] != '\0'){
        if (isspace(name[k])){
        	name[k]='_';
		}
        k++;
	}
}

void signIn(){
	srand(time(NULL));
	fstream users;
	users.open("users.txt", ios::out | ios::app );
	system("cls");
	cout<<"REJESTRACJA\n";
	cout<<"Podaj nazwe\nAby wyjsc wpisz exit\n";
	cin.clear();
	cin.ignore();
	getline(cin >> ws, name);
	if(name=="exit"){
		return;
	}
	deleteSpaces();
    cout<<"Nazwa zostala zmieniona na "<<name<<"\n";

	while(exist(name)){
		cin.clear();
		cin.ignore();
		system("cls");
		cout<<"Podana nazwa juz istnieje lub jest nieprawidlowa\nProsze podac inna\n";
		cout<<"Podaj nazwe\nAby wyjsc wpisz exit\n";
		getline(cin,name);
		if(name=="exit"){
			return;
		}
		deleteSpaces();
		cout<<"Nazwa zostala zmieniona na "<<name<<"\n";
	}
	salary = (rand()%1000 );
	cout<<endl;
	cout<<"Stan konta: "<<salary<<"$\n";

	cout<<"\nZarejestrowales sie pomyslnie\nNacisnij Enter aby zagrac!\n";

	users<<name<<" "<<intToStr(salary)<<"\n";
	update(0);
	users.close();
	system("pause");
	gameMenu();
}

void ranking(){
	system("cls");
	cout<<"RANKING TOP 100\n\n";
	fstream users;
	users.open("users.txt", ios::in);
	string topName;
	int top=1;
	sortRank();
	while(!users.eof() || top>=100){
		getline(users,topName);
		if(topName.empty()|| topName==" ")continue;
		cout<<top<<". "<<topName<<"\n";
		top++;
	}
	cout<<"\nNacisnij Enter aby cofnac!\n";
	users.close();
	system("pause");
}

void mainMenu(){
	int i;
	cout<<"\nMENU\n1. Zapisz sie\n2. Mam juz konto\n3. Ranking\n4. Wyjdz\n";
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

int main() {
	cout<<"Witamy w kasynie AdamVegas\nMilej zabawy\n";
	mainMenu();
}
