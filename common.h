#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>

#define INCOME "收入"
#define EXPAND "支出"
#define FILENAME "D:\\data\\AccountBook.txt"

using namespace std;

void showMainMenu();
void showAccountingMenu();
void showQueryMenu();

char readMenuSelection(int options);
char readQuitConfirm();
int readAmount();