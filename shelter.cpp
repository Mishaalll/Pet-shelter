#include "shelter.hpp"



Shelter::Shelter(time_t prev_time, time_t current_time, time_t prev_income_time, int bank_account, int montly_income)
{
    this->prev_time = prev_time;
    this->current_time = current_time;
    this->prev_income_time = prev_income_time;
    this->bank_account = bank_account;
    this->monthly_income = monthly_income;
    // get current month 1 day as timestamp
    //struct tm * timeinfo;
    
    //time_t rawtime;
    //time ( &rawtime );
    //timeinfo = localtime ( &rawtime );
    //timeinfo->tm_mday = 1;
    //prev_income_time = mktime(timeinfo);
    

}
void Shelter::addPet(Pet* pet)
{
    pets.push_back(pet);
}
void Shelter::addEmployee(Employee* employee)
{
    employes.push_back(employee);
}

bool Shelter::update()
{

    time_t deltaTime = (current_time - prev_time)/3600;
    cout << "hours since last enterence: " << deltaTime << endl;
    if(deltaTime > 0)
    {
        //upadete pets stats
        for(int i = 0; i < deltaTime; i++)
        for(Pet* pet : pets)
        {
            pet->update_attractivenes();
            pet->update_hunger();
            pet->update_happines();
        }
        
        vector<Task*> tasks_to_delete;
        for(Task* task: tasks)
        {
            Employee curr_employee;
            for(Employee* temp_emp : this->employes)
            {
                if(temp_emp->get_id().compare(task->employee_id) == 0)
                curr_employee = *temp_emp;
            }
    
            int passed_time_spent_on_work = 0;
            if(deltaTime >= task->duration)
            {
                passed_time_spent_on_work = task->duration;
            }
            else if(deltaTime < task->duration)
            {
                passed_time_spent_on_work = deltaTime;
            }
            switch(task->task_type)
            {

                case GROOM:
                    for(Pet* pet : pets)
                    {                      

                        int curr_attr = pet->get_attractivenes();
                        cout << "current attractiveness: "<< curr_attr << endl;
                        if(curr_attr < 900)
                            {
                                if(deltaTime >= task->duration)
                            {
                                passed_time_spent_on_work = task->duration;
                                deltaTime-=task->duration;
                            }
                            else if(deltaTime < task->duration)
                            {
                                cout << "we are here" << endl;
                                passed_time_spent_on_work = deltaTime;
                                deltaTime = 0;
                            }
                            int lacking_attr = 1000-curr_attr;
                            cout << "lacking attractiveness: "<< lacking_attr << endl;
                            if(lacking_attr/100<=passed_time_spent_on_work)
                            {
                                pet->groom(lacking_attr*(curr_employee.get_grooming_skill_level()/10.0));
                                task->duration -= lacking_attr/100;
                            }
                            else if(lacking_attr/100>passed_time_spent_on_work)
                            {
                                cout << "*************************" <<endl;
                                cout << passed_time_spent_on_work << endl
                                    << lacking_attr << endl
                                    <<task->duration << endl;
                                pet->groom(passed_time_spent_on_work*100*(curr_employee.get_grooming_skill_level()/10.0));
                                task->duration -=passed_time_spent_on_work;

                                cout << passed_time_spent_on_work << endl
                                    << lacking_attr << endl
                                    <<task->duration << endl;
                                cout << "*************************" <<endl;
                            }
                        }
                        if( task->duration <= 0 | deltaTime <= 0)
                        {
                            break;
                        }
                        
                    }
                    break;
                case ADVERTISE:
                    float mark_coef = curr_employee.get_marketing_skill_level()/10.0;
                    for(int i = 0; i<passed_time_spent_on_work; i++)
                    {
                        float rand_val = rand()*1.0 / RAND_MAX;
                        if(rand_val < mark_coef)
                        {
                            if(rand()*1.0 / RAND_MAX > 0.01)
                            {
                                int mood = rand()%2000; // if mood is 0 - any pet would be taken from the shelter
                                for(Pet* pet : pets)
                                {
                                    if(mood < (pet->get_attractivenes() + pet->get_happines()))
                                    {
                                        pets.erase(find(pets.begin(),pets.end(),pet));
                                        break;
                                    }
                                }
                            }
                            else
                            {
                                this-> monthly_income += curr_employee.get_marketing_skill_level();
                            }
                        }
                    }

                    break; 
                case TAKE_CARE:
                    for(Pet* pet : pets)
                    {
                        pet->increase_happines(passed_time_spent_on_work * 100*(curr_employee.get_grooming_skill_level()/10.0));
                    }
                    task->duration-=passed_time_spent_on_work;
                    break;
                case FEED:
                    for(Pet* pet : pets)
                    {
                        pet->feed(passed_time_spent_on_work * 10);
                    }
                    task->duration-=passed_time_spent_on_work;
                    break;
            }

            
            if(task->duration == 0)
            {
                tasks_to_delete.push_back(task);
            }
        }
        for(Task* task: tasks_to_delete)
        {
            tasks.erase(find(tasks.begin(),tasks.end(),task));
        }

        // check last time income came to account
        
        //convert last time income to tm structure
        struct tm* tm_prev_inc =  localtime(&this->prev_income_time);
        //convert current time to tm structure
        struct tm* tm_cur_time =  localtime(&this->current_time);
        //substract month numbers
        //if result is > 0      
        if(abs(tm_cur_time->tm_mon - tm_prev_inc->tm_mon )>0)
        {
            // add monthy income to account 
            this->bank_account += this->monthly_income;
            // set last time income came to account (last time income came to account + 1m)
            tm_prev_inc->tm_mon++;
            prev_income_time = mktime(tm_prev_inc);
            for(Employee* temp_emp : employes)
            {
                this->bank_account -= temp_emp->get_salary();
            }
        }
     
            // substract employee salaries from bank account

        return true;
    }
    return false;
    
}

void Shelter::show_pet_stats(Pet* pet)
{
    cout << "Alive: " << pet->get_alive_status() << endl;
    cout <<"attractivenes: " << pet->get_attractivenes() << endl;
    cout <<"hunger: " << pet->get_hunger() << endl;
    cout <<"happines: " << pet->get_happines() << endl;
    
}

void Shelter::show_pets_stats()
{   int i = 1;
    for(Pet* pet : pets)
    {   
        cout << "pet number: " << i++ << endl;
        show_pet_stats(pet);
    }
}

void Shelter::addNewTask(const string& employee_id, Task_type task_type, int duration)
{
    
    for(Task* temp_task: tasks)
    {
        if(temp_task->employee_id.compare(employee_id) == 0)
        {
            cout << "Current Employee is already bussy" << endl;
            return;
        }
    }

    this->tasks.push_back(new Task(to_string(this->tasks.size()),employee_id,task_type,duration));

}

void Shelter::showTasks()
{
    for(Task* task: tasks)
    {    
        cout << task->id << " " << task->employee_id << " " << enum_to_string(task->task_type) << " "  << task->duration << endl;
    }
}

void Shelter::show_employes()
{

    for(Employee* empl : employes)
    {
        cout << "id: " << empl->get_id() <<endl;
        cout << "name: " << empl->get_name() <<endl;
        cout << "grooming skill: " << empl->get_grooming_skill_level() <<endl;
        cout << "marketing skill: " << empl->get_marketing_skill_level() <<endl;
        cout << "caretaking skill: " << empl->get_caretaking_skill_level() <<endl;
    }
}


