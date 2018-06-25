#ifndef _UNMOVABLE_H
#define _UNMOVABLE_H

///
//
//  Class:      Unmovable
//  
//  Purpose:    Using inheritance, this will make a derived class unable to be moved
//              (unallowed move ctor/assignment)
//
///
class Unmovable
{
protected:
    Unmovable( )                            = default;
    Unmovable(const Unmovable&)             = default;
    ~Unmovable( )                           = default;

    Unmovable& operator=(const Unmovable&)  = default;

    // Move Ctor/Assignment Deleted
    Unmovable(Unmovable&&)                  = delete;
    Unmovable& operator=(Unmovable&&)       = delete;

};

#endif // _UNMOVABLE_H