#include <iostream>
#include<fstream>
#include<iomanip>

using namespace std;

class student
{

  int idnum;
  char name[50];
  int cpp, cloud_computing, drone ,hpc,evs;
  double per;
  char grade;

public:
   void calculate();
   void getdata();
   void showdata() const;
   void show_tabular() const;
   int getIDNum() const;
};

void student::calculate()
{
  per=(cpp+cloud_computing+drone+hpc+evs)/5.0;
  if(per>=90)
  grade='A+';
  else if (per>=80)
  grade='A';
  else if (per>=75)
  grade='A-';
  else if (per>=70)
  grade='B+';
  else if(per>=65)
  grade='B';
  else if (per>=60)
  grade='B-';
  else if(per>=55)
  grade='C+';
  else if (per>=50)
  grade='C';
  else 
  grade='F';
}
void student::getdata()
{
cout<<"\n Enter The ID number of the student ";
cin>>idnum; 
cout<<"\n\nEnter student's Name: ";
cin.ignore(); 
cin.getline(name,50);
cout<<"\nEnter student's CPP grade: "; 
cin>>cpp;
cout<<"\nEnter student's Cloud computing grade: "; 
cin>>cloud_computing; 
cout<<"\nEnter student's Drone grade: ";
cin>>drone;
cout<<"\nEnter student's High Performance Computing grade: ";
cin>>hpc;
cout<<"\nEnter student's Environmental studies grade: "; 
cin>>evs; 
calculate(); 
} 

void student::showdata() const
{
  cout<<"\nID Number: " <<idnum;
  cout<<"\nName: "<<name;
  cout<<"\nCPP: "<<cpp;
  cout<<"\ncloud_computing: "<<cloud_computing;
  cout<<"\ndrone: "<<drone;
  cout<<"\nHigh Performance computing: "<<hpc;
  cout<<"\nEnvironmental studies: "<<evs;
  cout<<"\nPercentage: "<<per;
  cout<<"\nLetter Grade: "<<grade;
}

void student::show_tabular() const
{
  cout<<idnum<<setw(6)<<" "<<name<<setw(10)<<cpp<<setw(4)<<cloud_computing<<setw(4)<<drone<<setw(4)<<hpc<<setw(4)<<evs<<setw(8)<<per<<setw(6)<<grade<<endl;
}

int student::getIDNum() const
{
  return idnum;
}

void SaveStudent();
void displayAll();
void Searchdisplay(int);
void modifyStudent(int);
void DisplayClassResult();
void DisplayResult();

void write_student()
{
  student st;
  ofstream outFile;
  outFile.open("student.dat",ios::binary|ios::app);
  st.getdata();
  outFile.write(reinterpret_cast<char *> (&st), sizeof(student));
  outFile.close();
  cout<<"\n\nStudent record has been Created ";
  cin.ignore();
  cin.get();
}

void display_all()
{
  student st;
  ifstream inFile;
  inFile.open("student.dat",ios::binary);
  if(!inFile)
  {
    cout<<"File could not be open !! press any key....";
    cin.ignore();
    cin.get();
    return;
  }

  cout<<"\n\n\n\tDISPLAY ALL RECORD !!\n\n";
  while(inFile.read(reinterpret_cast<char *>(&st),sizeof(student)))
  {
    st.showdata();
    cout<<"\n\n============================\n";
  }
    inFile.close();
    cin.ignore();
    cin.get();
}

  void display_sp(int n)
  {
    student st;
    ifstream inFile;
    inFile.open("student.dat",ios::binary);
    if(!inFile)
    {
      cout<<"File could not be open !! press any key...";
      cin.ignore();
      cin.get();
      return;
    }

    bool flag=false;
    while(inFile.read(reinterpret_cast<char*>(&st),sizeof(student)))
    {
      if(st.getIDNum()==n){
        st.showdata();
        flag=true;
      }
    }
    inFile.close();
    if(flag==false)
    cout<<"\n\nrecord not exist";
    cin.ignore();
    cin.get();
  }

void modify_student(int n)
{
  bool found=false;
  student st;
  fstream File;
  File.open("student.dat",ios::binary|ios::in|ios::out);
  if(!File)
  {
    cout<<"File could not be open !! press any key...";
    cin.ignore();
    cin.get();
    return;
  }
  while(!File.eof() && found==false)
  {
    File.read(reinterpret_cast<char*>(&st), sizeof(student));
    if(st.getIDNum()==n)
    {
      st.showdata();
      cout<<"\n\nPlease  Enter The New Details of student"<<endl;
      st.getdata();
      int pos=(-1)*static_cast<int>(sizeof(st));
      File.seekp(pos,ios::cur);
      File.write(reinterpret_cast<char *>(&st),sizeof(student));
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


void delete_student(int n)
{
  student st;
  ifstream inFile;
  inFile.open("student.dat",ios::binary);
  if(!inFile){
    cout<<"File could not be open !! press any key...";
    cin.ignore();
    cin.get();
    return;
  }
  ofstream outFile;
  outFile.open("Temp.dat",ios::out);
  inFile.seekg(0,ios::beg);
  while(inFile.read(reinterpret_cast<char *> (&st),sizeof(student)))
  {
    if(st.getIDNum()!=n)
    {
      outFile.write(reinterpret_cast<char *>(&st), sizeof(student));
    }
  }
  outFile.close();
  inFile.close();
  remove("student.dat");
  rename("Temp.dat","student.dat");
  cout<<"\n\n\tRecord Deleted ..";
  cin.ignore();
  cin.get();
}

void class_result()
{
  student st;
  ifstream inFile;
  inFile.open("student.dat",ios::binary);
  if(!inFile)
  {
    cout<<"File could not be open !! press any key...";
    cin.ignore();
    cin.get();
    return;
  }
  cout<<"\n\n\t\tALL STUDENTS RESULT \n\n";
  cout<<"=========================================\n";
  cout<<"R.No    Name      C++ CC   D   HPC  EVS  %age   GRADE"<<endl;
  cout<<"=========================================\n";
  while (inFile.read(reinterpret_cast<char *>(&st),sizeof(student)))
  {
    st.show_tabular();
  }
  cin.ignore();
  cin.get();
  inFile.close();
}

int main() 
{
 char ch;
 int num;
 cout.setf(ios::fixed|ios::showpoint);
 cout<<setprecision(2);
 do
 {
   cout<<"\n\n";
   cout<<"\t\t\tSTUDENT MANAGEMET SYSTEM";
   cout<<"\n\n\t++++++++++++++++++++++++++++++++++++";
   cout<<"\n\n\t\t\t1.CREATE STUDENT RECORD";
   cout<<"\n\n\t\t\t2.DISPLAY ALL STUDENTS RECORDS";
   cout<<"\n\n\t\t\t3.DISPLAY ALL STUDENT RECORDS";
   cout<<"\n\n\t\t\t4.MODIFY STUDENT RECORD";
   cout<<"\n\n\t\t\t5.DELETE SSTUDENT RECORD";
   cout<<"\n\n\t\t\t6. DISPLAY CLASS RESULT";
   cout<<"\n\n\t\t\t7. EXIT";
   cout<<"\n\n\t++++++++++++++++++++++++++++++++++++";
   cout<<"\n\n\t\t\tplease Enter your choice(1-7): ";
   cin>>ch;

   switch(ch)
   {
     case '1': write_student(); break;
     case '2':display_all(); break;
     case '3': cout<<"\n\n\tPlease Enter Student's ID number: ";
     cin>>num;
          display_sp(num); break;
    case '4': cout<<"\n\n\tPlease Enter Student's ID number: ";
    cin>>num;
         modify_student(num); break;
    case '5': cout<<"\n\n\tPlease Enter Student's ID number: ";
    cin>>num;
         delete_student(num); break;  
    case '6' : class_result(); break;
    case '7' : exit(0);;
    default:cout<<"\a";        

   }
 }while(ch!='7');

 return 0;
}
