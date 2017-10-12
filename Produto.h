#pragma once


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


using namespace std;



class Produto {
 private:
	string nome;
	double custo;


 public:
	Produto() { nome = ""; custo = 0.0; }
	Produto(string & in);
	string getNome() const;
	double getCusto() const;

	friend ostream& operator<<(ostream& out, const Produto & prod); // mostra produto
	//friend bool operator<(const Produto &prod1, const Produto &prod2); // compara dois produtos (1 produto e mais pequeno que outro se o seu nome for "alfabeticamente inferior"
};


