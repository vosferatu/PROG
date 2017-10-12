#include "Produto.h"


Produto::Produto(string & in)
{ // nome ; custo
	string date, prod;
	istringstream linha;
	linha.str(in);

	getline(linha, prod, ';');
	prod.pop_back();
	nome = prod;

	linha >> custo;
}

string Produto::getNome() const {
  return nome;
}

double Produto::getCusto() const {
  return custo;
}

ostream& operator<<(ostream& out, const Produto & prod)    //só se mostra produtos, nao se guarda
{
	out << prod.nome << " ; " << prod.custo;
	return out; //arranjar com setw
}


/*bool operator<(const Produto &prod1, const Produto &prod2){
  // A IMPLEMENTAR
}*/