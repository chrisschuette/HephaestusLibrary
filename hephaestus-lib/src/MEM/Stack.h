/* 
 * File:   stack.h
 * Author: chris
 *
 * Created on June 10, 2013, 9:50 PM
 */

#ifndef STACK_H
#define	STACK_H

#include <iostream>

namespace MEM {

    template <class T>
    class Stack {
    public:
        Stack(int iMaxSize) : m_iTop(0), m_iMaxSize(iMaxSize) {
            m_data = new T[iMaxSize];
        }
        ~Stack() {
            if(m_data)
                delete [] m_data;
        }
        void clear() {
            m_iTop = 0;
        }
        void push(T item) {
            if(m_iTop >= m_iMaxSize) {
                //fail
                std::cerr << "Stack full." << std::endl;
            }
            else {
                m_data[m_iTop] = item;
                m_iTop++;
            }
        }
        void pop() {
            if(m_iTop <= 0) {
                //fail
                std::cerr << "Stack already empty." << std::endl;
            } else {
                m_iTop--;
            }
        }
        
        int size() {
            return m_iTop;
        }
        T & top() {
            if(m_iTop <= 0) {
                //fail
                std::cerr << "Stack empty." << std::endl;

            } else {
                return m_data[m_iTop-1];
            }
        }
        const T & top() const {
             if(m_iTop <= 0) {
                //fail
                std::cerr << "Stack empty." << std::endl;

            } else {
                return m_data[m_iTop-1];
            }
        }
    private:
        T * m_data;
        int m_iTop;
        int m_iMaxSize;
    };
}

#endif	/* STACK_H */

