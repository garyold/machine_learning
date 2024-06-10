#pragma once
#include "common.h"

struct AccountItem
{
    string itemType;
    int amount;
    string detail;
};

void loadDataFromFile(vector<AccountItem>& items);


void accounting(vector<AccountItem>& items);
void insertIntoFile(const AccountItem& item);
void income(vector<AccountItem>& items);
void expand(vector<AccountItem>& items);


void query(const vector<AccountItem>& items); 
void queryItems(const vector<AccountItem>& items);
void queryItems(const vector<AccountItem>& items, const string itemType);
void printItem(const vector<AccountItem>& items);