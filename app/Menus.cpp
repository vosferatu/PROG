#include "Menus.h"



bool infoInicial(string & fichClientes, string & fichProdutos, string & fichTransacoes)
{

	bool um = false, dois = false, tres = false;
	int cli, trans, prod;
	//uso de variaveis locais e flags para verificar os ficheiros
	string one, two, three;
	
	if (fichClientes.size() < 4)
		fichClientes = fichClientes + ".txt";
	else
	{
		one = fichClientes.substr(fichClientes.size() - 5, fichClientes.size() - 1);
		if (one != ".txt")
		{
			fichClientes = fichClientes + ".txt";
		}
	}

	if (fichProdutos.size() < 4)
		fichProdutos = fichProdutos + ".txt";
	else
	{
		two = fichProdutos.substr(fichProdutos.size() - 5, fichProdutos.size() - 1);
		if (two != ".txt")
		{
			fichProdutos = fichProdutos + ".txt";
		}
	}

	if (fichTransacoes.size() < 4)
		fichTransacoes = fichTransacoes + ".txt";
	else
	{
		three = fichTransacoes.substr(fichTransacoes.size() - 5, fichTransacoes.size() - 1);
		if (three != ".txt")
		{
			fichTransacoes = fichTransacoes + ".txt";
		}
	}

	ifstream primeiro;
	primeiro.open(fichClientes);
	if (primeiro.is_open())
	{
		um = true;
		if (primeiro.peek() == std::ifstream::traits_type::eof())
		{
			um = false;
			cout << "\nO ficheiro de clientes '" << fichClientes << "' esta vazio.\n";
		}
		else 
		{
			primeiro >> cli;
			if (cli == 0)
			{
				cout << "0 clientes no ficheiro: " << fichClientes;
				um = false;
			}
		}
	}
	else
	{
		cout << "\nImpossivel abrir o ficheiro: " << fichClientes << " !!!";
		um = false;
	}
	primeiro.close();

	ifstream segundo;
	segundo.open(fichProdutos);
	if (segundo.is_open())
	{
		dois = true;
		if (segundo.peek() == std::ifstream::traits_type::eof())
		{
			dois = false;
			cout << "\nO ficheiro de produtos '" << fichProdutos << "' esta vazio.\n";
		}
		else
		{
			segundo >> prod;

			if (prod == 0)
			{
				cout << "0 produtos no ficheiro: " << fichProdutos;
				dois = false;
			}
		}
	}
	else
	{
		cout << "\nImpossivel abrir o ficheiro: " << fichProdutos << " !!!";
		dois = false;
	}
	segundo.close();

	ifstream terceiro;
	terceiro.open(fichTransacoes);
	if (terceiro.is_open())
	{
		tres = true;
		if (terceiro.peek() == std::ifstream::traits_type::eof())
		{
			tres = false;
			cout << "\nO ficheiro de transacoes '" << fichTransacoes << "' esta vazio.\n";
		}
		else
		{
			terceiro >> trans;
			if (trans == 0)
			{
				cout << "0 transacoes no ficheiro: " << fichTransacoes;
				tres = false;
			}

		}
	}
	else
	{
		cout << "\nImpossivel abrir o ficheiro: " << fichTransacoes << " !!!";
		tres = false;
	}
	terceiro.close();

	if (um && dois && tres)     //verifica se os 3 ficheiros estao corretos
		return true;
	else return false;
}

/******************************************
 * Gestao de Clientes
 ******************************************/
void menuGestaoClientes(VendeMaisMais & supermercado)
{
  unsigned short int opcao;

  clearScreen();

  cout << TAB_BIG << "Menu Gestao Clientes:" << endl;
  cout << TAB << "1 - Criar cliente" << endl;
  cout << TAB << "2 - Editar cliente" << endl;
  cout << TAB << "3 - Remover cliente" << endl;
  cout << TAB << "0 - Voltar ao menu inicial" << endl << endl;
  cout << TAB << "Qual a sua opcao: ";
  opcao = leUnsignedShortInt(0, 3);

  switch (opcao)
  {
  case 0:
	  return;
	  break;
  case 1:
	  supermercado.criaCliente();
	  break;
  case 2:
	  supermercado.alteraCliente();
	  break;
  case 3:
	  supermercado.removeCliente();
	  break;
  }

  system("pause");
}

void menuInformacao(VendeMaisMais & supermercado)
{
	unsigned short int opcao;

	clearScreen();

	cout << TAB_BIG << "Menu Visualizacao de Informacao:" << endl;
	cout << TAB << "1 - Informacao de Clientes" << endl;
	cout << TAB << "2 - Informacao de Transacoes" << endl;
	cout << TAB << "0 - Voltar ao menu inicial" << endl << endl;
	cout << TAB << "Qual a sua opcao: ";
	opcao = leUnsignedShortInt(0, 2);

	switch (opcao)
	{
	case 0:
		return;
		break;
	case 1:
		supermercado.InformacaoCliente();
		break;
	case 2:
		supermercado.InformacaoTransacoes();
		break;
	}

	system("pause");
}

/******************************************
 * Menu Inicial
 ******************************************/
void menuInicial(VendeMaisMais & supermercado)
{
  unsigned short int opcao;

  clearScreen();

  cout << TAB_BIG << "Menu Inicial" << endl;
  cout << TAB << "1 - Gestao de clientes" << endl;
  cout << TAB << "2 - Visualizar Informacao" << endl;
  cout << TAB << "3 - Efetuar Compras" << endl;
  cout << TAB << "4 - Recomendacoes" << endl;
  cout << TAB << "0 - Sair do programa" << endl << endl;
  cout << TAB << "Qual a sua opcao: ";
  opcao = leUnsignedShortInt(0, 4);

  switch (opcao)
  {
  case 0:
	  return;
	  break;
  case 1: 
	  menuGestaoClientes(supermercado);
	  break;
  case 2:
	  menuInformacao(supermercado);
	  break;
  case 3: 
	  supermercado.compras();
	  break;
  case 4: 
	  supermercado.Ad();
	  break;
  }

  menuInicial(supermercado);
}