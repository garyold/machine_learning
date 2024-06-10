#include "common.h"

char readMenuSelection(int options)
{
    string str;

    while(true)
    {
        getline(cin, str);

        if(str.size() != 1 || str[0] - '0' <= 0 || str[0] - '0' > options)
            cout << "輸入錯誤，請重新輸入:";
        else
            break;
    }

    return str[0];

}

char readQuitConfirm()
{
    string str;
    
    while(true)
    {
        getline(cin, str);

        if(str.size() != 1 || toupper(str[0]) != 'Y' && toupper(str[0]) != 'N') 
            cout << "輸入錯誤，請重新輸入(Y/N):";
        else
            break;
    }

    return toupper(str[0]);
}

int readAmount()
{
    int amount;

    string str;
    while(true)
    {
        getline(cin, str);

        try
        {
            amount = stoi(str);
            break;  
        }
        catch(invalid_argument e)
        {
            cout << "輸入錯誤，請輸入正確數字:";
        }
    }

    return amount;
}