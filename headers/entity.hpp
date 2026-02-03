#pragma once
#include <string>
#include <vector>

using namespace std;

class Entity {
    public:
        static string get_random_name(vector<string> names){return names[rand()%names.size()];}
    protected:
        string id;
        string name;
    public:
        Entity(){};
        Entity(const string& id, const string& name): id(id), name(name){}
        string get_id(){return this->id;}
        string get_name(){return this->name;}

        
};
