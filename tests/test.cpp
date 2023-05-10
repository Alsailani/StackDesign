// If you change anything in this file, your changes will be ignored 
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include <gtest/gtest.h>
#include "../code_1/DispersionModel.h"

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <array>
#include <vector>

using namespace std;

class test_DispersionModel : public ::testing::Test {
protected:
	// This function runs only once before any TEST_F function
	static void SetUpTestCase(){
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)0;
			outgrade.close();
		}
	}

	// This function runs after all TEST_F functions have been executed
	static void TearDownTestCase(){
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)std::ceil(100*total_grade/max_grade);
			outgrade.close();
			std::cout << "Total Grade is : " << (int)std::ceil(100*total_grade/max_grade) << std::endl;
		}
	}

	void add_points_to_grade(double points){
		if(!::testing::Test::HasFailure()){
			total_grade += points;
		}
	}

	// this function runs before every TEST_F function
	void SetUp() override {}

	// this function runs after every TEST_F function
	void TearDown() override {
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)std::ceil(100*total_grade/max_grade);
			outgrade.close();
		}
	}
	
	static double total_grade;
	static double max_grade;
};

double test_DispersionModel::total_grade = 0;
double test_DispersionModel::max_grade = 100;

/////////////////////////////////////////
// Test Helper Functions
/////////////////////////////////////////



std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

/////////////////////////////////////////
// Tests start here
/////////////////////////////////////////

//Test the AddExhaust function
TEST_F(test_DispersionModel, AddExhaust){
	// Case 1: Add one exhautst with ID 102
	DispersionModel myDispersionModel;
    myDispersionModel.AddExhaust(102, "Lab Exhaust", 1, 2, 3, 400, 20);
	ASSERT_EQ(102,myDispersionModel.exhaustList.at(0)->id);
	add_points_to_grade(4);
	ASSERT_EQ("Lab Exhaust",myDispersionModel.exhaustList.at(0)->name);
	add_points_to_grade(4);
	ASSERT_EQ(1,myDispersionModel.exhaustList.at(0)->xCoordinate);
	add_points_to_grade(4);
	ASSERT_EQ(2,myDispersionModel.exhaustList.at(0)->yCoordinate);
	add_points_to_grade(4);
	ASSERT_EQ(3,myDispersionModel.exhaustList.at(0)->zCoordinate);
	add_points_to_grade(4);
	ASSERT_EQ(400,myDispersionModel.exhaustList.at(0)->volumeFlowRate);
	add_points_to_grade(4);
	ASSERT_EQ(20,myDispersionModel.exhaustList.at(0)->diameter);
	add_points_to_grade(4);

	//Case 2: Add one before 102
	myDispersionModel.AddExhaust(101, "General Exhaust", 1, 2, 3, 400, 20);
	ASSERT_EQ(101,myDispersionModel.exhaustList.at(0)->id);
	add_points_to_grade(4);
	ASSERT_EQ("General Exhaust",myDispersionModel.exhaustList.at(0)->name);
	add_points_to_grade(4);


	//Case 3: Add one after 102
	myDispersionModel.AddExhaust(103, "DG", 1, 2, 3, 400, 20);
	ASSERT_EQ(103,myDispersionModel.exhaustList.at(2)->id);
	add_points_to_grade(4);
	ASSERT_EQ("DG",myDispersionModel.exhaustList.at(2)->name);
	add_points_to_grade(4);


	//Case 4: Add duplicate stacks then make sure all order are the same
	myDispersionModel.AddExhaust(101, "General Exhaust", 1, 2, 3, 400, 20);

	ASSERT_EQ(101,myDispersionModel.exhaustList.at(0)->id);
	add_points_to_grade(4);

	ASSERT_EQ(102,myDispersionModel.exhaustList.at(1)->id);
	add_points_to_grade(4);

	ASSERT_EQ(103,myDispersionModel.exhaustList.at(2)->id);
	add_points_to_grade(4);
}

TEST_F(test_DispersionModel, PrintExhaust){
	//add one exhaust and print it
	DispersionModel myDispersionModel;
	myDispersionModel.AddExhaust(101, "Lab Exhaust", 1, 2, 3, 400, 20);
	testing::internal::CaptureStdout();
	myDispersionModel.PrintExhaust();
	string output1 = testing::internal::GetCapturedStdout();
	ASSERT_EQ("The exhausts are:\n101 Lab Exhaust 1 2 3 400 20\n",output1);
	add_points_to_grade(4);
}

TEST_F(test_DispersionModel, RemoveExhaust){
	//add two exhaust deleate the second then check by printing
	DispersionModel myDispersionModel;
	myDispersionModel.AddExhaust(101, "Lab Exhaust", 1, 2, 3, 400, 20);
	myDispersionModel.AddExhaust(102, "Lab Exhaust", 1, 2, 3, 400, 20);
	myDispersionModel.RemoveExhaust(102);
	testing::internal::CaptureStdout();
	myDispersionModel.PrintExhaust();
	string output1 = testing::internal::GetCapturedStdout();
	ASSERT_EQ("The exhausts are:\n101 Lab Exhaust 1 2 3 400 20\n",output1);
	add_points_to_grade(4);
}


//Test the AddIntake function
TEST_F(test_DispersionModel, AddIntake){
	DispersionModel myDispersionModel;
	//test the following case
    myDispersionModel.AddIntake(1, "Roof", 1, 2, 3);
	ASSERT_EQ(1,myDispersionModel.intakeList.at(0)->id);
	add_points_to_grade(4);
	ASSERT_EQ("Roof",myDispersionModel.intakeList.at(0)->name);
	add_points_to_grade(4);
	ASSERT_EQ(1,myDispersionModel.intakeList.at(0)->xCoordinate);
	add_points_to_grade(4);
	ASSERT_EQ(2,myDispersionModel.intakeList.at(0)->yCoordinate);
	add_points_to_grade(4);
	ASSERT_EQ(3,myDispersionModel.intakeList.at(0)->zCoordinate);
	add_points_to_grade(4);
}


TEST_F(test_DispersionModel, RemoveIntake){
	//add two intakes deleate the second then check by printing
	DispersionModel myDispersionModel;
	myDispersionModel.AddIntake(1, "Roof1", 1, 2, 3);
	myDispersionModel.AddIntake(2, "Roof2", 1, 2, 3);
	myDispersionModel.RemoveIntake(2);
	testing::internal::CaptureStdout();
	myDispersionModel.PrintIntake();
	string output1 = testing::internal::GetCapturedStdout();
	ASSERT_EQ("The intakes are:\n1 Roof1 1 2 3\n",output1);
	add_points_to_grade(4);
}

TEST_F(test_DispersionModel, PrintIntake){
	//add one exhaust and print it
	DispersionModel myDispersionModel;
	myDispersionModel.AddIntake(1, "Roof", 1, 2, 3);
	testing::internal::CaptureStdout();
	myDispersionModel.PrintIntake();
	string output1 = testing::internal::GetCapturedStdout();
	ASSERT_EQ("The intakes are:\n1 Roof 1 2 3\n",output1);
	add_points_to_grade(4);
}


//This will test RunModel and PrintResults
TEST_F(test_DispersionModel, PrintResults){
	//add one exhaust and print it
	DispersionModel myDispersionModel;
    myDispersionModel.AddExhaust(101, "Lab Exhaust", 22, 32, 213, 400, 20);
    myDispersionModel.AddIntake(1, "Roof", 1, 2, 3);
	myDispersionModel.RunModel();
	testing::internal::CaptureStdout();
	myDispersionModel.PrintResults();
	string output1 = testing::internal::GetCapturedStdout();
	ASSERT_EQ("The results are:\nExhaust ID: 101 -- Intake ID: 1 -- Concentration = 7026\n",output1);
	add_points_to_grade(8);
}

