#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <vector>
#include <stdio.h>

class Bank
{

  std::string choice;
  public:
  void login(){
    
    system("cls");
    std::cout<<"\n1.Verifica balanta \n2.Trimite bani \n3.Inapoi la meniu \n\nAlege: ";
    std::cin>>choice;


    if (choice == "1")
    {
      std::cout<<"\nVerifica balanta\n";
    }

    if (choice == "2")
    {
      std::cout<<"\nTrimite bani\n";
    }

    if (choice == "3")
    {
      std::cout<<"\nInapoi\n";

    }else{
      std::cout<<"Te rog sa alegi din meniu.";
    }
  }
  
};

class Login
{
  // Variabilele functiei sunt toate private
private:
  std::string un,pw,npw,cknpw,passtr;
  int ch;
  std::vector<std::string> data;
  Bank bank;

public:
std::vector<std::string> get_data(std::string username,std::string password){
std::ifstream infile;
std::string un,pw,check;
infile.open(username +".txt");
infile>>un;
infile>>pw;
infile.close();
data.push_back(un);
data.push_back(pw);
return data;
data[0] = un;
data[1] = pw;
}


void change_pas(std::string username,std::string password){   //Schimba parola
  data = get_data(username,password);
  if (username == data[0] && password == data[1]) 
  {
    A :
     std::cout<<"\nIntrodu parola noua: ";
     ch=0;
     while(ch = getch()) {
      if (ch == 8 ) 
      {
        std::cout<<"\b \b";
        npw.erase(npw.length() - 1);
      }else if (ch == 13) {
        break;
        
      }else{
        std::cout<<"*";
        npw.push_back(ch);
      }
    }
     std::cout<<"\nIntrodu din nou: ";
     while(ch = getch()) {
      if (ch == 8 ) 
      {
        std::cout<<"\b \b";
        cknpw.erase(cknpw.length() - 1);
      }else if (ch == 13) {
        break;
        
      }else{
        std::cout<<"*";
        cknpw.push_back(ch);
      }
    }
    if (npw == cknpw)
    {
     std::ofstream outfile;
     outfile.open(username + ".txt");
     outfile<<data[0];
     outfile<<std::endl;
     outfile<<npw;
     outfile.close();
     std::cout<<"\nParola a fost schimbata cu succes!\n";
    }else if (npw != cknpw)
    {
      std::cout<<"\nParola nu se potriveste - incerca din nou \n";
      goto A;
    }
    
  }else if(username == data[0] && password != data[1]){
    std::cout<<"\nTe rog introdu o parola valida\n";
  }else if(username != data[0] && password != data[1]) {
    std::cout<<"\nTe rog introdu o parola si un email valid\n";
  }
}


  



void reset_account(std::string username){   //reseteaza codul
  std::ifstream infile(username + ".txt");
  infile>>un;
  infile>>pw;
  if (username == un)
  {
    std::cout<<"\n\nCont gasit!\n";
    std::cout<<"Emailul tau este : "<<un<<std::endl;
    std::cout<<"Parola ta este : "<<pw<<std::endl;
  }else if(username != un){
    std::cout<<"\n\nNu pot gasi contul , te rog sa verifici daca emailul a fost scris corect\n";
 
    
  }
}



int del_account(std::string username,std::string password){   //Sterge contul
  data = get_data(username,password);
  un = data[0];
  pw = data[1];
  if (username == un && password == pw) 
  {
    std::cout<<"\n\nCont gasit!\n";
    std::cout<<"\nEsti sigurt ca vrei sa stergi ? (y/n) : ";
    if (getch() == 'y')
  {
    username.append(".txt");
    if(!remove(username.c_str())){
      std::cout<<"\nFisierul a fost sters cu succes\n";
    }else {
      std::cout<<"\n\nNu pot sterge contul!\n\n";
    }
  }else{
  return 1;
  }
  }else {
    std::cout<<"\nTe rog sa introduci un email si o parola valida\n";
}
}


void log(std::string username, std::string password){   //Conectare cont
  data = get_data(username,password);
  un = data[0];
  pw = data[1];
  // std::cout<<data[0]<<std::endl<<data[1];
    if (username == un && password == pw) {
    bank.login();
  }else if(username == un && password != pw){
    std::cout<<"\nTe rog sa introduci o parola valida"<<"\n";
}else if(username != un && password == pw){
  std::cout<<"\nTe rog sa introduci o parola valida\n";
}else if(username != un && password != pw) {
  std::cout<<"\nEmailul si parola sunt gresite !!\n";
}

}

void reg(std::string username, std::string password){   //Inregistreaza contul
    std::ofstream outfile;
    int get;
    outfile.open(username + ".txt");

    {
    }
    outfile<<username<<std::endl<<password;
    std::cout<<"\nContul a fost creat cu succes\n";
    outfile.close();
}




std::string getpas(){    //Face caracterele parolei sa apara ca ******
passtr.erase();
while(ch = getch()) {
      if (ch == 8 ) 
      {
        while(passtr.length() < 0){
        std::cout<<"\b \b";
        }if(passtr.length() > 0){
          std::cout<<"\b \b";
        passtr.erase(passtr.length() - 1);
        }
      }else if (ch == 13) {
        break;

        
      }else{
        std::cout<<"*";
        passtr.push_back(ch);
      }
    }
    return passtr;
}
  
};

int main () {
Login login;
int ch;
std::string username,password,choice;

do {

  std::cout<<"\n1. Login\n2. Register\n3. Sterge contul\n4. Reseteaza contul \n5. Schimba parola\n6. Exit  \n\nAlege: ";
  std::cin>>choice;

  
    
    if(choice == "1"){
    system("cls");
    std::cout<<"Introdu emailul: ";
    std::cin>>username;
    std::cout<<"Introdu parola: ";
   password = login.getpas();
    // std::cout<<"\n"<<password<<std::endl;

    login.log(username,password);
    }

    else if( choice == "2"){
    system("cls");
    R:
    username="";
    password="";
    std::cout<<"Introdu noul email: ";
    std::cin>>username;
    std::cout<<"Noua parola : ";
    password = login.getpas();
    if(password.length() <= 3) {
      system("cls");
      std::cout<<"\n\nTe rog sa folosesti o parola mai puternica!\n\n";
      goto R;
    }else{
      login.reg(username,password);
    }

  }
    else if(choice == "3"){
    system("cls");
    std::cout<<"Introdu emailul contului :";
    std::cin>>username;
    std::cout<<"Introdu parola contului :";
    password = login.getpas();
    login.del_account(username,password);

    }

    else if(choice == "4") {
    system("cls");
    std::cout<<"Introdu emailul: ";
    std::cin>>username;
    login.reset_account(username);

    }

    else if(choice == "5"){
    system("cls");
    std::cout<<"Introdu emailul: ";
    std::cin>>username;
    std::cout<<"Introdu parola: ";
    password = login.getpas();
    login.change_pas(username,password);
    }

   else if(choice == "6"){
    system("cls");
    std::cout<<"La revedere! -";
    return 1;
   }
    else {
      system("cls");
    std::cout<<"\n Te rog alege din meniu.\n";
    }
} while(true);
}







