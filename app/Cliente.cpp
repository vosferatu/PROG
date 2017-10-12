#include "Cliente.h"


Cliente::Cliente(string& line)
{
	/*//string name, data;
	string data;
	in >> id;
	in.seekg(4, ios_base::cur);

	//getline(in, name, ';');
	//name.pop_back();
	//nome = name;

	getline(in, nome, ';');
	nome.pop_back();

	in.seekg(2, ios_base::cur);
	getline(in, data, ';');
	data.pop_back();
	cartaoCliente = data;

	in.seekg(3, ios_base::cur);
	in >> volCompras;*/
	string data;
	istringstream linha;
	linha.str(line);

	linha >> id;
	linha.seekg(3, ios_base::cur);
	getline(linha, nome, ';');
	nome.pop_back();

	linha.seekg(1, ios_base::cur);
	getline(linha, data, ';');
	data.pop_back();
	cartaoCliente = data;

	linha >> volCompras;
}

Cliente::Cliente(unsigned int ide, string name, Data cartao, float gasto)
{
	id = ide;
	nome = name;
	cartaoCliente = cartao;
	volCompras = gasto;
}

string Cliente::getNome() const
{
  return nome;
}

unsigned int Cliente::getId() const
{
  return id;
}

double Cliente::getVolCompras() const
{
  return volCompras;
}

Data Cliente::getcartaoCliente() const
{
	return cartaoCliente;
}

void Cliente::setVolCompras(double value)
{
	volCompras = value;
}

ofstream& operator<<(ofstream& outer, const Cliente & cli) //ofstream para usar com ficheiro
{
	outer << cli.id << " ; " << cli.nome << " ; " << cli.cartaoCliente << " ; " << cli.volCompras;
	return outer;
}

ostream& operator<<(ostream& out, const Cliente & client) //ostream para usar com cout
{
	out << client.id << " ; " << client.nome << " ; " << client.cartaoCliente << " ; " << client.volCompras;
	return out;          //faltam os setw
}

bool sortByVol(const Cliente &cliente1, const Cliente &cliente2)
{
	return (cliente1.volCompras < cliente2.volCompras);
}
