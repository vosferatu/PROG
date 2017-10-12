# pragma once


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;


class Data {
 private:
	string date;
	int dia;
	int mes;
	int ano;

 public:

  Data(){ date = ""; dia = 1; mes = 1; ano = 1;};
  Data(string data); // data na forma DD/MM/AAA  //put "curr" to get current date
  Data(int day, int month, int year);
  
  int getDia() const;
  int getMes() const;
  int getAno() const;
  string getData() const;
  
  void setDate(string dat);
  void setDate(unsigned int d, unsigned int m, unsigned int y);
  void setDia(int day);
  void setMes(int month);
  void setAno(int year);

  friend bool truedate(const Data & data);    //verifica a data
  friend bool operator>=(const Data &date1, const Data &date2);  //maior data
  friend bool operator<=(const Data &date1, const Data &date2);
  friend bool operator==(const Data &date1, const Data &date2); //datas iguais

  friend ostream& operator<<(ostream& out, const Data & data); //mostrar data
};


