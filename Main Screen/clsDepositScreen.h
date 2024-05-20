#pragma once
#include "clsScreen.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"
#include<iostream>
using namespace std;

class clsDepositScreen :
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
    static void ShowDepositScreen()
    {
        _DrawScreenHeader("\tDeposite Screeen");
        string AccountNumber = _ReadAcoountNumber();
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nClinet with [" << AccountNumber << "] dose not exist \n";
            AccountNumber = _ReadAcoountNumber();
        }
        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _PrintClient(Client1);

        double Amount = 0;
        cout << "\nPlease enter deposit amount? ";
        Amount = clsInputValidate::ReadDblNumber();
        cout << "\nAre you sure you want to perform this transaction? ";
        char Answer = 'n';
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            Client1.Deposit(Amount);
            cout << "\nAmount Deposited Successfully.\n";
            cout << "\nNew Balance Is: " << Client1.AccountBalance;
        }
        else
        {
            cout << "\nOperation was cancelled.\n";
        }
    }


};

