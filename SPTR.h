#pragma once

#include <iostream>
#include <vector>

//UNIQUE
template <typename T>
class Unique
{
private:
    T* m_ptr;

private:
    Unique();
    Unique(const Unique& ptr);

public:
    Unique(T* ptr);
    ~Unique();
};

template <typename T>
Unique<T>::Unique(T* ptr) : m_ptr(ptr)
{ 
    /*std::cout << "Constructed." << std::endl;*/
}

template <typename T>
Unique<T>::~Unique()
{
    delete m_ptr;
    /*std::cout << "Destructed." << std::endl;*/
}

//SHARED
template <typename T>
class Shared
{
private:
    static std::vector<unsigned int> reference_count;
    static unsigned int current_reference_id;

    unsigned int reference_id;

private:
    T* m_ptr;

private:
    Shared();

public:
    T* getmptr() const;

public:
    Shared(T* ptr);
    Shared(const Shared& ptr);
    ~Shared();
};

template<typename T>
std::vector<unsigned int> Shared<T>::reference_count;

template <typename T>
unsigned int Shared<T>::current_reference_id = 0;

template <typename T>
T* Shared<T>::getmptr() const
{
    return this->m_ptr;
}

template <typename T>
Shared<T>::Shared(T* ptr) : m_ptr(ptr), reference_id(current_reference_id)
{
    reference_count.push_back(0);
    reference_count[reference_id]++;
    /*std::cout << "Constructed." << std::endl;*/
    current_reference_id++;
}

template <typename T>
Shared<T>::Shared(const Shared& ptr) : m_ptr(ptr.m_ptr), reference_id(ptr.reference_id)
{
    reference_count[reference_id]++;
    /*std::cout << "Constructed." << std::endl;*/
}

template <typename T>
Shared<T>::~Shared()
{
    reference_count[reference_id]--;

    if (!reference_count[reference_id])
    {
        delete m_ptr;
        /*std::cout << "All references destructed." << std::endl;*/
    }
    else {
        /*std::cout << "Reference destructed." << std::endl;*/
    }
}

//WEAK
template <typename T>
class Weak
{
private:
    T* m_ptr;

private:
    Weak();

public:
    Weak(const Shared<T>& ptr);
};

template <typename T>
Weak<T>::Weak(const Shared<T>& ptr)
{
    m_ptr = ptr.getmptr();
}

// ignore
//template <typename T>
//class SPTR
//{
//private:
//    T* m_ptr;
//
//private:
//    SPTR();
//};