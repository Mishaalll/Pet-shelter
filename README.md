## 1. File `src/employee.cpp`
This file is responsible for the employees (`"employee"`).

*   `"vector<string> Employee::names;"` — Static global vector storing employee names.

1.  **`"Employee(const string& id, const string& name)"`**
    *   Calls the base class constructor `"Entity"`.
    *   Generates random skill levels in the range of 1 to 10.
    *   Calculates `"salary"` as the sum of all skills plus a random number from -10 to 10, multiplied by 100.

2.  **`"Employee(...)` (Load constructor)"**
    *   Used when loading data from a save file.
    *   Initializes all fields such as ID, name, skills, and salary with specific passed values.

*   **`"void work(int hours)"`**
    *   Reduces the `"work_capacity"` parameter (employee stamina) by the number of hours worked.
    *   Contains a check: if the value drops below zero, it is set to 0.

*   **`"void assignTask(int work_cost, time_t startTime)"`**
    *   Assigns a task to an employee.
    *   Saves the task difficulty and start time.
    *   Sets the flag `"isFree = false"` (employee availability status).

*   **`"void get_names_from_file()"`**
    *   Opens the file `"employee_names.txt"`.
    *   Reads available names line-by-line inside a `"while(getline(...))"` loop.
    *   Adds each read name to the static vector `"names"`.


## 2. File `src/pet.cpp`
This file is responsible for the shelter pets (`"pet"`).

1.  **`"Pet(const string& id, const string& name)"`**
    *   Creates a new pet.
    *   Generates random parameters for the pet:
        *   `"happines"` from 0 to 1000.
        *   `"hunger"` from 1 to 100.
        *   `"attractivenes"` from 0 to 1000.

2.  **`"Pet(...)"`**
    *   Loads a pet with saved characteristics.
    *   **Important check:** If `"hunger"` >= 100, the flag `isAlive = false` is set, meaning the pet has died of starvation.

*   **`"void increase_happines(int amount)"`**
    *   If the pet is alive, increases its happiness.
    *   Sets a maximum happiness limit of 1000.

*   **`"void update_happines()"`**
    *   Reduces pet happiness. Called once per hour.
    *   Decreases value by 1, minimum 0.

*   **`"void feed(int amount)"`**
    *   Reduces the pet's hunger level by the passed amount. Minimum value is 0.

*   **`"void update_hunger()"`**
    *   Hunger growth. Called once per hour.
    *   Increases hunger by 1 each time.
    *   If hunger reaches 100, the pet dies of starvation (more details in `"Pet(...)"`), changing the flag to `"isAlive = false"`.

*   **`"void update_attractivenes()"`**
    *   Decay of attractiveness.
    *   Decreases value by 1. Minimum 0.


## 3. File `src/shelter.cpp`

*   Responsible for the shelter state and income.

*  `"update()"` - runs the simulation for the skipped time.

1.  **Time Calculation:**
    *   `"deltaTime"` is calculated as the difference between the current time and the last launch time in hours `"/ 3600"`.
    *   Outputs the number of passed hours to the console.

2.  **Passive Update (if time passed > 0 hours):**
    *   A `for` loop runs for the number of passed hours.
    *   For each pet, the functions `"update_attractivenes"`, `"update_hunger"`, and `update_happines` are called.

3.  **Task Processing (`"Tasks"`):**
    *   Iterates through the list of active tasks.
    *   Finds the employee by their ID.
    *   Determines how much time was spent on the task `"passed_time_spent_on_work"`: the minimum between the task duration and the passed `"deltaTime"`.

    *   **Switch by task types:**
        *   **`"GROOM"`:**
            *   Checks pet attractiveness. If the value is less than 900, work begins.
            *   Calculates how many points are needed for max attractiveness `"lacking_attr"`.
            *   If there is enough time, restores it to the maximum. If not, partially restores it proportional to the employee's skill.
            *   Reduces the remaining duration of the task.
        *   **`"ADVERTISE"`:**
            *   Uses the `"marketing"` skill.
            *   Every hour, with a certain probability, it either sells a pet (removes it from the `"pets"` vector) or generates direct income (`"monthly_income"`).
            *   Sale condition: random buyer mood must be less than the sum of the pet's attractiveness and happiness.
        *   **`"TAKE_CARE"`:**
            *   Increases the happiness value of all pets using the employee's `"caretaking"` skill.
        *   **`"FEED"`:**
            *   Decreases the hunger value of pets.

    	*   Removes completed tasks where `"duration == 0"`.

4.  **`"Economy"`:**
    *   Compares the month of the last income with the current month.
    *   If the month has changed, adds `"monthly_income"` to the account, updates the last income timestamp, and subtracts the salaries (`"salary"`) of all employees from the `"bank_account"`.

**`Misc`:**
*   **`"addNewTask"`**: Checks the employee's availability status. If free, creates a new `"Task"` object and adds it to the list.
*   **`"showTasks"`, `"show_employes"`, `"show_pets_stats"`**: Methods for outputting information to the console, acting as a UI.


## 4. File `src/main.cpp`

The core of the program, responsible for initialization.

1.  **Reading name files:** Calls static functions `"Pet::get_names_from_file"` and `"Employee::get_names_from_file"`.
2.  **Reading `"game_data.txt"`:**
    *   File is opened with an `"ifstream"` stream.
    *   Reads the last launch time `"prev_time"`.
    *   Reads the current system time `"timestamp"`.
    *   Reads economic indicators (account balance and income from the shelter).
    *   Creates the `"Shelter"` object.

3.  **Loading Objects:**
    *   Reads the number of pets via a `for` loop, creates `"Pet"` objects via `new`, and adds them to the `"shelter"` object.
    *   Reads the number of employees via a `for` loop, creates `"Employee"` objects, and adds them to the `"shelter"` object.
    *   Reads the number of tasks via a `for` loop, then creates and adds tasks.

*   `"shelter.update()"`: Calculates everything that happened between program launches.

4.  **`CLI Arguments in Command Line`:**
    *   Checks `if(argc > 1)`.
    *   If arguments exist (e.g., `"./shelter 0 FEED 5"`), the program attempts to add a new task:
    	1.  `argv[1]` — Employee ID.
    	2.  `argv[2]` — Task type, converted by the function `"string_to_enum"`.
    	3.  `argv[3]` — Duration.
    *   The task is added using `"shelter.addNewTask"`.

5. **`Saving Progress`:**
*   The file `"game_data.txt"` is opened with the `"trunc"` flag, which completely overwrites it.
*   If the update was successful, `"update"` should return `"true"`, and the new time `"timestamp"` is written. Otherwise, nothing changes.
*   Sequentially writes economy data, quantity and data of pets, quantity and data of employees, and quantity and data of active tasks.
*   Outputs final statistics to the console.
*   The program terminates with `"return 0"`.


## 5. `Headers`

### 1. `headers/task.hpp`:
*   **`"enum Task_type"`**: Enumeration of tasks `"GROOM"`, `"ADVERTISE"`, `"TAKE_CARE"`, and `"FEED"`.
*   **`"string_to_enum"`**: Helper function. Converts a string to uppercase and maps it to the `"enum"`. Needed for processing command-line arguments.
*   **`"class Task"`**: Simple data structure for storing task information (ID, who does it, what they do, how much time, etc.).

### 2. `headers/entity.hpp`:
*   Base class for `"Pet"` and `"Employee"`.
*   Stores common fields `"id"` and `"name"`.

### 3. `headers/employee.hpp` and `pet.hpp`:
*   Class declarations.
*   Inherit from `"Entity"`.
*   Describe characteristic fields and prototypes of methods implemented in the `.cpp` files.
