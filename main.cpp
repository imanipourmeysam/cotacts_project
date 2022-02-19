///IMANIPOUR Meysam
/// comment lines start with 3 forward slash.(///).
/// if the line contian 2 forward slash it could be run.

#include <iostream>
#include "Contacts_Manager.h"

int main(int argc, char* argv[])
{

    if(argc < 2)
    {
        std::cerr << "phonebook path has not specified. please specify it as second argument. " << "\n";
        return EXIT_FAILURE;
    }
    if(argc > 2)
    {
        std::cerr << "extra command argument is provided\n";
        return EXIT_FAILURE;
    }
    ///creating the object of the class.
    //Contacts_Manager cm(argv[1]);
   
    ///4 different ways of initializing new contact.
    //cm.newcontact("ali","12345","ali@mail.com");
    //cm.newcontact(NPE("hassan","23456","hassan@hotmail.com"));
    //cm.newcontact("hossein","34567");
    //cm.newcontact(NPE("sadjad","45678"));
    
    ///wrong data input and warning handling.
    //cm.newcontact("@name","09876");// wrong name warning will arise.
    //cm.newcontact("name","j9382");// wrong phone number warning will arise.
    //cm.newcontact("name","84989","test"); // wrong email warning will arise.
    //cm.newcontact("ali","28913","anemail@gmail.com");// duplicated contact info warning will arise.

    ///removeing an existing member of phone book.
    //cm.removecontact("sadjad"); // it could be by phone number like -> cm.removecontact("45678") 
    
    ///warning for non existing data.
    //cm.removecontact("notexistdata"); // warning will arise saying this info doesn't exist to be removed.
   
    /// edit contacts of the phone book. 
    //cm.edit("ali","Ali");//will edit contact with name ali to be Ali.
    //cm.edit("Ali","11111");//will edit will name Ali to have a new phone number like"11111".
    //cm.edit("sadjad","NewSadjad","99999");//editing contact named sadjad to a new neme and new phone number
    //cm.edit("23456","newemail@hotmail.com");//editing a contact with the given phone numbe to have the new email(2nd arugment).
    //cm.edit("hossein","newname","98989","Newemail@server.com");
    
    ///if the given new data for editing are not correct(for example phone without digits) then there will be warning.
    
    ///print the info of a contact with giving one data of that contact. 
    //cm.printinfo("NewSadjad");
   
    ///remove all the contact 
    //cm.removeall();
    return 0;
}   
