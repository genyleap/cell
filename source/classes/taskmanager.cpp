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

    auto& engine = engineController.getEngine();
    auto language = createLanguageObject()->getLanguageCode();

    if (id.empty() || name.empty() || description.empty() || priority < 1)
    {
        auto exceptionMessage = safeTranslate(language, "exceptions", "invalid_task_parameters");
        (DeveloperMode::IsEnable) ? Log(exceptionMessage , LoggerType::Critical) : DO_NOTHING;
        throw std::invalid_argument(exceptionMessage);
    }

    // Check for duplicate task name
    for (const Task& task : tasks) {
        if (task.taskInfo.id == id || task.taskInfo.name.value() == name) {
            auto exceptionMessage = safeTranslate(language, "exceptions", "task_already_exists");
            (DeveloperMode::IsEnable) ? Log(exceptionMessage , LoggerType::Warning) : DO_NOTHING;
            throw std::runtime_error(exceptionMessage);
        }
    }

    tasks.push_back({ id, name, description, priority, action, scheduledTime, reminderTime });

    if (useFileStorage && !dataFile.empty()) {
        saveTasksToFile();
    }
}

void TaskManager::addTask(const std::string& id, const std::string& name, const std::string& description, int priority, ActionHandler action)
{
    auto& engine = engineController.getEngine();
    auto language = createLanguageObject()->getLanguageCode();

    if (id.empty() || name.empty() || description.empty() || priority < 1) {
        auto exceptionMessage = safeTranslate(language, "exceptions", "invalid_task_parameters");
        (DeveloperMode::IsEnable) ? Log(exceptionMessage , LoggerType::Critical) : DO_NOTHING;
        throw std::invalid_argument(exceptionMessage);
    }

    // Check for duplicate task name
    for (const Task& task : tasks) {
        auto exceptionMessage = safeTranslate(language, "exceptions", "task_already_exists");
        if (task.taskInfo.id == id || task.taskInfo.name.value() == name) {
            (DeveloperMode::IsEnable) ? Log(exceptionMessage , LoggerType::Warning) : DO_NOTHING;
            throw std::runtime_error(exceptionMessage);
        }
    }

    tasks.push_back({ id, name, description, priority, action, std::chrono::system_clock::now(), TimePoint() });

    if (useFileStorage && !dataFile.empty()) {
        saveTasksToFile();
    }
}

void TaskManager::echoTasks()
{
    auto& engine = engineController.getEngine();
    auto language = createLanguageObject()->getLanguageCode();
    auto exceptionMessage = safeTranslate(language, "exceptions", "no_tasks_found");

    if (tasks.empty()) {
        (DeveloperMode::IsEnable) ? Log(exceptionMessage , LoggerType::Warning) : DO_NOTHING;
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
    auto& engine = engineController.getEngine();
    auto language = createLanguageObject()->getLanguageCode();

    if (newName.empty() || newDescription.empty() || newPriority < 1)
    {
        auto exceptionMessage = safeTranslate(language, "exceptions", "invalid_task_parameters");
        (DeveloperMode::IsEnable) ? Log(exceptionMessage , LoggerType::Critical) : DO_NOTHING;
        throw std::invalid_argument(exceptionMessage);
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
    auto& engine = engineController.getEngine();
    auto language = createLanguageObject()->getLanguageCode();

    if (newName.empty() || newDescription.empty() || newPriority < 1) {
        auto exceptionMessage = safeTranslate(language, "exceptions", "invalid_task_parameters");
        (DeveloperMode::IsEnable) ? Log(exceptionMessage , LoggerType::Critical) : DO_NOTHING;
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
    auto& engine = engineController.getEngine();
    auto language = createLanguageObject()->getLanguageCode();

    auto it = std::find_if(tasks.begin(), tasks.end(), [&](const Task& task) { return task.taskInfo.id.value() == id; });
    if (it != tasks.end()) {
        Cell::Console::print << "Task found:"   << __cell_newline;
        Cell::Console::print << "ID: "          << it->taskInfo.id.value() << __cell_newline;
        Cell::Console::print << "Name: "        << it->taskInfo.name.value() << __cell_newline;
        Cell::Console::print << "Description: " << it->taskInfo.description.value() << __cell_newline;
        Cell::Console::print << "Priority: "    << it->priority << __cell_newline;
    }
    else {
        auto exceptionMessage = safeTranslate(language, "exceptions", "no_tasks_found");
        (DeveloperMode::IsEnable) ? Log(exceptionMessage , LoggerType::Warning) : DO_NOTHING;
    }
}

void TaskManager::runTask(const std::string& id)
{
    auto& engine = engineController.getEngine();
    auto language = createLanguageObject()->getLanguageCode();

    try {
        auto it = std::find_if(tasks.begin(), tasks.end(), [&](const Task& task) { return task.taskInfo.id.value() == id; });
        if (it != tasks.end()) {
            auto exceptionMessage = safeTranslate(language, "exceptions", "running_task");
            (DeveloperMode::IsEnable) ? Log(exceptionMessage + it->taskInfo.name.value() , LoggerType::Info) : DO_NOTHING;
            try {
                it->action();
                auto exceptionMessage = safeTranslate(language, "exceptions", "task_executed_successfully");
                (DeveloperMode::IsEnable) ? Log(exceptionMessage, LoggerType::Success) : DO_NOTHING;
            } catch (const Exception& e) {
                auto exceptionMessage = safeTranslate(language, "exceptions", "exception_occurred_during_task");
                (DeveloperMode::IsEnable) ? Log(exceptionMessage + FROM_CELL_STRING(e.what()), LoggerType::Critical) : DO_NOTHING;
            } catch (...) {
                auto exceptionMessage = safeTranslate(language, "exceptions", "unknown_exception_occurred_during_task");
                (DeveloperMode::IsEnable) ? Log(exceptionMessage, LoggerType::Critical) : DO_NOTHING;
            }
        }
        else {
            auto exceptionMessage = safeTranslate(language, "exceptions", "no_tasks_found");
            (DeveloperMode::IsEnable) ? Log(exceptionMessage, LoggerType::Warning) : DO_NOTHING;
            throw std::runtime_error(exceptionMessage);
        }
    }
    catch (const Exception& ex) {
        auto exceptionMessage = safeTranslate(language, "exceptions", "error");
        (DeveloperMode::IsEnable) ? Log(exceptionMessage + FROM_CELL_STRING(ex.what()), LoggerType::Critical) : DO_NOTHING;
    }
}

void TaskManager::saveTasksToFile()
{
    auto& engine = engineController.getEngine();
    auto language = createLanguageObject()->getLanguageCode();

    try {
        std::ofstream outputFile(dataFile);
        if (!outputFile.is_open()) {
            auto exceptionMessage = safeTranslate(language, "exceptions", "failed_open_data_file_writing");
            (DeveloperMode::IsEnable) ? Log(exceptionMessage, LoggerType::Critical) : DO_NOTHING;
            throw std::runtime_error(exceptionMessage);
        }

        for (const auto& task : tasks) {
            writeTaskToFile(task, outputFile);
        }

        outputFile.close();
    }
    catch (const Exception& ex) {
        auto exceptionMessage = safeTranslate(language, "exceptions", "error");
        (DeveloperMode::IsEnable) ? Log(exceptionMessage + FROM_CELL_STRING(ex.what()), LoggerType::Critical) : DO_NOTHING;
    }
}

void TaskManager::loadTasksFromFile()
{
    auto& engine = engineController.getEngine();
    auto language = createLanguageObject()->getLanguageCode();

    try {
        std::ifstream inputFile(dataFile);
        if (!inputFile.is_open()) {
            auto exceptionMessage = safeTranslate(language, "exceptions", "failed_open_data_file_reading");
            (DeveloperMode::IsEnable) ? Log(exceptionMessage, LoggerType::Critical) : DO_NOTHING;
            throw std::runtime_error(exceptionMessage);
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
        auto exceptionMessage = safeTranslate(language, "exceptions", "error");
        (DeveloperMode::IsEnable) ? Log(exceptionMessage + FROM_CELL_STRING(ex.what()), LoggerType::Critical) : DO_NOTHING;
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
