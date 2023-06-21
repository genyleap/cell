/*!
 * @file        taskmanager.hpp
 * @brief       This file is part of the Cell System.
 * @details     Task manager for accounts.
 * @author      <a href='https://www.kambizasadzadeh.com'>Kambiz Asadzadeh</a>
 * @package     The Genyleap
 * @since       29 Aug 2022
 * @copyright   Copyright (c) 2022 The Genyleap. All rights reserved.
 * @license     https://github.com/genyleap/cell/blob/main/LICENSE.md
 *
 */

#ifndef CELL_TASK_MANAGER
#define CELL_TASK_MANAGER

//! Cell's Core (Basic Requirements).
#if __has_include(<requirements>)
#   include <requirements>
#else
#   error "Cell's requirements was not found!"
#endif

//! Cell's Abstraction (Interfaces).
#if __has_include(<interface>)
#   include <interface>
#else
#   error "The abstractions of Cell was not found!"
#endif

CELL_NAMESPACE_BEGIN(Cell)

struct TaskInfo final
{
    Types::OptionalString id            {}; //!< Optional ID for the task.
    Types::OptionalString name          {}; //!< Optional name for the task.
    Types::OptionalString description   {}; //!< Optional description for the task.
};

using ActionHandler = std::function<void()>;
using TimePoint = std::chrono::system_clock::time_point;

/**
 * @brief Represents a task.
 * The `TaskManager` class is a class that manages tasks and provides operations for task management.
 * It encapsulates the logic for creating, editing, removing, and retrieving tasks.
 * The class allows users to perform various actions on tasks, such as adding tasks, editing task details, removing tasks, searching for tasks, running tasks, setting reminders, and more.
 * - Adding tasks: The class allows users to add tasks with specified details such as ID, name, description, priority, action handler, scheduled time, and reminder time.
 * - Editing tasks: Users can edit existing tasks by modifying their name, description, priority, action handler, scheduled time, and reminder time.
 * - Removing tasks: Tasks can be removed from the task list based on their ID.
 * - Searching for tasks: Users can search for tasks based on their ID.
 * - Running tasks: The class provides the ability to execute a task based on its ID.
 * - Setting reminders: Users can set reminder times for tasks to receive notifications.
 * - Saving and loading tasks from a file: The class supports saving the tasks to a file and loading tasks from a file.
 * - Sorting tasks: The class provides methods to sort tasks based on priority or scheduled time.
 *
 */
struct Task final
{
    TaskInfo        taskInfo;         //!< Information about the task.
    int             priority;         //!< Priority level of the task.
    ActionHandler   action;           //!< Handler for performing the task.
    TimePoint       scheduledTime;    //!< Scheduled time for the task.
    TimePoint       reminderTime;     //!< Reminder time for the task.
};

using TaskList = std::vector<Task>;

/**
 * @brief Manages tasks and provides operations for task management.
 */
class __cell_export TaskManager {
public:
    /**
     * @brief Constructs a TaskManager object.
     * @param useFileStorage Flag indicating whether to use file storage for tasks.
     * @param file The file path for storing tasks (if useFileStorage is true).
     */
    TaskManager(bool useFileStorage, const std::string& file);

    /**
     * @brief Retrieves the list of tasks.
     * @return Constant reference to the list of tasks.
     */
    const TaskList& getTasks() const;

    /**
     * @brief Adds a new task with specified details.
     * @param id The ID of the task.
     * @param name The name of the task.
     * @param description The description of the task.
     * @param priority The priority level of the task.
     * @param action The action handler for the task.
     * @param scheduledTime The scheduled time for the task.
     * @param reminderTime The reminder time for the task.
     */
    void addTask(const std::string& id,
                 const std::string& name,
                 const std::string& description,
                 int priority, ActionHandler action,
                 const TimePoint& scheduledTime,
                 const TimePoint& reminderTime);

    /**
     * @brief Adds a new task with specified details (without reminder time).
     * @param id The ID of the task.
     * @param name The name of the task.
     * @param description The description of the task.
     * @param priority The priority level of the task.
     * @param action The action handler for the task.
     */
    void addTask(const std::string& id,
                 const std::string& name,
                 const std::string& description,
                 int priority, ActionHandler action);

    /**
     * @brief Edits an existing task with new details.
     * @param id The ID of the task to edit.
     * @param newName The new name for the task.
     * @param newDescription The new description for the task.
     * @param newPriority The new priority level for the task.
     * @param newAction The new action handler for the task.
     * @param newScheduledTime The new scheduled time for the task.
     * @param newReminderTime The new reminder time for the task.
     */
    void editTask(const std::string& id,
                  const std::string& newName,
                  const std::string& newDescription,
                  int newPriority,
                  ActionHandler newAction,
                  const TimePoint& newScheduledTime,
                  const TimePoint& newReminderTime);

    /**
     * @brief Edits an existing task with new details (without reminder time).
     * @param id The ID of the task to edit.
     * @param newName The new name for the task.
     * @param newDescription The new description for the task.
     * @param newPriority The new priority level for the task.
     * @param newAction The new action handler for the task.
     */
    void editTask(const std::string& id,
                  const std::string& newName,
                  const std::string& newDescription,
                  int newPriority,
                  ActionHandler newAction);

    /**
     * @brief Removes a task with the specified ID.
     * @param id The ID of the task to remove.
     */
    void removeTask(const std::string& id);

    /**
     * @brief Searches for a task with the specified ID.
     * @param id The ID of the task to search for.
     */
    void searchTask(const std::string& id);

    /**
     * @brief Runs the task with the specified ID.
     * @param id The ID of the task to run.
     */
    void runTask(const std::string& id);

    /**
     * @brief Sets a reminder time for a task.
     * @param id The ID of the task.
     * @param reminderTime The reminder time for the task.
     */
    void setReminder(const std::string& id, const TimePoint& reminderTime);

    /**
     * @brief Writes the task details to an output file.
     * @param task The task to write.
     * @param outputFile The output file stream.
     */
    void writeTaskToFile(const Task& task, std::ofstream& outputFile);

    /**
     * @brief Reads a task from an input file.
     * @param inputFile The input file stream.
     * @return The read task.
     */
    Task readTaskFromFile(std::ifstream& inputFile);

    /**
     * @brief prints Lists all the tasks.
     */
    void echoTasks();

    /**
     * @brief Saves the tasks to the file.
     */
    void saveTasksToFile();

    /**
     * @brief Loads the tasks from the file.
     */
    void loadTasksFromFile();

    /**
     * @brief Sorts the tasks by priority.
     * @param tasks The list of tasks to sort.
     */
    void sortTasksByPriority(TaskList& tasks);

    /**
     * @brief Sorts the tasks by scheduled time.
     * @param tasks The list of tasks to sort.
     */
    void sortTasksByScheduledTime(TaskList& tasks);

private:
    TaskList tasks;         //!< List of tasks managed by the TaskManager.
    bool useFileStorage;    //!< Flag indicating whether to use file storage.
    std::string dataFile;   //!< The file path for storing tasks.
};

CELL_NAMESPACE_END

#endif  // CELL_TASK_MANAGER
