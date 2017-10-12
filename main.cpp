#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>

#include "Vende++.h"
#include "Menus.h"
#include "utils.h"


int main()
{
	string fichClients, fichProdutos, fichTransacoes;
 
	while (true)
	{
		  // pede a informacao sobre o nome da loja e os 3 ficheiros com
		// informacoo de clientes, produtos e transacoes
		cout << "Introduza o nome do ficheiro de clientes: ";
		getline(cin, fichClients);
	  
		 cout << "\nIntroduza o nome do ficheiro de produtos: ";
		 getline(cin, fichProdutos);
	  
		 cout << "\nIntroduza o nome do ficheiro de transacoes: ";
		 getline(cin, fichTransacoes);
	
		 if (!infoInicial(fichClients, fichProdutos, fichTransacoes)) //confirmar a informação
		 {
			cout << "\n\n" << TAB << "Dados incorretos! Por favor tente outra vez." << endl;
		 }
		 else break;
	}
	
	clearScreen();

	// cria o supermercado
	VendeMaisMais supermercado(fichClients, fichProdutos, fichTransacoes);

	startScreen();
	
	Sleep(3000);
	clearScreen();
	cout << endl << TAB_BIG << "Informacao do supermercado Vende++:" << endl;
	cout << supermercado << endl;  // mostra estatisticas do supermercado
   
	system("pause");
	clearScreen();

	menuInicial(supermercado); // menu inicial com as grandes opcoes
				// que implementam as funcionalidades
				// disponibilizadas

  return 0;
}
