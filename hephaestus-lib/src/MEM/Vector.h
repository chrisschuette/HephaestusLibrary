/* 
 * File:   Vector.h
 * Author: chris
 *
 * Created on February 3, 2014, 9:11 PM
 */

#ifndef VECTOR_H
#define	VECTOR_H

#include <stddef.h>

namespace MEM {
class Vector {
public:
    Vector( size_t item_size );
    Vector(const Vector& orig);
    const Vector& operator=(const Vector& orig);
    virtual ~Vector();
    
    size_t getItemSize() const { return m_item_size; }
    void * getItemsPointer() { return m_items; }


/**
 *  Returns a pointer to the item located at specified index.
 *
 *  @param  self  a vector structure
 *  @param  index the index of the item to be returned
 *  @return       pointer on the specified item
 */
  const void * get( size_t index );


/**
 *  Returns a pointer to the first item.
 *
 *  @param  self  a vector structure
 *  @return       pointer on the first item
 */
  const void * front();


/**
 *  Returns a pointer to the last item
 *
 *  @param  self  a vector structure
 *  @return pointer on the last item
 */
  const void * back();


/**
 *  Check if an item is contained within the vector.
 *
 *  @param  self  a vector structure
 *  @param  item  item to be searched in the vector
 *  @param  cmp   a pointer a comparison function
 *  @return       1 if item is contained within the vector, 0 otherwise
 */
  bool contains( const void *item, int (*cmp)(const void *, const void *) );


/**
 *  Checks whether the vector is empty.
 *
 *  @param  self  a vector structure
 *  @return       1 if the vector is empty, 0 otherwise
 */
  int empty();


/**
 *  Returns the number of items
 *
 *  @param  self  a vector structure
 *  @return       number of items
 */
  size_t size();


/**
 *  Reserve storage such that it can hold at last size items.
 *
 *  @param  self  a vector structure
 *  @param  size  the new storage capacity
 */
  void reserve( const size_t size );


/**
 *  Returns current storage capacity
 *
 *  @param  self  a vector structure
 *  @return       storage capacity
 */
  size_t capacity();


/**
 *  Decrease capacity to fit actual size.
 *
 *  @param  self  a vector structure
 */
  void shrink();


/**
 *  Removes all items.
 *
 *  @param  self  a vector structure
 */
  void clear();


/**
 *  Replace an item.
 *
 *  @param  self  a vector structure
 *  @param  index the index of the item to be replaced
 *  @param  item  the new item
 */
  void set( const size_t index,
              const void *item );


/**
 *  Erase an item.
 *
 *  @param  self  a vector structure
 *  @param  index the index of the item to be erased
 */
  void erase( const size_t index );


/**
 *  Erase a range of items.
 *
 *  @param  self  a vector structure
 *  @param  first the index of the first item to be erased
 *  @param  last  the index of the last item to be erased
 */
  void erase_range( const size_t first, const size_t last );


/**
 *  Appends given item to the end of the vector.
 *
 *  @param  self a vector structure
 *  @param  item the item to be inserted
 */
  void push_back( const void *item );


/**
 *  Removes the last item of the vector.
 *
 *  @param  self a vector structure
 */
  void pop_back();


/**
 *  Resizes the vector to contain size items
 *
 *  If the current size is less than size, additional items are appended and
 *  initialized with value. If the current size is greater than size, the
 *  vector is reduced to its first size elements.
 *
 *  @param  self a vector structure
 *  @param  size the new size
 */
  void resize( const size_t size );


/**
 *  Insert a single item at specified index.
 *
 *  @param  self  a vector structure
 *  @param  index location before which to insert item
 *  @param  item  the item to be inserted
 */
  void insert( const size_t index, const void *item );


/**
 *  Insert raw data at specified index.
 *
 *  @param  self  a vector structure
 *  @param  index location before which to insert item
 *  @param  data  a pointer to the items to be inserted
 *  @param  count the number of items to be inserted
 */
  void insert_data( const size_t index, const void * data, const size_t count );


/**
 *  Append raw data to the end of the vector.
 *
 *  @param  self  a vector structure
 *  @param  data  a pointer to the items to be inserted
 *  @param  count the number of items to be inserted
 */
  void push_back_data( const void * data, const size_t count );


/**
 *  Sort vector items according to cmp function.
 *
 *  @param  self  a vector structure
 *  @param  cmp   a pointer a comparison function
 */
  void sort( int (*cmp)(const void *, const void *) );
    
    
private:
     /** Pointer to dynamically allocated items. */
     void * m_items;

     /** Number of items that can be held in currently allocated storage. */
     size_t m_capacity;

     /** Number of items. */
     size_t m_size;

     /** Size (in bytes) of a single item. */
     size_t m_item_size;
};
}
#endif	/* VECTOR_H */

