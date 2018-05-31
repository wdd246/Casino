#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>
#include "functions.cpp"
#include "Game.h"
#include "blackJack.h"
using namespace std;

int salary;
string name;

int main() {
	void wait();
	void logOut();
	string intToStr(int n);
	int strToInt(string s);
	void mainMenu();
	void ranking();
	void signIn();
	void logIn();
	bool exist(string name);
	void gameMenu();
	void update(int bet);
	void sortRank();
	void deleteSpaces();
	cout<<"Witamy w kasynie AdamVegas\nMilej zabawy\n";
	mainMenu();
}



void logOut(){
	wait();
	exit(0);
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

void gameMenu(){
	system("cls");
	cout<<"Witamy "<<name<<" w Kasynie. Twoje saldo to "<<salary<<"$\n\n";
	cout<<"1. Jednoreki bandyta\n2. Ruletka\n3. Black Jack\n4. Wstecz\n5. Wyjdz\n";
	int j;
	cin>>j;
	if(j==1){
		system("cls");
		blackJack black;
	   	black.blackStart();
	}
	if(j==2){
	    //logIn();
	}
	if(j==3){
		//ddd
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
	cout<<"\nZalogowales sie pomyslnie\nTwoje saldo to: "<<salary<<"\nNacisnij Enter aby zagrac!\n";
	users.close();
	gameMenu();
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
	}
	salary = (rand()%1000 );
	cout<<endl;
	cout<<"Stan konta: "<<salary<<"$\n";
	cout<<"\nZarejestrowales sie pomyslnie\n";
	users<<name<<" "<<intToStr(salary)<<"\n";
	update(0);
	users.close();
	wait();
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
	wait();
	users.close();
	
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




