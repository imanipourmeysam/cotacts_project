#ifndef CONTACTS_MANAGER_H
#define CONTACTS_MANAGER_H

#include <iostream>
#include <string>
#include <set>
#include <fstream>
#include <sstream>
#include <locale>

struct NPE{ // stand for Name Phone Email
    NPE(std::string _Name, std::string _Phone, std::string _Email = "not defined");
    std::string Name, Phone, Email;
};

class Contacts_Manager
{
public:
    typedef const std::string& strp;
    Contacts_Manager(strp _Dir);
    void newcontact(const NPE& _NPE);
    void newcontact(strp _Name, strp _Phone, strp _Email = "not defined");
    void removecontact(strp _CurrentData);//remove the contact which include _CurrentData
    void edit(strp _CurrentData, strp _NewData);//edit info of a contact which include _CurrentData with replacing _NewData(s).
    void edit(strp _CurrentData, strp _NewData1, strp _NewData2);
    void edit(strp _CurrentData, strp _NewData1, strp _NewData2, strp _NewData3);
    void printinfo(strp _SearchData);//it fill find a contact based _SearchData and print its info.
    void removeall();
private:
    std::string Dir;// path to phonebook, where we store contacts info.
    std::fstream Fio;
    std::set<std::string> tempo_phonebook;
    char whatdata(strp _Data);//return 'n' if _Data is name, return 'p' if _Data is Phone and 'e' if _Data is email. 
    int find(strp _Dataitem);//return the number of the line containing _Dataitem.(_Dataitem could be name, phone or email).
    
};

#endif
