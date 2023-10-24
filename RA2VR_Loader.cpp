#include <iostream>
#include <cstdio>
#include <filesystem>

int promptUser();
int cp_replace(std::string source,std::string target);
void glueFunc(int choice);

int main(){
    glueFunc(promptUser());
    return 0;
}

//prompt user for choice -> index 0 input
int promptUser(){
    std::cout << "This CLI application allows user to quick swap yaml files in OpenRA2 RV Rules folder to use.\n Script by KF: https://github.com/kenf1\n";

    int choice;

    //loop until accepted input entered
    do{
        std::cout << "\n Enter choice:\n  1. Air Superiority\n  2. Reset air\n  3. Vehicle Superiority\n  4. Reset vehicle\n  5. Exit\n";
        std::cin >> choice;

        //throw error if non-int entered
        if(std::cin.fail()){
            std::cout << "Incorrect input. Please try again.\n";
            std::cin.clear();
            std::cin.ignore(10000,'\n');
        }
        choice--;
    }while(choice<0 || choice>4);

    return choice;
}

//copy & replace (overwrite if exist) + print output
int cp_replace(std::string source,std::string target){
    std::filesystem::copy(source,target,std::filesystem::copy_options::overwrite_existing);
    std::cout << "SOURCE: " << source << "\nTARGET: " << target << "\n";
    return 0;
}

//combine all subfunctions together
void glueFunc(int choice){
    const std::string RA_BASE = "RULES FOLDER";
    const std::string RA_MOD = "MODS FOLDER";
    
    const std::string AIR = "aircraft.yaml";
    const std::string VEHICLE = "allied-vehicles.yaml";

    //source
    const std::filesystem::path SRC_PATHS[] = {
        RA_MOD+AIR, //air modified
        RA_MOD+"orig_rules/"+AIR, //air original
        RA_MOD+VEHICLE, //ground modified
        RA_MOD+"orig_rules/"+VEHICLE //ground original
    };

    //target
    const std::filesystem::path TARGET_PATHS[] = {
        RA_BASE+AIR, //air
        RA_BASE+VEHICLE, //allied ground
    };

    //length of vectors
    int src_length = sizeof(SRC_PATHS)/sizeof(SRC_PATHS[0]);
    int target_length = sizeof(TARGET_PATHS)/sizeof(TARGET_PATHS[0]);

    //target_length should be 1/2 of src_length (2 options to same target)
    if(src_length/2 == target_length){
        switch(choice){
        case 0: cp_replace(SRC_PATHS[choice],TARGET_PATHS[0]);
            break;
        case 1: cp_replace(SRC_PATHS[choice],TARGET_PATHS[0]);
            break;
        case 2: cp_replace(SRC_PATHS[choice],TARGET_PATHS[1]);
            break;
        case 3: cp_replace(SRC_PATHS[choice],TARGET_PATHS[1]);
            break;
        case 4:
            std::exit(EXIT_SUCCESS); //quit app
        }
    }else{
        std::cout << "Check failed. Incorrect vector lengths.\n";
    }    
}