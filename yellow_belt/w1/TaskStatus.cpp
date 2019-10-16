#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <map>

using namespace std;
// Перечислимый тип для статуса задачи
//enum class TaskStatus {
//    NEW,          // новая
//    IN_PROGRESS,  // в разработке
//    TESTING,      // на тестировании
//    DONE          // завершена
//};

map <int, TaskStatus> index_to_task{
        {0, TaskStatus::NEW},
        {1, TaskStatus::IN_PROGRESS},
        {2, TaskStatus::TESTING},
        {3, TaskStatus::DONE}
};

map <TaskStatus , int> task_to_index{
        {TaskStatus::NEW, 0},
        {TaskStatus::IN_PROGRESS, 1},
        {TaskStatus::TESTING, 2},
        {TaskStatus::DONE, 3}
};

TaskStatus Next(const TaskStatus& st){
    return index_to_task[ task_to_index[st]+1];
}

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
//using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
public:
    // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo& GetPersonTasksInfo(const string& person) const{
        return dev_tasks.at(person);
    }

    // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void AddNewTask(const string& person){
        ++dev_tasks[person][TaskStatus::NEW];
    }

    // Обновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(
            const string& person, int task_count){
        TasksInfo updated_tasks;
        TasksInfo old_tasks;
        for (auto& category_status: dev_tasks[person]){

            // write old task counter
            if (category_status.second > task_count && category_status.first != TaskStatus::DONE){
                int n_old_tasks = category_status.second - task_count;
                old_tasks[category_status.first] = n_old_tasks;
            }

            // write updated_task counters
            if (task_count > 0){
                if (category_status.second > 0){
                    int n_updated = (category_status.second > task_count ? task_count : category_status.second );

                    if (category_status.first != TaskStatus::DONE){
                        updated_tasks[Next(category_status.first)] = n_updated;
                    }
                    task_count = task_count  > category_status.second ? task_count - category_status.second : 0;

                }
            }
        }

        int done_buffer = dev_tasks[person][TaskStatus::DONE];
        dev_tasks[person] = {}; // clear all records
        if (done_buffer > 0){
            dev_tasks[person][TaskStatus::DONE] = done_buffer;
        }
        // sum up content of updated and new
        for(const auto &category: updated_tasks)
            dev_tasks[person][category.first] += category.second;
        for(const auto &category: old_tasks)
            dev_tasks[person][category.first] += category.second;

        return tuple<TasksInfo , TasksInfo >(updated_tasks, old_tasks);
    }

private:
    map<string, TasksInfo> dev_tasks;
};

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
    cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
         ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
         ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
         ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main(){
    TeamTasks tasks;
    for (int i = 0; i < 5; ++i){
        tasks.AddNewTask("Alice");
    }
    tasks.PerformPersonTasks("Alice", 5);
    tasks.PerformPersonTasks("Alice", 5);
    tasks.PerformPersonTasks("Alice", 1);

    for (int i = 0; i < 5; ++i){
        tasks.AddNewTask("Alice");
    }
    TasksInfo updated_tasks, untouched_tasks;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 2);
    PrintTasksInfo(updated_tasks);
    PrintTasksInfo(untouched_tasks);
    cout << endl;
    PrintTasksInfo( tasks.GetPersonTasksInfo("Alice"));
    cout << endl;
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 4);
    PrintTasksInfo(updated_tasks);
    PrintTasksInfo(untouched_tasks);
    cout << endl;
    PrintTasksInfo( tasks.GetPersonTasksInfo("Alice"));
    cout << endl;

}

/*
 AddNewTasks Alice 5
PerformPersonTasks Alice 5
PerformPersonTasks Alice 5
PerformPersonTasks Alice 1
AddNewTasks Alice 5
PerformPersonTasks Alice 2
GetPersonTasksInfo Alice
PerformPersonTasks Alice 4
GetPersonTasksInfo Alice

Your output:
[]
[{"IN_PROGRESS": 5}, {}]
[{"TESTING": 5}, {}]
[{"DONE": 1}, {"TESTING": 4}]
[]
[{"IN_PROGRESS": 2}, {"NEW": 3, "TESTING": 7}]
{"NEW": 3, "IN_PROGRESS": 2, "TESTING": 7}
[{"IN_PROGRESS": 3, "TESTING": 1}, {"IN_PROGRESS": 1, "TESTING": 8}]
{"IN_PROGRESS": 4, "TESTING": 9}

Correct output:
[]
[{"IN_PROGRESS": 5}, {}]
[{"TESTING": 5}, {}]
[{"DONE": 1}, {"TESTING": 4}]
[]
[{"IN_PROGRESS": 2}, {"NEW": 3, "TESTING": 4}]
{"NEW": 3, "IN_PROGRESS": 2, "TESTING": 4, "DONE": 1}
[{"IN_PROGRESS": 3, "TESTING": 1}, {"IN_PROGRESS": 1, "TESTING": 4}]
{"IN_PROGRESS": 4, "TESTING": 5, "DONE": 1}
 */

//int main() {
//    TeamTasks tasks;
//    tasks.AddNewTask("Ilia");
//    for (int i = 0; i < 3; ++i) {
//        tasks.AddNewTask("Ivan");
//    }
//    cout << "Ilia's tasks: ";
//    PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
//    cout << "Ivan's tasks: ";
//    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
//
//    TasksInfo updated_tasks, untouched_tasks;
//
//    tie(updated_tasks, untouched_tasks) =
//            tasks.PerformPersonTasks("Ivan", 2);
//    cout << "Updated Ivan's tasks: ";
//    PrintTasksInfo(updated_tasks);
//    cout << "Untouched Ivan's tasks: ";
//    PrintTasksInfo(untouched_tasks);
//
//    tie(updated_tasks, untouched_tasks) =
//            tasks.PerformPersonTasks("Ivan", 2);
//    cout << "Updated Ivan's tasks: ";
//    PrintTasksInfo(updated_tasks);
//    cout << "Untouched Ivan's tasks: ";
//    PrintTasksInfo(untouched_tasks);
//
//    return 0;
//}


/*
Ilia's tasks: 1 new tasks, 0 tasks in progress, 0 tasks are being tested, 0 tasks are done
Ivan's tasks: 3 new tasks, 0 tasks in progress, 0 tasks are being tested, 0 tasks are done
Updated Ivan's tasks: 0 new tasks, 2 tasks in progress, 0 tasks are being tested, 0 tasks are done
Untouched Ivan's tasks: 1 new tasks, 0 tasks in progress, 0 tasks are being tested, 0 tasks are done
Updated Ivan's tasks: 0 new tasks, 1 tasks in progress, 1 tasks are being tested, 0 tasks are done
Untouched Ivan's tasks: 0 new tasks, 1 tasks in progress, 0 tasks are being tested, 0 tasks are done
 * */