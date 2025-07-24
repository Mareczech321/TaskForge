#ifndef TASK_H
#define TASK_H

#include <string>
#include <vector>
#include "../src/json.hpp"

class Task {

	public:
		Task() = default;
		Task(int id, const std::string& description);

		//ID getter
		int getId() const;

		//Description getter, setter
		std::string getDescription() const;

		void setDescription(const std::string& description);

		
		//Tags - getter, setters
		std::vector<std::string> getTags() const;
			
		void setTags(const std::vector<std::string>& tags);

		// Due date - getter, setter
		std::string getDueDate() const;
		void setDueDate(const std::string& dueDate);

		// Priority - getter, setter
		int getPriority() const;
		void setPriority(int priority);

		// Saving / loading tasks from json
		nlohmann::json toJson() const;
		static Task fromJson(const nlohmann::json& j);

		bool operator==(const Task& other) const;



	private:
		int id;
		std::string description;
		std::vector<std::string> tags;
		std::string dueDate;
		int priority;
};


#endif