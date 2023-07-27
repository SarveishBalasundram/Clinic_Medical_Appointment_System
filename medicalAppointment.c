#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//Notes
// 1. while(fscanf(fileName,"Content dia")) --> is very useful like how we use forloop to find the last EOF.
// 2. %[^,] --> is something that will read the string until it encounters ','. same as %[^\n].
// 3. String we cant use = or ==, we need to use strcat, strcmp. 
// 4. char* charVariable = (char*)malloc(244 * sizeof(char)) --> Something dynamic character instead of using cha var[size] 
// 5. We can use rewind(fileDoc), to rewind back the loop and also the file content to be scanned from the start.
// 6. After scanf and getting value of numerics and next you want to get value of string, ALWAYS have fflush(stdin) that removes all buffers and reset.
// 7. rand() % 100 --> Provides random numbers between 0 to 100.
// 8. From string to integer = atoi(stringValue)
// 9 . To remove any like non-alphabetic or any symbols from first index strings --> varName[0] = '\0'; \0 means Null.





// Got 3 Structs and One Node that will combine all of them to create a LinkedList.
typedef struct doctor
{
    int checker;
    char doctorID[50];
    char name[250];
    char email[250];
    char password[12];
    int availability; // 1 - Available Full 2 - Available Partial 3 - On Leave
    int specialist; //1 - Child , 2 - Adult, 3 - Old
}doctor;

typedef struct patient
{
    int checker;
    char patientID[50];
    char name[250];
    char email[250];
    char password[12];
}patient;


typedef struct user
{
    struct doctor Doctor;
    struct patient Patient;
}user;


typedef struct Node{
    struct user User;
    struct Node *next;
}Node;


Node *root=NULL, *currentLoginUser;
char* getAppointment(char str[]);
void profileEdit(char str[]);

void showAllPatient(){
    char* str = "doctor";
    char* appointmentID = getAppointment(str);
    printf("%s",appointmentID);
}

void mainMenuDoc(){
    fflush(stdin);
    int selection = 2;
    char* value;
    printf("------------------------------------------------------------------------------------------------------------------------\n|   Name: %s\t\t\t\t\t DoctorID: %s\t\t\t\t Date: %s\t\t \t|\n------------------------------------------------------------------------------------------------------------------------\t\n",currentLoginUser->User.Doctor.name, currentLoginUser->User.Doctor.doctorID,__DATE__);
    do{
    printf("\n\n--------------------------------------------- WELCOME TO DOCTOR PORTAL ---------------------------------------------\n\n\t\t Select any option:\n\n\t\t 1. View Appointment Information\n\n\t\t 2. View Profile \n\n\t\t 3. Go Back \n\n\t\t 4. Exit \n\n\n\t\t Enter Your Choice (1-4) : ");
    scanf("%d",&selection);

    if(selection < 1 || selection > 4){
        printf("\n\n Wrong Option selected. Please Try Again.. ");
    }

    }while(selection < 1 || selection > 4);

    switch (selection)
    {
    case 1:
        system("cls");
        showAllPatient();
        break;
    case 2:
        system("cls");
        profileEdit("doctor");
        break;
    case 3:
        system("cls");
        main();
        break;
    case 4:
        exit(1);
        break;
    
    default:
        break;
    }
}

char* getAppointment(char str[]){
    char appID[100],patientID[50],phoneNum[50],desc[250],doctorID[100],doctorName[90],patientName[100][255],patientEmail[100][255];
    char gender[30],sector[90];
    char* appointment = (char*)malloc(244 * sizeof(char));
    char appointmentID[100][100];
    int looper = 0;
    int totalAppointment = 0;
    FILE *file;
    file  = fopen("appointment.txt","r");
    FILE *fileDoc;
    fileDoc  = fopen("doctor.txt","r");

    FILE *filePatient;
    filePatient  = fopen("patient.txt","r");

    printf("------------------------------------------------------------------------------------------------------------------------\n|\t\t\t\t\t\t\t APPOINTMENT LIST      \t\t                               |\n");
    printf("------------------------------------------------------------------------------------------------------------------------");
    if(strcmp(str,"patient")==0){
    printf("|\t AppointmentID\t|   Sector Healthcare\t |      Health Problem\t\t  |       Doctor Name \t\t       |\n");
    printf("------------------------------------------------------------------------------------------------------------------------");
    while(fscanf(file,"AppID: %[^,], PID: %[^,], Gender: %[^,], PhoneNum: %[^,], Sector: %[^,], HealthProb: %[^,], DoctorID: %[^\n] ",appID,patientID, gender,phoneNum,sector,desc,doctorID)==7){
    char id[90], name[90],special[90];
    while(fscanf(fileDoc,"ID: %[^,], Name: %[^,], Email: %*[^,], Password: %*[^,], Availability: %*[^,], Specialist: %[^\n] ",id,name,special)==3){
        if(strcmp(doctorID, id) == 0 && strcmp(sector, special) == 0){
            strcpy(doctorName,name);
        }
    }

             rewind(fileDoc);



        if(strcmp(gender,"1") == 0){
            strcpy(gender,"Male");
        }else{
            strcpy(gender,"Female");
        }

        if(strcmp(sector,"1") == 0){
            strcpy(sector,"Child Healthcare");
        }else if(strcmp(sector,"2") == 0){
            strcpy(sector,"Adult Healthcare");
        }else{
            strcpy(sector,"Senior Adult Healthcare");
        }




        if(strcmp(str,"patient")==0){
            if(strcmp(currentLoginUser->User.Patient.patientID,patientID)==0){
                printf("\n|\t %s \t|\t%s  |     %s    \t  | %s \t\t |",appID,sector,desc,doctorName);
                strcpy(appointmentID[looper],appID);
                looper++;
                totalAppointment++;
            }
        }


    }  

        

        fclose(file);
        fclose(fileDoc);


    fflush(stdin);
    if(totalAppointment !=0){
    int checker = 0;
    do{
        printf("\n\n Enter the Appointment ID that needs to be cancel : ");
        gets(appointment);

    for(int i =0; i<100; i++){
        if(strcmp(appointment,appointmentID[i])==0){
            return appointment;
        }else{
            checker = 1;
        }
    }

    if(checker == 1){
        printf("\n\n You have entered an Invalid Appointment ID. Please Try Again !");
    }

    }while(checker == 1);
    }else{
            printf("\n\n No Appointments Booked under your name. Please Book An Appointment First !\n\n");
            system("pause");
            return "no";
}
    }else{
        char appointmentID[100][250], appointment[250];
        int looper = 0;
        int option =0;
        int total = 0;

        printf("|\t AppointmentID\t|   Patient Name\t |      Email\t\t  |       Health Problem \t\t       |\n");
        printf("------------------------------------------------------------------------------------------------------------------------"); 
            while(fscanf(file,"AppID: %[^,], PID: %[^,], Gender: %[^,], PhoneNum: %[^,], Sector: %[^,], HealthProb: %[^,], DoctorID: %[^\n] ",appID,patientID, gender,phoneNum,sector,desc,doctorID)==7){
                char pID[200],pName[255], pEmail[255];
                while (fscanf(filePatient, "ID: %[^,], Name: %[^,], Email: %[^,], Password: %*[^\n] ",pID, pName, pEmail) == 3) {
                    if(strcmp(doctorID,currentLoginUser->User.Doctor.doctorID)==0 && strcmp(pID,patientID)==0){
                        strcpy(patientName[looper],pName);
                        strcpy(patientEmail[looper],pEmail);
                        strcpy(appointmentID[looper],appID);
                        
                        printf("\n|\t %s \t|\t%s \t         |     %s    \t  | %s \t \t \t\t       |",appID,pName,pEmail,desc);
                        looper++;
                        total++;
                    }
                }
                rewind(filePatient);



            }
            printf("\n---------------------------------------------------------------------------------------\n");

        if(total == 0){
            fflush(stdin);
            printf("\n\nSorry, there is no appointment for you today. Press Enter to Go Back");
            getchar();
            system("cls");
            mainMenuDoc();
        }else{
            do{
            printf("\n\n\n\t Below are the Features you can access : \n\t\t 1. Cancel Appointment  \n\t\t 2. Appointment Completed \n\t\t 3. Go Back\n\n\t Enter your choice (1-3) : ");
            scanf("%d",&option);
            if (option==1 || option ==2 || option ==3){
                break;
            }else{
                printf("\n\nInvalid input entered..Please Try Again ! \n");
            }
            }while(1);

            fflush(stdin);

            if(option ==1){
            int checker = 0;
            do{
                printf("\n Enter the Appointment ID : ");
                gets(appointment);

            for(int i =0; i<100; i++){
                if(strcmp(appointment,appointmentID[i])==0){
                    FILE* fileApp;
                    FILE* fileCancel;
                    FILE* fileTemp;

                    fileApp = fopen("appointment.txt","r");
                    fileCancel = fopen("cancelAppointment.txt","a");
                    fileTemp = fopen("temporary.txt","w");



            while(fscanf(fileApp,"AppID: %[^,], PID: %[^,], Gender: %[^,], PhoneNum: %[^,], Sector: %[^,], HealthProb: %[^,], DoctorID: %[^\n] ",appID,patientID, gender,phoneNum,sector,desc,doctorID)==7){
                    if(strcmp(appID,appointment)==0){
                        fprintf(fileCancel,"AppID: %s, PID: %s, Gender: %s, PhoneNum: %s, Sector: %s, HealthProb: %s, DoctorID: %s\n",appID,patientID,gender,phoneNum,sector,desc,doctorID);
                    }else{
                       fprintf(fileTemp,"AppID: %s, PID: %s, Gender: %s, PhoneNum: %s, Sector: %s, HealthProb: %s, DoctorID: %s\n",appID,patientID,gender,phoneNum,sector,desc,doctorID); 
                    }
            }

            fclose(fileApp);
            fclose(fileCancel);
            fclose(fileTemp);
            remove("appointment.txt");
            rename("temporary.txt","appointment.txt");
            return "successful";


            }else{
                    printf("\n\n Invalid Appointment ID Entered.. Please Try Again!!\n\n");
                    checker = 1;
                    break;
            }
            }
            }while(checker == 1);


            }else if (option==3){
                system("cls");
                mainMenuDoc();
            }else{
                int checker = 0;
            do{
                printf("\n Enter the Appointment ID : ");
                gets(appointment);

            for(int i =0; i<100; i++){
                if(strcmp(appointment,appointmentID[i])==0){
                    FILE* fileApp;
                    FILE* fileTemp;

                    fileApp = fopen("appointment.txt","r");
                    fileTemp = fopen("temporary.txt","w");



            while(fscanf(fileApp,"AppID: %[^,], PID: %[^,], Gender: %[^,], PhoneNum: %[^,], Sector: %[^,], HealthProb: %[^,], DoctorID: %[^\n] ",appID,patientID, gender,phoneNum,sector,desc,doctorID)==7){
                    if(strcmp(appID,appointment) !=0){
                        fprintf(fileTemp,"AppID: %s, PID: %s, Gender: %s, PhoneNum: %s, Sector: %s, HealthProb: %s, DoctorID: %s\n",appID,patientID,gender,phoneNum,sector,desc,doctorID); 
                    }
            }

            fclose(fileApp);
            fclose(fileTemp);
            remove("appointment.txt");
            rename("temporary.txt","appointment.txt");
            return "success";
                }else{
                    printf("\n\n Invalid Appointment ID Entered.. Please Try Again!!\n\n");
                    checker = 1;
                    break;
                }
            }
            }while(checker == 1);




            }





    }
        }
}



void appointmentEdit(){
    system("cls");
    FILE* oriFile;
    FILE* tempFile;
    char appID[100],patientID[50],phoneNum[50],desc[250],doctorID[100],doctorName[90],gender[30],sector[90];
    oriFile = fopen("appointment.txt","r");
    tempFile = fopen("temporary.txt","w");

    
   char* appointmentID = getAppointment("patient");

   if(strcmp(appointmentID,"no")==0){
    mainMenuPatient();
   }else{
        while(fscanf(oriFile,"AppID: %[^,], PID: %[^,], Gender: %[^,], PhoneNum: %[^,], Sector: %[^,], HealthProb: %[^,], DoctorID: %[^\n] ",appID,patientID, gender,phoneNum,sector,desc,doctorID)==7){
            if(strcmp(appointmentID,appID) !=0){
                fprintf(tempFile,"AppID: %s, PID: %s, Gender: %s, PhoneNum: %s, Sector: %s, HealthProb: %s, DoctorID: %s\n",appID,patientID,gender,phoneNum,sector,desc,doctorID);
            }
        }
        fclose(oriFile);
        fclose(tempFile);
        remove("appointment.txt");
        rename("temporary.txt","appointment.txt");
        printf("\n\n Sucessfully Cancelled the Booked Appointment..Press Enter to Go Back to Main Menu..");
        getchar();
        system("cls");
        mainMenuPatient();
   }

}

void addIntoAppointmentFile(char patientID[50], int gender,char phoneNum[50],int sector,char desc[250],char doctorID[100]){

FILE* file;
file = fopen("appointment.txt","a");
int randomNum = rand() % 100;
char string[255];
sprintf(string, "%d", randomNum);
char result[255];
strcpy(result, "App");
strcat(result,string);
char resFinal[255];
strcpy(resFinal,patientID);


fprintf(file,"AppID: %s, PID: %s, Gender: %d, PhoneNum: %s, Sector: %d, HealthProb: %s, DoctorID: %s\n",strcat(result,resFinal),patientID,gender,phoneNum,sector,desc,doctorID);
printf("\n\nSuccessfully Booked An Appointment. These are the details:\n\t\tAppointmentID: %s\n\t\tPID: %s\n\t\t Gender: %d\n\t\t PhoneNum: %s\n\t\t Sector: %d\n\t\t HealthProb: %s\n\t\t DoctorID: %s",result, patientID, gender,phoneNum,sector,desc,doctorID);
fclose(file);
}


char* selectDoctor(int sector){
    FILE* fp;
    char docId[244];
    char* doctorID = (char*)malloc(244 * sizeof(char));
    char avString[200];
    int looper = 0;
    char doctorIDs[50][50];
    int totalDoctor = 0;
    fp = fopen("appointment.txt","r");
    printf("------------------------------------------------------------------------------------------------------------------------\n|\t\t\t\t\t\t\t DOCTOR LIST      \t\t                               |\n");
    printf("------------------------------------------------------------------------------------------------------------------------");
    printf("\n|\t Doctor ID\t| Name\t\t |   Email     |    Specialist    \t|\tAvailability (Hours)\t|\t Slots Available\t |");
    printf("\n------------------------------------------------------------------------------------------------------------------------");

    for ( Node *current = root; current != NULL; current = current->next )
    {
       int counter = 0;
        if(sector == 1 && current->User.Doctor.specialist == 1 ){
            while(fscanf(fp,"AppID: %*[^,], PID: %*[^,], Gender: %*[^,], PhoneNum: %*[^,], Sector: %*[^,], HealthProb: %*[^,], DoctorID: %[^\n] ",docId) == 1){
                if(strcmp(current->User.Doctor.doctorID,docId) == 0){
                    counter++;
                }
            }
            if(current->User.Doctor.availability == 1){
               strcpy(avString,"9 A.M - 5 P.M"); 
            }else if(current->User.Doctor.availability == 2){
                strcpy(avString,"9 A.M - 12 P.M"); 
            }else{
                strcpy(avString,"On Leave"); 
            }
            printf("\n\n\n\n\n Counter %d",counter);
            if(counter !=0 && counter <6 && current->User.Doctor.availability != 3){
                printf("\n|\t %s      \t|   %s \t | %s     \t | %s \t | \t %s\t|     %d  |",current->User.Doctor.doctorID,current->User.Doctor.name,current->User.Doctor.email,"Child Healthcare",avString,(6-counter));
                strcpy(doctorIDs[looper],current->User.Doctor.doctorID);
                looper++;
                totalDoctor++;
            }else if(counter ==0 && counter !=6 && current->User.Doctor.availability != 3){
                printf("\n|\t %s      \t|   %s \t | %s     \t | %s \t | \t %s\t|     %d  |",current->User.Doctor.doctorID,current->User.Doctor.name,current->User.Doctor.email,"Child Healthcare",avString,6);
                strcpy(doctorIDs[looper],current->User.Doctor.doctorID);
                looper++;        
                totalDoctor++;    
            }else if(counter == 6 && current->User.Doctor.availability != 3){
                printf("\n|\t %s  is not available today since slot is Full.",current->User.Doctor.name);
            }else if(current->User.Doctor.availability == 3){
                printf("\n|\t %s  is not available today since they are on leave.",current->User.Doctor.name);
            }
            rewind(fp);
        }else if(sector == 2 && current->User.Doctor.specialist == 2 ){
            while(fscanf(fp,"AppID: %*[^,], PID: %*[^,], Gender: %*[^,], PhoneNum: %*[^,], Sector: %*[^,], HealthProb: %*[^,], DoctorID: %[^\n] ",docId) == 1){
                if(strcmp(current->User.Doctor.doctorID,docId) == 0){
                    counter++;
                }
            };

            if(current->User.Doctor.availability == 1){
               strcpy(avString,"9 A.M - 5 P.M"); 
            }else if(current->User.Doctor.availability == 2){
                strcpy(avString,"9 A.M - 12 P.M"); 
            }else{
                strcpy(avString,"On Leave"); 
            }

            if(counter !=0 && counter <6 && current->User.Doctor.availability != 3){
                printf("\n|\t %s      \t|   %s \t | %s     \t | %s \t | \t %s\t|     %d  |",current->User.Doctor.doctorID,current->User.Doctor.name,current->User.Doctor.email,"Adult Healthcare",avString,(6-counter));
                strcpy(doctorIDs[looper],current->User.Doctor.doctorID);
                looper++;     
                totalDoctor++;       
            }else if(counter ==0 && counter !=6 && current->User.Doctor.availability != 3){
                printf("\n|\t %s      \t|   %s \t | %s     \t | %s \t | \t %s\t|     %d  |",current->User.Doctor.doctorID,current->User.Doctor.name,current->User.Doctor.email,"Adult Healthcare",avString,6);
                strcpy(doctorIDs[looper],current->User.Doctor.doctorID);
                looper++;         
                totalDoctor++;   
            }else if(counter == 6 && current->User.Doctor.availability != 3){
                printf("\n|\t %s  is not available today since slot is Full.",current->User.Doctor.name);
            
            }else if(current->User.Doctor.availability == 3){
                printf("\n|\t %s  is not available today since they are on leave.",current->User.Doctor.name);
  
            }

        }else if(sector == 3 && current->User.Doctor.specialist == 3 ){
            while(fscanf(fp,"AppID: %*[^,], PID: %*[^,], Gender: %*[^,], PhoneNum: %*[^,], Sector: %*[^,], HealthProb: %*[^,], DoctorID: %[^\n] ",docId) == 1){
                if(strcmp(current->User.Doctor.doctorID,docId) == 0){
                    counter++;
                }
            }

            if(current->User.Doctor.availability == 1){
               strcpy(avString,"9 A.M - 5 P.M"); 
            }else if(current->User.Doctor.availability == 2){
                strcpy(avString,"9 A.M - 12 P.M"); 
            }else{
                strcpy(avString,"On Leave"); 
            }

            if(counter !=0 && counter <6 && current->User.Doctor.availability != 3){
                printf("\n|\t %s      \t|   %s \t | %s     \t | %s \t | \t %s\t|     %d  |",current->User.Doctor.doctorID,current->User.Doctor.name,current->User.Doctor.email,"Senior Adult Healthcare",avString,(6-counter));
                strcpy(doctorIDs[looper],current->User.Doctor.doctorID);
                looper++;   
                totalDoctor++;         
            }else if(counter ==0 && counter !=6 && current->User.Doctor.availability != 3){
                printf("\n|\t %s      \t|   %s \t | %s     \t | %s \t | \t %s\t|     %d  |",current->User.Doctor.doctorID,current->User.Doctor.name,current->User.Doctor.email,"Senior Adult Healthcare",avString,6);
                strcpy(doctorIDs[looper],current->User.Doctor.doctorID);
                looper++;     
                totalDoctor++;       
            }else if(counter == 6 && current->User.Doctor.availability != 3){
                printf("\n|\t %s  is not available today since slot is Full.",current->User.Doctor.name);
            }else if(current->User.Doctor.availability == 3){
                printf("\n|\t %s  is not available today since they are on leave.",current->User.Doctor.name);
            }
        }

        rewind(fp);
        
    }
    printf("\n------------------------------------------------------------------------------------------------------------------------\n" );
fclose(fp);



if(totalDoctor !=0){
    int checker = 0;

    do{
    fflush(stdin);
    printf("\n\n Enter the Doctor ID listed above : ");
    gets(doctorID);

    for(int i =0; i<50; i++){
        if(strcmp(doctorID,doctorIDs[i])==0){
            return doctorID;
        }else{
            checker = 1;
        }
    }

    if(checker == 1){
        printf("\n\n You have entered an Invalid Doctor ID. Please Try Again !");
    }

    }while(checker == 1);
}else{
            printf("\n\n No Doctors Available at this moment. Please try to change to different sector. !\n\n");
            system("pause");
            system("cls");
            return "no";
}





}

void addDocIntoRoot(){
    FILE* fp;
    fp = fopen("doctor.txt","r");
    free(root);
    doctor docInfo;
    patient Patient;
    char name[100],email[200],available[100], specialist[100], id[20];

        while(fscanf(fp,"ID: %[^,], Name: %[^,], Email: %[^,], Password: %*[^,], Availability: %[^,], Specialist: %[^\n] ",id,name,email,available,specialist) == 5){
        
        int av = atoi(available);
        docInfo.availability = av;
        if(strcmp(available,"1")==0){
            available[0] = '\0';
            strcat(available,"9 A.M - 5 P.M");
        }else if(strcmp(available,"2")==0){
            available[0] = '\0';
            strcat(available,"9 A.M - 12 P.M");
        }else{
            available[0] = '\0';
            strcat(available,"On Leave"); 
        }
        
        if(strcmp(specialist,"1")==0){
            specialist[0] = '\0';
            strcat(specialist,"Child Healthcare");
            docInfo.specialist = 1;
        }else if(strcmp(specialist,"2")==0){
            specialist[0] = '\0';
            strcat(specialist,"Adult Healthcare");
            docInfo.specialist = 2;
        }else{
            specialist[0] = '\0';
            strcat(specialist,"Senior Adult Healthcare"); 
            docInfo.specialist = 3;
        }

        docInfo.name[0]='\0';
        docInfo.email[0]='\0';
        docInfo.doctorID[0]='\0';

        strcat(docInfo.doctorID , id);
        strcat(docInfo.name , name);
        strcat(docInfo.email , email);
         addNewNodes(docInfo,Patient,2);
}

}

void bookAppointment(){
    int selector; 
do{
    int gender, problem,sector;
    char phoneNum[50], desc[250];

    fflush(stdin);
    printf("------------------------------------------------------------------------------------------------------------------------\n|   Name: %s\t\t\t\t\t PatientID: %s\t\t\t\t Date: %s\t\t \t|\n------------------------------------------------------------------------------------------------------------------------\t\n",currentLoginUser->User.Patient.name, currentLoginUser->User.Patient.patientID,__DATE__);

    printf("\n\n Note: Each Doctor will have 6 Appointments Only per day ! Thanks. \n\n");

    do{
    printf("\n\t\tEnter your Gender ( 1-Male / 2-Female / 3-Others ) : ");
    scanf("%d",&gender);
    if(gender !=1 && gender !=2 && gender !=3){
        printf("\n\n Wrong Option selected. Please Try Again.. ");
    }
    }while(gender !=1 && gender !=2 && gender !=3);
    fflush(stdin);
    do{
    printf("\n\t\tEnter your Contact Number  : (+60) ");
    gets(phoneNum);
    if(strlen(phoneNum) > 8 && strlen(phoneNum) < 10){ 
        break;
    }else{
        printf("\n\n Invalid Contact Number. Please Try Again...");
    }
    }while(1);


    do{
    printf("\n\t\tEnter your Healthcare sector ( 1 - Child / 2 - Adult / 3 - Senior Adult ) :  ");
    scanf("%d",&sector);
    if(sector !=1 && sector !=2 && sector !=3){
        printf("\n\n Wrong Option selected. Please Try Again.. ");
    }
    }while(sector !=1 && sector !=2 && sector !=3);

fflush(stdin);
    do{
    printf("\n\t\tDescribe your health problem :  ");
    gets(desc);
    if(0>strlen(desc)>249){
        printf("\n\n Invalid Description. Please Provide a correct description for the doctor.");
    }
    }while(0>strlen(desc)>249);


    addDocIntoRoot();

    system("cls");

    char* doctorID = selectDoctor(sector);


    if(strcmp(doctorID,"no")==0){
        bookAppointment();
    }else{
        addIntoAppointmentFile(currentLoginUser->User.Patient.patientID,gender,phoneNum,sector,desc,doctorID);
    }

    do{
    printf("\n\n Do you want to book more appointment? (Yes - 1 / No - 2): ");
    scanf("%d",&selector);

    if(selector !=1 && selector !=2){
        printf("\n\n Wrong Input Entered. Please Try Again !");
    }
    }while(selector !=1 && selector !=2);
    if (selector ==2){
        system("cls");
        mainMenuPatient();
    }
    if(selector == 1){
        system("cls");
    }
    }while(selector == 1);




}


void modifyValue(char str[], int option){
    fflush(stdin);
    FILE* fp;
    FILE* tmpFile;

        char appID[100],patientID[50],phoneNum[50],desc[250],doctorID[100],doctorName[90];
    char gender[30],sector[90];
    
char name[100],email[200],available[100], specialist[100], id[20],password[150];

    if(strcmp(str,"patient")==0){
       fp = fopen("patient.txt","r");
       tmpFile = fopen("temp.txt","w");

    if(option == 1 ){

            printf("\n\t\t Current ID : %s",currentLoginUser->User.Patient.patientID);
            printf("\n\t\t\t Enter new ID : ");
            gets(id);

            printf("\n\t\t\t Enter password : ");
            gets(password);


        if(strcmp(id,currentLoginUser->User.Patient.patientID) != 0 && strcmp(password,currentLoginUser->User.Patient.password) == 0){

            char  tempID[100],tempName[200],tempEmail[100], tempPassword[100];

            while (fscanf(fp, "ID: %[^,], Name: %[^,], Email: %[^,], Password: %[^\n] ",tempID, tempName, tempEmail, tempPassword) == 4) {
            if (strcmp(tempID, currentLoginUser->User.Patient.patientID) == 0) {
                fprintf(tmpFile, "ID: %s, Name: %s, Email: %s, Password: %s\n",id, tempName, tempEmail, tempPassword);
                strcpy(currentLoginUser->User.Patient.patientID,"");
                strcat(currentLoginUser->User.Patient.patientID,id);
            } else {
                fprintf(tmpFile, "ID: %s, Name: %s, Email: %s, Password: %s\n",tempID, tempName, tempEmail, tempPassword);
            }
        }

        }else{
            printf("\n\n Invalid Password Entered!! Please Try Again!\nPress Enter to Continue..");
            getchar();
            system("cls");
            modifyValue("patient",1);
        } 
    }else if(option ==2){
            printf("\n\t\t Current Name : %s",currentLoginUser->User.Patient.name);
            printf("\n\t\t\t Enter new Name : ");
            gets(name);

            printf("\n\t\t\t Enter password : ");
            gets(password);


        if(strcmp(name,currentLoginUser->User.Patient.name) != 0 && strcmp(password,currentLoginUser->User.Patient.password) == 0){

            char  tempID[100],tempName[200],tempEmail[100], tempPassword[100];

            while (fscanf(fp, "ID: %[^,], Name: %[^,], Email: %[^,], Password: %[^\n] ",tempID, tempName, tempEmail, tempPassword) == 4) {
            if (strcmp(tempName, currentLoginUser->User.Patient.name) == 0) {
                fprintf(tmpFile, "ID: %s, Name: %s, Email: %s, Password: %s\n",tempID, name, tempEmail, tempPassword);
                strcpy(currentLoginUser->User.Patient.name,"");
                strcat(currentLoginUser->User.Patient.name,name);
            } else {
                fprintf(tmpFile, "ID: %s, Name: %s, Email: %s, Password: %s\n",tempID, tempName, tempEmail, tempPassword);
            }
        }

        }else{
            printf("\n\n Invalid Password Entered!! Please Try Again!\nPress Enter to Continue..");
            getchar();
            system("cls");
            modifyValue("patient",2);
        } 
    }else if(option ==3){

        printf("\n\t\t Current Email Address : %s",currentLoginUser->User.Patient.email);
            printf("\n\t\t\t Enter new Email : ");
            gets(email);

            printf("\n\t\t\t Enter password : ");
            gets(password);


        if(strcmp(email,currentLoginUser->User.Patient.email) != 0 && strcmp(password,currentLoginUser->User.Patient.password) == 0){

            char  tempID[100],tempName[200],tempEmail[100], tempPassword[100];

            while (fscanf(fp, "ID: %[^,], Name: %[^,], Email: %[^,], Password: %[^\n] ",tempID, tempName, tempEmail, tempPassword) == 4) {
            if (strcmp(tempEmail, currentLoginUser->User.Patient.email) == 0) {
                fprintf(tmpFile, "ID: %s, Name: %s, Email: %s, Password: %s\n",tempID, tempName, email, tempPassword);
                strcpy(currentLoginUser->User.Patient.email,"");
                strcat(currentLoginUser->User.Patient.email,email);
            } else {
                fprintf(tmpFile, "ID: %s, Name: %s, Email: %s, Password: %s\n",tempID, tempName, tempEmail, tempPassword);
            }
        }

        }else{
            printf("\n\n Invalid Password Entered!! Please Try Again!\nPress Enter to Continue..");
            getchar();
            system("cls");
            modifyValue("patient",3);
        }        
    }else if (option == 4){
        char newP[200],confirmPass[200];
        do{
        printf("\n\t\t Enter Current Password :");
        gets(password);

        printf("\n\t\t\t Enter new Password : ");
        gets(newP);

        printf("\n\t\t\t Re-enter new Password : ");
        gets(confirmPass);

         if(strcmp(currentLoginUser->User.Patient.password,password) !=0){
            printf("\nYou have entered invalid current Password. Please Try Again...\n\n");
         }else{

        if(strcmp(currentLoginUser->User.Patient.password,newP)==0){
            printf("\nYou have entered back the Current Password. Re-enter a new password...\n\n");
        }else if(strcmp(confirmPass,newP)!=0){
            printf("\nWrong confirmation password entered. Re-enter a new password...\n\n");
        }
         }



        }while(strcmp(currentLoginUser->User.Patient.password,password) !=0 || strcmp(password,newP)==0 || strcmp(confirmPass,newP)!=0);


        char  tempID[100],tempName[200],tempEmail[100], tempPassword[100];

            while (fscanf(fp, "ID: %[^,], Name: %[^,], Email: %[^,], Password: %[^\n] ",tempID, tempName, tempEmail, tempPassword) == 4) {
            if (strcmp(tempPassword, currentLoginUser->User.Patient.password) == 0) {
                fprintf(tmpFile, "ID: %s, Name: %s, Email: %s, Password: %s\n",tempID, tempName, tempEmail, newP);
                strcpy(currentLoginUser->User.Patient.password,"");
                strcat(currentLoginUser->User.Patient.password,newP);
            } else {
                fprintf(tmpFile, "ID: %s, Name: %s, Email: %s, Password: %s\n",tempID, tempName, tempEmail, tempPassword);
            }
        }

         
    }
        fclose(fp);
        fclose(tmpFile);
        remove("patient.txt");
        rename("temp.txt", "patient.txt");

        system("pause");
    }else{
       fp = fopen("doctor.txt","r");
       tmpFile = fopen("tempDoc.txt","w");

    if(option == 1 ){

            printf("\n\t\t Current ID : %s",currentLoginUser->User.Doctor.doctorID);
            printf("\n\t\t\t Enter new ID : ");
            gets(id);

            printf("\n\t\t\t Enter password : ");
            gets(password);


        if(strcmp(id,currentLoginUser->User.Doctor.doctorID) != 0 && strcmp(password,currentLoginUser->User.Doctor.password) == 0){

            char  tempID[100],tempName[200],tempEmail[100], tempPassword[100],tempAvailable[10],tempSpecialist[10];

            while (fscanf(fp, "ID: %[^,], Name: %[^,], Email: %[^,], Password: %[^,], Availability: %[^,], Specialist: %[^\n] ",tempID, tempName, tempEmail, tempPassword,tempAvailable,tempSpecialist) == 6) {
            if (strcmp(tempID, currentLoginUser->User.Doctor.doctorID) == 0) {
                fprintf(tmpFile, "ID: %s, Name: %s, Email: %s, Password: %s, Availability: %s, Specialist: %s\n",id, tempName, tempEmail, tempPassword,tempAvailable,tempSpecialist);
                FILE* fptr;
                FILE* temp;
                fptr = fopen("appointment.txt","r");
                temp = fopen("temporary.txt","w");

             while(fscanf(fptr,"AppID: %[^,], PID: %[^,], Gender: %[^,], PhoneNum: %[^,], Sector: %[^,], HealthProb: %[^,], DoctorID: %[^\n] ",appID,patientID, gender,phoneNum,sector,desc,doctorID)==7){
                if(strcmp(currentLoginUser->User.Doctor.doctorID,doctorID) ==0){
                fprintf(temp,"AppID: %s, PID: %s, Gender: %s, PhoneNum: %s, Sector: %s, HealthProb: %s, DoctorID: %s\n",appID,patientID,gender,phoneNum,sector,desc,id);
                }else{
                    fprintf(temp,"AppID: %s, PID: %s, Gender: %s, PhoneNum: %s, Sector: %s, HealthProb: %s, DoctorID: %s\n",appID,patientID,gender,phoneNum,sector,desc,doctorID);
                }
            }
                fclose(fptr);
                fclose(temp);
                remove("appointment.txt");
                rename("temporary.txt","appointment.txt");

                strcpy(currentLoginUser->User.Doctor.doctorID,"");
                strcat(currentLoginUser->User.Doctor.doctorID,id);
            } else {
                fprintf(tmpFile, "ID: %s, Name: %s, Email: %s, Password: %s, Availability: %s, Specialist: %s\n",tempID, tempName, tempEmail, tempPassword,tempAvailable,tempSpecialist);
            }
        }

        }else{
            printf("\n\n Invalid Password Entered!! Please Try Again!\nPress Enter to Continue..");
            getchar();
            system("cls");
            modifyValue("doctor",1);
        } 
    }else if(option ==2){
            printf("\n\t\t Current Name : %s",currentLoginUser->User.Doctor.name);
            printf("\n\t\t\t Enter new Name : ");
            gets(name);

            printf("\n\t\t\t Enter password : ");
            gets(password);


        if(strcmp(name,currentLoginUser->User.Doctor.name) != 0 && strcmp(password,currentLoginUser->User.Doctor.password) == 0){

            char  tempID[100],tempName[200],tempEmail[100], tempPassword[100],tempAvailable[10],tempSpecialist[10];

            while (fscanf(fp, "ID: %[^,], Name: %[^,], Email: %[^,], Password: %[^,], Availability: %[^,], Specialist: %[^\n] ",tempID, tempName, tempEmail, tempPassword,tempAvailable,tempSpecialist) == 6) {
            if (strcmp(tempName, currentLoginUser->User.Doctor.name) == 0) {
                fprintf(tmpFile, "ID: %s, Name: %s, Email: %s, Password: %s, Availability: %s, Specialist: %s\n",tempID, name, tempEmail, tempPassword,tempAvailable,tempSpecialist);
                strcpy(currentLoginUser->User.Doctor.name,"");
                strcat(currentLoginUser->User.Doctor.name,name);
            } else {
                fprintf(tmpFile, "ID: %s, Name: %s, Email: %s, Password: %s, Availability: %s, Specialist: %s\n",tempID, tempName, tempEmail, tempPassword,tempAvailable,tempSpecialist);
            }
        }

        }else{
            printf("\n\n Invalid Password Entered!! Please Try Again!\nPress Enter to Continue..");
            getchar();
            system("cls");
            modifyValue("doctor",2);
        } 
    }else if(option ==3){

            printf("\n\t\t Current Email Address : %s",currentLoginUser->User.Doctor.email);
            printf("\n\t\t\t Enter new Email : ");
            gets(email);

            printf("\n\t\t\t Enter password : ");
            gets(password);


        if(strcmp(email,currentLoginUser->User.Doctor.email) != 0 && strcmp(password,currentLoginUser->User.Doctor.password) == 0){

                        char  tempID[100],tempName[200],tempEmail[100], tempPassword[100],tempAvailable[10],tempSpecialist[10];

            while (fscanf(fp, "ID: %[^,], Name: %[^,], Email: %[^,], Password: %[^,], Availability: %[^,], Specialist: %[^\n] ",tempID, tempName, tempEmail, tempPassword,tempAvailable,tempSpecialist) == 6) {
            if (strcmp(tempEmail, currentLoginUser->User.Doctor.email) == 0) {
                fprintf(tmpFile, "ID: %s, Name: %s, Email: %s, Password: %s, Availability: %s, Specialist: %s\n",tempID, tempName, email, tempPassword,tempAvailable,tempSpecialist);
                strcpy(currentLoginUser->User.Doctor.email,"");
                strcat(currentLoginUser->User.Doctor.email,email);
            } else {
                fprintf(tmpFile, "ID: %s, Name: %s, Email: %s, Password: %s, Availability: %s, Specialist: %s\n",tempID, tempName, tempEmail, tempPassword,tempAvailable,tempSpecialist);
            }
        }

        }else{
            printf("\n\n Invalid Password Entered!! Please Try Again!\nPress Enter to Continue..");
            getchar();
            system("cls");
            modifyValue("doctor",3);
        }        
    }else if (option == 4){
        char newP[200],confirmPass[200];
        do{
        printf("\n\t\t Enter Current Password :");
        gets(password);

        printf("\n\t\t\t Enter new Password : ");
        gets(newP);

        printf("\n\t\t\t Re-enter new Password : ");
        gets(confirmPass);

         if(strcmp(currentLoginUser->User.Doctor.password,password) !=0){
            printf("\nYou have entered invalid current Password. Please Try Again...\n\n");
         }else{

        if(strcmp(currentLoginUser->User.Doctor.password,newP)==0){
            printf("\nYou have entered back the Current Password. Re-enter a new password...\n\n");
        }else if(strcmp(confirmPass,newP)!=0){
            printf("\nWrong confirmation password entered. Re-enter a new password...\n\n");
        }
         }



        }while(strcmp(currentLoginUser->User.Doctor.password,password) !=0 || strcmp(password,newP)==0 || strcmp(confirmPass,newP)!=0);


                    char  tempID[100],tempName[200],tempEmail[100], tempPassword[100],tempAvailable[10],tempSpecialist[10];

            while (fscanf(fp, "ID: %[^,], Name: %[^,], Email: %[^,], Password: %[^,], Availability: %[^,], Specialist: %[^\n] ",tempID, tempName, tempEmail, tempPassword,tempAvailable,tempSpecialist) == 6) {
            if (strcmp(tempPassword, currentLoginUser->User.Doctor.password) == 0) {
                fprintf(tmpFile, "ID: %s, Name: %s, Email: %s, Password: %s, Availability: %s, Specialist: %s\n",tempID, tempName, tempEmail, newP,tempAvailable,tempSpecialist);
                strcpy(currentLoginUser->User.Doctor.password,"");
                strcat(currentLoginUser->User.Doctor.password,newP);
            } else {
                fprintf(tmpFile, "ID: %s, Name: %s, Email: %s, Password: %s, Availability: %s, Specialist: %s\n",tempID, tempName, tempEmail, tempPassword,tempAvailable,tempSpecialist);
            }
        }

         
    }else if (option ==5){
            int available;
            do{
                if(currentLoginUser->User.Doctor.availability == 1){
                    printf("\n\t\t Current Availability : 9 A.M -> 5 P.M");
                }else if (currentLoginUser->User.Doctor.availability == 2){
                    printf("\n\t\t Current Availability : 9 A.M -> 12 P.M");
                }else{
                    printf("\n\t\t Current Availability : On Leave");
                }

                printf("\n\t\t\t Enter new Availability Slot (1 - 9 A.M -> 5 P.M / 2 - 9 A.M -> 12 P.M / 3 - On Leave) : ");
                scanf("%d",&available);
                fflush(stdin);
                if(available !=1 && available !=2 && available !=3){
                    printf("\n\n Invalid Option Entered.. Please Try Again!\n Press Enter to continue..");
                    getchar();
                    system("cls");
                }
            }while(available !=1 && available !=2 && available !=3);


            printf("\n\t\t\t Enter password : ");
            gets(password);


        if(strcmp(password,currentLoginUser->User.Doctor.password) == 0){

            char  tempID[100],tempName[200],tempEmail[100], tempPassword[100],tempAvailable[10],tempSpecialist[10];

            while (fscanf(fp, "ID: %[^,], Name: %[^,], Email: %[^,], Password: %[^,], Availability: %[^,], Specialist: %[^\n] ",tempID, tempName, tempEmail, tempPassword,tempAvailable,tempSpecialist) == 6) {
            if (strcmp(tempID, currentLoginUser->User.Doctor.doctorID) == 0) {
                fprintf(tmpFile, "ID: %s, Name: %s, Email: %s, Password: %s, Availability: %d, Specialist: %s\n",tempID, tempName, tempEmail, tempPassword,available,tempSpecialist);
                currentLoginUser->User.Doctor.availability = available;
            } else {
                fprintf(tmpFile, "ID: %s, Name: %s, Email: %s, Password: %s, Availability: %s, Specialist: %s\n",tempID, tempName, tempEmail, tempPassword,tempAvailable,tempSpecialist);
            }
        }

        }else{
            printf("\n\n Invalid Password Entered!! Please Try Again!\nPress Enter to Continue..");
            getchar();
            system("cls");
            modifyValue("doctor",5);
        }       



    }
        fclose(fp);
        fclose(tmpFile);
        remove("doctor.txt");
        rename("tempDoc.txt", "doctor.txt");
        system("cls");
        mainMenuDoc();
    }

}

void profileEdit(char str[]){
    system("cls");
    int option =0;
    int selection = 0;
    do{
    if(strcmp(str,"doctor")==0){
        do{
        printf("\t\t\t-----------------------------------------------------------------------------\n\t\t\t|\t\t\t\t Doctor Profile      \t\t            |\n");
        printf("\t\t\t-----------------------------------------------------------------------------");
        printf("\n\t\t\t| \t\t\t\t ID : %s      \t\t         \t    |\n\t\t\t| \t\t\t\t Name : %s      \t\t            |\n \t\t\t|\t\t             Email : %s      \t            |",currentLoginUser->User.Doctor.doctorID,
        currentLoginUser->User.Doctor.name, currentLoginUser->User.Doctor.email);
        printf("\n\t\t\t-----------------------------------------------------------------------------\n" );

        printf("\n\t\t Enter the Code to Continue\n\t\t\t 1. Modify ID\n\t\t\t 2. Modify Username\n\t\t\t 3. Modify Email\n\t\t\t 4. Modify Password\n\t\t\t 5. Update Availability\n\t\t\t 6. Go Back\n");
        printf("\t Enter Your Option (1-5): ");
        scanf("%d",&option);

        if(0>option>7){
            printf("\n\n Wrong Option selected. Please Try Again..\n");
            system("pause");
            system("cls");
        }
        }while(0>option>7);

            if(option !=6){
        modifyValue(str,option);
        }else{
        system("cls");
        mainMenuDoc();
        }
    }else{
        do{
        printf("\t\t\t-----------------------------------------------------------------------------\n\t\t\t|\t\t\t\t Patient Profile      \t\t            |\n");
        printf("\t\t\t-----------------------------------------------------------------------------");
        printf("\n\t\t\t| \t\t\t\t ID : %s      \t\t         \t    |\n\t\t\t| \t\t\t\t Name : %s      \t\t            |\n \t\t\t|\t\t             Email : %s      \t\t            |",currentLoginUser->User.Patient.patientID,
        currentLoginUser->User.Patient.name, currentLoginUser->User.Patient.email);
        printf("\n\t\t\t-----------------------------------------------------------------------------\n" );

        printf("\n\t\t Enter the Code to Continue\n\t\t\t 1. Modify ID\n\t\t\t 2. Modify Username\n\t\t\t 3. Modify Email\n\t\t\t 4. Modify Password\n\t\t\t 5. Go Back\n");
        printf("\t Enter Your Option (1-5): ");
        scanf("%d",&option);

        if(0>option>6){
            printf("\n\n Wrong Option selected. Please Try Again..\n");
            system("pause");
            system("cls");
        }
        }while(0>option>6);

        if(option !=5){
        modifyValue(str,option);
        }else{
        system("cls");
        mainMenuPatient();
        }
    }
    




    do
    {
            printf("\n\n Do you want to edit more of your profile ? ( 1 - Yes / 2 - No ) : ");
            scanf("%d",&selection);

            if(selection !=1 && selection !=2){
                printf("\n\n Wrong Option selected. Please Try Again..\n");
            }
    } while (selection !=1 && selection !=2);
    

    }while(selection == 1);

    if (selection ==2){
        system("cls");
        mainMenuPatient();
    }
    
}

void specificSpecialistDocByName(char str[]){
    int totalDoc = 0;


    printf("------------------------------------------------------------------------------------------------------------------------\n|\t\t\t\t\t\t\t DOCTOR LIST      \t\t                               |\n");
    printf("------------------------------------------------------------------------------------------------------------------------");
    printf("|\t Doctor ID\t| Name\t\t |   Email       \t  |    Specialist    \t|\tAvailability (Hours)\t|");
    printf("\n------------------------------------------------------------------------------------------------------------------------");


    for ( Node *current = root; current != NULL; current = current->next )
    {
        if(strstr(current->User.Doctor.name, str) != NULL){
            if(current->User.Doctor.specialist == 1){
            printf("\n|\t %s      \t|   %s \t | %s     \t | %s \t | \t %s\t       |",current->User.Doctor.doctorID,current->User.Doctor.name,current->User.Doctor.email,"Child Healthcare",current->User.Doctor.availability);
            totalDoc++;
            }else if(current->User.Doctor.specialist == 2){
            printf("\n|\t %s      \t|   %s \t | %s     \t | %s \t | \t %s\t       |",current->User.Doctor.doctorID,current->User.Doctor.name,current->User.Doctor.email,"Adult Healthcare",current->User.Doctor.availability);
            totalDoc++;
            }else{
            printf("\n|\t %s      \t|   %s \t | %s     \t | %s \t | \t %s\t       |",current->User.Doctor.doctorID,current->User.Doctor.name,current->User.Doctor.email,"Senior Adult Healthcare",current->User.Doctor.availability);
            totalDoc++;
            }

        }
    }
        printf("\n------------------------------------------------------------------------------------------------------------------------\n" );


        if(totalDoc ==0){
            printf("\n\n\t No Doctors Available at this moment. Please Try Again with Different Option !\n\n");
        }else{
            printf("\n\n\tPress Enter to Go Back...");
        }
        getchar();
        system("cls");
        showAllDoc();

}

void specificSpecialistDocBySpecialist(int selection){
    
    int totalDoc = 0;


    printf("------------------------------------------------------------------------------------------------------------------------\n|\t\t\t\t\t\t\t DOCTOR LIST      \t\t                               |\n");
    printf("------------------------------------------------------------------------------------------------------------------------");
    printf("|\t Doctor ID\t| Name\t\t |   Email       \t  |    Specialist    \t|\tAvailability (Hours)\t|");
    printf("\n------------------------------------------------------------------------------------------------------------------------");

    for ( Node *current = root; current != NULL; current = current->next )
    {
        if(selection == 1 && current->User.Doctor.specialist == 1 ){
            printf("\n|\t %s      \t|   %s \t | %s     \t | %s \t | \t %s\t       |",current->User.Doctor.doctorID,current->User.Doctor.name,current->User.Doctor.email,"Child Healthcare",current->User.Doctor.availability);
            totalDoc++;
        }else if(selection == 2 && current->User.Doctor.specialist == 2 ){
            printf("\n|\t %s      \t|   %s \t | %s     \t | %s \t | \t %s\t       |",current->User.Doctor.doctorID,current->User.Doctor.name,current->User.Doctor.email,"Adult Healthcare",current->User.Doctor.availability);
            totalDoc++;
        }else if(selection == 3 && current->User.Doctor.specialist == 3 ){
            printf("\n|\t %s      \t|   %s \t | %s     \t | %s \t | \t %s\t       |",current->User.Doctor.doctorID,current->User.Doctor.name,current->User.Doctor.email,"Senior Adult Healthcare",current->User.Doctor.availability);
            totalDoc++;
        }
    }
    printf("\n------------------------------------------------------------------------------------------------------------------------\n" );

        if(totalDoc ==0){
            printf("\n\n No Doctors Available at this moment. Please Try Again with Different Option !\n\n");
            system("pause");
            system("cls");
            showAllDoc();
        }
}


void showAllDoc(){
    FILE* fp;
    fp = fopen("doctor.txt","r");
    int count = 1;
    int selection = 0, feature = 0;
    doctor docInfo;
    patient Patient;
    char name[100],email[200],available[100], specialist[100], id[20];
    system("cls");
    printf("------------------------------------------------------------------------------------------------------------------------\n|\t\t\t\t\t\t\t DOCTOR LIST      \t\t                               |\n");
    printf("------------------------------------------------------------------------------------------------------------------------");
    printf("|\t No\t|   Name\t |      Email\t\t  |       Specialist \t\t |\tAvailability (Hours)\t\t|");
    printf("------------------------------------------------------------------------------------------------------------------------");
    while(fscanf(fp,"ID: %[^,], Name: %[^,], Email: %[^,], Password: %*[^,], Availability: %[^,], Specialist: %[^\n] ",id,name,email,available,specialist) == 5){
        

        docInfo.availability = available;
        if(strcmp(available,"1")==0){
            available[0] = '\0';
            strcat(available,"9 A.M - 5 P.M");
        }else if(strcmp(available,"2")==0){
            available[0] = '\0';
            strcat(available,"9 A.M - 12 P.M");
        }else{
            available[0] = '\0';
            strcat(available,"On Leave"); 
        }
        
        if(strcmp(specialist,"1")==0){
            specialist[0] = '\0';
            strcat(specialist,"Child Healthcare");
            docInfo.specialist = 1;
        }else if(strcmp(specialist,"2")==0){
            specialist[0] = '\0';
            strcat(specialist,"Adult Healthcare");
            docInfo.specialist = 2;
        }else{
            specialist[0] = '\0';
            strcat(specialist,"Senior Adult Healthcare"); 
            docInfo.specialist = 3;
        }
        printf("\n|\t %d \t|\t%s \t |     %s    | %s \t\t | \t %s \t\t|",count,name,email,specialist,available);
        count++;

        docInfo.name[0]='\0';
        docInfo.email[0]='\0';
        docInfo.doctorID[0]='\0';

        strcat(docInfo.doctorID , id);
        strcat(docInfo.name , name);
        strcat(docInfo.email , email);
        addNewNodes(docInfo,Patient,2);

    }
        printf("------------------------------------------------------------------------------------------------------------------------\n" );

    do{
            printf("\n\n  Additional Features : \n\t\t 1. View Specialist Doctors\n\t\t 2. Go Back\n\t\t 3. Exit Program \n\n\t Enter Your Option (1 / 2 / 3) : ");
            scanf("%d",&selection);

            switch (selection)
            {
            case 1:
                feature = 4;
                break;

            case 2:
                system("cls");
                mainMenuPatient();
                break;

            case 3:
                exit(1);
                break;
            
            default:
                printf("\n\n Wrong Option Entered.. Try again !\n");
                break;
            }
    }while(selection !=1 && selection !=2 && selection !=3);


while(feature != 1 && feature !=2 && feature !=3){
        printf("\n Options Available: \n\t\t 1. Search Doctors by Specialist Health Care Code Number \n\t\t 2. Search Doctors by Name \n\t\t 3. Go Back \n\n\t Enter Your Option (1 / 2 / 3) : ");
        scanf("%d",&feature);
        if(feature != 1 && feature !=2 && feature !=3){
            printf("\n\n Wrong Option Entered.. Try again !\n");
        }
}

    if(feature == 1){
        do{
            printf("\n\n Enter the Specialist Health Care Code Number (1 - Child, 2 - Adult  , 3 -  Senior Adult) : ");
            scanf("%d",&selection);

            if(selection !=1 && selection !=2 && selection !=3){
                printf("\n\n Wrong Option Entered.. Try again !\n");
            }else{
                system("cls");
                specificSpecialistDocBySpecialist(selection);
            }
        }while(selection !=1 && selection !=2 && selection !=3);
    }else if(feature == 2){
        fflush(stdin);
        char doctorName[255];
        printf("\n\n Enter the Doctor Name : ");
        gets(doctorName);

        system("cls");
        specificSpecialistDocByName(doctorName);


    }else{
        mainMenuPatient();
    }
}



void mainMenuPatient(){
    FILE *file;
    FILE *file2;
    file = fopen("cancelAppointment.txt","r");
    file2 = fopen("cancelTemp.txt","w");
    char appID[100],patientID[50],phoneNum[50],desc[250],doctorID[100],doctorName[90],gender[30],sector[90];
    fflush(stdin);
    int selection = 2;
    printf("------------------------------------------------------------------------------------------------------------------------\n|   Name: %s\t\t\t\t\t PatientID: %s\t\t\t\t Date: %s\t\t \t|\n------------------------------------------------------------------------------------------------------------------------\t\n",currentLoginUser->User.Patient.name, currentLoginUser->User.Patient.patientID,__DATE__);
    do{
        while(fscanf(file,"AppID: %[^,], PID: %[^,], Gender: %[^,], PhoneNum: %[^,], Sector: %[^,], HealthProb: %[^,], DoctorID: %[^\n] ",appID,patientID, gender,phoneNum,sector,desc,doctorID)==7){
            if(strcmp(currentLoginUser->User.Patient.patientID,patientID) ==0){
                printf("\n\n Your Appointment (ID: %s) on %s have been cancelled by the doctor. Please try to book again.\n Sorry on the Inconvience.", appID, desc);
            }else{
                fprintf(file2,"AppID: %s, PID: %s, Gender: %s, PhoneNum: %s, Sector: %s, HealthProb: %s, DoctorID: %s\n",appID,patientID,gender,phoneNum,sector,desc,doctorID);
            }
        }
        fclose(file);
        fclose(file2);

        remove("cancelAppointment.txt");
        rename("cancelTemp.txt","cancelAppointment.txt");
    printf("\n\n--------------------------------------------- WELCOME TO PATIENT PORTAL ---------------------------------------------\n\n\t\t Select any option:\n\n\t\t 1. View Doctors Information\n\n\t\t 2. Book Appointment \n\n\t\t 3. Edit Profile \n\n\t\t 4. Cancel Appointment\n\n\t\t 5. Go Back\n\n\t\t 6. Exit \n\n\n\t\t Enter Your Choice (1-6) : ");
    scanf("%d",&selection);

    if(selection < 1 || selection > 6){
        printf("\n\n Wrong Option selected. Please Try Again.. ");
    }

    }while(selection < 1 || selection > 6);

    switch (selection)
    {
    case 1:
        system("cls");
        showAllDoc();
        break;
    case 2:
        system("cls");
        bookAppointment();
        break;
    case 3:
        system("cls");
        profileEdit("patient");
        break;
    case 4:
        system("cls");
        appointmentEdit();
        break;
    case 5:
        system("cls");
        main();
        break;
    case 6:
        exit(1);
        break;
    
    default:
        break;
    }



    system("pause");
}

int readLogInFile(char str[],doctor docInfo,patient patientInfo){
    
    FILE *file;
    char line[250], id[100], password[100],name[100],email[200],available[10],special[10];

    if(strcmp(str,"patient")==0){
        file = fopen("patient.txt","r");
    }else{
        system("pause");
        file = fopen("doctor.txt","r");
    }

//%[^,] reads all the string until it faces ',' and stops. Its same as %[^\n] where this reads string until next line. * is used here to ignore that particular string space
if(strcmp(str,"patient") !=0){  
          //DOCTOR
        while (fscanf(file, "ID: %[^,], Name: %[^,], Email: %[^,], Password: %[^,], Availability: %[^,], Specialist: %[^\n] ", id, name, email ,password,available,special) == 6) { 
            
            if(strcmp(id,docInfo.doctorID)==0 && strcmp(password,docInfo.password)==0){
                Node *newNode = (struct Node*) malloc (sizeof(struct Node));
                docInfo.name[0] = '\0'; //clears the symbol at the front.
                strcat(docInfo.name,name);
                docInfo.email[0] = '\0'; //clears the symbol at the front.
                strcat(docInfo.email,email);

                docInfo.availability = atoi(available);
                docInfo.specialist = atoi(special);

                newNode->User.Doctor = docInfo;
                newNode->next = NULL;

                currentLoginUser = newNode;

                return 1;
            }
         }
    }else{
while ( fscanf(file, "ID: %[^,], Name: %[^,], Email: %[^,], Password: %[^\n] ", id, name,email ,password) == 4 ) { 

                if(strcmp(id,patientInfo.patientID)==0 && strcmp(password,patientInfo.password)==0){
                Node *newNode = (struct Node*) malloc (sizeof(struct Node));
                patientInfo.name[0] = '\0';
                strcat(patientInfo.name,name);
                patientInfo.email[0] = '\0';
                strcat(patientInfo.email,email);
                newNode->User.Patient = patientInfo;
                newNode->next = NULL;

                currentLoginUser = newNode;

                return 1;
}

    }
    }
         fclose(file);
         return 0;
}

    
void addIntoFile(){
    
    FILE *file;
    if(file==NULL)
    {
        printf("Error opening file.\n");
    }else{
        for(Node *curr = root;curr !=NULL;curr = curr->next){
        if(curr->User.Patient.checker == 0){
        file = fopen("patient.txt","a");
        fprintf(file,"ID: %s, Name: %s, Email: %s, Password: %s\n",curr->User.Patient.patientID, curr->User.Patient.name,curr->User.Patient.email,curr->User.Patient.password);
        printf("\n\nSuccessfully Registered. Use the ID and Password to Login: \nPID: %s \nName: %s \nEmail: %s \nPassword: %s\n",curr->User.Patient.patientID, curr->User.Patient.name,curr->User.Patient.email,curr->User.Patient.password);
        fclose(file);
        }

        if(curr->User.Doctor.checker == 0) {
        file = fopen("doctor.txt","a");
        fprintf(file,"ID: %s, Name: %s, Email: %s, Password: %s, Availability: %d, Specialist: %d\n",curr->User.Doctor.doctorID, curr->User.Doctor.name,curr->User.Doctor.email,curr->User.Doctor.password,curr->User.Doctor.availability,curr->User.Doctor.specialist);
        printf("\n\nSuccessfully Registered. Use the ID and Password to Login: \nID: %s \nName: %s \nEmail: %s \nPassword: %s\n",curr->User.Doctor.doctorID, curr->User.Doctor.name,curr->User.Doctor.email,curr->User.Doctor.password);
        }
        system("pause");
        fclose(file);
        }
        free(root);
    }
        


}



void addNewNodes(doctor newDoctor,patient newPatient,int checking){
    
   Node *newNode = (struct Node*) malloc (sizeof(struct Node));
   
   
   if(checking ==1 ){
    newNode->User.Patient = newPatient;
    newNode->User.Patient.checker = 0;
    newNode->User.Doctor = newDoctor;
    newNode->User.Doctor.checker = 1;
   }else{
    newNode->User.Doctor = newDoctor;
    newNode->User.Doctor.checker = 0;
    newNode->User.Patient = newPatient;
    newNode->User.Patient.checker = 1;
   }

    newNode->next =NULL;
    if(root==NULL){
        root = newNode;
    }else{
        newNode->next = root;
        root = newNode;
    }

    root = newNode;
//Check whether working or not only the below coding
    // for ( Node *current = root; current != NULL; current = current->next )
    // {
    //     if(current->User.Patient.checker == 0){
    //         printf("\n\n\n\nPNext = %s", current->User.Patient.name);
    //     }
    //     if(current->User.Doctor.checker == 0){
    //         printf("\n\n\n\nDNext = %s", current->User.Doctor.name);
    //     }
        
    // }
}



void signUp(char str[]){
    system("cls"); 
 //   int count = 0;
    int selection=1;
    char string[50];
    Node *curr,*newNode;
     

    printf("\n\n\t\t ---------------REGISTER NEW USER------------------\n\n");
    fflush(stdin);
    if(strcmp(str,"patient")==0){
            patient patient;
            printf("Enter patient name : ");
            gets(patient.name);
            printf("\nEnter patient email : ");
            gets(patient.email);
            printf("\nEnter patient password : ");
            gets(patient.password);

            snprintf(string, sizeof(string), "%d", rand()); //Generate RANDOM NUMBER and make into string
            strcpy(patient.patientID, patient.name); // Copy name into patientID
            strcat(patient.patientID, string); // Concatenate string to patientID


            //creating a new node to store the patient struct value in it
            newNode = (struct Node*) malloc (sizeof(struct Node));
            newNode->User.Patient = patient;
            newNode->next = NULL;
            doctor newDoctor;
            newNode->User.Patient.checker = 0;

            if(root==NULL){
                newNode->User.Doctor = newDoctor;
                newNode->User.Doctor.checker = 1;
                //Above two lines is very important to make Doctor value to be null.
                root = newNode;
            }else{
                addNewNodes(newDoctor, patient,1);
            }
    }else{
            doctor newDoctor;
            printf("Enter doctor name : ");
            gets(newDoctor.name);
            printf("\nEnter doctor email : ");
            gets(newDoctor.email);
            printf("\nEnter doctor password : ");
            gets(newDoctor.password);
            fflush(stdin);
            printf("\nEnter doctor specialist (1 - Child , 2 - Adult, 3 - Old) : ");
            scanf("%d",&newDoctor.specialist);


            snprintf(string, sizeof(string), "%d", rand()); //Generate RANDOM NUMBER and make into string
            strcpy(newDoctor.doctorID, newDoctor.name); // Copy name into doctorID
            strcat(newDoctor.doctorID, string); // Concatenate string to doctorID

            newDoctor.availability = 1; //Default for now.


            //creating a new node to store the newDoctor struct value in it

            newNode = (struct Node*) malloc (sizeof(struct Node));
            newNode->User.Doctor = newDoctor;
            newNode->next = NULL;
            newNode->User.Doctor.checker = 0;
            patient patient;


            if(root==NULL){
            newNode->User.Patient = patient;
            newNode->User.Patient.checker = 1;
            
            root = newNode;
            }else{
                addNewNodes(newDoctor,patient,0);
            }        
    }


    printf("\nDo you want to add a new user? (Yes - 1 / No - 2 ): ");
    scanf("%d",&selection);
    system("cls");

    if(selection == 1){
        int res = mainDashboard();
        if(res == 1){
            signUp("doctor");
        }else{
            signUp("patient");
        }
    }else{
        addIntoFile();
        system("cls");
        fflush(stdin);
        main();
    }

}


void signIn(char str[]){
    fflush(stdin);
    int result = 0;
    patient signInPatient;
    doctor signInDoctor;

    while(result !=1){
    patient signInPatient;
    doctor signInDoctor;

    printf("\n\n\t\t ---------------SIGN IN------------------\n\n");
    if(strcmp(str,"patient")==0){
        printf("Enter patient ID: ");
        gets(signInPatient.patientID);
        printf("Enter patient Password: ");
        gets(signInPatient.password);

        doctor docInfo;
        result =  readLogInFile(str,docInfo, signInPatient);


    }else{
        printf("Enter Doctor ID: ");
        gets(signInDoctor.doctorID);
        printf("Enter Doctor Password: ");
        gets(signInDoctor.password);

        
        result =  readLogInFile(str, signInDoctor, signInPatient);

        }
        if(result == 1){
            printf("Login Succesfully!!\t Press Enter to Continue..");
            getchar();
            system("cls");
            if(strcmp(str,"patient")==0){
              free(root);
              mainMenuPatient();
            }else{
                free(root);
                mainMenuDoc();
            }
            
        }else{
            printf("\n\n Wrong Credentials Entered. Please Try again!\nPress Enter to Continue..");
            getchar();
            system("cls");
        }       


    }
}


int mainDashboard(){
    int selection;
    while(selection !=1 && selection !=2){
     
            printf(
        "\t\t\t\t -------------- WELCOME TO SENTOSA MEDICAL CLINIC -------------\n\n\t\t Select Your Role : \n\n \t\t 1. DOCTOR\n\t\t 2. PATIENT\n\n Enter Your Role Number (1/2) :"
    );
    scanf("%d", &selection);

    if(selection !=1 && selection !=2){
        fflush(stdin); 
        printf("\t\t\n\n\nWrong Selection, Please Try Again!!\t\t\n\n\n Press Enter to Continue....");
        getchar();
        system("cls"); 
    }
    }
    return selection;
}

void selectionDashboard(char str[]){
    int selection;
    while(selection !=1 && selection !=2 && selection !=3 && selection !=4){
            printf("\n-------------- WELCOME TO SENTOSA MEDICAL CLINIC -------------\n\n\t\t Select Your Option : \n\n \t\t 1. Sign In\n\t\t 2. Register\n\t\t 3. Go Back\n\t\t 4. Exit\n\n\n\n Enter Your Option  (1/2):");

    scanf("%d",&selection);

    if(selection !=1 && selection !=2 && selection !=3 && selection !=4){
        fflush(stdin); 
        printf("\t\t\n\n\nWrong Selection, Please Try Again!!\t\t\n\n\n Press Enter to Continue....");
        getchar();
        system("cls"); 
    }
    }
    fflush(stdin);
    switch(selection){ 
        case 1:
            system("cls");
            signIn(str);
            break;
        case 2: 
            system("cls");
            signUp(str);
            break;
        case 3: 
            system("cls");
            main();
            break;
        case 4: 
            exit(1);
            break;
        default:
            printf("Wrong Option selected");
            break;
    }

}




//Main function
int main(){
   int mainDashSelection =  mainDashboard(); //MainDashboard
    getchar();
    system("cls");
    switch (mainDashSelection)
    {
    case 1:
        selectionDashboard("admin");
        break;
    
    case 2:
        selectionDashboard("patient");
        break;
    
    default:
        printf("Wrong Selection Number Entered.");
        getchar();
        break;
    }

    return 0;
}