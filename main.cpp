#include <iostream>
#include <map>
#include <string>

void parseRequest(std::string& req, std::string& phone, std::string& person){
    int k = 0;
    for(int i = 0 ; i < req.length();i++){
        if(((req[i] >= '0')&&(req[i] <= '9'))||(req[i] ==  '-')){
            k = i;
        }
    }
    if(k == 0){
        phone ="";
        person = req;
    } else if(k == req.length()-1){
        phone = req;
        person = "";
    }else{
        phone = req.substr(0,k+1);
        person = req.substr(k+2);
    }

}

std::string makePersonWithNumber(std::string& person, int num){
    return person +'_'+ std::to_string(num);
}

int extractLastPersonNum(std::map<std::string,std::string>& rPB, std::string& person) {
    int i = 0;
    while(rPB.find(makePersonWithNumber(person,i))!=rPB.end()){
        i++;
    }
    return i;
}
void insertPerson(std::map<std::string,std::string>& rPB, std::string& person, std::string& phone){
    int num = extractLastPersonNum(rPB,person);
    rPB.insert(std::make_pair(makePersonWithNumber(person,num), phone));
}

int main() {
    std::map<std::string,std::string>phoneBook;
    std::map<std::string,std::string>reversPhoneBook;
    std::string request;
    std::cout << "Input your request, or 'exit' for exit" << std::endl;
    std::getline(std::cin,request);
    while(request != "exit"){
        std::string phone, person;

        parseRequest(request,phone, person);
        if((phone.length()>0)&&(person.length()>0)) {
            phoneBook.insert(std::make_pair(phone, person));
            insertPerson(reversPhoneBook, person, phone);
        }if((phone.length()>0)&&(person.length()==0)){
            auto iter = phoneBook.find(phone);
            if(iter!=phoneBook.end()) {
                std::cout << iter->second << std::endl;
            } else {
                std::cout << "There is no this phone number!" << std::endl;
            }
        }if((phone.length()==0)&&(person.length()>0)){
            auto iter = reversPhoneBook.find(makePersonWithNumber(person,0));
            if(iter == reversPhoneBook.end()){
                std::cout << "There is no this person!" << std::endl;
            } else{
                int i = 0;
                for(auto it = reversPhoneBook.find(makePersonWithNumber(person,i)); it != reversPhoneBook.end();
                it = reversPhoneBook.find(makePersonWithNumber(person,++i))){

                    std::cout << it->second << " ";
                }
                std::cout << std::endl;
            }
        }

        std::cout << "Input your request, or 'exit' for exit" << std::endl;
        std::getline(std::cin,request);

    }
   // for(auto it = phoneBook.begin(); it!=phoneBook.end(); ++it){
   //     std::cout << it->first << " " << it -> second << std::endl;
   // }

   // for(auto it = reversPhoneBook.begin(); it!=reversPhoneBook.end(); ++it){
   //     std::cout << it->first << " " << it -> second << std::endl;
   // }

    return 0;
}
