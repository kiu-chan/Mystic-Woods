#ifndef TIME_H
#define TIME_H



class Time
{
    public:
    Time();
    ~Time();

    void start();

    int getTicks();


    private:
    int start_tick;
    int pause_tick;

    bool is_paused;
    bool is_started;
};



#endif