// --------------------------------
// projects/c++/deque/TestDeque.c++
// Copyright (C) 2015
// Glenn P. Downing
// --------------------------------

// http://www.cplusplus.com/reference/deque/deque/

// --------
// includes
// --------

#include <deque>     // deque
#include <stdexcept> // invalid_argument, out_of_range
#include <iostream>

#include "gtest/gtest.h"

#include "Deque.h"

// -----
// Using
// -----

using namespace std;

using testing::Test;
using testing::Types;

// -----
// Types
// -----

template <typename T>
struct Deque_Fixture : Test {
    typedef T                               deque_type;
    typedef typename deque_type::value_type value_type;};

typedef Types<
               deque<int>,
            my_deque<int>>
        deque_types;

TYPED_TEST_CASE(Deque_Fixture, deque_types);

// -----
// Tests
// -----


/******************************/
/**** DEQUE FUNCTIONS TESTS ***/
/******************************/

TYPED_TEST(Deque_Fixture, test_1) {
    typedef typename TestFixture::deque_type deque_type;

    const deque_type x;
    ASSERT_TRUE(x.empty());
    ASSERT_EQ(x.size(),0);}
    

//CONSTRUCTOR

TYPED_TEST(Deque_Fixture, constructor1) {
	typedef typename TestFixture::deque_type deque_type;

	const deque_type x(2,2);
    

    ASSERT_TRUE(!x.empty());
    ASSERT_EQ(x.size(),2);
    }

 TYPED_TEST(Deque_Fixture, constructor2) {
	typedef typename TestFixture::deque_type deque_type;

	const deque_type x;
    

    ASSERT_TRUE(x.empty());
    ASSERT_EQ(x.size(),0);
    }

TYPED_TEST(Deque_Fixture, constructor3) {
	typedef typename TestFixture::deque_type deque_type;

	const deque_type x(19,1);
    

    ASSERT_TRUE(!x.empty());
    ASSERT_EQ(x.size(),19);
    }

 TYPED_TEST(Deque_Fixture, constructor4) {
	typedef typename TestFixture::deque_type deque_type;

	const deque_type x(25,1);
    
  	ASSERT_EQ(x.size(), 25);
  }


TYPED_TEST(Deque_Fixture, copyconstr1){
	typedef typename TestFixture::deque_type deque_type;

	const deque_type x(25, 1);
	//const deque_type y(25, 0);

	const deque_type y(x);

	ASSERT_EQ(y.back(), 1);
	ASSERT_EQ(y.front(), 1);
	ASSERT_EQ(y.size(), 25);
}

TYPED_TEST(Deque_Fixture, copyconstr2){
	typedef typename TestFixture::deque_type deque_type;

	const deque_type x(50, 16);
	//const deque_type y(25, 0);

	const deque_type y(x);

	ASSERT_EQ(y.back(), 16);
	ASSERT_EQ(y.front(), 16);
	ASSERT_EQ(y.size(), 50);
}

TYPED_TEST(Deque_Fixture, copyconstr3){
	typedef typename TestFixture::deque_type deque_type;

	const deque_type x(5, 2);
	//const deque_type y(25, 0);

	const deque_type y(x);

	ASSERT_EQ(y.back(), 2);
	ASSERT_EQ(y.front(), 2);
	ASSERT_EQ(y.size(), 5);
}

TYPED_TEST(Deque_Fixture, subscript1){
	typedef typename TestFixture::deque_type deque_type;

	const deque_type x(10, 2);
	//const deque_type y(25, 0);

	ASSERT_EQ(x.back(), 2);
	ASSERT_EQ(x.front(), 2);
	ASSERT_EQ(x.size(), 10);
	ASSERT_EQ(x[5], 2);
}

TYPED_TEST(Deque_Fixture, subscript2){
	typedef typename TestFixture::deque_type deque_type;

	const deque_type x(10, 2);

	const deque_type y(x);

	ASSERT_EQ(y.back(), 2);
	ASSERT_EQ(y.front(), 2);
	ASSERT_EQ(y.size(), 10);
	ASSERT_EQ(y[5], 2);
	ASSERT_EQ(y[3], 2);
	ASSERT_EQ(y[8], 2);
}

TYPED_TEST(Deque_Fixture, subscript3){
	typedef typename TestFixture::deque_type deque_type;

	const deque_type x(2, 2);

	//const deque_type y(x);

	ASSERT_EQ(x.front(), x.back());
	ASSERT_EQ(x[0], 2);
	ASSERT_EQ(x[1], 2);
	ASSERT_EQ(x.size(), 2);

}


/*
TYPED_TEST(Deque_Fixture, copyconstr2){
	typedef typename TestFixture::deque_type deque_type;

	const deque_type x(25, 1);
	const deque_type y(25, 0);

	ASSERT_EQ(y.back(), 0);
	ASSERT_EQ(y.front(), 0);

	y = x;

	ASSERT_EQ(y.back(), 1);
	ASSERT_EQ(y.front(), 1);
}

TYPED_TEST(Deque_Fixture, copyconstr3){
	typedef typename TestFixture::deque_type deque_type;

	const deque_type x(45, 5);
	const deque_type y;

	ASSERT_EQ(y.back(), 0);
	ASSERT_EQ(y.front(), 0);

	y = x;

	ASSERT_EQ(y.back(), 5);
	ASSERT_EQ(y.front(), 5);
	ASSERT_EQ(y.size(), 45)
}
*/


//BACK

TYPED_TEST(Deque_Fixture, back1) {
	typedef typename TestFixture::deque_type deque_type;

	const deque_type x(3,1);

	//cout << "The last value is: " << x.back() << endl;
    
  	ASSERT_EQ(x.back(), 1);
  }


TYPED_TEST(Deque_Fixture, back2) {
	typedef typename TestFixture::deque_type deque_type;

	const deque_type x(1,9);

	//cout << "The last value is: " << x.back() << endl;
    
  	ASSERT_EQ(x.back(), 9);
  }

TYPED_TEST(Deque_Fixture, back3) {
	typedef typename TestFixture::deque_type deque_type;

	const deque_type x(3,5);

	//cout << "The  value is: " << x.back() << endl;
    
  	ASSERT_EQ(x.back(), 5);
  }

TYPED_TEST(Deque_Fixture, back4) {
	typedef typename TestFixture::deque_type deque_type;

	const deque_type x(7,16);

	//cout << "The  value is: " << x.back() << endl;
    
  	ASSERT_EQ(x.back(), 16);
  }

//FRONT

TYPED_TEST(Deque_Fixture, front1) {
	typedef typename TestFixture::deque_type deque_type;

	const deque_type x(1,1);

	//cout << "The front value is: " << x.front() << endl;
    
  	ASSERT_EQ(x.front(), 1);
  }

TYPED_TEST(Deque_Fixture, front2) {
	typedef typename TestFixture::deque_type deque_type;

	const deque_type x(3,11);

	//cout << "The front value is: " << x.front() << endl;
    
  	ASSERT_EQ(x.front(), 11);
  }

TYPED_TEST(Deque_Fixture, front3) {
	typedef typename TestFixture::deque_type deque_type;

	const deque_type x(25,11);

	//cout << "The front value is: " << x.front() << endl;
    
  	ASSERT_EQ(x.front(), 11);
  }

TYPED_TEST(Deque_Fixture, front4) {
	typedef typename TestFixture::deque_type deque_type;

	const deque_type x(67,1);

	//cout << "The front value is: " << x.front() << endl;
    
  	ASSERT_EQ(x.front(), 1);
  }



// ---------
// push back
// ---------
/*
TYPED_TEST(Deque_Fixture, push_back1) {
	deque_type<int> dq(3, 1);
	ASSERT_TRUE(dq.back() == 1);
	ASSERT_TRUE(dq.size() == 3);
	dq.push_back(2);
	ASSERT_TRUE(dq.back() == 2);
	ASSERT_TRUE(dq.size() == 4);
}
TYPED_TEST(Deque_Fixture, push_back2) {
	deque_type<int> dq(1, 1);
	ASSERT_TRUE(dq.back() == 1);
	ASSERT_TRUE(dq.size() == 1);
	dq.push_back(2);
	dq.push_back(3);
	dq.push_back(4);
	ASSERT_TRUE(dq.back() == 4);
	ASSERT_TRUE(dq.size() == 4);
}
TYPED_TEST(Deque_Fixture, push_back3) {
	deque_type<int> dq(50, 5);
	ASSERT_TRUE(dq.back() == 5);
	ASSERT_TRUE(dq.size() == 50);
	for(int i =  0; i < 15; ++i){
		int temp = i;
		dq.push_back(temp);
	}
	ASSERT_TRUE(dq.back() == 14);
	ASSERT_TRUE(dq.size() == 65);
}
// --------
// pop back
// --------
TYPED_TEST(Deque_Fixture, pop_back1) {
	deque_type<int> dq(1, 1);
	dq.push_back(2);
	dq.push_back(3);
	ASSERT_TRUE(dq.size() == 3);
	ASSERT_TRUE(dq.back() == 3);
	dq.pop_back();
	ASSERT_TRUE(dq.size() == 2);
	ASSERT_TRUE(dq.back() == 2);
}
TYPED_TEST(Deque_Fixture, pop_back2) {
	deque_type<int> dq(10, 7);
	dq.push_back(1);
	dq.push_back(14);
	dq.push_back(11);
	ASSERT_TRUE(dq.size() == 13);
	ASSERT_TRUE(dq.back() == 11);
	dq.pop_back();
	dq.pop_back();
	ASSERT_TRUE(dq.size() == 11);
	ASSERT_TRUE(dq.back() == 1);
}
TYPED_TEST(Deque_Fixture, pop_back3) {
	deque_type<int> dq(5, 2);
	ASSERT_TRUE(dq.size() == 5);
	ASSERT_TRUE(dq.back() == 2);
	dq.push_back(3);
	dq.push_back(9);
	dq.pop_back();
	ASSERT_TRUE(dq.size() == 6);
	ASSERT_TRUE(dq.back() == 3);
}
// ----------
// push front
// ----------
TYPED_TEST(Deque_Fixture, push_front1) {
	deque_type<int> dq(50, 5);
	ASSERT_TRUE(dq.front() == 5);
	ASSERT_TRUE(dq.size() == 50);
	dq.push_front(1);
	ASSERT_TRUE(dq.back() == 5);
	ASSERT_TRUE(dq.front() == 1);
	ASSERT_TRUE(dq.size() == 51);
}
TYPED_TEST(Deque_Fixture, push_front2) {
	deque_type<int> dq(4, 1);
	ASSERT_TRUE(dq.front() == 1);
	ASSERT_TRUE(dq.size() == 4);
	dq.push_front(2);
	ASSERT_TRUE(dq.back() == 1);
	ASSERT_TRUE(dq.front() == 2);
	ASSERT_TRUE(dq.size() == 5);
}
TYPED_TEST(Deque_Fixture, push_front3) {
	deque_type<int> dq(1, 1);
	ASSERT_TRUE(dq.front() == 1);
	ASSERT_TRUE(dq.size() == 1);
	for(int i = 0; i < 15; ++i){
		int temp = i;
		dq.push_front(temp);
	}
	ASSERT_TRUE(dq.size() == 16);
	ASSERT_TRUE(dq.front() == 14);
}
// ----------
// pop front
// ----------
TYPED_TEST(Deque_Fixture, pop_front1) {
	deque_type<int> dq(5, 3);
	ASSERT_TRUE(dq.size() == 5);
	ASSERT_TRUE(dq.front() == 3);
	dq.pop_front();
	ASSERT_TRUE(dq.size() == 4);
	ASSERT_TRUE(dq.front() == 3);
}
TYPED_TEST(Deque_Fixture, pop_front2) {
	deque_type<int> dq(1, 1);
	ASSERT_TRUE(dq.size() == 1);
	ASSERT_TRUE(dq.front() == 1);
	dq.push_front(3);
	dq.push_front(4);
	dq.push_front(19);
	ASSERT_TRUE(dq.size() == 4);
	ASSERT_TRUE(dq.front() == 19);
	dq.pop_front();
	ASSERT_TRUE(dq.size() == 3);
	ASSERT_TRUE(dq.front() == 4);	
}
TYPED_TEST(Deque_Fixture, pop_front3) {
	deque_type<int> dq(7, 8);
	ASSERT_TRUE(dq.size() == 7);
	ASSERT_TRUE(dq.front() == 8);
	for(int i = 0; i < 4; ++i){
		dq.pop_front();
	}
	ASSERT_TRUE(dq.size() == 3);
	ASSERT_TRUE(dq.front() == 8);
}
// -----
// empty
// -----
TYPED_TEST(Deque_Fixture, empty1) {
	deque_type<int> dq(1, 1);
	ASSERT_FALSE(dq.empty());
}
TYPED_TEST(Deque_Fixture, empty2) {
	deque_type<int> dq(1, 1);
	dq.pop_front();
	ASSERT_TRUE(dq.empty());
}
TYPED_TEST(Deque_Fixture, empty3) {
	deque_type<int> dq(5, 5);
	dq.pop_back();
	dq.pop_front();
	ASSERT_FALSE(dq.empty());
}
// -----
// clear
// -----
TYPED_TEST(Deque_Fixture, clear1) {
	deque_type<int> dq(5, 5);
	ASSERT_TRUE(dq.size() == 5);
	dq.clear();
	ASSERT_TRUE(dq.empty());
}
TYPED_TEST(Deque_Fixture, clear2) {
	deque_type<int> dq(3, 3);
	ASSERT_TRUE(dq.size() == 3);
	dq.clear();
	ASSERT_TRUE(dq.empty());
}
TYPED_TEST(Deque_Fixture, clear3) {
	deque_type<int> dq(1, 5);
	ASSERT_TRUE(dq.size() == 1);
	dq.push_front(5);
	dq.push_back(10);
	dq.clear();
	ASSERT_TRUE(dq.empty());
}
// --
// ==
// --
TYPED_TEST(Deque_Fixture, equals1) {
}
TYPED_TEST(Deque_Fixture, equals2) {
}
TYPED_TEST(Deque_Fixture, equals3) {
}
// -------------------------
// < - lexigraphical compare
// -------------------------
TYPED_TEST(Deque_Fixture, lexicmp1) {
}
TYPED_TEST(Deque_Fixture, lexicmp2) {
}
TYPED_TEST(Deque_Fixture, lexicmp3) {
}
*/

/***************/
/***ITERATORS***/
/***************/

// -----------
// == iterator
// -----------


/*
TYPED_TEST(Deque_Fixture, itequal1) {
}
TYPED_TEST(Deque_Fixture, itequal2) {
}
TYPED_TEST(Deque_Fixture, itequal3) {
}
// -----------
// != iterator
// -----------
TYPED_TEST(Deque_Fixture, noteq1) {
}
TYPED_TEST(Deque_Fixture, noteq2) {
}
TYPED_TEST(Deque_Fixture, noteq3) {
}
*/