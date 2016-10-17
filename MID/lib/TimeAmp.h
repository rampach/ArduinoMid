//
// Created by Angel Zaprianov on 29.9.2016 г..
//
#include <Arduino.h>

#ifndef ARDUINOMID_TIMEAMP_H
#define ARDUINOMID_TIMEAMP_H


#if !defined(MILLIS_SENS)
#define MILLIS_SENS 200
#endif

#if !defined(MILLIS_PER_HR)
#define MILLIS_PER_HR 3600000
#endif

#if !defined(MILLIS_PER_MN)
#define MILLIS_PER_MN 60000
#endif

#if !defined(MILLIS_PER_SC)
#define MILLIS_PER_SC 1000
#endif

/** @description
 *
 */
class TimeAmp {

private:
    unsigned long timer;
    unsigned long curLow = 0, curSec = 0, curMid = 0, curMin = 0, curBig = 0, curMax = 0;
    long int ampLow = 0, ampSec = 0, ampMid = 0, ampMin = 0, ampBig = 0, ampMax = 0;
    long int _isLow = 0, _isSec = 0, _isMid = 0, _isMin = 0, _isBig = 0, _isMax = 0;
    long int _isSecond = 0, _isMinute = 0, _isHour = 0, _isSens = 0;
    long int curSecond = 0, curMinute = 0, curHour = 0, curSens = 0;

    /**
     * MAX 1,193,046 Hour	(h)
     */
    unsigned long loopCounter = 0;
public:
    TimeAmp(int intervalMin, int intervalLow, int intervalMid, int intervalSec, int intervalBig, int intervalMax);

    void listener();

    unsigned long getLoopIndex() { return loopCounter; }

    bool isLow() { return (boolean) _isLow; }

    bool isMin() { return (boolean) _isMin; }

    bool isSec() { return (boolean) _isSec; }

    bool isMid() { return (boolean) _isMid; }

    bool isBig() { return (boolean) _isBig; }

    bool isMax() { return (boolean) _isMax; }

    /************** Real Time *********************/

    bool isSecond() { return (boolean) _isSecond; }

    bool isMinute() { return (boolean) _isMinute; }

    bool isHour() { return (boolean) _isHour; }

    bool isSens() { return (boolean) _isSens; }

    void setTimer(unsigned long time);


};


/***********************************************************************************************
 *                                                                                             *
 *                                   CPP part of file                                          *
 *                                                                                             *
 ***********************************************************************************************/


TimeAmp::TimeAmp(int intervalMin, int intervalLow, int intervalMid, int intervalSec, int intervalBig, int intervalMax) {

    ampMin = intervalMin;
    ampLow = intervalLow;
    ampSec = intervalSec;
    ampMid = intervalMid;
    ampBig = intervalBig;
    ampMax = intervalMax;

}

/**
 * Sets external timer
 */
void TimeAmp::setTimer(unsigned long time) {
    timer = time;
}

/**
 * Listen cases
 */
void TimeAmp::listener() {

    unsigned long curIndex = loopCounter;

    if (curIndex >= curMin + ampMin) {
        curMin = curIndex;
        _isMin = 1;
    } else {
        _isMin = 0;
    }

    if (curIndex >= curLow + ampLow) {
        curLow = curIndex;
        _isLow = 1;
    } else {
        _isLow = 0;
    }


    if (curIndex >= curSec + ampSec) {
        curSec = curIndex;
        _isSec = 1;
    } else {
        _isSec = 0;
    }

    if (curIndex >= curMid + ampMid) {
        curMid = curIndex;
        _isMid = 1;
    } else {
        _isMid = 0;
    }

    if (curIndex >= curBig + ampBig) {
        curBig = curIndex;
        _isBig = 1;
    } else {
        _isBig = 0;
    }

    if (curIndex >= curMax + ampMax) {
        curMax = curIndex;
        _isMax = 1;
    } else {
        _isMax = 0;
    }

    loopCounter++;

    /************** Real Time *********************/

    if (timer >= curSecond + MILLIS_PER_SC) {
        curSecond = timer;
        _isSecond = 1;
    } else {
        _isSecond = 0;
    }

    if (timer >= curSecond + MILLIS_PER_MN) {
        curMinute = timer;
        _isMinute = 1;
    } else {
        _isMinute = 0;
    }

    if (timer >= curSecond + MILLIS_PER_HR) {
        curHour = timer;
        _isHour = 1;
    } else {
        _isHour = 0;
    }

    if (timer >= curSens + MILLIS_SENS) {
        curSens = timer;
        _isSens = 1;
    } else {
        _isSens = 0;
    }


};
#endif //ARDUINOMID_TIMEAMP_H
