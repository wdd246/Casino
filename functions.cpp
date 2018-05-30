#include <iostream>
#include <fstream>
#include <string>

using namespace std;

extern string name;
extern int salary;

void wait(){
	cin.clear();
    cout<<"Nacisnij dowolny klawisz aby kontynowac...\n";
    cin.ignore();
	//cin.ignore();
	//cin.clear();
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
