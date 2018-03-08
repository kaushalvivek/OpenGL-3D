#ifndef TIMER_H
#define TIMER_H


class Timer {
public:
    Timer() {
        prev = 0;
    }
    Timer(float interval);
    float interval;
    bool processTick();
private:
    float prev;
};

#endif // TIMER_H
