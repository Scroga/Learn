#include <iostream>
#include <vector>
#include <fstream>

class Student
{
	std::string m_first = "Name";
	std::string m_last = "Surname";
	int m_id = 0;
	float m_avg = 0;

public:
	Student() {}

	Student(std:: string first, std::string last, int id, float avg) 
		: m_first (first)
		, m_last (last)
		, m_id (id)
		, m_avg (avg)
	{}

	void print() const
	{
		std::cout << m_first << " " << m_last << " ";
		std::cout << m_id << " " << m_avg << " ";
	}
};

class Course
{
	std::string m_name = "Course";
	std::vector<Student> m_students;

public:

	Course(){}
	Course(const std::string& name) 
		: m_name (name)
	{}

	void addStudent (const Student& s)
	{
		m_students.push_back(s);
	}

	const std::vector<Student>& getStudents() const
	{
		return m_students;
	}

	void loadFromFile(const std::string& filename)
	{
		std::ifstream fin("data/" + filename);
		std::string first, last;
		int id;
		float avg;

		while (fin >> first)
		{
			fin >> last >> id >> avg;

			addStudent(Student(first, last, id, avg));
		}
	}

	void print() const
	{
		for (const auto& s : m_students)
		{
			s.print();
			std::cout << "\n";
		}
	}
};

int main(int argc, char * argv[])
{
	Course c("COMP 4300");
	c.loadFromFile("students.txt");
	c.print();

	return 0;
}