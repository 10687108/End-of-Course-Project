#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;



//   CLASS USED IN PROJECT


class student
{
	int rollno;
	char name[60];
	double p_marks, c_marks, m_marks, e_marks, cs_marks;
	double per;
	char grade;
	void calculate();	
public:
	void getdata();		
	void showdata() const;	
	void show_tabular() const;
	int retrollno() const;
}; 

//function to calculate grade
void student::calculate()
{
	per=(p_marks+c_marks+m_marks+e_marks+cs_marks)/5.0;
	if(per>=80)
		grade='A';
	else if(per<=79 )
		grade='B+';
	else if(per<=74 )
		grade='B';
	
};
//function to accept data from user
void student::getdata()
{
	cout<<"\nEnter The roll number of student ";
	cin>>rollno;
	cout<<"\n\nEnter The Name of student ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nEnter The marks in physics out of 100 : ";
	cin>>p_marks;
	cout<<"\nEnter The marks in chemistry out of 100 : ";
	cin>>c_marks;
	cout<<"\nEnter The marks in maths out of 100 : ";
	cin>>m_marks;
	cout<<"\nEnter The marks in english out of 100 : ";
	cin>>e_marks;
	cout<<"\nEnter The marks in computer science out of 100 : ";
	cin>>cs_marks;
	calculate();
}
//function to show data on screen
void student::showdata() const
{ 
    cout<<"\n *****Display of Results*****";
	cout<<"\nRoll number of student : "<<rollno;
	cout<<"\nName of student : "<<name;
	cout<<"\nMarks in Physics : "<<p_marks;
	cout<<"\nMarks in Chemistry : "<<c_marks;
	cout<<"\nMarks in Maths : "<<m_marks;
	cout<<"\nMarks in English : "<<e_marks;
	cout<<"\nMarks in Computer Science :"<<cs_marks;
	cout<<"\nPercentage of student is  :"<<per;
	cout<<"\nGrade of student is :"<<grade;
}

void student::show_tabular() const
{
	cout<<rollno<<setw(7)<<" "<<name<<setw(11)<<p_marks<<setw(5)<<c_marks<<setw(5)<<m_marks<<setw(5)
		<<e_marks<<setw(5)<<cs_marks<<setw(9)<<per<<setw(7)<<grade<<endl;
}

int  student::retrollno() const
{
	return rollno;
}



//  function declaration


void write_student();	//write the record in file
void display_all();	//read all records from file
void display_sp(int);	//accept rollno and read record from file
void modify_student(int);	//accept rollno and update record of file
void delete_student(int);	//accept rollno and delete selected records from file
void class_result();	//display all records in tabular format from file
void result();		//display result menu
void intro();		//display welcome screen
void entry_menu();	//display entry menu on screen



// THE MAIN FUNCTION OF PROGRAM



int main()
{
   cout<<fixed<<showpoint<<setprecision(2);
	char ch;
	cout.setf(ios::fixed|ios::showpoint);
	cout<<setprecision(2); // program outputs decimal number to two decimal places
	intro();
	do
	{
		system("cls");
		cout<<"\n\n\n\tMAIN PAGE";
		cout<<"\n\n\t01. RESULT PAGE";
		cout<<"\n\n\t02. EDIT/ENTRY PAGE";
		cout<<"\n\n\t03. EXIT PAGE";
		cout<<"\n\n\tKindly Select An Option (1-3) ";
		cin>>ch;
		switch(ch)
		{
			case '1': result();
				break;
			case '2': entry_menu();
				break;
			case '3':
				break;
			default :cout<<"\a";
		}
    }while(ch!='3');
	return 0;
}


// function to write in file

void write_student()
{
	student st;
	ofstream outFile;
	outFile.open("student.dat",ios::binary|ios::app);
	st.getdata();
	outFile.write(reinterpret_cast<char *> (&st), sizeof(student));
	outFile.close();
    	cout<<"\n\nStudent record Has Been Created ";
	cin.ignore();
	cin.get();
}


// function to read all records from file


void display_all()
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\n\t\tDISPLAY ALL RECORDS !!!\n\n";
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		st.showdata();
		cout<<"\n\n====================================\n";
	}
	inFile.close();
	cin.ignore();
	cin.get();
}


//  function to read specific record from file


void display_sp(int n)
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag=false;
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		if(st.retrollno()==n)
		{
	  		 st.showdata();
			 flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nrecord does not exist";
	cin.ignore();
	cin.get();
}


// function to modify record of file


void modify_student(int n)
{
	bool found=false;
	student st;
	fstream File;
	File.open("student.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
    	while(!File.eof() && found==false)
	{

		File.read(reinterpret_cast<char *> (&st), sizeof(student));
		if(st.retrollno()==n)
		{
			st.showdata();
			cout<<"\n\nPlease Enter The New Details of student"<<endl;
			st.getdata();
		    	int pos=(-1)*static_cast<int>(sizeof(st));
		    	File.seekp(pos,ios::cur);
		    	File.write(reinterpret_cast<char *> (&st), sizeof(student));
		    	cout<<"\n\n\t Record Updated";
		    	found=true;
		}
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
	cin.ignore();
	cin.get();
}


//  function to delete record of file


void delete_student(int n)
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	ofstream outFile;
	outFile.open("temp.dat",ios::out);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		if(st.retrollno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&st), sizeof(student));
		}
	}
	outFile.close();
	inFile.close();
	remove("student.dat");
	rename("temp.dat","student.dat");
	cout<<"\n\n\tRecord Deleted ..";
	cin.ignore();
	cin.get();
}


// function to display all students grade report


void class_result()
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\t\tALL STUDENTS RESULT \n\n";
	cout<<"==========================================================\n";
	cout<<"R.No       Name        P   C   M   E   CS   %age   Grade"<<endl;
	cout<<"==========================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		st.show_tabular();
	}
	cin.ignore();
	cin.get();
	inFile.close();
}


//  function to display result menu


void result()
{
	char ch;
	int rno;
	system("cls");
	cout<<"\n\n\n\tRESULT PAGE";
	cout<<"\n\n\n\t1. Class Result";
	cout<<"\n\n\t2. Student Report Card";
	cout<<"\n\n\t3. Return To Main Menu";
	cout<<"\n\n\n\tEnter Choice (1/2/3)? ";
	cin>>ch;
	system("cls");
	switch(ch)
	{
	case '1' :	class_result(); break;
	case '2' :	cout<<"\n\n\t Please Enter Student Roll No. : "; cin>>rno;
				display_sp(rno); break;
	case '3' :	break;
	default:	cout<<"\a";
	}
}


//    	INTERFACE FUNCTION


void intro()
{
	cout<<"\n\n\n\t\t WELCOME TO THE SCHOOL MANAGEMENT SYSTEM";
	cout<<"\n\n\n\tCREATED BY : KOBIRI SOLOMON OWUSU - 10687108";
	cout<<"\n\t\t\t DEPARTMENT OF COMPUTER SCIENCE";
	cout<<"\n\t\t\t UNIVERSITY OF GHANA, LEGON";
	cout<<"\n\t\tPress any key to continue."<<endl;
	cin.get();
}


//   ENTRY / EDIT MENU FUNCTION

void entry_menu()
{
	char ch;
	int num;
	system("cls");
	cout<<"\n\n\n\tENTRY PAGE";
	cout<<"\n\n\t1.CREATE STUDENT RECORD";
	cout<<"\n\n\t2.DISPLAY ALL STUDENT RECORDS";
	cout<<"\n\n\t3.SEARCH STUDENT RECORD ";
	cout<<"\n\n\t4.MODIFY STUDENT RECORD";
	cout<<"\n\n\t5.DELETE STUDENT RECORD";
	cout<<"\n\n\t6.RETURN TO MAIN MENU";
	cout<<"\n\n\tPlease Enter Your Choice (1-6) ";
	cin>>ch;
	system("cls");
	switch(ch)
	{
	case '1':	write_student(); break;
	case '2':	display_all(); break;
	case '3':	cout<<"\n\n\tKindly Enter The roll number "; cin>>num;
			display_sp(num); break;
	case '4':	cout<<"\n\n\tKindly Enter The roll number "; cin>>num;
			modify_student(num);break;
	case '5':	cout<<"\n\n\tKindly Enter The roll number "; cin>>num;
			delete_student(num);break;
	case '6':	break;
	default:	cout<<"\a"; entry_menu();
	}
}


//  THE	END

