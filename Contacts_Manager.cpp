#include "Contacts_Manager.h"

NPE::NPE(std::string _Name, std::string _Phone, std::string _Email)
{
    Name  = _Name;
    Phone = _Phone;
    Email = _Email;
};

Contacts_Manager::Contacts_Manager(strp _Dir)
{
    Dir = _Dir;
}

void Contacts_Manager::newcontact(const NPE& _NPE)
{
    Fi.close();
    if (this->find(_NPE.Name) != -1)
    {
        std::cout << "this name is already exist." << "\n";
        return;
    }
    else if (this->whatdata(_NPE.Email) != 'e')
    {
        std::cout << "wrong email, basically email contiain '@' character." << "\n";
        return;
    }
    else if(this->whatdata(_NPE.Phone) != 'p')
    {
        std::cout << "wrong number, basically phone number should contain digits not letter" << "\n"; 
        return;
    }
    else if(this->whatdata(_NPE.Name) == 'e')
    {
        std::cout << "wrong name, basically name shouldn't contain '@' character." << "\n";
        return;
    }
    else
    {
        Fo.open(Dir,std::fstream::app);
        Fo << _NPE.Name << "," << _NPE.Phone << "," << _NPE.Email << "\n";
    }
    return;
}

void Contacts_Manager::newcontact(strp _Name, strp _Phone, strp _Email)
{
    Fi.close();
    if(this->find(_Name) != -1)
    {
        std::cout << "this name is already exist." << "\n";
        return;
    }
    else if (this->whatdata(_Email) != 'e')
    {
        std::cout << "wrong email, basically email contiain '@' character." << "\n";
        return;
    }
    else if(this->whatdata(_Phone) != 'p')
    {
        std::cout << "wrong number, basically phone number should contain digits not letter" << "\n"; 
        return;
    }
    else if(this->whatdata(_Name) == 'e')
    {
        std::cout << "wrong name, basically name shouldn't contain '@' character." << "\n";
        return;
    }
    else
    {
        Fo.open(Dir,std::fstream::app);
        NPE temp(_Name, _Phone, _Email); 
        Fo << _Name << "," << _Phone << "," << _Email << "\n";
    }
    return; 
}

void Contacts_Manager::removecontact(strp _CurrentData)
{
    int fline = this->find(_CurrentData);
    if(fline == -1)
    {
        std::cout << "can't find a contact with given info." << "\n";
        return;
    }
    Fo.close();
    Fi.open(Dir);
    tempo_phonebook.clear();
    bool condition = true;
    std::string line;
    int cnt = 0;
    while(std::getline(Fi,line))
    {
        if(line == "")
           condition = false; 
        if(cnt != fline && condition)
        {
            tempo_phonebook.insert(line);
        }
        cnt++;
        condition = true;
    }
    Fi.close();
    Fo.open(Dir,std::fstream::trunc);
    for(auto i : tempo_phonebook)
    {
        Fo << i << "\n";
    }
    Fo.close();
}

int Contacts_Manager::find(strp _Dataitem)
{
    char datatype = this->whatdata(_Dataitem);
    int fline = 0;
    Fo.close();
    Fi.open(Dir);
    std::string line;
    while(std::getline(Fi,line))
    {
        size_t firstcomma = line.find(',',0);
        size_t secondcomma= line.find(',',firstcomma+1);
        size_t res = line.find(_Dataitem);
        if(res != std::string::npos)
        {
            switch(datatype)
            {
                case 'n':
                    {
                        if(!line.compare(0,firstcomma,_Dataitem))
                        {
                             Fi.close();
                             return fline;
                        }
                    }break;
                case 'p':
                    {
                        if(!line.compare(firstcomma+1,secondcomma-firstcomma-1,_Dataitem))
                        {
                             Fi.close();
                             return fline; 
                        }

                    }break;
                case 'e':
                    {
                        if(!line.compare(secondcomma+1,line.length()-secondcomma-1,_Dataitem))
                        {
                             Fi.close();
                             return fline;                            
                        }
                    }break;
            }

        }
        fline++;
    }
    fline = -1;
    Fi.close();
    return fline;
}

char Contacts_Manager::whatdata(strp _Data)
{
    
    if(_Data.find('@')!= std::string::npos||_Data == "not defined")
    {
        return 'e';
    }
    else if (std::isdigit(_Data[0]) == 1)
    {
        return 'p';
    }
    else
    {
         return 'n'; 
    }
}

void Contacts_Manager::edit(strp _CurrentName, strp _NewData)
{
    int fline = this->find(_CurrentName);
    if(fline == -1)
    {
        std::cout << "can't find a contact with given info." << "\n";
        return;
    }
    tempo_phonebook.clear();
    Fi.open(Dir);
    std::string line;
    int cnt = 0;
    while(std::getline(Fi,line))
    {
        if(cnt == fline)
        {
            size_t firstcomma = line.find(',',0);
            size_t secondcomma= line.find(',',firstcomma+1);
            char datatype = this->whatdata(_NewData);
            switch(datatype)
            {
                case 'n':
                    {
                        line.replace(0,firstcomma,_NewData);
                    }break;

                case 'p':
                    {
                        line.replace(firstcomma+1,secondcomma-firstcomma-1,_NewData);
                    }break;
                case 'e':
                    {
                        line.replace(secondcomma+1,line.length()-secondcomma-1,_NewData);
                    }      
            }
            tempo_phonebook.insert(line);
        }
        else
        {
            tempo_phonebook.insert(line);
        }
        cnt++;
    }
    Fi.close();
    Fo.open(Dir,std::fstream::trunc);
    for(auto i : tempo_phonebook)
    {
        Fo << i << "\n";
    }
    Fo.close();
    return;
}

