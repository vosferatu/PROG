#include "Data.h"
#include <time.h>


Data::Data(string dataStr)
{ // data na forma DD/MM/AAA //input "curr" to get the current date

	if (dataStr != "curr")
	{
		if (dataStr[0] == ' ')
			dataStr = dataStr.substr(1, dataStr.size());
		string year, month, day;
		istringstream primeira;

		primeira.str(dataStr);
		getline(primeira, day, '/');
		getline(primeira, month, '/');
		getline(primeira, year);

		ano = stoi(year);
		mes = stoi(month);
		dia = stoi(day);
		date = dataStr;
	}
	else
	{
		char dat[9];
		_strdate_s(dat);
		string data = dat;
		string da = data.substr(3, 2);
		string mont = data.substr(0, 2);
		string yea = "20" + data.substr(6, 2);
		data = da + '/' + mont + '/' + yea;
		date = data;

		ano = stoi(yea);
		mes = stoi(mont);
		dia = stoi(da);
	}
}

Data::Data(int day, int month, int year)
{
	dia = day;
	mes = month;
	ano = year;
	if (month < 10)
		date = to_string(day) + "/0" + to_string(month) + '/' + to_string(year);
	else
		date = to_string(day) + "/" + to_string(month) + '/' + to_string(year);
}


string Data::getData() const
{
	return date;
}

int Data::getDia() const
{
  return dia;
}

int Data::getMes() const
{
  return mes;
}

int Data::getAno() const
{
  return ano;
}


void Data::setDia(int day)
{
	dia = day;
}

void Data::setMes(int month)
{
	mes = month;
}

void Data::setAno(int year)
{
	ano = year;
}

void Data::setDate(string dat)
{
	if (dat != "curr")
	{
		if (dat[0] == ' ')
			dat = dat.substr(1, dat.size());

		string year, month, day;
		istringstream primeira;

		primeira.str(dat);
		getline(primeira, day, '/');
		getline(primeira, month, '/');
		getline(primeira, year);

		ano = stoi(year);
		mes = stoi(month);
		dia = stoi(day);
		date = dat;
	}
	else
	{
		char datt[9];
		_strdate_s(datt);
		string data = datt;
		string da = data.substr(3, 2);
		string mont = data.substr(0, 2);
		string yea = "20" + data.substr(6, 2);
		data = da + '/' + mont + '/' + yea;
		date = data;

		ano = stoi(yea);
		mes = stoi(mont);
		dia = stoi(da);
	}
}

void Data::setDate(unsigned int d, unsigned int m, unsigned int y)
{
	dia = d;
	mes = m;
	ano = y;
	if (m < 10)
		date = to_string(d) + "/0" + to_string(m) + '/' + to_string(y);
	else
		date = to_string(d) + "/" + to_string(m) + '/' + to_string(y);
}


bool truedate(const Data & data)
{
	if (data.mes == 1 || data.mes == 3 || data.mes == 5 || data.mes == 7 || data.mes == 8 || data.mes == 10 || data.mes == 12)
	{
		if (data.dia >= 1 && data.dia <= 31)
			return true;
		else return false;
	}
	else
	{
		if (data.mes == 4 || data.mes == 6 || data.mes == 9 || data.mes == 11)
		{
			if (data.dia >= 1 && data.dia <= 30)
				return true;
			else return false;
		}
		else
		{
			if (data.mes == 2)
			{
				if ((data.ano % 4 == 0 && data.ano % 100 != 0) || (data.ano % 4 == 0 && data.ano % 100 == 0 && data.ano % 400 == 0))
				{
					if (data.dia >= 1 && data.dia <= 29)
						return true;
					else return false;
				}
				else 
				{
					if (data.dia >= 1 && data.dia <= 28)
						return true;
					else return false;
				};
			}
			else
				return false;
		}
	}
}

bool operator>=(const Data &date1, const Data &date2)
{
	if (date1.ano > date2.ano)
		return true;
	else if (date2.ano > date1.ano)
		return false;
	else if (date1.mes > date2.mes)
		return true;
	else if (date2.mes > date1.mes)
		return false;
	else if (date1.dia > date2.dia)
		return true;
	else if (date2.dia > date1.dia)
		return false;
	else return true;
}

bool operator<=(const Data &date1, const Data &date2)
{
	if (date1.ano < date2.ano)
		return true;
	else if (date2.ano < date1.ano)
		return false;
	else if (date1.mes < date2.mes)
		return true;
	else if (date2.mes < date1.mes)
		return false;
	else if (date1.dia < date2.dia)
		return true;
	else if (date2.dia < date1.dia)
		return false;
	else return true;
}

bool operator==(const Data &date1, const Data &date2)
{
	return (date1.dia == date2.dia && date1.mes == date2.mes && date1.ano == date2.ano);
}

ostream& operator<<(ostream& out, const Data & data)
{
	out << data.date;
	return out;
}