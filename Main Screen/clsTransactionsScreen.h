#pragma once
#include<iostream>
#include "clsScreen.h"
#include"clsBankClient.h"
#include<iomanip>
#include "clsInputValidate.h"
#include"clsDepositScreen.h"
#include"clsWithdrawScreen.h"
#include"clsTotalBalancesScreen.h"
#include"clsTrasferScreen.h"
#include"clsTransferLogScreen.h"
using namespace std;


class clsTransactionsScreen :
    protected clsScreen
{
private:
    enum enTransactiomMenueOptions{eDeposite=1,eWithdraw ,eShowTotalBalance ,eTransfer,eTransferLog ,eShowMainMenue};
    static short ReadTransactionsMenueOption()
    {
        cout << setw(37) << left << "" << "Chose what do you want do ? [1 to 6 ] ? ";
        int Choice = clsInputValidate::ReadShortNumberBetween(1,6, "Please Enter Number Between 1 to 6 ? ");
        return Choice;
    }
    static void _ShowDepositScreen()
    {
       // cout << "\n Deposit Screen will be here.\n";
        clsDepositScreen::ShowDepositScreen();
    }

    static void _ShowWithdrawScreen()
    {
        //cout << "\n Withdraw Screen will be here.\n";
        clsWithdrawScreen::ShowWithdrawScreen();
    }

    static void _ShowTotalBalancesScreen()
    {
       // cout << "\n Balances Screen will be here.\n";
        clsTotalBalancesScreen::ShowtotalBalances();
    }
    static void _ShowTransferScreen()
    {
        clsTrasferScreen::ShowTransferScreen();
    }
    static void _showTransferLogScreen()
    {
        clsTransferLogScreen::ShowTransferLogScreen();
    }

    static void _GoBackToTransactionsMenue()
    {
        cout << "\n\nPress any key to go back to Transactions Menue...";
        system("pause>0");
        ShowTransactionsMenue();

    }
    static void _PerformTransactionsMainMenue(enTransactiomMenueOptions TransactionsMenueOption)
    {
        switch (TransactionsMenueOption)
        {
        case clsTransactionsScreen::eDeposite:
        {
            system("cls");
            _ShowDepositScreen();
            _GoBackToTransactionsMenue();
            break;
        }
        case clsTransactionsScreen::eWithdraw:
        {
            system("cls");
            _ShowWithdrawScreen();
            _GoBackToTransactionsMenue();
            break;
        }
        case clsTransactionsScreen::eShowTotalBalance:
        {
            system("cls");
            _ShowTotalBalancesScreen();
            _GoBackToTransactionsMenue();
            break;
        }
        case clsTransactionsScreen::eTransfer:
        {
            system("cls");
            _ShowTransferScreen();
            _GoBackToTransactionsMenue();
            break;
        }
        case clsTransactionsScreen::eTransferLog:
        {
            system("cls");
            _showTransferLogScreen();
            _GoBackToTransactionsMenue();
            break;
        }
        case clsTransactionsScreen::eShowMainMenue:
        {

        }

        }
    }

public:
    static void ShowTransactionsMenue()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pTransactions))
        {
            return;
        }
        system("cls");
        _DrawScreenHeader("\tTrans Action Menue");
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Transactions Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit.\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
        cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
        cout << setw(37) << left << "" << "\t[4] Trnsfer.\n";
        cout << setw(37) << left << "" << "\t[5] Trnsfer Log.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";
        _PerformTransactionsMainMenue((enTransactiomMenueOptions)ReadTransactionsMenueOption());
    }
};

