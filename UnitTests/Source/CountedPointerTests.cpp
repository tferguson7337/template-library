#include "CountedPointer.hpp"

#include "CountedPointerTests.h"

#include "MemoryManagementHelper.hpp"

std::list<std::function<UnitTestResult(void)>> TTLTests::CountedPointer::BuildTestList( )
{
    static const std::list<std::function<UnitTestResult(void)>> testList =
    {
        // Constructor Tests
        DefaultConstructor_Single,
        DefaultConstructor_Array,
        NullConstructor_Single,
        NullConstructor_Array,
        RawConstructor_Single,
        RawConstructor_Array,
        CopyConstructor_Single,
        CopyConstructor_Array,
        MoveConstructor_Single,
        MoveConstructor_Array,

        // Bool and Relational Operator Tests
        BoolOperator_Single,
        BoolOperator_Array,
        EquivalenceOperator_Single,
        EquivalenceOperator_Array,
        NonEquivalenceOperator_Single,
        NonEquivalenceOperator_Array,
        LessThanOperator_Single,
        LessThanOperator_Array,
        GreaterThanOperator_Single,
        GreaterThanOperator_Array,
        LessThanOrEqualOperator_Single,
        LessThanOrEqualOperator_Array,
        GreaterThanOrEqualOperator_Single,
        GreaterThanOrEqualOperator_Array,

        // Assignment Operator Overload Tests
        AssignmentOperatorRaw_Single,
        AssignmentOperatorRaw_Array,
        AssignmentOperatorNull_Single,
        AssignmentOperatorNull_Array,
        AssignmentOperatorCopy_Single,
        AssignmentOperatorCopy_Array,
        AssignmentOperatorMove_Single,
        AssignmentOperatorMove_Array,
        AssignmentOperatorSelf_Single,
        AssignmentOperatorSelf_Array,

        // Public Method Tests
        Release_Single,
        Release_Array,
        SetNull_Single,
        SetNull_Array,
        SetRaw_Single,
        SetRaw_Array,
        SetCopy_Single,
        SetCopy_Array,
        SetMove_Single,
        SetMove_Array,
        SetSelf_Single,
        SetSelf_Array
    };

    return testList;
}

// Constructor Tests
UnitTestResult TTLTests::CountedPointer::DefaultConstructor_Single( )
{
    TTL::CountedPointer<size_t> ptr;

    SUTL_TEST_ASSERT(ptr.Get( ) == nullptr);
    SUTL_TEST_ASSERT(ptr.Count( ) == 0);

    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::CountedPointer::DefaultConstructor_Array( )
{
    TTL::CountedPointer<size_t[ ]> arrPtr;

    SUTL_TEST_ASSERT(arrPtr.Get( ) == nullptr);
    SUTL_TEST_ASSERT(arrPtr.Count( ) == 0);

    SUTL_TEST_SUCCESS( );
}


UnitTestResult TTLTests::CountedPointer::NullConstructor_Single( )
{
    TTL::CountedPointer<size_t> ptr(nullptr);

    SUTL_TEST_ASSERT(ptr.Get( ) == nullptr);
    SUTL_TEST_ASSERT(ptr.Count( ) == 0);

    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::CountedPointer::NullConstructor_Array( )
{
    TTL::CountedPointer<size_t[ ]> arrPtr(nullptr);

    SUTL_TEST_ASSERT(arrPtr.Get( ) == nullptr);
    SUTL_TEST_ASSERT(arrPtr.Count( ) == 0);

    SUTL_TEST_SUCCESS( );
}


UnitTestResult TTLTests::CountedPointer::RawConstructor_Single( )
{
    const size_t VAL = 1 << 10;
    size_t* p = nullptr;
    TTL::CountedPointer<size_t>* pPtr = nullptr;

    try
    {
        p = new size_t(VAL);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_SETUP_ASSERT(*p == VAL);

    try
    {
        pPtr = new TTL::CountedPointer<size_t>(p);
    }
    catch ( const std::exception& e )
    {
        SUTL_TEST_EXCEPTION(e.what( ));
    }

    SUTL_TEST_ASSERT(pPtr->Get( ) != nullptr);
    SUTL_TEST_ASSERT(pPtr->Count( ) == 1);

    SUTL_TEST_ASSERT(pPtr->Get( ) == p);
    SUTL_TEST_ASSERT(*(pPtr->Get( )) == *p);
    SUTL_TEST_ASSERT(*(pPtr->Get( )) == VAL);

    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::CountedPointer::RawConstructor_Array( )
{
    const size_t ARR_SIZE = 10;
    size_t* arr = nullptr;
    TTL::CountedPointer<size_t[ ]>* pArr = nullptr;

    try
    {
        arr = new size_t[ARR_SIZE];

        for ( size_t i = 0; i < ARR_SIZE; i++ )
        {
            arr[i] = i;
        }
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    try
    {
        pArr = new TTL::CountedPointer<size_t[ ]>(arr);
    }
    catch ( const std::exception& e )
    {
        SUTL_TEST_EXCEPTION(e.what( ));
    }

    SUTL_TEST_ASSERT(pArr->Get( ) != nullptr);
    SUTL_TEST_ASSERT(pArr->Count( ) == 1);

    SUTL_TEST_ASSERT(pArr->Get( ) == arr);
    for ( size_t i = 0; i < ARR_SIZE; i++ )
    {
        SUTL_TEST_ASSERT(pArr->Get( )[i] == arr[i]);
        SUTL_TEST_ASSERT(pArr->Get( )[i] == i);
    }

    SUTL_TEST_SUCCESS( );
}


UnitTestResult TTLTests::CountedPointer::CopyConstructor_Single( )
{
    const size_t VAL = 1 << 10;
    TTL::CountedPointer<size_t> ptr;

    try
    {
        ptr.Set(new size_t(VAL));
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_SETUP_ASSERT(ptr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(ptr.Count( ) == 1);
    SUTL_SETUP_ASSERT(*(ptr.Get( )) == VAL);

    TTL::CountedPointer<size_t> copyPtr(ptr);

    SUTL_TEST_ASSERT(copyPtr.Get( ) != nullptr);
    SUTL_TEST_ASSERT(copyPtr.Get( ) == ptr.Get( ));
    SUTL_TEST_ASSERT(*copyPtr.Get( ) == *ptr.Get( ));
    SUTL_TEST_ASSERT(copyPtr.Count( ) == 2);
    SUTL_TEST_ASSERT(copyPtr.Count( ) == ptr.Count( ));

    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::CountedPointer::CopyConstructor_Array( )
{
    const size_t ARR_SIZE = 10;
    TTL::CountedPointer<size_t[ ]> arrPtr;

    try
    {
        arrPtr.Set(new size_t[ARR_SIZE]);
        for ( size_t i = 0; i < ARR_SIZE; i++ )
        {
            arrPtr.Get( )[i] = i;
        }
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_SETUP_ASSERT(arrPtr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(arrPtr.Count( ) == 1);
    for ( size_t i = 0; i < ARR_SIZE; i++ )
    {
        SUTL_SETUP_ASSERT(arrPtr.Get( )[i] == i);
    }

    TTL::CountedPointer<size_t[ ]> copyPtr(arrPtr);

    SUTL_TEST_ASSERT(copyPtr.Get( ) != nullptr);
    SUTL_TEST_ASSERT(copyPtr.Get( ) == arrPtr.Get( ));
    for ( size_t i = 0; i < ARR_SIZE; i++ )
    {
        SUTL_TEST_ASSERT(copyPtr.Get( )[i] == arrPtr.Get( )[i]);
    }

    SUTL_TEST_ASSERT(copyPtr.Count( ) == 2);
    SUTL_TEST_ASSERT(copyPtr.Count( ) == arrPtr.Count( ));

    SUTL_TEST_SUCCESS( );
}


UnitTestResult TTLTests::CountedPointer::MoveConstructor_Single( )
{
    const size_t VAL = 1 << 10;
    const size_t* p = nullptr;
    TTL::CountedPointer<size_t> ptr;

    try
    {
        ptr.Set(new size_t(VAL));
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_SETUP_ASSERT(ptr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(ptr.Count( ) == 1);
    SUTL_SETUP_ASSERT(*(ptr.Get( )) == VAL);

    p = ptr.Get( );
    TTL::CountedPointer<size_t> movePtr(std::move(ptr));

    SUTL_TEST_ASSERT(movePtr.Get( ) != nullptr);
    SUTL_TEST_ASSERT(ptr.Get( ) == nullptr);
    SUTL_TEST_ASSERT(ptr.Count( ) == 0);
    SUTL_TEST_ASSERT(movePtr.Get( ) == p);
    SUTL_TEST_ASSERT(*(movePtr.Get( )) == *p);
    SUTL_TEST_ASSERT(*(movePtr.Get( )) == VAL);
    SUTL_TEST_ASSERT(movePtr.Count( ) == 1);

    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::CountedPointer::MoveConstructor_Array( )
{
    const size_t ARR_SIZE = 10;
    const size_t* p = nullptr;
    TTL::CountedPointer<size_t[ ]> arr;

    try
    {
        arr.Set(new size_t[ARR_SIZE]);
        for ( size_t i = 0; i < ARR_SIZE; i++ )
        {
            arr.Get( )[i] = i;
        }
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_SETUP_ASSERT(arr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(arr.Count( ) == 1);
    for ( size_t i = 0; i < ARR_SIZE; i++ )
    {
        SUTL_SETUP_ASSERT(arr.Get( )[i] == i);
    }

    p = arr.Get( );
    TTL::CountedPointer<size_t[ ]> movePtr(std::move(arr));

    SUTL_TEST_ASSERT(movePtr.Get( ) != nullptr);
    SUTL_TEST_ASSERT(arr.Get( ) == nullptr);
    SUTL_TEST_ASSERT(arr.Count( ) == 0);
    SUTL_TEST_ASSERT(movePtr.Get( ) == p);
    for ( size_t i = 0; i < ARR_SIZE; i++ )
    {
        SUTL_TEST_ASSERT(movePtr.Get( )[i] == p[i]);
        SUTL_TEST_ASSERT(movePtr.Get( )[i] == i);
    }

    SUTL_TEST_ASSERT(movePtr.Count( ) == 1);

    SUTL_TEST_SUCCESS( );
}



// Bool and Relational Operator Tests
UnitTestResult TTLTests::CountedPointer::BoolOperator_Single( )
{
    TTL::CountedPointer<size_t> ptr;

    SUTL_TEST_ASSERT(!ptr);

    try
    {
        ptr.Set(new size_t(0));
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_TEST_ASSERT(ptr);

    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::CountedPointer::BoolOperator_Array( )
{
    const size_t ARR_SIZE = 10;
    TTL::CountedPointer<size_t> ptr;

    SUTL_TEST_ASSERT(!ptr);

    try
    {
        ptr.Set(new size_t[ARR_SIZE]);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_TEST_ASSERT(ptr);

    SUTL_TEST_SUCCESS( );
}


UnitTestResult TTLTests::CountedPointer::EquivalenceOperator_Single( )
{
    const size_t* p = nullptr;
    TTL::CountedPointer<size_t> emptyPtr;
    TTL::CountedPointer<size_t> ptr;
    TTL::CountedPointer<size_t>* pCopy = nullptr;
    TTL::CountedPointer<size_t> otherPtr;

    SUTL_TEST_ASSERT(emptyPtr == nullptr);
    SUTL_TEST_ASSERT(emptyPtr == ptr);
    SUTL_TEST_ASSERT(emptyPtr == otherPtr);

    SUTL_TEST_ASSERT(emptyPtr == emptyPtr);
    SUTL_TEST_ASSERT(ptr == ptr);
    SUTL_TEST_ASSERT(otherPtr == otherPtr);

    try
    {
        ptr.Set(new size_t(0));
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    p = ptr.Get( );
    SUTL_TEST_ASSERT(ptr == p);
    SUTL_TEST_ASSERT(ptr == ptr);
    SUTL_TEST_ASSERT((ptr == nullptr) == false);
    SUTL_TEST_ASSERT((emptyPtr == ptr) == false);
    SUTL_TEST_ASSERT((ptr == otherPtr) == false);

    try
    {
        pCopy = new TTL::CountedPointer<size_t>(ptr);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_TEST_ASSERT(ptr == *pCopy);
    SUTL_TEST_ASSERT(*pCopy == p);
    SUTL_TEST_ASSERT(*pCopy == *pCopy);
    SUTL_TEST_ASSERT((emptyPtr == *pCopy) == false);
    SUTL_TEST_ASSERT((otherPtr == *pCopy) == false);

    try
    {
        otherPtr.Set(new size_t(0));
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_TEST_ASSERT((otherPtr == nullptr) == false);
    SUTL_TEST_ASSERT((otherPtr == emptyPtr) == false);
    SUTL_TEST_ASSERT(otherPtr == otherPtr);
    SUTL_TEST_ASSERT((otherPtr == ptr) == false);
    SUTL_TEST_ASSERT((otherPtr == *pCopy) == false);

    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::CountedPointer::EquivalenceOperator_Array( )
{
    const size_t* p = nullptr;
    const size_t ARR_SIZE = 10;
    TTL::CountedPointer<size_t[ ]> emptyPtr;
    TTL::CountedPointer<size_t[ ]> arr;
    TTL::CountedPointer<size_t[ ]>* pCopy = nullptr;
    TTL::CountedPointer<size_t[ ]> otherArr;

    SUTL_TEST_ASSERT(emptyPtr == nullptr);
    SUTL_TEST_ASSERT(emptyPtr == arr);
    SUTL_TEST_ASSERT(emptyPtr == otherArr);

    SUTL_TEST_ASSERT(emptyPtr == emptyPtr);
    SUTL_TEST_ASSERT(arr == arr);
    SUTL_TEST_ASSERT(otherArr == otherArr);

    try
    {
        arr.Set(new size_t[ARR_SIZE]);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    p = arr.Get( );
    SUTL_TEST_ASSERT(arr == p);
    SUTL_TEST_ASSERT(arr == arr);
    SUTL_TEST_ASSERT((arr == nullptr) == false);
    SUTL_TEST_ASSERT((emptyPtr == arr) == false);
    SUTL_TEST_ASSERT((arr == otherArr) == false);

    try
    {
        pCopy = new TTL::CountedPointer<size_t[ ]>(arr);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_TEST_ASSERT(arr == *pCopy);
    SUTL_TEST_ASSERT(p == *pCopy);
    SUTL_TEST_ASSERT(*pCopy == *pCopy);
    SUTL_TEST_ASSERT((*pCopy == nullptr) == false);
    SUTL_TEST_ASSERT((emptyPtr == *pCopy) == false);
    SUTL_TEST_ASSERT((otherArr == *pCopy) == false);

    try
    {
        otherArr.Set(new size_t[ARR_SIZE]);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_TEST_ASSERT((otherArr == nullptr) == false);
    SUTL_TEST_ASSERT((otherArr == emptyPtr) == false);
    SUTL_TEST_ASSERT(otherArr == otherArr);
    SUTL_TEST_ASSERT((otherArr == arr) == false);
    SUTL_TEST_ASSERT((otherArr == *pCopy) == false);

    SUTL_TEST_SUCCESS( );
}


UnitTestResult TTLTests::CountedPointer::NonEquivalenceOperator_Single( )
{
    const size_t* p = nullptr;
    TTL::CountedPointer<size_t> emptyPtr;
    TTL::CountedPointer<size_t> ptr;
    TTL::CountedPointer<size_t>* pCopy = nullptr;
    TTL::CountedPointer<size_t> otherPtr;

    SUTL_TEST_ASSERT((emptyPtr != nullptr) == false);
    SUTL_TEST_ASSERT((emptyPtr != ptr) == false);
    SUTL_TEST_ASSERT((emptyPtr != otherPtr) == false);

    SUTL_TEST_ASSERT((emptyPtr != emptyPtr) == false);
    SUTL_TEST_ASSERT((ptr != ptr) == false);
    SUTL_TEST_ASSERT((otherPtr != otherPtr) == false);

    try
    {
        ptr.Set(new size_t(0));
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    p = ptr.Get( );
    SUTL_TEST_ASSERT(ptr != nullptr);
    SUTL_TEST_ASSERT((ptr != ptr) == false);
    SUTL_TEST_ASSERT((ptr != p) == false);
    SUTL_TEST_ASSERT(emptyPtr != ptr);
    SUTL_TEST_ASSERT(ptr != otherPtr);

    try
    {
        pCopy = new TTL::CountedPointer<size_t>(ptr);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_TEST_ASSERT(*pCopy != nullptr);
    SUTL_TEST_ASSERT((*pCopy != *pCopy) == false);
    SUTL_TEST_ASSERT((ptr != *pCopy) == false);
    SUTL_TEST_ASSERT((*pCopy != p) == false);
    SUTL_TEST_ASSERT(emptyPtr != *pCopy);
    SUTL_TEST_ASSERT(*pCopy != otherPtr);

    try
    {
        otherPtr.Set(new size_t(0));
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_TEST_ASSERT(otherPtr != nullptr);
    SUTL_TEST_ASSERT(otherPtr != emptyPtr);
    SUTL_TEST_ASSERT((otherPtr != otherPtr) == false);
    SUTL_TEST_ASSERT(otherPtr != p);
    SUTL_TEST_ASSERT(otherPtr != ptr);
    SUTL_TEST_ASSERT(otherPtr != *pCopy);

    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::CountedPointer::NonEquivalenceOperator_Array( )
{
    const size_t ARR_SIZE = 10;
    const size_t* p = nullptr;
    TTL::CountedPointer<size_t[ ]> emptyPtr;
    TTL::CountedPointer<size_t[ ]> arr;
    TTL::CountedPointer<size_t[ ]>* pCopy = nullptr;
    TTL::CountedPointer<size_t[ ]> otherArr;

    SUTL_TEST_ASSERT((emptyPtr != nullptr) == false);
    SUTL_TEST_ASSERT((emptyPtr != arr) == false);
    SUTL_TEST_ASSERT((emptyPtr != otherArr) == false);

    SUTL_TEST_ASSERT((emptyPtr != emptyPtr) == false);
    SUTL_TEST_ASSERT((arr != arr) == false);
    SUTL_TEST_ASSERT((otherArr != otherArr) == false);

    try
    {
        arr.Set(new size_t[ARR_SIZE]);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    p = arr.Get( );
    SUTL_TEST_ASSERT(arr != nullptr);
    SUTL_TEST_ASSERT((arr != arr) == false);
    SUTL_TEST_ASSERT((arr != p) == false);
    SUTL_TEST_ASSERT(emptyPtr != arr);
    SUTL_TEST_ASSERT(arr != otherArr);

    try
    {
        pCopy = new TTL::CountedPointer<size_t[ ]>(arr);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_TEST_ASSERT(*pCopy != nullptr);
    SUTL_TEST_ASSERT((*pCopy != *pCopy) == false);
    SUTL_TEST_ASSERT(*pCopy != emptyPtr);
    SUTL_TEST_ASSERT((*pCopy != arr) == false);
    SUTL_TEST_ASSERT((*pCopy != p) == false);
    SUTL_TEST_ASSERT(*pCopy != otherArr);

    try
    {
        otherArr.Set(new size_t[ARR_SIZE]);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_TEST_ASSERT(otherArr != nullptr);
    SUTL_TEST_ASSERT(otherArr != emptyPtr);
    SUTL_TEST_ASSERT((otherArr != otherArr) == false);
    SUTL_TEST_ASSERT(otherArr != p);
    SUTL_TEST_ASSERT(otherArr != arr);
    SUTL_TEST_ASSERT(otherArr != *pCopy);

    SUTL_TEST_SUCCESS( );
}


UnitTestResult TTLTests::CountedPointer::LessThanOperator_Single( )
{
    const size_t* p = nullptr;
    TTL::CountedPointer<size_t> emptyPtr;
    TTL::CountedPointer<size_t> ptr;
    TTL::CountedPointer<size_t>* pCopy = nullptr;
    TTL::CountedPointer<size_t> otherPtr;

    SUTL_TEST_ASSERT((emptyPtr < nullptr) == false);
    SUTL_TEST_ASSERT((emptyPtr < ptr) == false);
    SUTL_TEST_ASSERT((emptyPtr < otherPtr) == false);

    SUTL_TEST_ASSERT((emptyPtr < emptyPtr) == false);
    SUTL_TEST_ASSERT((ptr < ptr) == false);
    SUTL_TEST_ASSERT((otherPtr < otherPtr) == false);

    try
    {
        ptr.Set(new size_t(0));
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    p = ptr.Get( );
    SUTL_TEST_ASSERT(nullptr < ptr);
    SUTL_TEST_ASSERT(emptyPtr < ptr);
    SUTL_TEST_ASSERT((ptr < p) == false);
    SUTL_TEST_ASSERT((ptr < ptr) == false);
    SUTL_TEST_ASSERT(otherPtr < ptr);

    try
    {
        pCopy = new TTL::CountedPointer<size_t>(ptr);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_TEST_ASSERT(nullptr < *pCopy);
    SUTL_TEST_ASSERT(emptyPtr < *pCopy);
    SUTL_TEST_ASSERT((*pCopy < *pCopy) == false);
    SUTL_TEST_ASSERT((ptr < *pCopy) == false);
    SUTL_TEST_ASSERT((p < *pCopy) == false);
    SUTL_TEST_ASSERT(otherPtr < *pCopy);

    try
    {
        otherPtr.Set(new size_t(0));
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_TEST_ASSERT(nullptr < otherPtr);
    SUTL_TEST_ASSERT(emptyPtr < otherPtr);
    SUTL_TEST_ASSERT((otherPtr < otherPtr) == false);
    if ( ptr.Get( ) < otherPtr.Get( ) )
    {
        SUTL_TEST_ASSERT(ptr < otherPtr);
        SUTL_TEST_ASSERT(p < otherPtr);
    }
    else
    {
        SUTL_TEST_ASSERT(otherPtr < ptr);
        SUTL_TEST_ASSERT(otherPtr < p);
    }

    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::CountedPointer::LessThanOperator_Array( )
{
    const size_t ARR_SIZE = 10;
    const size_t* p = nullptr;
    TTL::CountedPointer<size_t[ ]> emptyPtr;
    TTL::CountedPointer<size_t[ ]> arr;
    TTL::CountedPointer<size_t[ ]>* pCopy = nullptr;
    TTL::CountedPointer<size_t[ ]> otherArr;

    SUTL_TEST_ASSERT((emptyPtr < nullptr) == false);
    SUTL_TEST_ASSERT((emptyPtr < arr) == false);
    SUTL_TEST_ASSERT((emptyPtr < otherArr) == false);

    SUTL_TEST_ASSERT((emptyPtr < emptyPtr) == false);
    SUTL_TEST_ASSERT((arr < arr) == false);
    SUTL_TEST_ASSERT((otherArr < otherArr) == false);

    try
    {
        arr.Set(new size_t[ARR_SIZE]);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    p = arr.Get( );
    SUTL_TEST_ASSERT(nullptr < arr);
    SUTL_TEST_ASSERT(emptyPtr < arr);
    SUTL_TEST_ASSERT((arr < p) == false);
    SUTL_TEST_ASSERT((arr < arr) == false);
    SUTL_TEST_ASSERT(otherArr < arr);

    try
    {
        pCopy = new TTL::CountedPointer<size_t[ ]>(arr);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_TEST_ASSERT(nullptr < *pCopy);
    SUTL_TEST_ASSERT(emptyPtr < *pCopy);
    SUTL_TEST_ASSERT((*pCopy < *pCopy) == false);
    SUTL_TEST_ASSERT((arr < *pCopy) == false);
    SUTL_TEST_ASSERT((p < *pCopy) == false);
    SUTL_TEST_ASSERT(otherArr < *pCopy);

    try
    {
        otherArr.Set(new size_t[ARR_SIZE]);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_TEST_ASSERT(nullptr < otherArr);
    SUTL_TEST_ASSERT(emptyPtr < otherArr);
    SUTL_TEST_ASSERT((otherArr < otherArr) == false);
    if ( arr.Get( ) < otherArr.Get( ) )
    {
        SUTL_TEST_ASSERT(arr < otherArr);
        SUTL_TEST_ASSERT(p < otherArr);
    }
    else
    {
        SUTL_TEST_ASSERT(otherArr < arr);
        SUTL_TEST_ASSERT(otherArr < p);
    }

    SUTL_TEST_SUCCESS( );
}


UnitTestResult TTLTests::CountedPointer::GreaterThanOperator_Single( )
{
    const size_t* p = nullptr;
    TTL::CountedPointer<size_t> emptyPtr;
    TTL::CountedPointer<size_t> ptr;
    TTL::CountedPointer<size_t>* pCopy = nullptr;
    TTL::CountedPointer<size_t> otherPtr;

    SUTL_TEST_ASSERT((emptyPtr > nullptr) == false);
    SUTL_TEST_ASSERT((emptyPtr > ptr) == false);
    SUTL_TEST_ASSERT((emptyPtr > otherPtr) == false);

    SUTL_TEST_ASSERT((emptyPtr > emptyPtr) == false);
    SUTL_TEST_ASSERT((ptr > ptr) == false);
    SUTL_TEST_ASSERT((otherPtr > otherPtr) == false);

    try
    {
        ptr.Set(new size_t(0));
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    p = ptr.Get( );
    SUTL_TEST_ASSERT(ptr > nullptr);
    SUTL_TEST_ASSERT(ptr > emptyPtr);
    SUTL_TEST_ASSERT((ptr > p) == false);
    SUTL_TEST_ASSERT((ptr > ptr) == false);
    SUTL_TEST_ASSERT(ptr > otherPtr);

    try
    {
        pCopy = new TTL::CountedPointer<size_t>(ptr);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_TEST_ASSERT(*pCopy > nullptr);
    SUTL_TEST_ASSERT(*pCopy > emptyPtr);
    SUTL_TEST_ASSERT((*pCopy > *pCopy) == false);
    SUTL_TEST_ASSERT((ptr > *pCopy) == false);
    SUTL_TEST_ASSERT((p > *pCopy) == false);
    SUTL_TEST_ASSERT(*pCopy > otherPtr);

    try
    {
        otherPtr.Set(new size_t(0));
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_TEST_ASSERT(otherPtr > nullptr);
    SUTL_TEST_ASSERT(otherPtr > emptyPtr);
    SUTL_TEST_ASSERT((otherPtr > otherPtr) == false);
    if ( otherPtr.Get( ) > ptr.Get( ) )
    {
        SUTL_TEST_ASSERT(otherPtr > ptr);
        SUTL_TEST_ASSERT(otherPtr > p);
    }
    else
    {
        SUTL_TEST_ASSERT(ptr > otherPtr);
        SUTL_TEST_ASSERT(p > otherPtr);
    }

    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::CountedPointer::GreaterThanOperator_Array( )
{
    const size_t ARR_SIZE = 10;
    const size_t* p = nullptr;
    TTL::CountedPointer<size_t[ ]> emptyPtr;
    TTL::CountedPointer<size_t[ ]> arr;
    TTL::CountedPointer<size_t[ ]>* pCopy = nullptr;
    TTL::CountedPointer<size_t[ ]> otherArr;

    SUTL_TEST_ASSERT((emptyPtr > nullptr) == false);
    SUTL_TEST_ASSERT((emptyPtr > arr) == false);
    SUTL_TEST_ASSERT((emptyPtr > otherArr) == false);

    SUTL_TEST_ASSERT((emptyPtr > emptyPtr) == false);
    SUTL_TEST_ASSERT((arr > arr) == false);
    SUTL_TEST_ASSERT((otherArr > otherArr) == false);

    try
    {
        arr.Set(new size_t[ARR_SIZE]);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    p = arr.Get( );
    SUTL_TEST_ASSERT(arr > nullptr);
    SUTL_TEST_ASSERT(arr > emptyPtr);
    SUTL_TEST_ASSERT((arr > p) == false);
    SUTL_TEST_ASSERT((arr > arr) == false);
    SUTL_TEST_ASSERT(arr > otherArr);

    try
    {
        pCopy = new TTL::CountedPointer<size_t[ ]>(arr);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_TEST_ASSERT(*pCopy > nullptr);
    SUTL_TEST_ASSERT(*pCopy > emptyPtr);
    SUTL_TEST_ASSERT((*pCopy > *pCopy) == false);
    SUTL_TEST_ASSERT((*pCopy > arr) == false);
    SUTL_TEST_ASSERT((*pCopy > p) == false);
    SUTL_TEST_ASSERT(*pCopy > otherArr);

    try
    {
        otherArr.Set(new size_t[ARR_SIZE]);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_TEST_ASSERT(otherArr > nullptr);
    SUTL_TEST_ASSERT(otherArr > emptyPtr);
    SUTL_TEST_ASSERT((otherArr > otherArr) == false);
    if ( otherArr.Get( ) > arr.Get( ) )
    {
        SUTL_TEST_ASSERT(otherArr > arr);
        SUTL_TEST_ASSERT(otherArr > p);
    }
    else
    {
        SUTL_TEST_ASSERT(arr > otherArr);
        SUTL_TEST_ASSERT(p > otherArr);
    }

    SUTL_TEST_SUCCESS( );
}


UnitTestResult TTLTests::CountedPointer::LessThanOrEqualOperator_Single( )
{
    const size_t* p = nullptr;
    TTL::CountedPointer<size_t> emptyPtr;
    TTL::CountedPointer<size_t> ptr;
    TTL::CountedPointer<size_t>* pCopy = nullptr;
    TTL::CountedPointer<size_t> otherPtr;

    SUTL_TEST_ASSERT(emptyPtr <= nullptr);
    SUTL_TEST_ASSERT(emptyPtr <= ptr);
    SUTL_TEST_ASSERT(emptyPtr <= otherPtr);

    SUTL_TEST_ASSERT(emptyPtr <= emptyPtr);
    SUTL_TEST_ASSERT(ptr <= ptr);
    SUTL_TEST_ASSERT(otherPtr <= otherPtr);

    try
    {
        ptr.Set(new size_t(0));
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    p = ptr.Get( );
    SUTL_TEST_ASSERT(nullptr <= ptr);
    SUTL_TEST_ASSERT(emptyPtr <= ptr);
    SUTL_TEST_ASSERT(ptr <= p);
    SUTL_TEST_ASSERT(ptr <= ptr);
    SUTL_TEST_ASSERT(otherPtr <= ptr);

    try
    {
        pCopy = new TTL::CountedPointer<size_t>(ptr);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_TEST_ASSERT(nullptr <= *pCopy);
    SUTL_TEST_ASSERT(emptyPtr <= *pCopy);
    SUTL_TEST_ASSERT(*pCopy <= *pCopy);
    SUTL_TEST_ASSERT(ptr <= *pCopy);
    SUTL_TEST_ASSERT(p <= *pCopy);
    SUTL_TEST_ASSERT(otherPtr <= *pCopy);

    try
    {
        otherPtr.Set(new size_t(0));
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_TEST_ASSERT(nullptr <= otherPtr);
    SUTL_TEST_ASSERT(emptyPtr <= otherPtr);
    SUTL_TEST_ASSERT(otherPtr <= otherPtr);
    if ( ptr.Get( ) <= otherPtr.Get( ) )
    {
        SUTL_TEST_ASSERT(ptr <= otherPtr);
        SUTL_TEST_ASSERT(p <= otherPtr);
    }
    else
    {
        SUTL_TEST_ASSERT(otherPtr <= ptr);
        SUTL_TEST_ASSERT(otherPtr <= p);
    }

    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::CountedPointer::LessThanOrEqualOperator_Array( )
{
    const size_t ARR_SIZE = 10;
    const size_t* p = nullptr;
    TTL::CountedPointer<size_t[ ]> emptyPtr;
    TTL::CountedPointer<size_t[ ]> arr;
    TTL::CountedPointer<size_t[ ]>* pCopy = nullptr;
    TTL::CountedPointer<size_t[ ]> otherArr;

    SUTL_TEST_ASSERT(emptyPtr <= nullptr);
    SUTL_TEST_ASSERT(emptyPtr <= arr);
    SUTL_TEST_ASSERT(emptyPtr <= otherArr);

    SUTL_TEST_ASSERT(emptyPtr <= emptyPtr);
    SUTL_TEST_ASSERT(arr <= arr);
    SUTL_TEST_ASSERT(otherArr <= otherArr);

    try
    {
        arr.Set(new size_t[ARR_SIZE]);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    p = arr.Get( );
    SUTL_TEST_ASSERT(nullptr <= arr);
    SUTL_TEST_ASSERT(emptyPtr <= arr);
    SUTL_TEST_ASSERT(arr <= p);
    SUTL_TEST_ASSERT(arr <= arr);
    SUTL_TEST_ASSERT(otherArr <= arr);

    try
    {
        pCopy = new TTL::CountedPointer<size_t[ ]>(arr);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_TEST_ASSERT(nullptr <= *pCopy);
    SUTL_TEST_ASSERT(emptyPtr <= *pCopy);
    SUTL_TEST_ASSERT(*pCopy <= *pCopy);
    SUTL_TEST_ASSERT(arr <= *pCopy);
    SUTL_TEST_ASSERT(p <= *pCopy);
    SUTL_TEST_ASSERT(otherArr <= *pCopy);

    try
    {
        otherArr.Set(new size_t[ARR_SIZE]);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_TEST_ASSERT(nullptr <= otherArr);
    SUTL_TEST_ASSERT(emptyPtr <= otherArr);
    SUTL_TEST_ASSERT(otherArr <= otherArr);
    if ( arr.Get( ) <= otherArr.Get( ) )
    {
        SUTL_TEST_ASSERT(arr <= otherArr);
        SUTL_TEST_ASSERT(p <= otherArr);
    }
    else
    {
        SUTL_TEST_ASSERT(otherArr <= arr);
        SUTL_TEST_ASSERT(otherArr <= p);
    }

    SUTL_TEST_SUCCESS( );
}


UnitTestResult TTLTests::CountedPointer::GreaterThanOrEqualOperator_Single( )
{
    const size_t* p = nullptr;
    TTL::CountedPointer<size_t> emptyPtr;
    TTL::CountedPointer<size_t> ptr;
    TTL::CountedPointer<size_t>* pCopy = nullptr;
    TTL::CountedPointer<size_t> otherPtr;

    SUTL_TEST_ASSERT(emptyPtr >= nullptr);
    SUTL_TEST_ASSERT(emptyPtr >= ptr);
    SUTL_TEST_ASSERT(emptyPtr >= otherPtr);

    SUTL_TEST_ASSERT(emptyPtr >= emptyPtr);
    SUTL_TEST_ASSERT(ptr >= ptr);
    SUTL_TEST_ASSERT(otherPtr >= otherPtr);

    try
    {
        ptr.Set(new size_t(0));
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    p = ptr.Get( );
    SUTL_TEST_ASSERT(ptr >= nullptr);
    SUTL_TEST_ASSERT(ptr >= emptyPtr);
    SUTL_TEST_ASSERT(ptr >= p);
    SUTL_TEST_ASSERT(ptr >= ptr);
    SUTL_TEST_ASSERT(ptr >= otherPtr);

    try
    {
        pCopy = new TTL::CountedPointer<size_t>(ptr);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_TEST_ASSERT(*pCopy >= nullptr);
    SUTL_TEST_ASSERT(*pCopy >= emptyPtr);
    SUTL_TEST_ASSERT(*pCopy >= *pCopy);
    SUTL_TEST_ASSERT(ptr >= *pCopy);
    SUTL_TEST_ASSERT(p >= *pCopy);
    SUTL_TEST_ASSERT(*pCopy >= otherPtr);

    try
    {
        otherPtr.Set(new size_t(0));
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_TEST_ASSERT(otherPtr >= nullptr);
    SUTL_TEST_ASSERT(otherPtr >= emptyPtr);
    SUTL_TEST_ASSERT(otherPtr >= otherPtr);
    if ( otherPtr.Get( ) >= ptr.Get( ) )
    {
        SUTL_TEST_ASSERT(otherPtr >= ptr);
        SUTL_TEST_ASSERT(otherPtr >= p);
    }
    else
    {
        SUTL_TEST_ASSERT(ptr >= otherPtr);
        SUTL_TEST_ASSERT(p >= otherPtr);
    }

    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::CountedPointer::GreaterThanOrEqualOperator_Array( )
{
    const size_t ARR_SIZE = 10;
    const size_t* p = nullptr;
    TTL::CountedPointer<size_t[ ]> emptyPtr;
    TTL::CountedPointer<size_t[ ]> arr;
    TTL::CountedPointer<size_t[ ]>* pCopy = nullptr;
    TTL::CountedPointer<size_t[ ]> otherArr;

    SUTL_TEST_ASSERT(emptyPtr >= nullptr);
    SUTL_TEST_ASSERT(emptyPtr >= arr);
    SUTL_TEST_ASSERT(emptyPtr >= otherArr);

    SUTL_TEST_ASSERT(emptyPtr >= emptyPtr);
    SUTL_TEST_ASSERT(arr >= arr);
    SUTL_TEST_ASSERT(otherArr >= otherArr);

    try
    {
        arr.Set(new size_t[ARR_SIZE]);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    p = arr.Get( );
    SUTL_TEST_ASSERT(arr >= nullptr);
    SUTL_TEST_ASSERT(arr >= emptyPtr);
    SUTL_TEST_ASSERT(arr >= p);
    SUTL_TEST_ASSERT(arr >= arr);
    SUTL_TEST_ASSERT(arr >= otherArr);

    try
    {
        pCopy = new TTL::CountedPointer<size_t[ ]>(arr);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_TEST_ASSERT(*pCopy >= nullptr);
    SUTL_TEST_ASSERT(*pCopy >= emptyPtr);
    SUTL_TEST_ASSERT(*pCopy >= *pCopy);
    SUTL_TEST_ASSERT(*pCopy >= arr);
    SUTL_TEST_ASSERT(*pCopy >= p);
    SUTL_TEST_ASSERT(*pCopy >= otherArr);

    try
    {
        otherArr.Set(new size_t[ARR_SIZE]);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_TEST_ASSERT(otherArr >= nullptr);
    SUTL_TEST_ASSERT(otherArr >= emptyPtr);
    SUTL_TEST_ASSERT(otherArr >= otherArr);
    if ( otherArr.Get( ) >= arr.Get( ) )
    {
        SUTL_TEST_ASSERT(otherArr >= arr);
        SUTL_TEST_ASSERT(otherArr >= p);
    }
    else
    {
        SUTL_TEST_ASSERT(arr >= otherArr);
        SUTL_TEST_ASSERT(p >= otherArr);
    }

    SUTL_TEST_SUCCESS( );
}



// Assignment Operator Overload Tests
UnitTestResult TTLTests::CountedPointer::AssignmentOperatorRaw_Single( )
{
    const size_t VAL = 1 << 10;
    size_t* p = nullptr;
    TTL::CountedPointer<size_t> ptr;

    try
    {
        p = new size_t(VAL);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_SETUP_ASSERT(*p == VAL);

    try
    {
        ptr = p;
    }
    catch ( const std::exception& e )
    {
        SUTL_TEST_EXCEPTION(e.what( ));
    }

    SUTL_TEST_ASSERT(ptr.Get( ) != nullptr);
    SUTL_TEST_ASSERT(ptr.Get( ) == p);
    SUTL_TEST_ASSERT(ptr.Count( ) == 1);
    SUTL_TEST_ASSERT(*(ptr.Get( )) == VAL);

    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::CountedPointer::AssignmentOperatorRaw_Array( )
{
    const size_t ARR_SIZE = 10;
    size_t* p = nullptr;
    TTL::CountedPointer<size_t[ ]> arr;

    try
    {
        p = new size_t[ARR_SIZE];
        for ( size_t i = 0; i < ARR_SIZE; i++ )
        {
            p[i] = i;
        }
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    for ( size_t i = 0; i < ARR_SIZE; i++ )
    {
        SUTL_SETUP_ASSERT(p[i] == i);
    }

    try
    {
        arr = p;
    }
    catch ( const std::exception& e )
    {
        SUTL_TEST_EXCEPTION(e.what( ));
    }

    SUTL_TEST_ASSERT(arr.Get( ) != nullptr);
    SUTL_TEST_ASSERT(arr.Get( ) == p);
    SUTL_TEST_ASSERT(arr.Count( ) == 1);
    for ( size_t i = 0; i < ARR_SIZE; i++ )
    {
        SUTL_TEST_ASSERT(arr.Get( )[i] == p[i]);
        SUTL_TEST_ASSERT(arr.Get( )[i] == i);
    }

    SUTL_TEST_SUCCESS( );
}


UnitTestResult TTLTests::CountedPointer::AssignmentOperatorNull_Single( )
{
    TTL::CountedPointer<size_t> ptr;

    try
    {
        ptr.Set(new size_t(0));
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_SETUP_ASSERT(ptr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(ptr.Count( ) == 1);

    ptr = nullptr;

    SUTL_TEST_ASSERT(ptr.Get( ) == nullptr);
    SUTL_TEST_ASSERT(ptr.Count( ) == 0);

    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::CountedPointer::AssignmentOperatorNull_Array( )
{
    const size_t ARR_SIZE = 10;
    TTL::CountedPointer<size_t> arr;

    try
    {
        arr.Set(new size_t[ARR_SIZE]);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_SETUP_ASSERT(arr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(arr.Count( ) == 1);

    arr = nullptr;

    SUTL_TEST_ASSERT(arr.Get( ) == nullptr);
    SUTL_TEST_ASSERT(arr.Count( ) == 0);

    SUTL_TEST_SUCCESS( );
}


UnitTestResult TTLTests::CountedPointer::AssignmentOperatorCopy_Single( )
{
    const size_t VAL = 1 << 10;
    TTL::CountedPointer<size_t> ptr;
    TTL::CountedPointer<size_t> copyPtr;

    bool threw = false;

    try
    {
        ptr.Set(new size_t(VAL));
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_SETUP_ASSERT(ptr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(*(ptr.Get( )) == VAL);
    SUTL_SETUP_ASSERT(ptr.Count( ) == 1);

    try
    {
        ptr = ptr;
    }
    catch ( const std::invalid_argument& )
    {
        threw = true;
    }

    SUTL_TEST_ASSERT(threw);
    SUTL_TEST_ASSERT(ptr.Get( ) != nullptr);
    SUTL_TEST_ASSERT(*(ptr.Get( )) == VAL);
    SUTL_TEST_ASSERT(ptr.Count( ) == 1);

    threw = false;
    try
    {
        copyPtr = ptr;
    }
    catch ( const std::invalid_argument& )
    {
        threw = true;
    }
    catch ( const std::exception& e )
    {
        SUTL_TEST_EXCEPTION(e.what( ));
    }

    SUTL_TEST_ASSERT(threw == false);

    SUTL_TEST_ASSERT(ptr.Get( ) != nullptr);
    SUTL_TEST_ASSERT(*(ptr.Get( )) == VAL);
    SUTL_TEST_ASSERT(copyPtr.Get( ) == ptr.Get( ));
    SUTL_TEST_ASSERT(*(copyPtr.Get( )) == *(ptr.Get( )));
    SUTL_TEST_ASSERT(ptr.Count( ) == 2);
    SUTL_TEST_ASSERT(copyPtr.Count( ) == ptr.Count( ));

    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::CountedPointer::AssignmentOperatorCopy_Array( )
{
    const size_t ARR_SIZE = 10;
    TTL::CountedPointer<size_t[ ]> arr;
    TTL::CountedPointer<size_t[ ]> copyArr;

    bool threw = false;

    try
    {
        arr.Set(new size_t[ARR_SIZE]);
        for ( size_t i = 0; i < ARR_SIZE; i++ )
        {
            arr.Get( )[i] = i;
        }
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_SETUP_ASSERT(arr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(arr.Count( ) == 1);
    for ( size_t i = 0; i < ARR_SIZE; i++ )
    {
        SUTL_SETUP_ASSERT(arr.Get( )[i] == i);
    }

    try
    {
        arr = arr;
    }
    catch ( const std::invalid_argument& )
    {
        threw = true;
    }

    SUTL_TEST_ASSERT(threw);
    SUTL_TEST_ASSERT(arr.Get( ) != nullptr);
    SUTL_TEST_ASSERT(arr.Count( ) == 1);
    for ( size_t i = 0; i < ARR_SIZE; i++ )
    {
        SUTL_TEST_ASSERT(arr.Get( )[i] == i);
    }

    threw = false;
    try
    {
        copyArr = arr;
    }
    catch ( const std::invalid_argument& )
    {
        threw = true;
    }
    catch ( const std::exception& e )
    {
        SUTL_TEST_EXCEPTION(e.what( ));
    }

    SUTL_TEST_ASSERT(threw == false);

    SUTL_TEST_ASSERT(arr.Get( ) != nullptr);
    SUTL_TEST_ASSERT(copyArr.Get( ) == arr.Get( ));
    for ( size_t i = 0; i < ARR_SIZE; i++ )
    {
        SUTL_TEST_ASSERT(copyArr.Get( )[i] == arr.Get( )[i]);
        SUTL_TEST_ASSERT(copyArr.Get( )[i] == i);
    }
    SUTL_TEST_ASSERT(arr.Count( ) == 2);
    SUTL_TEST_ASSERT(copyArr.Count( ) == arr.Count( ));

    SUTL_TEST_SUCCESS( );
}


UnitTestResult TTLTests::CountedPointer::AssignmentOperatorMove_Single( )
{
    const size_t VAL = 1 << 10;

    const size_t* p = nullptr;
    TTL::CountedPointer<size_t> ptr;
    TTL::CountedPointer<size_t> movePtr;

    bool threw = false;

    try
    {
        ptr.Set(new size_t(VAL));
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    p = ptr.Get( );
    SUTL_SETUP_ASSERT(ptr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(p == ptr.Get( ));
    SUTL_SETUP_ASSERT(*(ptr.Get( )) == VAL);
    SUTL_SETUP_ASSERT(ptr.Count( ) == 1);

    try
    {
        movePtr = std::move(ptr);
    }
    catch ( const std::invalid_argument& )
    {
        threw = true;
    }
    catch ( const std::exception& e )
    {
        SUTL_TEST_EXCEPTION(e.what( ));
    }

    SUTL_TEST_ASSERT(threw == false);

    SUTL_TEST_ASSERT(ptr.Get( ) == nullptr);
    SUTL_TEST_ASSERT(ptr.Count( ) == 0);

    SUTL_TEST_ASSERT(movePtr.Get( ) != nullptr);
    SUTL_TEST_ASSERT(movePtr.Get( ) == p);

    SUTL_TEST_ASSERT(*(movePtr.Get( )) == *p);
    SUTL_TEST_ASSERT(*(movePtr.Get( )) == VAL);

    SUTL_TEST_ASSERT(movePtr.Count( ) == 1);

    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::CountedPointer::AssignmentOperatorMove_Array( )
{
    const size_t ARR_SIZE = 10;

    const size_t* p = nullptr;
    TTL::CountedPointer<size_t> arr;
    TTL::CountedPointer<size_t> moveArr;

    bool threw = false;

    try
    {
        arr.Set(new size_t[ARR_SIZE]);
        for ( size_t i = 0; i < ARR_SIZE; i++ )
        {
            arr.Get( )[i] = i;
        }
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    p = arr.Get( );
    SUTL_SETUP_ASSERT(arr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(p == arr.Get( ));
    SUTL_SETUP_ASSERT(arr.Count( ) == 1);
    for ( size_t i = 0; i < ARR_SIZE; i++ )
    {
        SUTL_SETUP_ASSERT(arr.Get( )[i] == i);
    }

    try
    {
        moveArr = std::move(arr);
    }
    catch ( const std::invalid_argument& )
    {
        threw = true;
    }
    catch ( const std::exception& e )
    {
        SUTL_TEST_EXCEPTION(e.what( ));
    }

    SUTL_TEST_ASSERT(threw == false);

    SUTL_TEST_ASSERT(arr.Get( ) == nullptr);
    SUTL_TEST_ASSERT(arr.Count( ) == 0);

    SUTL_TEST_ASSERT(moveArr.Get( ) != nullptr);
    SUTL_TEST_ASSERT(moveArr.Get( ) == p);

    for ( size_t i = 0; i < ARR_SIZE; i++ )
    {
        SUTL_TEST_ASSERT(moveArr.Get( )[i] == p[i]);
        SUTL_TEST_ASSERT(moveArr.Get( )[i] == i);
    }

    SUTL_TEST_ASSERT(moveArr.Count( ) == 1);

    SUTL_TEST_SUCCESS( );
}


UnitTestResult TTLTests::CountedPointer::AssignmentOperatorSelf_Single( )
{
    const size_t VAL = 1 << 10;
    bool threw = false;
    TTL::CountedPointer<size_t> ptr;

    try
    {
        ptr = ptr;
    }
    catch ( const std::invalid_argument& )
    {
        threw = true;
    }

    SUTL_TEST_ASSERT(threw);

    threw = false;
    try
    {
        ptr = std::move(ptr);
    }
    catch ( const std::invalid_argument& )
    {
        threw = true;
    }

    SUTL_TEST_ASSERT(threw);

    try
    {
        ptr.Set(new size_t(VAL));
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_SETUP_ASSERT(ptr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(*(ptr.Get( )) == VAL);
    SUTL_SETUP_ASSERT(ptr.Count( ) == 1);

    threw = false;
    try
    {
        ptr = ptr;
    }
    catch ( const std::invalid_argument& )
    {
        threw = true;
    }

    SUTL_TEST_ASSERT(threw);
    SUTL_TEST_ASSERT(ptr.Get( ) != nullptr);
    SUTL_TEST_ASSERT(*(ptr.Get( )) == VAL);
    SUTL_TEST_ASSERT(ptr.Count( ) == 1);

    threw = false;
    try
    {
        ptr = std::move(ptr);
    }
    catch ( const std::invalid_argument& )
    {
        threw = true;
    }

    SUTL_TEST_ASSERT(threw);
    SUTL_TEST_ASSERT(ptr.Get( ) != nullptr);
    SUTL_TEST_ASSERT(*(ptr.Get( )) == VAL);
    SUTL_TEST_ASSERT(ptr.Count( ) == 1);

    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::CountedPointer::AssignmentOperatorSelf_Array( )
{
    const size_t ARR_SIZE = 10;
    bool threw = false;
    TTL::CountedPointer<size_t[ ]> arr;

    try
    {
        arr = arr;
    }
    catch ( const std::invalid_argument& )
    {
        threw = true;
    }

    SUTL_TEST_ASSERT(threw);

    threw = false;
    try
    {
        arr = std::move(arr);
    }
    catch ( const std::invalid_argument& )
    {
        threw = true;
    }

    SUTL_TEST_ASSERT(threw);

    try
    {
        arr.Set(new size_t[ARR_SIZE]);
        for ( size_t i = 0; i < ARR_SIZE; i++ )
        {
            arr.Get( )[i] = i;
        }
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_SETUP_ASSERT(arr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(arr.Count( ) == 1);
    for ( size_t i = 0; i < ARR_SIZE; i++ )
    {
        SUTL_SETUP_ASSERT(arr.Get( )[i] == i);
    }

    threw = false;
    try
    {
        arr = arr;
    }
    catch ( const std::invalid_argument& )
    {
        threw = true;
    }

    SUTL_TEST_ASSERT(threw);
    SUTL_TEST_ASSERT(arr.Get( ) != nullptr);
    SUTL_TEST_ASSERT(arr.Count( ) == 1);
    for ( size_t i = 0; i < ARR_SIZE; i++ )
    {
        SUTL_TEST_ASSERT(arr.Get( )[i] == i);
    }

    threw = false;
    try
    {
        arr = std::move(arr);
    }
    catch ( const std::invalid_argument& )
    {
        threw = true;
    }

    SUTL_TEST_ASSERT(threw);
    SUTL_TEST_ASSERT(arr.Get( ) != nullptr);
    SUTL_TEST_ASSERT(arr.Count( ) == 1);
    for ( size_t i = 0; i < ARR_SIZE; i++ )
    {
        SUTL_TEST_ASSERT(arr.Get( )[i] == i);
    }

    SUTL_TEST_SUCCESS( );
}



// Public Method Tests
UnitTestResult TTLTests::CountedPointer::Release_Single( )
{
    bool threw = false;
    TTL::CountedPointer<MemoryManagementHelper> ptr;
    TTL::CountedPointer<MemoryManagementHelper> copyPtr;

    SUTL_SETUP_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 0);

    try
    {
        ptr.Set(new MemoryManagementHelper);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_SETUP_ASSERT(ptr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 0);
    SUTL_SETUP_ASSERT(ptr.Count( ) == 1);

    copyPtr.Set(ptr);

    SUTL_SETUP_ASSERT(ptr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(copyPtr.Get( ) == ptr.Get( ));
    SUTL_SETUP_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 0);
    SUTL_SETUP_ASSERT(ptr.Count( ) == 2);
    SUTL_SETUP_ASSERT(copyPtr.Count( ) == ptr.Count( ));

    copyPtr.Release( );

    SUTL_TEST_ASSERT(ptr.Get( ) != nullptr);
    SUTL_TEST_ASSERT(copyPtr.Get( ) == nullptr);
    try
    {
        *copyPtr;
    }
    catch ( const std::logic_error& )
    {
        threw = true;
    }

    SUTL_TEST_ASSERT(threw == true);
    SUTL_TEST_ASSERT(ptr.Count( ) == 1);
    SUTL_TEST_ASSERT(copyPtr.Count( ) == 0);
    SUTL_TEST_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 0);

    ptr.Release( );

    SUTL_TEST_ASSERT(ptr.Get( ) == nullptr);
    threw = false;
    try
    {
        *ptr;
    }
    catch ( const std::logic_error& )
    {
        threw = true;
    }

    SUTL_TEST_ASSERT(threw == true);
    SUTL_TEST_ASSERT(ptr.Count( ) == 0);
    SUTL_TEST_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 1);

    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::CountedPointer::Release_Array( )
{
    const size_t ARR_SIZE = 10;
    bool threw = false;
    TTL::CountedPointer<MemoryManagementHelper[ ]> arrPtr;
    TTL::CountedPointer<MemoryManagementHelper[ ]> copyPtr;

    SUTL_SETUP_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 0);

    try
    {
        arrPtr.Set(new MemoryManagementHelper[ARR_SIZE]);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_SETUP_ASSERT(arrPtr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 0);
    SUTL_SETUP_ASSERT(arrPtr.Count( ) == 1);

    copyPtr.Set(arrPtr);

    SUTL_SETUP_ASSERT(arrPtr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(copyPtr.Get( ) == arrPtr.Get( ));
    SUTL_SETUP_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 0);
    SUTL_SETUP_ASSERT(arrPtr.Count( ) == 2);
    SUTL_SETUP_ASSERT(copyPtr.Count( ) == arrPtr.Count( ));

    copyPtr.Release( );

    SUTL_TEST_ASSERT(arrPtr.Get( ) != nullptr);
    SUTL_TEST_ASSERT(copyPtr.Get( ) == nullptr);
    try
    {
        *copyPtr;
    }
    catch ( const std::logic_error& )
    {
        threw = true;
    }

    SUTL_TEST_ASSERT(threw == true);
    SUTL_TEST_ASSERT(arrPtr.Count( ) == 1);
    SUTL_TEST_ASSERT(copyPtr.Count( ) == 0);
    SUTL_TEST_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 0);

    arrPtr.Release( );

    SUTL_TEST_ASSERT(arrPtr.Get( ) == nullptr);
    threw = false;
    try
    {
        *arrPtr;
    }
    catch ( const std::logic_error& )
    {
        threw = true;
    }

    SUTL_TEST_ASSERT(threw == true);
    SUTL_TEST_ASSERT(arrPtr.Count( ) == 0);
    SUTL_TEST_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == ARR_SIZE);

    SUTL_TEST_SUCCESS( );
}


UnitTestResult TTLTests::CountedPointer::SetNull_Single( )
{
    bool threw = false;
    TTL::CountedPointer<MemoryManagementHelper> ptr;
    TTL::CountedPointer<MemoryManagementHelper> copyPtr;

    SUTL_SETUP_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 0);

    try
    {
        ptr.Set(new MemoryManagementHelper);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_SETUP_ASSERT(ptr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 0);
    SUTL_SETUP_ASSERT(ptr.Count( ) == 1);

    copyPtr.Set(ptr);

    SUTL_SETUP_ASSERT(ptr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(copyPtr.Get( ) == ptr.Get( ));
    SUTL_SETUP_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 0);
    SUTL_SETUP_ASSERT(ptr.Count( ) == 2);
    SUTL_SETUP_ASSERT(copyPtr.Count( ) == ptr.Count( ));

    copyPtr.Set(nullptr);

    SUTL_TEST_ASSERT(ptr.Get( ) != nullptr);
    SUTL_TEST_ASSERT(copyPtr.Get( ) == nullptr);
    try
    {
        *copyPtr;
    }
    catch ( const std::logic_error& )
    {
        threw = true;
    }

    SUTL_TEST_ASSERT(threw == true);
    SUTL_TEST_ASSERT(ptr.Count( ) == 1);
    SUTL_TEST_ASSERT(copyPtr.Count( ) == 0);
    SUTL_TEST_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 0);

    ptr.Set(nullptr);

    SUTL_TEST_ASSERT(ptr.Get( ) == nullptr);
    threw = false;
    try
    {
        *ptr;
    }
    catch ( const std::logic_error& )
    {
        threw = true;
    }

    SUTL_TEST_ASSERT(threw == true);
    SUTL_TEST_ASSERT(ptr.Count( ) == 0);
    SUTL_TEST_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 1);

    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::CountedPointer::SetNull_Array( )
{
    const size_t ARR_SIZE = 10;
    bool threw = false;
    TTL::CountedPointer<MemoryManagementHelper[ ]> arrPtr;
    TTL::CountedPointer<MemoryManagementHelper[ ]> copyPtr;

    SUTL_SETUP_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 0);

    try
    {
        arrPtr.Set(new MemoryManagementHelper[ARR_SIZE]);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_SETUP_ASSERT(arrPtr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 0);
    SUTL_SETUP_ASSERT(arrPtr.Count( ) == 1);

    copyPtr.Set(arrPtr);

    SUTL_SETUP_ASSERT(arrPtr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(copyPtr.Get( ) == arrPtr.Get( ));
    SUTL_SETUP_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 0);
    SUTL_SETUP_ASSERT(arrPtr.Count( ) == 2);
    SUTL_SETUP_ASSERT(copyPtr.Count( ) == arrPtr.Count( ));

    copyPtr.Set(nullptr);

    SUTL_TEST_ASSERT(arrPtr.Get( ) != nullptr);
    SUTL_TEST_ASSERT(copyPtr.Get( ) == nullptr);
    try
    {
        *copyPtr;
    }
    catch ( const std::logic_error& )
    {
        threw = true;
    }

    SUTL_TEST_ASSERT(threw == true);
    SUTL_TEST_ASSERT(arrPtr.Count( ) == 1);
    SUTL_TEST_ASSERT(copyPtr.Count( ) == 0);
    SUTL_TEST_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 0);

    arrPtr.Set(nullptr);

    SUTL_TEST_ASSERT(arrPtr.Get( ) == nullptr);
    threw = false;
    try
    {
        *arrPtr;
    }
    catch ( const std::logic_error& )
    {
        threw = true;
    }

    SUTL_TEST_ASSERT(threw == true);
    SUTL_TEST_ASSERT(arrPtr.Count( ) == 0);
    SUTL_TEST_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == ARR_SIZE);

    SUTL_TEST_SUCCESS( );
}


UnitTestResult TTLTests::CountedPointer::SetRaw_Single( )
{
    TTL::CountedPointer<MemoryManagementHelper> ptr;
    TTL::CountedPointer<MemoryManagementHelper> copyPtr;

    MemoryManagementHelper* pRaw = nullptr;

    try
    {
        pRaw = new MemoryManagementHelper;
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_SETUP_ASSERT(pRaw != nullptr);
    SUTL_SETUP_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 0);

    try
    {
        ptr.Set(new MemoryManagementHelper);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_SETUP_ASSERT(ptr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 0);
    SUTL_SETUP_ASSERT(ptr.Count( ) == 1);

    try
    {
        copyPtr.Set(ptr);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_SETUP_ASSERT(ptr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(copyPtr.Get( ) == ptr.Get( ));
    SUTL_SETUP_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 0);
    SUTL_SETUP_ASSERT(ptr.Count( ) == 2);
    SUTL_SETUP_ASSERT(copyPtr.Count( ) == ptr.Count( ));

    copyPtr.Set(pRaw);

    SUTL_TEST_ASSERT(ptr.Get( ) != nullptr);
    SUTL_TEST_ASSERT(copyPtr.Get( ) != ptr.Get( ));
    try
    {
        *copyPtr;
    }
    catch ( const std::logic_error& e )
    {
        SUTL_TEST_EXCEPTION(e.what( ));
    }

    SUTL_TEST_ASSERT(ptr.Count( ) == 1);
    SUTL_TEST_ASSERT(copyPtr.Count( ) == 1);
    SUTL_TEST_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 0);

    ptr.Release( );
    copyPtr.Release( );

    SUTL_TEST_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 2);

    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::CountedPointer::SetRaw_Array( )
{
    const size_t ARR_SIZE = 10;
    TTL::CountedPointer<MemoryManagementHelper[]> ptr;
    TTL::CountedPointer<MemoryManagementHelper[]> copyPtr;

    MemoryManagementHelper* pRaw = nullptr;

    try
    {
        pRaw = new MemoryManagementHelper[ARR_SIZE];
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_SETUP_ASSERT(pRaw != nullptr);
    SUTL_SETUP_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 0);

    try
    {
        ptr.Set(new MemoryManagementHelper[ARR_SIZE]);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_SETUP_ASSERT(ptr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 0);
    SUTL_SETUP_ASSERT(ptr.Count( ) == 1);

    try
    {
        copyPtr.Set(ptr);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_SETUP_ASSERT(ptr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(copyPtr.Get( ) == ptr.Get( ));
    SUTL_SETUP_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 0);
    SUTL_SETUP_ASSERT(ptr.Count( ) == 2);
    SUTL_SETUP_ASSERT(copyPtr.Count( ) == ptr.Count( ));

    copyPtr.Set(pRaw);

    SUTL_TEST_ASSERT(ptr.Get( ) != nullptr);
    SUTL_TEST_ASSERT(copyPtr.Get( ) != ptr.Get( ));
    try
    {
        *copyPtr;
    }
    catch ( const std::logic_error& e )
    {
        SUTL_TEST_EXCEPTION(e.what( ));
    }

    SUTL_TEST_ASSERT(ptr.Count( ) == 1);
    SUTL_TEST_ASSERT(copyPtr.Count( ) == 1);
    SUTL_TEST_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 0);

    ptr.Release( );
    copyPtr.Release( );

    SUTL_TEST_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == ARR_SIZE << 1);

    SUTL_TEST_SUCCESS( );
}


UnitTestResult TTLTests::CountedPointer::SetCopy_Single( )
{
    TTL::CountedPointer<MemoryManagementHelper> ptr;
    TTL::CountedPointer<MemoryManagementHelper> copyPtr;

    try
    {
        ptr.Set(new MemoryManagementHelper);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_SETUP_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 0);
    SUTL_SETUP_ASSERT(ptr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(ptr.Count( ) == 1);

    try
    {
        copyPtr.Set(ptr);
    }
    catch ( const std::exception& e )
    {
        SUTL_TEST_EXCEPTION(e.what( ));
    }

    SUTL_TEST_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 0);
    SUTL_TEST_ASSERT(copyPtr.Get( ) == ptr.Get( ));
    SUTL_TEST_ASSERT(ptr.Count( ) == 2);
    SUTL_TEST_ASSERT(ptr.Count( ) == copyPtr.Count( ));

    copyPtr.Release( );

    SUTL_TEST_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 0);
    SUTL_TEST_ASSERT(copyPtr.Get( ) == nullptr);
    SUTL_TEST_ASSERT(copyPtr.Count( ) == 0);
    SUTL_TEST_ASSERT(ptr.Get( ) != nullptr);
    SUTL_TEST_ASSERT(ptr.Count( ) == 1);

    ptr.Release( );

    SUTL_TEST_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 1);
    SUTL_TEST_ASSERT(ptr.Get( ) == nullptr);
    SUTL_TEST_ASSERT(ptr.Count( ) == 0);

    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::CountedPointer::SetCopy_Array( )
{
    const size_t ARR_SIZE = 10;
    TTL::CountedPointer<MemoryManagementHelper[ ]> ptr;
    TTL::CountedPointer<MemoryManagementHelper[ ]> copyPtr;

    try
    {
        ptr.Set(new MemoryManagementHelper[ARR_SIZE]);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_SETUP_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 0);
    SUTL_SETUP_ASSERT(ptr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(ptr.Count( ) == 1);

    try
    {
        copyPtr.Set(ptr);
    }
    catch ( const std::exception& e )
    {
        SUTL_TEST_EXCEPTION(e.what( ));
    }

    SUTL_TEST_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 0);
    SUTL_TEST_ASSERT(copyPtr.Get( ) == ptr.Get( ));
    SUTL_TEST_ASSERT(ptr.Count( ) == 2);
    SUTL_TEST_ASSERT(ptr.Count( ) == copyPtr.Count( ));

    copyPtr.Release( );

    SUTL_TEST_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 0);
    SUTL_TEST_ASSERT(copyPtr.Get( ) == nullptr);
    SUTL_TEST_ASSERT(copyPtr.Count( ) == 0);
    SUTL_TEST_ASSERT(ptr.Get( ) != nullptr);
    SUTL_TEST_ASSERT(ptr.Count( ) == 1);

    ptr.Release( );

    SUTL_TEST_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == ARR_SIZE);
    SUTL_TEST_ASSERT(ptr.Get( ) == nullptr);
    SUTL_TEST_ASSERT(ptr.Count( ) == 0);

    SUTL_TEST_SUCCESS( );
}


UnitTestResult TTLTests::CountedPointer::SetMove_Single( )
{
    TTL::CountedPointer<MemoryManagementHelper> ptr;
    TTL::CountedPointer<MemoryManagementHelper> movePtr;

    try
    {
        ptr.Set(new MemoryManagementHelper);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_SETUP_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 0);
    SUTL_SETUP_ASSERT(ptr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(ptr.Count( ) == 1);

    try
    {
        movePtr.Set(std::move(ptr));
    }
    catch ( const std::exception& e )
    {
        SUTL_TEST_EXCEPTION(e.what( ));
    }

    SUTL_TEST_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 0);
    SUTL_TEST_ASSERT(movePtr.Get( ) != nullptr);
    SUTL_TEST_ASSERT(movePtr.Count( ) == 1);
    SUTL_TEST_ASSERT(ptr.Get( ) == nullptr);
    SUTL_TEST_ASSERT(ptr.Count( ) == 0); 

    movePtr.Release( );

    SUTL_TEST_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 1);
    SUTL_TEST_ASSERT(movePtr.Get( ) == nullptr);
    SUTL_TEST_ASSERT(movePtr.Count( ) == 0);

    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::CountedPointer::SetMove_Array( )
{
    const size_t ARR_SIZE = 10;
    TTL::CountedPointer<MemoryManagementHelper[ ]> ptr;
    TTL::CountedPointer<MemoryManagementHelper[ ]> movePtr;

    try
    {
        ptr.Set(new MemoryManagementHelper[ARR_SIZE]);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_SETUP_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 0);
    SUTL_SETUP_ASSERT(ptr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(ptr.Count( ) == 1);

    try
    {
        movePtr.Set(std::move(ptr));
    }
    catch ( const std::exception& e )
    {
        SUTL_TEST_EXCEPTION(e.what( ));
    }

    SUTL_TEST_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 0);
    SUTL_TEST_ASSERT(movePtr.Get( ) != nullptr);
    SUTL_TEST_ASSERT(movePtr.Count( ) == 1);
    SUTL_TEST_ASSERT(ptr.Get( ) == nullptr);
    SUTL_TEST_ASSERT(ptr.Count( ) == 0);

    movePtr.Release( );

    SUTL_TEST_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == ARR_SIZE);
    SUTL_TEST_ASSERT(movePtr.Get( ) == nullptr);
    SUTL_TEST_ASSERT(movePtr.Count( ) == 0);

    SUTL_TEST_SUCCESS( );
}


UnitTestResult TTLTests::CountedPointer::SetSelf_Single( )
{
    bool threw = false;
    TTL::CountedPointer<size_t> ptr;

    try
    {
        ptr = new size_t;
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    try
    {
        ptr.Set(ptr);
    }
    catch ( const std::invalid_argument& )
    {
        threw = true;
    }

    SUTL_TEST_ASSERT(threw);

    threw = false;
    try
    {
        ptr.Set(std::move(ptr));
    }
    catch ( const std::invalid_argument& )
    {
        threw = true;
    }

    SUTL_TEST_ASSERT(threw);

    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::CountedPointer::SetSelf_Array( )
{
    bool threw = false;
    const size_t ARR_SIZE = 10;
    TTL::CountedPointer<size_t[ ]> ptr;

    try
    {
        ptr = new size_t[ARR_SIZE];
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    try
    {
        ptr.Set(ptr);
    }
    catch ( const std::invalid_argument& )
    {
        threw = true;
    }

    SUTL_TEST_ASSERT(threw);

    threw = false;
    try
    {
        ptr.Set(std::move(ptr));
    }
    catch ( const std::invalid_argument& )
    {
        threw = true;
    }

    SUTL_TEST_ASSERT(threw);

    SUTL_TEST_SUCCESS( );
}

