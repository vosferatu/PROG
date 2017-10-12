#pragma once


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "Data.h"



using namespace std;


class Transacao {
 private:
	
	unsigned int idCliente;
	Data data; // na forma DD/MM/AAAAA
	vector<string> produtos;

 public:
	
	Transacao() { idCliente = 0; data = Data("curr"); };
	Transacao(string & in); // transacao na forma de  idCliente ; data ; lista de produtos
	Transacao(unsigned int ide, Data date, vector<string>& products);
	
	unsigned int getIdCliente() const;
	Data getDateClient() const;
	const vector<string>& getProdutos() const;
	
	friend bool sortByDate(const Transacao &trans1, const Transacao &trans2); //para usar com sort
	friend ofstream& operator<<(ofstream& outer, const Transacao & transfer); //guarda a transacao
	friend ostream& operator<<(ostream& out, const Transacao & trans); // mostra a transacao
};



