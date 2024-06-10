#include "common.h"
#include "account_item.h"

void loadDataFromFile(vector<AccountItem>& items)
{
    ifstream input(FILENAME);

    AccountItem item;
    while(input >> item.itemType >> item.amount >> item.detail)
    {
        items.push_back(item);
    }

    input.close();
}

void accounting(vector<AccountItem>& items)
{
    char key = readMenuSelection(3);

    switch(key)
    {
        case '1': 
            income(items);
            break;
        case '2': 
            expand(items);
            break;
        default: 
            break;
    }
}

void income(vector<AccountItem>& items)
{
    AccountItem item;

    item.itemType = INCOME;

    cout << "\n本次收入金額:";
    item.amount = readAmount();

    cout << "\n備註";
    getline(cin, item.detail);

    items.push_back(item);
    insertIntoFile(item);

    cout << "\n---------------------記帳成功!---------------------" << endl;
    cout << "\n請按空白鍵返回主菜單..." << endl;

    string line;
    getline(cin, line);
}

void expand(vector<AccountItem>& items)
{
    AccountItem item;

    item.itemType = EXPAND;

    cout << "\n本次支出金額:";
    item.amount = -readAmount();

    cout << "\n備註";
    getline(cin, item.detail);

    items.push_back(item);
    insertIntoFile(item);

    cout << "\n---------------------記帳成功!---------------------" << endl;
    cout << "\n請按空白鍵返回主菜單..." << endl;

    string line;
    getline(cin, line);
}

void insertIntoFile(const AccountItem& item)
{
    ofstream output(FILENAME, ios::out | ios::app);

    output << item.itemType << "\t" << item.amount << "\t" << item.detail << endl;

    output.close();
}


void query(const vector<AccountItem>& items)
{
    char key = readMenuSelection(4);

    switch(key)
    {
      case '1': 
        queryItems(items);
        break;
      case '2': 
        queryItems(items, INCOME);
        break;
      case '3': 
        queryItems(items, EXPAND);
        break;
      default: 
        break;
    }
}

void queryItems(const vector<AccountItem>& items)
{
    cout << "--------------------查詢結果---------------------" << endl;
    cout << "\n類型\t\t金額\t\t備註\n" <<endl;

    int total = 0;
    for(auto item : items)
    {
        printItem(item);
        total += item.amount;
    }

    cout << "-----------------------------------------------\n" << endl;
    cout << "總收支:" << total << endl;
    cout << "\n請按空白鍵返回主菜單..." << endl;

    string line;
    getline(cin, line);
}

void queryItems(const vector<AccountItem>& items, const string itemType)
{
    cout << "--------------------查詢結果---------------------" << endl;
    cout << "\n類型\t\t金額\t\t備註\n" <<endl;

    int total = 0;
    for(auto item : items)
    {
        if(item.itemType != itemType)
        {
            continue;
        }
        printItem(item);
        total += item.amount;
    }

    cout << "-----------------------------------------------\n" << endl;
    cout << ((itemType == INCOME) ? "總收入:" : "總支出:") << total << endl;
    cout << "\n請按空白鍵返回主菜單..." << endl;

    string line;
    getline(cin, line);
}

void printItem(const AccountItem& item)
{
    cout << item.itemType << "\t\t" << item.amount << "\t\t" << item.detail << endl;
}