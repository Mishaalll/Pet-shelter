#include "pet.hpp"
#include <fstream>
vector<string> Pet::names;

Pet::Pet(const string& id, const string& name) : Entity(id,name)
{
    this->happines = rand() % 1001;
    this->hunger = 10 + rand() % 91;
    this->attractivenes = rand() % 1001;
}

Pet::Pet(const string& id, const string& name, int attractivenes, int hunger, int happines) 
: Entity(id,name), attractivenes(attractivenes), hunger(hunger), happines(happines)
{
    if(this->hunger>=100)
    {
        this->isAlive = false;
        this->hunger = 100;
    }
}

void Pet::name_pet(string name)
{
    this->name = name;
}

void Pet::get_names_from_file()
{
    ifstream pet_names_file;
    pet_names_file.open("pet_names.txt");
    string line;
    while(getline(pet_names_file,line))
    {
        Pet::names.push_back(line);
    }
}

void Pet::increase_happines(int amount)
{
    if(this->isAlive)
    {
        this->happines += amount;
        if(this->happines > 1000)
        {
            this->happines = 1000;
        }
    }
}

void Pet::update_happines()
{
    if(this->isAlive)
    {
        this->happines--;
        if(this->happines < 0)
        {
            this->happines = 0;
        }
    }
}

void Pet::feed(int amount)
{

    if(this->isAlive)
    {
        this->hunger -= amount;
        if(this->hunger < 0)
        {
            this->hunger = 0;
        }
    }
}

void Pet::update_hunger()
{
    if(this->isAlive)
    {
        this->hunger++;
        if(this->hunger >= 100)
        {
            this->isAlive = false;
            this->hunger = 100;
        }
    }
}

void Pet::update_attractivenes()
{
    if(this->isAlive)
    {
        this->attractivenes--;
        if(this->attractivenes < 0)
        {
            this->attractivenes = 0;
        }
    }
}
