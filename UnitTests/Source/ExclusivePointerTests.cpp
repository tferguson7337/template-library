#include "ExclusivePointerTests.h"

#include <ExclusivePointer.hpp>


std::list<std::function<UnitTestResult(void)>> TTLTests::ExclusivePointer::BuildTestList( )
{
    static const std::list<std::function<UnitTestResult(void)>> testList =
    {
        // Constructor Tests
        DefaultConstructor,
        NullConstructor,
        RawConstructor,
        MoveConstructor,

        // Bool and Relational Operator Tests
        BoolOperator,
        EquivalenceOperator,
        NonEquivalenceOperator,
        LessThanOperator,
        GreaterThanOperator,
        LessThanOrEqualOperator,
        GreaterThanOrEqualOperator,

        // Assignment Operator Overload Tests
        AssignmentOperatorRaw,
        AssignmentOperatorNull,
        AssignmentOperatorMove,
        AssignmentOperatorSelf,

        // Public Method Tests
        Release,
        SetNull,
        SetRaw,
        SetMove,
        SetSelf
    };

    return testList;
}


/// Constructor Tests \\\

UnitTestResult TTLTests::ExclusivePointer::DefaultConstructor( )
{
    TTL::ExclusivePointer<int> numPtr;
    TTL::ExclusivePointer<int[ ]> arrPtr;

    // Ensure default constructor initializes with nullptr.
    SUTL_TEST_ASSERT(numPtr.Get( ) == nullptr);
    SUTL_TEST_ASSERT(arrPtr.Get( ) == nullptr);

    /// Test Pass!
    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::ExclusivePointer::NullConstructor( )
{
    TTL::ExclusivePointer<int> numPtr(nullptr);
    TTL::ExclusivePointer<int[ ]> arrPtr(nullptr);

    // Ensure nullptr_t constructor initializes with nullptr.
    SUTL_TEST_ASSERT(numPtr.Get( ) == nullptr);
    SUTL_TEST_ASSERT(arrPtr.Get( ) == nullptr);

    /// Test Pass!
    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::ExclusivePointer::RawConstructor( )
{
    int* n = nullptr;
    int* arr = nullptr;

    try
    {
        n = new int;
        arr = new int[16];
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    // Confirm Initial Test Conditions
    SUTL_SETUP_ASSERT(n != nullptr);
    SUTL_SETUP_ASSERT(arr != nullptr);

    TTL::ExclusivePointer<int> numPtr(n);
    TTL::ExclusivePointer<int[ ]> arrPtr(arr);

    // Ensure raw pointer constructor initialized with raw pointer values.
    SUTL_TEST_ASSERT(numPtr.Get( ) == n);
    SUTL_TEST_ASSERT(arrPtr.Get( ) == arr);

    /// Test Pass!
    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::ExclusivePointer::MoveConstructor( )
{
    int* n = nullptr;
    int* arr = nullptr;
    TTL::ExclusivePointer<int> numPtr;
    TTL::ExclusivePointer<int[ ]> arrPtr;

    try
    {
        numPtr.Set(new int);
        arrPtr.Set(new int[16]);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    n = numPtr.Get( );
    arr = arrPtr.Get( );

    // Confirm Initial Test Conditions
    SUTL_SETUP_ASSERT(numPtr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(arrPtr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(numPtr.Get( ) == n);
    SUTL_SETUP_ASSERT(arrPtr.Get( ) == arr);

    TTL::ExclusivePointer<int> moveNum(std::move(numPtr));
    TTL::ExclusivePointer<int[ ]> moveArr(std::move(arrPtr));

    // Ensure move constructor transferred resource ownership.
    SUTL_TEST_ASSERT(numPtr.Get( ) == nullptr);
    SUTL_TEST_ASSERT(arrPtr.Get( ) == nullptr);
    SUTL_TEST_ASSERT(moveNum.Get( ) == n);
    SUTL_TEST_ASSERT(moveArr.Get( ) == arr);

    /// Test Pass!
    SUTL_TEST_SUCCESS( );
}


/// Bool/Relational Operator Tests \\\

UnitTestResult TTLTests::ExclusivePointer::BoolOperator( )
{
    TTL::ExclusivePointer<int> numPtr(nullptr);
    TTL::ExclusivePointer<int[ ]> arrPtr(nullptr);

    // Confirm Initial Test Conditions
    SUTL_SETUP_ASSERT(numPtr.Get( ) == nullptr);
    SUTL_SETUP_ASSERT(arrPtr.Get( ) == nullptr);

    // Test operator bool() - nullptr
    SUTL_TEST_ASSERT(!numPtr);
    SUTL_TEST_ASSERT(!arrPtr);

    // Allocate and assign memory
    try
    {
        numPtr.Set(new int);
        arrPtr.Set(new int[16]);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    // Test operator bool() - not null
    SUTL_TEST_ASSERT(numPtr);
    SUTL_TEST_ASSERT(arrPtr);

    /// Test pass!
    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::ExclusivePointer::EquivalenceOperator( )
{
    int* n = nullptr;

    TTL::ExclusivePointer<int> numPtr;
    TTL::ExclusivePointer<int[ ]> arrPtr;

    // Confirm Initial Test Conditions
    SUTL_SETUP_ASSERT(n == nullptr);
    SUTL_SETUP_ASSERT(numPtr.Get( ) == nullptr);
    SUTL_SETUP_ASSERT(arrPtr.Get( ) == nullptr);

    // Test operator==(ExclusivePtr<T1>, ExclusivePtr<T2>)
    SUTL_TEST_ASSERT(numPtr == arrPtr);

    // Test operator==(ExclusivePtr<T>, const T* const)
    SUTL_TEST_ASSERT(numPtr == n);

    // Test operator==(ExclusivePtr<T[ ]>, const T* const)
    SUTL_TEST_ASSERT(arrPtr == n);

    // Test operator==(const T* const, ExclusivePtr<T>)
    SUTL_TEST_ASSERT(n == numPtr);

    // Test operator==(const T* const, ExclusivePtr<T[ ]>)
    SUTL_TEST_ASSERT(n == arrPtr);

    // Test operator==(ExclusivePtr<T>, std::nullptr_t)
    SUTL_TEST_ASSERT(numPtr == nullptr);

    // Test operator==(ExclusivePtr<T[ ]>, std::nullptr_t)
    SUTL_TEST_ASSERT(arrPtr == nullptr);

    // Test operator==(std::nullptr_t, ExclusivePtr<T>)
    SUTL_TEST_ASSERT(nullptr == numPtr);

    // Test operator==(std::nullptr_t, ExclusivePtr<T[ ]>)
    SUTL_TEST_ASSERT(nullptr == arrPtr);


    /// Test Pass!
    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::ExclusivePointer::NonEquivalenceOperator( )
{
    int* n = nullptr;

    TTL::ExclusivePointer<int> numPtr;
    TTL::ExclusivePointer<int[ ]> arrPtr;

    try
    {
        n = new int;
        numPtr = new int;
        arrPtr = new int[16];
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    // Confirm Initial Test Conditions
    SUTL_SETUP_ASSERT(n != nullptr);
    SUTL_SETUP_ASSERT(numPtr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(arrPtr.Get( ) != nullptr);

    // Test operator!=(ExclusivePtr<T1>, ExclusivePtr<T2>)
    SUTL_TEST_ASSERT(numPtr != arrPtr);

    // Test operator!=(ExclusivePtr<T>, const T* const)
    SUTL_TEST_ASSERT(numPtr != n);

    // Test operator!=(ExclusivePtr<T[ ]>, const T* const)
    SUTL_TEST_ASSERT(arrPtr != n);

    // Test operator!=(const T* const, ExclusivePtr<T>)
    SUTL_TEST_ASSERT(n != numPtr);

    // Test operator!=(const T* const, ExclusivePtr<T[ ]>)
    SUTL_TEST_ASSERT(n != arrPtr);

    // Test operator!=(ExclusivePtr<T>, std::nullptr_t)
    SUTL_TEST_ASSERT(numPtr != nullptr);

    // Test operator!=(ExclusivePtr<T[ ]>, std::nullptr_t)
    SUTL_TEST_ASSERT(arrPtr != nullptr);

    // Test operator!=(std::nullptr_t, ExclusivePtr<T>)
    SUTL_TEST_ASSERT(nullptr != numPtr);

    // Test operator!=(std::nullptr_t, ExclusivePtr<T[ ]>)
    SUTL_TEST_ASSERT(nullptr != arrPtr);

    delete n;
    n = nullptr;

    // Confirm Cleanup
    SUTL_CLEANUP_ASSERT(n == nullptr);

    /// Test Pass!
    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::ExclusivePointer::LessThanOperator( )
{
    int* n = nullptr;

    TTL::ExclusivePointer<int> numPtr;
    TTL::ExclusivePointer<int[ ]> arrPtr;

    try
    {
        n = new int;
        numPtr = new int;
        arrPtr = new int[16];
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    // Confirm Initial Test Conditions
    SUTL_SETUP_ASSERT(n != nullptr);
    SUTL_SETUP_ASSERT(numPtr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(arrPtr.Get( ) != nullptr);

    // Test operator<(ExclusivePtr<T1>, ExclusivePtr<T2>)
    SUTL_TEST_ASSERT(numPtr.Get( ) < arrPtr.Get( ) ? numPtr < arrPtr : arrPtr < numPtr);

    // Test operator<(ExclusivePtr<T>, const T* const)
    SUTL_TEST_ASSERT(numPtr.Get( ) < n ? numPtr < n : n < numPtr);

    // Test operator<(ExclusivePtr<T[ ]>, const T* const)
    SUTL_TEST_ASSERT(arrPtr.Get( ) < n ? arrPtr < n : n < arrPtr);

    // Test operator<(const T* const, ExclusivePtr<T>)
    SUTL_TEST_ASSERT(!(numPtr.Get( ) < n ? n < numPtr : numPtr < n));

    // Test operator<(const T* const, ExclusivePtr<T[ ]>)
    SUTL_TEST_ASSERT(!(arrPtr.Get( ) < n ? n < arrPtr : arrPtr < n));

    // Test operator<(ExclusivePtr<T>, std::nullptr_t)
    SUTL_TEST_ASSERT(!(numPtr < nullptr));

    // Test operator<(ExclusivePtr<T[ ]>, std::nullptr_t)
    SUTL_TEST_ASSERT(!(arrPtr < nullptr));

    // Test operator<(std::nullptr_t, ExclusivePtr<T>)
    SUTL_TEST_ASSERT(nullptr < numPtr);

    // Test operator<(std::nullptr_t, ExclusivePtr<T[ ]>)
    SUTL_TEST_ASSERT(nullptr < arrPtr);

    /// Test Pass!
    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::ExclusivePointer::GreaterThanOperator( )
{
    int* n = nullptr;

    TTL::ExclusivePointer<int> numPtr;
    TTL::ExclusivePointer<int[ ]> arrPtr;

    try
    {
        n = new int;
        numPtr = new int;
        arrPtr = new int[16];
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    // Confirm Initial Test Conditions
    SUTL_SETUP_ASSERT(n != nullptr);
    SUTL_SETUP_ASSERT(numPtr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(arrPtr.Get( ) != nullptr);

    // Test operator>(ExclusivePtr<T1>, ExclusivePtr<T2>)
    SUTL_TEST_ASSERT(numPtr.Get( ) > arrPtr.Get( ) ? numPtr > arrPtr : arrPtr > numPtr);

    // Test operator>(ExclusivePtr<T>, const T* const)
    SUTL_TEST_ASSERT(numPtr.Get( ) > n ? numPtr > n : n > numPtr);

    // Test operator>(ExclusivePtr<T[ ]>, const T* const)
    SUTL_TEST_ASSERT(arrPtr.Get( ) > n ? arrPtr > n : n > arrPtr);

    // Test operator>(const T* const, ExclusivePtr<T>)
    SUTL_TEST_ASSERT(!(numPtr.Get( ) > n ? n > numPtr : numPtr > n));

    // Test operator>(const T* const, ExclusivePtr<T[ ]>)
    SUTL_TEST_ASSERT(!(arrPtr.Get( ) > n ? n > arrPtr : arrPtr > n));

    // Test operator>(ExclusivePtr<T>, std::nullptr_t)
    SUTL_TEST_ASSERT(numPtr > nullptr);

    // Test operator>(ExclusivePtr<T[ ]>, std::nullptr_t)
    SUTL_TEST_ASSERT(arrPtr > nullptr);

    // Test operator>(std::nullptr_t, ExclusivePtr<T>)
    SUTL_TEST_ASSERT(!(nullptr > numPtr));

    // Test operator>(std::nullptr_t, ExclusivePtr<T[ ]>)
    SUTL_TEST_ASSERT(!(nullptr > arrPtr));

    /// Test Pass!
    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::ExclusivePointer::LessThanOrEqualOperator( )
{
    int* n = nullptr;
    int* arr = nullptr;

    TTL::ExclusivePointer<int> numPtr, numCopy;
    TTL::ExclusivePointer<int[ ]> arrPtr, arrCopy;

    try
    {
        n = new int;
        arr = new int[16];
        numPtr = new int;
        numCopy = n;
        arrPtr = new int[16];
        arrCopy = arr;
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    // Confirm Initial Test Conditions
    SUTL_SETUP_ASSERT(n != nullptr);
    SUTL_SETUP_ASSERT(arr != nullptr);
    SUTL_SETUP_ASSERT(numPtr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(arrPtr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(numCopy.Get( ) == n);
    SUTL_SETUP_ASSERT(arrCopy.Get( ) == arr);

    // Test operator<=(ExclusivePtr<T1>, ExclusivePtr<T2>)
    SUTL_TEST_ASSERT(numPtr.Get( ) <= arrPtr.Get( ) ? numPtr <= arrPtr : arrPtr <= numPtr);

    // Test operator<=(ExclusivePtr<T>, const T* const)
    SUTL_TEST_ASSERT(numPtr.Get( ) <= n ? numPtr <= n : n <= numPtr);

    // Test operator<=(ExclusivePtr<T[ ]>, const T* const)
    SUTL_TEST_ASSERT(arrPtr.Get( ) <= n ? arrPtr <= n : n <= arrPtr);

    // Test operator<=(const T* const, ExclusivePtr<T>)
    SUTL_TEST_ASSERT(!(numPtr.Get( ) <= n ? n <= numPtr : numPtr <= n));

    // Test operator<=(const T* const, ExclusivePtr<T[ ]>)
    SUTL_TEST_ASSERT(!(arrPtr.Get( ) <= n ? n <= arrPtr : arrPtr <= n));

    // Test operator<=(ExclusivePtr<T>, std::nullptr_t)
    SUTL_TEST_ASSERT(!(numPtr <= nullptr));

    // Test operator<=(ExclusivePtr<T[ ]>, std::nullptr_t)
    SUTL_TEST_ASSERT(!(arrPtr <= nullptr));

    // Test operator<=(std::nullptr_t, ExclusivePtr<T>)
    SUTL_TEST_ASSERT(nullptr <= numPtr);

    // Test operator<=(std::nullptr_t, ExclusivePtr<T[ ]>)
    SUTL_TEST_ASSERT(nullptr <= arrPtr);

    // Focus on "equal to" part of "less than or equal to"
    SUTL_TEST_ASSERT(numCopy <= n);
    SUTL_TEST_ASSERT(n <= numCopy);
    SUTL_TEST_ASSERT(arrCopy <= arr);
    SUTL_TEST_ASSERT(arr <= arrCopy);

    /// Test Pass!
    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::ExclusivePointer::GreaterThanOrEqualOperator( )
{
    int* n = nullptr;
    int* arr = nullptr;

    TTL::ExclusivePointer<int> numPtr, numCopy;
    TTL::ExclusivePointer<int[ ]> arrPtr, arrCopy;

    try
    {
        n = new int;
        arr = new int[16];
        numPtr = new int;
        numCopy = n;
        arrPtr = new int[16];
        arrCopy = arr;
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    // Confirm Initial Test Conditions
    SUTL_SETUP_ASSERT(n != nullptr);
    SUTL_SETUP_ASSERT(arr != nullptr);
    SUTL_SETUP_ASSERT(numPtr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(arrPtr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(numCopy.Get( ) == n);
    SUTL_SETUP_ASSERT(arrCopy.Get( ) == arr);

    // Test operator>=(ExclusivePtr<T1>, ExclusivePtr<T2>)
    SUTL_TEST_ASSERT(numPtr.Get( ) >= arrPtr.Get( ) ? numPtr >= arrPtr : arrPtr >= numPtr);

    // Test operator>=(ExclusivePtr<T>, const T* const)
    SUTL_TEST_ASSERT(numPtr.Get( ) >= n ? numPtr >= n : n >= numPtr);

    // Test operator>=(ExclusivePtr<T[ ]>, const T* const)
    SUTL_TEST_ASSERT(arrPtr.Get( ) >= n ? arrPtr >= n : n >= arrPtr);

    // Test operator>=(const T* const, ExclusivePtr<T>)
    SUTL_TEST_ASSERT(!(numPtr.Get( ) >= n ? n >= numPtr : numPtr >= n));

    // Test operator>=(const T* const, ExclusivePtr<T[ ]>)
    SUTL_TEST_ASSERT(!(arrPtr.Get( ) >= n ? n >= arrPtr : arrPtr >= n));

    // Test operator>=(ExclusivePtr<T>, std::nullptr_t)
    SUTL_TEST_ASSERT(numPtr >= nullptr);

    // Test operator>=(ExclusivePtr<T[ ]>, std::nullptr_t)
    SUTL_TEST_ASSERT(arrPtr >= nullptr);

    // Test operator>=(std::nullptr_t, ExclusivePtr<T>)
    SUTL_TEST_ASSERT(!(nullptr >= numPtr));

    // Test operator>=(std::nullptr_t, ExclusivePtr<T[ ]>)
    SUTL_TEST_ASSERT(!(nullptr >= arrPtr));

    // Focus on "equal to" part of "greater than or equal to"
    SUTL_TEST_ASSERT(numCopy >= n);
    SUTL_TEST_ASSERT(n >= numCopy);
    SUTL_TEST_ASSERT(arrCopy >= arr);
    SUTL_TEST_ASSERT(arr >= arrCopy);

    /// Test Pass!
    SUTL_TEST_SUCCESS( );
}


/// Assignment Operator Tests \\\

UnitTestResult TTLTests::ExclusivePointer::AssignmentOperatorRaw( )
{
    int* n = nullptr;
    int* arr = nullptr;
    TTL::ExclusivePointer<int> numPtr;
    TTL::ExclusivePointer<int[ ]> arrPtr;

    try
    {
        n = new int;
        arr = new int[16];
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    // Confirm Initial Test Conditions
    SUTL_SETUP_ASSERT(numPtr.Get( ) == nullptr);
    SUTL_SETUP_ASSERT(arrPtr.Get( ) == nullptr);
    SUTL_SETUP_ASSERT(n != nullptr);
    SUTL_SETUP_ASSERT(arr != nullptr);

    // Test Raw Pointer Assignment
    numPtr = n;
    SUTL_TEST_ASSERT(numPtr.Get( ) != nullptr);
    SUTL_TEST_ASSERT(numPtr.Get( ) == n);

    arrPtr = arr;
    SUTL_TEST_ASSERT(arrPtr.Get( ) != nullptr);
    SUTL_TEST_ASSERT(arrPtr.Get( ) == arr);

    /// Test Pass!
    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::ExclusivePointer::AssignmentOperatorNull( )
{
    int* n = nullptr;
    int* arr = nullptr;
    TTL::ExclusivePointer<int> numPtr;
    TTL::ExclusivePointer<int[ ]> arrPtr;

    try
    {
        numPtr.Set(new int);
        arrPtr.Set(new int[16]);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    n = numPtr.Get( );
    arr = arrPtr.Get( );

    // Confirm Initial Test Conditions
    SUTL_SETUP_ASSERT(numPtr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(numPtr.Get( ) == n);
    SUTL_SETUP_ASSERT(arrPtr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(arrPtr.Get( ) == arr);

    // Test nullptr assignment
    numPtr = nullptr;
    arrPtr = nullptr;

    SUTL_TEST_ASSERT(numPtr.Get( ) != n);
    SUTL_TEST_ASSERT(numPtr.Get( ) == nullptr);
    SUTL_TEST_ASSERT(arrPtr.Get( ) != arr);
    SUTL_TEST_ASSERT(arrPtr.Get( ) == nullptr);

    /// Test Pass!
    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::ExclusivePointer::AssignmentOperatorMove( )
{
    TTL::ExclusivePointer<int> numPtr, moveNum;
    TTL::ExclusivePointer<int[ ]> arrPtr, moveArr;
    int* copyNum = nullptr;
    int* copyArr = nullptr;

    try
    {
        moveNum.Set(new int);
        moveArr.Set(new int[16]);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    copyNum = moveNum.Get( );
    copyArr = moveArr.Get( );

    // Confirm Initial Test Conditions
    SUTL_SETUP_ASSERT(numPtr.Get( ) == nullptr);
    SUTL_SETUP_ASSERT(moveNum.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(copyNum == moveNum.Get( ));

    SUTL_SETUP_ASSERT(arrPtr.Get( ) == nullptr);
    SUTL_SETUP_ASSERT(moveArr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(copyArr == moveArr.Get( ));

    // Test ExclusivePointer Move Assignment
    numPtr = std::move(moveNum);
    SUTL_TEST_ASSERT(moveNum.Get( ) == nullptr);
    SUTL_TEST_ASSERT(numPtr.Get( ) != nullptr);
    SUTL_TEST_ASSERT(numPtr.Get( ) == copyNum);

    arrPtr = std::move(moveArr);
    SUTL_TEST_ASSERT(moveArr.Get( ) == nullptr);
    SUTL_TEST_ASSERT(arrPtr.Get( ) != nullptr);
    SUTL_TEST_ASSERT(arrPtr.Get( ) == copyArr);

    /// Test Pass!
    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::ExclusivePointer::AssignmentOperatorSelf( )
{
    bool selfAssignmentThrew = false;
    int* n = nullptr;
    int* arr = nullptr;
    TTL::ExclusivePointer<int> numPtr;
    TTL::ExclusivePointer<int[ ]> arrPtr;

    try
    {
        numPtr.Set(new int);
        arrPtr.Set(new int[16]);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    n = numPtr.Get( );
    arr = arrPtr.Get( );

    // Confirm Initial Test Conditions
    SUTL_SETUP_ASSERT(selfAssignmentThrew == false);
    SUTL_SETUP_ASSERT(numPtr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(numPtr.Get( ) == n);
    SUTL_SETUP_ASSERT(arrPtr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(arrPtr.Get( ) == arr);

    // Attempt Self Assignment - Non-Array
    try
    {
        numPtr = std::move(numPtr);
    }
    catch ( const std::exception& )
    {
        selfAssignmentThrew = true;
    }

    // Ensure self-assignment threw exception.
    SUTL_TEST_ASSERT(selfAssignmentThrew == true);
    // Ensure data was preserved.
    SUTL_TEST_ASSERT(numPtr.Get( ) == n);

    // Setup for Array Pointer Self Assignment
    selfAssignmentThrew = false;
    SUTL_SETUP_ASSERT(selfAssignmentThrew == false);

    // Attempt Self Assignment - Array
    try
    {
        arrPtr = std::move(arrPtr);
    }
    catch ( const std::exception& )
    {
        selfAssignmentThrew = true;
    }

    // Ensure self-assignment threw exception.
    SUTL_TEST_ASSERT(selfAssignmentThrew == true);
    // Ensure data was preserved.
    SUTL_TEST_ASSERT(arrPtr.Get( ) == arr);

    /// Test Pass!
    SUTL_TEST_SUCCESS( );
}


/// Public Method Tests \\\

UnitTestResult TTLTests::ExclusivePointer::Release( )
{
    TTL::ExclusivePointer<int> numPtr;
    TTL::ExclusivePointer<int[ ]> arrPtr;

    try
    {
        numPtr = new int;
        arrPtr = new int[16];
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    // Confirm Initial Test Conditions
    SUTL_SETUP_ASSERT(numPtr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(arrPtr.Get( ) != nullptr);

    numPtr.Release( );
    arrPtr.Release( );

    // Ensure release actually released resources.
    SUTL_TEST_ASSERT(numPtr.Get( ) == nullptr);
    SUTL_TEST_ASSERT(arrPtr.Get( ) == nullptr);

    /// Test Pass!
    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::ExclusivePointer::SetNull( )
{
    TTL::ExclusivePointer<int> numPtr;
    TTL::ExclusivePointer<int[ ]> arrPtr;

    try
    {
        numPtr = new int;
        arrPtr = new int[16];
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    // Confirm Initial Test Conditions
    SUTL_SETUP_ASSERT(numPtr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(arrPtr.Get( ) != nullptr);

    numPtr.Set(nullptr);
    arrPtr.Set(nullptr);

    // Ensure set actually modified the object.
    SUTL_TEST_ASSERT(numPtr.Get( ) == nullptr);
    SUTL_TEST_ASSERT(arrPtr.Get( ) == nullptr);

    /// Test Pass!
    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::ExclusivePointer::SetRaw( )
{
    int* n = nullptr;
    int* arr = nullptr;

    TTL::ExclusivePointer<int> numPtr;
    TTL::ExclusivePointer<int[ ]> arrPtr;

    try
    {
        n = new int;
        arr = new int[16];
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    // Confirm Initial Test Conditions
    SUTL_SETUP_ASSERT(n != nullptr);
    SUTL_SETUP_ASSERT(arr != nullptr);

    numPtr.Set(n);
    arrPtr.Set(arr);

    // Ensure set actually modified the object.
    SUTL_TEST_ASSERT(numPtr.Get( ) == n);
    SUTL_TEST_ASSERT(arrPtr.Get( ) == arr);

    /// Test Pass!
    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::ExclusivePointer::SetMove( )
{
    int* n = nullptr;
    int* arr = nullptr;

    TTL::ExclusivePointer<int> numPtr, moveNum;
    TTL::ExclusivePointer<int[ ]> arrPtr, moveArr;

    try
    {
        numPtr = new int;
        arrPtr = new int[16];
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    n = numPtr.Get( );
    arr = arrPtr.Get( );

    // Confirm Initial Test Conditions
    SUTL_SETUP_ASSERT(numPtr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(arrPtr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(numPtr.Get( ) == n);
    SUTL_SETUP_ASSERT(arrPtr.Get( ) == arr);

    moveNum.Set(std::move(numPtr));
    moveArr.Set(std::move(arrPtr));

    // Ensure ownership of resources were transferred.
    SUTL_TEST_ASSERT(numPtr.Get( ) == nullptr);
    SUTL_TEST_ASSERT(moveNum.Get( ) != nullptr);
    SUTL_TEST_ASSERT(moveNum.Get( ) == n);
    SUTL_TEST_ASSERT(arrPtr.Get( ) == nullptr);
    SUTL_TEST_ASSERT(moveArr.Get( ) != nullptr);
    SUTL_TEST_ASSERT(moveArr.Get( ) == arr);

    /// Test Pass!
    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::ExclusivePointer::SetSelf( )
{
    bool selfSetThrew = false;
    int* n = nullptr;
    int* arr = nullptr;
    TTL::ExclusivePointer<int> numPtr;
    TTL::ExclusivePointer<int[ ]> arrPtr;

    try
    {
        numPtr = new int;
        arrPtr = new int[16];
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    n = numPtr.Get( );
    arr = arrPtr.Get( );

    // Confirm Initial Test Conditions
    SUTL_SETUP_ASSERT(selfSetThrew == false);
    SUTL_SETUP_ASSERT(numPtr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(numPtr.Get( ) == n);
    SUTL_SETUP_ASSERT(arrPtr.Get( ) != nullptr);
    SUTL_SETUP_ASSERT(arrPtr.Get( ) == arr);

    // Attempt Self Set - Non-Array
    try
    {
        numPtr.Set(std::move(numPtr));
    }
    catch ( const std::exception& )
    {
        selfSetThrew = true;
    }

    // Ensure self-set threw exception.
    SUTL_TEST_ASSERT(selfSetThrew == true);
    // Ensure data was preserved.
    SUTL_TEST_ASSERT(numPtr.Get( ) == n);

    // Setup for Array Pointer Self Set
    selfSetThrew = false;
    SUTL_SETUP_ASSERT(selfSetThrew == false);

    // Attempt Self Set - Array
    try
    {
        arrPtr.Set(std::move(arrPtr));
    }
    catch ( const std::exception& )
    {
        selfSetThrew = true;
    }

    // Ensure self-set threw exception.
    SUTL_TEST_ASSERT(selfSetThrew == true);
    // Ensure data was preserved.
    SUTL_TEST_ASSERT(arrPtr.Get( ) == arr);

    /// Test Pass!
    SUTL_TEST_SUCCESS( );
}
