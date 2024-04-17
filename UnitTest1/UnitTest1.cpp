#include "pch.h"
#include "CppUnitTest.h"
#include "../LB_11.3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

        TEST_METHOD(TestAverageGradeCalculation)
        {
            // Arrange
            Student student;
            student.physicsGrade = 90;
            student.mathGrade = 85;
            student.additionalGrade = 80;

            // Act
            student.averageGrade = (student.physicsGrade + student.mathGrade + student.additionalGrade) / 3.0;

            // Assert
            Assert::AreEqual(student.averageGrade, 85.0);
        }

        TEST_METHOD(TestSortingByCourse)
        {
            // Arrange
            vector<Student> students = { {"Smith", 3, ComputerScience, 85, 90, 80, 85.0},
                                        {"Johnson", 2, Informatics, 75, 85, 70, 76.6667},
                                        {"Doe", 3, MathAndEconomics, 90, 95, 85, 90.0} };

            // Act
            sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
                return a.course < b.course;
                });

            // Assert
            Assert::AreEqual(students[0].surname.c_str(), "Johnson");
            Assert::AreEqual(students[1].surname.c_str(), "Smith");
            Assert::AreEqual(students[2].surname.c_str(), "Doe");
        }

	};
}
