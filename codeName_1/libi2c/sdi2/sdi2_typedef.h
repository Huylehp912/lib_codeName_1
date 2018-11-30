/**@defgroup TYPEDEF TYPEDEF 定义SDI乃至整个EastWin系列软件中的基本数据类型

@brief Typedef模块对应头文件sdi2_typedef.h，主要定义SDI乃至整个Eastwin系列软件中
的基本数据类型，如SDI_BOOL、SDI_HANDLE等，没有接口需要实现。现对定义的32位整
数型变量和64位整数型变量的定义做如下说明：

- 本模块虽然有定义SDI_INT32、SDI_UINT32等32位整数型变量，但除非需要精确控制
变量的长度，如位运行，否则Eastwin会尽量使用C语言原生的数据结构而不是这里的定义。\n
- 如果平台不支持原生64位整数（这样的平台已经越来越少了），或者对64位整数的运算不
符合C99规范，则不需要定义MMCP_SUPPORT_LL宏，这种情况下SDI会通过一个Struct模
拟64位整数，并在Eastwin内部提供该模拟的64位数学运算方法。需要特别注意的是，部分
SDI接口中已包含了SDI_UINT64类型的参数，在实现这些接口时，若需要涉及64位整数的
运算，需移植层自行实现。\n

@note 本模块仅定义结构，没有接口需要实现。
@note 除非特别说明，整个SDI接口必须保证线程安全。

@version 2.0.3 2009/08/24 去掉64位运算宏，由平台去实现。
@version 2.0.2 2009/08/20 增加64位运算宏，移除公共返回错误代码
@version 2.0.1 2009/07/27 初稿
@{
*/

//这里描述整个SDI的总体描述及版本信息，所有涉及SDI的改动，请在这里记录

/**@mainpage Unified Driver Interface(SDI2.0) 文档

@version <B>SDI_V2.1.1</B> 2009/09/26
- 增加更详细的模块总体说明及要点说明
- 调整大量接口语言描述使之更清晰更容易理解
- 去掉枚举最后一个成员的逗号，以解决部分平台无法编译通过的问题
- 添加Tuner,Demux连接状态查询功能；添加Tuner和Demux不可连接的错误代码说明
- 修改获取Tuner信息接口，使得现在可以单独获取部分信息以提高效率
- 修正一些文档语言描述性的错误

@version <B>SDI_V2.1.0</B> 2009/09/09
- 增加可移动设备的支持，包括Tuner,存储设备;统一了可移动存储设备的接口

@version <B>SDI_V2.0.3</B> 2009/08/28
- 增加了图片硬解码接口；增加了demux连接tuner的接口

@version <B>SDI_V2.0.2</B> 2009/08/25
- 经过第一次综合评审

@version <B>SDI_V2.0.1</B> 2009/08/16
- 初始版本
*/

#ifndef _SDI2_TYPEDEF_H_
#define _SDI2_TYPEDEF_H_

#ifdef __cplusplus
extern "C" {
#endif

/***********以下内容在绝大多数平台上,不需要改动*********************/

typedef int                 SDI_BOOL;           ///< 布尔类型
typedef void *			    SDI_HANDLE;         ///< 句柄类型,其长度等于指针长度。note Eastwin会将SDI_NULL当做一个非法的句柄，请是现实特别注意所有Handle的取值范围

//除非需要精确控制长度,否则不建议使用以下定义
typedef signed char	        SDI_INT8;             ///< 8位有符号数
typedef unsigned char	    SDI_UINT8;            ///< 8位无符号数

typedef signed short	    SDI_INT16;            ///< 16位有符号数
typedef unsigned short	    SDI_UINT16;           ///< 16位无符号数

typedef signed long	        SDI_INT32;            ///< 32位有符号数
typedef unsigned long	    SDI_UINT32;           ///< 32位无符号数,注意禁止使用SDI_UINT32存储指针

//gcc,VC提供的头文件均按此方式定义
#ifdef __cplusplus
#define SDI_NULL    		0
#else
#define SDI_NULL    		((void *)0)
#endif

#ifndef NULL
#define NULL (void *)0
#endif

#define SDI_FALSE         (0 == 1)
#define SDI_TRUE          (!(SDI_FALSE))


/***********以下内容可能会根据平台的不同,经常改变,定义以下结构仅为兼容部分第三方代码而设,请尽量不要使用*********************/


/**@brief 若平台支持64位数,则必须定义以下类型,否则可不关注

@note 该宏定义必须由平台决定是否支持，并进行定义
*/

#ifdef MMCP_SUPPORT_LL

typedef long long           SDI_INT64;            ///< 64位有符号数,当定义MMCP_SUPPORT_LL时有效
typedef unsigned long long  SDI_UINT64;          ///< 64位无符号数,当定义MMCP_SUPPORT_LL时有效

#else

/**@brief 64位有符号数结构体*/
typedef	struct
{
	SDI_UINT32	low; ///< 低32位
	SDI_INT32	    high;///< 高32位
}SDI_INT64;

/**@brief 64位无符号数结构体*/
typedef	struct
{
	SDI_UINT32	low;///< 低32位
	SDI_UINT32	high;///< 高32位
}SDI_UINT64;

#endif

#ifdef __cplusplus
}
#endif
/** @} */
#endif  //_SDI2_TYPEDEF_H_

