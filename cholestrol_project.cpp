// including modules and libraries used in the program below
#include <iostream> // To use cout and endl
#include <fstream> // To make use of input and output file streams
#include <string> // To make use of data type string
#include <iomanip> // To make use of setprecision
#include <ctype.h> // To use isalpha() function call
#include <cstdio>

using namespace std; // Allows us to use functions without 
                     // mentioning those are from standard library

// prototypes of the functions used below.
void evaluate_cholesterol(int, int, string&, string&); // evaluates and doesnt return but, sets the string pointer to evaluated evaluation statement
void evaluate_blood_pressure(int, int, string&, string&); // evaluates and doesnt return but, sets the string pointer to evaluated evaluation statement
int count_total_patients_in_file(ifstream&); // function to count total number of patients in the infile.txt to read
string return_ratio(float); // function to return the ratio evaluation
string return_status(char); // function to return the patient status

//entry point of the program
int main(){

    ifstream infile("infile.txt"); // declare input file handler to open a file
    string HDL_Evaluation, LDL_Evaluation, Systolic_Evaluation, Diastolic_Evaluation; // declare string identifier to store HDL comment, LDL comment, systolic comment, and diastolic comment
    int number_of_records; // declare int identifier for no. of patients to access
    
     
    //file handling error
    if(!infile.is_open()){
        cerr << "The file did not open. There is an error."<< endl;
        return 1;
    }

    cout << "Enter the number of patient records: " ; // Prompt to enter number of patients records in stdin
    cin >> number_of_records; // get number of records to access from the user
    // error handling if user tries to access more number of patients than are in the file
    int actual =count_total_patients_in_file(infile);
    if (number_of_records > actual){
        cout << "There are not " << number_of_records << " patients in the infile.txt.\nInstead there are a total of " << actual << " patients."<< endl;
        return 1;
    }

    // Following two lines brings the cursor back to starting of the file, which was near to eof, by the count_total_patients_in_file() function
    infile.clear() ;
    infile.seekg( 0, ios::beg ) ;

    // outer loop for unique number of patients
    for(int i = 1; i <= number_of_records ; i++){
        string patient_name; // declare string identifier to store patients name
        char status; // declare char identifier to store status of patient
        int number_of_data; // declare int identifier for number of data for each patient
        infile >> patient_name >> status >> number_of_data; // get data for patients
        cout << endl << "----------------------------------------------------" << endl;
        cout << "| Patient Number " << i << ") " << patient_name << "\n|   Status: " <<  return_status(status) << endl << "\n";

        // inner loop for many datasets for the same patient
        for(int j = 1; j <= number_of_data ; j++){
            int HDL_Reading, LDL_Reading, Systolic_Reading, Diastolic_Reading; // declare int identifier HDL level, LDL level, Systolic Pressure, and Diastolic Pressure
            cout << "|   DATA SET " << j << endl;
            infile >> HDL_Reading >> LDL_Reading >> Systolic_Reading >> Diastolic_Reading;
            cout << "|   Cholestrol Profile\n|     HDL: " <<  HDL_Reading << " LDL: " << LDL_Reading << endl;
            evaluate_cholesterol(HDL_Reading, LDL_Reading, HDL_Evaluation, LDL_Evaluation);
            cout << HDL_Evaluation << endl;
            cout << LDL_Evaluation << endl;
            cout << "|     Ratio: " << fixed << setprecision(4)  << (float)HDL_Reading/LDL_Reading << endl;
            cout <<  return_ratio((float)HDL_Reading/LDL_Reading) << endl ;
            cout << "|   Blood Pressure Profile\n|     Systolic: " << Systolic_Reading << " Diastolic: " << Diastolic_Reading << endl;
            evaluate_blood_pressure(Systolic_Reading, Diastolic_Reading, Systolic_Evaluation, Diastolic_Evaluation);
            cout << Systolic_Evaluation << endl;
            cout << Diastolic_Evaluation << endl << endl << endl;
        }
    }
    infile.close();
    return 0;
}

/**
 * Function below returns the total number of patients whose records are present in the file
 * @param  reference to infile.txt handler
 * @return count integer count
 * @author Biraj Dahal, Micah Capezzone, Christian R Batson, Jaleel Williams
 */ 
int count_total_patients_in_file(ifstream& infile){
    string line;
    int count = 0;
    while (getline(infile, line)){
        
        if (isalpha(line[0])){
            count += 1;
        }
    }
    
    return count;
}

/**
 * Function below returns the patient status
 * @param  char status 'N' or 'C' or 'F' or 'R'
 * @return meaning of the status
 * @author Biraj Dahal, Micah Capezzone, Christian R Batson, Jaleel Williams
 */ 
string return_status(char status){
    string return_statement;
    if (status == 'C'){
        return_statement = "Current Patient";
    }
    else if(status == 'R'){
        return_statement = "Returning Patient";
    }
    else if(status == 'N'){
        return_statement = "New Patient";
    }
    else if (status == 'F'){
        return_statement = "Referral Patient";
    }
    return return_statement;
}
/**
 * Function below returns the HDL/LDL ratio evaluation
 * @param  ratio of HDL/LDL
 * @return evaluation of the ratio
 * @author Biraj Dahal, Micah Capezzone, Christian R Batson, Jaleel Williams
 */ 
string return_ratio(float ratio){
    if (ratio > 0.3) {
        return "|     Ratio of HDL to LDL is good";
    }
    else{
        return "|     Ratio of HDL to LDL is not good";
    }
}

/**
 * Function below changes the statement of the reference of HDL_Evaluation and LDL_Evaluation
 * @param  HDL reading, LDL reading, HDL_Evaluation reference, and LDL_Evaluation Reference
 * @return nothing
 * @author Biraj Dahal, Micah Capezzone, Christian R Batson, Jaleel Williams
 */ 
void evaluate_cholesterol(int HDL, int LDL, string& HDL_Evaluation, string& LDL_Evaluation){
    if (HDL < 40){
        HDL_Evaluation = "|     HDL is Too Low";
    }
    else if(HDL >=40 && HDL < 60){
        HDL_Evaluation = "|     HDL is Okay";
    }
    else{
        HDL_Evaluation = "|     HDL is Excellent";
    }

    if (LDL < 100){
        LDL_Evaluation = "|     LDL is Optimal";
    }
    else if(LDL >=100 && LDL < 130){
        LDL_Evaluation = "|     LDL is Near Optimal";
    }
    else if(LDL >=130 && LDL < 160){
        LDL_Evaluation = "|     LDL is Borderline High";
    }
    else if(LDL >=160 && LDL < 190){
        LDL_Evaluation = "|     LDL is High";
    }
    else{
        HDL_Evaluation = "|     HDL is Very High";
    }  

}
/**
 * Function below changes the statement of the reference of Systolic Evaluation, and Diastolic_Evaluation
 * @param  Systolic reading, Diastolic reading, Systolic_Evaluation reference, and Diastolic_Evaluation Reference
 * @return nothing
 * @author Biraj Dahal, Micah Capezzone, Christian R Batson, Jaleel Williams
 */ 
void evaluate_blood_pressure(int Systolic, int Diastolic, string& Systolic_Evaluation, string& Diastolic_Evaluation){
    if (Systolic < 120){
        Systolic_Evaluation = "|     Systolic Reading is Optimal";
    }
    else if(Systolic < 130){
        Systolic_Evaluation = "|     Systolic Reading is Normal";
    }
    else if(Systolic < 140){
        Systolic_Evaluation = "|     Systolic Reading is Normal High";
    }
    else if(Systolic < 160){
        Systolic_Evaluation = "|     Systolic Reading is Stage 1 hypertension";
    }
    else if(Systolic < 180){
        Systolic_Evaluation = "|     Systolic Reading is Stage 2 hypertension";
    }
    else{
        Systolic_Evaluation = "|     Systolic Reading is Stage 3 hypertension";
    }

    if (Diastolic < 80){
        Diastolic_Evaluation = "|     Diastolic Reading is Optimal";
    }
    else if(Diastolic < 85){
        Diastolic_Evaluation = "|     Diastolic Reading is Normal";
    }
    else if(Diastolic < 90){
        Diastolic_Evaluation = "|     Diastolic Reading is Normal High";
    }
    else if(Diastolic < 100){
        Diastolic_Evaluation = "|     Diastolic Reading is Stage 1 hypertension";
    }
    else if(Diastolic < 110){
        Diastolic_Evaluation = "|     Diastolic Reading is Stage 2 hypertension";
    }
    else{
        Diastolic_Evaluation = "|     Diastolic Reading is Stage 3 hypertension";
    }
}
