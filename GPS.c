#include <stdio.h>
#include <stdlib.h>
#include<string.h>
/*
题目内容：

NMEA-0183协议是为了在不同的GPS（全球定位系统）导航设备中建立统一的BTCM（海事无线电技术委员会）标准，
由美国国家海洋电子协会（NMEA-The National Marine Electronics Associa-tion）制定的一套通讯协议。
GPS接收机根据NMEA-0183协议的标准规范，将位置、速度等信息通过串口传送到PC机、PDA等设备。



NMEA-0183协议是GPS接收机应当遵守的标准协议，
也是目前GPS接收机上使用最广泛的协议，
大多数常见的GPS接收机、GPS数据处理软件、导航软件都遵守或者至少兼容这个协议。



NMEA-0183协议定义的语句非常多，
但是常用的或者说兼容性最广的语句只有$GPGGA、$GPGSA、$GPGSV、$GPRMC、$GPVTG、$GPGLL等。



其中$GPRMC语句的格式如下：

    $GPRMC,024813.640,A,3158.4608,N,11848.3737,E,10.05,324.27,150706,,,A*50



这里整条语句是一个文本行，行中以逗号“,”隔开各个字段，
每个字段的大小（长度）不一，这里的示例只是一种可能，并不能认为字段的大小就如上述例句一样。

    字段0：$GPRMC，语句ID，表明该语句为Recommended Minimum Specific GPS/TRANSIT Data（RMC）推荐最小定位信息
    字段1：UTC时间，hhmmss.sss格式
    字段2：状态，A=定位，V=未定位
    字段3：纬度ddmm.mmmm，度分格式（前导位数不足则补0）
    字段4：纬度N（北纬）或S（南纬）
    字段5：经度dddmm.mmmm，度分格式（前导位数不足则补0）
    字段6：经度E（东经）或W（西经）
    字段7：速度，节，Knots
    字段8：方位角，度
    字段9：UTC日期，DDMMYY格式
    字段10：磁偏角，（000 - 180）度（前导位数不足则补0）
    字段11：磁偏角方向，E=东W=西
    字段16：校验值

这里，“*”为校验和识别符，其后面的两位数为校验和，
代表了“$”和“*”之间所有字符（不包括这两个字符）的异或值的十六进制值。
上面这条例句的校验和是十六进制的50，也就是十进制的80。



提示：^运算符的作用是异或。
将$和*之间所有的字符做^运算
(第一个字符和第二个字符异或，结果再和第三个字符异或，依此类推)
之后的值对65536取余后的结果，应该和*后面的两个十六进制数字的值相等，
否则的话说明这条语句在传输中发生了错误。
注意这个十六进制值中是会出现A-F的大写字母的。



现在，你的程序要读入一系列GPS输出，其中包含$GPRMC，也包含其他语句。
在数据的最后，有一行单独的

    END

表示数据的结束。



你的程序要从中找出$GPRMC语句，计算校验和，找出其中校验正确，
并且字段2表示已定位的语句，从中计算出时间，换算成北京时间。
一次数据中会包含多条$GPRMC语句，以最后一条语句得到的北京时间作为结果输出。

你的程序一定会读到一条有效的$GPRMC语句。



输入格式:

多条GPS语句，每条均以回车换行结束。最后一行是END三个大写字母。



输出格式：

6位数时间，表达为：

    hh:mm:ss

其中，hh是两位数的小时，不足两位时前面补0；
mm是两位数的分钟，不足两位时前面补0；
ss是两位数的秒，不足两位时前面补0。



输入样例：
$GPRMC,024813.640,A,3158.4608,N,11848.3737,E,10.05,324.27,150706,,,A*50
END




输出样例：

10:48:13
*/

typedef struct
{
	//字段0：$GPRMC，语句ID，表明该语句为Recommended Minimum Specific GPS/TRANSIT Data（RMC）推荐最小定位信息
	char *ID;
    //字段1：UTC时间，hhmmss.sss格式
    char *UTC;
    //字段16：校验值
    int CalibrationValue;
}GPRMC;

typedef struct
{
    int hh;
    int mm;
    int ss;
} TIME;

TIME UTC2BJT(TIME time);

int main(int argc, char *argv[]) {
    GPRMC gprmc;
    do{
        char str[200];
        char *UTC_time;
        char *state;
        scanf("%s",str);
        printf("字符串%s\n",str);
        char* str1;//校验符前
        char* str2;//校验符
        gprmc.ID=strtok(str, ",");
        UTC_time=strtok(NULL, ",");
        state=strtok(NULL, ",");
        str1=strtok(NULL, "*");
        str2=strtok(NULL," ");
        printf("str2:%s\n",str2);
        int str3[2];
        str3[0]=(int)str2[0]-48;
        str3[1]=(int)str2[1]-48;
        //gprmc.CalibrationValue=str3[0]*16+str3[1];
        printf("gprmc.CalibrationValue:%s\n",str3[0]*16+str3[1]);
        printf("ID:%s\n",gprmc.ID);
        printf("UTC_time:%s\n",UTC_time);
        printf("state:%s\n",state);
        printf("gprmc.CalibrationValue:%s\n",gprmc.CalibrationValue);
        //找出GPRMC语句
        if(!strcmp(gprmc.ID, "$GPRMC"))
        {
            //判断是否已定位
            if(state[0]=='A')
            {
                //校验值判断
                if(gprmc.CalibrationValue==Calibration(str))
                {
                    gprmc.UTC=UTC_time;
                    printf("gprmc.UTC:%s\n",gprmc.UTC);
                }
            }
            else
            {
                scanf("%d");
            }
        }
        else
        {
            scanf("%[^\n]");
        }
    }
    while(gprmc.ID=="END");
    //把六位整数拆成三个两位整数作为时间
    int utc;
    TIME UTC;
    sscanf(gprmc.UTC,"%d",&utc);
    printf("utc:%s\n",utc);
    UTC.hh=utc/10000;
    UTC.mm=utc%10000/100;
    UTC.ss=utc%100;
    printf("%.2d:%.2d:%.2d\n",UTC.hh,UTC.mm,UTC.ss);
    //UTC时间转换成北京时间
	TIME BJT = UTC2BJT(UTC);
	printf("%.2d:%.2d:%.2d\n",BJT.hh,BJT.mm,BJT.ss);
	system("pause");
	return 0;
}

TIME UTC2BJT(TIME UTC)
{
	//BJT=UTC+8
	TIME BJT={(UTC.hh+8)%24,UTC.mm,UTC.ss};
	return BJT;
}

int Calibration(char str[])
{
    //$GPRMC,024813.640,A,3158.4608,N,11848.3737,E,10.05,324.27,150706,,,A*50
    str=str+1;
    str=strtok(str, "*");
    int CalibrationValue=str[0];
    int i =0;
    for(;str[i]!='\0';i++)
    {
        CalibrationValue^=str[i];
    }
    return CalibrationValue;
}
