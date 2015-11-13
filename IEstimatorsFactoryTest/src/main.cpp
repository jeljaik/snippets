#include "EstimatorsFactory.h"
#include "IEstimator.h"

#include <iostream>
#include <vector>

void get_names(char* a[], int argc, std::vector<std::string>* names)
{
    for ( unsigned int i = 1; i<argc; i++ )
        names->push_back(a[i]);
}

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        std::cout << "Please specify a class name!" << std::endl;
        return 0;
    }

	IEstimator* p;

    // Get all queried classes in a vector
    std::vector<std::string> names;
    get_names(argv, argc, &names);

    for (std::vector<std::string>::iterator i = names.begin(); i != names.end(); i++)
    {
        p = EstimatorsFactory::create(*i);

        if(p != NULL)
            p->foo();
        else
            std::cout << "Class not found!" << std::endl;

        delete p;
    }

	return 0;
}

