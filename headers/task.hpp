#pragma once
#include <string>
#include <ctime>
#include <algorithm>
#include <cctype>

using namespace std;


enum Task_type
{
    ERROR,
    GROOM,
    ADVERTISE,
    TAKE_CARE,
    FEED
    

};

inline string enum_to_string(Task_type task)
{
    switch(task)
    {
        case Task_type::GROOM: return "GROOM";
        case Task_type::ADVERTISE: return "ADVERTISE";
        case Task_type::TAKE_CARE: return "TAKE_CARE";
        case Task_type::FEED: return "FEED";
    }
    return NULL;
}

inline Task_type string_to_enum(const string& task)
{
    string temp_task = task;
    transform(temp_task.begin(),temp_task.end(),temp_task.begin(),::toupper);

    if(temp_task.compare("GROOM") == 0)
    {
        return GROOM;
    }
    else if(temp_task.compare("ADVERTISE") == 0)
    {
        return ADVERTISE;
    }
    else if(temp_task.compare("TAKE_CARE") == 0)
    {
        return TAKE_CARE;
    }
    else if(temp_task.compare("FEED") == 0)
    {
        return FEED;
    }

    return ERROR;
}

class Task{
    
    public:
        string id;
        string employee_id;
        Task_type task_type;
        int duration;    
        Task(const string& id, const string& employee_id, Task_type task_type, int duration):
        id(id), employee_id(employee_id), task_type(task_type), duration(duration){}
        bool operator==(const Task& other) const {return id == other.id;}
        


};
