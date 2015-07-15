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
            // <your code>
            // you must use std::equal()
            return true;}

        // ----------
        // operator <
        // ----------

        /**
         * <your documentation>
         */
        friend bool operator < (const my_deque& lhs, const my_deque& rhs) {
            // <your code>
            // you must use std::lexicographical_compare()
            return true;}

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
        pointer* _outer_begin;                      //beginning of the used space
        pointer* _outer_end;                        //end of the used space

        //inner arrays
        pointer _inner_begin;                       //this keeps track of the inners start
        pointer _inner_end;                         //this keeps track of the inner's end
        pointer _inner_absolute_s;                  //beignning of the allocated dpace
        pointer _inner_absolute_e;                  
        size_type _size;                            //keeps track of the size of the used space
        size_type _cap;

        pointer temp_start;
        pointer temp_end;

    private:
        // -----
        // valid
        // -----

        bool valid () const {



            if(_inner_begin > _inner_end){
                return false;
            }

            if(_outer_begin > _outer_end){
                return false;
            }
        
            if(_size < 0){
                return false;
            }


            if(_outer_absolute_s > _outer_absolute_e){
                return false;
            }

            if(_cap < 0){
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
                    return lhs._it_location == rhs._it_location;}

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
                
                pointer* _outer_begin;
                pointer _it_location;
                pointer _end_of_data;
                pointer _start_of_data;
                size_type _room_left;
                pointer _it_abs_s;
                pointer _it_abs_e;

            private:
                // -----
                // valid
                // -----

                bool valid () const {

                    return (_outer_begin != 0);}

            public:
                // -----------
                // constructor
                // -----------

                /**
                 * <your documentation>
                 */
                iterator (my_deque* dq) :
                     //size_type i;
                    _outer_begin(dq->_outer_begin),
                    _it_location(dq->_inner_begin),
                    _end_of_data(dq->_inner_end), 
                    _start_of_data(dq-> _inner_begin),
                    _it_abs_s(dq->_inner_absolute_s),
                    _it_abs_e(dq->_inner_absolute_e){

                        _room_left = ARRSIZE - (_it_location) - 1;

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
                    return *_it_location;}

                // -----------
                // operator ->
                // -----------

                /**
                 * <your documentation>
                 */
                pointer operator -> () const {
                    return &**this;}

                // -----------
                // operator ++
                // -----------

                /**
                 * <your documentation>
                 */
                iterator& operator ++ () {

                    if(_it_location == _end_of_data){
                        throw std::out_of_range("Trying to increment iterator past end of data.");
                    }


                    if(_room_left == 0){

                        _outer_begin =  _outer_begin + 1;
                        _it_location = *_outer_begin;

                        _room_left = 19;
                        *this = _it_location;
                    }
                    else{
                        _it_location = _it_location + 1;
                        _room_left = _room_left - 1;
                    }
                    
                    
                    assert(valid());
                    return *this;}

                /**
                 * <your documentation>
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
                 * <your documentation>
                 */
                iterator& operator -- () {
                   
                    if(_it_location == _start_of_data){
                        throw std::out_of_range("Trying to decrement iterator past the start of data.");
                    }


                    if(_room_left == 19){

                        _outer_begin =  _outer_begin - 1;
                        _it_location = *_outer_begin+19;

                        _room_left = 0;
                        *this = _it_location;
                    }
                    else{
                        _it_location = _it_location - 1;
                        _room_left = _room_left + 1;
                    }
                    
                    assert(valid());
                    return *this;}

                /**
                 * <your documentation>
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
                 * <your documentation>
                 */
                iterator& operator += (difference_type d) {

                    //d = positive o rnegative value

                    while(d > 0){

                        if(_it_location == _end_of_data){
                            throw std::out_of_range("Trying to increment iterator past end of data.");
                        }


                        if(_room_left == 0){

                            _outer_begin =  _outer_begin + 1;
                            _it_location = *_outer_begin;

                            _room_left = 19;
                            *this = _it_location;
                        }
                        else{
                            _it_location = _it_location + 1;
                            _room_left = _room_left - 1;
                        }



                        --d;
                    }

                    assert(valid());
                    return *this;}

                // -----------
                // operator -=
                // -----------

                /**
                 * <your documentation>
                 */
                iterator& operator -= (difference_type d) {

                    while( d > 0){

                        if(_it_location == _start_of_data){
                            throw std::out_of_range("Trying to decrement iterator past the start of data.");
                        }


                        if(_room_left == 19){

                            _outer_begin =  _outer_begin - 1;
                            _it_location = *_outer_begin+19;

                            _room_left = 0;
                            *this = _it_location;
                        }
                        else{
                            _it_location = _it_location - 1;
                            _room_left = _room_left + 1;
                        }

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

                    return lhs._it_location == rhs._it_location;}

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

                pointer* _outer_begin;
                pointer _it_location;
                pointer _end_of_data;
                pointer _start_of_data;
                size_type _room_left;
                pointer _it_abs_s;
                pointer _it_abs_e;

            private:
                // -----
                // valid
                // -----

                bool valid () const {
                    // <your code>
                    return true;}

            public:
                // -----------
                // constructor
                // -----------

                /**
                 * <your documentation>
                 */
                const_iterator (const my_deque dq) :
                     //size_type i;
                    _outer_begin(dq->_outer_begin),
                    _it_location(dq->_inner_begin),
                    _end_of_data(dq->_inner_end), 
                    _start_of_data(dq-> _inner_begin),
                    _it_abs_s(dq->_inner_absolute_s),
                    _it_abs_e(dq->_inner_absolute_e){

                        _room_left = ARRSIZE - (_it_location) - 1;

                    assert(valid());}

                // Default copy, destructor, and copy assignment.
                // const_iterator (const const_iterator&);
                // ~const_iterator ();
                // const_iterator& operator = (const const_iterator&);

                // ----------
                // operator *
                // ----------

                /**
                 * <your documentation>
                 */
                reference operator * () const {

                    return *_it_location;}

                // -----------
                // operator ->
                // -----------

                /**
                 * <your documentation>
                 */
                pointer operator -> () const {
                    return &**this;}

                // -----------
                // operator ++
                // -----------

                /**
                 * <your documentation>
                 */
                const_iterator& operator ++ () {
                   
                    if(_it_location == _end_of_data){
                        //check ends and start
                    }


                    if(_room_left == 0){

                        _outer_begin =  _outer_begin + 1;
                        _it_location = *_outer_begin;

                        _room_left = 19;
                        *this = _it_location;
                    }
                    else{
                        _it_location = _it_location + 1;
                        _room_left = _room_left - 1;
                    }
                    
                    assert(valid());
                    return *this;}

                /**
                 * <your documentation>
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
                 * <your documentation>
                 */
                const_iterator& operator -- () {
                    
                    if(_it_location == _start_of_data){
                        //check it hits front;
                    }


                    if(_room_left == 19){

                        _outer_begin =  _outer_begin - 1;
                        _it_location = *_outer_begin+19;

                        _room_left = 0;
                        *this = _it_location;
                    }
                    else{
                        _it_location = _it_location - 1;
                        _room_left = _room_left + 1;
                    }
                    
                    assert(valid());
                    return *this;}

                /**
                 * <your documentation>
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
                 * <your documentation>
                 */
                const_iterator& operator += (difference_type) {
                    // <your code>
                    assert(valid());
                    return *this;}

                // -----------
                // operator -=
                // -----------

                /**
                 * <your documentation>
                 */
                const_iterator& operator -= (difference_type) {
                    // <your code>
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

                //set everything to zero - this is basically the zero consturctor, no arguements -> my_deque<int> s
                _outer_begin = 0;                                   //set outer's to 0
                _outer_end = 0;             
                _inner_begin = 0;                                   //set inners to 0
                _inner_end = 0;
                _outer_absolute_s = 0;                                       //set the outer absol to 0
                _outer_absolute_e = 0;   
                _inner_absolute_s = 0;
                _inner_absolute_e = 0;
                _size = 0;  
                _top = 0;
                _bot = 0;
                _cap = 0;

            assert(valid());}

        /**
         * cosntructor
         */
        explicit my_deque (size_type s, const_reference v = value_type(), const allocator_type& a = allocator_type()):

            _a(a) {

                _size = s;

                size_type x =s/ARRSIZE+2;
               
                _top=_b.allocate(x);

                for(int i=0; i<x; ++i){
                    _top[i] = _a.allocate(ARRSIZE);
                }

                _outer_absolute_s = _top;
                _outer_absolute_e = _top + x -1;
                _bot = _outer_absolute_e;

                if(x == 1){
                    _outer_begin = _top+1;
                    _outer_end = _top+1;
                }
                else if(x > 1){
                    _outer_begin = _top+1;
                    _outer_end = _top+x-1;
                }

                //top is our deque_map
                _inner_begin = _top[0];                      //from

                if(s < 20){
                    _inner_end = _inner_begin + s;
                    uninitialized_fill(_a, _inner_begin, _inner_end, v);
                }
                else{
                    size_type temp = s/20;

                    pointer temp_start;
                    pointer temp_end;

                    for(int i = 0; i < temp; ++i){
                        temp_start = _top[i];
                        temp_end = _top[i]+19;
                        uninitialized_fill(_a, temp_start, temp_end, v);
                    }

                    //done filling the front , now need to fill the offset if there exists

                    size_type offset = s % 20;
                    _inner_end=_top[temp]+offset;
                    temp_start = _top[temp];
                    //_outer_end = _top+temp-1;
                    uninitialized_fill(_a, temp_start, _inner_end, v);
                }

                _inner_absolute_s = _top[0];                            //abs start of the allocation
                _inner_absolute_e = _top[x-1]+19;                       //abs end of the allocation

                _cap = x * ARRSIZE;


                uninitialized_fill(_a, _inner_begin, _inner_end, v);
            
            assert(valid());}

        /**
         * copy constructor
         */
        my_deque (const my_deque& that):
            _a(that._a){

                _size = that.size();

                size_type x = _size/ARRSIZE + 2;

                _top = _b.allocate(x);


                for(int i=0; i<x; ++i){
                    _top[i] = _a.allocate(ARRSIZE);
                }

                _outer_absolute_s = _top;
                _outer_absolute_e = _top + x -1;
                _bot = _outer_absolute_e;

                if(x == 1){
                    _outer_begin = _top+1;
                    _outer_end = _top+1;
                }
                else if(x > 1){
                    _outer_begin = _top+1;
                    _outer_end = _top+x;
                }

                //top is our deque_map
                _inner_begin = _top[1];                      //from

                size_type offset;

                if(_size <= 20){
                    _inner_end = _inner_begin + _size;
                }
                else{

                    //_inner_end setting the end

                    size_type temp = _size/20;
                    size_type offset = _size % 20;
                    _inner_end=_top[temp]+offset;
                    _outer_end = _top+temp+1;
                }

                _inner_absolute_s = _top[0];
                _inner_absolute_e = _top[0+x-1]+19;

                //_inner_end is set to offset
                //_inner_start is looking at the beignning of a inner array set to top[1]

                uninitialized_copy(_a, that.begin(), that.end(), _inner_begin);

            assert(valid());}

        // ----------
        // destructor
        // ----------

        /**
         * <your documentation>
         */
        ~my_deque () {

            if(empty()){
                clear();                        //cleaqr is gonna call destroy


                for(int i = 0; _top > _bot; ++i){
                    _a.deallocate(*(_top+i), ARRSIZE);
                }
            }

            assert(valid());}

        // ----------
        // operator =
        // ----------

        /**
         * <your documentation>
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
                //stuff?
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


            static value_type dummy;
            return dummy;}

        /**
         * <your documentation>
         */
        const_reference operator [] (size_type index) const {
            return const_cast<my_deque*>(this)->operator[](index);}

        // --
        // at
        // --

        /**
         * <your documentation>
         */
        reference at (size_type index) {
            // <your code>
            // dummy is just to be able to compile the skeleton, remove it
            static value_type dummy;
            return dummy;}

        /**
         * <your documentation>
         */
        const_reference at (size_type index) const {
            return const_cast<my_deque*>(this)->at(index);}

        // ----
        // back
        // ----

        /**
         * <your documentation>
         */
        reference back () {

            return *(_inner_end-1);}

        /**
         * <your documentation>
         */
        const_reference back () const {
            return const_cast<my_deque*>(this)->back();}

        // -----
        // begin
        // -----

        /**
         * <your documentation>
         */
        iterator begin () {
            // <your code>
            return iterator(/* <your arguments> */);}

        /**
         * <your documentation>
         */
        const_iterator begin () const {
            // <your code>
            return const_iterator(/* <your arguments> */);}

        // -----
        // clear
        // -----

        /**
         * destrys all elements curretly constructed
         */
        void clear () {

            destroy(_a, _inner_begin, _inner_end);
            assert(valid());}

        // -----
        // empty
        // -----

        /**
         * <your documentation>
         */
        bool empty () const {
            return !size();}

        // ---
        // end
        // ---

        /**
         * <your documentation>
         */
        iterator end () {
            // <your code>
            return iterator(/* <your arguments> */);}

        /**
         * <your documentation>
         */
        const_iterator end () const {
            // <your code>
            return const_iterator(/* <your arguments> */);}

        // -----
        // erase
        // -----

        /**
         * <your documentation>
         */
        iterator erase (iterator) {
            // <your code>
            assert(valid());
            return iterator();}

        // -----
        // front
        // -----

        /**
         * <your documentation>
         */
        reference front () {

            return *_inner_begin;}

        /**
         * <your documentation>
         */
        const_reference front () const {
            return const_cast<my_deque*>(this)->front();}

        // ------
        // insert
        // ------

        /**
         * <your documentation>
         */
        iterator insert (iterator, const_reference) {
            // <your code>
            assert(valid());
            return iterator();}

        // ---
        // pop
        // ---

        /**
         * <your documentation>
         */
        void pop_back () {
            // <your code>
            assert(valid());}

        /**
         * <your documentation>
         */
        void pop_front () {
            // <your code>
            assert(valid());}

        // ----
        // push
        // ----

        /**
         * <your documentation>
         */
        void push_back (const_reference) {
            // <your code>
            assert(valid());}

        /**
         * <your documentation>
         */
        void push_front (const_reference) {
            // <your code>
            assert(valid());}

        // ------
        // resize
        // ------

        /**
         * <your documentation>
         */
        void resize (size_type s, const_reference v = value_type()) {
            // <your code>
            assert(valid());}

        // ----
        // size
        // ----

        /**
         * <your documentation>
         */
        size_type size () const {
            // <your code>
            return _size;}

        // ----
        // swap
        // ----

        /**
         * <your documentation>
         */
        void swap (my_deque&) {
            // <your code>
            assert(valid());}};

#endif // Deque_h