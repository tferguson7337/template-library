#pragma once

#include "Array.hpp"
#include "IDynamicArray.h"

namespace TTL
{
    template <class T>
    class DynamicArray : public virtual IDynamicArray<T>, public Array<T>
    {
    private:
        size_t mSize;
        static const size_t mDefaultCap = 8;

        /// Private Helper \\\

        void Shrink( )
        {
            if ( mSize == 0 )
            {
                Clear( );
                return;
            }

            ExclusivePointer<T[ ]> newArr(new T[mSize]);

            for ( size_t i = 0; i < mSize; i++ )
            {
                newArr[i] = Array<T>::mArr[i];
            }

            Array<T>::mArr = std::move(newArr);
            Array<T>::mCapacity = mSize;
        }

        void Grow( )
        {
            const size_t newCap = (Array<T>::mCapacity == 0) ? mDefaultCap : ((Array<T>::mCapacity * 3) >> 1);

            ExclusivePointer<T[ ]> newArr(new T[newCap]);

            for ( size_t i = 0; i < mSize; i++ )
            {
                newArr[i] = Array<T>::mArr[i];
            }

            Array<T>::mArr = std::move(newArr);
            Array<T>::mCapacity = newCap;
        }

    public:
        /// Ctors \\\
        
        // Default
        explicit DynamicArray( ) noexcept :
            Array<T>( ),
            mSize(0ull)
        { }

        // Capacity
        explicit DynamicArray(const size_t cap) :
            Array<T>(cap),
            mSize(0ull)
        { }

        // Copy
        DynamicArray(const DynamicArray& src) :
            Array<T>(src),
            mSize(src.mSize)
        { }

        // Move
        DynamicArray(DynamicArray&& src) noexcept :
            Array<T>(std::move(src)),
            mSize(src.mSize)
        {
            src.mSize = 0ull;
        }

        /// Dtor \\\

        ~DynamicArray( ) = default;

        /// Assignment Overloads \\\

        // Copy
        DynamicArray& operator=(const DynamicArray& src)
        {
            Array<T>::operator=(src);
            mSize = src.mSize;

            return *this;
        }

        // Move
        DynamicArray& operator=(DynamicArray&& src)
        {
            Array<T>::operator=(std::move(src));
            mSize = src.mSize;
            src.mSize = 0;

            return *this;
        }

        /// Subscript Overload \\\

        inline T& operator[](size_t index)
        {
            if ( index >= mSize )
            {
                throw std::out_of_range("TTL::Array<T>::operator[](size_t) - Attempted to access memory beyond array boundaries.");
            }

            return Array<T>::mArr[index];
        }

        inline const T& operator[](size_t index) const
        {
            if ( index >= mSize )
            {
                throw std::out_of_range("TTL::Array<T>::operator[](size_t) - Attempted to access memory beyond array boundaries.");
            }

            return Array<T>::mArr[index];
        }

        /// Getters \\\

        static inline size_t DefaultCapacity( ) noexcept
        {
            return mDefaultCap;
        }

        inline size_t Size( ) const noexcept
        {
            return mSize;
        }

        inline bool Empty( ) const noexcept
        {
            return mSize == 0;
        }

        /// Public Methods \\\

        // Subscript Wrapper
        inline T& At(size_t index)
        {
            return operator[](index);
        }

        // Subscript Wrapper
        inline const T& At(size_t index) const
        {
            return operator[](index);
        }

        // Empty out the array.
        inline void Clear( ) noexcept
        {
            Array<T>::Clear( );
            mSize = 0;
        }

        // Copy element to the end of the array.
        inline void Append(const T& data)
        {
            if ( mSize == Array<T>::mCapacity )
            {
                Grow( );
            }

            Array<T>::mArr[mSize++] = data;
        }

        // Move element to the end of the array.
        inline void Append(T&& data)
        {
            if ( mSize == Array<T>::mCapacity )
            {
                Grow( );
            }

            Array<T>::mArr[mSize++] = std::move(data);
        }

        // Access front element of array.
        inline T& Front( )
        {
            if ( mSize == 0 )
            {
                throw std::out_of_range("TTL::DynamicArray<T>::Front( ) - Attempted to access empty array.");
            }

            return Array<T>::mArr[0];
        }

        inline const T& Front( ) const
        {
            if ( mSize == 0 )
            {
                throw std::out_of_range("TTL::DynamicArray<T>::Front( ) - Attempted to access empty array.");
            }

            return Array<T>::mArr[0];
        }

        // Access last element of array.
        inline T& Back( )
        {
            if ( mSize == 0 )
            {
                throw std::out_of_range("TTL::DynamicArray<T>::Back( ) - Attempted to access empty array.");
            }

            return Array<T>::mArr[mSize - 1];
        }

        inline const T& Back( ) const
        {
            if ( mSize == 0 )
            {
                throw std::out_of_range("TTL::DynamicArray<T>::Back( ) - Attempted to access empty array.");
            }

            return Array<T>::mArr[mSize - 1];
        }

        // Remove extra space (make capacity == size).
        inline void Compress( )
        {
            if ( mSize == Array<T>::mCapacity )
            {
                return;
            }

            Shrink( );
        }

        // Attempt to increase the array's capacity to amount specified via arg.
        inline void Reserve(const size_t newCap)
        {
            ExclusivePointer<T[ ]> arr;

            if ( newCap <= Array<T>::mCapacity )
            {
                return;
            }

            // Try to allocate new array.
            try
            {
                arr.Set(new T[newCap]);
            }
            catch ( const std::exception& )
            {
                return;
            }

            // Move data to new array.
            for ( size_t i = 0; i < mSize; i++ )
            {
                arr[i] = std::move(Array<T>::mArr[i]);
            }

            // Update member variables.
            Array<T>::mArr.Set(std::move(arr));
            Array<T>::mCapacity = newCap;
        }
    };
}