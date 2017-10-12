#include "Vende++.h"

/*************************
* Publicidade
**************************/
void VendeMaisMais::Ad()
{
	unsigned short int opcao;
	clearScreen();
	cout << TAB << "\nQual a publicidade que deseja?" << endl;
	cout << endl << TAB_BIG << "1 - Publicidade para um cliente." << endl;
	cout << TAB_BIG << "2 - Publicidade Bottom10." << endl;
	cout << TAB_BIG << "0 - Menu Principal." << endl;
	cout << TAB_BIG << "Introduza a sua opcao: ";
	opcao = leUnsignedShortInt(0, 2);

	switch (opcao)
	{
	case 0:
		return;
		break;
	case 1:

		/////////////////////////obter o indice do cliente alvo
		unsigned int alvo_pos, option;

		cout << endl << TAB << "Defina o cliente alvo." << endl;
		cout << endl << TAB << "1 - Pesquisa por nome." << endl;
		cout << TAB << "2 - Pesquisa por ID." << endl;
		cout << "Introduza a sua opcao: ";
		option = leUnsignedShortInt(1, 2);

		switch (option)
		{
		case 1:
			alvo_pos = searchByName();
			cout << endl << TAB_BIG << "O cliente procurado foi encontrado:\n";
			cout << TAB << clientes[alvo_pos] << endl << endl;
			clientAd(alvo_pos);
			break;
		case 2:
			alvo_pos = searchByClienteID();
			cout << endl << TAB << "O cliente procurado foi encontrado:\n";
			cout << endl << TAB_BIG << clientes[alvo_pos] << endl << endl;
			clientAd(alvo_pos);
			break;
		}
		//////////////////////////////////////////////////////////////////////
		break;
	case 2:
		if (clientes.size() > 10)  //tem de ser maior que 10 obrigatoriamente
			bottom10Ad();			//mas precisamos de pelo menos mais 1 cliente para os clientes semelhantes
		else						//o que mesmo assim, nao seria aceitavel
		{
			cout << TAB << "Tem de existir pelo menos 11 clientes. No momento existem " << clientes.size() << " clientes." << endl;
			cout << TAB << "Utilize no menu principal: Gestao de clientes -> Criar cliente." << endl;
			cout << TAB << "Tera de faze-lo pelo menos " << 11 - clientes.size() << " vez(es)." << endl << endl;
		}
		break;
	}
}


bool VendeMaisMais::searchtruth(int cli, int prod, vector<Transacao>& tra, vector<Cliente>& clientes, vector<Produto>& produtos)
{ //preenches as linhas dos clientes "normais"
	bool flag = false;; //cli -> indice do cliente no vetor de clientes || prod -> indice de prod no vetor de produtos

	for (size_t i = 0; i < tra.size(); i++) //percorre o vetor de transacoes
	{
		if (clientes[cli].getId() == tra[i].getIdCliente())  //verifica se a transacao é do cliente em questao
		{
			for (size_t j = 0; j < tra[i].getProdutos().size(); j++) //se é, percorre os produtos dessa transacao
			{
				if (tra[i].getProdutos()[j] == produtos[prod].getNome()) //se encontrar o produto passado à função
				{													//nessa transacao, retorna verdade
					flag = true;									//colocando o valor na matriz
					break;  //faz break porque ja sabe que o cliente comprou o produto pelo menos 1 vez
				}
			}
		}
	} //flag foi inicializada a falso no caso de se encontrar, muda o valor. se nao encontrar, continua a falso
	return flag;
}

bool VendeMaisMais::searchtruthghosts(int fanta, int prod, vector<unsigned int>& ghost, vector<Transacao>& tra, vector<Produto>& produtos) 
{  //preenche as linhas dos fantasmas
	bool flag = false; //fanta-> indice do fantasma no vetor de fantasmas
						//prod -> indice do produto que estamos à procura
	for (size_t i = 0; i < tra.size(); i++) //percorre o vetor de transacoes
	{
		if (ghost[fanta] == tra[i].getIdCliente())  //verifica se o id da transacao é igual ao do fantasma
		{
			for (size_t j = 0; j < tra[j].getProdutos().size(); j++) //se é, percorre os produtos da transacao
			{
				if (tra[i].getProdutos()[j] == produtos[prod].getNome()) //verifica se o nome do produto passado à função
				{														//se encontra no vetor de produtos da transação
					flag = true;  //se estiver coloca a flag a true
					break;  //faz break porque já sabe que o cliente comprou o produto pelo menos 1 vez
				}
			}
		}
	}  //flag foi inicializada a falso para: encontrar, muda o valor. se nao encontrar, continua a falso
	return true;
}
//acrescentar uma função que testa condições iniciais da publicidade
void VendeMaisMais::clientAd(unsigned int alvo_pos)
{
	unsigned int countprod = produtos.size(), countcli = clientes.size(), countghost = 0;
	vector<unsigned int> ghosts;      //vetor de id's de clientes que estao nas transacoes e nao nos clientes(fantasmas)

	for (size_t i = 0; i < transacoes.size(); i++)
	{
		if (!checkID(transacoes[i].getIdCliente()))
			ghosts.push_back(transacoes[i].getIdCliente());                //preenche "fantasmas"
	}

	sort(ghosts.begin(), ghosts.end());    //ordena os fantasmas
	ghosts.erase(unique(ghosts.begin(), ghosts.end()), ghosts.end());//elimina fantasmas possivelmente repetidos

	for (size_t i = 0; i < ghosts.size(); i++)
	{
		for (size_t j = 0; j < clientes.size(); j++)
		{
			if (checkID(ghosts[i]))          //verifica novamente
				ghosts.erase(ghosts.begin() + i); //se estiver nos clientes, remove-o
		}
	}

	countghost = ghosts.size();                           //numero de fantasmas
	countcli = countcli + countghost;                      // "clientes" totais

	vector<vector<bool>> matrix(countcli, vector<bool>(countprod, false)); //matriz de booleanos 
	 //countcli-> todos os clientes       //countprod->numero de produtos
	//há uma correspondencia entre a matriz e os indices dos vetores de clientes e de produtos
	for (size_t x = 0; x < matrix.size(); x++) //percorre os clientes
	{
		for (size_t y = 0; y < matrix[x].size(); y++) //percorre os produtos    //clientes -> x
		{																		//produtos -> y
			if (x < clientes.size()) //se o indice é menor que o tamanho de vetores de clientes
				matrix[x][y] = searchtruth(x, y, transacoes, clientes, produtos); //função para preencher
			else
			{
				if (ghosts.size() > 0)  //se existirem fantasmas
					matrix[x][y] = searchtruthghosts(x - clientes.size(), y, ghosts, transacoes, produtos);
			}														//função para preencher fantasmas
		}
	}
	

	vector<int> produtosNao;  //guarda os indices (no vetor de produtos) dos produtos nao comprados pelo alvo

	for (size_t y = 0; y < matrix[alvo_pos].size(); y++) //percorre os produtos na linha do cliente alvo
	{
		if (!matrix[alvo_pos][y])      //se nao o comprou
			produtosNao.push_back(y);     //guarda o indice no vetor   
	}

	unsigned int counterProdClient = produtos.size()-produtosNao.size(); //numero de produtos comprados pelo cliente alvo

	if (counterProdClient == produtos.size())
	{
		cout << TAB << clientes[alvo_pos].getNome() << ", com o ID " << clientes[alvo_pos].getId()
			<< " ja comprou todos os produtos do supermercado." << endl << endl;
		return;
	}

	unsigned int minimo = floor(0.75 * counterProdClient);   //clientes semelhantes tem 75% de similariedade (alteravel)
												//achamos que é o minimo aceitável
	vector<unsigned int> correlator;  //vetor que guarda os id's de clientes com compras similares ao alvo

	for (size_t x = 0; x < matrix.size(); x++) //percorre os clientes da matriz
	{
		unsigned int conta = 0;  //guarda o numero de produtos comprados pelo cliente que foram comprados pelo alvo

		if (x != alvo_pos) //não interessa percorrer o próprio alvo
		{
			for (size_t y = 0; y < matrix[x].size(); y++)  //percorre os produtos da matriz
			{
				if (matrix[x][y] == matrix[alvo_pos][y] && matrix[alvo_pos][y] == true)
					conta++; //verifica se o cliente e o alvo correspondem neste produto
			}				//e verifica se ambos compraram o produto e adiciona o contador
			
			if (conta > minimo)  //se o numero de produtos for maior que o minimo (50% dos produtos comprados pelo alvo)
				correlator.push_back(x);  //coloca-se no vetor correlator o indice do cliente na matriz que é o mesmo
		}								 // que no vetor de clientes	
	}								 					

	vector<unsigned int> tracorre; //vetor que guarda os id's de clientes que compraram pelo menos 1 produto
							//que o alvo nao comprou
	for (size_t x = 0; x < matrix.size(); x++) //percorre os clientes na matriz
	{
		int counter = 0;     //contador de produtos nao comprados por um cliente e comprados pelo alvo

		if (x != alvo_pos) //nao interessa comparar com o proprio alvo
		{
			for (size_t y = 0; y < matrix[x].size(); y++)  //percorre os produtos
			{                                               
				if (matrix[x][y] == true && matrix[alvo_pos][y] == false) //se o produto foi comprado pelo cliente 
					counter++;											//e não foi comprado pelo alvo
			}															//incrementa o contador
			
			if (counter > 0)   //se o contador desse cliente é maior do que 0(pelo menos 1 produto)
				tracorre.push_back(x);  //adiciona ao vetor
		}
	}


	vector<unsigned int> finalcorre; //"correlador final" que faz a interseção dos 2 vetores anteriores
		//no fim, fica com  o os ids dos clientes da matriz que compraram a maior parte ou mesmo todos produtos que o alvo
		//e compraram pelo menos um produto que o alvo não comprou.
	for (size_t x = 0; x < correlator.size(); x++)  //percorrer o primeiro vetor
	{
			for (size_t y = 0; y < tracorre.size(); y++)  //percorrer o segundo vetor
			{												
				if (correlator[x] == tracorre[y])        //verificar se sao iguais
					finalcorre.push_back(correlator[x]); //se forem adicionar ao vetor
			}
	}

	vector<unsigned int> counters(produtos.size(), 0); //contadores para os produtos

	for (size_t x = 0; x < finalcorre.size(); x++) //percorre os clientes semelhantes
	{
		for (size_t y = 0; y < produtosNao.size(); y++)      //percorre os produtos nao comprados pelo alvo
		{          //nao podemos publicitar um produto que o alvo ja comprou. o vetor produtosNao contem os indices 
			if (matrix[finalcorre[x]][produtosNao[y]]) //se esse produto foi comprado por esse cliente
				counters[produtosNao[y]]++;  //incrementar contador desse produto
		}
	}

	int prodFrequente = - 1;

	for (size_t i = 0; i < counters.size(); i++)
	{
		unsigned int max = 0;
		if (counters[i] > max)
		{									//encontrar o indice no vetor de produtos do produto mais frequente
			max = counters[i];
			prodFrequente = i;
		}
	}

	string produtofixe;

	if (prodFrequente > 0)
		produtofixe = produtos[prodFrequente].getNome(); //guarda o produto a publicitar
	else
	{
		if (produtosNao.size() == produtos.size()) //se o alvo nao comprou nenhum produto 
		{
			cout << TAB << clientes[alvo_pos].getNome() << ", com o ID " << clientes[alvo_pos].getId() <<
				" nao efetuou nenhuma compra." << endl;
			return;
		}
		else

		{
			cout << "Nao existem produtos que os clientes semelhantes tenham comprado e que " << clientes[alvo_pos].getNome() << ", com o ID "
				<< clientes[alvo_pos].getId()
				<< " nao tenha comprado." << endl;
			return;
		}
	}

	if (correlator.size() == 0)  //nao existem clientes com 75% de semelhança (publicitar o que nao comprou)
		cout << TAB << "Nao existem clientes semelhantes a " << clientes[alvo_pos].getNome() << ", com o ID "
		<< clientes[alvo_pos].getId() << endl;
	else if (tracorre.size() == 0) //se ninguem do supermercado comprou o produto
		cout << TAB << "Ninguem comprou os produtos que " << clientes[alvo_pos].getNome() << ", com o ID " << clientes[alvo_pos].getId()
		<< " nao comprou." << endl;
	else if (finalcorre.size() == 0)
	{
		cout << TAB << "Nao existem clientes semelhantes que tenham comprado pelo menos um produto que " << clientes[alvo_pos].getNome() 
			<< ", com o ID " << clientes[alvo_pos].getId()
			<< " nao comprou." << endl;
	}
	else
	{
		cout << TAB << "O produto a publicitar a " << clientes[alvo_pos].getNome() << ", com o ID " << clientes[alvo_pos].getId()
			<< " deve ser " << produtofixe << "!" << endl << endl;
		cout << TAB << "INFORMACAO DO PRODUTO: " << endl << endl;
		cout << TAB_BIG << produtos[prodFrequente] << "$" << endl;
	}
}


void VendeMaisMais::bottom10Ad()
{
	//como os clientes estao por ordem crescente de volume de compras
	//basta selecionar os primeiros 10
	vector<unsigned int> bottom10Clients;
	for (size_t i = 0; i < 10; i++)
	{
		bottom10Clients.push_back(i);
	}

	vector<unsigned int> bottom10Produtos(produtos.size());
	//este vetor vai guardar contadores para cada produto
	for (size_t i = 0; i < bottom10Clients.size(); i++)   //percorrer os bottom10
	{
		for (size_t j = 0; j < produtos.size(); j++)  //percorrer os produtos
		{
			if (searchtruth(i, j, transacoes, clientes, produtos)) //verifica que produtos o bottom10 i comprou 
			{													//se comprou o produto j, incrementa
				bottom10Produtos[j]++;							//se nao, mantem o valor
			}
		}
	}
	//os produtos que ficam a 10, são aqueles comprados por todos os bottom10, sendo os produtos comuns
	//o indice deles, corresponde ao seu indice no vetor de produtos
	//os produtos que ficam a 0, são aqueles nao comprados por nenhum bottom 10
	//os restantes sao os comprados por alguns bottom10

	unsigned int bottom10comuns = 0; //guarda o numero de produtos comuns

	for (size_t i = 0; i < bottom10Produtos.size(); i++)   //percorrer os bottom10
	{
		if (bottom10Produtos[i] == 10) //conta o numero de produtos comuns aos bottom10
			bottom10comuns++;
	}

	vector<unsigned int> correlatorTodos;
	//guarda os indices dos clientes que compraram todos os produtos comuns aos bottom10
	for (size_t i = 10; i < clientes.size(); i++) //como os bottom10 sao os 10 primeiros (o vetor esta ordenado pelo
	{											 //volume de compras. a iteração começa no 10 (0-9 bottom10)
		int conta = 0;  //conta os produtos comprados comuns aos bottom10
		for (size_t j = 0; j < bottom10Produtos.size(); j++) //percorre os produtos
		{
			if (bottom10Produtos[j] == 10)  //se o produto é um produto comum aos bottom10, analisa
			{
				if (searchtruth(i, j, transacoes, clientes, produtos)) //se o cliente comprou
					conta++;			//se o cliente i comprou um produto j comum aos bottom10, conta
			}
		}
		if (conta == bottom10comuns)  //se comprou todos os produtos comuns aos bottom10
			correlatorTodos.push_back(i); //adiciona o indice no vetor de clientes desse cliente ao vetor
	}

	vector <unsigned int> correlatorUmNao;
	//guarda os indices dos clientes que compraram um produto nao comum
	for (size_t i = 10; i < clientes.size(); i++) //como os bottom10 sao os 10 primeiros (o vetor esta ordenado pelo
	{											 //volume de compras. a iteração começa no 10 (0-9 bottom10)
		int conta = 0;  //conta os produtos comprados não comuns aos bottom10
		for (size_t j = 0; j < bottom10Produtos.size(); j++) //percorre os produtos
		{
			if (bottom10Produtos[j] != 10)  //se o produto não é um produto comum aos bottom10, analisa
			{
				if (searchtruth(i, j, transacoes, clientes, produtos)) //se o cliente comprou
					conta++;			//se o cliente i comprou um produto j não comum aos bottom10, conta
			}
		}
		if (conta > 0)    //se comprou pelo menos um produto não comum aos bottom10
			correlatorUmNao.push_back(i); //adiciona o indice no vetor de clientes desse cliente ao vetor
	}

	vector<unsigned int> finalcorre; //"correlador final" que faz a interseção dos 2 vetores anteriores
	//no fim, fica com  o os ids dos clientes que compraram todos os produtos comuns aos bottom10
	//e compraram pelo menos um produto não comum aos bottom10
	for (size_t x = 0; x < correlatorTodos.size(); x++)  //percorrer o primeiro vetor
	{
		for (size_t y = 0; y < correlatorUmNao.size(); y++)  //percorrer o segundo vetor
		{
			if (correlatorTodos[x] == correlatorUmNao[y])        //verificar se sao iguais
				finalcorre.push_back(correlatorTodos[x]); //se forem adicionar ao vetor
		}
	}

	vector<unsigned int> histogram(produtos.size());
	//histograma para produtos comprados pelos clientes interessantes e que não foram comprados por todos os Bottom10
	for (size_t i = 0; i < bottom10Produtos.size(); i++) //percorre o histograma para bottom10
	{
		if (bottom10Produtos[i] != 10) //se nem todos (ou até nenhum) os bottom10 compraram o produto, analisa
		{
			for (size_t j = 0; j < finalcorre.size(); j++) //percorre os id dos clientes semelhantes
			{
				if (searchtruth(finalcorre[j], bottom10Produtos[i], transacoes, clientes, produtos)) //se o cliente semelhante
					histogram[i]++;												//comprou o produto
			}																	//incrementa o histograma para esse produto
		}
	}

	map<unsigned int, unsigned int> histograma;

	for (size_t i = 0; i < histogram.size(); i++)
	{
		histograma.insert(pair<unsigned int, unsigned int>(histogram[i], i));
	}

	int produtoFor10 = -1;  //funciona também como uma flag

	map <unsigned int, unsigned int> ::reverse_iterator i;

	for (i = histograma.rend(); i != histograma.rbegin(); i++)//percorre o histograma do maior para o menor
	{//histograma percorre do maior para o menor logo nao precisamos de nos preocupar com isso
		if (bottom10Produtos[i->second] == 0) //second tem o indice no vetor de produtos
		{				//verificamos se esse produto do histograma é também um produto nao comprado por nenhum bottom10			
			produtoFor10 = i->second; //se for, guardamos o seu indice
			break;    //e saltamos fora do ciclo (para nao ficar com um indice de um possivel produto menos frequente
		}//e tambem nao comprado pelos bottom10)
	}
	
	if (produtoFor10 > 0)   //se há um produto nas condições pedidas, publicita-o
	{
		cout << endl << TAB << "Produto a publicitar aos bottom10:" << endl << endl;
		cout << TAB_BIG << produtos[produtoFor10].getNome() << endl;
		cout << endl << TAB << "INFORMACAO DO PRODUTO:" << endl;
		cout << endl << TAB_BIG << produtos[produtoFor10] << "$" <<  endl;
		return;
	}
	else
	{
		vector<unsigned int> produtosSemelhantes(produtos.size());
		//histograma de contadores para produtos dos clientes semelhantes
		for (size_t i = 0; i < produtosSemelhantes.size(); i++)  //percorre os produtos
		{
			for (size_t j = 0; j < finalcorre.size(); j++)  //percorre os clientes semelhantes
			{		//se o cliente semelhante comprou o produto, incrementa o produto no seu indice
				if (searchtruth(finalcorre[j], produtosSemelhantes[i], transacoes, clientes, produtos))
					produtosSemelhantes[i]++;
			}
		}

		map<unsigned int, unsigned int> histogramaSem;

		for (size_t i = 0; i < produtosSemelhantes.size(); i++)
		{
			histogramaSem.insert(pair<unsigned int, unsigned int>(produtosSemelhantes[i], i));
		}

		map <unsigned int, unsigned int> ::reverse_iterator j;


		map<unsigned int, unsigned int> histogramaBot;

		for (size_t i = 0; i < bottom10Produtos.size(); i++)
		{
			histogramaBot.insert(pair<unsigned int, unsigned int>(bottom10Produtos[i], i));
		}

		map <unsigned int, unsigned int> ::const_iterator k;


		int produtoAlternativo = -1;

		for (j = histogramaSem.rend(); j != histogramaSem.rbegin(); j++)//percorre o histograma de semelhantes do maior para o menor
		{//histograma percorre do maior para o menor logo nao precisamos de nos preocupar com ter o produto mais frequente
			for (k = histogramaBot.begin(); k != histogramaBot.end(); k++)  //percorre o histograma de contadores de produtos bottom10
			{												//o valor j-> first é o mais frequente (semelhantes)		
				if (k->first != 0 && k->second == j->second)//se o valor é menos frequente nos bottom10 (sem ser 0)
				{									//e apontam para o mesmo produto
					produtoAlternativo = k->second; //este produto é o que queremos publicitar e tiramos o seu indice
					break;						 //saindo entao do ciclo
				}
			}

			if (produtoAlternativo > 0) //se ja encontramos, sair do ciclo
				break;
		}

		cout << endl << TAB << "Produto a publicitar aos bottom10:" << endl << endl;
		cout << TAB_BIG << produtos[produtoAlternativo].getNome() << endl;
		cout << endl << TAB << "INFORMACAO DO PRODUTO:" << endl;
		cout << endl << TAB_BIG << produtos[produtoAlternativo] << "$" << endl;
	}
}