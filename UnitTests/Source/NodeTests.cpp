#include "NodeTests.h"
#include "MemoryManagementHelper.hpp"

#include <Node.hpp>


std::list<std::function<UnitTestResult(void)>> TTLTests::Node::BuildTestList( )
{
    static const std::list<std::function<UnitTestResult(void)>> testList =
    {
        // Constructor Tests
        DefaultConstructor,
        MoveConstructor,

        // Assignment Operator Test
        MoveAssignment,

        // Setter Tests
        SetDataCopy,
        SetDataMove,
        SetNextRaw
    };

    return testList;
}


/// Constructor Tests \\\

UnitTestResult TTLTests::Node::DefaultConstructor( )
{
    TTL::Node<int> iNode;
    TTL::Node<unsigned long long> ullNode;
    TTL::Node<double> dNode;
    TTL::Node<char*> ptrNode;
    TTL::Node<TTL::Node<int>> iNodeNode;

    // Ensure that various data values are default-initialized.
    SUTL_TEST_ASSERT(iNode.GetData( ) == 0);
    SUTL_TEST_ASSERT(ullNode.GetData( ) == 0ull);
    SUTL_TEST_ASSERT(dNode.GetData( ) == 0.0);
    SUTL_TEST_ASSERT(ptrNode.GetData( ) == nullptr);
    SUTL_TEST_ASSERT(iNodeNode.GetData( ).GetData( ) == 0 && iNodeNode.GetData( ).GetNext( ) == nullptr);

    // Ensure that next ptr values are nullptr-initialized.
    SUTL_TEST_ASSERT(iNode.GetNext( ) == nullptr);
    SUTL_TEST_ASSERT(ullNode.GetNext( ) == nullptr);
    SUTL_TEST_ASSERT(dNode.GetNext( ) == nullptr);
    SUTL_TEST_ASSERT(ptrNode.GetNext( ) == nullptr);
    SUTL_TEST_ASSERT(iNodeNode.GetNext( ) == nullptr);

    /// Test Pass!
    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::Node::MoveConstructor( )
{
    TTL::Node<MemoryManagementHelper>* pNext = nullptr;
    TTL::Node<MemoryManagementHelper>* pNode = nullptr;
    TTL::Node<MemoryManagementHelper>* pMoveNode = nullptr;

    SUTL_SETUP_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 0);

    try
    {
        pNode = new TTL::Node<MemoryManagementHelper>;
        pNext = new TTL::Node<MemoryManagementHelper>;
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    pNode->SetNext(pNext);

    // Confirm Initial Test Conditions
    SUTL_SETUP_ASSERT(pNode->GetData( ).GetCopy( ) == false);
    SUTL_SETUP_ASSERT(pNode->GetData( ).GetMove( ) == false);
    SUTL_SETUP_ASSERT(pNode->GetNext( ) != nullptr);
    SUTL_SETUP_ASSERT(pNode->GetNext( ) == pNext);

    try
    {
        pMoveNode = new TTL::Node<MemoryManagementHelper>(std::move(*pNode));
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    // Ensure values were transferred.
    SUTL_TEST_ASSERT(pNode->GetNext( ) == nullptr);
    SUTL_TEST_ASSERT(pMoveNode->GetData( ).GetCopy( ) == false);
    SUTL_TEST_ASSERT(pMoveNode->GetData( ).GetMove( ) == true);
    SUTL_TEST_ASSERT(pMoveNode->GetNext( ) == pNext);

    // Cleanup
    delete pNode;
    pNode = nullptr;
    delete pNext;
    pNext = nullptr;
    delete pMoveNode;
    pMoveNode = nullptr;

    SUTL_CLEANUP_ASSERT(pNode == nullptr);
    SUTL_CLEANUP_ASSERT(pNext == nullptr);
    SUTL_CLEANUP_ASSERT(pMoveNode == nullptr);
    SUTL_CLEANUP_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 3);

    /// Test Pass!
    SUTL_TEST_SUCCESS( );
}


/// Move Assignment Test \\\

UnitTestResult TTLTests::Node::MoveAssignment( )
{
    TTL::Node<MemoryManagementHelper>* pNext = nullptr;
    TTL::Node<MemoryManagementHelper>* pNode = nullptr;
    TTL::Node<MemoryManagementHelper>* pMoveNode = nullptr;

    bool threw = false;

    SUTL_SETUP_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 0);

    try
    {
        pNext = new TTL::Node<MemoryManagementHelper>;
        pNode = new TTL::Node<MemoryManagementHelper>;
        pMoveNode = new TTL::Node<MemoryManagementHelper>;
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    pNode->SetNext(pNext);

    // Confirm Initial Test Conditions
    SUTL_SETUP_ASSERT(pNode->GetData( ).GetCopy( ) == false);
    SUTL_SETUP_ASSERT(pNode->GetData( ).GetMove( ) == false);
    SUTL_SETUP_ASSERT(pNode->GetNext( ) != nullptr);
    SUTL_SETUP_ASSERT(pNode->GetNext( ) == pNext);

    try
    {
        *pNode = std::move(*pNode);
    }
    catch ( const std::invalid_argument& )
    {
        threw = true;
    }

    SUTL_TEST_ASSERT(threw == true);

    *pMoveNode = std::move(*pNode);

    // Ensure values were transferred.
    SUTL_TEST_ASSERT(pNode->GetNext( ) == nullptr);
    SUTL_TEST_ASSERT(pMoveNode->GetData( ).GetCopy( ) == false);
    SUTL_TEST_ASSERT(pMoveNode->GetData( ).GetMove( ) == true);
    SUTL_TEST_ASSERT(pMoveNode->GetNext( ) == pNext);

    // Cleanup
    delete pNode;
    pNode = nullptr;
    delete pNext;
    pNext = nullptr;
    delete pMoveNode;
    pMoveNode = nullptr;

    SUTL_CLEANUP_ASSERT(pNode == nullptr);
    SUTL_CLEANUP_ASSERT(pNext == nullptr);
    SUTL_CLEANUP_ASSERT(pMoveNode == nullptr);
    SUTL_CLEANUP_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 3);

    /// Test Pass!
    SUTL_TEST_SUCCESS( );
}


/// Setter Tests \\\

UnitTestResult TTLTests::Node::SetDataCopy( )
{
    TTL::Node<MemoryManagementHelper>* pNode = nullptr;

    SUTL_SETUP_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 0);

    try
    {
        MemoryManagementHelper copyHelper;
        pNode = new TTL::Node<MemoryManagementHelper>( );
        pNode->SetData(copyHelper);
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_SETUP_ASSERT(pNode != nullptr);

    // Ensure copy was used.
    SUTL_TEST_ASSERT(pNode->GetData( ).GetCopy( ) == true);
    SUTL_TEST_ASSERT(pNode->GetData( ).GetMove( ) == false);

    delete pNode;
    pNode = nullptr;

    SUTL_CLEANUP_ASSERT(pNode == nullptr);
    SUTL_CLEANUP_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 2);

    /// Test Pass!
    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::Node::SetDataMove( )
{
    TTL::Node<MemoryManagementHelper>* pNode = nullptr;

    SUTL_SETUP_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 0);

    try
    {
        MemoryManagementHelper copyHelper;
        pNode = new TTL::Node<MemoryManagementHelper>( );
        pNode->SetData(std::move(copyHelper));
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    SUTL_SETUP_ASSERT(pNode != nullptr);

    // Ensure copy was used.
    SUTL_TEST_ASSERT(pNode->GetData( ).GetCopy( ) == false);
    SUTL_TEST_ASSERT(pNode->GetData( ).GetMove( ) == true);

    delete pNode;
    pNode = nullptr;

    SUTL_CLEANUP_ASSERT(pNode == nullptr);
    SUTL_CLEANUP_ASSERT(MemoryManagementHelper::ResetDeleteCount( ) == 2);

    /// Test Pass!
    SUTL_TEST_SUCCESS( );
}

UnitTestResult TTLTests::Node::SetNextRaw( )
{
    TTL::Node<int> node;
    TTL::Node<int>* pNext = nullptr;

    try
    {
        pNext = new TTL::Node<int>;
    }
    catch ( const std::exception& e )
    {
        SUTL_SETUP_EXCEPTION(e.what( ));
    }

    // Confirm Initial Test Conditions
    SUTL_SETUP_ASSERT(node.GetNext( ) == nullptr);
    SUTL_SETUP_ASSERT(pNext != nullptr);

    node.SetNext(pNext);

    // Ensure value was copied.
    SUTL_TEST_ASSERT(node.GetNext( ) != nullptr);
    SUTL_TEST_ASSERT(node.GetNext( ) == pNext);

    // Cleanup
    delete pNext;
    pNext = nullptr;

    SUTL_CLEANUP_ASSERT(pNext == nullptr);

    /// Test Pass!
    SUTL_TEST_SUCCESS( );
}