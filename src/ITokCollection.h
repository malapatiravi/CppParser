/*
 * ITokCollection.h
 *
 *  Created on: Feb 8, 2016
 *      Author: malz
 */

#ifndef SRC_ITOKCOLLECTION_H_
#define SRC_ITOKCOLLECTION_H_
/////////////////////////////////////////////////////////////////////
//  ITokCollection.h - package for the ITokCollection interface    //
//  ver 1.2                                                        //
//  Language:      Visual C++ 2008, SP1                            //
//  Platform:      Dell Precision T7400, Vista Ultimate SP1        //
//  Application:   Prototype for CSE687 Pr1, Sp09                  //
//  Author:        Ravichandra Malapati, , Syracuse University     //
//                 (315) 706 3437, rmalapat@twcny.rr.com           //
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
//  ITokCollection.h - package for the ITokCollection interface    //
//  ver 1.1                                                        //
//  Language:      Visual C++ 2008, SP1                            //
//  Platform:      Dell Precision T7400, Vista Ultimate SP1        //
//  Application:   Prototype for CSE687 Pr1, Sp09                  //
//  Author:        Jim Fawcett, CST 4-187, Syracuse University     //
//                 (315) 443-3948, jfawcett@twcny.rr.com           //
/////////////////////////////////////////////////////////////////////
/*
 Module Purpose:
 ===============
 ITokCollection is an interface that supports substitution of different
 types of scanners for parsing.  In this solution, we illustrate that
 by binding two different types of collections, SemiExp and XmlParts,
 to this interface.  This is illustrated in the test stubs for the
 SemiExpression and XmlElementParts modules.

 Maintenance History:
 ====================
 ver 1.2 :Feb 10 2016
 modified few functions as they are already implemented in SemiExp
 ver 1.1 : 02 Jun 11
 - added merge, remove overload, and default param in get
 ver 1.0 : 17 Jan 09
 - first release
 */

struct ITokCollection
{
	virtual bool get1(bool clear = true)=0;
	//virtual size_t length()=0;
	virtual std::string& operator[](int n)=0;
	virtual size_t find(const std::string& tok)=0;
	virtual void push_back(const std::string& tok)=0;
	virtual bool merge(const std::string& firstTok,
			const std::string& secondTok)=0;
	virtual bool remove(const std::string& tok)=0;
	virtual bool remove(size_t i)=0;
	virtual void toLower()=0;
	virtual void trimFront()=0;
	virtual void clear()=0;
	virtual std::string show1(bool showNewLines = false)=0;
	virtual ~ITokCollection()
	{
	}
	;
};

#endif /* SRC_ITOKCOLLECTION_H_ */
