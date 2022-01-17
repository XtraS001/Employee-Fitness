#include <iostream>
#include <string>
#ifndef PERSONINFO_H
#define PERSONINFO_H

using namespace std ;

class personInfo // Class to store staff personal info
{
	private :
		long long int stafID ;
		string name ;
		string gender ;

	public :
		personInfo () ;                                   // Default Constructor
		~personInfo () ;                                  // Default Destructor
		void setPerson ( long long int , string , string ) ; // all function with 'set' are use to set a value
		void setsID( long long int sID) { stafID = sID ;}
		void setname( string n) { name = n ;}
		void setgender (string g ) { gender = g ; }
		long long int getsID() { return stafID ;}
		string getName() { return name ;}
		string getGender () { return gender ; }

};

personInfo :: personInfo ()  //Default Constructor
{
	stafID = 0 ;
	name = " " ;
	gender = " " ;
}

personInfo :: ~personInfo ()  //Default Destructor
{
	stafID = 0 ;
	name = " " ;
	gender = " " ;
}

void personInfo :: setPerson ( long long int sID, string n, string g)
{
	stafID = sID ;
	name = n ;
	gender = g ;
}

#endif


































