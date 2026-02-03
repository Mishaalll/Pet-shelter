#pragma once
#include <vector>
#include "pet.hpp"
#include "employee.hpp"
#include "task.hpp"
#include <ctime>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

class Shelter{

    private:
        vector<Pet*> pets;
        vector<Employee*> employes;
        vector<Task*> tasks;
        time_t prev_time;
        time_t current_time;
        int bank_account;
        int monthly_income = 0;
        time_t prev_income_time; //Www Mmm dd hh:mm:ss yyyy
    public:
        Shelter(time_t prev_time, time_t current_time, time_t prev_income_time, int bank_account, int montly_income);
        void addPet(Pet* pet);
        void addEmployee(Employee* employee);
        bool update();
        void show_pet_stats(Pet* pet);
        void show_pets_stats();
        void show_employes();
        void addNewTask(const string& employee_id, Task_type task_type, int duration);
        void showTasks();
        time_t getPrevIncTime(){return this->prev_income_time;};
        int get_bank_account(){return this->bank_account;}
        int get_monthly_income(){return this->monthly_income;}
        vector<Task*> getTasks(){return this->tasks;};
        vector<Pet*> get_pets(){return this->pets;};
        vector<Employee*> get_employes(){return this->employes;};


};
