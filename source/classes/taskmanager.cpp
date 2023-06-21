//! Cell's Tasks.
#if __has_include("taskmanager.hpp")
#   include "taskmanager.hpp"
#else
#   error "Cell's taskmanager was not found!"
#endif

#if __has_include("core/core.hpp")
#   include "core/core.hpp"
#else
#   error "Cell's core/core was not found!"
#endif

CELL_USING_NAMESPACE Cell;
CELL_USING_NAMESPACE Cell::System;
CELL_USING_NAMESPACE Cell::Utility;

CELL_NAMESPACE_BEGIN(Cell)

TaskManager::TaskManager(bool useFileStorage, const std::string& file)
    : useFileStorage(useFileStorage), dataFile(file)
{
    if (useFileStorage && !dataFile.empty()) {
        loadTasksFromFile();
    }
}

const TaskList& TaskManager::getTasks() const
{
    return tasks;
}

void TaskManager::addTask(const std::string& id,
                          const std::string& name,
                          const std::string& description,
                          int priority,
                          ActionHandler action,
                          const TimePoint& scheduledTime,
                          const TimePoint& reminderTime)
{

    if (id.empty() || name.empty() || description.empty() || priority < 1)
    {
        (DeveloperMode::IsEnable) ? Log("Invalid task parameters." , LoggerType::Critical) : DO_NOTHING;
        throw std::invalid_argument("Invalid task parameters.");
    }

    // Check for duplicate task name
    for (const Task& task : tasks) {
        if (task.taskInfo.id == id || task.taskInfo.name.value() == name) {
            (DeveloperMode::IsEnable) ? Log("A task with the same ID already exists." , LoggerType::Warning) : DO_NOTHING;
            throw std::runtime_error("A task with the same ID already exists.");
        }
    }

    tasks.push_back({ id, name, description, priority, action, scheduledTime, reminderTime });

    if (useFileStorage && !dataFile.empty()) {
        saveTasksToFile();
    }
}

void TaskManager::addTask(const std::string& id, const std::string& name, const std::string& description, int priority, ActionHandler action)
{
    if (id.empty() || name.empty() || description.empty() || priority < 1) {
        (DeveloperMode::IsEnable) ? Log("Invalid task parameters." , LoggerType::Critical) : DO_NOTHING;
        throw std::invalid_argument("Invalid task parameters.");
    }

    // Check for duplicate task name
    for (const Task& task : tasks) {
        if (task.taskInfo.id == id || task.taskInfo.name.value() == name) {
            (DeveloperMode::IsEnable) ? Log("A task with the same ID already exists." , LoggerType::Warning) : DO_NOTHING;
            throw std::runtime_error("A task with the same ID already exists.");
        }
    }

    tasks.push_back({ id, name, description, priority, action, std::chrono::system_clock::now(), TimePoint() });

    if (useFileStorage && !dataFile.empty()) {
        saveTasksToFile();
    }
}

void TaskManager::echoTasks()
{
    if (tasks.empty()) {
        (DeveloperMode::IsEnable) ? Log("No tasks found." , LoggerType::Warning) : DO_NOTHING;
        return;
    }

    Cell::Console::print << "Tasks:" << __cell_newline;
    for (const auto& task : tasks) {
        Cell::Console::print << "ID: "          << task.taskInfo.id.value() << __cell_newline;
        Cell::Console::print << "Name: "        << task.taskInfo.name.value() << __cell_newline;
        Cell::Console::print << "Description: " << task.taskInfo.description.value() << __cell_newline;
        Cell::Console::print << "Priority: "    << task.priority << __cell_newline;
        Cell::Console::print << __cell_newline;
    }
}

void TaskManager::editTask(const std::string& id,
                           const std::string& newName,
                           const std::string& newDescription,
                           int newPriority,
                           ActionHandler newAction,
                           const TimePoint& newScheduledTime,
                           const TimePoint& newReminderTime)
{
    if (newName.empty() || newDescription.empty() || newPriority < 1)
    {
        (DeveloperMode::IsEnable) ? Log("Invalid task parameters." , LoggerType::Critical) : DO_NOTHING;
        throw std::invalid_argument("Invalid task parameters.");
    }

    auto it = std::find_if(tasks.begin(), tasks.end(), [&](const Task& task) { return task.taskInfo.id.value() == id; });
    if (it != tasks.end()) {
        it->taskInfo.name.value() = newName;
        it->taskInfo.description.value() = newDescription;
        it->priority = newPriority;
        it->action = newAction;
        it->scheduledTime = newScheduledTime;
        it->reminderTime = newReminderTime;
        if (useFileStorage && !dataFile.empty()) {
            saveTasksToFile();
        }
    }
}

void TaskManager::editTask(const std::string& id,
                           const std::string& newName,
                           const std::string& newDescription,
                           int newPriority, ActionHandler newAction)
{
    if (newName.empty() || newDescription.empty() || newPriority < 1) {
        (DeveloperMode::IsEnable) ? Log("Invalid task parameters." , LoggerType::Critical) : DO_NOTHING;
        throw std::invalid_argument("Invalid task parameters.");
    }

    editTask(id, newName, newDescription, newPriority, newAction, std::chrono::system_clock::now(), TimePoint());
}

void TaskManager::removeTask(const std::string& id)
{
    auto it = std::find_if(tasks.begin(), tasks.end(), [&](const Task& task) { return task.taskInfo.id.value() == id; });
    if (it != tasks.end()) {
        tasks.erase(it);
        if (useFileStorage && !dataFile.empty()) {
            saveTasksToFile();
        }
    }
}

void TaskManager::searchTask(const std::string& id)
{
    auto it = std::find_if(tasks.begin(), tasks.end(), [&](const Task& task) { return task.taskInfo.id.value() == id; });
    if (it != tasks.end()) {
        Cell::Console::print << "Task found:"   << __cell_newline;
        Cell::Console::print << "ID: "          << it->taskInfo.id.value() << __cell_newline;
        Cell::Console::print << "Name: "        << it->taskInfo.name.value() << __cell_newline;
        Cell::Console::print << "Description: " << it->taskInfo.description.value() << __cell_newline;
        Cell::Console::print << "Priority: "    << it->priority << __cell_newline;
    }
    else {
        (DeveloperMode::IsEnable) ? Log("Task not found." , LoggerType::Warning) : DO_NOTHING;
    }
}

void TaskManager::runTask(const std::string& id)
{
    try {
        auto it = std::find_if(tasks.begin(), tasks.end(), [&](const Task& task) { return task.taskInfo.id.value() == id; });
        if (it != tasks.end()) {
            (DeveloperMode::IsEnable) ? Log("Running task:" + it->taskInfo.name.value() , LoggerType::Info) : DO_NOTHING;
            try {
                it->action();
                (DeveloperMode::IsEnable) ? Log("Task executed successfully.", LoggerType::Success) : DO_NOTHING;
            } catch (const std::exception& e) {
                (DeveloperMode::IsEnable) ? Log("An exception occurred during task execution:" + FROM_CELL_STRING(e.what()), LoggerType::Critical) : DO_NOTHING;
            } catch (...) {
                (DeveloperMode::IsEnable) ? Log("An unknown exception occurred during task execution.", LoggerType::Critical) : DO_NOTHING;
            }
        }
        else {
            (DeveloperMode::IsEnable) ? Log("Task not found.", LoggerType::Warning) : DO_NOTHING;
            throw std::runtime_error("Task not found.");
        }
    }
    catch (const std::exception& ex) {
        (DeveloperMode::IsEnable) ? Log("Error:" + FROM_CELL_STRING(ex.what()), LoggerType::Critical) : DO_NOTHING;
    }
}

void TaskManager::saveTasksToFile()
{
    try {
        std::ofstream outputFile(dataFile);
        if (!outputFile.is_open()) {
            (DeveloperMode::IsEnable) ? Log("Failed to open the data file for writing.", LoggerType::Critical) : DO_NOTHING;
            throw std::runtime_error("Failed to open the data file for writing.");
        }

        for (const auto& task : tasks) {
            writeTaskToFile(task, outputFile);
        }

        outputFile.close();
    }
    catch (const Exception& ex) {
        (DeveloperMode::IsEnable) ? Log("Error:" + FROM_CELL_STRING(ex.what()), LoggerType::Critical) : DO_NOTHING;
    }
}

void TaskManager::loadTasksFromFile()
{
    try {
        std::ifstream inputFile(dataFile);
        if (!inputFile.is_open()) {
            (DeveloperMode::IsEnable) ? Log("Failed to open the data file for reading.", LoggerType::Critical) : DO_NOTHING;
            throw std::runtime_error("Failed to open the data file for reading.");
        }

        tasks.clear();
        while (!inputFile.eof()) {
            Task task = readTaskFromFile(inputFile);
            if (!task.taskInfo.id.value().empty()) {
                tasks.push_back(task);
            }
        }

        inputFile.close();
    }
    catch (const Exception& ex) {
        (DeveloperMode::IsEnable) ? Log("Error:" + FROM_CELL_STRING(ex.what()), LoggerType::Critical) : DO_NOTHING;
    }
}

void TaskManager::setReminder(const std::string& id, const TimePoint& reminderTime)
{
    auto it = std::find_if(tasks.begin(), tasks.end(), [&](const Task& task) { return task.taskInfo.id.value() == id; });
    if (it != tasks.end()) {
        it->reminderTime = reminderTime;
        if (useFileStorage && !dataFile.empty()) {
            saveTasksToFile();
        }
    }
}

void TaskManager::writeTaskToFile(const Task& task, std::ofstream& outputFile)
{
    outputFile << task.taskInfo.id.value() << std::endl;
    outputFile << task.taskInfo.name.value() << std::endl;
    outputFile << task.taskInfo.description.value() << std::endl;
    outputFile << task.priority << std::endl;
    outputFile << std::chrono::system_clock::to_time_t(task.scheduledTime) << std::endl;
    outputFile << std::chrono::system_clock::to_time_t(task.reminderTime) << std::endl;
}

Task TaskManager::readTaskFromFile(std::ifstream& inputFile)
{
    Task task;
    std::getline(inputFile, task.taskInfo.id.value());
    std::getline(inputFile, task.taskInfo.name.value());
    std::getline(inputFile, task.taskInfo.description.value());
    inputFile >> task.priority;
    std::time_t scheduledTime, reminderTime;
    inputFile >> scheduledTime;
    inputFile >> reminderTime;
    task.scheduledTime = std::chrono::system_clock::from_time_t(scheduledTime);
    task.reminderTime = std::chrono::system_clock::from_time_t(reminderTime);
    inputFile.ignore(); // Ignore newline character
    return task;
}

void TaskManager::sortTasksByPriority(TaskList& tasks)
{
    std::sort(tasks.begin(), tasks.end(), [](const Task& taskA, const Task& taskB)
              {
        return taskA.priority < taskB.priority;
    });
}

void TaskManager::sortTasksByScheduledTime(TaskList& tasks)
{
    std::sort(tasks.begin(), tasks.end(), [](const Task& taskA, const Task& taskB)
              {
        return taskA.scheduledTime < taskB.scheduledTime;
    });
}

CELL_NAMESPACE_END
