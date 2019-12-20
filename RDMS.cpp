//Robot Database Management System implemented using Datafile Handling in C++
#include<fstream.h>
#include<conio.h>
#include<string.h>
#include<process.h>
#include<stdio.h>

int n,i,j;    //variables for loops
char X,choice;`//variables for user choice

class Robot
{
    int serialno;
    char name[50];
    char type[50];
    float price;
    char metal[50];
    char grade;
    
   public:
   
   //Calculates grade based on metal type
    void calc(char a[])
    {
      if(strcmpi(a,"Titanium")==0)
      grade='C';
      else if(strcmpi(a,"Vibranium")==0)
           grade='A';
           else if(strcmpi(a,"Adamantium")==0)
          grade='B';
          else
          grade='D';
    }
    
    //Gets user input for new record
    void get()
    {
      cout<<"Enter the following information: ";
      cout<<"\nSerial number: "; cin>>serialno;
      cout<<"\nName: "; gets(name);
      cout<<"\nRobot type: "; gets(type);
      cout<<"\nPrice: ";cin>>price;
      cout<<"\nMetal: "; gets(metal);
      calc(metal);
    }
    
    //Displays a record
    void show()
    {
      cout<<"\nSerial number: "<<serialno;
      cout<<"\nName: "; puts(name);
      cout<<"Robot type: "; puts(type);
      cout<<"Price: "<<price;
      cout<<"\nGrade: "<<grade<<"\n";
    }
    
    //Returns the Serial number of record
    int RetSNo()
    {
      return serialno;
    }
    
    //Returns Robot name of record
    char* RetName()
    {
      return name;
    }
    
}R;

void main()
{
   clrscr();
   
   ofstream f("rob.dat",ios::out|ios::binary);  //opens a file to write in
   cout<<"\nEnter number of Robot details you wish to enter: ";
   cin>>n;  
   
   //Enter n records into file
   for(i=0;i<n;i++)
   {
      R.get();
      f.write((char*)&R,sizeof(R));
   }
   f.close(); //closes file
   
   //do while loop to keep repeating until prompted not to.
   do
   {
      clrscr();
      cout<<"\nWhat changes do you wish to do to your database? ";
      cout<<"\n1. Add a new Robot.\n2. Modify details of an existing Robot.";
      cout<<"\n3. Delete details of an existing Robot.\n4. Find Robot.";
      cout<<"\n5. Show details.\n6. Exit.\nEnter your choice: ";
      cin>>X; //Gets user choice
      clrscr();
      
      //switch case which implements user choice
      switch(X)
      {
          //Adds N records  
          case '1':  cout<<"1. Add a new Robot.";
                     ofstream f1("rob.dat",ios::app|ios::binary);
                     cout<<"\nEnter number of Robot(s) you wish to add: ";
                     int N; cin>>N;
                     for(i=0;i<N;i++)
                     {
                        R.get();
                        f1.write((char*)&R,sizeof(Robot));
                     }
                     f1.close();
                     break;

           //Modifies a record based on its record number
           case '2': cout<<"2. Modify details of an existing Robot.";
                     ofstream f2("rob.dat",ios::out|ios::ate|ios::binary);
                     cout<<"\nEnter the record number you wish to modify: ";
                     int rec; cin>>rec;
                     f2.seekp((rec-1)*sizeof(Robot),ios::beg);
                     R.get();
                     f2.write((char*)&R,sizeof(Robot));
                     f2.close();
                     break;

           //Deletes a record based on record number
           case '3': cout<<"3. Delete details of an existing Robot.";
                     ifstream f3("rob.dat",ios::in|ios::binary);
                     ofstream g;
                     g.open("rbt.dat",ios::out|ios::app|ios::binary);
                     cout<<"\nEnter the record you wish to delete: ";
                     int no,count=0; 
                     cin>>no;
                     f3.seekg(0,ios::beg);
                     while(f3.read((char*)&R,sizeof(R)))
                     {
                        if(count!=no)
                        g.write((char*)&R,sizeof(R));
                        count++;
                     }
                     f3.close();
                     g.close();
                     remove("rob.dat");
                     rename("rbt.dat","rob.dat");
                     break;

           //Finds a robot
           case '4': cout<<"4. Find Robot."; int flop=0;
                     ifstream f4("rob.dat",ios::in|ios::binary);
                     f4.seekg(0,ios::beg);
                     cout<<"\nHow do you wish to find your Robot?";
                     cout<<"\nA. By Serial number.\nB. By Name.";
                     cout<<"\nEnter your choice: "; 
                     char ch; cin>>ch;
                     
                     //Finds robot using serial number OR robot name
                     switch(ch)
                     {
                        //Search by Serial number
                        case 'A':cout<<"\nEnter Robot Serial number: ";
                                 int rsn; cin>>rsn;
                                 while(f4.read((char*)&R,sizeof(R)))
                                 {
                                   if(R.RetSNo()==rsn)
                                   {
                                      R.show();
                                      flop++;
                                   }
                                 }
                                 if(flop==0)
                                 cout<<"\nError 401 : Robot not found.";  //Robot not found
                                 break;
                                 
                        //Search by name
                        case 'B':cout<<"\nEnter Robot Name: ";int flp=0;
                                 char rn[50]; gets(rn);
                                 while(f4.read((char*)&R,sizeof(R)))
                                 {
                                    if(strcmpi(R.RetName(),rn)==0)
                                    {
                                       R.show();
                                       flp++;
                                    }
                                 }
                                 if(flp==0)
                                 cout<<"\nError 401 : Robot not found.";  //Robot not found
                                 break;
                                 
                       //Wrong choice         
                       default:cout<<"\nChoose either A or B";
                      }
                      f4.close();
                      break;

            //Display records
           case '5': cout<<"5. Show details.";
                     ifstream f5("rob.dat",ios::in|ios::binary);
                     f5.seekg(0,ios::beg);
                     while(f5.read((char*)&R,sizeof(R)))
                     {
                        R.show();
                     }
                     f5.close();
                     break;
            
            //Exits program successfully
            case '6': exit(0);
            
            //Wrong choice
            default:cout<<"Enter choice from 1 to 6 as per table above.";
      }
      
      //Case to check for repetition of do while loop
      cout<<"\nDo you wish to continue? Press 'y' to continue: "; cin>>choice;
      if(choice=='y')
        cout<<"\nGreat!";
      else
        cout<<"\nAww, too bad. Bubye!";
   } while(choice=='y');
   getch();
}
//Sriram N. V. 9th October, 2018
