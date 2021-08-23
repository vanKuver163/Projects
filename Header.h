#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

class Card
{
private:
	double balance;
	string number;
	string bank;
public:
	Card(double bal = 0.0, const string& num = "0", const string& b = "Bank");
	~Card();
	void Deposit(double money);
	void Withdraw(double money);
	double GetBalance();
	string GetNumber();
	Card& operator=(const Card c);
	friend ostream& operator <<(ostream& os, Card const& c);
	friend ofstream& operator <<(ofstream& of, Card& c);
	friend ifstream& operator >>(ifstream& ifs, Card& c);
	friend istream& operator >>(istream& ist, Card& c);
};

class Transaction
{
private:
	double sum;
	int day;
	int mon;
	string type;
	string number;
public:
	Transaction(double s = 0.0, int d = 0, int m = 0, const string& t = "0", const string& num = "0");
	~Transaction();
	double getSum();
	int getMon();
	int getDay();
	string Number();
	string getType();
	int checkMon();
	int checkDay(int m);
	int checkType();
	Transaction& operator=(const Transaction Tr);
	friend ostream& operator <<(ostream& os, const Transaction& Tr);
	friend ofstream& operator <<(ofstream& of, Transaction& Tr);
	friend ifstream& operator >>(ifstream& ifs, Transaction& Tr);
	friend istream& operator >>(istream& ist, Transaction& Tr);
};

class Wallet
{
private:
	Card* arr;
	int size = 0;
	ifstream file;
	ofstream file1;
public:
	Wallet();
	~Wallet();
	void ShowWallet();
	void BalanceAll();
	void AddCard();
	void SaveCard();
	void DelCard();	
	int getSize();
	Card* getCard();
};

class Statistics
{
private:
	Transaction* arr;
	int size = 0;
	ifstream file;
	ofstream file1;
public:
	Statistics();
	~Statistics();
	void ShowStatistics();
	void SaveTransaction();
	void AddTransaction(int mon, int day, int c);
	void DelTransaction();
	Transaction& lastTr();
	int lastD();
	int lastM();
};

class Application
{
private:
	Wallet MyWallet;
	Statistics MyStat;
	int lastMon = MyStat.lastM();
	int lastDay = MyStat.lastD();
public:
	Application();
	void Menu();
	void ReturnMenu();	
	int checkDigits();
	bool checkData();
	void Work();
};

char* newLine(char*& Digits);
void Months(int a);