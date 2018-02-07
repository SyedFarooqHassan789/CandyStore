#include "datastructure.hh"
#include "string.h"
using namespace std;
// Empty implementations for public interface, modify and add your own code here

Datastructure::Datastructure()
{
    choclatestore.resize(1000);
    countvalues = 0;
}

Datastructure::~Datastructure()
{
}

void Datastructure::add(const string& ID, const string& location,
    unsigned int amount, const string& name)
{
    warehouseinfo info;
    info.id_candy = ID;
    info.location_of_candy = location;
    info.amount_of_candy = amount;
    info.name_of_candy = name;

    if (countvalues >= choclatestore.size() / 2) {
        countvalues = 0;
        resizevector(choclatestore.size() * 10);
    }
    int sum = findkey(ID);
    unsigned int index = hash(sum);

    if (choclatestore.at(index).name_of_candy == "") {
        countvalues += 1;
        choclatestore.at(index) = info;
    }
    else if (ID == choclatestore.at(index).id_candy && choclatestore.at(index).name_of_candy != "") {
        choclatestore.at(index).amount_of_candy += amount;
    }
    else {
        for (unsigned int i = (index + 1) % choclatestore.size(); i != index; i = (i + 1) % choclatestore.size()) {
            if (ID == choclatestore.at(index).id_candy) {
                choclatestore.at(index).amount_of_candy += amount;
                break;
            }
            else {
                if (choclatestore.at(i).name_of_candy == "") {
                    countvalues += 1;
                    choclatestore.at(i) = info;
                    break;
                }
            }
        }
    }
}
void Datastructure::substract(const string& ID, unsigned int amount)
{
    int sum = findkey(ID);
    unsigned int index = hash(sum);
    if (choclatestore.at(index).amount_of_candy != 0 && choclatestore.at(index).amount_of_candy >= amount) {
        choclatestore.at(index).amount_of_candy = choclatestore.at(index).amount_of_candy - amount;
        cout << "Amount: " << choclatestore.at(index).amount_of_candy << " Shelf: " << choclatestore.at(index).location_of_candy << "\n";
        if (choclatestore.at(index).amount_of_candy == 0) {
            countvalues = countvalues - 1;
        }
    }
    else if (choclatestore.at(index).amount_of_candy <= amount) {
        cout << NOT_ENOUGH_CANDY << "\n"
             << "Amount: " << choclatestore.at(index).amount_of_candy << " Shelf: " << choclatestore.at(index).location_of_candy << "\n";
    }
    else {
        for (unsigned int i = (index + 1) % choclatestore.size(); i != index; i = (i + 1) % choclatestore.size()) {
            if (ID == choclatestore.at(i).id_candy && choclatestore.at(i).amount_of_candy >= amount) {
                choclatestore.at(i).amount_of_candy = choclatestore.at(i).amount_of_candy - amount;
                cout << "Amount: " << choclatestore.at(i).amount_of_candy << " Shelf: "
                     << choclatestore.at(i).location_of_candy << "\n";
                if (choclatestore.at(i).amount_of_candy == 0) {
                    countvalues = countvalues - 1;
                }
                break;
            }
            else {
                if (choclatestore.at(i).name_of_candy == "") {
                    cout << NOT_AVAILABLE << "\n";
                    break;
                }
            }
        }
    }
}

void Datastructure::find(const string& ID) const
{
    int sum = findkey(ID);
    unsigned int index = hash(sum);
    if (choclatestore.at(index).id_candy == ID && choclatestore.at(index).amount_of_candy != 0) {
        cout << choclatestore.at(index).name_of_candy << " " << choclatestore.at(index).amount_of_candy << " " << choclatestore.at(index).location_of_candy << "\n";
    }
    else if (choclatestore.at(index).name_of_candy == "" || choclatestore.at(index).amount_of_candy == 0) {
        cout << NOT_AVAILABLE << "\n";
    }
    else {
        for (unsigned int i = (index + 1) % choclatestore.size(); i != index; i = (i + 1) % choclatestore.size()) {
            if (ID == choclatestore.at(i).id_candy) {
                cout << choclatestore.at(i).name_of_candy << " " << choclatestore.at(i).amount_of_candy
                     << " " << choclatestore.at(i).location_of_candy << "\n";
                break;
            }
            else {
                if (choclatestore.at(i).name_of_candy == "") {
                    cout << NOT_AVAILABLE << "\n";
                    break;
                }
            }
        }
    }
}

size_t Datastructure::count() const
{
    return (size_t)countvalues;
}

void Datastructure::empty()
{
    choclatestore.clear();
    choclatestore.resize(1000);
    countvalues = 0;
}
int Datastructure::hash(int id) const
{ //taking mod
    return (id % choclatestore.size());
}
//My functions starts from here

int Datastructure::findkey(string key) const
{ // function to find index of hashtable
    int has = 5381;
    unsigned int i;

    for (has = i = 0; i < key.size(); i++) {
        has = ((has << 5) + has) + key[i];
    }
    has *= has;
    has /= 100;
    return has;
}
void Datastructure::resizevector(int size_of_vector)
{ //resizing vector size according to data
    vector<warehouseinfo> tempvector;
    tempvector.resize(choclatestore.size());

    for (unsigned int i = 0; i < choclatestore.size(); i++) {
        tempvector.at(i) = choclatestore.at(i);
    }

    choclatestore.resize(size_of_vector);

    for (unsigned int i = 0; i < choclatestore.size(); i++) {
        choclatestore.at(i).name_of_candy = "";
    }
    for (unsigned int i = 0; i < tempvector.size(); i++) {

        if (tempvector.at(i).name_of_candy != "") {
            add(tempvector.at(i).id_candy, tempvector.at(i).location_of_candy,
                tempvector.at(i).amount_of_candy, tempvector.at(i).name_of_candy);
        }
    }
}
