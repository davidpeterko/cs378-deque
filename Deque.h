// --------------------------
// projects/c++/deque/Deque.h
// Copyright (C) 2015
// Glenn P. Downing
// --------------------------

#ifndef Deque_h
#define Deque_h

// --------
// includes
// --------

#include <algorithm> // copy, equal, lexicographical_compare, max, swap
#include <cassert>   // assert
#include <iterator>  // iterator, bidirectional_iterator_tag
#include <memory>    // allocator
#include <stdexcept> // out_of_range
#include <utility>   // !=, <=, >, >=
#include <iostream>  //cout

#define ARRSIZE 20

// -----
// using
// -----

using std::rel_ops::operator!=;
using std::rel_ops::operator<=;
using std::rel_ops::operator>;
using std::rel_ops::operator>=;

// -------
// destroy
// -------

template <typename A, typename BI>
BI destroy (A& a, BI b, BI e) {
    while (b != e) {
        //std::cout<<"we are in destry while loop and b is: "<<*b<<" this is e: "<<*e+1<<std::endl; 
        --e;
        a.destroy(&*e);}
    return b;}

// ------------------
// uninitialized_copy
// ------------------

template <typename A, typename II, typename BI>
BI uninitialized_copy (A& a, II b, II e, BI x) {
    BI p = x;
    try {
        while (b != e) {

            a.construct(&*x, *b);
            ++b;
            ++x;}}
    catch (...) {
        destroy(a, p, x);
        throw;}
    return x;}

// ------------------
// uninitialized_fill
// ------------------

template <typename A, typename BI, typename U>
BI uninitialized_fill (A& a, BI b, BI e, const U& v) {
    BI p = b;
    try {
        while (b != e) {
            a.construct(&*b, v);
            ++b;}}
    catch (...) {
        destroy(a, p, b);
        throw;}
    return e;}

// -------
// my_deque
// -------

template < typename T, typename A = std::allocator<T> >
class my_deque {
    public:
        // --------
        // typedefs
        // --------

        typedef A                                           allocator_type;
        typedef typename allocator_type::value_type         value_type;

        typedef typename allocator_type::size_type          size_type;
        typedef typename allocator_type::difference_type    difference_type;

        typedef typename allocator_type::pointer            pointer;
        typedef typename allocator_type::const_pointer      const_pointer;

        typedef typename allocator_type::reference          reference;
        typedef typename allocator_type::const_reference    const_reference;

        typedef typename A::template rebind<pointer>::other B;
        // typedef typename B::pointer top;
        // typedef typename B::pointer bot;

    public:
        // -----------
        // operator ==
        // -----------

        /**
         * <your documentation>
         */
        friend bool operator == (const my_deque& lhs, const my_deque& rhs) {
                    //call std equal

                    //check same size
                    if(lhs.size() != rhs.size()){
                        return false;
                    }

                    //check if nothing, zero
                    if(lhs.size() == 0 && rhs.size() ==0){
                        return true;
                    }

                    return std::equal(lhs.begin(), lhs.end(), rhs.begin());}

        // ----------
        // operator <
        // ----------

        /**
         * <your documentation>
         */
        friend bool operator < (const my_deque& lhs, const my_deque& rhs) {
            // <your code>
            // you must use std::lexicographical_compare()
            return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());}

    private:
        // ----
        // data
        // ----

        allocator_type _a;

        B _b;

        pointer* _top;
        pointer* _bot;

        pointer* _outer_absolute_s;                 //pointer to pointer, this pointer to start of the outer array, we use this to iterate through the outer array
        pointer* _outer_absolute_e;                 //s and e point to the definite start and end, where as outer_begin and outer_end point to where the actual data starts, diff frmo outer s and outer e

        //inner arrays
        pointer _inner_begin;                       //this keeps track of the inners start
        pointer _inner_end;                         //this keeps track of the inner's end
    
        size_type _inner_front_index;               //index to keep track of the inner array front location
        size_type _inner_back_index;                //index to keep track of the inner array back location

        size_type _outer_front_index;               //index to keep track of the outer array front location
        size_type _outer_back_index;                //index to keep track of the outer array back location

        size_type _outer_size;                      //outer arary size
        size_type _size;                            //keeps track of the size of the used space
        size_type _cap;


    private:
        // -----
        // valid
        // -----

        bool valid () const {


            if(_size < 0){
                return false;
            }

            if(_cap < 0){
                return false;
            }

            if(_inner_begin > _inner_end){
                return false;
            }

            if(_inner_front_index > (ARRSIZE - 1)){
                return false;
            }

            if(_outer_front_index > (_outer_size - 1)){
                return false;
            }
            
            return true;}

    public:
        // --------
        // iterator
        // --------

        class iterator {
            public:
                // --------
                // typedefs
                // --------

                typedef          std::bidirectional_iterator_tag iterator_category;
                typedef typename my_deque::value_type            value_type;
                typedef typename my_deque::difference_type       difference_type;
                typedef typename my_deque::pointer               pointer;
                typedef typename my_deque::reference             reference;
                typedef typename my_deque::size_type             size_type;

            public:
                // -----------
                // operator ==
                // -----------

                /**
                 * <your documentation>
                 */
                friend bool operator == (const iterator& lhs, const iterator& rhs) {
                    if (lhs.dq != rhs.dq)
                        return false;
                    if (lhs._front_inner_index != rhs._front_inner_index)
                        return false;
                    if (lhs._front_outer_index != rhs._front_outer_index)
                        return false;
                    return true;}

                /**
                 * <your documentation>
                 */
                friend bool operator != (const iterator& lhs, const iterator& rhs) {
                    return !(lhs == rhs);}

                // ----------
                // operator +
                // ----------

                /**
                 * <your documentation>
                 */
                friend iterator operator + (iterator lhs, difference_type rhs) {
                    return lhs += rhs;}

                // ----------
                // operator -
                // ----------

                /**
                 * <your documentation>
                 */
                friend iterator operator - (iterator lhs, difference_type rhs) {
                    return lhs -= rhs;}

            private:
                // ----
                // data
                // ----
                
                my_deque* dq;
                size_type _front_outer_index;
                size_type _front_inner_index;



            private:
                // -----
                // valid
                // -----

                bool valid () const {
                    if(_front_outer_index > dq->_outer_size){
                        return false;
                    }


                    return  true;}

            public:
                // -----------
                // constructor
                // -----------

                /**
                 * iterator constructor
                 */
                iterator (my_deque* myd, size_type inner_index, size_type outer_index){

                    dq = myd;
                    _front_inner_index = inner_index;
                    _front_outer_index = outer_index;

                    //we want _it_location to point at this location -> _top[f o][f i]

                    //std::cout << "The value where our iterator is pointing to is: " << (dq + _front_inner_index) << std::endl;
                    //std::cout << "the location of _it_location" << _it_location << std::endl;


                    assert(valid());}

                // Default copy, destructor, and copy assignment.
                // iterator (const iterator&);
                // ~iterator ();
                // iterator& operator = (const iterator&);

                // ----------
                // operator *
                // ----------

                /**
                 * grabs value at the iterator location
                 */
                reference operator * () const {
                    return dq->_top[_front_outer_index][_front_inner_index];}

                // -----------
                // operator ->
                // -----------

                /**
                 * value operator
                 */
                pointer operator -> () const {
                    return &**this;}

                // -----------
                // operator ++
                // -----------

                /**
                 * iterator incrment pre
                 */
                iterator& operator ++ () {

                    this->_front_inner_index = this->_front_inner_index + 1;


                    if(this->_front_inner_index > 19){
                        this->_front_inner_index = 0;
                        this->_front_outer_index = this->_front_outer_index + 1;
                    }
                   
                

                    assert(valid());
                    return *this;}

                /**
                 * iterator increment post
                 */
                iterator operator ++ (int) {
                    iterator x = *this;
                    ++(*this);
                    assert(valid());
                    return x;}

                // -----------
                // operator --
                // -----------

                /**
                 * iterator pre decrement
                 */
                iterator& operator -- () {
                 
                // std::cout <<"went into decrement function " << std::endl;

                    _front_inner_index = _front_inner_index - 1;

                     if((int)_front_inner_index < 0){
                         
                         _front_inner_index =  ARRSIZE - 1;

                        _front_outer_index = _front_outer_index - 1;  
                      }
                     

                    assert(valid());
                    return *this;}

                /**
                 * iterator post decrement
                 */
                iterator operator -- (int) {
                    iterator x = *this;
                    --(*this);
                    assert(valid());
                    return x;}

                // -----------
                // operator +=
                // -----------

                /**
                 * iterator +=
                 */
                iterator& operator += (difference_type d) {

                     this->_front_inner_index = this->_front_inner_index + d;


                    if(this->_front_inner_index >  19){
                        difference_type temp= d/20;
                        difference_type offset=d%20;
                        this->_front_inner_index = offset;
                        this->_front_outer_index = this->_front_outer_index + temp;
                    }


                    assert(valid());
                    return *this;}

                // -----------
                // operator -=
                // -----------

                /**
                 * iterator -=
                 */
                iterator& operator -= (difference_type d) {

                    while(d>0){
                        --*this;
                        --d;
                    }

                    assert(valid());
                    return *this;}};

    public:
        // --------------
        // const_iterator
        // --------------

        class const_iterator {
            public:
                // --------
                // typedefs
                // --------

                typedef          std::bidirectional_iterator_tag iterator_category;
                typedef typename my_deque::value_type            value_type;
                typedef typename my_deque::difference_type       difference_type;
                typedef typename my_deque::const_pointer         pointer;
                typedef typename my_deque::const_reference       reference;

            public:
                // -----------
                // operator ==
                // -----------

                /**
                 * <your documentation>
                 */
                friend bool operator == (const const_iterator& lhs, const const_iterator& rhs) {
                    if (lhs.dq != rhs.dq)
                        return false;
                    if (lhs._front_inner_index != rhs._front_inner_index)
                        return false;
                    if (lhs._front_outer_index != rhs._front_outer_index)
                        return false;
                    return true;}

                /**
                 * <your documentation>
                 */
                friend bool operator != (const const_iterator& lhs, const const_iterator& rhs) {
                    return !(lhs == rhs);}

                // ----------
                // operator +
                // ----------

                /**
                 * <your documentation>
                 */
                friend const_iterator operator + (const_iterator lhs, difference_type rhs) {
                    return lhs += rhs;}

                // ----------
                // operator -
                // ----------

                /**
                 * <your documentation>
                 */
                friend const_iterator operator - (const_iterator lhs, difference_type rhs) {
                    return lhs -= rhs;}

            private:
                // ----
                // data
                // ----
                const my_deque* dq;
                 size_type _front_inner_index;
                 size_type _front_outer_index;

            private:
                // -----
                // valid
                // -----

                bool valid () const {
                    if(_front_outer_index > dq->_outer_size){
                        return false;
                    }
                    return true;}

            public:
                // -----------
                // constructor
                // -----------

                /**
                 *  cosnt iterator contrsuctor
                 */
                const_iterator (const my_deque* myd,  size_type inner_index,  size_type outer_index){
                    dq = myd;
                    _front_inner_index = inner_index;
                    _front_outer_index = outer_index;

                    assert(valid());}

                // Default copy, destructor, and copy assignment.
                // const_iterator (const const_iterator&);
                // ~const_iterator ();
                // const_iterator& operator = (const const_iterator&);

                // ----------
                // operator *
                // ----------

                /**
                 * const iterator * operator
                 */
                reference operator * () const {
                    return dq->_top[_front_outer_index][_front_inner_index];}

                // -----------
                // operator ->
                // -----------

                /**
                 * const iterator value
                 */
                pointer operator -> () const {
                    return &**this;}

                // -----------
                // operator ++
                // -----------

                /**
                 * cosnt iterator increment pre
                 */
                const_iterator& operator ++ () {
                   
                    this->_front_inner_index = this->_front_inner_index + 1;


                    if(this->_front_inner_index > 19){
                        this->_front_inner_index = 0;
                        this->_front_outer_index = this->_front_outer_index + 1;
                    }
                   

                   /// std::cout<<"dq->_top[0]: "<<dq->_top[0]<<std::endl;
                    //std::cout<<"&(dq[_front_outer_index][_front_inner_index] "<<&(dq[_front_outer_index][_front_inner_index])<<std::endl;
                    
                    // if (dq->_top[0]==&(dq[_front_outer_index][_front_inner_index])){
                    //     throw std::out_of_range("No space has been allocated");
                    // }
                
                    
                    assert(valid());
                    return *this;}

                /**
                 * const iterator increment post
                 */
                const_iterator operator ++ (int) {
                    const_iterator x = *this;
                    ++(*this);
                    assert(valid());
                    return x;}

                // -----------
                // operator --
                // -----------

                /**
                 * const iterator decrement, pre
                 */
                const_iterator& operator -- () {
                    
                    // std::cout <<"went into decrement function " << std::endl;

                    _front_inner_index = _front_inner_index - 1;

                     if((int)_front_inner_index < 0){
                         
                         _front_inner_index =  ARRSIZE - 1;

                        _front_outer_index = _front_outer_index - 1;  
                      }
        
                    assert(valid());
                    return *this;}

                /**
                 * cost iterator decrement, post
                 */
                const_iterator operator -- (int) {
                    const_iterator x = *this;
                    --(*this);
                    assert(valid());
                    return x;}

                // -----------
                // operator +=
                // -----------

                /**
                 * csont iterator operation +=
                 */
                const_iterator& operator += (difference_type d) {
                    
                    this->_front_inner_index = this->_front_inner_index + d;


                    if(this->_front_inner_index >  19){
                        difference_type temp= d/20;
                        difference_type offset=d%20;
                        this->_front_inner_index = offset;
                        this->_front_outer_index = this->_front_outer_index + temp;
                    }

                    assert(valid());
                    return *this;}

                // -----------
                // operator -=
                // -----------

                /**
                 * const iterator operation -=
                 */
                const_iterator& operator -= (difference_type d) {

                    while(d>0){
                        --*this;
                        --d;
                    }

                    assert(valid());
                    return *this;}};

    public:
        // ------------
        // constructors
        // ------------

        /**
         * empty constructor
         */
        explicit my_deque (const allocator_type& a = allocator_type()):

            _a(a){
                _top = 0;
                _bot = 0;

                _outer_absolute_s = 0;                 //pointer to pointer, this pointer to start of the outer array, we use this to iterate through the outer array
                _outer_absolute_e = 0;                 //s and e point to the definite start and end, where as outer_begin and outer_end point to where the actual data starts, diff frmo outer s and outer e

                _inner_begin = 0;                       //this keeps track of the inners start
                _inner_end = 0;                         //this keeps track of the inner's end
            
                _inner_front_index = 0;
                _inner_back_index = 0;
                _outer_front_index = 0;
                _outer_back_index = 0;

                _outer_size = 0;
                _size =0;                            //keeps track of the size of the used space
                _cap = 0;


            assert(valid());}

        /**
         * cosntructor
         */
        explicit my_deque (size_type s, const_reference v = value_type(), const allocator_type& a = allocator_type()):

            _a(a) {
                _size = s;
                size_type offset = s % ARRSIZE;
                size_type num_row_count;

                if(offset == 0){
                    num_row_count = s/ARRSIZE;
                }
                else if(offset > 0){
                    num_row_count = s/ARRSIZE + 1;
                }

                _outer_size = (s/ARRSIZE) + 1;                   //get the outer array size
                _outer_size = num_row_count;

                _cap = _outer_size * ARRSIZE;

                _top = _b.allocate(_outer_size);                 //allocate outer array


                //allocateing the inner arrays
                for(int i = 0; i < _outer_size; ++i){
                    _top[i] = _a.allocate(ARRSIZE);
                }

                size_type start_index = 0;
                size_type remaining_values = s;

                size_type last_index = _outer_size - 1;

                //filling the inner arrays
                for(int i = 0; i < _outer_size; ++i){

                    //filling first row
                    if( i == 0){
                        _inner_begin = _top[0]+ start_index;
                        _inner_front_index = 0  + start_index;                                       //set to zero
                        _outer_front_index = 0;                                                 //set to zero, so its at the front
                    
                        if(ARRSIZE <= s){
                            uninitialized_fill(_a, _inner_begin, _top[0] + ARRSIZE, v);
                            remaining_values = remaining_values - ARRSIZE;
                        }

                        //this puts data on the row if it fits onn one row
                        else{
                            _inner_end = _inner_begin + s;
                            _inner_back_index = start_index + s;
                            _outer_back_index = 0;
                            uninitialized_fill(_a, _inner_begin, _inner_end, v);
                            remaining_values = remaining_values - s;
                        }
                    }
                    //filling last row
                    else if( i == last_index){
                        _inner_end = _top[i] + remaining_values;
                        _inner_back_index = remaining_values;
                        _outer_back_index = i;
                        uninitialized_fill(_a, _top[i], _inner_end, v);

                        remaining_values = remaining_values - remaining_values;

                        if(remaining_values != 0){
                            //this will be an error, we minused wrong
                            //cout <<"error, we didnt calcualte reminaing right" << endl;
                        }
                    }
                    //filling inbetween rows
                    else{
                        uninitialized_fill(_a, _top[i], _top[i] + ARRSIZE, v);
                        remaining_values = remaining_values - ARRSIZE;
                    }
                }

                //debugging
                //run asserts to check inner and outer front and end

                _outer_absolute_s = _top;
                _outer_absolute_e = _top+num_row_count-1;
                _bot = _outer_absolute_e;

                //outer absolute keeps track of the outer array CONCRETE end points

            
            assert(valid());}

        /**
         * copy constructor
         */
        my_deque (const my_deque& that):
            _a(that._a){

                //assign old deque to new deque stuff
                _size = that._size;
                _cap = that._cap;
                _outer_size = that._outer_size;
                _inner_front_index = that._inner_front_index;
                _outer_front_index = that._outer_front_index;
                _inner_back_index = that._inner_back_index;
                _outer_back_index = that._outer_back_index;

                //reallocate outside space
                _top = _b.allocate(_outer_size);

                size_type offset;

                offset = _size % ARRSIZE;

                if(offset > 0){
                    //do stuff?
                    //the last row needs to be initialized partially?
                }

                //allocate and fill
                for(int i = 0; i < _outer_size; ++i){
                    _top[i] = _a.allocate(ARRSIZE);
                }

                for(int i = 0 ; i < _outer_size; ++i){
                    uninitialized_copy(_a, that._top[i], that._top[i] + ARRSIZE, _top[i]);
                }

                //now we gotta get the _inner_begin and _inner end
                int x_start_loc;
                int x_end_loc;
                int y_start_loc;
                int y_end_loc;

                for(int outer = 0; outer < _outer_size; ++outer){

                    for(int inner = 0; inner < ARRSIZE; ++inner) {

                        //check to see if that spot is the _inner_begin
                        if((that._top[outer] + inner) == that._inner_begin){
                            x_start_loc = outer;
                            y_start_loc = inner;
                        }

                        if((that._top[outer] + inner) == that._inner_end){
                            x_end_loc = outer;
                            y_end_loc = inner;
                        }
                    }
                }

                //now we have the index locations
                _inner_begin = _top[x_start_loc] + y_start_loc;
                _inner_end = _top[x_end_loc] + y_end_loc;


                //debug
                //cout << "The object here is: " << *_inner_begin << endl;
                //cout << "The object here is: " << *_inner_end << endl;

            assert(valid());}

        // ----------
        // destructor
        // ----------

        /**
         * destructs and frees all memory after a deque is used
         */
        ~my_deque () {
            
            //std::cout<< "just entered the destructor " << std::endl;
            //destroy all the valid objects
            destroy(_a, begin(), end());

            //std::cout<< "finishes destroy " << std::endl;


            //deallocate all the inner arrays
            //std::cout<<"the outer size is : " << _outer_size << std::endl;

            for(int i  = 0; i < _outer_size; ++i){
                _a.deallocate(_top[i], ARRSIZE);
                //std::cout<< " inside the for loop, deallocating each inner array, now deallo aray: " << i << std::endl;
            }    

            //std::cout<<"finishse deallocating inner arrays"<<std::endl;

            _b.deallocate(_top, _outer_size);

            //std::cout<<"finished deallocating outer array" << std::endl;
        
            assert(valid());}

        // ----------
        // operator =
        // ----------

        /**
         * assignment oeprator
         */
        my_deque& operator = (const my_deque& rhs) {

            if(this == &rhs){
                return *this;
            }
            if(rhs.size() == size()){
               std::copy(rhs.begin(), rhs.end(), begin()); 
            }
            else if(rhs.size() < size()){
                std::copy(rhs.begin(), rhs.end(), begin());
                resize(rhs.size());
            }
            else if(rhs.size() <= _cap){
                std::copy(rhs.begin(), rhs.begin() + size(), begin());
                uninitialized_copy(_a, rhs.begin() + size(), rhs.end(), end());
            }
            else{
                clear();
                resize(rhs.size());

            }


            assert(valid());
            return *this;}

        // -----------
        // operator []
        // -----------

        /**
         * this takes an index, and counts from the beginning of the deque and returns the value at the index
         */
        reference operator [] (size_type index) {

            size_type temp_inner = _inner_front_index + index;
            size_type temp_outer = _outer_front_index;

            while(temp_inner >= ARRSIZE){
                temp_inner = temp_inner - ARRSIZE;
                ++temp_outer;
            }

            return _top[temp_outer][temp_inner];}

        /**
         * <your documentation>
         */
        const_reference operator [] (size_type index) const {
            return const_cast<my_deque*>(this)->operator[](index);}

        // --
        // at
        // --

        /**
         * the at function for acecss elements, this shuold throw a out of range error if they go past our bounds
         */
        reference at (size_type index) {

            size_type temp_inner = _inner_front_index + index;
            size_type temp_outer = _outer_front_index;

            while(temp_inner >= ARRSIZE){
                temp_inner = temp_inner - ARRSIZE;
                ++temp_outer;
            }

            //check the reference out of bounds?
            if(temp_outer > _outer_size){
                throw std::out_of_range("The access of the operator at is trying to access a spot that is not allocated or constructed.");
            }

            if(temp_inner > ARRSIZE){
                throw std::out_of_range("The access of the operator at is trying to access a spot that is not allocated or constructed.");
            }


            return _top[temp_outer][temp_inner];}
        /**
         * <your documentation>
         */
        const_reference at (size_type index) const {
            return const_cast<my_deque*>(this)->at(index);}

        // ----
        // back
        // ----

        /**
         * returns last value of the back of the deque
         */
        reference back () {

            size_type temp_back = _inner_back_index;

            //we need to grab the preivous array, lat value, if our index is 0, sinc w can go into a negative reference

            if(temp_back == 0){
                //std::cout << " we are in the if, wre the indx should be 0 iof the preivous array " << std::endl;

                return _top[_outer_back_index-1][_inner_back_index+19];
            }


            return _top[_outer_back_index][_inner_back_index-1];}

        /**
         * a const_reference use of back
         */
        const_reference back () const {
            return const_cast<my_deque*>(this)->back();}

        // -----
        // begin
        // -----

        /**
         * calls a iterator to start at the beginning of the deque
         */
        iterator begin () {
            return iterator(this, _inner_front_index, _outer_front_index);}

        /**
         * calls a const iterator
         */
        const_iterator begin () const {
            return const_iterator(this, _inner_front_index, _outer_front_index);}

        // -----
        // clear
        // -----

        /**
         * destrys all elements curretly constructed
         */
        void clear () {

            resize(0);
            assert(valid());}

        // -----
        // empty
        // -----

        /**
         * returns a bool to see if the deque is empty or not
         */
        bool empty () const {
            return !size();}

        // ---
        // end
        // ---

        /**
         * returns a iterato to the end()
         */
        iterator end () {
            return iterator(this, _inner_back_index, _outer_back_index);}

        /**
         * returns a const iterator for the end()
         */
        const_iterator end () const {
            // <your code>
            return const_iterator(this, _inner_back_index, _outer_back_index);}

        // -----
        // erase
        // -----

        /**
         * erases the value at the iterator location
         */
        iterator erase (iterator i) {

            _size = _size - 1;

            while(i != end()){
                *i = *i + 1;                        //assignt he after value to the current value and keep pushing 
                ++i;                                //the values forward
            }

            _inner_back_index = _inner_back_index - 1;

            if(_inner_back_index < 0){
                _inner_back_index = ARRSIZE - 1;
                _outer_back_index  = _outer_back_index - 1;
            }

            assert(valid());
            return i;}

        // -----
        // front
        // -----

        /**
         * returns the value at the front of the deque
         */
        reference front () {

            return _top[_outer_front_index][_inner_front_index];}

        /**
         * a cosn reference return of the front value of the deque
         */
        const_reference front () const {
            return const_cast<my_deque*>(this)->front();}

        // ------
        // insert
        // ------

        /**
         * insert a value at the iterator location, we push back the values behind what we inserted
         */
        iterator insert (iterator i, const_reference v) {
            
            //check if there is anymore space in the deque in the back
            if((_outer_back_index == _outer_size -1) && (_inner_back_index == ARRSIZE-1)){
                size_type force_size = _cap * 2;
                resize(force_size);
            }


            //if inserting into end, call push back, push back shuld take care of the size issue with resize called in it
            if(i == this->end()){
                push_back(v);
            }

            //push back the inner back index, i::deallocate(int*, unsigned long) (in /v/filer4b/v38q001/davidko/Desktop/cs378-deque/TestDeque)f past the array, 
            //reset to the next array @ 0 and increment outer array pointer by 1 to next array
            _inner_back_index = _inner_back_index + 1;

            if(_inner_back_index > 19){
                _inner_back_index = 0;
                _outer_back_index = _outer_back_index + 1;
            }

            //copy everything from - to end, to i + 1 to end + 1
            std::copy(i, end(), i + 1);

            //assign the value of v to the position of *i, we dont change *i position
            *i = v;

            _size = _size + 1;

            assert(valid());
            return i;}

        // ---
        // pop
        // ---

        /**
         * removes the last value of the deque, and reduces size, and resets our indices
         */
        void pop_back () {

            if(_size == 0){
                throw std::out_of_range("There is nothing to call pop_back() on.");
            }

            _size = _size - 1;

            _inner_back_index = _inner_back_index - 1;

            
            if(_inner_back_index < 0){

                _outer_back_index = _outer_front_index - 1;                 //so we decrement the OUTSIDE array index cause were going back u poen
                _inner_back_index = ARRSIZE - 1;
            }

            assert(valid());}

        /**
         * removes the first value from the deque, reduces size, and reset our front indices
         */
        void pop_front () {

            if(_size == 0){
                throw std::out_of_range("There is nothing to call pop_front() on.");
            }

            _size = _size - 1;

            _inner_front_index = _inner_front_index + 1;

            if(_inner_front_index > 19){
                _outer_front_index = _outer_front_index + 1;
                _inner_front_index = 0;
            }

            assert(valid());}

        // ----
        // push
        // ----

        /**
         * pushes the value v to the back of the deque, resizes if no size
         */
        void push_back (const_reference x) {

            if((_outer_back_index == _outer_size -1) && (_inner_back_index == ARRSIZE-1)){
                size_type force_size = _cap * 2;
                resize(force_size);
            }
             
           _inner_back_index=_inner_back_index + 1;
           if(_inner_back_index > 19){
            _inner_back_index = 0;
            _outer_back_index = _outer_back_index + 1;
           }

           _top[_outer_back_index][_inner_back_index - 1]=x;

           _size  = _size + 1;

            assert(valid());}

        /**
         * pushes a value x into the front, if no size left, resize, and reset indices
         */
        void push_front (const_reference x) {

            if(_outer_front_index == 0 && _inner_front_index == 0){
                size_type force_size = _cap*2;
                resize(force_size);
                }


            _inner_front_index = _inner_front_index - 1;
            if(_inner_front_index < 0){
                _inner_front_index = ARRSIZE -1;
                _outer_front_index = _outer_front_index - 1;
            }


            _top[_outer_front_index][_inner_front_index] = x;            


            _size = _size + 1;

            assert(valid());}

        // ------
        // resize
        // ------

        /**
         * resizes based on the size s passed through
         */
        void resize (size_type s, const_reference v = value_type()) {

            if (s == size())

                return;

            if(s<size()){

                size_type difference = _size - s;
                
                destroy(_a, begin()+s, end());          //destroys all the extra stuff we dont need


                while(difference > 0){

                    _inner_back_index = _inner_back_index - 1;

                    if(_inner_back_index < 0){
                        _inner_back_index = ARRSIZE - 1;
                        _outer_back_index = _outer_back_index - 1;
                    }

                    difference = difference - 1;
                }

                //indices are set
                _size = s;
            }
            else if(s<=_cap){

                _size = s;
                uninitialized_fill(_a, end(), begin() + s, v);

                //we need to reassign the back indices, since the front dont move
                size_type _outer_front_temp;
                size_type _inner_front_temp;

                _outer_front_temp = _outer_front_index;
                _inner_front_temp = _inner_front_index;


                size_type temp_size = _size;
                while(temp_size > 0){
                    
                    _inner_front_temp = _inner_front_temp + 1;

                    if(_inner_front_temp > ARRSIZE - 1){
                        _inner_front_temp = 0;
                        _outer_front_temp = _outer_front_temp;
                    }

                    temp_size = temp_size - 1;
                }


                _outer_back_index = _outer_front_temp;
                _inner_back_index = _inner_front_temp;
            }
            //if size > cap
            //problem = resize doesntwork when we need to move data to thenext arary

            else{
                
                //std::cout <<"we get into this part where we try n resize bigger" << std::endl;

                _size = s;

                pointer* _new_top;
                pointer* _new_bot;

                pointer* _old_top = _top;

                //std::cout<<"the original _bot is " << _bot << std::endl;
                pointer* _old_bot = _bot;

                size_type _new_front_outer_index;
                size_type _new_back_outer_index;

                size_type _new_front_inner_index;
                size_type _new_back_inner_index;

                size_type _temp_old_front_outer_index = _outer_front_index;
                size_type _temp_old_back_outer_index = _outer_back_index;

                size_type _temp_old_front_inner_index = _inner_front_index;
                size_type _temp_old_back_inner_index = _inner_back_index;

                size_type _old_outer_size = _outer_size;                             //old outer size
                size_type _old_size = _size;                                        

                size_type offset = 0;
                size_type _new_cap; 

                size_type _new_outer_size = _old_outer_size * 2;

                _new_cap = _new_outer_size * ARRSIZE;

                //allocating outer array, with our new outer size
                _new_top = _b.allocate(_new_outer_size);
                _new_bot = _new_top + _new_outer_size - 1;

                offset = (_new_outer_size - _old_outer_size) / 2;                   //this should give us the front space we need to fill / offset

                std::cout<<"the offset here is : " << offset << std::endl;

                if(offset == 0){
                    offset = offset + 1;
                }

                size_type running_counter = 0;

                //allocate the front space before we copy
                while(running_counter < offset){
                    _new_top[running_counter] = _a.allocate(ARRSIZE);
                    running_counter = running_counter + 1;
                }
            std::cout<<"the running counter here is : " << offset << std::endl;


                //std::cout<<"Get herse before the std:;copy"<< std::endl;
                //std::cout<<"the old top: " << _old_top << std::endl;
               // std::cout<<"the old bot: " << _old_bot << std::endl;
                //std::cout<<"the new top + offset: " << _new_top + offset<< std::endl;

                std::copy(_old_top, _old_bot, _new_top + offset);

                std::cout<<"Get herse after the std:;copy"<< std::endl;

                running_counter = running_counter + _old_outer_size;

                std::cout << "the value of running counter after the copy: " << running_counter << std::endl;
                std::cout<<"the new outer size : " << _new_outer_size << std::endl;

                while(running_counter < _new_outer_size){
                    _new_top[running_counter] = _a.allocate(ARRSIZE);
                    running_counter = running_counter + 1;
                std::cout << "while loopsdfapssd: " << running_counter << std::endl;

                }

                std::cout << "now we broke out of the while loop"  << std::endl;
                std::cout << "the value of running counter breaks out of while loop: " << running_counter << std::endl;
                std::cout << "the value of offset:  " << offset << std::endl;


                //reassign values
                _top = _new_top;
                _bot = _new_bot;

                _outer_front_index = _temp_old_front_outer_index + offset;
                _outer_back_index = _temp_old_back_outer_index + offset;

                //inner indicies shouldnt move

                _outer_size = _new_outer_size;
                _cap = _new_cap;


                //deallocate
                _b.deallocate(_old_top, _old_outer_size - 1);
                std::cout<<"debugger debugger" << std::endl;

            }
            assert(valid());}

        // ----
        // size
        // ----

        /**
         * returns the size of the deque (actual values)
         */
        size_type size () const {
            return _size;}

        // ----
        // swap
        // ----

        /**
         * swaps 2 deques values
         */
        void swap (my_deque& that) {

            if(_a == that._a){
                //swap the traits

                std::swap(_top, that._top);
                std::swap(_bot, that._bot);
                std::swap(_size, that._size);
                std::swap(_cap, that._cap);
                std::swap(_inner_front_index, that._inner_front_index);
                std::swap(_inner_back_index, that._inner_back_index);
                std::swap(_outer_front_index, that._outer_front_index);
                std::swap(_outer_back_index, that._outer_back_index);
                std::swap(_outer_size, that._outer_size);
                std::swap(_outer_absolute_e, that._outer_absolute_e);
                std::swap(_outer_absolute_s, that._outer_absolute_s);
            }

            else{
                my_deque x(*this);
                *this = that;
                that = x;
            }

            assert(valid());}};

#endif // Deque_h
