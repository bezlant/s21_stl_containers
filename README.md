# STL Containers

### Table of Contents

---

- [Introduction](#introduction)
- [Goals](#goals)
- [Build](#build)
- [Tests](#tests)

### Introduction

---

Implementation of C++ standard template library containers: _list, map, queue, set, stack and vector_. The library provides a full set of standard methods and attributes for element handling, container capacity checking and iteration.

##### Each type of containers provides the user with the following methods:

- standard constructors (default constructor, copy constructor, move constructor, constructor with initialization list)
- methods for accessing container elements (e.g. accessing an element with the index i)
- methods for checking if a container is full (e.g. the number of elements in the container, check if the container is empty)
- methods for changing the container (removing and adding new elements, cleaning the container)
- methods for dealing with the container iterator.

<details>
  <summary>Vector</summary>
<br />

_Vector Member type_

This table contains in-class type overrides (typical for the standard STL library) that are adopted to make class code easy to understand:

| Member type       | definition                                                                                                           |
| ----------------- | -------------------------------------------------------------------------------------------------------------------- |
| `value_type`      | `T` defines the type of the element (T is template parameter)                                                        |
| `reference`       | `T &` defines the type of the reference to an element                                                                |
| `const_reference` | `const T &` defines the type of the constant reference                                                               |
| `iterator`        | `T *` or internal class `VectorIterator<T>` defines the type for iterating through the container                     |
| `const_iterator`  | `const T *` or internal class `VectorConstIterator<T>` defines the constant type for iterating through the container |
| `size_type`       | `size_t` defines the type of the container size (standard type is size_t)                                            |

_Vector Member functions_

This table contains the main public methods for interacting with the class:

| Functions                                                | Definition                                                                                  |
| -------------------------------------------------------- | ------------------------------------------------------------------------------------------- |
| `vector()`                                               | default constructor, creates an empty vector                                                |
| `vector(size_type n)`                                    | parameterized constructor, creates the vector of size n                                     |
| `vector(std::initializer_list<value_type> const &items)` | initializer list constructor, creates a vector initizialized using std::initializer_list<T> |
| `vector(const vector &v)`                                | copy constructor                                                                            |
| `vector(vector &&v)`                                     | move constructor                                                                            |
| `~vector()`                                              | destructor                                                                                  |
| `operator=(vector &&v)`                                  | assignment operator overload for moving an object                                           |

_Vector Element access_

This table contains the public methods for accessing the elements of the class:

| Element access                         | Definition                                      |
| -------------------------------------- | ----------------------------------------------- |
| `reference at(size_type pos)`          | access a specified element with bounds checking |
| `reference operator[](size_type pos);` | access a specified element                      |
| `const_reference front()`              | access the first element                        |
| `const_reference back()`               | access the last element                         |
| `iterator data()`                      | direct access the underlying array              |

_Vector Iterators_

This table contains the public methods for iterating over class elements (access to iterators):

| Iterators          | Definition                           |
| ------------------ | ------------------------------------ |
| `iterator begin()` | returns an iterator to the beginning |
| `iterator end()`   | returns an iterator to the end       |

_Vector Capacity_

This table contains the public methods for accessing the container capacity information:

| Capacity                       | Definition                                                                                      |
| ------------------------------ | ----------------------------------------------------------------------------------------------- |
| `bool empty()`                 | checks whether the container is empty                                                           |
| `size_type size()`             | returns the number of elements                                                                  |
| `size_type max_size()`         | returns the maximum possible number of elements                                                 |
| `void reserve(size_type size)` | allocate storage of size elements and copies current array elements to a newely allocated array |
| `size_type capacity()`         | returns the number of elements that can be held in currently allocated storage                  |
| `void shrink_to_fit()`         | reduces memory usage by freeing unused memory                                                   |

_Vector Modifiers_

This table contains the public methods for modifying a container:

| Modifiers                                              | Definition                                                                                 |
| ------------------------------------------------------ | ------------------------------------------------------------------------------------------ |
| `void clear()`                                         | clears the contents                                                                        |
| `iterator insert(iterator pos, const_reference value)` | inserts elements into concrete pos and returns the iterator that points to the new element |
| `void erase(iterator pos)`                             | erases an element at pos                                                                   |
| `void push_back(const_reference value)`                | adds an element to the end                                                                 |
| `void pop_back()`                                      | removes the last element                                                                   |
| `void swap(vector& other)`                             | swaps the contents                                                                         |

</details>

<details>
  <summary>Array</summary>
<br />

_Array Member type_

This table contains in-class type overrides (typical for the standard STL library) that are adopted to make class code easy to understand:

| Member type       | definition                                                                |
| ----------------- | ------------------------------------------------------------------------- |
| `value_type`      | `T` defines the type of an element (T is template parameter)              |
| `reference`       | `T &` defines the type of the reference to an element                     |
| `const_reference` | `const T &` defines the type of the constant reference                    |
| `iterator`        | `T *` defines the type for iterating through the container                |
| `const_iterator`  | `const T *` defines the constant type for iterating through the container |
| `size_type`       | `size_t` defines the type of the container size (standard type is size_t) |

_Array Member functions_

This table contains the main public methods for interacting with the class:

| Functions                                               | Definition                                                                               |
| ------------------------------------------------------- | ---------------------------------------------------------------------------------------- |
| `array()`                                               | default constructor, creates an empty array                                              |
| `array(std::initializer_list<value_type> const &items)` | initializer list constructor, creates array initizialized using std::initializer_list<T> |
| `array(const array &a)`                                 | copy constructor                                                                         |
| `array(array &&a)`                                      | move constructor                                                                         |
| `~array()`                                              | destructor                                                                               |
| `operator=(array &&a)`                                  | assignment operator overload for moving an object                                        |

_Array Element access_

This table contains the public methods for accessing the elements of the class:

| Element access                        | Definition                                      |
| ------------------------------------- | ----------------------------------------------- |
| `reference at(size_type pos)`         | access a specified element with bounds checking |
| `reference operator[](size_type pos)` | access a specified element                      |
| `const_reference front()`             | access the first element                        |
| `const_reference back()`              | access the last element                         |
| `iterator data()`                     | direct access to the underlying array           |

_Array Iterators_

This table contains the public methods for iterating over class elements (access to iterators):

| Iterators          | Definition                           |
| ------------------ | ------------------------------------ |
| `iterator begin()` | returns an iterator to the beginning |
| `iterator end()`   | returns an iterator to the end       |

_Array Capacity_

This table contains the public methods for accessing the container capacity information:

| Capacity               | Definition                                      |
| ---------------------- | ----------------------------------------------- |
| `bool empty()`         | checks whether the container is empty           |
| `size_type size()`     | returns the number of elements                  |
| `size_type max_size()` | returns the maximum possible number of elements |

_Array Modifiers_

This table contains the public methods for modifying a container:

| Modifiers                           | Definition                                                |
| ----------------------------------- | --------------------------------------------------------- |
| `void swap(array& other)`           | swaps the contents                                        |
| `void fill(const_reference value);` | assigns the given value to all elements in the container. |

</details>

<details>
  <summary>List</summary>
<br />

_List Member type_

This table contains in-class type overrides (typical for the standard STL library) that are adopted to make class code easy to understand:

| Member type       | definition                                                                                          |
| ----------------- | --------------------------------------------------------------------------------------------------- |
| `value_type`      | `T` defines the type of an element (T is a template parameter)                                      |
| `reference`       | `T &` defines the type of the reference to an element                                               |
| `const_reference` | `const T &` defines the type of the constant reference                                              |
| `iterator`        | internal class `ListIterator<T>` defines the type for iterating through the container               |
| `const_iterator`  | internal class `ListConstIterator<T>` defines the constant type for iterating through the container |
| `size_type`       | `size_t` defines the type of the container size (standard type is size_t)                           |

_List Functions_

This table contains the main public methods for interacting with the class:

| Functions                                              | Definition                                                                                |
| ------------------------------------------------------ | ----------------------------------------------------------------------------------------- |
| `list()`                                               | default constructor, creates an empty list                                                |
| `list(size_type n)`                                    | parameterized constructor, creates the list of size n                                     |
| `list(std::initializer_list<value_type> const &items)` | initializer list constructor, creates a list initizialized using std::initializer_list<T> |
| `list(const list &l)`                                  | copy constructor                                                                          |
| `list(list &&l)`                                       | move constructor                                                                          |
| `~list()`                                              | destructor                                                                                |
| `operator=(list &&l)`                                  | assignment operator overload for moving an object                                         |

_List Element access_

This table contains the public methods for accessing the elements of the class:

| Element access            | Definition               |
| ------------------------- | ------------------------ |
| `const_reference front()` | access the first element |
| `const_reference back()`  | access the last element  |

_List Iterators_

This table contains the public methods for iterating over class elements (access to iterators):

| Iterators          | Definition                           |
| ------------------ | ------------------------------------ |
| `iterator begin()` | returns an iterator to the beginning |
| `iterator end()`   | returns an iterator to the end       |

_List Capacity_

This table contains the public methods for accessing the container capacity information:

| Capacity               | Definition                                      |
| ---------------------- | ----------------------------------------------- |
| `bool empty()`         | checks whether the container is empty           |
| `size_type size()`     | returns the number of elements                  |
| `size_type max_size()` | returns the maximum possible number of elements |

_List Modifiers_

This table contains the public methods for modifying a container:

| Modifiers                                              | Definition                                                                                 |
| ------------------------------------------------------ | ------------------------------------------------------------------------------------------ |
| `void clear()`                                         | clears the contents                                                                        |
| `iterator insert(iterator pos, const_reference value)` | inserts elements into concrete pos and returns the iterator that points to the new element |
| `void erase(iterator pos)`                             | erases an element at pos                                                                   |
| `void push_back(const_reference value)`                | adds an element to the end                                                                 |
| `void pop_back()`                                      | removes the last element                                                                   |
| `void push_front(const_reference value)`               | adds an element to the head                                                                |
| `void pop_front()`                                     | removes the first element                                                                  |
| `void swap(list& other)`                               | swaps the contents                                                                         |
| `void merge(list& other)`                              | merges two sorted lists                                                                    |
| `void splice(const_iterator pos, list& other)`         | transfers elements from list other starting from pos                                       |
| `void reverse()`                                       | reverses the order of the elements                                                         |
| `void unique()`                                        | removes consecutive duplicate elements                                                     |
| `void sort()`                                          | sorts the elements                                                                         |

</details>

<details>
  <summary>Map</summary>
<br />

_Map Member type_

This table contains in-class type overrides (typical for the standard STL library) that are adopted to make class code easy to understand:

| Member type       | Definition                                                                                                                                                                         |
| ----------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `key_type`        | `Key` the first template parameter (Key)                                                                                                                                           |
| `mapped_type`     | `T` the second template parameter (T)                                                                                                                                              |
| `value_type`      | `std::pair<const key_type,mapped_type>` Key-value pair                                                                                                                             |
| `reference`       | `value_type &` defines the type of the reference to an element                                                                                                                     |
| `const_reference` | `const value_type &` defines the type of the constant reference                                                                                                                    |
| `iterator`        | internal class `MapIterator<K, T>` or `BinaryTree::iterator` as internal iterator of tree subclass; defines the type for iterating through the container                           |
| `const_iterator`  | internal class `MapConstIterator<K, T>` or `BinaryTree::const_iterator` as internal const iterator of tree subclass; defines the constant type for iterating through the container |
| `size_type`       | `size_t` defines the type of the container size (standard type is size_t)                                                                                                          |

_Map Member functions_

This table contains the main public methods for interacting with the class:

| Member functions                                      | Definition                                                                                 |
| ----------------------------------------------------- | ------------------------------------------------------------------------------------------ |
| `map()`                                               | default constructor, creates an empty map                                                  |
| `map(std::initializer_list<value_type> const &items)` | initializer list constructor, creates the map initizialized using std::initializer_list<T> |
| `map(const map &m)`                                   | copy constructor                                                                           |
| `map(map &&m)`                                        | move constructor                                                                           |
| `~map()`                                              | destructor                                                                                 |
| `operator=(map &&m)`                                  | assignment operator overload for moving an object                                          |

_Map Element access_

This table contains the public methods for accessing the elements of the class:

| Element access                  | Definition                                      |
| ------------------------------- | ----------------------------------------------- |
| `T& at(const Key& key)`         | access a specified element with bounds checking |
| `T& operator[](const Key& key)` | access or insert specified element              |

_Map Iterators_

This table contains the public methods for iterating over class elements (access to iterators):

| Iterators          | Definition                           |
| ------------------ | ------------------------------------ |
| `iterator begin()` | returns an iterator to the beginning |
| `iterator end()`   | returns an iterator to the end       |

_Map Capacity_

This table contains the public methods for accessing the container capacity information:

| Capacity               | Definition                                      |
| ---------------------- | ----------------------------------------------- |
| `bool empty()`         | checks whether the container is empty           |
| `size_type size()`     | returns the number of elements                  |
| `size_type max_size()` | returns the maximum possible number of elements |

_Map Modifiers_

This table contains the public methods for modifying a container:

| Modifiers                                                                   | Definition                                                                                                                                 |
| --------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------ |
| `void clear()`                                                              | clears the contents                                                                                                                        |
| `std::pair<iterator, bool> insert(const value_type& value)`                 | inserts a node and returns an iterator to where the element is in the container and bool denoting whether the insertion took place         |
| `std::pair<iterator, bool> insert(const Key& key, const T& obj)`            | inserts a value by key and returns an iterator to where the element is in the container and bool denoting whether the insertion took place |
| `std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);` | inserts an element or assigns to the current element if the key already exists                                                             |
| `void erase(iterator pos)`                                                  | erases an element at pos                                                                                                                   |
| `void swap(map& other)`                                                     | swaps the contents                                                                                                                         |
| `void merge(map& other);`                                                   | splices nodes from another container                                                                                                       |

_Map Lookup_

This table contains the public methods for viewing the container:

| Lookup                          | Definition                                                                |
| ------------------------------- | ------------------------------------------------------------------------- |
| `bool contains(const Key& key)` | checks if there is an element with key equivalent to key in the container |

</details>

<details>
  <summary>Queue</summary>
<br />

_Queue Member type_

This table contains in-class type overrides (typical for the standard STL library) that are adopted to make class code easy to understand:

| Member type       | Definition                                                                |
| ----------------- | ------------------------------------------------------------------------- |
| `value_type`      | `T` the template parameter T                                              |
| `reference`       | `T &` defines the type of the reference to an element                     |
| `const_reference` | `const T &` defines the type of the constant reference                    |
| `size_type`       | `size_t` defines the type of the container size (standard type is size_t) |

_Queue Member functions_

This table contains the main public methods for interacting with the class:

| Functions                                               | Definition                                                                               |
| ------------------------------------------------------- | ---------------------------------------------------------------------------------------- |
| `queue()`                                               | default constructor, creates an empty queue                                              |
| `queue(std::initializer_list<value_type> const &items)` | initializer list constructor, creates queue initizialized using std::initializer_list<T> |
| `queue(const queue &q)`                                 | copy constructor                                                                         |
| `queue(queue &&q)`                                      | move constructor                                                                         |
| `~queue()`                                              | destructor                                                                               |
| `operator=(queue &&q)`                                  | assignment operator overload for moving an object                                        |

_Queue Element access_

This table contains the public methods for accessing the elements of the class:

| Element access            | Definition               |
| ------------------------- | ------------------------ |
| `const_reference front()` | access the first element |
| `const_reference back()`  | access the last element  |

_Queue Capacity_

This table contains the public methods for accessing the container capacity information:

| Capacity           | Definition                            |
| ------------------ | ------------------------------------- |
| `bool empty()`     | checks whether the container is empty |
| `size_type size()` | returns the number of elements        |

_Queue Modifiers_

This table contains the public methods for modifying a container:

| Modifiers                          | Definition                    |
| ---------------------------------- | ----------------------------- |
| `void push(const_reference value)` | inserts an element at the end |
| `void pop()`                       | removes the first element     |
| `void swap(queue& other)`          | swaps the contents            |

</details>

<details>
  <summary>Set</summary>
<br />

_Set Member type_

This table contains in-class type overrides (typical for the standard STL library) that are adopted to make class code easy to understand:

| Member type       | Definition                                                                                                                                                                          |
| ----------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `key_type`        | `Key` the first template parameter (Key)                                                                                                                                            |
| `value_type`      | `Key` value type (the value itself is a key)                                                                                                                                        |
| `reference`       | `value_type &` defines the type of the reference to an element                                                                                                                      |
| `const_reference` | `const value_type &` defines the type of the constant reference                                                                                                                     |
| `iterator`        | internal class `SetIterator<T>` or `BinaryTree::iterator` as the internal iterator of tree subclass; defines the type for iterating through the container                           |
| `const_iterator`  | internal class `SetConstIterator<T>` or `BinaryTree::const_iterator` as the internal const iterator of tree subclass; defines the constant type for iterating through the container |
| `size_type`       | `size_t` defines the type of the container size (standard type is size_t)                                                                                                           |

_Set Member functions_

This table contains the main public methods for interacting with the class:

| Member functions                                      | Definition                                                                                 |
| ----------------------------------------------------- | ------------------------------------------------------------------------------------------ |
| `set()`                                               | default constructor, creates an empty set                                                  |
| `set(std::initializer_list<value_type> const &items)` | initializer list constructor, creates the set initizialized using std::initializer_list<T> |
| `set(const set &s)`                                   | copy constructor                                                                           |
| `set(set &&s)`                                        | move constructor                                                                           |
| `~set()`                                              | destructor                                                                                 |
| `operator=(set &&s)`                                  | assignment operator overload for moving an object                                          |

_Set Iterators_

This table contains the public methods for iterating over class elements (access to iterators):

| Iterators          | Definition                           |
| ------------------ | ------------------------------------ |
| `iterator begin()` | returns an iterator to the beginning |
| `iterator end()`   | returns an iterator to the end       |

_Set Capacity_

This table contains the public methods for accessing the container capacity information:

| Capacity               | Definition                                      |
| ---------------------- | ----------------------------------------------- |
| `bool empty()`         | checks whether the container is empty           |
| `size_type size()`     | returns the number of elements                  |
| `size_type max_size()` | returns the maximum possible number of elements |

_Set Modifiers_

This table contains the public methods for modifying a container:

| Modifiers                                                   | Definition                                                                                                                         |
| ----------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------- |
| `void clear()`                                              | clears the contents                                                                                                                |
| `std::pair<iterator, bool> insert(const value_type& value)` | inserts a node and returns an iterator to where the element is in the container and bool denoting whether the insertion took place |
| `void erase(iterator pos)`                                  | erases an element at pos                                                                                                           |
| `void swap(set& other)`                                     | swaps the contents                                                                                                                 |
| `void merge(set& other);`                                   | splices nodes from another container                                                                                               |

_Set Lookup_

This table contains the public methods for viewing the container:

| Lookup                          | Definition                                                      |
| ------------------------------- | --------------------------------------------------------------- |
| `iterator find(const Key& key)` | finds an element with a specific key                            |
| `bool contains(const Key& key)` | checks if the container contains an element with a specific key |

</details>

<details>
  <summary>Stack</summary>
<br />

_Stack Member type_

This table contains in-class type overrides (typical for the standard STL library) that are adopted to make class code easy to understand:

| Member type       | Definition                                                                |
| ----------------- | ------------------------------------------------------------------------- |
| `value_type`      | `T` the template parameter T                                              |
| `reference`       | `T &` defines the type of the reference to an element                     |
| `const_reference` | `const T &` defines the type of the constant reference                    |
| `size_type`       | `size_t` defines the type of the container size (standard type is size_t) |

_Stack Member functions_

This table contains the main public methods for interacting with the class:

| Functions                                               | Definition                                                                               |
| ------------------------------------------------------- | ---------------------------------------------------------------------------------------- |
| `stack()`                                               | default constructor, creates an empty stack                                              |
| `stack(std::initializer_list<value_type> const &items)` | initializer list constructor, creates stack initizialized using std::initializer_list<T> |
| `stack(const stack &s)`                                 | copy constructor                                                                         |
| `stack(stack &&s)`                                      | move constructor                                                                         |
| `~stack()`                                              | destructor                                                                               |
| `operator=(stack &&s)`                                  | assignment operator overload for moving an object                                        |

_Stack Element access_

This table contains the public methods for accessing the elements of the class:

| Element access          | Definition               |
| ----------------------- | ------------------------ |
| `const_reference top()` | accesses the top element |

_Stack Capacity_

This table contains the public methods for accessing the container capacity information:

| Capacity           | Definition                            |
| ------------------ | ------------------------------------- |
| `bool empty()`     | checks whether the container is empty |
| `size_type size()` | returns the number of elements        |

_Stack Modifiers_

This table contains the public methods for modifying a container:

| Modifiers                          | Definition                    |
| ---------------------------------- | ----------------------------- |
| `void push(const_reference value)` | inserts an element at the top |
| `void pop()`                       | removes the top element       |
| `void swap(stack& other)`          | swaps the contents            |

</details>

<details>
  <summary>Multiset</summary>
<br />

_Multiset Member type_

This table contains in-class type overrides (typical for the standard STL library) that are adopted to make class code easy to understand:

| Member type       | Definition                                                                                                                                                                           |
| ----------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| `key_type`        | `Key` the first template parameter (Key)                                                                                                                                             |
| `value_type`      | `Key` value type (the value itself is a key)                                                                                                                                         |
| `reference`       | `value_type &` defines the type of the reference to an element                                                                                                                       |
| `const_reference` | `const value_type &` defines the type of the constant reference                                                                                                                      |
| `iterator`        | internal class `MultisetIterator<T>` or `BinaryTree::iterator` as internal iterator of tree subclass; defines the type for iterating through the container                           |
| `const_iterator`  | internal class `MultisetConstIterator<T>` or `BinaryTree::const_iterator` as internal const iterator of tree subclass; defines the constant type for iterating through the container |
| `size_type`       | `size_t` defines the type of the container size (standard type is size_t)                                                                                                            |

_Multiset Member functions_

This table contains the main public methods for interacting with the class:

| Member functions                                           | Definition                                                                                 |
| ---------------------------------------------------------- | ------------------------------------------------------------------------------------------ |
| `multiset()`                                               | default constructor, creates an empty set                                                  |
| `multiset(std::initializer_list<value_type> const &items)` | initializer list constructor, creates the set initizialized using std::initializer_list<T> |
| `multiset(const multiset &ms)`                             | copy constructor                                                                           |
| `multiset(multiset &&ms)`                                  | move constructor                                                                           |
| `~multiset()`                                              | destructor                                                                                 |
| `operator=(multiset &&ms)`                                 | assignment operator overload for moving an object                                          |

_Multiset Iterators_

This table contains the public methods for iterating over class elements (access to iterators):

| Iterators          | Definition                           |
| ------------------ | ------------------------------------ |
| `iterator begin()` | returns an iterator to the beginning |
| `iterator end()`   | returns an iterator to the end       |

_Multiset Capacity_

This table contains the public methods for accessing the container capacity information:

| Capacity               | Definition                                      |
| ---------------------- | ----------------------------------------------- |
| `bool empty()`         | checks whether the container is empty           |
| `size_type size()`     | returns the number of elements                  |
| `size_type max_size()` | returns the maximum possible number of elements |

_Multiset Modifiers_

This table contains the public methods for modifying a container:

| Modifiers                                  | Definition                                                                      |
| ------------------------------------------ | ------------------------------------------------------------------------------- |
| `void clear()`                             | clears the contents                                                             |
| `iterator insert(const value_type& value)` | inserts a node and returns an iterator to where the element is in the container |
| `void erase(iterator pos)`                 | erases an element at pos                                                        |
| `void swap(multiset& other)`               | swaps the contents                                                              |
| `void merge(multiset& other)`              | splices nodes from another container                                            |

_Multiset Lookup_

This table contains the public methods for viewing the container:

| Lookup                                                     | Definition                                                           |
| ---------------------------------------------------------- | -------------------------------------------------------------------- |
| `size_type count(const Key& key)`                          | returns the number of elements matching a specific key               |
| `iterator find(const Key& key)`                            | finds element with a specific key                                    |
| `bool contains(const Key& key)`                            | checks if the container contains element with a specific key         |
| `std::pair<iterator,iterator> equal_range(const Key& key)` | returns range of elements matching a specific key                    |
| `iterator lower_bound(const Key& key)`                     | returns an iterator to the first element not less than the given key |
| `iterator upper_bound(const Key& key)`                     | returns an iterator to the first element greater than the given key  |

</details>

### Goals

---

- [x] Outline the project structure
- [x] Integrate CMake
- [x] Integrate Gtest
- [x] Array class
- [x] Vector class
- [x] List class
- [x] Queue class
- [x] Stack class
- [x] Map class
- [x] Set class
- [x] Multiset class

### Build

---

```
$ git clone https://github.com/bezlant/s21_stl_containers
$ cd s21_stl_containers
$ mkdir build && cd build
$ cmake ..
$ make
```

### Tests

---

Unit tests are implemented using [googletest](https://google.github.io/googletest/) & coverage report with [llvm-cov](https://llvm.org/docs/CommandGuide/llvm-cov.html)

### Credits

---

A huge amount of work was done by [Dmitriy (@hubertfu)](https://github.com/HubertFurr).
