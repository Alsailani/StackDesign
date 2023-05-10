


#include "DispersionModel.h"





DispersionModel::DispersionModel(){
}



DispersionModel::~DispersionModel(){
    // You don't need to add anything here
}
    

//Add Exhaust Function 
void DispersionModel::AddExhaust(int id, string name, double xCoordinate, double yCoordinate, double zCoordinate, double volumeFlowRate, double diameter) {
    if (ExhaustIDExist(id) == true) { // if exhaust id already exist don't do any thing and print the following
    cout<<"Exhaust already exist"<<endl;
    return;
    }
    shared_ptr<exhaust> ret(new exhaust);
    ret->id=id;    
    ret->name=name;
    ret->xCoordinate=xCoordinate;
    ret->yCoordinate=yCoordinate;
    ret->zCoordinate=zCoordinate;
    ret->volumeFlowRate=volumeFlowRate;
    ret->diameter=diameter;

    //find insertion location then insert
    auto it = lower_bound(exhaustList.begin(), exhaustList.end(), ret, CompareExhaustByID());
    exhaustList.insert(it, ret);
    
    //unefficent way below
    //exhaustList.push_back(ret);
    //sort(exhaustList.begin(), exhaustList.end(), CompareExhaustByID());
}

//Print Results Function 
void DispersionModel::PrintExhaust() {
    cout << "The exhausts are:\n";
    for(unsigned int i=0; i < exhaustList.size(); i++) {
        cout << exhaustList.at(i)->id<< " ";
        cout << exhaustList.at(i)->name<< " ";
        cout << exhaustList.at(i)->xCoordinate<< " ";
        cout << exhaustList.at(i)->yCoordinate<< " ";
        cout << exhaustList.at(i)->zCoordinate<< " ";
        cout << exhaustList.at(i)->volumeFlowRate<< " ";
        cout << exhaustList.at(i)->diameter<<endl;
    }
}
    
//Remove Exhaust Function 
void DispersionModel::RemoveExhaust(int ID) {
    for(unsigned int i=0; i < exhaustList.size(); i++) {
        if (exhaustList.at(i)->id==ID) {
            exhaustList.erase(exhaustList.begin()+i);
        }
    }
}



void DispersionModel::AddIntake(int id, string name, double xCoordinate, double yCoordinate, double zCoordinate){
    if (IntaketIDExist(id) == true) { // if intake id already exist don't do any thing and print the following
        cout<<"Intake already exist"<<endl;
        return;
    }
    shared_ptr<intake> ret(new intake);
    ret->id=id;    
    ret->name=name;
    ret->xCoordinate=xCoordinate;
    ret->yCoordinate=yCoordinate;
    ret->zCoordinate=zCoordinate;

    //find insertion location then insert
    auto it = lower_bound(intakeList.begin(), intakeList.end(), ret, CompareIntakesByID());
    intakeList.insert(it, ret);

    //unefficient way
    //intakeList.push_back(ret);
    //sort(intakeList.begin(), intakeList.end(), CompareIntakesByID());
}


void DispersionModel::PrintIntake() {
    cout << "The intakes are:\n";
    for(unsigned int i=0; i < intakeList.size(); i++) {
        cout << intakeList.at(i)->id<< " ";
        cout << intakeList.at(i)->name<< " ";
        cout << intakeList.at(i)->xCoordinate<< " ";
        cout << intakeList.at(i)->yCoordinate<< " ";
        cout << intakeList.at(i)->zCoordinate<< "\n";
    }
}


void DispersionModel::RemoveIntake(int ID) {
    for(unsigned int i=0; i < intakeList.size(); i++) {
        if (intakeList.at(i)->id==ID) {
            intakeList.erase(intakeList.begin()+i);
        }
    }
}


void DispersionModel::RunModel() {
    for(unsigned int i=0; i < exhaustList.size(); i++) {
        for(unsigned int j=0; j < intakeList.size(); j++) {
            shared_ptr<result> ret(new result);
            ret->r_exhaust=exhaustList.at(i);
            ret->r_intake=intakeList.at(j);
            ret->result = 33* (exhaustList.at(i)->zCoordinate) - (intakeList.at(j)->zCoordinate);
            resultsList.push_back(ret);
        }
    }
}



void DispersionModel::PrintResults() {
    if (resultsList.size()==0) {
        cout<<"There are no results to print"<<endl;
    }
    cout << "The results are:\n";
    for(unsigned int i=0; i < resultsList.size(); i++) {
        cout << "Exhaust ID: " << resultsList.at(i)->r_exhaust->id<< " ";
        cout << "-- Intake ID: " << resultsList.at(i)->r_intake->id<< " ";
        cout << "-- Concentration = " << resultsList.at(i)->result<< "\n";
    }
}




bool DispersionModel::ExhaustIDExist(int ID) {
    for(unsigned int i=0; i < exhaustList.size(); i++) {
        if (exhaustList.at(i)->id==ID) {
            return true; 
        }
    }
    return false;
}
            


bool DispersionModel::IntaketIDExist(int ID) {
    for(unsigned int i=0; i < intakeList.size(); i++) {
        if (intakeList.at(i)->id==ID) {
            return true; 
        }
    }
    return false;
}
            
