#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "Data.h"

using namespace std;


class Cliente {
 private:
  unsigned int id;
  string nome;
  Data cartaoCliente;
  double volCompras;

 public:

  Cliente() { id = 0; nome = ""; cartaoCliente = Data("curr"); volCompras = 0;};
  Cliente(string & line);
  Cliente(unsigned int ide, string name, Data cartao, float gasto);

  string getNome() const;
  unsigned int getId() const;
  double getVolCompras() const;
  Data getcartaoCliente() const;
	
  void setVolCompras(double value);

  friend bool sortByVol(const Cliente &cliente1, const Cliente &cliente2); //para usar com sort
  friend ofstream& operator<<(ofstream& outer, const Cliente & cli);  // guarda a informacao do cliente no ficheiro
  friend ostream& operator<<(ostream& out, const Cliente & client);  //mostra o cliente no ecra

  //friend bool operator<(const Cliente &cli1, const Cliente &cli2); // compara 2 clientes (1 cliente e menor que outro se o seu nome for "alfabeticamente" inferior)
};

