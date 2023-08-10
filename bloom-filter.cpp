
    #include "bloom-filter.h"
    #include <iostream>
    #include <string>
    #include <cstring>

    using namespace std;

    unsigned long bloomFilter:: djb2(unsigned char *str) {
        int c;
        unsigned long hash = 5381;

        while ((c = *str++))
            hash = ((hash << 5) + hash) + c; // hash * 33 + c

        return hash;
    }

    unsigned long bloomFilter:: sdbm(unsigned char *str) {
        int c;
        unsigned long hash = 0;

        while ((c = *str++))
            hash = c + (hash << 6) + (hash << 16) - hash;

        return hash;
    }

    unsigned long bloomFilter:: hash_i(unsigned char *str, unsigned int i) {
	    return ((djb2(str) + i * sdbm(str) + i * i));
    }

    bloomFilter::bloomFilter(int bytes){
        this->array = (uint8_t*)malloc(bytes*1024*sizeof(uint8_t));
        this->length = bytes * 1024;
        
        for(int i = 0; i < this->length; i++){
            this->array[i] = 0;
        }
    }

    bloomFilter::~bloomFilter(){
        free(this->array);
        this->array = NULL;
        this->length = 0;
    }

    int bloomFilter::getLength(){
        return this->length;
    }

    int bloomFilter::search(string str){
        int n = str.length();
        char char_array[n + 1];
        char_array[n+1] = '\0';
        strcpy(char_array, str.c_str());
        int K = 16;
        int values[K];
        for(int i = 0; i < K; i++){
            values[i] = hash_i((unsigned char*)char_array, i) % this->length;
        }
        for(int i = 0; i < K; i++){
            if(!this->array[values[i]]){
                return 0;
            }
        }
        return 1;
    }   

    uint8_t* bloomFilter::getArray(){
        return this->array;
    }

    int bloomFilter::insert(string str){
        int n = str.length();
        char char_array[n + 1];
        char_array[n+1] = '\0';
        strcpy(char_array, str.c_str());
        int K = 16;
        int values[K];
        for(int i = 0; i < K ; i++){
            values[i] = hash_i((unsigned char*)char_array, i) % this->length;
            //cout <<values[i]<<endl;
        }
        for(int i = 0; i < K; i++){
            this->array[values[i]] = 1;
        }
    }
