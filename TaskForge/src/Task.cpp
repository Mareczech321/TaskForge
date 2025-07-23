#include "../include/Task.h"
#include <vector>
#include <string>

Task::Task(int id, const std::string& description)
    : id(id), description(description), priority(0), dueDate("") {
}

// ID getter
int Task::getId() const {
    return id;
}

// Description - getter
std::string Task::getDescription() const {
    return description;
}

// Description - setter
void Task::setDescription(const std::string& description) {
    this->description = description; // 'this->' needed to disambiguate from parameter
}

// Tags - getter
std::vector<std::string> Task::getTags() const {
    return tags;
}

// Tags - setter
void Task::setTags(const std::vector<std::string>& tags) {
    this->tags = tags;
}

// Due date - getter
std::string Task::getDueDate() const {
    return dueDate;
}

// Due date - setter
void Task::setDueDate(const std::string& dueDate) {
    this->dueDate = dueDate;
}

// Priority - setter
void Task::setPriority(int priority) {
    this->priority = priority;
}

// Priority - getter
int Task::getPriority() const {
    return priority;
}

// Serialize Task object to JSON - chatgpt
nlohmann::json Task::toJson() const {
    nlohmann::json j;
    j["id"] = id;
    j["Description"] = description;
    j["tags"] = tags;
    j["Due date"] = dueDate;
    j["Priority"] = priority;
    return j;
}

// Deserialize Task object from JSON - chatgpt
Task Task::fromJson(const nlohmann::json& j) {
    Task t(j["id"], j["Description"]);
    t.setTags(j["tags"].get<std::vector<std::string>>());
    t.setDueDate(j["Due date"]);
    t.setPriority(j["Priority"]);
    return t;
}