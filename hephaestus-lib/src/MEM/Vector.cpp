/* 
 * File:   Vector.cpp
 * Author: chris
 * 
 * Created on February 3, 2014, 9:11 PM
 */

#include "Vector.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

namespace MEM {
Vector::Vector(size_t item_size) {
    assert(item_size);
    m_item_size = item_size;
    m_size = 0;
    m_capacity = 1;
    m_items = malloc(m_item_size * m_capacity);
    assert(m_items);
}

Vector::Vector(const Vector& orig) {
    m_item_size = orig.m_item_size;
    m_size = orig.m_size;
    m_capacity = orig.m_capacity;
    if (orig.m_items) {
        m_items = malloc(m_item_size * m_capacity);
        memcpy(m_items, orig.m_items, m_item_size * m_capacity);
    }
}

const Vector& Vector::operator=(const Vector& orig) {
    if (m_items) {
        free(m_items);
        m_items = 0;
        m_size = 0;
    }
    m_item_size = orig.m_item_size;
    m_size = orig.m_size;
    m_capacity = orig.m_capacity;
    if (orig.m_items) {
        m_items = malloc(m_item_size * m_capacity);
        memcpy(m_items, orig.m_items, m_item_size * m_capacity);
    }
}

Vector::~Vector() {
    if (m_items)
        free(m_items);
}


// ------------------------------------------------------------- vector_get ---
const void * Vector::get( size_t index )
{
    assert( m_size );
    assert( index  < m_size );

    return (char*)(m_items) + index * m_item_size;
}


// ----------------------------------------------------------- vector_front ---
const void * Vector::front()
{
    assert( m_size );
    return get( 0 );
}


// ------------------------------------------------------------ vector_back ---
const void * Vector::back()
{
    assert( m_size );
    return get( m_size-1 );
}


// -------------------------------------------------------- vector_contains ---
bool Vector::contains( const void *item, int (*cmp)(const void *, const void *) )
{
    size_t i;
    for( i=0; i<m_size; ++i )
    {
        if( (*cmp)(item, get(i) ) == 0 )
        {
            return true;
        }
    }
   return false;
}


// ----------------------------------------------------------- vector_empty ---
int Vector::empty(  )
{
    return m_size == 0;
}


// ------------------------------------------------------------ vector_size ---
size_t Vector::size(  )
{
    return m_size;
}


// --------------------------------------------------------- vector_reserve ---
void Vector::reserve( const size_t size )
{
    if( m_capacity < size)
    {
        m_items = realloc( m_items, size * m_item_size );
        m_capacity = size;
    }
}


// -------------------------------------------------------- vector_capacity ---
size_t Vector::capacity(  )
{
    return m_capacity;
}


// ---------------------------------------------------------- vector_shrink ---
void Vector::shrink()
{
    if( m_capacity > m_size )
    {
        m_items = realloc( m_items, m_size * m_item_size );
    }
    m_capacity = m_size;
}


// ----------------------------------------------------------- vector_clear ---
void Vector::clear()
{
    m_size = 0;
}


// ------------------------------------------------------------- vector_set ---
void
Vector::set( const size_t index, const void *item )
{
    assert( m_size );
    assert( index  < m_size );

    memcpy( (char *)(m_items) + index * m_item_size,
            item, m_item_size );
}


// ---------------------------------------------------------- vector_insert ---
void
Vector::insert( const size_t index, const void *item )
{
    assert( index <= m_size);
    if( m_capacity <= m_size )
    {
        reserve( 2 * m_capacity );
    }
    if( index < m_size )
    {
        memmove( (char *)(m_items) + (index + 1) * m_item_size,
                 (char *)(m_items) + (index + 0) * m_item_size,
                 (m_size - index)  * m_item_size);
    }
    m_size++;
    set( index, item );
}


// ----------------------------------------------------- vector_erase_range ---
void Vector::erase_range( const size_t first, const size_t last )
{
    assert( first < m_size );
    assert( last  < m_size+1 );
    assert( first < last );
    memmove( (char *)(m_items) + first * m_item_size,
             (char *)(m_items) + last  * m_item_size,
             (m_size - last)   * m_item_size);
    m_size -= (last-first);
}


// ----------------------------------------------------------- vector_erase ---
void
Vector::erase( 
              const size_t index )
{
    
    assert( index < m_size );

    erase_range(  index, index+1 );
}


// ------------------------------------------------------- vector_push_back ---
void
Vector::push_back( 
                  const void *item )
{
    insert( m_size, item );
}


// -------------------------------------------------------- vector_pop_back ---
void
Vector::pop_back()
{
    
    assert( m_size );

    m_size--;
}


// ---------------------------------------------------------- vector_resize ---
void
Vector::resize( 
               const size_t size )
{
    

    if( size > m_capacity)
    {
        reserve(  size );
        m_size = m_capacity;
    }
    else
    {
        m_size = size;
    }
}


// -------------------------------------------------- vector_push_back_data ---
void
Vector::push_back_data( 
                       const void * data,
                       const size_t count )
{
    
    assert( data );
    assert( count );

    if( m_capacity < (m_size+count) )
    {
        reserve( m_size+count);
    }
    memmove( (char *)(m_items) + m_size * m_item_size, data,
             count*m_item_size );
    m_size += count;
}


// ----------------------------------------------------- vector_insert_data ---
void
Vector::insert_data( 
                    const size_t index,
                    const void * data,
                    const size_t count )
{
    
    assert( index < m_size );
    assert( data );
    assert( count );

    if( m_capacity < (m_size+count) )
    {
        reserve( m_size+count);
    }
    memmove( (char *)(m_items) + (index + count ) * m_item_size,
             (char *)(m_items) + (index ) * m_item_size,
             count*m_item_size );
    memmove( (char *)(m_items) + index * m_item_size, data,
             count*m_item_size );
    m_size += count;
}


// ------------------------------------------------------------ vector_sort ---
void
Vector::sort( 
             int (*cmp)(const void *, const void *) )
{
    
    assert( m_size );

    qsort(m_items, m_size, m_item_size, cmp);
}

}
