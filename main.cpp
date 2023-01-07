#include<iostream>
#include<string.h>
#include<fstream>
#include<sstream>
#include<cstdlib>
using namespace std;

ifstream f;
std::ofstream out_en;
std::ofstream out_ro;

int nr, nrAct;

void createFile_names(int *nr){
    f.open("cast.csv");
    out_en.open("names.csv");
    out_ro.open("nume.csv");

    if(out_en.is_open() && out_ro.is_open()){

    string line = "";
    while(getline(f, line)){
        string name, role;
        *nr = *nr + 1;

        stringstream inputString(line);
        
        getline(inputString, name, ',');
        out_en << name << endl;
        out_ro << name << endl;
        getline(inputString, role, ',');
        if(role == "actor")
            nrAct++;
    }
    string figurant = "Extra";
    for (int i = 1; i <= 132; i++){
        out_en << "Extra" << " " << i << endl;
        out_ro << "Figurant" << " " << i << endl;
    }
    f.close();
    out_en.close();
    out_ro.close();
    }
    else
        throw "File could not be opened!";
}

void addBudget(int nrDays, float transport, long long makeup, long long lunch, long long hotel, long long drinks, long long booking, long long totalCost){
    out_en << nrDays << ',' << transport << "$" << ',' << (unsigned long long)makeup << "$" << ',' << (unsigned long long)lunch << "$"
           << "," << (unsigned long long)drinks << "$"
           << "," << (unsigned long long)booking << "$" << ',' << (unsigned long long)totalCost << "$" << endl;
    out_ro << nrDays << ',' << transport << "$" << ',' << (unsigned long long)makeup << "$" << ',' << (unsigned long long)lunch << "$"
           << "," << (unsigned long long)booking << "$" << ',' << (unsigned long long)totalCost << "$" << endl;
}

//clasa virtuala ce va fi folosita pentru calcularea diferitelor bugete mostenite 
class Budget{
    protected:
        float totalPerDay;
    public:
        virtual float cost(int nrDays){
            return this->totalPerDay * nrDays;
        }
        virtual void calcBudget(long long *budget, int nrDays){
            *budget = *budget + this->totalPerDay * nrDays;
        }
};

class Transport{
private:
    int nr_buses;
public:
    float cost;
    Transport(){
        if(nr % 50 != 0)
            this->nr_buses = nr / 50 + 1;
        else
            this->nr_buses = nr / 50;

        this->cost = (this->nr_buses * 5680) * 2; // calcularea si pentru drumul de intoarcere
        this->cost = this->cost * 0.21;
    }

    void calcBudget(long long *budget){
        *budget = *budget + this->cost;
    }
    ~Transport();
};
Transport ::~Transport(void){};

class Makeup : public Budget{
    public:
    Makeup(){
        totalPerDay = 0;
        srand((unsigned)time(NULL));
        for (int i = 0; i < nrAct; i++){
            int random = (1 + rand() % 4);
            switch(random){
                case 1:{
                    totalPerDay = totalPerDay + 230;
                    break;
                }
                case 2:{
                    totalPerDay = totalPerDay + 555;
                    break;
                }
                case 3:{
                    totalPerDay = totalPerDay + 345;
                    break;
                }
                case 4:{
                    totalPerDay = totalPerDay + 157;
                    break;
                }
                case 5:{
                    totalPerDay = totalPerDay + 55;
                    break;
                }
            }
        }
        totalPerDay = totalPerDay * 0.21;
    }
    ~Makeup();
};
Makeup::~Makeup(void){};

class Lunch : public Budget{
    public:
        Lunch(){
            totalPerDay = 0;
            srand((unsigned)time(NULL));
            for (int i = 0; i < nrAct; i++){
                int random = (1 + rand() % 2);
                switch(random){
                    case 1:{
                        totalPerDay = totalPerDay + 40;
                        break;
                    }
                    case 2:{
                        totalPerDay = totalPerDay + 33;
                        break;
                    }
                    case 3:{
                        totalPerDay = totalPerDay + 46;
                        break;
                    }
                }
            }
            totalPerDay = totalPerDay * 0.21;
        }
        ~Lunch();
};
Lunch::~Lunch(void){};

class Hotel : public Budget{
    public:
        Hotel(){
            if(nr%2 != 0)
                totalPerDay = (nr / 2 + 1) * 350;
            else
                totalPerDay = (nr / 2) * 350;

            totalPerDay = totalPerDay + (132 / 3) * 420;
            totalPerDay = totalPerDay * 0.21;
        }
        ~Hotel();
};
Hotel::~Hotel(void){};

class Drinks : public Budget{
    public:
        Drinks(){
            if((nr + 132) % 2 != 0)
                totalPerDay = ((nr + 132) / 2  + 1) * 44;
            else
                totalPerDay = ((nr + 132) / 2) * 44;
            totalPerDay = totalPerDay * 0.21;
        }
        ~Drinks();
};
Drinks::~Drinks(void){};

class Booking{
    public:
        long long budget;
    public:
        Booking(){
            budget = 0;
        }
        Booking(int nrDays){
            budget = 10000 * nrDays - 200 * (nrDays / 10);
            budget = budget * 0.21;
        }
        ~Booking();
};
Booking::~Booking(void){};

//Crearea maniului
//template general ce foloseste literele e,v,f, reprezentand tipul de persoana(mananca orice, vegetarian, flexitarian) cu care realizam meniul
//si generam fisierul in limba engleza cu meniul
template <class T>
void meniu(T x){
    switch(x){
        //eats anything
        case 'e':{
            //soup
            out_en << "Chicken soup" << ',' << "Tripe soup" << ',' << "Beef soup" << endl;
            // main course
            out_en << "Chicken breast with rice" << ',' << "Salami pizza" << ',' << "Indian butter chicken" << endl;
            // dessert
            out_en << "Tiramisu" << ',' << "Papanasi" << ',' << "Ice cream" << endl;

            break;
        }
        //vegetarian
        case 'v':{
            //soup
            out_en << "Creamy tomato soup with croutons" << ',' << "Creamy mushroom soup" << ',' << "Creamy broccoli soup" << endl;
            // main course
            out_en << "Hawaian pizza" << ',' << "Quattro formaggi pizza" << ',' << "Arrabiata pasta" << endl;
            // dessert
            out_en << "Ice cream" << ',' << "Lava cake" << ',' << "Chocolate cake" << endl;
            break;
        }
        //flexitarian
        case 'f':{
            //soup
            out_en<<"Fish soup"<<','<<"Seafood"<<','<<"Paella"<<endl;
            //main course
            out_en<<"Salmon with creamy dill sauce"<<','<<"Octopus with mashed potatoes"<<','<<"Cornmeal-crusted catfish"<<endl;
            //dessert
            out_en<<"Red velvet cake"<<','<<"Ice cream"<<','<<"Chocolate cookies and donuts"<<endl;
            break;
        }
    }
}

//template specializat pentru tipul int, ce foloseste numerele 1,2,3, reprezentand cele 3 tipuri de persoane(mananca orice,
//vegetarian si flexitarian) si va genera fisier in limba romana cu meniul
template <>
void meniu(int x){
    switch(x){
        //mananca orice
        case '1':{
            //supa
            out_ro << "Supa de pui" << ',' << "Ciorba de burta" << ',' << "Ciorba de vacuta" << endl;
            // fel principal
            out_ro << "Piept de pui cu orez" << ',' << "Pizza salami" << ',' << "Pui cu sos indian" << endl;
            // desert
            out_ro << "Tiramisu" << ',' << "Papanasi" << ',' << "Inghetata" << endl;

            break;
        }
        //vegetarian
        case '2':{
            //supa
            out_ro<<"Supa crema de rosii cu crutoane"<<','<<"Supa crema de ciuperci"<<','<<"Supa crema de broccoli"<<endl;
            //fel principal
            out_ro << "Pizza hawaiana" << ',' << "Pizza quattro formaggi" << ',' << "Paste arrabiata" << endl;
            // desert
            out_ro << "Inghetata" << ',' << "Lava cake" << ',' << "Tort de ciocolata" << endl;
            break;
        }
        //flexitarian
        case '3':{
            //supa
            out_ro << "Supa de peste" << ',' << "Fructe de mare" << ',' << "Paella" << endl;
            // fel principal
            out_ro << "Somon cu crema de marar" << ',' << "Caracatita cu piure de cartofi" << ',' << "File de somn in crusta de porumb" << endl;
            // desert
            out_ro << "Tort red velvet" << ',' << "Inghetata" << ',' << "Biscuiti si gogosi cu ciocolata" << endl;
            break;
        }
    }
}

int main()
{
    long long budget;
    int nrDays;

    try{
    createFile_names(&nr);
    }catch(const char *msg){
        cerr << msg << endl;
    }

    Transport transport;
    Makeup makeup;
    Lunch lunch;
    Hotel hotel;
    Drinks drinks;
    Booking booking;

    out_en.open("budget.csv");
    out_ro.open("buget.csv");

    //calculam bugetele pentru 30, 45, 60, 100 zile si le introducem in fisierle de en/ro cu bugete
    nrDays = 30;
    budget = 0;
    transport.calcBudget(&budget);
    makeup.calcBudget(&budget, 30);
    lunch.calcBudget(&budget, 30);
    hotel.calcBudget(&budget, 30);
    drinks.calcBudget(&budget, 30);
    Booking booking30(nrDays);
    addBudget(nrDays, transport.cost, makeup.cost(nrDays), lunch.cost(nrDays), hotel.cost(nrDays), drinks.cost(nrDays), booking30.budget, budget);

    nrDays = 45;
    budget = 0;
    transport.calcBudget(&budget);
    makeup.calcBudget(&budget, nrDays);
    lunch.calcBudget(&budget, nrDays);
    hotel.calcBudget(&budget, nrDays);
    drinks.calcBudget(&budget, nrDays);
    Booking booking45(nrDays);
    addBudget(nrDays, transport.cost, makeup.cost(nrDays), lunch.cost(nrDays), hotel.cost(nrDays), drinks.cost(nrDays), booking45.budget, budget);

    nrDays = 60;
    budget = 0;
    transport.calcBudget(&budget);
    makeup.calcBudget(&budget, nrDays);
    lunch.calcBudget(&budget, nrDays);
    hotel.calcBudget(&budget, nrDays);
    drinks.calcBudget(&budget, nrDays);
    Booking booking60(nrDays);
    addBudget(nrDays, transport.cost, makeup.cost(nrDays), lunch.cost(nrDays), hotel.cost(nrDays), drinks.cost(nrDays), booking60.budget, budget);

    nrDays = 100;
    budget = 0;
    transport.calcBudget(&budget);
    makeup.calcBudget(&budget, nrDays);
    lunch.calcBudget(&budget, nrDays);
    hotel.calcBudget(&budget, nrDays);
    drinks.calcBudget(&budget, nrDays);
    Booking booking100(nrDays);
    addBudget(nrDays, transport.cost, makeup.cost(nrDays), lunch.cost(nrDays), hotel.cost(nrDays), drinks.cost(nrDays), booking100.budget, budget);

    out_en.close();
    out_ro.close();

    out_en.open("menuEng.csv");
    out_ro.open("menuRo.csv");

    out_en << "Day One" << ',' << "Day Two" << ',' << "Day Three" << endl; // organizarea meniului pe zile
    out_ro << "Ziua 1" << ',' << "Ziua 2" << ',' << "Ziua 3" << endl;

    // folosire meniu pentru eats anything / mananca orice
    out_en << " " << ',' << "Eats anything" << endl;
    meniu<char>('e');
    out_ro << " " << ',' << "Mananca orice" << endl;
    meniu<int>('1');

    // folosire meniu pentru vegetarian
    out_en << " " << ',' << "Vegetarian" << endl;
    meniu<char>('v'); 
    out_ro<<" "<<','<<"Vegetarian"<<endl;
    meniu<int>('2');

    // folosire meniu pentru flexitarian
    out_en << " " << ',' << "Flexitarian" << endl;
    meniu<char>('f'); 
    out_ro<<" "<<','<<"Flexitarian"<<endl;
    meniu<int>('3');

    out_en.close();
    out_ro.close();
    return 0;
}