#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "Personinfo.h"
#include "Fitinfo.h"


using namespace std ;


class staffFitness : public personInfo
{
	private :
		fitInfo FitInfo ;
		string dob , wCategory;
		double age ;
		double bmi ;
		double bmr ;
		double rmr ;

	public :
		staffFitness ()           //Constructor
		{
			dob = " " ;
			wCategory = " " ;
			age = 0 ;
			bmi = bmr = rmr = 0 ;
		}
		~staffFitness ()          //Destructor
		{
			dob = " " ;
			wCategory = " " ;
			age = 0 ;
			bmi = bmr = rmr = 0 ;
		}
		double getAge () { return age ; }
		double getBMI () { return bmi ; }
		double getBMR () { return bmr ; }
		double getRMR () { return rmr ; }
		void calAge ( long long int ) ;              //Function start with cal is to use for calculating the particular data
		void calDOB ( long long int ) ;              //Calculate date of birth
		void calBMI ( double , double ) ;
		void calBMR ( int , int , int , string ) ;
		void calRMR ( int , int , int , string ) ;
		void calWCat () ;                             //Calculate weight category
		void setStaffFitness (long long int , string , string , long long int , double , double );
		void displayStaffFitness () ;
		friend int search ( staffFitness [] , int , long long int ) ;   //Friend functions
		friend void modify ( staffFitness [] , int  ) ;
		friend void stats ( staffFitness [] , int   ) ;
		friend void dietPlan ( staffFitness [] , int ) ;
		friend int dietPlan2( staffFitness [] , int  ) ;
		friend void comSearch( staffFitness obj [] , int index  ) ;



};

void staffFitness::calAge ( long long int stafID )  //Function to calculate age
{
	stringstream ss1 ;
	string a ;

	ss1 << stafID ;
	ss1 >> a ;
	ss1.clear() ;
	a=a.substr(0,2) ;
	ss1 << a ;
	ss1 >> age ;
	age = 120 - age ;
}

void staffFitness::calDOB ( long long int stafID )   //Function to calculate date of birth
{
	stringstream ss1 ;
	string a , y , m , d ;

	ss1 << stafID ;
	ss1 >> a ;
	ss1.clear () ;
	y = a.substr(0,2) ;
	m = a.substr(2,2) ;
	d = a.substr(4,2) ;
	dob = d + "/" + m + "/19" + y ;
}

void staffFitness::calBMI ( double w , double h )
{
	bmi = (w /  ( h/100  *   h/100 ) );
	//bmi[b] = weight[b] / (height[b]/100 * height[b]/100);
}

void staffFitness::calBMR ( int w , int h , int a , string g )
{
	if (g=="Male")
	{
		bmr = (10*w) + (6.25*h) - (5*a) + 5 ;
	}
	else
		bmr = (10*w) + (6.25*h) - (5*a) - 161 ;
}

void staffFitness::calRMR ( int w , int h , int a , string g )
{
	if (g=="Male")
	{
		rmr = 88.362 + (13.397*w) + (4.799*h) - (5.677*a) ;
	}
	else
		rmr = 447.593 + (9.247*w) + (3.098*h) - (4.330*a) ;
}

void staffFitness::calWCat ()       // Function to calculate weight category
{
	if ( bmi<20 )
		wCategory = "Underweight";
	else if ( bmi >= 20 && bmi <25)
		wCategory = "Normal weight";
	else if ( bmi >= 25 && bmi <30)
		wCategory = "Overweight";
	else
		wCategory = "Obese" ;
}

void staffFitness::setStaffFitness ( long long int stafID , string name , string gender , long long int staffID , double weight , double height  )
{
	setPerson ( stafID , name, gender ) ;                    //All the data in class staffFitness is calculate when input is taken
	FitInfo.setFit( staffID , weight , height ) ;
	calAge ( stafID ) ;
	calDOB ( stafID ) ;
	calBMI ( weight , height ) ;
	calBMR ( weight , height , age , gender ) ;
	calRMR ( weight , height , age , gender ) ;
	calWCat () ;

}

void staffFitness::displayStaffFitness ()
{
	cout << "Staff ID           :" << getsID() << "\n";
	cout << "Name               :" << getName() << "\n";
	cout << "gender             :" << getGender() << "\n";
	cout << "staff ID           :" << FitInfo.getSID() << "\n";
	cout << "Weight(kg)         :" << FitInfo.getWeight() << " kg\n";
	cout << "Height             :" << FitInfo.getHeight() << " cm\n";
	cout << "Age                :" << age << " years old\n" ;
	cout << "Date of Birth      :" << dob << "\n" ;
	cout << "BMI                :" << bmi << "\n" ;
	cout << "BMR                :" << bmr << "\n" ;
	cout << "RMR                :" << rmr << "\n" ;
	cout << "Weight Category    :" << wCategory << "\n" ;
	cout << "------------------------------------------------------------------------\n" ;
}

//------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------

void intro () ;//Display Let's Get Fit !! .Can be used anytime anywhere

void menu () ; //Main Menu

void menuM () ;  // Menu for data modifying

void menuCS () ; // Menu for combine search

int search ( staffFitness [] , int , long long int ) ;

void readFile ( staffFitness []  , int &) ; // function to read file

int validSID ( long long int & ) ;

int validSID0 ( staffFitness []  , int , long long int & ) ;  //When Staff ID need to be new

int validSID1 ( staffFitness [] , int , long long int & ) ;  //When Staff ID need to exist before input

int validN ( string & );

int validG ( string & );

int validW ( int & );

int validH ( int & );

void validyon( string & );

void validRange ( int , double & ,double & );

int exitF ();

void addData( staffFitness [] , int &  );

void modify ( staffFitness []  , int ) ;

void comSearch( staffFitness [] , int ) ;

void dietPlan ( staffFitness [] , int ) ;

int dietPlan2( staffFitness [] , int x ) ;

void stats ( staffFitness [] , int ) ;

void deleteData ( staffFitness [] , int & ) ;

//------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------

int main ()
{
	int index ,choice ,exit , weight , height;
	index = exit = 0 ;
	staffFitness obj[200] ;
	long long int stafID ;
	string name  , gender  ;
	cout<<fixed<<showpoint<<setprecision(2);

	readFile (obj , index) ;
	system ("pause") ;

	do
	{
		system("cls") ;
		menu () ;
		cout << "Enter the number you wish to navigate to:" ;
		cin >> choice ;
		if ( cin.fail() || choice<0 && choice>9 )
		{
			system ("cls") ;
			cin.clear() ;
			cin.ignore() ;
			menu() ;
			cout << "Invalid input !!" << endl ;
			cout << "Please enter a number ." << endl ;
			cout << "Enter the number you wish to navigate to:" ;
			cin >> choice ;
			system ("cls") ;
		}
		switch ( choice )
		{
			case 1 :
				system ("cls") ;
				addData(obj , index) ;
				system ("Pause") ;
				system ("cls") ;
				break ;

			case 2 :

				system ("cls") ;
				modify( obj , index ) ;
				system ("Pause") ;
				system ("cls") ;
				break ;

			case 3 :
				{
					system ("cls") ;
					int e = 1 ;
					int x ;
					long long int ID ;
					while (e==1)
					{
						system ("cls") ;
						intro () ;
						cout << "Please nter the staff ID of the staff you are looking for\n" ;
						cout << "Staff ID :" ;
						cin >> ID ;
						validSID (ID) ;
						x=search ( obj , index , ID) ;
						if (x<0)
						{
							cout << "Staff ID does not exist . \n" ;
							e=exitF() ;
						}
						else
						{
							cout << "\nStaff ID found ! \n" ;
							cout << "------------------------------------------------------------------------\n" ;
							obj[x].displayStaffFitness() ;
							e=exitF() ;
						}
					}
					system ("Pause") ;
					break ;
				}

			case 4 :
				system ("cls") ;
				comSearch( obj ,  index  ) ;
				system ("Pause") ;
				system ("cls") ;
				break ;

			case 5 :
				system ("cls") ;
				dietPlan ( obj , index ) ;
				system ("Pause") ;
				system ("cls") ;
				break ;

			case 6 :
				system ("cls") ;
				intro () ;
				for(int j = 0 ; j<index ; j++)
				{
					obj[j].displayStaffFitness() ;
				}

				system ("Pause") ;
				system ("cls") ;
				break ;

			case 7 :
				system ("cls") ;
				stats ( obj ,index  );
				system ("Pause") ;
				break ;

			case 8 :
				system ("cls") ;
				deleteData ( obj , index ) ;
				system ("Pause") ;
				break ;

			case 9 :
				{
					system ("cls") ;
					string yon ;
					intro () ;
					cout << "Are you sure you want to exit the program ? ('Yes'or'No') \n" ;
					cout << "Choice:" ;
					cin >> yon ;
					validyon(yon) ;
					if (yon=="Yes" || yon=="yes")
					{
						cout << "\nThank for using Let's Go Fit !! \n" ;
						exit = -1 ;
					}
					else if  (yon=="No" || yon=="No")
						exit = 0 ;
					break ;
				}


			default :
				cout << "Invalid Input !!" << endl ;
				break ;

		}



	}while ( exit==0 ) ;

	system ("PAUSE") ;

	return 0 ;
}


//------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------

void intro ()  //Display Let's Get Fit !! .Can be used anytime anywhere
{
	cout << "\t\t\t _________________________________________________________ "<<endl << "\t\t\t|" ;
	cout.width(58) ;
	cout <<  "|" << endl << "\t\t\t|" ;
	cout.width(58) ;
	cout <<  "|" << endl << "\t\t\t|\t\t\tLET'S GET FIT!!	";
	cout.width(19) ;
	cout <<  "|" << endl << "\t\t\t|" ;
	cout.width(58) ;
	cout <<  "|" << endl << "\t\t\t|_________________________________________________________|"<<endl << endl;

}

void menu ()  //Main Menu
{
	cout << "\t\t\t _________________________________________________________ \n"<< "\t\t\t|" ;
	cout.width(59) ;
	cout << "|\n" << "\t\t\t|" ;
	cout.width(59) ;
	cout << "|\n" << "\t\t\t|\t\t\tLET'S GET FIT!!	";
	cout.width(20) ;
	cout << "|\n" << "\t\t\t|" ;
	cout.width(59) ;
	cout << "|\n" << "\t\t\t|_________________________________________________________|"<<"\n\t\t\t|" ;
	cout.width(59) ;
	cout << "|\n" << "\t\t\t|1. Add new staff information";
	cout.width (31) ;
	cout << "|\n" << "\t\t\t|2. Modify staff information";
	cout.width (32) ;
	cout << "|\n" << "\t\t\t|3. Search staff information by staff ID";
	cout.width (20) ;
	cout << "|\n" << "\t\t\t|4. Search staff information by combinational information";
	cout.width (3) ;
	cout << "|\n" << "\t\t\t|5. Diet Planning";
	cout.width (43) ;
	cout << "|\n" << "\t\t\t|6. Display all staff information";
	cout.width (27) ;
	cout << "|\n" << "\t\t\t|7. Statistical information";
	cout.width (33) ;
	cout << "|\n" << "\t\t\t|8. Delete specific staff information";
	cout.width (23) ;
	cout << "|\n" << "\t\t\t|9. Exit";
	cout.width (52) ;
	cout << "|\n" << "\t\t\t|_________________________________________________________|\n\n"  ;
}

void menuM ()   // Menu for data modifying
{
	intro () ;
	cout << "\t\t\t _________________________________________________________ \n" << "\t\t\t|";
	cout.width(59) ;
	cout << "|\n"<<"\t\t\t|\tWhat data you would like to modify?  "  ;
	cout.width(15) ;
	cout << "|\n"<<"\t\t\t|" ;
	cout.width(59) ;
	cout << "|\n"<<"\t\t\t|1. Staff ID" ;
	cout.width(48) ;
	cout << "|\n"<<"\t\t\t|2. Name " ;
	cout.width(51) ;
	cout << "|\n"<<"\t\t\t|3. Gender " ;
	cout.width(49) ;
	cout << "|\n"<<"\t\t\t|4. Weight " ;
	cout.width(49) ;
	cout << "|\n"<<"\t\t\t|5. Height " ;
	cout.width(49) ;
	cout << "|\n"<<"\t\t\t|_________________________________________________________|\n" ;

}

int search ( staffFitness obj[]  , int index, long long int ID )
{
	for (int i = 0 ; i<index ; i++)
	{
		if (ID==(obj[i].getsID()))
		{
			//obj[i] .displayStaffFitness () ;
			return i ;
		}
	}
	return -1 ;
}


void readFile ( staffFitness obj[]  , int &index )  // function to read file
{

	long long int stafID , staffID ;
	int height ,weight ;
	string filename1 , filename2 , name , gender ;
	ifstream perInfo , fitInfo ;
	stringstream ss ;
	string str ;
	int lineP , lineF , lineFP , lineFF ,F;
	lineP = lineF = lineFP = lineFF = F = 0 ;
	intro() ;
//read file
	cout << "Please enter the file name to input staff info and fitness info.(Exp : staffInfo , fitnessInfo ) \n" ;

//read staff info file
	cout << "Staff info file name : \n" ;
	cin >> filename1 ;
	filename1 = filename1 + ".txt" ;
	perInfo.open( filename1.c_str()) ;

	while (!perInfo)
	{
		cout << "Invalid file ! Enter a valid file name : \n" ;
		cout << "(Exp : staffInfo , fitnessInfo ) \n" ;
		cin >> filename1 ;
		filename1 = filename1 + ".txt" ;
		perInfo.open( filename1.c_str()) ;
	}
//read fitness info file
	cout << "Fitness info file name : \n" ;
	cin >> filename2 ;
	filename2 = filename2 + ".txt" ;
	fitInfo.open( filename2.c_str()) ;

	while (!fitInfo)
	{
		cout << "Invalid file ! Enter a valid file name : \n" ;
		cout << "(Exp : staffInfo , fitnessInfo ) \n" ;
		cin >> filename2 ;
		filename2 = filename2 + ".txt" ;
		fitInfo.open( filename2.c_str()) ;
	}

//Pass input data into variable

	while (!perInfo.eof())      //First step :Read personal info file and input the data
	{
		getline (perInfo , str , '\t'  ) ;  // StaffID is read as string
		//cout << "str=" << str << endl ;
		ss << str;                          //string->stringtream
		ss >> stafID ;                      //stringtream->int

		ss.clear() ;
		getline (perInfo , name , '\t') ;

		getline (perInfo , gender , '\n' ) ;
		//perInfo.ignore(1000,'\n') ;
        int x = -1 ;
        x=search(obj , index , stafID );
	//	F=0 ;
		while (  !fitInfo.eof())  //Second step :Read fitness info file and input the data
		{
			fitInfo >> staffID ;

			{
				if ( stafID != staffID ) //To find the staff ID in fitness file that match with staff ID in person file
				{
					fitInfo.ignore(1000,'\n') ;

					continue ;
				}
				else
					{                                           //Data is input if staff ID matched

						fitInfo >> weight ;

						fitInfo >> height ;


						if ( stafID > 400000000000 && stafID<999999999999 && staffID > 400000000000 && stafID<999999999999 && x<0 && name.substr(0,1)!=" " && name.substr(0,1)!="	" &&
					        name != "" && name!= "\t" &&( gender=="Male" || gender=="Female" ) && ( weight>1 && weight<595 ) && ( height>1 && height<272 )  )
						{
							obj[index].setStaffFitness (stafID,name,gender,staffID,weight,height) ;
							index++ ;
	

							break ;
						}
					}
			}


		}

		fitInfo.clear() ;
		fitInfo.seekg(0, fitInfo.beg);

	}
    fitInfo.clear() ;
    fitInfo.seekg(0, fitInfo.beg);

    perInfo.clear() ;
    perInfo.seekg(0, fitInfo.beg);
	while (!perInfo.eof())
	{
		lineP ++ ;
		getline (perInfo , str , '\t'  ) ;  // StaffID is read as string

		ss << str;                          //string->stringtream
		ss >> stafID ;                      //stringtream->int

		ss.clear() ;
		getline (perInfo , name , '\t') ;

		getline (perInfo , gender  ) ;
	
  
		if ( cin.fail() || stafID<400000000000 || stafID>999999999999 || name.substr(0,1)==" " || name.substr(0,1)=="	"
             || name==" " || name=="  " || name=="" || ( gender!="Male" && gender!="Female" ) )
		{
			cout << "Error reading file '"<< filename1 << "' line " << lineP << " .\n" ;
			lineFP ++ ;

		}
        stafID=0 ;
	}

	while ( !fitInfo.eof() )
	{
		lineF ++ ;
		fitInfo >> staffID ;
		if (cin.fail())
		{
			cin.ignore() ;
		   	cin.clear() ;
		   	fitInfo.ignore() ;
			break ;
						}
		fitInfo >> weight ;

        if (cin.fail())
		{
		  	weight = 0 ;
			cin.clear() ;
		    cin.ignore() ;

			fitInfo.ignore() ;
			cout << "Error reading file '"<< filename2 << "' line " << lineF << " .\n" ;
             lineFF ++ ;
						  
						}  
		fitInfo >> height ;

	if (cin.fail())
						{
						    height = 0 ;
						    cin.clear() ;
						    cin.ignore() ;

						    fitInfo.ignore() ;

						    cout << "Error reading file '"<< filename2 << "' line " << lineF << " .\n" ;
                            lineFF ++ ;
						   
						}

		 if ( cin.fail() || staffID<400000000000 || staffID>999999999999 || weight<1 || weight>595 || height<1 || height>272 )
		{
			cout << "Error reading file '"<< filename2 << "' line " << lineF << " .\n" ;
			lineFF ++ ;
			cin.ignore() ;
			cin.clear() ;
			fitInfo.ignore() ;
		
		}
  
	}
    lineF -- ;
	lineFP = lineP - lineFP ;
	lineFF = lineF - lineFF ;
	cout << "\n" ;
	cout << "File '" << filename1 << "' contain " << lineP << " lines of data .\n\n" ;
	cout << lineFP << " lines can be extracted while " << index << " lines of data are successfully extracted .\n\n";

	cout << "File '" << filename2 << "' contain " << lineF << " lines of data .\n\n" ;
	cout << lineFF << " lines can be extracted while " << index << " lines of data are successfully extracted .\n\n" ;

}

int validSID ( long long int &ID )
{
	while( cin.fail() || ID<400000000000 || ID >999999999999 )
	{
		cin.clear() ;
		cin.ignore( 1000 , '\n' ) ;
		system("cls") ;
		intro () ;
		cout << "\nInvalid Input !! " << endl ;
		cout << "Please enter a valid ID(Exp: '990845048765' )" << endl ;
		cout << "Reminder : Only staff with age between 21-80 years old is accepted." << endl ;
		cout << "Staff ID    : " ;
		cin >> ID ;
	}
	return 1 ;
}


int validSID0 ( staffFitness obj[]  , int index , long long int &ID )   //When Staff ID need to be new
{
	int x ;
	x=search ( obj   , index ,  ID) ;
	while( cin.fail() || ID<400000000000 || ID >999999999999 || x>=0 )
	{
		cin.clear() ;
		cin.ignore( 1000 , '\n' ) ;
		x=search ( obj   , index ,  ID) ;
		cout << "\nInvalid Input !! " << endl ;
		if (x>=0)
		{
			cout << "Staff ID cannot be repeated !! \n" ;
		}
		cout << "Please enter a valid ID(Exp: '990845048765' )" << endl ;
		cout << "Reminder : Only staff with age between 21-80 years old is accepted." << endl ;
		cout << "Staff ID    : " ;
		cin >> ID ;
		x=search ( obj   , index ,  ID) ;
	}
	return 1 ;
}

int validSID1 ( staffFitness obj[]  , int index , long long int &ID )   //When Staff ID need to exist before input
{
	int x ;
	x=search ( obj   , index ,  ID) ;
	cout <<"x=" << x << endl ;
	while( cin.fail() || ID<400000000000 || ID >999999999999 || x<0 )
	{
		cin.clear() ;
		cin.ignore( 1000 , '\n' ) ;
		system("cls") ;
		x=search ( obj   , index ,  ID) ;
		intro () ;
		cout << "\nInvalid Input !! " << endl ;
		if (x<0)
		{
			cout << "Staff ID does not exist !! \n" ;
		}
		cout << "Please enter a valid ID(Exp: '990845048765' )" << endl ;
		cout << "Reminder : Only staff with age between 21-80 years old is accepted." << endl ;
		cout << "Staff ID    : " ;
		cin >> ID ;
	}
	return 1 ;
}

int validN ( string &n )
{
	while ( cin.fail())
	{
		cin.clear() ;
		cin.ignore( 1000 , '\n' ) ;
		cout << "\nInvalid Input !! \n" ;
		cout << "Please enter your name\n" ;
		cout << "Name        : " ;
		cin >> n ;
	}
	return  1 ;
}

int validG ( string &g  )
{
	while ( cin.fail() || ( g!="Male" && g!="Female" ) )
	{
		cin.clear() ;
		cin.ignore( 1000 , '\n' ) ;
		cout << "\nInvalid Input !! \n" ;
		cout << "Please enter 'Male' or 'Female' \n" ;
		cout << "Gender      : " ;
		cin >> g ;
	}
	return  1 ;
}

int validW ( int &w )
{
	while ( cin.fail() || ( w<1 || w>595 ) )
	{
		cin.clear() ;
		cin.ignore( 1000 , '\n' ) ;
		cout << "\nInvalid Input !! \n" ;
		cout << "Please enter your weight in (kg) \n" ;
		cout << "Reminder: Weight input must between 1-595 kg since the heaviest man in the world 595kg \n" ;
		cout << "Weight (kg) : " ;
		cin >> w ;
	}
	return 1 ;
}

int validH ( int &h )
{
	while ( cin.fail() || ( h<1 || h>272 ) )
	{
		cin.clear() ;
		cin.ignore( 1000 , '\n' ) ;
		cout << "\nInvalid Input !! \n" ;
		cout << "Please enter your Height in (cm) \n" ;
		cout << "Reminder: Height input must between 1-272 cm since the tallest man in the world 272cm \n" ;
		cout << "Height (cm) : " ;
		cin >> h ;

	}
	return 1 ;
}

void validyon( string &yon )
{
	while ( cin.fail() || ( yon!="Yes" && yon!="yes" && yon!="No" && yon!="no" ) )
	{
		cin.clear() ;
		cin.ignore(1000,'\n');
		cout << "\nPlease enter 'Yes' or 'No' ! \n" ;
		cout << "Choice:" ;
		cin >> yon ;
	}
}

int exitF ()
{
	string yon ;
	cout << "\nDo you wish to continue ? ('Yes' or 'No')\n" ;
	cout << "Choice:" ;
	cin  >> yon ;
	validyon ( yon ) ;
	if ( (yon=="Yes") || (yon=="yes") )
	{
		return 1 ;
	}
	else if ( (yon=="No") || (yon=="No") )
	{
		return -1 ;
	}
}

void addData( staffFitness obj [] , int &index  )
{
	int e ;
	e=1 ;
	while (e>0)
	{
		long long int sID ;
		string n , g ;
		int w , h ;
		intro () ;
		cout << "Add New Staff Data\n\n"  ;
		cout << "Staff ID        :" ;
		cin >> sID ;
		validSID0 (obj,index,sID) ;
		cout << "\nName          :" ;
		cin >> n ;
		validN (n) ;
		cout << "\nGender        :" ;
		cin >> g ;
		validG (g) ;
		cout << "\nWeight (kg)   :" ;
		cin >> w ;
		validW (w) ;
		cout << "\nHeight (cm)   :" ;
		cin >> h ;
		validH (h) ;

		obj[index].setStaffFitness (sID,n,g,sID,w,h) ;
		index ++ ;
		e = exitF() ;
		system("cls") ;
	}
}

void modify ( staffFitness obj []  , int index  )
{
	long long int s ;
	int x ,c ;
	int e = 1 ;
	intro () ;
	cout << "Enter the ID of the staff that you like to Modify his data \n" ;
	cout << "Staff ID : " ;
	cin >> s ;
	validSID ( s ) ;
	x = search ( obj , index , s ) ;

	if( x < 0 )
	{
		cout << "Staff ID not exist\n" ;
	}
	else
	{
		while ( e>0 )
		{
			system ("cls") ;
			menuM() ;
			cout << "Choice:" ;
			cin >> c ;
			while ( cin.fail() || c<1 || c>5 )
			{
				cin.clear () ;
				cin.ignore(1000,'\n') ;
				system ("cls") ;
				menuM() ;
				cout << "Invalid Input!!\n" ;
				cout << "Choice:" ;
				cin >> c ;
			}
			switch (c)
			{
				case 1 :
					long long int sID ;
					system ("cls") ;
					intro () ;
					cout << "Enter Staff ID :" ;
					cin >> sID ;
					validSID0 ( obj , index , sID ) ;
					obj[x].setStaffFitness ( sID , obj[x].getName() , obj[x].getGender() , sID , obj[x].FitInfo.getWeight() , obj[x].FitInfo.getHeight() ) ;
					e = exitF () ;
					break ;

				case 2 :
					{
						string n ;
						system("cls") ;
						cout << "Enter name :" ;
						cin >> n ;
						validN( n ) ;
						obj[x].setStaffFitness ( obj[x].getsID() , n , obj[x].getGender() , obj[x].FitInfo.getSID() , obj[x].FitInfo.getWeight() , obj[x].FitInfo.getHeight() ) ;
						e = exitF () ;
						break ;
		 			}

				case 3 :
					{
						string g ;
						system("cls") ;
						cout << "Enter gender :" ;
						cin >> g ;
						validG( g ) ;
						obj[x].setStaffFitness ( obj[x].getsID() , obj[x].getName() , g , obj[x].FitInfo.getSID() , obj[x].FitInfo.getWeight() , obj[x].FitInfo.getHeight() ) ;
						e = exitF () ;
						break ;
					}

				case 4 :
					{
						int w ;
						system("cls") ;
						cout << "Enter weight :" ;
						cin >> w ;
						validW ( w ) ;
						obj[x].setStaffFitness ( obj[x].getsID() , obj[x].getName() , obj[x].getGender() , obj[x].FitInfo.getSID() , w , obj[x].FitInfo.getHeight() ) ;
						e = exitF () ;
						break ;
					}

				case 5 :
					{
						int h ;
						system("cls") ;
						cout << "Enter height :" ;
						cin >> h ;
						validH ( h ) ;
						obj[x].setStaffFitness ( obj[x].getsID() , obj[x].getName() , obj[x].getGender() , obj[x].FitInfo.getSID() , obj[x].FitInfo.getWeight() , h ) ;
						e = exitF () ;
						break ;
					}

				default :
					cout << "Wrong input\n" ;
					break ;

			}cout << "Modify success!!\n" ;
		}
	}
}

void dietPlan ( staffFitness obj[] , int index )
{
	long long int ID;
	int e = 1 ;
	int x , consume ;
	while ( e == 1)
	{
		system ("cls") ;
		intro () ;
		cout << "Please enter your staff ID:" ;
		cin >> ID ;
		validSID( ID ) ;
		x=search ( obj ,index , ID) ;
		if (x<0)
		{
			cout << "Staff ID do not exist .\n" ;
			e=exitF ();
		}
		else
		{
			cout << "Staff ID found !!\n" ;
			cout << "------------------------------------------------------------------------\n" ;
			obj[x].displayStaffFitness () ;
			if ( obj[x].wCategory == "Underweight" )
			{
				consume = dietPlan2 ( obj , x ) ;
				cout << "\n\nYour are underweight !! You need to gain more weight." ;
				cout << "\nPlease consume more than " << consume << "kj daily to gain weight. \n\n" ;
				e= exitF() ;
			}
			else if ( obj[x].wCategory == "Normal weight" )
			{
				consume = dietPlan2 ( obj , x ) ;
				cout << "\n\nCongratulations ! You have normal weight !" ;
				cout << "\nPlease consume around " << consume << "kj daily to maintain your weight. \n\n" ;
				e= exitF() ;
			}
			else if ( obj[x].wCategory == "Overweight" )
			{
				consume = dietPlan2 ( obj , x ) ;
				cout << "\n\nYou are overweight !! You need to lose weight.";
				cout << "\nPlease consume less than " << consume << "kj daily to lose weight. \n\n" ;
				e= exitF() ;
			}
			else if ( obj[x].wCategory=="Obese")
			{
				consume = dietPlan2 ( obj , x ) ;
				cout << "\n\nYou are obese !! You need to lose weight." ;
				cout << "\nPlease consume less than " << consume << "kj daily to lose weight. \n\n" ;
				e= exitF() ;
			}

		}
	}
}

int dietPlan2( staffFitness obj[] , int x )
{
	cout << "How often do you exerxise?\n\n" ;
	cout << "1.Sedentray\n2.Lightly active\n3.Moderately active\n4.Very active\n5.Extremely active\n\n" ;
	cout << "Enter your choice: " ;
	int c ;
	cin >> c ;
	while ( cin.fail() || c<1 || c>5 )
	{
		cin.clear () ;
		cin.ignore(1000,'\n') ;
		cout << "Invalid Input!!(Please choose from a number from 1 to 5)\n" ;
		cout << "Enter your choice:" ;
		cin >> c ;
	}
	switch (c)
	{
		case 1 :
			return obj[x].bmr * 1.2 ;
		case 2 :
			return obj[x].bmr * 1.375 ;
		case 3 :
			return obj[x].bmr * 1.55 ;
		case 4 :
			return obj[x].bmr * 1.725 ;
		case 5 :
			return obj[x].bmr * 1.9 ;
		default :
			cout << "wrong input" ;
			break ;
	}
}

void stats ( staffFitness obj[] , int index  )
{
	double NumUW , NumNW , NumOW , NumObese;        // number of person in all weight category
	double MNumUW , MNumNW , MNumOW , MNumObese;    // number of male in all weight category
	double FNumUW , FNumNW , FNumOW , FNumObese;    // number of female in all weight category
	double total , mtotal , ftotal;
	NumUW = NumNW = NumOW = NumObese = MNumUW = MNumNW = NumOW = MNumObese = FNumUW = FNumNW = FNumOW = FNumObese = total = mtotal = ftotal = 0;

	for ( int i = 0 ; i<index ; i++ )
	{
		if ( obj[i].wCategory == "Underweight")
			NumUW++ ;
		else if (obj[i].wCategory == "Normal weight")
			NumNW++ ;
		else if (obj[i].wCategory == "Overweight")
			NumOW++ ;
		else if (obj[i].wCategory == "Obese")
			NumObese++ ;
	}
	total = NumUW + NumNW + NumOW + NumObese ;
	for ( int i = 0 ; i<index ; i++ )
	{
		if ( obj[i].getGender() =="Male" && obj[i].wCategory == "Underweight")
			MNumUW++ ;
		else if (obj[i].getGender() =="Male" && obj[i].wCategory == "Normal weight")
			MNumNW++ ;
		else if (obj[i].getGender() =="Male" && obj[i].wCategory == "Overweight")
			MNumOW++ ;
		else if (obj[i].getGender() =="Male" && obj[i].wCategory == "Obese")
			MNumObese++ ;
		else if ( obj[i].getGender() =="Female" && obj[i].wCategory == "Underweight")
			FNumUW++ ;
		else if (obj[i].getGender() =="Female" && obj[i].wCategory == "Normal weight")
			FNumNW++ ;
		else if (obj[i].getGender() =="Female" && obj[i].wCategory == "Overweight")
			FNumOW++ ;
		else if (obj[i].getGender() =="Female" && obj[i].wCategory == "Obese")
			FNumObese++ ;
	}
	mtotal=MNumUW + MNumNW + MNumOW + MNumObese ;
	ftotal=FNumUW + FNumNW + FNumOW + FNumObese ;
	cout<<setprecision(1);
	//Display the number of employees for each weight category
	intro () ;
	cout<<"\t\t-----------------------------------------------------------------------------\n";
	cout<<"\t\t|         BMI           |    WEIGHT CATEGORY    |    NUMBER OF EMPLOYEES    |\n";
	cout<<"\t\t-----------------------------------------------------------------------------\n";
	cout<<"\t\t|         <20           |      Underweight      |             "<<NumUW<<"           |\n";
	cout<<"\t\t-----------------------------------------------------------------------------\n";
	cout<<"\t\t|      20<=BMI<25       |     Normal Weight     |             "<<NumNW<<"           |\n";
	cout<<"\t\t-----------------------------------------------------------------------------\n";
	cout<<"\t\t|      25<=BMI<30       |      Overweight       |             "<<NumOW<<"           |\n";
	cout<<"\t\t-----------------------------------------------------------------------------\n";
	cout<<"\t\t|         >=30          |         Obese         |             "<<NumObese<<"           |\n";
	cout<<"\t\t-----------------------------------------------------------------------------\n\n";

//	double percentage = NumUW / total * 100;
	cout<<fixed<<showpoint<<setprecision(2);
	double percentage = NumUW / total * 100;
	cout<<"\t\t"<<percentage<<"% of USM staff are underweight.\n" ;
	percentage = NumNW / total * 100;
	cout<<"\t\t"<<percentage<<"% of USM staff have normal weight.\n" ;
	percentage = NumOW / total * 100;
	cout<<"\t\t"<<percentage<<"% of USM staff are overweight.\n" ;
	percentage = NumObese / total * 100;
	cout<<"\t\t"<<percentage<<"% of USM staff are obese.\n\n\n" ;

	cout<<setprecision(1);
	cout<<"\t\tMALE:\n";
	cout<<"\t\t-----------------------------------------------------------------------------\n";
	cout<<"\t\t|         BMI           |    WEIGHT CATEGORY    |    NUMBER OF EMPLOYEES    |\n";
	cout<<"\t\t-----------------------------------------------------------------------------\n";
	cout<<"\t\t|         <20           |      Underweight      |             "<<MNumUW<<"           |\n";
	cout<<"\t\t-----------------------------------------------------------------------------\n";
	cout<<"\t\t|      20<=BMI<25       |     Normal Weight     |             "<<MNumNW<<"           |\n";
	cout<<"\t\t-----------------------------------------------------------------------------\n";
	cout<<"\t\t|      25<=BMI<30       |      Overweight       |             "<<MNumOW<<"           |\n";
	cout<<"\t\t-----------------------------------------------------------------------------\n";
	cout<<"\t\t|         >=30          |         Obese         |             "<<MNumObese<<"           |\n";
	cout<<"\t\t-----------------------------------------------------------------------------\n\n";

	cout <<"\t\tThere are " << mtotal << " male staff in USM.\n" ;
	cout<<fixed<<showpoint<<setprecision(2);

	percentage = MNumUW / mtotal *100;
	cout<<"\t\t"<<percentage<<"% of male USM staff are underweight.\n" ;
	percentage = MNumNW / mtotal * 100;
	cout<<"\t\t"<<percentage<<"% of male USM staff have normal weight.\n" ;
	percentage = MNumOW / mtotal * 100;
	cout<<"\t\t"<<percentage<<"% of male USM staff are overweight.\n" ;
	percentage = MNumObese / mtotal * 100;
	cout<<"\t\t"<<percentage<<"% of male USM staff are obese.\n\n\n" ;

	cout<<fixed<<setprecision(1);
	cout<<"\t\tFEMALE:\n";
	cout<<"\t\t-----------------------------------------------------------------------------\n";
	cout<<"\t\t|         BMI           |    WEIGHT CATEGORY    |    NUMBER OF EMPLOYEES    |\n";
	cout<<"\t\t-----------------------------------------------------------------------------\n";
	cout<<"\t\t|         <20           |      Underweight      |             "<<FNumUW<<"           |\n";
	cout<<"\t\t-----------------------------------------------------------------------------\n";
	cout<<"\t\t|      20<=BMI<25       |     Normal Weight     |             "<<FNumNW<<"           |\n";
	cout<<"\t\t-----------------------------------------------------------------------------\n";
	cout<<"\t\t|      25<=BMI<30       |      Overweight       |             "<<FNumOW<<"           |\n";
	cout<<"\t\t-----------------------------------------------------------------------------\n";
	cout<<"\t\t|         >=30          |         Obese         |             "<<FNumObese<<"           |\n";
	cout<<"\t\t-----------------------------------------------------------------------------\n\n";

	cout <<"\t\tThere are " << ftotal << " female staff in USM.\n" ;
	cout<<fixed<<showpoint<<setprecision(2);

	percentage = FNumUW / ftotal *100;
	cout<<"\t\t"<<percentage<<"% of female USM staff are underweight.\n" ;
	percentage = FNumNW / ftotal * 100;
	cout<<"\t\t"<<percentage<<"% of female USM staff have normal weight.\n" ;
	percentage = FNumOW / ftotal * 100;
	cout<<"\t\t"<<percentage<<"% of female USM staff are overweight.\n" ;
	percentage = FNumObese / ftotal * 100;
	cout<<"\t\t"<<percentage<<"% of female USM staff are obese.\n\n\n" ;
}

void deleteData ( staffFitness obj[] , int &index )
{
	int e = 1 ;
	long long int sID ;

	while (e>0)
	{
		system ("cls") ;
		intro () ;
		cout << "Enter the Staff ID of the staff that you want to delete his/her data \n" ;
		cout << "Stafff ID :" ;
		cin >> sID ;
		validSID ( sID ) ;
		int x ;
		x=search (obj , index , sID) ;
		if ( x < 0 )
		{
			cout << "Staff ID does not exist " ;
			e=exitF () ;
		}
		else if ( x>=0 )
		{
			cout << "\nStaff ID found !!\n " ;
			cout << "------------------------------------------------------------------------\n" ;
			obj[x].displayStaffFitness () ;
			string yon ;
			cout << "Are you sure you want to delete this staff data?\n" ;
			cout << "Please answer ('Yes' or 'No') \n" ;
			cout << "Choice :" ;
			cin >> yon ;
			validyon(yon) ;
			if (yon=="Yes" || yon=="yes")
			{
				for ( int i = x ; i < index ; i++ )
				{
					obj[i] = obj[i+1] ;
				}
				index -- ;
				cout << "\nStaff data was deleted.\n" ;
				e=exitF () ;
			}
			else if (yon=="No" || yon=="no")
			{
				e = -1 ;
			}
		}
	}
}

void menuCS ()
{
	cout << "\t\t\t _________________________________________________________ \n" << "\t\t\t|";
	cout.width(59) ;
	cout << "|\n"<<"\t\t\t|\tWhat data you would like to search with?" ;
	cout.width(12) ;
	cout << "|\n"<<"\t\t\t|\t\tPlease enter 2 choices." ;
	cout.width(21) ;
	cout << "|\n"<<"\t\t\t|" ;
	cout.width(59) ;
	cout << "|\n"<<"\t\t\t|1. Age" ;
	cout.width(53) ;
	cout << "|\n"<<"\t\t\t|2. Gender " ;
	cout.width(49) ;
	cout << "|\n"<<"\t\t\t|3. Weight " ;
	cout.width(49) ;
	cout << "|\n"<<"\t\t\t|4. Height " ;
	cout.width(49) ;
	cout << "|\n"<<"\t\t\t|5. BMI " ;
	cout.width(52) ;
	cout << "|\n"<<"\t\t\t|_________________________________________________________|\n\n" ;
}

void comSearch( staffFitness obj [] , int index  )
{
	int c1 , c2  ,n , j , k , x ;
	double minW , maxW , minH , maxH , minA , maxA ;
	c1=c2=j=k=n=x=0 ;
	maxA = maxW = maxH = 79 ;
	int e = 1 ;
	string  g ,bmi ;
	staffFitness objX [200] = {} ;
	staffFitness objY [200] = {} ;

//	cout << obj [2].FitInfo.getHeight() ;
//	system ("pause") ;

	while ( e>0 )
	{
		system ("cls") ;
		intro () ;
		menuCS() ;

		cout << "Choice 1 : " ;    //Input choice 1
		cin >> c1 ;
		while ( cin.fail() || c1<1 || c1>5 )
		{
			cout << "Input Invalid !! (Please choose from a number from 1-5 ) \n" ;
			cout << "Choice 1 : " ;
			cin >> c1 ;
		}

		cout << "\nChoice 2 : " ;   //Input choice 2
		cin >> c2 ;
		while ( cin.fail() || c2<1 || c2>5 || c2==c1 )
		{
			cout << "Input Invalid !! (Please choose from a number from 1-5 ) \n" ;
			cout << "Choice 2 cannot be same as Choice 1 \n" ;
			cout << "Choice 2 : " ;
			cin >> c2 ;
		}

		cout << "\n" ;

		switch (c1)
		{
			case 1 :
				cout << "Please enter a range of age. Minimum and maxinmum age can between 21-80 years old.\n" ;
				cout << "Min. age : " ;
				cin >> minA ;
				cout << "Max. age : " ;
				cin >> maxA ;
				validRange( 1 , minA , maxA ) ;

				for ( int i = 0 ; i<index ; i++ )
				{
					if ( obj[i].age >= minA && obj[i].age <=maxA )
					{
						objX[j].setStaffFitness( obj[i].getsID() , obj[i].getName() , obj[i].getGender() , obj[i].getsID() , obj[i].FitInfo.getWeight() , obj[i].FitInfo.getHeight() )  ;
						j++ ;
						cout << " j =" << j << endl ;
					}
				}

				break ;

			case 2 :
				cout << "\nGender : " ;
				cin >> g ;
				validG( g ) ;

				for ( int i = 0 ; i<index ; i++ )
				{
					if ( obj[i].getGender() == g  )
					{
						objX[j].setStaffFitness( obj[i].getsID() , obj[i].getName() , obj[i].getGender() , obj[i].getsID() , obj[i].FitInfo.getWeight() , obj[i].FitInfo.getHeight() )  ;
						j++ ;
					}
				}

				break ;

			case 3 :
				cout << "Please enter a range of weight. Minimum and maxinmum weight can between 1-595kg.\n" ;
				cout << "Min. weight : " ;
				cin >> minW ;
				cout << "Max. weight : " ;
				cin >> maxW ;
				validRange( 3 , minW , maxW ) ;

				for ( int i = 0 ; i<index ; i++ )
				{
					if ( obj[i].FitInfo.getWeight() >= minW && obj[i].FitInfo.getWeight() <=maxW )
					{
						objX[j].setStaffFitness( obj[i].getsID() , obj[i].getName() , obj[i].getGender() , obj[i].getsID() , obj[i].FitInfo.getWeight() , obj[i].FitInfo.getHeight() )  ;
						j++ ;
					}
				}

				break ;

			case 4 :
				cout << "Please enter a range of weight. Minimum and maxinmum height can between 1-272cm.\n" ;
				cout << "Min. height : " ;
				cin >> minH ;
				cout << "Max. height : " ;
				cin >> maxH ;
				validRange( 4 , minH , maxH ) ;

				for ( int i = 0 ; i<index ; i++ )
				{
					if ( obj[i].FitInfo.getHeight() >= minH && obj[i].FitInfo.getHeight() <=maxH )
					{
						objX[j].setStaffFitness( obj[i].getsID() , obj[i].getName() , obj[i].getGender() , obj[i].getsID() , obj[i].FitInfo.getWeight() , obj[i].FitInfo.getHeight() ) ;
						j++ ;
					}
				}

				break ;

			case 5 :
				cout << "Please choose a weight category \n\n" ;
				cout << "1. Underweight \n2. Normal weight \n3. Overweight \n4.Obese \n " ;
				cout << "Choice : " ;
				cin >> n ;
				while ( cin.fail() || n<1 || n>4 )
				{
					cin.clear() ;
					cin.ignore();
					cout << "Please choose from 1 to 4\n " ;
					cin >> n ;
				}
				if(n==1)
				{ bmi = "Underweight" ;	}
				else if (n==2)
				{ bmi = "Normal weight" ; }
				else if (n==2)
				{ bmi = "Overweight" ; }
				else if (n==4)
				{ bmi = "Obese" ; }

				for ( int i = 0 ; i<index ; i++ )
				{
					if ( obj[i].wCategory == bmi  )
					{
						objX[j].setStaffFitness( obj[i].getsID() , obj[i].getName() , obj[i].getGender() , obj[i].getsID() , obj[i].FitInfo.getWeight() , obj[i].FitInfo.getHeight() )  ;
						j++ ;
					}
				}

				break ;

			default :
				break ;
		}

		switch (c2)
		{
			case 1 :
				cout << "Please enter a range of age. Minimum and maxinmum age can between 21-80 years old.\n" ;
				cout << "Min. age : " ;
				cin >> minA ;
				cout << "Max. age : " ;
				cin >> maxA ;
				validRange( 1 , minA , maxA ) ;

				for ( int i = 0 ; i<j ; i++ )
				{
					if ( objX[i].age >= minA && objX[i].age <=maxA )
					{
						objY[k].setStaffFitness( objX[i].getsID() , objX[i].getName() , objX[i].getGender() , objX[i].getsID() , objX[i].FitInfo.getWeight() , objX[i].FitInfo.getHeight() )  ;
						k++ ;
					}
				}

				break ;

			case 2 :
				cout << "\nGender : " ;
				cin >> g ;
				validG( g ) ;

				for ( int i = 0 ; i<j ; i++ )
				{
					if ( objX[i].getGender() == g  )
					{
						objY[k].setStaffFitness( objX[i].getsID() , objX[i].getName() , objX[i].getGender() , objX[i].getsID() , objX[i].FitInfo.getWeight() , objX[i].FitInfo.getHeight() )  ;
						k++ ;
					}
				}

				break ;

			case 3 :
		{
				cout << "Please enter a range of weight. Minimum and maxinmum weight can between 1-595kg.\n" ;
				cout << "Min. weight : " ;
				cin >> minW ;
				cout << "Max. weight : " ;
				cin >> maxW ;
				validRange( 3 , minW , maxW ) ;
				cout <<minW << maxW << endl;
				for ( int i = 0 ; i<index ; i++ )
				{
					if ( objX[i].FitInfo.getWeight() >= minW && objX[i].FitInfo.getWeight() <=maxW )
					{
						objY[k].setStaffFitness( objX[i].getsID() , objX[i].getName() , objX[i].getGender() , objX[i].getsID() , objX[i].FitInfo.getWeight() , objX[i].FitInfo.getHeight() )  ;
						k++ ;
					}
				}
				break ; 				}

			case 4 :
				cout << "Please enter a range of weight. Minimum and maxinmum height can between 1-272cm.\n" ;
				cout << "Min. height : " ;
				cin >> minH ;
				cout << "Max. height : " ;
				cin >> maxH ;
				validRange( 4 , minH , maxH ) ;

				for ( int i = 0 ; i<j ; i++ )
				{
					if ( objX[i].FitInfo.getHeight() >= minH && objX[i].FitInfo.getHeight() <=maxH )
					{
						objY[k].setStaffFitness( objX[i].getsID() , objX[i].getName() , objX[i].getGender() , objX[i].getsID() , objX[i].FitInfo.getWeight() , objX[i].FitInfo.getHeight() )  ;
						k++ ;
					}
				}

				break ;

			case 5 :
				cout << "Please choose a weight category \n\n" ;
				cout << "1. Underweight \n2. Normal weight \n3. Overweight \n4. Obese \n" ;
				cout << "Choice : " ;
				cin >> n ;
				while ( cin.fail() || n<1 || n>4 )
				{
					cin.clear() ;
					cin.ignore();
					cout << "Please choose from 1 to 4\n" ;
					cin >> n ;
				}
				if(n==1)
				{ bmi = "Underweight" ;	}
				else if (n==2)
				{ bmi = "Normal weight" ; }
				else if (n==2)
				{ bmi = "Overweight" ; }
				else if (n==4)
				{ bmi = "Obese" ; }

				for ( int i = 0 ; i<j ; i++ )
				{
					if ( objX[i].wCategory == bmi  )
					{
						objY[k].setStaffFitness( objX[i].getsID() , objX[i].getName() , objX[i].getGender() , objX[i].getsID() , objX[i].FitInfo.getWeight() , objX[i].FitInfo.getHeight() )  ;
						k++ ;
					}
				}

				break ;

			default :
				break ;
		}
		cout << " k =" << k << endl ;
		cout << "\n\nThis is the staff that fulfill the condition : \n" ;

		for ( int i = 0 ; i < k ; i++)
		{
			cout << "------------------------------------------------------------------------\n" ;
			objY[i].displayStaffFitness() ;
		}

	e = -1 ;  //exit function
	}

}

void validRange ( int c , double &min ,double &max )
{
	switch ( c )
	{
		case 1 :
			while( cin.fail() || min > max || min<21 || min>80 || max<21 || max>80 )
			{
				cin.clear() ;
				cin.ignore(1000,'\n') ;
				cout << "Invalid input !! \n" ;
				cout << "Reminder (Valid age range is between 21-80 , min. age cannot bigger than max. age) \n" ;
				cout << "Min. age : " ;
				cin >> min ;
				cout << "Max. age : " ;
				cin >> max ;
			}
			break ;

		case 2 :
			break ;
		case 3 :
			while( cin.fail() || (min>max) || (min<1) || (min>595) || (max<1) || (max>595) )
			{
				cin.clear() ;
				cin.ignore(1000,'\n') ;
				cout << "Invalid input !! \n" ;
				cout << "Reminder (Valid weight range is between 1-595 kg, min. weight cannot be heavier than max. weight) \n\n" ;
				cout << "Min. weight(kg) : " ;
				cin >> min ;
				cout << "Max. weight(kg) : " ;
				cin >> max ;
			}
			break ;

		case 4 :
			while( cin.fail() || (min>max) || (min<1) || (min>595) || (max<1) || (max>595) )
			{
				cin.clear() ;
				cin.ignore(1000,'\n') ;
				cout << "Invalid input !! \n" ;
				cout << "Reminder (Valid height range is between 1-272cm, min. height cannot be taller than max. height) \n" ;
				cout << "Min. height(kg) : " ;
				cin >> min ;
				cout << "Max. height(kg) : " ;
				cin >> max ;
			}
			break ;

		default :
			break ;
	}

}




