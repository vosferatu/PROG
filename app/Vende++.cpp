#include "Vende++.h"


//Armazena a informação
VendeMaisMais::VendeMaisMais(string fichClient, string fichProduto, string fichTransacao)
{//nome de ficheiros
	fichClientes = fichClient;
	fichProdutos = fichProduto;
	fichTransacoes = fichTransacao;
	//preencher vetores
	readClients();
	readProd();
	readTrans();
	//inicializar flags
	transacoesAlteradas = false;
	clientesAlterados = false;
	//preencher maps
	fillclimap();
	fillprodmap();
	filltransmap();

	//preencher max ID's
	unsigned int max1 = 0, max2 = 0;
	for (size_t i = 0; i < clientes.size(); i++)
	{
		if (clientes[i].getId() > max1)
			max1 = clientes[i].getId();
	}
	maxClientesId = max1;

	for (size_t i = 0; i < transacoes.size(); i++)
	{
		if (transacoes[i].getIdCliente() > max2 && checkID(transacoes[i].getIdCliente()) == false)
			max2 = transacoes[i].getIdCliente();
	}
	maxGhostsId = max2;
}

//Le os ficheiros para os vetores
void VendeMaisMais::readClients()
{
	ifstream mfile;
	istringstream linhas;
	string linha;

	mfile.open(fichClientes);

	getline(mfile, linha);
	linhas.str(linha);
	int max;
	linhas >> max;
	
	clientes.resize(max);

	for (size_t i = 0; i < clientes.size(); i++)
	{
		if (getline(mfile, linha), linha == "")
		{
			getline(mfile, linha);
		}
		linhas.str(linha);
		clientes[i] = Cliente(linha);
	}

	mfile.close();

	sort(clientes.begin(), clientes.end(), sortByVol); //ordena logo todos os clientes pelo seu volume de compras
}

void VendeMaisMais::readProd()
{
	ifstream mfile;
	istringstream linhas;
	string linha;

	mfile.open(fichProdutos);
	
	getline(mfile, linha);
	linhas.str(linha);
	int max;
	linhas >> max;

	produtos.resize(max);

	for (size_t i = 0; i < produtos.size(); i++)
	{
		if (getline(mfile, linha), linha == "")
		{
			getline(mfile, linha);
		}
		linhas.str(linha);
		produtos[i] = Produto(linha);
	}

	mfile.close();
}

void VendeMaisMais::readTrans()
{
	ifstream mfile;
	istringstream linhas;
	string linha;

	mfile.open(fichTransacoes);

	getline(mfile, linha);
	linhas.str(linha);
	int max;
	linhas >> max;

	transacoes.resize(max);

	for (size_t i = 0; i < transacoes.size(); i++)
	{
		if (getline(mfile, linha), linha == "")
		{
			getline(mfile, linha);
		}
		linhas.str(linha);
		transacoes[i] = Transacao(linha);
	}
	mfile.close();
											//ordena todas as transacoes por data
											//de modo a serem usadas na visualização de informação cronológica
											//os maps sao preenchidos depois desta operação
	sort(transacoes.begin(), transacoes.end(), sortByDate); //pelo que não sao afetados por isso

}															
//preenche os maps
void VendeMaisMais::fillclimap()
{
	for (size_t i = 0; i < clientes.size(); i++)
	{
		clienteIdx.insert(pair<string, int>(clientes[i].getNome(), i));
	}
}

void VendeMaisMais::fillprodmap()
{
	for (size_t i = 0; i < produtos.size(); i++)
	{
		produtoIdx.insert(pair<string, int>(produtos[i].getNome(), i));
	}
}

void VendeMaisMais::filltransmap()
{
	for (size_t i = 0; i < transacoes.size(); i++)
	{
		transacaoIdx.insert(pair<int, int>(transacoes[i].getIdCliente(), i));
	}
}

/**********************************/
//pesquisas (por nome ou id) uteis para gestao de clientes e visualização de informação  
///////////////////////////////////   (TALVEZ ACRESCENTAR PESQUISA POR DATAS PARA TRANS)
unsigned int VendeMaisMais::searchByName() const
{
	unsigned int indice = 0;
	string nome = "";
	bool flag = false;

	while (true)
	{
		cout << endl << TAB << "Nomes dos clientes existentes: " << endl;
		for (size_t i = 0; i < clientes.size(); i++)
		{
			cout << TAB << clientes[i].getId() << " - " << clientes[i].getNome() << endl;
		}
		
		cout << endl << TAB << "Introduza o nome do cliente: ";
		getline(cin, nome);

		if (nome == "")
		{
			getline(cin, nome);
		}

		

		for (size_t i = 0; i < clientes.size(); i++)
		{
			if (clientes[i].getNome() == nome)
			{
				indice = i;
				flag = true;
				break;
			}
		}
		
		
		if (flag == true)
			break;
		else cout << endl << TAB << "'" << nome << "' nao existe. Tente outra vez." << endl;
	}

	return indice;
}

unsigned int VendeMaisMais::searchByClienteID() const
{
	unsigned int id, indice;
	bool flag = false;

	while (true)
	{
		cout << endl << TAB << "ID's dos clientes existentes: " << endl;
		for (size_t i = 0; i < clientes.size(); i++)
		{
			cout << TAB << clientes[i].getId() << " - " << clientes[i].getNome() << endl;
		}

		cout << endl << TAB << "Introduza o ID do cliente: ";
		id = leInteiro(1, maxClientesId);

		for (size_t i = 0; i < clientes.size(); i++)
		{
			if (clientes[i].getId() == id)
			{
				indice = i;
				flag = true;
				break;
			}
		}

		if (flag)
			break;
		else cout << endl << TAB << "'" << id << "' nao existe. Tente outra vez." << endl;

	}

	return indice;
}

vector<unsigned int> VendeMaisMais::searchByTransID() const  //utiliza-se nas transacoes
{															//de um cliente
	unsigned int id;
	vector<unsigned int> indices;
	unsigned short int option;

	cout << endl << TAB << "1 - Pesquisa por nome." << endl;
	cout << TAB << "2 - Pesquisa por ID." << endl;
	cout << "Introduza a sua opcao: ";
	option = leUnsignedShortInt(1, 2);
	
	switch (option)
		{
		case 1:
			id = searchByName();
			break;
		case 2:
			id = searchByClienteID();
			break;
		} 

	cout << endl << TAB_BIG << "O cliente procurado foi encontrado:\n";
	cout << TAB << clientes[id] << endl << endl;

	for (size_t i = 0; i < transacoes.size(); i++)
	{
		if (transacoes[i].getIdCliente() == id)
		{
			indices.push_back(i);
		}
	}

	return indices;
}

bool VendeMaisMais::checkID(unsigned int value) const
{
	bool found = false;

	for (size_t i = 0; i < clientes.size(); i++)
	{
		if (clientes[i].getId() == value)
			found = true;
	}
	return found;
}

bool VendeMaisMais::checkTransID(unsigned int value) const
{
	bool found = false;

	for (size_t i = 0; i < transacoes.size(); i++)
	{
		if (transacoes[i].getIdCliente() == value)
			found = true;
	}
	return found;
}

///////////////////////////////////////////////////
// DEFINIR DATA (ATUAL OU INTRODUÇÃO DO UTILIZADOR)
Data definirData()
{
	unsigned  short int option;
	Data nova;
	cout << endl << TAB_BIG << "Definir a Data:" << endl;
	cout << TAB << "1 - Data de hoje." << endl;
	cout << TAB << "2 - Introduzir Manualmente." << endl;
	option = leUnsignedShortInt(1, 2);

	switch (option)
	{
	case 1:
		nova.setDate("curr");
		break;
	case 2:
		unsigned int day, month, year;
		do
		{
			cout << TAB << "Insira o dia: ";
			day = leUnsignedShortInt(1, 31);
			cout << TAB << "Insira o mes: ";
			month = leUnsignedShortInt(1, 12);
			cout << TAB << "Insira o ano: ";
			year = leUnsignedShortInt(2000, 2099);
			nova.setDate(day, month, year);

			if (truedate(nova) == false)
				cout << endl << TAB << "A data " << nova << " nao existe. Tente outra vez." << endl;
		} while (truedate(nova) == false);
	}

	return nova;
}

/*********************************
 * Gestao de Clientes
 ********************************/  
//////////////////////////////////
//visualizar clientes
//////////////////////////////////
void VendeMaisMais::InformacaoCliente() const
{
	unsigned int id;
	unsigned short int opcao;

	cout << endl << TAB_BIG << "Menu Informacao de Clientes:" << endl;
	cout << TAB << "1 - Informacao de um cliente." << endl;
	cout << TAB << "2 - Informacao dos clientes." << endl;
	cout << TAB << "0 - Menu Principal" << endl;
	cout << "Introduza a sua opcao: ";
	opcao = leUnsignedShortInt(0, 2);

	switch (opcao)
	{
	case 0:
		return;
		break;
	case 1:
		clearScreen();
		unsigned int option;

		cout << endl << TAB << "1 - Pesquisa por nome." << endl;
		cout << TAB << "2 - Pesquisa por ID." << endl;
		cout << "Introduza a sua opcao: ";
		option = leUnsignedShortInt(1, 2);

		switch (option)
		{
		case 1:
			id = searchByName();
			cout << endl << TAB_BIG << "O cliente procurado foi encontrado:\n";
			cout << TAB << clientes[id] << endl << endl;
			break;
		case 2:
			id = searchByClienteID();
			cout << endl << TAB << "O cliente procurado foi encontrado:\n";
			cout << endl << TAB_BIG << clientes[id] << endl << endl;
			break;
		}
		break;
	case 2:
		clearScreen();
		//o map ordena automaticamente por ordem alfabetica (map ordena as key, neste caso strings)
		// que sao os nomes dos clientes
		map<string, int>::const_iterator s;
		
		cout << endl << TAB << "Lista de Clientes:" << endl << endl;

		for (s = clienteIdx.begin(); s != clienteIdx.end(); s++)
		{
			cout << TAB_BIG << clientes[s->second] << endl;
		}
		break;
	}
}

////////////////////////////////
//gerir clientes
///////////////////////////////
void VendeMaisMais::criaCliente()
{
	clearScreen();
	unsigned int idNovo;
	string newName;

	do
	{
		cout << endl << TAB << "Insira o ID do novo cliente: ";
		idNovo = leInteiro(0, 4294967295); //maximo unsigned int

		if (checkID(idNovo) == true || checkTransID(idNovo) == true)
			cout << endl << TAB << "O ID " << idNovo << " ja existe. Tente outra vez.\n";
	} while (checkID(idNovo) == true || checkTransID(idNovo) == true);

	do
	{
		cout << endl << TAB << "Insira o nome do novo cliente:\n";
		cin.clear();
		cin.ignore(100, '\n');
		getline(cin, newName);
		if (newName == "")   //pensar em mais condicoes
		{
			cout << endl << TAB << "Nome invalido!\n";
		}
		else break;
	} while (true);

	cout << endl << TAB << "Data do cartao do cliente. \n";
	Data novaData = definirData();

	Cliente novo(idNovo, newName, novaData, 0.0);

	clientes.push_back(novo);

	cout << endl << TAB << "O novo cliente foi criado!" << endl;
	cout << TAB_BIG << novo << endl;

	clientesAlterados = true;
	saveChanges();
}

void VendeMaisMais::alteraCliente()
{
	clearScreen();
	unsigned short int option;
	unsigned int id;

	cout << endl << TAB_BIG << "Alterar Cliente" << endl;
	cout << TAB << "1 - Pesquisa por nome." << endl;
	cout << TAB << "2 - Pesquisa por ID." << endl;
	cout << "Introduza a sua opcao: ";
	option = leUnsignedShortInt(1, 2);

	switch (option)
	{
	case 1:
		id = searchByName();
		cout << endl << TAB << "O cliente procurado foi encontrado:\n";
		cout << TAB_BIG << clientes[id] << endl << endl;

		alteraClienteMenu(id);
		break;
	case 2:
		id = searchByClienteID();
		cout << endl << TAB << "O cliente procurado foi encontrado:\n";
		cout << TAB_BIG << clientes[id] << endl << endl;

		alteraClienteMenu(id);
		break;
	}

	clientesAlterados = true;
	saveChanges();
}

// só faz sentido alterar o montante de compras. alterar id e nome não faz porque sao
//identificadores mutuamente unicos (combinacao id/nome é unica, apesar de poder haver nomes iguais)
// a data do cartao tambem não faz sentido alterar pois guarda a informação
//acerca do momento de adesao do cliente
void VendeMaisMais::alteraClienteMenu(unsigned int look)
{
	clearScreen();
	unsigned short int option;
	double newValue;

	cout << endl << TAB_BIG << "Alterar volume de compras" << endl;
	cout << TAB << "1 - Acrescentar valor." << endl;  //coima ou algo do genero
	cout << TAB << "2 - Definir novo valor." << endl; //limpar conta e adicionar um custo
	cout << TAB << "3 - Colocar a conta a 0." << endl;//limpar conta
	cout << "Introduza a sua opcao: ";
	option = leUnsignedShortInt(1, 3);

	switch (option)
	{
	case 1:
		cout << endl << TAB << "Introduza o valor a acrescentar: ";
		while (true)
		{
			if (cin >> newValue)
				break;
			else {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << endl << TAB << "Invalido. Tente outra vez: ";
			}
		}
		clientes[look].setVolCompras(newValue + clientes[look].getVolCompras());
		cout << endl << TAB <<"O cliente foi alterado!" << endl;
		cout << TAB_BIG << clientes[look] << endl;
		break;
	case 2:
		cout << endl << TAB << "Introduza o novo valor: ";
		while (true)
		{
			if (cin >> newValue)
				break;
			else {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << endl << TAB << "Invalido. Tente outra vez: ";
			}
		}
		clientes[look].setVolCompras(newValue);
		cout << endl << TAB << "O cliente foi alterado!" << endl;
		cout << TAB_BIG << clientes[look] << endl;
		break;
	case 3:
		clientes[look].setVolCompras(0.0);
		cout << endl << TAB << "O cliente foi alterado!" << endl;
		cout << TAB_BIG << clientes[look] << endl;
		break;
	}

}

void VendeMaisMais::removeCliente()
{
	clearScreen();
	unsigned short int option;
	unsigned int id;

	cout << endl << TAB_BIG << "Alterar Cliente" << endl;
	cout << TAB << "1 - Pesquisa por nome." << endl;
	cout << TAB << "2 - Pesquisa por ID." << endl;
	cout << "Introduza a sua opcao: ";
	option = leUnsignedShortInt(1, 2);

	switch (option)
	{
	case 1:
		id = searchByName();
		cout << endl << TAB << "O cliente procurado foi encontrado:\n";
		cout << TAB_BIG << clientes[id] << endl << endl;

		clientes.erase(clientes.begin() + id);
		cout << endl << TAB << "O cliente foi eliminado!" << endl;
		break;
	case 2:
		id = searchByClienteID();
		cout << endl << TAB_BIG << "O cliente procurado foi encontrado:\n";
		cout << TAB << clientes[id] << endl << endl;
		
		clientes.erase(clientes.begin() + id);
		cout << endl << TAB << "O cliente foi eliminado!" << endl;
		break;
	}

	clientesAlterados = true;
	saveChanges();
}

/*******************************
*Gestao de Transacoes
********************************/
void VendeMaisMais::InformacaoTransacoes() const
{
	clearScreen();
	unsigned int opcao;
	Data diaTrans, entreDatas1, entreDatas2;
	vector<unsigned int> ides;

	cout << endl << TAB_BIG << "Menu Informacao de Transacoes:" << endl;
	cout << TAB << "1 - Informacao de um cliente." << endl;
	cout << TAB << "2 - Informacao de um dia." << endl;
	cout << TAB << "3 - Informacao entre duas datas." << endl;
	cout << TAB << "4 - Informacao de todas as transacoes." << endl;
	cout << TAB << "0 - Menu Principal" << endl;
	cout << "Introduza a sua opcao: ";
	opcao = leUnsignedShortInt(0, 4);

	switch (opcao)
	{
	case 0:
		return;
		break;
	case 1:
		clearScreen();
		ides = searchByTransID();

		if (ides.size() == 0)
			cout << endl << TAB << "O cliente nao realizou transacoes." << endl;
		else
		{
			cout << endl << TAB << "As transacoes do cliente sao:" << endl << endl;

			for (size_t i = 0; i < ides.size(); i++)
			{
				cout << TAB << transacoes[ides[i]] << endl;
			}
			cout << endl;
		}
	break;
	
	case 2:
		clearScreen();
		cout << endl << TAB << "Introduza a data a procurar: " << endl;
		diaTrans = definirData();
		
		cout << endl << TAB_BIG << "As transacoes de " << diaTrans << " sao:" << endl << endl;

		for (size_t i = 0; i < transacoes.size(); i++)
		{
			if (transacoes[i].getDateClient() == diaTrans)
				cout << TAB << transacoes[i] << endl;
		}
		cout << endl;
	break;
	case 3:
		clearScreen();
		cout << endl << TAB_BIG << "Introduza a primeira data: " << endl;
		entreDatas1 = definirData();
		cout << endl << TAB_BIG << "Introduza a segunda data: " << endl;
		entreDatas2 = definirData();
		
		if (!(entreDatas2 >= entreDatas1))
			swap(entreDatas1, entreDatas2);

		cout << endl << TAB_BIG << "As transacoes entre " << entreDatas1 << " e " << entreDatas2 << " sao:" << endl << endl;

		for (size_t i = 0; i < transacoes.size(); i++)
		{
			if ((transacoes[i].getDateClient() >= entreDatas1) && (transacoes[i].getDateClient() <= entreDatas2))
				cout << TAB << transacoes[i] << endl;
		}
		cout << endl;
		break;
	case 4:
		clearScreen();
		cout << endl << TAB_BIG << "Todas as transacoes:" << endl << endl;

		for (size_t i = 0; i < transacoes.size(); i++)
		{
				cout << TAB << transacoes[i] << endl;
		}
		cout << endl;
		break;
	}
}

/*********************************
*Compras
***********************************/
void VendeMaisMais::compras()
{
	clearScreen();
	cout << endl << TAB_BIG << "Fazer Compras:\n" << endl;
	cout << TAB << "Pesquisar pelo cliente:\n";
	double custoTrans = 0.0;
	unsigned int choice = 1, changeCount = 0, indice, id;

	unsigned int option;

	cout << endl << TAB << "1 - Pesquisa por nome." << endl;
	cout << TAB << "2 - Pesquisa por ID." << endl;
	cout << "Introduza a sua opcao: ";
	option = leUnsignedShortInt(1, 2);

	switch (option)
	{
	case 1:
		indice = searchByName();
		id = clientes[indice].getId();

		cout << endl << TAB_BIG << "O cliente procurado foi encontrado:\n";
		cout << TAB << clientes[indice] << endl << endl;
		break;
	case 2:
		indice = searchByClienteID();
		id = clientes[indice].getId();

		cout << endl << TAB_BIG << "O cliente procurado foi encontrado:\n";
		cout << TAB << clientes[indice] << endl << endl;
		break;
	}

	cout << endl <<  TAB_BIG << "Introduza a data da nova transacao." << endl;
	Data transacaoData;
	do
	{
		transacaoData = definirData();
		if (transacaoData >= clientes[indice].getcartaoCliente())
			break;
		else
		{
			cout << endl << TAB << "A data introduzida: " << transacaoData <<
				" e menor do que a data de adesao do cliente: " << clientes[indice].getcartaoCliente()
				<< ". Tente outra vez." << endl;
		}
	} while (true);

	vector<string> prodescolha;

	while (choice != 0)
	{

		cout << endl << TAB_BIG << "Produtos Disponiveis:" << endl;
		for (size_t i = 0; i < produtos.size(); i++)
		{
			cout << TAB << i + 1 << " - " << produtos[i] << "$" << endl;
		}

		cout << "\nEscolha uma opcao (0 para terminar): ";
		choice = leUnsignedShortInt(0, produtos.size());

		if (choice == 0)
			break;

		changeCount++;
		
		prodescolha.push_back(produtos[choice - 1].getNome());
		custoTrans = custoTrans + produtos[choice - 1].getCusto();
	}

	if (changeCount == 0)
	{
		cout << endl << TAB_BIG << "Nenhum Produto adicionado.\n";
		return;
	}

	Transacao novaTrans(id, transacaoData, prodescolha);
	transacoes.push_back(novaTrans);

	clientes[indice].setVolCompras(clientes[indice].getVolCompras() + custoTrans);

	transacoesAlteradas = true;
	clientesAlterados = true;
	saveChanges();

	cout << endl << TAB << "A nova transacao foi adicionada: " << endl << endl;
	cout << endl << TAB_BIG << novaTrans << endl;
}

/*********************************
 * Preservar Informacao
 ********************************/  
// guarda apenas a informacao de clientes e/ou de transacoes que foi alterada
void VendeMaisMais::saveChanges()  //nao e´const
{
	if (clientesAlterados == true)
	{
		ofstream writeClient;
		writeClient.open(fichClientes, ofstream::out | ofstream::trunc);
		
		if (!writeClient)
		{
			cout << endl << TAB << "Ficheiro danificado.\nImpossivel escrever dados!" << endl;
			return;
		}

		writeClient << clientes.size() << endl;

		for (size_t i = 0; i < clientes.size(); i++)
		{
			writeClient << clientes[i] << endl;   //newline que fica a mais não importa
		}										//porque ao ler o ficheiro faz-se resize do vetor
												//para o numero de clientes que aparece na primeira linha

		sort(clientes.begin(), clientes.end(), sortByVol); //faz o sort do pelo volume de compras de novo
		fillclimap();		//atualiza o map
	}									

	if (transacoesAlteradas == true)
	{
		ofstream writeTrans;
		writeTrans.open(fichTransacoes, ofstream::out | ofstream::trunc);

		if (!writeTrans)
		{
			cout << endl << TAB << "Ficheiro danificado.\nImpossivel escrever dados!" << endl;
			return;
		}

		writeTrans << transacoes.size() << endl;

		for (size_t i = 0; i < transacoes.size(); i++)
		{
			writeTrans << transacoes[i] << endl;   //newline que fica a mais não importa
		}										//porque ao ler o ficheiro faz-se resize do vetor
										//para o numero de clientes que aparece na primeira linha
	
		sort(transacoes.begin(), transacoes.end(), sortByDate); //atualiza a ordem por datas
		filltransmap();                    //atualiza o map
	}
	clientesAlterados = false;  //nao é const para nao guardar quando nao e necessario
	transacoesAlteradas = false; //depois de guardar faz reset as flags
}

/*********************************
 * Mostrar Loja
 ********************************/  
// mostra o conteudo de uma loja //usado para estatisticas //pensar em mais cenas para aqui
ostream& operator<<(ostream& out, const VendeMaisMais & supermercado)
{
	out << TAB << "Numero de clientes: " << supermercado.clientes.size() << endl;
	out << TAB << "Numero de Transacoes: " << supermercado.transacoes.size() << endl;
	
	double totalTransactions = 0.0;
	for (size_t i = 0; i < supermercado.clientes.size(); i++)
	{
		totalTransactions = totalTransactions + supermercado.clientes[i].getVolCompras();
	}

	out << TAB << "Volume de compras dos clientes atuais: " << totalTransactions << endl;
	out << TAB << "Media de gasto por cliente: " << totalTransactions / supermercado.clientes.size() << endl;

	double totalGhosts = 0.0;
	for (size_t i = 0; i < supermercado.transacoes.size(); i++)
	{
		for (size_t j = 0; j < supermercado.transacoes[i].getProdutos().size(); j++)
		{
			for (size_t k = 0; k < supermercado.produtos.size(); k++)
			{
				if (supermercado.transacoes[i].getProdutos()[j] == supermercado.produtos[k].getNome())
					totalGhosts = totalGhosts + supermercado.produtos[k].getCusto();
			}     //vai a cada uma das transacoes e soma o preco de cada produto dessa transacao 
		}			//obtendo o total movimentos de que ha registo no supermercado
	}

	out << TAB << "Volume total em transacoes: " << totalGhosts << endl;
	out << TAB << "Media de gasto por transacao: " << totalGhosts / supermercado.transacoes.size() << endl;

	
	out << TAB << "Numero de produtos diferentes em stock: " << supermercado.produtos.size() << endl;

	double totalProducts = 0.0;
	for (size_t i = 0; i < supermercado.transacoes.size(); i++)
	{
		totalProducts = totalProducts + supermercado.transacoes[i].getProdutos().size();
	}
	out << TAB << "Numero de produtos comprados: " << totalProducts << endl;
	out << TAB << "Media de produtos comprados por transacao: " << totalProducts / supermercado.transacoes.size() << endl;

	unsigned int cheap = 0, expensive;
	double max = 0.0;
	for (size_t i = 0; i < supermercado.produtos.size(); i++)
	{
		if (supermercado.produtos[i].getCusto() > max)
		{
			expensive = i;
			max = supermercado.produtos[i].getCusto();
		}
	}
	out << TAB << "Produto mais caro:\n" << TAB_BIG << supermercado.produtos[expensive] << endl;

	double min = supermercado.produtos[0].getCusto();
	for (size_t i = 1; i < supermercado.produtos.size(); i++)
	{
		if (supermercado.produtos[i].getCusto() < min)
		{
			cheap = i;
			min = supermercado.produtos[i].getCusto();
		}
	}

	out << TAB << "Produto mais barato:\n" << TAB_BIG << supermercado.produtos[cheap] << endl;

	double costProd = 0.0;
	for (size_t i = 0; i < supermercado.produtos.size(); i++)
	{
		costProd = costProd + supermercado.produtos[i].getCusto();
	}

	out << TAB << "Media de preco dos produtos: " << costProd / supermercado.produtos.size() << endl << endl;

	return out;
}