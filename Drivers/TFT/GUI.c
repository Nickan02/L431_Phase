
#include "Lcd_Driver.h"
#include "GUI.h"
#include "delay.h"
#include "font.h"

uint16_t LCD_BGR2RGB(uint16_t c)
{
    uint16_t  r,g,b,rgb;
    b=(c>>0)&0x1f;
    g=(c>>5)&0x3f;
    r=(c>>11)&0x1f;
    rgb=(b<<11)+(g<<5)+(r<<0);
    return(rgb);

}




void Gui_Circle(uint16_t X,uint16_t Y,uint16_t R,uint16_t fc)
{   //Bresenham算法
    unsigned short  a,b;
    int c;
    a=0;
    b=R;
    c=3-2*R;
    while (a<b)
    {
        Gui_DrawPoint(X+a,Y+b,fc);     //        7
        Gui_DrawPoint(X-a,Y+b,fc);     //        6
        Gui_DrawPoint(X+a,Y-b,fc);     //        2
        Gui_DrawPoint(X-a,Y-b,fc);     //        3
        Gui_DrawPoint(X+b,Y+a,fc);     //        8
        Gui_DrawPoint(X-b,Y+a,fc);     //        5
        Gui_DrawPoint(X+b,Y-a,fc);     //        1
        Gui_DrawPoint(X-b,Y-a,fc);     //        4

        if(c<0) c=c+4*a+6;
        else
        {
            c=c+4*(a-b)+10;
            b-=1;
        }
        a+=1;
    }
    if (a==b)
    {
        Gui_DrawPoint(X+a,Y+b,fc);
        Gui_DrawPoint(X+a,Y+b,fc);
        Gui_DrawPoint(X+a,Y-b,fc);
        Gui_DrawPoint(X-a,Y-b,fc);
        Gui_DrawPoint(X+b,Y+a,fc);
        Gui_DrawPoint(X-b,Y+a,fc);
        Gui_DrawPoint(X+b,Y-a,fc);
        Gui_DrawPoint(X-b,Y-a,fc);
    }

}
//画线函数，使用Bresenham 画线算法
void Gui_DrawLine(uint16_t x0, uint16_t y0,uint16_t x1, uint16_t y1,uint16_t Color)
{
    int dx,             // difference in x's
        dy,             // difference in y's
        dx2,            // dx,dy * 2
        dy2,
        x_inc,          // amount in pixel space to move during drawing
        y_inc,          // amount in pixel space to move during drawing
        error,          // the discriminant i.e. error i.e. decision variable
        index;          // used for looping


    Lcd_SetXY(x0,y0);
    dx = x1-x0;//计算x距离
    dy = y1-y0;//计算y距离

    if (dx>=0)
    {
        x_inc = 1;
    }
    else
    {
        x_inc = -1;
        dx    = -dx;
    }

    if (dy>=0)
    {
        y_inc = 1;
    }
    else
    {
        y_inc = -1;
        dy    = -dy;
    }

    dx2 = dx << 1;
    dy2 = dy << 1;

    if (dx > dy)//x距离大于y距离，那么每个x轴上只有一个点，每个y轴上有若干个点
    {   //且线的点数等于x距离，以x轴递增画点
        // initialize error term
        error = dy2 - dx;

        // draw the line
        for (index=0; index <= dx; index++)//要画的点数不会超过x距离
        {
            //画点
            Gui_DrawPoint(x0,y0,Color);

            // test if error has overflowed
            if (error >= 0) //是否需要增加y坐标值
            {
                error-=dx2;

                // move to next line
                y0+=y_inc;//增加y坐标值
            } // end if error overflowed

            // adjust the error term
            error+=dy2;

            // move to the next pixel
            x0+=x_inc;//x坐标值每次画点后都递增1
        } // end for
    } // end if |slope| <= 1
    else//y轴大于x轴，则每个y轴上只有一个点，x轴若干个点
    {   //以y轴为递增画点
        // initialize error term
        error = dx2 - dy;

        // draw the line
        for (index=0; index <= dy; index++)
        {
            // set the pixel
            Gui_DrawPoint(x0,y0,Color);

            // test if error overflowed
            if (error >= 0)
            {
                error-=dy2;

                // move to next line
                x0+=x_inc;
            } // end if error overflowed

            // adjust the error term
            error+=dx2;

            // move to the next pixel
            y0+=y_inc;
        } // end for
    } // end else |slope| > 1
}



void Gui_box(uint16_t x, uint16_t y, uint16_t w, uint16_t h,uint16_t bc)
{
    Gui_DrawLine(x,y,x+w,y,0xEF7D);
    Gui_DrawLine(x+w-1,y+1,x+w-1,y+1+h,0x2965);
    Gui_DrawLine(x,y+h,x+w,y+h,0x2965);
    Gui_DrawLine(x,y,x,y+h,0xEF7D);
    Gui_DrawLine(x+1,y+1,x+1+w-2,y+1+h-2,bc);
}
void Gui_box2(uint16_t x,uint16_t y,uint16_t w,uint16_t h, uint8_t mode)
{
    if (mode==0)	{
        Gui_DrawLine(x,y,x+w,y,0xEF7D);
        Gui_DrawLine(x+w-1,y+1,x+w-1,y+1+h,0x2965);
        Gui_DrawLine(x,y+h,x+w,y+h,0x2965);
        Gui_DrawLine(x,y,x,y+h,0xEF7D);
    }
    if (mode==1)	{
        Gui_DrawLine(x,y,x+w,y,0x2965);
        Gui_DrawLine(x+w-1,y+1,x+w-1,y+1+h,0xEF7D);
        Gui_DrawLine(x,y+h,x+w,y+h,0xEF7D);
        Gui_DrawLine(x,y,x,y+h,0x2965);
    }
    if (mode==2)	{
        Gui_DrawLine(x,y,x+w,y,0xffff);
        Gui_DrawLine(x+w-1,y+1,x+w-1,y+1+h,0xffff);
        Gui_DrawLine(x,y+h,x+w,y+h,0xffff);
        Gui_DrawLine(x,y,x,y+h,0xffff);
    }
}


/**************************************************************************************
功能描述: 在屏幕显示一凸起的按钮框
输    入: uint16_t x1,y1,x2,y2 按钮框左上角和右下角坐标
输    出: 无
**************************************************************************************/
void DisplayButtonDown(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
    Gui_DrawLine(x1,  y1,  x2,y1, GRAY2);  //H
    Gui_DrawLine(x1+1,y1+1,x2,y1+1, GRAY1);  //H
    Gui_DrawLine(x1,  y1,  x1,y2, GRAY2);  //V
    Gui_DrawLine(x1+1,y1+1,x1+1,y2, GRAY1);  //V
    Gui_DrawLine(x1,  y2,  x2,y2, WHITE);  //H
    Gui_DrawLine(x2,  y1,  x2,y2, WHITE);  //V
}

/**************************************************************************************
功能描述: 在屏幕显示一凹下的按钮框
输    入: uint16_t x1,y1,x2,y2 按钮框左上角和右下角坐标
输    出: 无
**************************************************************************************/
void DisplayButtonUp(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
    Gui_DrawLine(x1,  y1,  x2,y1, WHITE); //H
    Gui_DrawLine(x1,  y1,  x1,y2, WHITE); //V

    Gui_DrawLine(x1+1,y2-1,x2,y2-1, GRAY1);  //H
    Gui_DrawLine(x1,  y2,  x2,y2, GRAY2);  //H
    Gui_DrawLine(x2-1,y1+1,x2-1,y2, GRAY1);  //V
    Gui_DrawLine(x2,y1,x2,y2, GRAY2);     //V
}


void Gui_DrawFont_GBK16(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, char *s)
{
    unsigned char i,j;
    unsigned short k,x0;
    x0=x;

    while(*s)
    {
        if((*s) < 128)
        {
            k=*s;
            if (k==13)
            {
                x=x0;
                y+=16;
            }
            else
            {
                if (k>32) k-=32;
                else k=0;

                for(i=0; i<16; i++)
                    for(j=0; j<8; j++)
                    {
                        if(asc16[k*16+i]&(0x80>>j))	Gui_DrawPoint(x+j,y+i,fc);
                        else
                        {
                            if (fc!=bc) Gui_DrawPoint(x+j,y+i,bc);
                        }
                    }
                x+=8;
            }
            s++;
        }

        else
        {


            for (k=0; k<hz16_num; k++)
            {
                if ((hz16[k].Index[0]==*(s))&&(hz16[k].Index[1]==*(s+1)))
                {
                    for(i=0; i<16; i++)
                    {
                        for(j=0; j<8; j++)
                        {
                            if(hz16[k].Msk[i*2]&(0x80>>j))	Gui_DrawPoint(x+j,y+i,fc);
                            else {
                                if (fc!=bc) Gui_DrawPoint(x+j,y+i,bc);
                            }
                        }
                        for(j=0; j<8; j++)
                        {
                            if(hz16[k].Msk[i*2+1]&(0x80>>j))	Gui_DrawPoint(x+j+8,y+i,fc);
                            else
                            {
                                if (fc!=bc) Gui_DrawPoint(x+j+8,y+i,bc);
                            }
                        }
                    }
                }
            }
            s+=2;
            x+=16;
        }

    }
}

void Gui_DrawFont_GBK24(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *s)
{
    unsigned char i,j;
    unsigned short k;

    while(*s)
    {
        if( *s < 0x80 )
        {
            k=*s;
            if (k>32) k-=32;
            else k=0;

            for(i=0; i<16; i++)
                for(j=0; j<8; j++)
                {
                    if(asc16[k*16+i]&(0x80>>j))
                        Gui_DrawPoint(x+j,y+i,fc);
                    else
                    {
                        if (fc!=bc) Gui_DrawPoint(x+j,y+i,bc);
                    }
                }
            s++;
            x+=8;
        }
        else
        {

            for (k=0; k<hz24_num; k++)
            {
                if ((hz24[k].Index[0]==*(s))&&(hz24[k].Index[1]==*(s+1)))
                {
                    for(i=0; i<24; i++)
                    {
                        for(j=0; j<8; j++)
                        {
                            if(hz24[k].Msk[i*3]&(0x80>>j))
                                Gui_DrawPoint(x+j,y+i,fc);
                            else
                            {
                                if (fc!=bc) Gui_DrawPoint(x+j,y+i,bc);
                            }
                        }
                        for(j=0; j<8; j++)
                        {
                            if(hz24[k].Msk[i*3+1]&(0x80>>j))	Gui_DrawPoint(x+j+8,y+i,fc);
                            else {
                                if (fc!=bc) Gui_DrawPoint(x+j+8,y+i,bc);
                            }
                        }
                        for(j=0; j<8; j++)
                        {
                            if(hz24[k].Msk[i*3+2]&(0x80>>j))
                                Gui_DrawPoint(x+j+16,y+i,fc);
                            else
                            {
                                if (fc!=bc) Gui_DrawPoint(x+j+16,y+i,bc);
                            }
                        }
                    }
                }
            }
            s+=2;
            x+=24;
        }
    }
}
void Gui_DrawFont_Num32(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint16_t num)
{
    unsigned char i,j,k,c;
    //lcd_text_any(x+94+i*42,y+34,32,32,0x7E8,0x0,sz32,knum[i]);
//	w=w/8;

    for(i=0; i<32; i++)
    {
        for(j=0; j<4; j++)
        {
            c=*(sz32+num*32*4+i*4+j);
            for (k=0; k<8; k++)
            {

                if(c&(0x80>>k))	Gui_DrawPoint(x+j*8+k,y+i,fc);
                else {
                    if (fc!=bc) Gui_DrawPoint(x+j*8+k,y+i,bc);
                }
            }
        }
    }
}
//******************************************************************
//函数名：  LCD_ShowChar
//功能：    显示单个英文字符
//输入参数：(x,y):字符显示位置起始坐标
//        	fc:前置画笔颜色
//			bc:背景颜色
//			num:数值（0-94）
//			size:字体大小
//			mode:模式  0,填充模式;1,叠加模式
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_ShowChar(uint16_t x,uint16_t y,uint16_t fc, uint16_t bc, uint8_t num,uint8_t size,uint8_t mode)
{
    uint8_t temp;
    uint8_t pos,t;


    num=num-' ';//得到偏移后的值
    Lcd_SetRegion(x,y,x+size/2-1,y+size-1);//设置单个文字显示窗口
    if(!mode) //非叠加方式
    {

        for(pos=0; pos<size; pos++)
        {
            if(size==12)temp=asc2_1206[num][pos];//调用1206字体
            else temp=asc2_1608[num][pos];		 //调用1608字体
            for(t=0; t<size/2; t++)
            {
                if(temp&0x01)Lcd_WriteData(bc);
                else Lcd_WriteData(fc);
                temp>>=1;

            }

        }
    } else//叠加方式
    {
        for(pos=0; pos<size; pos++)
        {
            if(size==12)temp=asc2_1206[num][pos];//调用1206字体
            else temp=asc2_1608[num][pos];		 //调用1608字体
            for(t=0; t<size/2; t++)
            {

                if(temp&0x01)Gui_DrawPoint(x+t,y+pos,fc);//画一个点
                else Gui_DrawPoint(x+t,y+pos,bc);
                temp>>=1;
            }
        }
    }
    Lcd_SetRegion(0,0,128-1,128-1);//恢复窗口为全屏
}

void Show_Str(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *str,uint8_t size,uint8_t mode)
{
    uint16_t x0=x;
    uint8_t bHz=0;     //字符或者中文
    while(*str!=0)//数据未结束
    {
        if(!bHz)
        {
            if(x>(128-size/2)||y>(128-size))
                return;
            if(*str>0x80)bHz=1;//中文
            else              //字符
            {
                if(*str==0x0D||x>112)//换行符号
                {
                    y+=size;
                    x=x0;
//                    str++;
                }
                else
                {
                    if(size==12||size==16)
                    {
                        LCD_ShowChar(x,y,fc,bc,*str,size,mode);
                        x+=size/2; //字符,为全字的一半
                    }
                    else//字库中没有集成16X32的英文字体,用8X16代替
                    {
                        LCD_ShowChar(x,y,fc,bc,*str,16,mode);
                        x+=8; //字符,为全字的一半
                    }
                }
                str++;

            }
        }//中文

//			if(x>(128-size)||y>(128-size))
//			return;
//            bHz=0;//有汉字库
//			if(size==32)
//			GUI_DrawFont32(x,y,fc,bc,str,mode);
//			else if(size==24)
//			GUI_DrawFont24(x,y,fc,bc,str,mode);
//			else
//			GUI_DrawFont16(x,y,fc,bc,str,mode);
//
//	        str+=2;
//	        x+=size;//下一个汉字偏移 uint16_t x,uint16_t y,uint16_t fc, uint16_t bc, uint8_t num,uint8_t size,uint8_t mode

    }
}
//******************************************************************
//函数名：  LCD_ShowChar
//功能：    局部显示数字顺序从个位到十位显示
//输入参数：(x,y):字符显示位置起始坐标
//        	fc:前置画笔颜色BLUE
//			bc:背景颜色GRAY1
//			num:支持16位数
//			size:字体大小
//			mode:模式 1,叠加模式
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_ShowNum(uint16_t x,uint16_t y,u32 num,u8 len,u8 size)
{
    unsigned char i,k[len];
    //lcd_text_any(x+94+i*42,y+34,32,32,0x7E8,0x0,sz32,knum[i]);
//	w=w/8;
    uint32_t j=1;
		x=x+((len-1)*size/2);
    for(i=0; i<len; i++)
    {
        k[i]=num/j%10; // 3g 2s 1b 0q
        j=j*10;
				if(size==12||size==16)
        {
            LCD_ShowChar(x,y,BLUE,GRAY1,k[i]+'0',size,1);
            x-=size/2; //字符,为全字的一半
        }
        else//字库中没有集成16X32的英文字体,用8X16代替
        {
            LCD_ShowChar(x,y,BLUE,GRAY1,k[i]+'0',size,1);
            x-=8; //字符,为全字的一半
        }
    }

}

