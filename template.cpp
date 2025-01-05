#include <iostream>
#include <fstream>

int main(){
    std::ifstream inputFile("./input.txt");
    int total = 0;
    if(inputFile.is_open()){
        std::string str_buffer;
        
        while( std::getline(inputFile, str_buffer) ){
            // do something
        }
    }

    std::cout << "total: " << total << std::endl;
    return 0;
}