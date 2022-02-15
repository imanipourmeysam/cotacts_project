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
//I was thinking if I could use multiprocessing then I would invok two times edit function with _NewData 1 and 2.
void Contacts_Manager::edit(strp _CurrentData, strp _NewData1, strp _NewData2)
{
    if(this->whatdata(_NewData1) == this->whatdata(_NewData2))
    {
       std::cout << "Please enter two different types of data.\n";
       std::cout << "More detial -> " << _NewData1 << " and " << _NewData2 << "are both the same type.\n";
       return;
    }
    if(this->whatdata(_NewData1) != this->whatdata(_CurrentData))
    {
        this->edit(_CurrentData,_NewData1);
        this->edit(_CurrentData,_NewData2);
        return;
    }
    else if(this->whatdata(_NewData2) != this->whatdata(_CurrentData))
    {
        this->edit(_CurrentData,_NewData2);
        this->edit(_CurrentData,_NewData1);
        return;
    }
    else 
    {
        this->edit(_CurrentData,_NewData2);
        this->edit(_CurrentData,_NewData1);
        return;
    }
}

void Contacts_Manager::edit(strp _CurrentData, strp _NewData1, strp _NewData2, strp _NewData3)
{
    char input_types[3] = {this->whatdata(_NewData1),this->whatdata(_NewData2),this->whatdata(_NewData3)};
    if(input_types[0] == input_types[1] || input_types[0] == input_types[2] || input_types[1] == input_types[2])
    {
       std::cout << "Please enter different types of new data.\n";
       return;
    }

    if(input_types[0] != this->whatdata(_CurrentData))
    {
        this->edit(_CurrentData,_NewData1);
        if(input_types[1] != this->whatdata(_CurrentData))
        {
            this->edit(_CurrentData,_NewData2);
            this->edit(_CurrentData,_NewData3);
            return;
        }
        else if(input_types[2] != this->whatdata(_CurrentData))
        {
            this->edit(_CurrentData,_NewData3);
            this->edit(_CurrentData,_NewData2);
            return;
        }
    }

    if(input_types[1] != this->whatdata(_CurrentData))
    {
        this->edit(_CurrentData,_NewData2);
        if(input_types[0] != this->whatdata(_CurrentData))
        {
            this->edit(_CurrentData,_NewData1);
            this->edit(_CurrentData,_NewData3);
            return;
        }
        else if(input_types[2] != this->whatdata(_CurrentData))
        {
            this->edit(_CurrentData,_NewData3);
            this->edit(_CurrentData,_NewData1);
            return;
        }
    }
    
    if(input_types[2] != this->whatdata(_CurrentData))
    {
        this->edit(_CurrentData,_NewData3);
        if(input_types[0] != this->whatdata(_CurrentData))
        {
            this->edit(_CurrentData,_NewData1);
            this->edit(_CurrentData,_NewData2);
            return;
        }
        else if(input_types[1] != this->whatdata(_CurrentData))
        {
            this->edit(_CurrentData,_NewData2);
            this->edit(_CurrentData,_NewData1);
            return;
        }
    }

}


void Contacts_Manager::printinfo(strp _SearchData)
{
    int fline = this->find(_SearchData);
    if(fline == -1)
    {
        std::cout << "No contact has been found" << "\n";
        return;
    }
    Fo.close();
    Fi.open(Dir);
    int cnt = 0;
    std::string line;
    while(std::getline(Fi,line))
    {
        if(cnt == fline)
        {
            size_t firstcomma = line.find(',',0);
            size_t secondcomma= line.find(',',firstcomma+1);
            std::cout << "Name  : " << line.substr(0,firstcomma) << "\n";
            std::cout << "Phone : " << line.substr(firstcomma+1,secondcomma-firstcomma-1) << "\n";
            std::cout << "Email : " << line.substr(secondcomma+1,line.length()-secondcomma-1) << "\n";
            return;
        }
        cnt++;
    }
}

void Contacts_Manager::removeall()
{
    Fi.close();
    Fo.open(Dir,std::ofstream::trunc);
    return;
}


