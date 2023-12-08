/**
 * @file    ICompareStrategy.hpp
 * @date    2023-12-08
 * @author  Andri Trottmann
 */

#pragma once

/**
 * @brief Template interface for comparison strategy
*/
template<typename T>
class ICompareStrategy
{
    public:
        virtual bool equals(const T& t1, const T& t2) = 0;
        virtual bool nonEquals(const T& t1, const T& t2) = 0;
        virtual bool lesserThan(const T& t1, const T& t2) = 0;
        virtual bool greaterThan(const T& t1, const T& t2) = 0;
        virtual bool lessOrEqual(const T& t1, const T& t2) = 0;
        virtual bool greatOrEqual(const T& t1, const T& t2) = 0;
};
