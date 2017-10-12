#pragma once

#include <iostream>
#include <fstream>
#include <string>


#include "defs.h"
#include "utils.h"
#include "Vende++.h"

using namespace std;

bool infoInicial(string & fichClients, string & fichProdutos, string & fichTransacoes);

void menuInicial(VendeMaisMais & supermercado);

void menuGestaoClientes(VendeMaisMais & supermercado);

void menuInformacao(VendeMaisMais & supermercado);

//void opcoesRecomendacao(VendeMaisMais & supermercado);
