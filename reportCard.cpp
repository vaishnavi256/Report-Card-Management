#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

/*******************************/
/*          STUDENT CLASS      */ 
/*******************************/

class student {
    public:
    string name;
    int rollno;
    int pMarks, cMarks, mMarks, csMarks;
    double percentage;
    char grade;
    void calculate();
public:
    void getData ();
    void showData ();
    void showTabular();
    int  getRollNum();
};
void student :: calculate(){
    
    percentage = (pMarks + cMarks + mMarks + csMarks) / 5;
    if (percentage >= 90) {
        grade = 'A';
    }
    else if (percentage >= 80){
        grade = 'B';
    }
    else if (percentage >= 70){
        grade = 'C';
    }
    else if (percentage >= 60){
        grade = 'D';
    }
    else if (percentage >= 33){
        grade = 'E';
    }
    else{
        grade = 'F';
    }
}
void student:: getData(){
    cout << "Enter name of student           : ";
    cin >> name;
    cout << "Enter roll number of student    : ";
    cin >> rollno;
    cin >> name;
    cout << "Enter marks in Maths            : ";
    cin >> mMarks;
    cout << "Enter marks in Physics          : ";
    cin >> pMarks;
    cout << "Enter marks in Chemistry        : ";
    cin >> cMarks;
    cout << "Enter marks in Computer Science : ";
    cin >> csMarks;
}

void student:: showData(){
    cout << "\nRoll number of student    :" << rollno;
    cout << "\nName of student           :" << name;
    cout << "\nMarks in Maths            :" << mMarks;
    cout << "\nMarks in Physics          :" << pMarks;
    cout << "\nMarks in Chemistry        :" << cMarks;
    cout << "\nMarks in Computer Science :" << csMarks;
}
void student::showTabular(){
    // setw() --> iomaip library --> used to set width 
    cout << rollno << setw(6) << " " << name << setw(10)
    << mMarks << setw(4) << pMarks << setw(4) << cMarks << setw(4) 
    << csMarks << setw(8) << percentage << setw(6) << grade << endl;
}

int student :: getRollNum(){
    return rollno;
}

/***************************/
/*        FUNCTIONS        */ 
/***************************/ 


void writeStudent();            //for storing records
void displayAll ();             //to read all record 
void displayStudentRec (int);   // to display reecord of a particular student using roll no
void modifyStudemt (int);       // to modify usinf roll no
void deleteStudent (int);       // accept roll num all delete 
void classResult ();
void result ();
void intro ();                  // display welcome screen
void entryMenu();               // display entry menu



/*****************************/
/*      MAIN FUNCTION        */
/*****************************/ 


int main()
{
    char ch;
    intro();
    while (true)
    {
        cout << "\n\n\\n\tMAIN MENU";
        cout << "\n\n\t  (i). RESULT MENU";
        cout << "\n\n\t (ii). ENTRY/EDIT MENU";
        cout << "\n\n\t(iii). EXIT";
        cout << "\n\n]tPlease select the service (1 - 3)";
        cin >> ch;
        if (ch == 3) break;
        switch (ch){

            case '1': result();
                    break;
            case '2': entryMenu();
                    break;
            default: cout << "\nDONE";
        }
    }
    return 0;
}

/**************************************/
/*     function to write in file      */
/**************************************/

void writeStudent(){
    student st;
    ofstream outputFile;
    outputFile.open("student.dat", ios::binary|ios::app);
    st.getData();

    // reinterpret_cast<char*>(&st): This is a C++ cast operator 
    // (reinterpret_cast) used to convert the memory representation of 
    // the st object into a pointer to a character.
    //  The &st gets the address of the st object.
    outputFile.write(reinterpret_cast<char*>(&st), sizeof(student));
    outputFile.close();
    cout << "\n\nStudent record has been generated";
    cin.ignore();
    cin.get();
}

/**************************************/
/* function to read records from file */
/**************************************/

void displayAll(){
    student st;
    ifstream inputFile;
    inputFile.open("student.dat", ios::binary);

    if (!inputFile){

        cout << "Unknown error occured! Press any key";
        cin.ignore();
        cin.get();
        return;

    }

    cout << "Display all record! \n\n";

    while (inputFile.read(reinterpret_cast<char*> (&st), sizeof(student))){

        st.showData();
        cout << "\n\n_______________________________________\n";

    } 

    inputFile.close();
    cin.ignore();
    cin.get();

}

/**************************************************/
/*  function to read specific record from file    */ 
/**************************************************/

void displayStudentRec(int n)
{
    student st;
    ifstream inputFile;
    inputFile.open ("student.dat", ios::binary);
    if (!inputFile)
    {
        cout << "Unknown error occured! Press any key";
        cin.ignore();
        cin.get();
        return;
    }

    bool flag = false;
    while (inputFile.read(reinterpret_cast<char*> (&st), sizeof(student)))
    {
        if (st.getRollNum() == n){
            st.showData();
            flag = true;
        }
    }
    inputFile.close();
    if (flag == false){
        cout << "\n\nRecord does not exists";
        cin.ignore();
        cin.get();
    }
}

/*******************************************/
/*      Function to modify record          */ 
/*******************************************/

void modifyStudemt(int n){

    bool found = false;
    student st;
    fstream file;
    file.open("stdent.dat", ios::binary|ios::in|ios::out);
    if (!file){

        cout << "Unknown error occured! Press any key";
        cin.ignore();
        cin.get();
        return;

    }
    while (!file.eof() && found == false){

        file.read(reinterpret_cast<char*> (&st), sizeof (student));
        if (st.getRollNum() == n)
        {
            st.showData();
            cout << "\n\nPlease enter the new details of student" << endl;
            st.getData();
            int pos = (-1)*static_cast<int> (sizeof(st));
            file.seekp(pos,ios::cur);
            file.write(reinterpret_cast<char*> (&st), sizeof(student));
            cout << "\n\n\t Record updated";
            found = true;
        }

    }
    file.close();
    if (found == false) cout << "\n\n Record not found";
    cin.ignore();
    cin.get();

}

/**************************************************************/ 
/*      Function to delete record of file                     */
/**************************************************************/

void deleteStudent (int n){

    student st;
    ifstream inputFile;
    inputFile.open("student.dat", ios::binary);
    if (!inputFile){

        cout << "Unknown error occured! Press any key";
        cin.ignore();
        cin.get();
        return;
    }
    ofstream outputFile;
    outputFile.open ("temp.dat", ios::out);
    inputFile.seekg (0, ios::beg);
    while (inputFile.read( reinterpret_cast<char*> (&st), sizeof (student)))
    {
        if (st.getRollNum()!=n)
        {
            outputFile.write (reinterpret_cast<char*> (&st), sizeof (student));
        }
    }

    outputFile.close();
    inputFile.close();
    remove ("student.dat");
    rename("temp.dat", "student.dat");
    cout << "\n\n\t Record deleted successfully";
    cin.ignore();
    cin.get();

}

/****************************************************/
/*   Function to display all students grade report  */  
/****************************************************/

void classResult(){
    student st;
    ifstream inputFile;
    inputFile.open ("student.dat", ios::binary);
    if (!inputFile){
        cout << "Unknown error occured! Press any key";
        cin.ignore();
        cin.get();
        return;
    }
    cout << "\n\n]t\tAll student result \n\n";
    cout << "_________________________________________________________________\n";
    cout << "RollNum        Name        P   C   M   CS  Percentage  Grade" << endl;
    cout << "_________________________________________________________________\n";
    while (inputFile.read(reinterpret_cast<char*> (&st), sizeof (student))){
        st.showTabular();
    }
    cin.ignore();
    cin.get();
    inputFile.close();
}


/*************************************************************************/
/*                      Function to display result menu                  */ 
/*************************************************************************/

void result(){
    char ch;
    int rno;
    system ("cls");
    cout << "\n\n\n\tRESULT MENU";
    cout << "\n\n\n\t1. Class Result";
    cout << "\n\n\t2. Student Report Card";
    cout << "\n\n\n\tEnter Choice (1/2/3)";
    cin >> ch;
    system("cls");
    switch (ch){
        case '1' : classResult(); break;
        case '2' : cout << "\n\n\tEnter Roll Number : "; cin >> rno;
                    displayStudentRec(rno); 
                    break;
        case '3' : break;
        default: cout << "\nDONE";

    }
}

/*****************************************************************************/
/*                  Introduction function                                    */
/*****************************************************************************/ 

void intro(){
    cout << "\n\n\n\t\t STUDENT";
    cout << "\n\n\t\tREPORT CARD";
    cout << "\n\n\t\tPROJECT";
    cin.get();
}

/*****************************************************************************/
/*                       Entry / Edit menu funtion                           */ 
/*****************************************************************************/

void entryMenu(){
    char ch;
    int num;
    system("cls");
    cout << "\n\n\n\tEntry Menu";
    cout << "\n\n\t1.Create Student Record";
    cout << "\n\n\t2.Display all Students Records";
    cout << "\n\n\t3.Search Student Record";
    cout << "\n\n\t4.Modify Student Record";
    cout << "\n\n\t5.Delete Student Record";
    cout << "\n\n\t6.Back to Main Menu";
    cout << "\n\n\tPlease enter your choice (1-6)";
    cin >> ch;
    system ("cls");
    switch (ch)
    {
        case '1': writeStudent();
                    break;
        case '2': displayAll();
                    break;
        case '3': cout << "\n\n\tPlease enter the roll number";
                    cin >> num;
                    displayStudentRec(num);
                    break;
        case '4': cout << "\n\n\tPlease enter the roll number";
                    cin >> num;
                    modifyStudemt (num);
                    break;
        case '5': cout << "\n\n\tPlease enter the roll number";
                    cin >> num;
                    deleteStudent (num);
                    break;
        case '6': break;
        default:  cout << "\nDONE";
                    entryMenu();
    }
}