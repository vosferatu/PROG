#include "Transacao.h"


Transacao::Transacao(string & in)
{ // le uma transacao na forma de  idcliente ; data ; lista produtos
	/*string date, prod;

	in >> idCliente;
	in.seekg(4, ios_base::cur);

	getline(in, date, ';');
	date = date.substr(0, date.size() - 1);
	string lista;
	getline(in, lista);*/
	string date, prod;
	istringstream linha;
	in = in + ',';
	linha.str(in);

	linha >> idCliente;

	linha.seekg(3, ios_base::cur);

	getline(linha, date, ';');
	date.pop_back();
	data = date;

	//linha.seekg(3, ios_base::cur);

	while (getline(linha, prod, ','))
	{
		prod = prod.substr(1, prod.size());

		produtos.push_back(prod);
	}
}

Transacao::Transacao(unsigned int ide, Data date, vector<string>& products)
{
	idCliente= ide;
	data = date;
	produtos = products;
}


unsigned int Transacao::getIdCliente() const
{
	return idCliente;
}

Data Transacao::getDateClient() const
{
	return data;
}

const vector<string>& Transacao::getProdutos() const //para funcionar o valor de retorno tem de ser
{                                                    //const 
	return produtos;
}


bool sortByDate(const Transacao &trans1, const Transacao &trans2)
{
	return !(trans1.data >= trans2.data);
	//fizemos o overload do operador >= para as datas
	//esta função serve para ordenar as transações através das datas, usando o algoritmo sort
	//como o sort só aceita o operador <
	//fizemos :
	//  !>= que é o mesmo que <
}

ofstream& operator<<(ofstream& outer, const Transacao & transfer)
{
	outer << transfer.idCliente << " ; " << transfer.data << " ; ";  //fileTransacoes << Cliente;

	for (size_t i = 0; i < transfer.produtos.size(); i++)
	{
		if (i == transfer.produtos.size() - 1)
			outer << transfer.produtos[i];
		else outer << transfer.produtos[i] << ", ";
	}

	return outer;
}

ostream& operator<<(ostream& out, const Transacao & trans) //falta estruturar com setw
{
	out << trans.idCliente << " ; " << trans.data << " ; ";

	for (size_t i = 0; i < trans.produtos.size(); i++)
	{
		if (i == trans.produtos.size() - 1)
			out << trans.produtos[i];
		else out << trans.produtos[i] << ", ";
	}
	
	return out;
}