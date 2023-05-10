#ifndef DispersionModel_H__
#define DispersionModel_H__


#include <string>
#include <memory>
#include <iostream>
#include <vector>
#include <gtest/gtest.h>
#include <algorithm>


using namespace std;

// structure for storing exhaust
struct exhaust {    
    int id;
    string name;
    double xCoordinate;  
    double yCoordinate;  
    double zCoordinate;
    double volumeFlowRate;
    double diameter;
};

// structure for storing intake
struct intake {
    int id;
    string name;
    double xCoordinate;  
    double yCoordinate;  
    double zCoordinate;
};


// structure for comparison, bool operators, makes insertion faster.

    struct CompareExhaustByID {
        bool operator()(const shared_ptr<exhaust>& object1, const shared_ptr<exhaust>& object2)
        {
            return(object1->id < object2->id);
            }
            };

    struct CompareIntakesByID {
        bool operator()(const shared_ptr<intake>& object1, const shared_ptr<intake>& object2)
        {
            return(object1->id < object2->id);
            }
            };


// structure to store the results
struct result {
    shared_ptr<exhaust> r_exhaust;
    shared_ptr<intake> r_intake;  
    double result;  
};


class DispersionModel {
public:
  // constructor
  DispersionModel();

  //deconstructor, as we are using shared_pointers we don't need to keep track of
  // freeing memory and you can leave this blank
  ~DispersionModel();
  
  // Public functions
  //Add user specified new exhaust data structure in the heap and store it in the ExhaustsList private Data Structure.
  void AddExhaust(int id, string name, double xCoordinate, double yCoordinate, double zCoordinate, double volumeFlowRate, double diameter);
  
  //Print all exhaust with their paratmers found in ExhaustsList private Data memebr.
  void PrintExhaust();

  //RemoveExahust source from the mememry and ExhaustsList private Data memeber
  void RemoveExhaust(int ID);

  //Similar to AddExhaust(), but Intake instead of Exhaust.
  void AddIntake(int id, string name, double xCoordinate, double yCoordinate, double zCoordinate);
  
  //Similar to PrintExhaust(), but Intake instead of Exhaust.
  void PrintIntake();

  //Similar to RemoveExhaust(), but Intake instead of Exhaust.
    void RemoveIntake(int ID);
    
  //Create a new memory location in the heap for every exhaust/ receptor combo and store the results in the ResultsList private Data memeber.
  void RunModel();

  //Print results after running the model
  void PrintResults();  
    


private:
    // these help accessing private data members from Gtests
    FRIEND_TEST(test_DispersionModel, AddExhaust);
    FRIEND_TEST(test_DispersionModel, AddIntake);

    //Vector stores pointers of every exhaust 
    vector<shared_ptr<intake>> intakeList;

    //Vector stores pointers of every intake.
    vector<shared_ptr<exhaust>> exhaustList;

    //Vector stores pointers of every intake/exhaust result combo.
    vector<shared_ptr<result>> resultsList;
    
    //private fucntions to check if Exhaust or Intake alrady exist
    bool ExhaustIDExist(int ID);
    bool IntaketIDExist(int ID);
};    

#endif  // DispersionModel_H__