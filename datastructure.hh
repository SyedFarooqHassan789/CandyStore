// Definition of Datastructure class for UDS/Tiraka homework 2 -


#ifndef DATASTRUCTURE_HH
#define DATASTRUCTURE_HH

#include <string>
#include <vector>
#include <iostream>
using std::string;

const std::string NOT_AVAILABLE = "Product not in warehouse.";
const std::string NOT_ENOUGH_CANDY = "Not enough candy available.";

class Datastructure
{
    public:

    Datastructure();

    ~Datastructure();

    // Adds candies to the datastructure (command "A")
    void add(const std::string& ID, const std::string& location,
            unsigned int amount, const std::string& name);

    // Removes candies from the datastructure (command "D")
    void substract(const std::string& ID, unsigned int amount);

    // Finds candy and prints its status (command "F")
    void find(const std::string& ID) const;

    // Returns how many different types of candy the datastructure contains (command "C")
    size_t count() const;

    // Empties the datastructure (command "E")
    void empty();

    // my functions
    int hash(int id) const; //taking mod
    int findkey(string key) const; // function to find index of hashtable
    void resizevector(int size_of_vector);
    void print();

    // Copy constructor is forbidden (not important for this assignment)
    Datastructure(const Datastructure&) = delete;
    // Assignment operator is forbidden (not important for this assignment)
    Datastructure& operator=(const Datastructure&) = delete;

private:

    // Add your own implementation here
struct warehouseinfo{
    std::string id_candy;
    std::string location_of_candy;
    unsigned int amount_of_candy;
    std::string name_of_candy;
    warehouseinfo()
    {
        id_candy = "";
        location_of_candy = "";
        amount_of_candy = 0;
        name_of_candy = "";
    }
};
mutable bool idequal=false;
std::vector<warehouseinfo> choclatestore;
unsigned int countvalues;
std:: string prevvaluetemp ="";
int newindex;
};

#endif
