#pragma once
#include <ctime>
#include "entity.hpp"
#include <vector>

class Employee : public Entity
{   
    public:
        static vector<string> names;
    private: 
        int salary;
        int grooming_skill_level;
        int marketing_skill_level;
        int caretaking_skill_level;
        int work_capacity = 8;
        bool isFree = true;
        time_t last_order_given;
        int work_cost;

    public:
        Employee(){};
        Employee(const string& id, const string& name);
        Employee(const string& id, const string& name, int grooming_skill_level, int marketing_skill_level, int caretaking_skill_level, int salary);
        void work(int hours);
        void assignTask(int work_cost, time_t startTime);
        static void get_names_from_file();
        int get_grooming_skill_level(){return this->grooming_skill_level;}
        int get_marketing_skill_level(){return this->marketing_skill_level;}
        int get_caretaking_skill_level(){return this->caretaking_skill_level;}
        int get_salary(){return this->salary;}
};
