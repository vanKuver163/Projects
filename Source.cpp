#include "Header.h"
Card::Card(double bal, const string& num, const string& b)
{
	balance = bal;
	number = num;
	bank = b;
}

Card::~Card() {};
void Card::Deposit(double money)
{
	if (money < 0)cout << "Отрицательную сумму внести нельзя!" << endl;
	else balance += money;
}
void Card::Withdraw(double money)
{
	if (money < 0)cout << "Отрицательную сумму снять нельзя!" << endl;
	else if (money <= balance) balance -= money;
	else cout << "Сумма снятия превышает текущий баланс" << endl;
}
double Card::GetBalance()
{
	return balance;
}
string Card::GetNumber()
{
	return number;
}
Card& Card::operator=(const Card c)
{
	balance = c.balance;
	number = c.number;
	bank = c.bank;
	return *this;
}
ostream& operator << (ostream& os, Card const& c)
{
	cout << c.bank << " - " << "номер карты: " << c.number << ", баланс: " << c. balance << " руб." << endl;
	return os;
}
ofstream& operator <<(ofstream& of, Card& c)
{
	of << c.balance << " ";
	of << c.number << " ";
	of << c.bank;
	return of;
}
ifstream& operator >>(ifstream& ifs, Card& c)
{
	ifs >> c.balance;
	ifs >> c.number;
	ifs >> c.bank;
	return ifs;
}
istream& operator >>(istream& ist, Card& c)
{
	cout << "Введите номер карты: ";
	ist >> c.number;
	cout << "Введите банк карты: ";
	ist >> c.bank;
	cout << "Введите баланс карты: ";
	ist >> c.balance;
	ist.get();	
	return ist;
}

Transaction::Transaction(double s, int d, int m, const string& t, const string& num)
{
	sum = s;
	day = d;
	mon = m;
	type = t;
	number = num;	
}

Transaction::~Transaction() {}

Transaction& Transaction::operator=(const Transaction Tr)
{
	day = Tr.day;
	mon = Tr.mon;
	sum = Tr.sum;
	type = Tr.type;
	number = Tr.number;	
	return *this;
}

string Transaction::Number()
{
	return number;
}

double Transaction::getSum()
{
	return sum;
}

ostream& operator << (ostream& os, const Transaction& Tr)
{
	cout << Tr.day << "." << Tr.mon << " номер карты: " << Tr.number << ", " << Tr.type <<" - " << Tr.sum << " руб." << endl;
	return os;
}

ofstream& operator <<(ofstream& of, Transaction& Tr)
{
	of << Tr.day << " ";
	of << Tr.mon << " ";
	of << Tr.number << " ";
	of << Tr.type << " ";
	of << Tr.sum;
	return of;
}

ifstream& operator >>(ifstream& ifs, Transaction& Tr)
{
	ifs >> Tr.day;
	ifs >> Tr.mon;
	ifs >> Tr.number;
	ifs >> Tr.type;
	ifs >> Tr.sum;
	return ifs;
}

istream& operator >>(istream& ist, Transaction& Tr)
{
	cout << "Введите месяц: ";		
	Tr.mon = Tr.checkMon();	
	cout << "Введите день: ";
	Tr.day = Tr.checkDay(Tr.mon);		
	cout << "Введите тип операции (1 - снять/ 2 - внести): ";
	int val = Tr.checkType();
	if (val == 1) Tr.type = "снять";
	else if (val == 2) Tr.type = "внести";
	cout << "Введите номер карты: ";
	ist >> Tr.number;	
	cout << "Введите сумму: ";	
	ist >> Tr.sum;
	cin.get();
	system("cls");
	return ist;
}

int Transaction::getMon()
{
	return mon;
}
int Transaction::getDay()
{
	return day;
}

int  Transaction::checkMon()
{
	int value = -1;
	char* Digits;
	while (true)
	{
		newLine(Digits);
		if (atoi(Digits) > 0 && atoi(Digits) <= 12) value = atoi(Digits);
		else cout << "Вы вели не верное значение, попробйте снова: ";
		delete[]Digits;
		if (value >= 0) break;
	}
	return value;
}

int Transaction::checkDay(int m)
{
	int value = -1;
	char* Digits;
	int days= 0;
	if (m % 2 != 0 || m == 8) days = 31;
	else if (m % 2 == 0 && m != 8 && m != 2) days = 30;
	else if (m == 2) days = 28;
	while (true)
	{
		newLine(Digits);
		if (atoi(Digits) > 0 && atoi(Digits) <= days) value = atoi(Digits);
		else cout << "Вы вели не верное значение, попробйте снова: ";
		delete[]Digits;
		if (value >= 0) break;
	}
	return value;
}

int Transaction::checkType()
{
	int value = -1;
	char* Digits;
	while (true)
	{
		newLine(Digits);
		if (atoi(Digits) == 1 || atoi(Digits) == 2) value = atoi(Digits);
		else cout << "Вы вели не верное значение, попробйте снова: ";
		delete[]Digits;
		if (value >= 0) break;
	}
	return value;
}

string  Transaction::getType()
{
	return type;
}


Wallet::Wallet()
{
	char text[255];
	file.open("Cards.txt");
	if (!file.is_open()) cout << "Ошибка открытия файла!\n";
	while (file.getline(text, 255))
	{
		size++;
	}
	file.close();		
	if (size == 0) arr = nullptr;
	else
	{
		arr = new Card[size];
		file.open("Cards.txt");
		if (!file.is_open()) cout << "Ошибка открытия файла!\n";		
		while (!file.eof())
		{
			for (int i = 0; i < size; i++)
			{
				file >> arr[i];						
			}
		}
		file.close();
	}	
}

Wallet::~Wallet()
{
	delete[] arr;
}

void Wallet::ShowWallet()
{
	system("cls");
	for (int i = 0; i < size; i++)
	{
		cout << arr[i];
	}
}

void Wallet::AddCard()
{
	system("cls");
	if (size == 0)
	{
		arr = new Card[size + 1];
		cin >> arr[0];
		size++;
	}
	else
	{
		Card* tempArr = new Card[size + 1];
		for (int i = 0; i < size; i++)
		{
			tempArr[i] = arr[i];
		}
		delete[] arr;
		cin >> tempArr[size];
		size++;
		arr = new Card[size];
		for (int i = 0; i < size; i++)
		{
			arr[i] = tempArr[i];
		}
		delete[]tempArr;
		SaveCard();
	}
	
}

void Wallet::SaveCard()
{
	file1.open("Cards.txt");
	if (!file1.is_open()) cout << "Ошибка открытия файла!\n";
	for (int i = 0; i < size; i++)
	{
		if (i != size - 1) file1 << arr[i] << endl;
		else file1 << arr[i];
	}
	file1.close();
}

void Wallet::DelCard()
{	
	if (size == 0)arr = nullptr;	
	else
	{
		string tempNum;
		ShowWallet();
		while (true)
		{
			int count = 0;
			cout << "Ввведите номер карты для удаления: ";
			cin >> tempNum;
			cin.get();
			for (int i = 0; i < size; i++)
			{
				if (tempNum == arr[i].GetNumber()) count++;
			}
			if (count == 0)
			{
				cout << "Такой карты не существует, попробуйте снова.\n";
			}
			else break;
		}
		Card* tempArr = new Card[size - 1];
		for (int i = 0; i < size; i++)
		{
			if (tempNum != arr[i].GetNumber())
			tempArr[i] = arr[i];
		}
		delete[] arr;
		size--;
		arr = new Card[size];
		for (int i = 0; i < size; i++)
		{
			arr[i] = tempArr[i];
		}
		delete[]tempArr;
		system("cls");
		cout << "Карта удалена из базы!" << endl;
		SaveCard();
	}
}

void Wallet::BalanceAll()
{
	system("cls");
	double sum=0;
	for (int i = 0; i < size; i++)
	{
		sum += arr[i].GetBalance();
	}
	cout << "Общий баланс кошелька: " << sum << " руб.\n" << endl;
}

int Wallet::getSize()
{
	return size;
}

Card* Wallet::getCard()
{
	return arr;
}


Statistics::Statistics()
{
	char text[255];	
	file.open("Transactions.txt");
	if (!file.is_open()) cout << "Ошибка открытия файла!\n";
	while (file.getline(text, 255))
	{
		size++;
	}
	file.close();
	if (size == 0) arr = nullptr;
	else
	{
		arr = new Transaction[size];
		file.open("Transactions.txt");
		if (!file.is_open()) cout << "Ошибка открытия файла!\n";
		while (!file.eof())
		{
			for (int i = 0; i < size; i++)
			{
				file >> arr[i];
			}
		}
		file.close();
	}
}

void Statistics::DelTransaction()
{
	if (arr == nullptr)
	{
		cout << "arr==nullptr" << endl;
		return;
	}
	else
	{
		while (size != 0)
		{
			Transaction* tempArr = new Transaction[size - 1];
			for (int i = 0; i < size; i++)
			{
				if (i != (size - 1))
					tempArr[i] = arr[i];
			}			
			delete[] arr;
			size--;
			arr = new Transaction[size];
			for (int i = 0; i < size; i++)
			{
				arr[i] = tempArr[i];
			}
			delete[]tempArr;
		}
		arr = nullptr;
		system("cls");
		cout << "История транзакций очищена.\n";
	}
}

Statistics::~Statistics()
{
	delete[] arr;
}


void Statistics::ShowStatistics()
{
	system("cls");
	for (int i = 0; i < size; i++)
	{
		cout << arr[i];
	}
}

void Statistics::SaveTransaction()
{
	file1.open("Transactions.txt");
	if (!file1.is_open()) cout << "Ошибка открытия файла!\n";	
	for (int i = 0; i < size; i++)
	{
		if (i != size - 1) file1 << arr[i] << endl;
		else file1 << arr[i];
	}
	file1.close();
}

void Statistics::AddTransaction(int mon, int day, int c)
{

	if (size == 0)
	{
		arr = new Transaction[size + 1];
		cout << "\nДата должна быть не раньше: " << day << "-го";
		Months(mon);
		cin >> arr[0];
		size++;
	}
	else
	{
		Transaction* tempArr = new Transaction[size + 1];
		for (int i = 0; i < size; i++)
		{
			tempArr[i] = arr[i];
		}
		delete[] arr;
		cout << "\nДата должна быть не раньше: " << day << "-го";
		Months(mon);
		cin >> tempArr[size];
		size++;
		arr = new Transaction[size];
		for (int i = 0; i < size; i++)
		{
			arr[i] = tempArr[i];
		}
		delete[]tempArr;
	}


}


Transaction& Statistics::lastTr()
{	
	return arr[size - 1];	
}

int Statistics::lastD()
{
	if (arr == nullptr) return 1;
	return arr[size - 1].getDay();
}
int Statistics::lastM()
{
	if (arr == nullptr) return 1;
	return arr[size - 1].getMon();
}

Application::Application() {};

void Application::Menu()
{
	cout << "\t\tМеню приложения по управлению финансами:\n\n";
	cout << "1) Показать все банковские карты.\n";
	cout << "2) Добавить новую банковскую карту.\n";
	cout << "3) Удалить банковскую карту.\n";
	cout << "4) Показать общий баланс.\n";
	cout << "5) Выполнить транзакцию.\n";
	cout << "6) Показать все транзакции.\n";
	cout << "7) Сбросить историю транзакций.\n";
	cout << "8) Выход из приложения.\n";
	cout << "Введите действие(1-8): ";
}

void Application::ReturnMenu()
{
	char* y_or_n;
	cout << "Вернутся к меню (да - y/нет - n)? ";
	while (true)
	{
		newLine(y_or_n);
		if (*(y_or_n) == 'y')break;
		else if (*(y_or_n) == 'n')
		{
			cout << "Вернутся к меню (да - y/нет - n)? ";
			delete[]y_or_n;
		}
		else
		{
			cout << "Вы вели не верное значение, попробуйте снова: ";
			delete[]y_or_n;
		}
	}
	delete[]y_or_n;
}


int Application::checkDigits()
{
	int value = -1;
	char* Digits;
	while (true)
	{
		newLine(Digits);
		if (atoi(Digits) > 0 && atoi(Digits) <= 8) value = atoi(Digits);
		else cout << "Вы вели не верное значение, попробйте снова: ";
		delete[]Digits;
		if (value >= 0) break;
	}
	return value;
}

bool Application::checkData()
{
	bool flag = false;	
	int count_1 = 0;
	int count_2 = 0;
	Card* tempArr = MyWallet.getCard();
	Transaction tempTr = MyStat.lastTr();		
	if (lastMon > tempTr.getMon())
	{
		cout << "Неверная дата!\n";
		ReturnMenu();
		return true;
	}
	else if (lastDay > tempTr.getDay())
	{
		cout << "Неверная дата!\n";
		ReturnMenu();
		return true;
	}	
	for (int i = 0; i < MyWallet.getSize(); i++)
	{
		if (tempTr.Number() == tempArr[i].GetNumber())
		{
			count_1++;
			if (tempTr.getSum() < 0) count_2++;
			if (tempTr.getType() == "внести") MyWallet.getCard()[i].Deposit(tempTr.getSum());
			if ((tempTr.getSum() > tempArr[i].GetBalance()) && tempTr.getType() == "снять") count_2++;
			if (tempTr.getType() == "снять") MyWallet.getCard()[i].Withdraw(tempTr.getSum());
			break;
		}
	}
	if (count_1 == 0)
	{
		cout << "Вы ввели не верный номер карты, попробуйте снова.\n";
		ReturnMenu();		
		return true;
	}
	else if (count_2 != 0)
	{		
		ReturnMenu();
		return true;
	}
	else
	{
		lastMon = tempTr.getMon();
		lastDay = tempTr.getDay();
		cout << "Операция выполнена успешно.\n";
		return false;
	}		
}

void Application::Work()
{
	bool flag = false;
	int count = 0;
	while (true)
	{
		Menu();		
		switch (checkDigits())
		{
			case 1:
				MyWallet.ShowWallet(); 					
				ReturnMenu();	
				break;
			case 2:				
				MyWallet.AddCard();
				ReturnMenu();
				break;
			case 3:			
				MyWallet.DelCard();
				ReturnMenu();
				break;
			case 4:
				MyWallet.BalanceAll();
				ReturnMenu();
				break;
			case 5:
				while (true)
				{
					do
					{
						MyWallet.ShowWallet();
						if (count == 0)MyStat.AddTransaction(lastMon, lastDay, count);
						else
						{
							cout << "\nДата должна быть не раньше: " << lastDay << "-го";
							Months(lastMon);
							cin >> MyStat.lastTr();
						}
						count++;
					} while (checkData());
					count = 0;
					MyStat.SaveTransaction();
					MyWallet.SaveCard();										
					ReturnMenu();
					break;				
				}
				break;
			case 6:
				MyStat.ShowStatistics();
				ReturnMenu();
				break;
			case 7:	
				MyStat.DelTransaction();				
				MyStat.SaveTransaction();
				lastMon = 1;
				lastDay = 1;
				ReturnMenu();
				break;	
			case 8:
				flag = true;
				break;
			default:
				break;
		}
		system("cls");
		if (flag) break;
	}
}


char* newLine(char*& Digits)
{
	char* a = new char[255];
	cin.getline(a, 255);
	int len = strlen(a);
	Digits = new char[len + 1];
	strcpy(Digits, a);
	delete[]a;
	return Digits;
}

void Months(int a)
{
	switch (a)
	{
	case 1:
		cout << " января\n";
		break;
	case 2:
		cout << " февраля\n";
		break;
	case 3:
		cout << " марта\n";
		break;
	case 4:
		cout << " апреля\n";
		break;
	case 5:
		cout << " мая\n";
		break;
	case 6:
		cout << " июня\n";
		break;
	case 7:
		cout << " июля\n";
		break;
	case 8:
		cout << " августа\n";
		break;
	case 9:
		cout << " сентября\n";
		break;
	case 10:
		cout << " октября\n";
		break;
	case 11:
		cout << " ноября\n";
		break;
	case 12:
		cout << " декабря\n";
		break;
	}
}