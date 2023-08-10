#include "helpers.h"


using namespace std; 
int main(int argc, char *argv[]){    
    string line;
    ifstream myfile;

    int id;
    int age;
    int bloomSize = 0;
    string name;
    string surname;
    string country;
    string virus;
    string vaccinated;
    string sdate;
    date* dateOfVaccination;
    char* fileName;

    if(argc != 5) {
        cout << "Sorry, not enough parametres (4 needed).\n";
        exit(1);
    }


    if(strcmp(argv[1], "-c") == 0){
        
        // first command param is -c
        // I expect a file following...
        fileName = argv[2];

        // -b should follow...
        if(strcmp(argv[3], "-b") == 0){
            char c = argv[4][0];
            int counter = 1;
            while(c != '\0'){
                if(c < '0' || c > '9'){
                    cout << "This parameter should be a legal number.\n";
                    exit(1);
                }
                c = argv[4][counter];
                counter++;
            }
            bloomSize = atoi(argv[4]);
        }else{
            cout << "Sorry, this parameter should be -b.\n";
            exit(1);
        }

    }else if(strcmp(argv[1], "-b") == 0){
        
        // i expect a number following...
        char c = argv[2][0];
        int counter = 1;
        while(c != '\0'){
            if(c < '0' || c > '9'){
                cout << "This parameter should be a legal number.\n";
                exit(1);
            }
            c = argv[2][counter];
            counter++;
        }

        // next should follows -c ... 
        // check...

        if(strcmp(argv[3], "-c") == 0){
            //yes... follows file name...
            fileName = argv[4];
            bloomSize = atoi(argv[2]);
        }else{
            cout << "Sorry, this parameter should be -c.\n";
            exit(1);
        }

    }

    cout << bloomSize << endl;
    myfile.open(fileName);

    if(!myfile.is_open()) {
      perror("Error open");
      exit(EXIT_FAILURE);
    }

    int numLines = 0;
    while(getline(myfile, line)) {
        if( myfile.eof() ) break;
        numLines++;
    }
    numLines++;

    myfile.close();

    myfile.open("inputFile.txt");
    if(myfile.eof()){
        return -1;
    }

    person** personsArray = (person**) malloc(numLines * sizeof(person*));
    int legalLines = 0;

    for(int i = 0; i < numLines; i++){
        personsArray[i] = NULL;
    }

    person* citizen;
    myfile >> id >> name >> surname >> age >> country >> virus >> vaccinated;
    
    hashTable* countryHash = new hashTable(COUNTRYARRAY);
    hashTable* virusHash = new hashTable(VIRUSARRAY);

    if(vaccinated.compare("NO") == 0){

        citizen = new person(id, name, surname, age, vaccinated);

    }else{

        myfile >> sdate;
        string myText(sdate);
        istringstream iss(myText);
        string token;
        
        getline(iss, token, '-');
        int day = stoi(token);
        
        getline(iss, token, '-');
        int month = stoi(token);
        
        getline(iss, token, '-');
        int year = stoi(token);

        dateOfVaccination = new date(day,month,year);
        citizen = new person(id, name, surname, age, vaccinated, NULL, NULL,dateOfVaccination);
    
    }

    int faulty = citizen->checkRecord();

    if(faulty == 1){

        cout << "Error illegal record: \n";
        citizen->printData();

        if(citizen->arrayVaccinated[0] == "YES"){
            delete citizen;
            delete dateOfVaccination;
        }else{
            delete citizen;
        }

        legalLines--;

    }else{

        string* countryPtr = (string*)countryHash->insertToHash(country);
        string* virusPtr = (string*)virusHash->insertToHash(virus);
        citizen->initCountry(countryPtr);
        citizen->initVirus(virusPtr);
        //citizen->updateArrays(virusPtr, vaccinated, dateOfVaccination);
        personsArray[legalLines] = citizen;

    }

    while(getline(myfile, line)) {

        int flag = 0;       
        if( myfile.eof() ) break;
        myfile >> id >> name >> surname >> age >> country >> virus >> vaccinated;

        if(vaccinated.compare("NO") == 0){

            citizen = new person(id, name, surname, age, vaccinated);
            faulty = citizen->checkRecord();
            //not surre if this is helpful...
            if(faulty == 1){
                cout << "Error illegal record: \n";
                citizen->printData();
                cout << endl;
                delete citizen;
                continue;
            }

            string* countryPtr = (string*)countryHash->insertToHash(country);
            string* virusPtr = (string*)virusHash->insertToHash(virus);
            citizen->initCountry(countryPtr);
            citizen->initVirus(virusPtr);

        }else{

            myfile >> sdate;
            
            string myText(sdate);
            istringstream iss(myText);
            string token;
        
            getline(iss, token, '-');
            int day = stoi(token);
        
            getline(iss, token, '-');
            int month = stoi(token);
        
            getline(iss, token, '-');
            int year = stoi(token);

            dateOfVaccination = new date(day,month,year);
            citizen = new person(id, name, surname, age,"YES",NULL, NULL,dateOfVaccination);
            faulty = citizen->checkRecord();

            if(faulty == 1){
                cout << "Error illegal record: \n";
                citizen->printData();
                cout << endl;
                delete citizen;
                delete dateOfVaccination;
                continue;
            }
            
            string* countryPtr = (string*)countryHash->insertToHash(country);
            string* virusPtr = (string*)virusHash->insertToHash(virus);
            citizen->initCountry(countryPtr);
            citizen->initVirus(virusPtr); 
        }

        legalLines++;

        if(legalLines <= numLines){
            personsArray[legalLines] = new person(citizen);
            delete citizen;
        }
    } 
    legalLines++;

    if(legalLines < numLines){
        person** updatedPerson = (person**)(malloc((legalLines)*sizeof(person*)));

        for(int i = 0; i < legalLines; i++){
            updatedPerson[i] = personsArray[i];
        }

        free(personsArray);
        personsArray = NULL;
        personsArray = updatedPerson;
    }

    hashTable* citizenHash = new hashTable(legalLines);   
    
    int updateBuckets = countryHash->checkHash();
    hashTable* updateCountryHash = NULL;

    if(updateBuckets > 0 ){

        updateCountryHash = new hashTable(updateBuckets);
        (*updateCountryHash) = (*countryHash); 

        linkedListNode** array = countryHash->getArray();
        
        for(int i = 0; i < countryHash->getNumBuckets(); i++){
            delete array[i];
        }

        delete [] array;
        countryHash->array = NULL;
        delete countryHash;

        countryHash = NULL;
        countryHash = updateCountryHash;
    }

    updateBuckets = virusHash->checkHash();
    hashTable* updateVirusHash = NULL;

    if(updateBuckets > 0 ){

        updateVirusHash = new hashTable(updateBuckets);
        (*updateVirusHash) = (*virusHash); 
        linkedListNode** array = virusHash->getArray();

        for(int i = 0; i < virusHash->getNumBuckets(); i++){
            delete array[i];
        }

        delete [] array;

        virusHash->array = NULL;
        delete virusHash;

        virusHash = NULL;
        virusHash = updateVirusHash;
    }

    int i = 0;

    for(int k = 0; k < legalLines; k++){
        if(personsArray[k] != NULL){
            
            if(citizenHash->insertToHash(personsArray[k]) == 0){
                delete personsArray[k];
                personsArray[k] = NULL;
            }
            if(personsArray[k] != NULL)
                if(personsArray[k]->getId() == 8201) personsArray[k]->printData();
        }
    }
    
    cout << "\n****************************************************\n";

    citizenHash->initSkipListBloomFilter(bloomSize,virusHash);

    inputCheck(&virusHash, &citizenHash, &countryHash, legalLines, personsArray);
    
    return 0;
}