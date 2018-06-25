#include "StackTests.h"

#include "Stack.hpp"

#include "MemoryManagementHelper.hpp"

std::list<std::function<UnitTestResult(void)>> TTLTests::Stack::BuildTestList( )
{
    static const std::list<std::function<UnitTestResult(void)>> testList =
    {
        DefaultConstructor,
        CopyConstructor,
        MoveConstructor,
        CopyAssignment,
        MoveAssignment,
        Clear,
        CopyPush,
        MovePush,
        Pop
    };

    return testList;
}

// Constructor Tests
UnitTestResult TTLTests::Stack::DefaultConstructor( )
{
    bool threw = false;
    TTL::Stack<size_t> stack;

    SUTL_TEST_ASSERT(stack.Empty( ));
    SUTL_TEST_ASSERT(stack.Size( ) == 0);
    SUTL_TEST_ASSERT(stack.TopPtr( ) == nullptr);

    try
    {
        stack.Top( );
    }
    catch ( const std::logic_error& )
    {
        threw = true;
    }

    SUTL_TEST_ASSERT(threw);

    threw = false;
    try
    {
        stack.Pop( );
    }
    catch ( const std::logic_error& )
    {
        threw = true;
    }

    SUTL_TEST_ASSERT(threw);

    /// Test Pass!
    SUTL_TEST_SUCCESS( );
}


UnitTestResult TTLTests::Stack::CopyConstructor( )
{
    const size_t STACK_SIZE = 3;
    const TTL::Node<size_t>* numStackPtr = nullptr;
    const TTL::Node<size_t>* copyStackPtr = nullptr;

    TTL::Stack<size_t> numStack;
    TTL::Stack<size_t>* pCopyStack = nullptr;

    try
    {
        numStack.Push(2);
        numStack.Push(1);
        numStack.Push(0);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    try
    {
        pCopyStack = new TTL::Stack<size_t>(numStack);
    }
    catch ( const std::exception& e )
    {
        SUTL_TEST_EXCEPTION(e.what( ));
    }

    numStackPtr = numStack.TopPtr( );
    copyStackPtr = pCopyStack->TopPtr( );
    
    SUTL_TEST_ASSERT(numStackPtr != nullptr);
    SUTL_TEST_ASSERT(copyStackPtr != nullptr);

    while ( numStackPtr && copyStackPtr )
    {
        SUTL_TEST_ASSERT(numStackPtr != copyStackPtr);
        SUTL_TEST_ASSERT(numStackPtr->GetData( ) == copyStackPtr->GetData( ));
        numStackPtr = numStackPtr->GetNext( );
        copyStackPtr = copyStackPtr->GetNext( );
    }

    SUTL_TEST_ASSERT(numStackPtr == nullptr);
    SUTL_TEST_ASSERT(copyStackPtr == nullptr);

    SUTL_TEST_ASSERT(numStack.Empty( ) == false);
    SUTL_TEST_ASSERT(pCopyStack->Empty( ) == false);
    SUTL_TEST_ASSERT(numStack.Size( ) == STACK_SIZE);
    SUTL_TEST_ASSERT(numStack.Size( ) == pCopyStack->Size( ));

    /// Test Pass!
    SUTL_TEST_SUCCESS( );
}


UnitTestResult TTLTests::Stack::MoveConstructor( )
{
    const TTL::Node<size_t>* numStackPtr = nullptr;
    const TTL::Node<size_t>* moveStackPtr = nullptr;
    const size_t STACK_SIZE = 3;
    TTL::Stack<size_t> numStack;
    TTL::Stack<size_t>* pMoveStack = nullptr;

    try
    {
        numStack.Push(2);
        numStack.Push(1);
        numStack.Push(0);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    numStackPtr = numStack.TopPtr( );

    try
    {
        pMoveStack = new TTL::Stack<size_t>(std::move(numStack));
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    moveStackPtr = pMoveStack->TopPtr( );
    SUTL_TEST_ASSERT(numStack.TopPtr( ) == nullptr);
    SUTL_TEST_ASSERT(numStackPtr == moveStackPtr);
    SUTL_TEST_ASSERT(moveStackPtr != nullptr);

    for ( size_t i = 0; i < STACK_SIZE; i++ )
    {
        SUTL_TEST_ASSERT(moveStackPtr->GetData( ) == i);
        moveStackPtr = moveStackPtr->GetNext( );
    }

    SUTL_TEST_ASSERT(moveStackPtr == nullptr);

    SUTL_TEST_ASSERT(numStack.Empty( ) == true);
    SUTL_TEST_ASSERT(pMoveStack->Empty( ) == false);
    SUTL_TEST_ASSERT(numStack.Size( ) == 0);
    SUTL_TEST_ASSERT(pMoveStack->Size( ) == STACK_SIZE);

    /// Test Pass!
    SUTL_TEST_SUCCESS( );
}



// Assignment Operator Tests
UnitTestResult TTLTests::Stack::CopyAssignment( )
{
    const size_t STACK_SIZE = 3;
    const TTL::Node<size_t>* stackPtr = nullptr;
    const TTL::Node<size_t>* copyPtr = nullptr;

    TTL::Stack<size_t> stack;
    TTL::Stack<size_t> copyStack;

    try
    {
        stack.Push(2);
        stack.Push(1);
        stack.Push(0);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    try
    {
        copyStack = stack;
    }
    catch ( const std::exception& e )
    {
        SUTL_TEST_EXCEPTION(e.what( ));
    }

    stackPtr = stack.TopPtr( );
    copyPtr = copyStack.TopPtr( );

    while ( stackPtr && copyPtr )
    {
        SUTL_TEST_ASSERT(stackPtr != copyPtr);
        SUTL_TEST_ASSERT(stackPtr->GetData( ) == copyPtr->GetData( ));
        stackPtr = stackPtr->GetNext( );
        copyPtr = copyPtr->GetNext( );
    }

    SUTL_TEST_ASSERT(stackPtr == nullptr);
    SUTL_TEST_ASSERT(copyPtr == nullptr);

    SUTL_TEST_ASSERT(stack.Empty( ) == false);
    SUTL_TEST_ASSERT(copyStack.Empty( ) == false);
    SUTL_TEST_ASSERT(stack.Size( ) == STACK_SIZE);
    SUTL_TEST_ASSERT(copyStack.Size( ) == STACK_SIZE);

    /// Test Pass!
    SUTL_TEST_SUCCESS( );
}


UnitTestResult TTLTests::Stack::MoveAssignment( )
{
    const size_t STACK_SIZE = 3;
    const TTL::Node<size_t>* stackPtr = nullptr;
    const TTL::Node<size_t>* movePtr = nullptr;

    TTL::Stack<size_t> stack;
    TTL::Stack<size_t> moveStack;

    try
    {
        stack.Push(2);
        stack.Push(1);
        stack.Push(0);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    stackPtr = stack.TopPtr( );

    moveStack = std::move(stack);

    movePtr = moveStack.TopPtr( );
    SUTL_TEST_ASSERT(stackPtr == movePtr);
    SUTL_TEST_ASSERT(stack.TopPtr( ) == nullptr);

    for ( size_t i = 0; i < STACK_SIZE; i++ )
    {
        SUTL_TEST_ASSERT(movePtr->GetData( ) == i);
        movePtr = movePtr->GetNext( );
    }

    SUTL_TEST_ASSERT(stack.Empty( ) == true);
    SUTL_TEST_ASSERT(moveStack.Empty( ) == false);
    SUTL_TEST_ASSERT(stack.Size( ) == 0);
    SUTL_TEST_ASSERT(moveStack.Size( ) == STACK_SIZE);

    /// Test Pass!
    SUTL_TEST_SUCCESS( );
}



// Public Method Tests
UnitTestResult TTLTests::Stack::Clear( )
{
    const size_t STACK_SIZE = 3;
    TTL::Stack<size_t> stack;

    try
    {
        stack.Push(2);
        stack.Push(1);
        stack.Push(0);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_TEST_ASSERT(stack.Empty( ) == false);
    SUTL_TEST_ASSERT(stack.Size( ) == STACK_SIZE);
    SUTL_TEST_ASSERT(stack.TopPtr( ) != nullptr);

    stack.Clear( );

    SUTL_TEST_ASSERT(stack.Empty( ) == true);
    SUTL_TEST_ASSERT(stack.Size( ) == 0);
    SUTL_TEST_ASSERT(stack.TopPtr( ) == nullptr);

    /// Test Pass!
    SUTL_TEST_SUCCESS( );
}


UnitTestResult TTLTests::Stack::CopyPush( )
{
    const TTL::Node<MemoryManagementHelper>* ptr = nullptr;

    TTL::Stack<MemoryManagementHelper>* pStack = nullptr;

    SUTL_SETUP_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 0);
    
    try
    {
        MemoryManagementHelper copyHelper;
        pStack = new TTL::Stack<MemoryManagementHelper>;
        pStack->Push(copyHelper);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_TEST_ASSERT(pStack->Empty( ) == false);
    SUTL_TEST_ASSERT(pStack->Size( ) == 1);
    SUTL_TEST_ASSERT(pStack->TopPtr( ) != nullptr);
    SUTL_TEST_ASSERT(pStack->Top( ).GetCopy( ) == true);
    SUTL_TEST_ASSERT(pStack->Top( ).GetMove( ) == false);

    ptr = pStack->TopPtr( );

    try
    {
        MemoryManagementHelper copyHelper;
        pStack->Push(copyHelper);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_TEST_ASSERT(pStack->Empty( ) == false);
    SUTL_TEST_ASSERT(pStack->Size( ) == 2);
    SUTL_TEST_ASSERT(pStack->TopPtr( ) != nullptr);
    SUTL_TEST_ASSERT(pStack->Top( ).GetCopy( ) == true);
    SUTL_TEST_ASSERT(pStack->Top( ).GetMove( ) == false);
    SUTL_TEST_ASSERT(ptr == pStack->TopPtr( )->GetNext( ));

    delete pStack;
    pStack = nullptr;

    SUTL_TEST_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 4);
    SUTL_CLEANUP_ASSERT(pStack == nullptr);

    /// Test Pass!
    SUTL_TEST_SUCCESS( );
}


UnitTestResult TTLTests::Stack::MovePush( )
{
    const TTL::Node<MemoryManagementHelper>* ptr = nullptr;

    TTL::Stack<MemoryManagementHelper>* pStack = nullptr;

    SUTL_SETUP_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 0);

    try
    {
        pStack = new TTL::Stack<MemoryManagementHelper>;
        pStack->Push(MemoryManagementHelper( ));
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_TEST_ASSERT(pStack->Empty( ) == false);
    SUTL_TEST_ASSERT(pStack->Size( ) == 1);
    SUTL_TEST_ASSERT(pStack->TopPtr( ) != nullptr);
    SUTL_TEST_ASSERT(pStack->Top( ).GetCopy( ) == false);
    SUTL_TEST_ASSERT(pStack->Top( ).GetMove( ) == true);

    ptr = pStack->TopPtr( );

    try
    {
        pStack->Push(MemoryManagementHelper( ));
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_TEST_ASSERT(pStack->Empty( ) == false);
    SUTL_TEST_ASSERT(pStack->Size( ) == 2);
    SUTL_TEST_ASSERT(pStack->TopPtr( ) != nullptr);
    SUTL_TEST_ASSERT(pStack->Top( ).GetCopy( ) == false);
    SUTL_TEST_ASSERT(pStack->Top( ).GetMove( ) == true);
    SUTL_TEST_ASSERT(ptr == pStack->TopPtr( )->GetNext( ));

    delete pStack;
    pStack = nullptr;

    SUTL_TEST_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 4);
    SUTL_CLEANUP_ASSERT(pStack == nullptr);

    /// Test Pass!
    SUTL_TEST_SUCCESS( );
}


UnitTestResult TTLTests::Stack::Pop( )
{
    const size_t STACK_SIZE = 10;
    bool threw = false;

    TTL::Stack<size_t> stack;

    try
    {
        stack.Pop( );
    }
    catch ( const std::logic_error& )
    {
        threw = true;
    }

    SUTL_TEST_ASSERT(threw == true);

    try
    {
        for ( size_t i = 0; i < STACK_SIZE; i++ )
        {
            stack.Push(STACK_SIZE - i - 1);
        }
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_TEST_ASSERT(stack.Empty( ) == false);
    SUTL_TEST_ASSERT(stack.Size( ) == STACK_SIZE);

    size_t i = 0;
    while ( !stack.Empty( ) )
    {
        SUTL_TEST_ASSERT(i < STACK_SIZE);
        SUTL_TEST_ASSERT(stack.TopPtr( ) != nullptr);
        SUTL_TEST_ASSERT(stack.Top( ) == i++);

        try
        {
            stack.Pop( );
        }
        catch ( const std::logic_error& e )
        {
            SUTL_TEST_EXCEPTION(e.what( ));
        }
    }

    /// Test Pass!
    SUTL_TEST_SUCCESS( );
}
