// FILE: statistician.cpp
// CLASS IMPLEMENTED: statistician (see stats.h for documentation)

#include <iostream>  // Provides istream class
#include "statistician.h"

using namespace std;

namespace coen79_lab2
{
    statistician operator +(const statistician& s1, const statistician& s2);

    void statistician::next(double r) {
        mySum += r;
        myLen++;
        myMin = r < myMin ? r : myMin;
        myMax = r > myMax ? r : myMax;
    }

    void statistician::reset() {
        mySum = 0;
        myLen = 0;
        myMin = INFINITY;
        myMax = -INFINITY;
    }

    statistician operator +(const statistician& s1, const statistician& s2) {
        statistician newS;

        int newLen = s1.length() + s2.length();
        double newSum = s1.sum() + s2.sum();
        double newMean = newSum / newLen;
        double newMin = s1.minimum() < s2.minimum() ? s1.minimum() : s2.minimum();
        double newMax = s1.maximum() > s2.maximum() ? s1.maximum() : s2.maximum();

        //adds the new minimum and new maximum to the sequence
        newS.next(newMin);
        newS.next(newMax);

        //adds numbers to the sequence so that the length, sum, and mean are correct
        for(int i = 0; i < newLen - 2; i++)
            newS.next((newSum - newMax - newMin) / (newLen - 2));

        return newS;
    }

    statistician operator *(double scale, const statistician& s) {
        statistician newS;

        int newLen = s.length();
        double newSum = scale * s.sum();
        double newMean = scale * s.mean();
        double newMin = scale >= 0 ? scale * s.minimum() : scale * s.maximum();
        double newMax = scale >= 0 ? scale * s.maximum() : scale * s.minimum();

        //adds the new minimum and new maximum to the sequence
        newS.next(newMin);
        newS.next(newMax);

        //adds numbers to the sequence so that the length, sum, and mean are correct
        for(int i = 0; i < newLen - 2; i++)
            newS.next((newSum - newMax - newMin) / (newLen - 2));

        return newS;
    }

    bool operator ==(const statistician& s1, const statistician& s2) {
        return (
            (s1.length() == 0 && s2.length() == 0) ||

            (
                s1.length() == s2.length() &&
                s1.sum() == s2.sum() &&
                s1.mean() == s2.mean() &&
                s1.minimum() == s2.minimum() &&
                s1.maximum() == s2.maximum()
            )
        );
    }
}


// [-1, 4, 6, 7, 8]             length=5        sum=24      mean=24/5
// [-1, 8, 17/3, 17/3, 17/3]    length=5        sum=24      mean=24/5