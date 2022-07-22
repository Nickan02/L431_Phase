
#ifndef __Filter_H_
#define __Filter_H_
#include "arm_math.h"
#define Contains_Symbols 1 //当返回值有小数时为1 无小数为0(默认为0)

#if Contains_Symbols  
typedef float  Type_IN;
typedef float  Type_OUT; 
#else  
typedef int  Type_IN;
typedef int  Type_OUT; 
#endif
/*单纯用限幅滤波没有作用*/
Type_OUT Clipping_filter(unsigned int Amplitude,Type_IN get_ad);//限幅滤波Amplitude值根据实际调
Type_OUT Limiting_Debounce_Filtering(unsigned int N,unsigned int A,Type_IN get_ad);//限幅消抖滤波
/*一般不用以上的滤波*/
                                //		    	1    1000
#define Precision	1000		//精度千分之一0.001~0
Type_OUT First_order_lag_filtering(unsigned int A,Type_IN get_ad);//一阶滞后滤波
Type_OUT First_order_lag_filtering1(unsigned int A,Type_IN get_ad);
	
Type_OUT Debounce_filtering(unsigned int N,Type_IN get_ad);//消抖滤波
Type_OUT Median_filter(unsigned int N,Type_IN get_ad);//中位值滤波
Type_OUT Arithmetic_Average_Filtering(unsigned int N,Type_IN get_ad);//算数平均滤波
Type_OUT Recursive_averaging_filter(unsigned int N,Type_IN get_ad);//递推平均滤波
Type_OUT Median_Average_Filtering(unsigned int N,Type_IN get_ad);//中位值平均滤波
Type_OUT Weighted_recursive_average_filtering(unsigned int N,Type_IN get_ad);//加权递推平均滤波
Type_OUT ABS(Type_IN n);//取绝对值函数

typedef struct 
{
    float Last_P;//上次估算协方差 不可以为0 ! ! ! ! ! 
    float Now_P;//当前估算协方差
    float out;//卡尔曼滤波器输出
    float Kg;//卡尔曼增益
    float Q;//过程噪声协方差
    float R;//观测噪声协方差
}Kalman;
// void KalmanFilter_Init(float Last_P,//上次估算协方差 不可以为0 ! ! ! ! ! 
//     float Now_P,//当前估算协方差
//     float out,//卡尔曼滤波器输出
//     float Kg,//卡尔曼增益
//     float Q,//过程噪声协方差
//     float R);//观测噪声协方差)
//extern Kalman Kalman_INIT;
//float KalmanFilter(Kalman *kfp,float input);

#define FFT_N 16                                        //定义傅里叶变换的点数
//#define PI 3.1415926                                    //定义圆周率值
struct compx { double real, imag; };                    //定义一个复数结构
extern struct compx Compx[];							//FFT输入和输出：从Compx[0]开始存放，根据大小自己定义
extern double SIN_TAB[];								//正弦信号表
extern void Refresh_Data(struct compx *xin, int id, double wave_data);
extern void create_sin_tab(double *sin_t);
extern void FFT(struct compx *xin);
extern void Get_Result(struct compx *xin, double sample_frequency);

#endif

