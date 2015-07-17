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


//COPY CONSTRUC

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

//SUBSCRIPT

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


//POP BACK

TYPED_TEST(Deque_Fixture, pop_back1){
	typedef typename TestFixture::deque_type deque_type;

	deque_type x(5, 0);


	x.pop_back();

	ASSERT_EQ(x.size(), 4);

	x[3] = 1;

	ASSERT_EQ(x.back(), 1);
}

TYPED_TEST(Deque_Fixture, pop_back2){
	typedef typename TestFixture::deque_type deque_type;

	deque_type x(27, 0);

	x[26] = 10;
	x[25] = 9;
	x[24] = 8;
	x[23] = 7;

	x.pop_back();
	x.pop_back();

	ASSERT_EQ(x.size(), 25);
	ASSERT_EQ(x.back(), 8);
}


TYPED_TEST(Deque_Fixture, pop_back3){
	typedef typename TestFixture::deque_type deque_type;

	deque_type x(3, 2);

	x[2] = 5;
	x[1] = 4;

	//cout<< "The value at x = 2: " << x[2] << endl;

	x.pop_back();

	ASSERT_EQ(x.size(), 2);

}

TYPED_TEST(Deque_Fixture, pop_back4){
	typedef typename TestFixture::deque_type deque_type;
	/*
	deque_type x(22, 0);

	x[21] = 10;
	x[20] = 9;
	x[19] = 8;
	x[18] = 7;
	x[17] = 6;
	x[16] = 5;
	x[15] = 4;

	x.pop_back();
	x.pop_back();
	x.pop_back();

	ASSERT_EQ(x.size(), 19);
	ASSERT_EQ(x.back(), 7);
	*/

	deque_type x(19, 1);

	x[18] = 6;
	x[17] = 5;

	ASSERT_EQ(x.back(), 6);
	ASSERT_EQ(x.size(), 19);

	x.pop_back();
	//x.pop_back();
	//x.pop_back();
	//x.pop_back();

	ASSERT_EQ(x.back(), 5);
	ASSERT_EQ(x.size(), 18);
}

TYPED_TEST(Deque_Fixture, pop_back5){
	typedef typename TestFixture::deque_type deque_type;
	
	deque_type x(22, 0);

	x[21] = 10;
	x[20] = 9;
	x[19] = 8;
	x[18] = 7;
	x[17] = 6;
	x[16] = 5;
	x[15] = 4;

	x.pop_back();
	x.pop_back();

	ASSERT_EQ(x.size(), 20);
	ASSERT_EQ(x.back(), 8);
	
}

//POP FRONT

TYPED_TEST(Deque_Fixture, pop_front1){
	typedef typename TestFixture::deque_type deque_type;

	deque_type x(3, 0);

	x[0] = 1;
	x[1] = 2;
	x[2] = 3;

	ASSERT_EQ(x.size(), 3);
	ASSERT_EQ(x.front(), 1);

	x.pop_front();

	ASSERT_EQ(x.size(), 2);
	ASSERT_EQ(x.front(), 2);

}

TYPED_TEST(Deque_Fixture, pop_front2){
	typedef typename TestFixture::deque_type deque_type;

	deque_type x(25, 0);


	x[19] = 1;
	x[20] = 2;
	x[21] = 3;
	x[22] = 4;
	x[23] = 5;
	x[24] = 6;

	//std::cout<<"x[0] "<< x[0]<<std::endl;

	x.pop_front();
	x.pop_front();
	x.pop_front();
	x.pop_front();
	x.pop_front();
	x.pop_front();
	x.pop_front();
	x.pop_front();
	x.pop_front();
	x.pop_front();
	x.pop_front();
	x.pop_front();
	x.pop_front();
	x.pop_front();
	x.pop_front();
	x.pop_front();
	x.pop_front();
	x.pop_front();
	x.pop_front();
	x.pop_front();

	//std::cout<< "the value at x[0] is now: " << x[0] << std::endl;

	ASSERT_EQ(x.front(), 2);

}

TYPED_TEST(Deque_Fixture, pop_front3){
	typedef typename TestFixture::deque_type deque_type;

	deque_type x(10, 0);

	for(int i = 0 ; i < 10; ++i){
		x[i] = i;
	}


	x.pop_front();
	x.pop_front();
	x.pop_back();

	ASSERT_EQ(x.size(), 7);
	ASSERT_EQ(x.back(), 8);
	ASSERT_EQ(x.front(), 2);

}


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


//PUSH BACK


TYPED_TEST(Deque_Fixture, push_back1) {
	typedef typename TestFixture::deque_type deque_type;

	deque_type x(5,0);

	for(int i = 0; i < 5; ++i){
		x[i] = i;
	}

	x.push_back(5);

	//cout << "The front value is: " << x.front() << endl;
    
 	ASSERT_EQ(x.size(), 6);
 	ASSERT_EQ(x.back(), 5);
 	ASSERT_EQ(x[4], 4);
 	ASSERT_EQ(x[5], 5);
  }


//PUSH FRONT

TYPED_TEST(Deque_Fixture, push_front1) {
	typedef typename TestFixture::deque_type deque_type;

	deque_type x(5, 0);

	x.pop_front();

	ASSERT_EQ(x.size(), 4);
	ASSERT_EQ(x.front(), 0);

	x.push_front(3);

	ASSERT_EQ(x.size(), 5);
	ASSERT_EQ(x.front(), 3);
  }


//TEST ITERATOR

TYPED_TEST(Deque_Fixture, inc_test_iterator_1) {
	typedef typename TestFixture::deque_type deque_type;
	
	deque_type x(10, 0);
	
	int count = 0;

	for(int i = 0; i < 10; ++i){
		x[i] = i;
		//cout << "i: " << i << endl;
	}
	
	for (typename deque_type::iterator i = x.begin(); i != x.end(); ++i) {
		//cout<< "x[i]: " << *i <<endl;
		++count;
	}

	ASSERT_EQ(count, 10);
}

TYPED_TEST(Deque_Fixture, inc_test_iterator_2) {
	typedef typename TestFixture::deque_type deque_type;
	
	deque_type x(25, 1);
	
	int count = 0;

	for(int i = 0; i < 25; ++i){
		x[i] = i;
		//cout << "i: " << i << endl;
	}
	
	for (typename deque_type::iterator i = x.begin(); i != x.end(); ++i) {
		//cout<< "x[i]: " << *i <<endl;
		++count;
	}

	ASSERT_EQ(count, 25);
}

TYPED_TEST(Deque_Fixture, inc_test_iterator_3) {
	typedef typename TestFixture::deque_type deque_type;
	
	deque_type x(47, 0);
	
	int count = 0;

	for(int i = 0; i < 47; ++i){
		x[i] = i;
		//cout << "i: " << i << endl;
	}
	
	for (typename deque_type::iterator i = x.begin(); i != x.end(); ++i) {
		//cout<< "x[i]: " << *i <<endl;
		++count;
	}

	ASSERT_EQ(count, 47);
}

//DEC ITER

TYPED_TEST(Deque_Fixture, dec_test_iterator_1) {
	typedef typename TestFixture::deque_type deque_type;
	
	deque_type x(10, 0);
	
	int count = 0;

	for(int i = 0; i < 10; ++i){
		x[i] = i;
		//cout << "i: " << i << endl;
	}
	
	for (typename deque_type::iterator i = x.end()-1; i != x.begin(); --i) {
		++count;
	}

	ASSERT_EQ(count, 9);
}
TYPED_TEST(Deque_Fixture, dec_test_iterator_2) {
	typedef typename TestFixture::deque_type deque_type;
	
	deque_type x(10, 0);
	
	int count = 0;

	for(int i = 0; i < 10; ++i){
		x[i] = i;
		//cout << "i: " << i << endl;
	}
	
	for (typename deque_type::iterator i = x.end()-1; i != x.begin(); --i) {
		++count;
	}

	ASSERT_EQ(count, 9);
}

TYPED_TEST(Deque_Fixture, dec_test_iterator_3) {
	typedef typename TestFixture::deque_type deque_type;
	
	deque_type x(25, 0);
	
	int count = 0;

	for(int i = 0; i < 25; ++i){
		x[i] = i;
		//cout << "i: " << i << endl;
	}
	
	for (typename deque_type::iterator i = x.end()-1; i != x.begin(); --i) {
		++count;
	}

	ASSERT_EQ(count, 24);
}


// +=

TYPED_TEST(Deque_Fixture, plus_equal_1) {
	typedef typename TestFixture::deque_type deque_type;
	
	deque_type x(10, 0);
	typename deque_type::iterator i=x.begin();
	i+=5;
	

	ASSERT_EQ(*i, 0);
}

TYPED_TEST(Deque_Fixture, plus_equal_2) {
	typedef typename TestFixture::deque_type deque_type;
	
	deque_type x(10, 0);
	typename deque_type::iterator i=x.begin();

	for(int i = 0; i < 10; ++i){
		x[i] = i;
	}

	i+=5;

	ASSERT_EQ(*i, 5);
}

TYPED_TEST(Deque_Fixture, plus_equal_3) {
	typedef typename TestFixture::deque_type deque_type;
	
	deque_type x(45, 0);
	typename deque_type::iterator i=x.begin();

	for(int i = 0; i < 45; ++i){
		x[i] = i;
	}

	i+=25;

	ASSERT_EQ(*i, 25);
}

// -=

TYPED_TEST(Deque_Fixture, minus_equal_1) {
	typedef typename TestFixture::deque_type deque_type;
	
	deque_type x(10, 0);
	typename deque_type::iterator i=x.end()-1;
	i-=5;
	

	ASSERT_EQ(*i, 0);
}

TYPED_TEST(Deque_Fixture, minus_equal_2) {
	typedef typename TestFixture::deque_type deque_type;
	
	deque_type x(10, 0);
	typename deque_type::iterator i=x.end()-1;

	for(int i = 0; i < 10; ++i){
		x[i] = i;
	}

	i-=5;

	ASSERT_EQ(*i, 4);
}

TYPED_TEST(Deque_Fixture, minus_equal_3) {
	typedef typename TestFixture::deque_type deque_type;
	
	deque_type x(16, 0);
	typename deque_type::iterator i=x.end()-1;

	for(int i = 0; i < 16; ++i){
		x[i] = i;
	}

	i-=5;

	ASSERT_EQ(*i, 10);
}


/*********************** CNOST ITERATOR ********************/
TYPED_TEST(Deque_Fixture, inc_test_const_iterator_1) {
	typedef typename TestFixture::deque_type deque_type;
	
	const deque_type x(10, 0);
	
	int count = 0;

	
	for (typename deque_type::const_iterator i = x.begin(); i != x.end(); ++i) {

		++count;
	}

 	ASSERT_EQ(count, 10);
 }

TYPED_TEST(Deque_Fixture, inc_test_const_iterator_2) {
	typedef typename TestFixture::deque_type deque_type;
	
	const deque_type x(25, 1);
	
	int count = 0;

	
	for (typename deque_type::const_iterator i = x.begin(); i != x.end(); ++i) {
		++count;
	}

	ASSERT_EQ(count, 25);
}

TYPED_TEST(Deque_Fixture, inc_test_const_iterator_3) {
	typedef typename TestFixture::deque_type deque_type;
	
	const deque_type x(47, 0);
	
	int count = 0;

	
	for (typename deque_type::const_iterator i = x.begin(); i != x.end(); ++i) {
		++count;
	}

	ASSERT_EQ(count, 47);
}

//DEC ITER

TYPED_TEST(Deque_Fixture, dec_test_const_iterator_1) {
	typedef typename TestFixture::deque_type deque_type;
	
	const deque_type x(10, 0);
	
	int count = 0;

	
	for (typename deque_type::const_iterator i = x.end()-1; i != x.begin(); --i) {
		++count;
	}

	ASSERT_EQ(count, 9);
}
TYPED_TEST(Deque_Fixture, dec_test_const_iterator_2) {
	typedef typename TestFixture::deque_type deque_type;
	
	const deque_type x(10, 0);
	
	int count = 0;
	
	for (typename deque_type::const_iterator i = x.end()-1; i != x.begin(); --i) {
		++count;
	}

	ASSERT_EQ(count, 9);
}

// +=

TYPED_TEST(Deque_Fixture, const_iterator_plus_equal_1) {
	typedef typename TestFixture::deque_type deque_type;
	
	const deque_type x(10, 0);
	typename deque_type::const_iterator i=x.begin();
	

	ASSERT_EQ(*i, 0);
}

TYPED_TEST(Deque_Fixture, const_iterator_plus_equal_2) {
	typedef typename TestFixture::deque_type deque_type;
	
	const deque_type x(10, 0);
	typename deque_type::const_iterator i=x.begin();





	ASSERT_EQ(*i, 0);
}

TYPED_TEST(Deque_Fixture, const_iterator_plus_equal_3) {
	typedef typename TestFixture::deque_type deque_type;
	
	const deque_type x(45, 0);
	typename deque_type::const_iterator i=x.begin();


	i+=25;

	ASSERT_EQ(*i, 0);
}

// -=

TYPED_TEST(Deque_Fixture, const_iterator_minus_equal_1) {
	typedef typename TestFixture::deque_type deque_type;
	
	const deque_type x(10, 0);
	typename deque_type::const_iterator i=x.end()-1;
	i-=5;
	

	ASSERT_EQ(*i, 0);
}

TYPED_TEST(Deque_Fixture, const_iterator_minus_equal_2) {
	typedef typename TestFixture::deque_type deque_type;
	
	const deque_type x(10, 0);
	typename deque_type::const_iterator i=x.end()-1;



	i-=5;

	ASSERT_EQ(*i, 0);
}

TYPED_TEST(Deque_Fixture, const_iterator_minus_equal_3) {
	typedef typename TestFixture::deque_type deque_type;
	
	const deque_type x(16, 0);
	typename deque_type::const_iterator i=x.end()-1;

	i-=5;

	ASSERT_EQ(*i, 0);
}

//ERASE
TYPED_TEST(Deque_Fixture, erase1) {
	typedef typename TestFixture::deque_type deque_type;
	
	deque_type x(16, 1);

	typename deque_type::iterator i = x.begin();

	x.erase(i + 2);

	ASSERT_EQ(x.size(), 15);
}

TYPED_TEST(Deque_Fixture, erase2) {
	typedef typename TestFixture::deque_type deque_type;
	
	deque_type x(16, 1);

	typename deque_type::iterator i = x.begin();

	x.erase(i + 7);

	ASSERT_EQ(x.size(), 15);
}

TYPED_TEST(Deque_Fixture, erase3) {
	typedef typename TestFixture::deque_type deque_type;
	
	deque_type x(16, 1);

	typename deque_type::iterator i = x.begin();

	x.erase(i + 10);
	x.erase(i + 2);

	ASSERT_EQ(x.size(), 14);
}

//INSERT
TYPED_TEST(Deque_Fixture, insert1) {
	typedef typename TestFixture::deque_type deque_type;
	
	deque_type x(16, 1);

	typename deque_type::iterator i = x.begin();

	x.insert(i+5, 5);

	ASSERT_EQ(x.size(), 17);
	ASSERT_EQ(x[5], 5);
}

TYPED_TEST(Deque_Fixture, insert2) {
	typedef typename TestFixture::deque_type deque_type;
	
	deque_type x(28, 1);

	typename deque_type::iterator i = x.begin();

	x.insert(i+8, 20);

	ASSERT_EQ(x.size(), 29);
	ASSERT_EQ(x[8], 20);
}


//RESIZE

TYPED_TEST(Deque_Fixture, resize1){

	typedef typename TestFixture::deque_type deque_type;

	deque_type x(5, 0);

	x[0] = 0;
	x[1] = 1;
	x[2] = 2;
	x[3] = 3;
	x[4] = 4;

	x.resize(4);

	ASSERT_EQ(x.size(), 4);
	ASSERT_EQ(x.back(), 3);
}

TYPED_TEST(Deque_Fixture, resize2){

	typedef typename TestFixture::deque_type deque_type;

	deque_type x(25, 0);

	x[0] = 0;
	x[1] = 1;
	x[2] = 2;
	x[3] = 3;
	x[4] = 4;

	x.resize(0);

	ASSERT_EQ(x.size(), 0);
}


TYPED_TEST(Deque_Fixture, resize3){

	typedef typename TestFixture::deque_type deque_type;

	deque_type x(175, 0);

	x[0] = 0;
	x[1] = 1;
	x[2] = 2;
	x[3] = 3;
	x[4] = 4;

	x.resize(95);

	ASSERT_EQ(x.size(), 95);
}

TYPED_TEST(Deque_Fixture, resize4){

	typedef typename TestFixture::deque_type deque_type;

	deque_type x(45, 0);

	x[0] = 0;
	x[1] = 1;
	x[2] = 2;
	x[3] = 3;
	x[4] = 4;

	x.resize(59);

	ASSERT_EQ(x.size(), 59);
}

TYPED_TEST(Deque_Fixture, resize5){

	typedef typename TestFixture::deque_type deque_type;

	deque_type x(45, 0);

	x[0] = 0;
	x[1] = 1;
	x[2] = 2;
	x[3] = 3;
	x[4] = 4;

	x.resize(5);

	ASSERT_EQ(x.size(), 5);
}

TYPED_TEST(Deque_Fixture, resize6){

	typedef typename TestFixture::deque_type deque_type;

	deque_type x(48, 0);

	x[0] = 0;
	x[1] = 1;
	x[2] = 2;
	x[3] = 3;
	x[4] = 4;

	x.resize(63);

	ASSERT_EQ(x.size(), 63);
}

//TEST REPO SOMEONE ELSES RESIZE TEST
TYPED_TEST(Deque_Fixture, resize_test_1) {
    typedef typename TestFixture::deque_type deque_type;
    deque_type x(3, 1);
    x.resize(3, 2);
    ASSERT_EQ(3, x.size());
    for (int i = 0; i < 3; ++i) {
        ASSERT_EQ(1, x[i]);
    }
}

TYPED_TEST(Deque_Fixture, resize_test_3) {
    typedef typename TestFixture::deque_type deque_type;
    deque_type x(5);
    for (int i = 0; i < 5; ++i) { x[i] = i; }
    x.resize(3);
    ASSERT_EQ(3, x.size());
    for (int i = 0; i < 3; ++i) {
        ASSERT_EQ(i, x[i]);
    }
}

/*
TYPED_TEST(Deque_Fixture, resize_1) {
    typedef typename TestFixture::deque_type deque_type;

    deque_type x(10,10);
    for(int i= 0; i < 15; ++i){
        x.push_back(i);
    }
    ASSERT_EQ(x.size(),25);
}
*/

//SWAP
TYPED_TEST(Deque_Fixture, swap1) {
    typedef typename TestFixture::deque_type deque_type;

     deque_type x(15,2);
     deque_type y(10, 3);
     x.swap(y);
     ASSERT_EQ(x.size(), 10);
}

TYPED_TEST(Deque_Fixture, swap2) {
    typedef typename TestFixture::deque_type deque_type;

     deque_type x;
     deque_type y(75, 3);
     x.swap(y);
     ASSERT_EQ(x.size(), 75);
}

TYPED_TEST(Deque_Fixture, swap3) {
    typedef typename TestFixture::deque_type deque_type;

     deque_type x(16,16);
     deque_type y(27, 13);
     x.swap(y);
     ASSERT_EQ(x.size(), 27);
     ASSERT_EQ(*x.begin(), 13);
}
