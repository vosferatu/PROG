#pragma once

#include <iostream>
#include <string>
#include <map>
#include<algorithm>


#include "defs.h"
#include "Data.h"
#include "Cliente.h"
#include "Transacao.h"
#include "Produto.h"
#include "utils.h"


using namespace std;

class VendeMaisMais{
 private:
  string fichClientes, fichProdutos, fichTransacoes; // nome dos
						     // ficheiros de
						     // clientes,
						     // produtos e
						     // transacoes
  bool transacoesAlteradas; // flag que fica a true se for preciso guardar no final as transacoes
  bool clientesAlterados; // flag que fica a true se for preciso guardar no final os clientes
  unsigned int maxClientesId; // variavel que guarda o identificador unico do cliente com o maior numero de identificacao
  unsigned int maxGhostsId; //identificador do cliente de transacoes com o maior id (pode ser fantasma)
  vector<Cliente> clientes; // vetor que guarda a informacao dos clientes existentes
  vector<Produto> produtos; // vetor que guarda a informacao dos produtos disponiveis
  vector<Transacao> transacoes; // vetor que guarda a informacao das transacoes efetuadas
  map<string, int> clienteIdx;  // map para "traduzir" nome do cliente no  correspondente  indice no vetor de clientes
  map<string, int> produtoIdx;  // map para "traduzir" nome do produto no correspondente indice no vetor de produtos
  multimap<int, int> transacaoIdx; // multimap para "traduzir" o identificador do cliente nos indices das suas
				   // transacoes no vetor de transacoes

 public:
  
  VendeMaisMais(string fichClient, string fichProduto, string fichTransacao);
  void readClients();
  void readProd();
  void readTrans();
  void fillclimap();
  void fillprodmap();
  void filltransmap();

  unsigned int searchByName() const;
  unsigned int searchByClienteID() const;
  vector<unsigned int> searchByTransID() const;

  void InformacaoCliente() const;
  void InformacaoTransacoes() const;

  bool checkID(unsigned int value) const;
  bool checkTransID(unsigned int value) const;
  void alteraClienteMenu(unsigned int look);

  void criaCliente();
  void alteraCliente();
  void removeCliente();

  void compras(); 

  void Ad();

  void clientAd(unsigned int target);
  void bottom10Ad();

  void saveChanges();

  bool searchtruth(int cli, int prod, vector<Transacao>& tra, vector<Cliente>& clientes, vector<Produto>& produtos);
  bool searchtruthghosts(int fanta, int prod, vector<unsigned int>& ghost, vector<Transacao>& tra, vector<Produto>& produtos);

  friend ostream& operator<<(ostream& out, const VendeMaisMais & supermercado); //serve para mostrar estatisticas
  friend ofstream& operator<<(ofstream& outer, const VendeMaisMais & supermercado);

  friend Data definirData();
};
