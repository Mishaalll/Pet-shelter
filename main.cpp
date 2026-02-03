#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include "shelter.hpp"



using namespace std;

int main(int argc, char** argv)
{   
      

    string line;
    ifstream game_data;
    Pet::get_names_from_file();
    Employee::get_names_from_file();
    game_data.open("game_data.txt");
    
    getline(game_data,line);

    time_t prev_time = stoi(line,0,10);
    time_t timestamp; 
    time(&timestamp);


    getline(game_data,line);
    time_t prev_inc_time = stoi(line,0,10);

    getline(game_data,line);
    int bank_account = stoi(line,0,10);
    getline(game_data,line);
    int monthly_income = stoi(line,0,10);

    Shelter shelter(prev_time,timestamp,prev_inc_time,bank_account,monthly_income);
    

    getline(game_data,line);
    int pet_count = stoi(line,0,10);

    for(int i = 0; i< pet_count; i++)
    {   
        int temp_at;
        int temp_hun;
        int temp_hap;
        string temp_id;
        string temp_name;
        if(getline(game_data,line)){temp_id = line;}else{break;}
        if(getline(game_data,line)){temp_name = line;}else{break;}
        if(getline(game_data,line)){temp_at = stoi(line);}else{break;}
        if(getline(game_data,line)){temp_hun = stoi(line);}else{break;}
        if(getline(game_data,line)){temp_hap = stoi(line);}else{break;}
        Pet* test_pet = new Pet(temp_id, temp_name, temp_at,temp_hun,temp_hap);
        shelter.addPet(test_pet);

    }

    getline(game_data,line);
    int employes_count = stoi(line,0,10);

    for(int i = 0; i< employes_count; i++)
    {   
        int temp_gr;
        int temp_mr;
        int temp_ct;
        int temp_sl;
        string temp_id;
        string temp_name;
        if(getline(game_data,line)){temp_id = line;}else{break;}
        if(getline(game_data,line)){temp_name = line;}else{break;}
        if(getline(game_data,line)){temp_gr = stoi(line);}else{break;}
        if(getline(game_data,line)){temp_mr = stoi(line);}else{break;}
        if(getline(game_data,line)){temp_ct = stoi(line);}else{break;}
        if(getline(game_data,line)){temp_sl = stoi(line);}else{break;}
        Employee* temp_employee = new Employee(temp_id, temp_name, temp_gr,temp_mr,temp_ct,temp_sl);
        shelter.addEmployee(temp_employee);

    }

    if(getline(game_data,line))
    {
        int task_count = stoi(line,0,10);
        for(int i = 0; i< task_count; i++)
        {
            string temp_employee_id;
            Task_type temp_task_type;
            time_t temp_start_time;
            int temp_duration;
            if(getline(game_data,line)){;}else{break;}
            if(getline(game_data,line)){temp_employee_id = line;}else{break;}
            if(getline(game_data,line)){temp_task_type = Task_type(stoi(line));}else{break;}
            if(getline(game_data,line)){temp_duration = stoi(line);}else{break;}
            shelter.addNewTask(temp_employee_id,temp_task_type,temp_duration);
        }
    }

    game_data.close();
    
    bool update = shelter.update();
    
    if(argc > 1) //employee_id task_type duration ./shelter 0 FEED 5
    {
        
        Task_type tsk = string_to_enum(string(argv[2]));
        if(tsk)
        {
            cout << string(argv[1]) << tsk << stoi(argv[3]) << endl;
            shelter.addNewTask(string(argv[1]),tsk,stoi(argv[3]));
        }
        
    }
    
    if(true)
    {
        ofstream game_data;
        game_data.open("game_data.txt", ios::out | ios::trunc);
        if(update)
        {
            game_data << timestamp << endl;
        }
        else
        {
            game_data << prev_time << endl;
        }
        game_data << shelter.getPrevIncTime() << endl;
        game_data << shelter.get_bank_account() << endl;
        game_data << shelter.get_monthly_income() << endl;
        game_data << shelter.get_pets().size() << endl;
        for(Pet* pet: shelter.get_pets())
        {   
            game_data << pet->get_id() << endl;
            game_data << pet->get_name() << endl;
            game_data << pet->get_attractivenes() << endl;
            game_data << pet->get_hunger() << endl;
            game_data << pet->get_happines() << endl;
        }
        game_data << shelter.get_employes().size() << endl;
        for(Employee* employee: shelter.get_employes())
        {   
            game_data << employee->get_id() << endl;
            game_data << employee->get_name() << endl;
            game_data << employee->get_grooming_skill_level() << endl;
            game_data << employee->get_marketing_skill_level() << endl;
            game_data << employee->get_caretaking_skill_level() << endl;
            game_data << employee->get_salary() << endl;
        }
        if(shelter.getTasks().size() > 0)
        {
            game_data << shelter.getTasks().size() << endl;
            for(Task* task: shelter.getTasks())
            {
                game_data << task->id << endl; 
                game_data << task->employee_id << endl; 
                game_data << task->task_type << endl; 
                game_data << task->duration << endl;
            
            }
        }
        game_data.close();
    }
    shelter.show_pets_stats();
    shelter.show_employes();
    shelter.showTasks();

    return 0;

}