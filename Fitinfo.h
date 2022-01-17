#include <iostream>
#include <string>
#ifndef FITINFO_H
#define FITINFO_H

using namespace std ;

class fitInfo // Class to store fitness info
{
	private :
		long long int staffID ;
		double weight ;
		double height ;

	public :
		fitInfo() ;
		~fitInfo() ;
		void setFit(long long int , int , int) ;
		void setSID (long long int SID){ staffID = SID;}
		void setWeight (int w){ weight = w ; }
		void setHeight (int h){ height = h ; }
		long long int getSID () {return staffID ; }
		double getWeight (){return weight ; }
		double getHeight (){return height ; }



};

fitInfo :: fitInfo()
{
	staffID = 0 ;
	weight = 0 ;
	height = 0 ;
}


fitInfo :: ~fitInfo()
{
	staffID = 0 ;
	weight = 0 ;
	height = 0 ;
}

void fitInfo :: setFit(long long int SID, int w, int h)
{
	staffID = SID ;
	weight = w ;
	height = h ;
}

#endif
