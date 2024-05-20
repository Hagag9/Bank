#pragma once
#include "clsScreen.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"
#include<iostream>
using namespace std;
class clsWithdrawScreen :
    protected clsScreen
{
    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";
    }
    static string _ReadAcoountNumber()
    {
        cout << "Please Enter Account Number ? ";
        return clsInputValidate::ReadString();
    }

public:
    static void ShowWithdrawScreen()
    {
        _DrawScreenHeader("\tWithDraw Screen");
        string AccountNumber = _ReadAcoountNumber();
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nClinet with [" << AccountNumber << "] dose not exist \n";
             AccountNumber = _ReadAcoountNumber();
        }
        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _PrintClient(Client1);
        int Amount = 0;
        cout <<"\nPlease enter withdraw amount? "; 
        cin >> Amount;
        cout << "\nAre you sure you want to perform this transaction? ";
        char Answer = 'n';
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            if (Client1.Withdraw(Amount))
                {
                    cout << "\nAmount Deposited Successfully.\n";
                    cout << "\nNew Balance Is: " << Client1.AccountBalance;
                }
                else
                {
                cout << "\nCannot withdraw, Insuffecient Balance!\n";
                cout << "\nAmout to withdraw is: " << Amount;
                cout << "\nYour Balance is: " << Client1.AccountBalance;
                }
        }
        else
        {
            cout << "\nOperation was cancelled.\n";
        }


    }
};

