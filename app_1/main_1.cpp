#include <iostream>
#include <fstream>
#include "../code_1/DispersionModel.h"



using namespace std;


int main()
{
    cout<<"------------------------------"<<endl;
    cout<<"Start"<<endl;
    cout<<"------------------------------"<<endl;


    //Example 1: Add two exhausts print exahust list
    cout<<"Example 1"<<endl;
    DispersionModel myDispersionModel1;
    myDispersionModel1.AddExhaust(102, "Lab Exhaust", 22, 32, 213, 400, 20);
    myDispersionModel1.AddExhaust(101, "Lab Exhaust", 22, 32, 213, 400, 20);
    myDispersionModel1.PrintExhaust();
    cout<<"End of example 1"<<endl;
    cout<<"------------------------------"<<endl;



    //Example 2: Add two exhausts and 1 intake, run model, then print results
    cout<<"Example 2"<<endl;
    DispersionModel myDispersionModel2;
    myDispersionModel2.AddIntake(1, "Roof", 1, 2, 3);
    myDispersionModel2.AddExhaust(102, "Lab Exhaust", 22, 32, 213, 400, 20);
    myDispersionModel2.AddExhaust(101, "Lab Exhaust", 22, 32, 213, 400, 20);
    myDispersionModel2.RunModel();
    myDispersionModel2.PrintResults();
    cout<<"End of example 2"<<endl;
    cout<<"------------------------------"<<endl;


    //Example 3: Add exhaust with same ID
    cout<<"Example 3"<<endl;
    DispersionModel myDispersionModel3;
    myDispersionModel3.AddExhaust(101, "Lab Exhaust", 22, 32, 213, 400, 20);
    myDispersionModel3.AddExhaust(101, "Lab Exhaust", 22, 32, 213, 400, 20);
    cout<<"End of example 3"<<endl;
    cout<<"------------------------------"<<endl;



    return 0;
}