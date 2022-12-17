#include "list.h"
#include <fstream>

int main(int argc, char **argv) {

    std::string filename = argv[1];
    std::ifstream in(filename);
    List mylist;
    int x;
    
    in >> x;
    if (in.fail()){
        std::cout << "file is empty" << std::endl;
        exit(-1);
    }
    while (!in.eof()) {
        mylist.addNode(x);
        in >> x;  
        if (in.fail()) {
            std::cout << "It must be at least two numbers in file" << std::endl;
        }
    }

    mylist.deleteElement(x);
    mylist.printLinkedList();
    return 0;

}