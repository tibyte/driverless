#pragma once


class PID
{

public:
    bool prescale_flag = false;

    float data;
    float scale;
    float error_total;
    float goal=0.0f;
    float p_error=0.0f;
    float error=0.0f;
    float error_integral=0.0f;
    float filtering=0.0f;
    float pre_scale;
    //initial value setting

    float cycle_time=0.015f;
    //1cycle time setting

    float alpha=0.05f;
    //filtering alpha value

    float Kp=6.0f;
    float Ki=1.5f;
    float Kd=0.5f;
    //P, I, D setting

	float coef = 3.0f;
    float steering;


	PID();
	~PID();
	int init();
    int process(float input);

};
