#include "ArrayTests.h"

#include <Array.hpp>

std::list<std::function<UnitTestResult(void)>> TTLTests::Array::BuildTestList( )
{
    static const std::list<std::function<UnitTestResult(void)>> testList =
    {
        // Constructor Tests
        DefaultConstructor,
        CapacityConstructor,
        CopyConstructor,
        MoveConstructor,

        // Assignment Tests
        CopyAssignment,
        MoveAssignment,

        // Subscript Test
        Subscript,

        // Public Method Tests
        At,
        Clear
    };

    return testList;
}


// Constructor Tests
UnitTestResult TTLTests::Array::DefaultConstructor( )
{
    TTL::Array<uint64> emptyArr;

    SUTL_TEST_ASSERT(emptyArr.Capacity( ) == 0ull);
    SUTL_TEST_ASSERT(emptyArr.Data( ) == nullptr);
    SUTL_TEST_ASSERT(emptyArr.Empty( ) == true);

    /// Test Pass!
    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::Array::CapacityConstructor( )
{
    const uint64 ARR_SIZE = 16ull;
    TTL::Array<uint64> arr(ARR_SIZE);
    TTL::Array<uint64> emptyArr(0ull);

    SUTL_TEST_ASSERT(arr.Capacity( ) == ARR_SIZE);
    SUTL_TEST_ASSERT(arr.Data( ) != nullptr);
    SUTL_TEST_ASSERT(arr.Empty( ) == false);

    SUTL_TEST_ASSERT(emptyArr.Capacity( ) == 0ull);
    SUTL_TEST_ASSERT(emptyArr.Data( ) == nullptr);
    SUTL_TEST_ASSERT(emptyArr.Empty( ) == true);

    /// Test Pass!
    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::Array::CopyConstructor( )
{
    const uint64 ARR_SIZE = 16ull;
    TTL::Array<uint64> arr(ARR_SIZE);

    for ( uint64 i = 0; i < ARR_SIZE; i++ )
    {
        arr.Data( )[i] = i;
    }

    // Confirm Initial Test Conditions
    SUTL_SETUP_ASSERT(arr.Capacity( ) == ARR_SIZE);
    SUTL_SETUP_ASSERT(arr.Data( ) != nullptr);
    SUTL_SETUP_ASSERT(arr.Empty( ) == false);
    for ( uint64 i = 0; i < ARR_SIZE; i++ )
    {
        SUTL_SETUP_ASSERT(arr.Data( )[i] == i);
    }

    TTL::Array<uint64> copyArr(arr);

    // Ensure data was copied.
    SUTL_TEST_ASSERT(arr.Capacity( ) == ARR_SIZE);
    SUTL_TEST_ASSERT(copyArr.Capacity( ) == ARR_SIZE);
    SUTL_TEST_ASSERT(arr.Data( ) != nullptr);
    SUTL_TEST_ASSERT(copyArr.Data( ) != nullptr);
    SUTL_TEST_ASSERT(arr.Empty( ) == false);
    SUTL_TEST_ASSERT(copyArr.Empty( ) == false);
    SUTL_TEST_ASSERT(copyArr.Data( ) != arr.Data( ));
    for ( uint64 i = 0; i < ARR_SIZE; i++ )
    {
        SUTL_TEST_ASSERT(copyArr.Data( )[i] == arr.Data( )[i]);
    }

    /// Test Pass!
    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::Array::MoveConstructor( )
{
    const uint64 ARR_SIZE = 16ull;
    TTL::Array<uint64> arr(ARR_SIZE);
    uint64* pArr = arr.Data( );

    for ( uint64 i = 0; i < ARR_SIZE; i++ )
    {
        arr.Data( )[i] = i;
    }

    // Confirm Initial Test Conditions
    SUTL_SETUP_ASSERT(arr.Capacity( ) == ARR_SIZE);
    SUTL_SETUP_ASSERT(arr.Data( ) != nullptr);
    SUTL_SETUP_ASSERT(arr.Data( ) == pArr);
    SUTL_SETUP_ASSERT(arr.Empty( ) == false);
    for ( uint64 i = 0; i < ARR_SIZE; i++ )
    {
        SUTL_SETUP_ASSERT(arr.Data( )[i] == i);
    }

    TTL::Array<uint64> moveArr(std::move(arr));

    // Ensure data was moved.
    SUTL_TEST_ASSERT(arr.Capacity( ) == 0);
    SUTL_TEST_ASSERT(moveArr.Capacity( ) == ARR_SIZE);
    SUTL_TEST_ASSERT(arr.Data( ) == nullptr);
    SUTL_TEST_ASSERT(moveArr.Data( ) != nullptr);
    SUTL_TEST_ASSERT(moveArr.Data( ) == pArr);
    SUTL_TEST_ASSERT(arr.Empty( ) == true);
    SUTL_TEST_ASSERT(moveArr.Empty( ) == false);
    for ( uint64 i = 0; i < ARR_SIZE; i++ )
    {
        SUTL_TEST_ASSERT(moveArr.Data( )[i] == i);
    }

    /// Test Pass!
    SUTL_TEST_SUCCESS( );
}


// Assignment Tests
UnitTestResult TTLTests::Array::CopyAssignment( )
{
    const uint64 ARR_SIZE = 16ull;
    TTL::Array<uint64> arr(ARR_SIZE);
    TTL::Array<uint64> copyArr;

    for ( uint64 i = 0; i < ARR_SIZE; i++ )
    {
        arr.Data( )[i] = i;
    }

    // Confirm Initial Test Conditions
    SUTL_SETUP_ASSERT(arr.Capacity( ) == ARR_SIZE);
    SUTL_SETUP_ASSERT(arr.Data( ) != nullptr);
    SUTL_SETUP_ASSERT(arr.Empty( ) == false);
    SUTL_SETUP_ASSERT(copyArr.Capacity( ) == 0ull);
    SUTL_SETUP_ASSERT(copyArr.Data( ) == nullptr);
    SUTL_SETUP_ASSERT(copyArr.Empty( ) == true);
    for ( uint64 i = 0; i < ARR_SIZE; i++ )
    {
        SUTL_SETUP_ASSERT(arr.Data( )[i] == i);
    }

    copyArr = arr;

    // Ensure data was copied.
    SUTL_TEST_ASSERT(arr.Capacity( ) == ARR_SIZE);
    SUTL_TEST_ASSERT(copyArr.Capacity( ) == ARR_SIZE);
    SUTL_TEST_ASSERT(arr.Data( ) != nullptr);
    SUTL_TEST_ASSERT(copyArr.Data( ) != nullptr);
    SUTL_TEST_ASSERT(arr.Empty( ) == false);
    SUTL_TEST_ASSERT(copyArr.Empty( ) == false);
    SUTL_TEST_ASSERT(copyArr.Data( ) != arr.Data( ));
    for ( uint64 i = 0; i < ARR_SIZE; i++ )
    {
        SUTL_TEST_ASSERT(copyArr.Data( )[i] == arr.Data( )[i]);
    }

    /// Test Pass!
    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::Array::MoveAssignment( )
{
    const uint64 ARR_SIZE = 16ull;
    TTL::Array<uint64> arr(ARR_SIZE);
    TTL::Array<uint64> moveArr;
    uint64* pArr = arr.Data( );

    for ( uint64 i = 0; i < ARR_SIZE; i++ )
    {
        arr.Data( )[i] = i;
    }

    // Confirm Initial Test Conditions
    SUTL_SETUP_ASSERT(arr.Capacity( ) == ARR_SIZE);
    SUTL_SETUP_ASSERT(arr.Data( ) != nullptr);
    SUTL_SETUP_ASSERT(arr.Data( ) == pArr);
    SUTL_SETUP_ASSERT(arr.Empty( ) == false);
    SUTL_SETUP_ASSERT(moveArr.Capacity( ) == 0ull);
    SUTL_SETUP_ASSERT(moveArr.Data( ) == nullptr);
    SUTL_SETUP_ASSERT(moveArr.Empty( ) == true);
    for ( uint64 i = 0; i < ARR_SIZE; i++ )
    {
        SUTL_SETUP_ASSERT(arr.Data( )[i] == i);
    }

    moveArr = std::move(arr);

    // Ensure data was moved.
    SUTL_TEST_ASSERT(arr.Capacity( ) == 0);
    SUTL_TEST_ASSERT(moveArr.Capacity( ) == ARR_SIZE);
    SUTL_TEST_ASSERT(arr.Data( ) == nullptr);
    SUTL_TEST_ASSERT(moveArr.Data( ) != nullptr);
    SUTL_TEST_ASSERT(moveArr.Data( ) == pArr);
    SUTL_TEST_ASSERT(arr.Empty( ) == true);
    SUTL_TEST_ASSERT(moveArr.Empty( ) == false);
    for ( uint64 i = 0; i < ARR_SIZE; i++ )
    {
        SUTL_TEST_ASSERT(moveArr.Data( )[i] == i);
    }

    /// Test Pass!
    SUTL_TEST_SUCCESS( );
}


// Subscript Test
UnitTestResult TTLTests::Array::Subscript( )
{
    const size_t ARR_SIZE = 16ull;
    bool boundaryThrow = false;
    TTL::Array<uint64> emptyArr;
    TTL::Array<uint64> arr;

    try
    {
        arr = std::move(TTL::Array<uint64>(ARR_SIZE));
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    // Confirm Initial Test Conditions
    SUTL_SETUP_ASSERT(arr.Capacity( ) == ARR_SIZE);
    SUTL_SETUP_ASSERT(arr.Data( ) != nullptr);
    SUTL_SETUP_ASSERT(arr.Empty( ) == false);
    SUTL_SETUP_ASSERT(emptyArr.Capacity( ) == 0ull);
    SUTL_SETUP_ASSERT(emptyArr.Data( ) == nullptr);
    SUTL_SETUP_ASSERT(emptyArr.Empty( ) == true);

    try
    {
        emptyArr[0] = 0;
    }
    catch ( const std::out_of_range& )
    {
        boundaryThrow = true;
    }

    SUTL_TEST_ASSERT(boundaryThrow == true);

    boundaryThrow = false;

    size_t idx = 0;
    try
    {
        for ( ; idx < ARR_SIZE + 1; idx++ )
        {
            arr[idx] = idx;
        }
    }
    catch ( const std::out_of_range& )
    {
        boundaryThrow = true;
    }

    SUTL_TEST_ASSERT(boundaryThrow == true);
    SUTL_TEST_ASSERT(idx == ARR_SIZE);

    for ( idx = 0; idx < ARR_SIZE; idx++ )
    {
        SUTL_TEST_ASSERT(arr[idx] == idx);
    }

    /// Test Pass!
    SUTL_TEST_SUCCESS( );
}


// Public Method Tests
UnitTestResult TTLTests::Array::At( )
{
    const size_t ARR_SIZE = 16ull;
    bool boundaryThrow = false;
    TTL::Array<uint64> emptyArr;
    TTL::Array<uint64> arr;

    try
    {
        arr = std::move(TTL::Array<uint64>(ARR_SIZE));
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    // Confirm Initial Test Conditions
    SUTL_SETUP_ASSERT(arr.Capacity( ) == ARR_SIZE);
    SUTL_SETUP_ASSERT(arr.Data( ) != nullptr);
    SUTL_SETUP_ASSERT(arr.Empty( ) == false);
    SUTL_SETUP_ASSERT(emptyArr.Capacity( ) == 0ull);
    SUTL_SETUP_ASSERT(emptyArr.Data( ) == nullptr);
    SUTL_SETUP_ASSERT(emptyArr.Empty( ) == true);

    try
    {
        emptyArr.At(0) = 0;
    }
    catch ( const std::out_of_range& )
    {
        boundaryThrow = true;
    }

    SUTL_TEST_ASSERT(boundaryThrow == true);

    boundaryThrow = false;

    size_t idx = 0;
    try
    {
        for ( ; idx < ARR_SIZE + 1; idx++ )
        {
            arr.At(idx) = idx;
        }
    }
    catch ( const std::out_of_range& )
    {
        boundaryThrow = true;
    }

    SUTL_TEST_ASSERT(boundaryThrow == true);
    SUTL_TEST_ASSERT(idx == ARR_SIZE);

    for ( idx = 0; idx < ARR_SIZE; idx++ )
    {
        SUTL_TEST_ASSERT(arr.At(idx) == idx);
    }

    /// Test Pass!
    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::Array::Clear( )
{
    const size_t ARR_SIZE = 16ull;
    TTL::Array<uint64> arr;

    try
    {
        arr = std::move(TTL::Array<uint64>(ARR_SIZE));
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    // Confirm Initial Test Conditions
    SUTL_SETUP_ASSERT(arr.Capacity( ) == ARR_SIZE);
    SUTL_SETUP_ASSERT(arr.Data( ) != nullptr);
    SUTL_SETUP_ASSERT(arr.Empty( ) == false);

    arr.Clear( );

    SUTL_TEST_ASSERT(arr.Capacity( ) == 0ull);
    SUTL_TEST_ASSERT(arr.Data( ) == nullptr);
    SUTL_TEST_ASSERT(arr.Empty( ) == true);

    /// Test Pass!
    SUTL_TEST_SUCCESS( );
}