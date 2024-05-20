#pragma once
#include "clsPerson.h"
#include<iostream>
#include"clsString.h"
#include<vector>
#include<fstream>
#include"clsDate.h"
#include"clsUtil.h"
using namespace std;

class clsUser :
    public clsPerson
{
    enum enMode{EmptyMode=1,UpdateMode,AddNewMode};
    enMode _Mode;
    string _UserName;
    string _Password;
    int _Permissions;
    bool _MarkedForDelete = false;

    struct stLoginRegisterRecord;
    static stLoginRegisterRecord _ConvertLoginRegisterLineTorecord(string Line, string Seperator = "#//#")
    {
        stLoginRegisterRecord LoginRegisterRecord;
        vector<string >LoginRegisterDataLine = clsString::Split(Line, Seperator);
        LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
        LoginRegisterRecord.UserName = LoginRegisterDataLine[1];
        LoginRegisterRecord.Password = LoginRegisterDataLine[2];
        LoginRegisterRecord.Permissions = stoi(LoginRegisterDataLine[3]);
        return LoginRegisterRecord;
    }

    string _PrepareLogInRecord(string Seperator = "#//#")
    {
        string LineRecord = "";
        LineRecord += clsDate::GetSystemDateTimeString() + Seperator;
        LineRecord += _UserName + Seperator;
        LineRecord += clsUtil::Encryption(_Password) + Seperator;
        LineRecord += to_string(_Permissions);
        return LineRecord;
    }

    static clsUser _ConvertLinetoUserObject(string Line, string Seperator = "#//#")
    {
        vector<string> vUserData;
        vUserData = clsString::Split(Line, Seperator);
        return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
            vUserData[3], vUserData[4], clsUtil::Decryption(vUserData[5]), stoi(vUserData[6]));
    }
    static string _ConvertUserObjectToLine(clsUser User, string Seperator = "#//#")
    {

        string UserRecord = "";
        UserRecord += User.FirstName + Seperator;
        UserRecord += User.LastName + Seperator;
        UserRecord += User.Email + Seperator;
        UserRecord += User.Phone + Seperator;
        UserRecord += User.UserName + Seperator;
        UserRecord += clsUtil::Encryption(User.Password) + Seperator;
        UserRecord += to_string(User.Permissions);

        return UserRecord;

    }
    static vector<clsUser>_LoadUsersDataFromFile()
    {
        vector <clsUser>vUserData;
        fstream Myfile;
        Myfile.open("Users.txt", ios::in);
        if (Myfile.is_open())
        {
            string Line;
            while (getline(Myfile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                vUserData.push_back(User);
            }
            Myfile.close();
        }
        return vUserData;
    }
    static void _SaveUsersDataToFile(vector <clsUser> vUsers)
    {

        fstream MyFile;
        MyFile.open("Users.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsUser U : vUsers)
            {
                if (U.MarkedForDeleted() == false)
                {
                    //we only write records that are not marked for delete.  
                    DataLine = _ConvertUserObjectToLine(U);
                    MyFile << DataLine << endl;

                }

            }

            MyFile.close();

        }

    }
    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }
    }
     void _Update()
    {
         vector <clsUser> _vUsers;
         _vUsers = _LoadUsersDataFromFile();

         for (clsUser& U : _vUsers)
         {
             if (U.UserName == UserName)
             {
                 U = *this;
                 break;
             }
         }
         _SaveUsersDataToFile(_vUsers);
    }
     void _AddNew()
     {
         _AddDataLineToFile(_ConvertUserObjectToLine(*this));
     }
     static  clsUser _GetEmptyUserObject()
    {
        return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

public:
    enum enPermissions{eAll = -1 , pListClients = 1 , pAddNewClient = 2, pDeleteClient = 4 ,
        pUpdateClients = 8, pFindClient = 16 , pTransactions = 32 , pManageUsers = 64, pShowLogInRegister =128};

    struct stLoginRegisterRecord
    {
        string DateTime;
        string UserName;
        string Password;
        int Permissions;
    };

    clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone,
            string UserName, string PassWord, int Permissions)
        :clsPerson(FirstName, LastName, Email, Phone)
    {
        _Mode = Mode;
        _UserName = UserName;
        _Password = PassWord;
        _Permissions = Permissions;
    }

    bool IsEmpty()
    {
        return(_Mode == enMode::EmptyMode);
    }
    bool MarkedForDeleted()
    {
        return _MarkedForDelete;
    }
    string GetUserName()
    {
        return _UserName;
    }
    void SetUserName(string UserName)
    {
        _UserName = UserName;
    }
    __declspec(property(get = GetUserName, put = SetUserName))string UserName;

    string GetPassWord()
    {
        return _Password;
    }
    void SetPassword(string PassWord)
    {
        _Password = PassWord;
    }
    __declspec(property(get = GetPassWord, put = SetPassword))string Password;

    int GetPermissions()
    {
        return _Permissions;
    }
    void SetPermessions(int Permissions)
    {
        _Permissions = Permissions;
    }
    __declspec(property(get = GetPermissions, put = SetPermessions))int Permissions;

    static clsUser Find(string UserName)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::in);
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.UserName == UserName)
                {
                    MyFile.close();
                    return User;
                }
            }
            MyFile.close();
        }
        return _GetEmptyUserObject();
    }
    static clsUser Find(string UserName,string passWord)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::in);
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.UserName == UserName && User.Password==passWord)
                {
                    MyFile.close();
                    return User;
                }
            }
            MyFile.close();
        }
        return _GetEmptyUserObject();
    }
    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };
    enSaveResults Save()
    {
        switch (_Mode)
        {
        case clsUser::EmptyMode:
        {
            if (IsEmpty())
            {
                return  enSaveResults::svFaildEmptyObject;
                break;
            }
        }
        case clsUser::UpdateMode:

        {
             _Update();
            return enSaveResults::svSucceeded;
            break;
        }
        case clsUser::AddNewMode:
        {
            //This will add new record to file or database
            if (IsUserExist(_UserName))
            {
                return enSaveResults::svFaildUserExists;

            }
            else
            {
                  _AddNew();
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }
            break;
        }
 
        }
     }
    static bool IsUserExist(string UserName)
    {

        clsUser User = clsUser::Find(UserName);
        return (!User.IsEmpty());
    }
    bool Delete()
    {
        vector <clsUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();

        for (clsUser& U : _vUsers)
        {
            if (U.UserName == _UserName)
            {
                U._MarkedForDelete = true;
                break;
            }

        }
        _SaveUsersDataToFile(_vUsers);
        *this = _GetEmptyUserObject();
        return true;
    }
    static clsUser GetAddNewUserObject(string UserName)
    {
        return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
    }
    static vector <clsUser> GetUsersList()
    {
        return _LoadUsersDataFromFile();
    }
    bool CheckAccessPermission(enPermissions Permission)
    {
        if (this->Permissions == enPermissions::eAll)
            return true;
        if (Permission & this->Permissions == Permission)
            return true;
        else
            return false;
    }
    void RegisterLogIn()
    {
        string stDataLine = _PrepareLogInRecord();
        fstream MyFile;
        MyFile.open("LoginRegister.txt", ios::app | ios::out);

        if (MyFile.is_open())
        {
            MyFile << stDataLine << endl;
               
            MyFile.close();
        }
    }
    static vector <stLoginRegisterRecord>GetLoginRegisterList()
    {
        vector <stLoginRegisterRecord> vLoginRegisterRecord;
        fstream MyFile;
        MyFile.open("LoginRegister.txt", ios::in);
        if (MyFile.is_open())
        {
            string Line;
            stLoginRegisterRecord LoginRegisterRecord;
            while (getline(MyFile, Line))
            {
                LoginRegisterRecord = _ConvertLoginRegisterLineTorecord(Line);
                vLoginRegisterRecord.push_back(LoginRegisterRecord);
            }
            MyFile.close();
        }
        return vLoginRegisterRecord;
    }
};

