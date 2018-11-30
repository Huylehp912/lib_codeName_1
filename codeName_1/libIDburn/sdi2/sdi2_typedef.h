/**@defgroup TYPEDEF TYPEDEF ����SDI��������EastWinϵ������еĻ�����������

@brief Typedefģ���Ӧͷ�ļ�sdi2_typedef.h����Ҫ����SDI��������Eastwinϵ�������
�Ļ����������ͣ���SDI_BOOL��SDI_HANDLE�ȣ�û�нӿ���Ҫʵ�֡��ֶԶ����32λ��
���ͱ�����64λ�����ͱ����Ķ���������˵����

- ��ģ����Ȼ�ж���SDI_INT32��SDI_UINT32��32λ�����ͱ�������������Ҫ��ȷ����
�����ĳ��ȣ���λ���У�����Eastwin�ᾡ��ʹ��C����ԭ�������ݽṹ����������Ķ��塣\n
- ���ƽ̨��֧��ԭ��64λ������������ƽ̨�Ѿ�Խ��Խ���ˣ������߶�64λ���������㲻
����C99�淶������Ҫ����MMCP_SUPPORT_LL�꣬���������SDI��ͨ��һ��Structģ
��64λ����������Eastwin�ڲ��ṩ��ģ���64λ��ѧ���㷽������Ҫ�ر�ע����ǣ�����
SDI�ӿ����Ѱ�����SDI_UINT64���͵Ĳ�������ʵ����Щ�ӿ�ʱ������Ҫ�漰64λ������
���㣬����ֲ������ʵ�֡�\n

@note ��ģ�������ṹ��û�нӿ���Ҫʵ�֡�
@note �����ر�˵��������SDI�ӿڱ��뱣֤�̰߳�ȫ��

@version 2.0.3 2009/08/24 ȥ��64λ����꣬��ƽ̨ȥʵ�֡�
@version 2.0.2 2009/08/20 ����64λ����꣬�Ƴ��������ش������
@version 2.0.1 2009/07/27 ����
@{
*/

//������������SDI�������������汾��Ϣ�������漰SDI�ĸĶ������������¼

/**@mainpage Unified Driver Interface(SDI2.0) �ĵ�

@version <B>SDI_V2.1.1</B> 2009/09/26
- ���Ӹ���ϸ��ģ������˵����Ҫ��˵��
- ���������ӿ���������ʹ֮���������������
- ȥ��ö�����һ����Ա�Ķ��ţ��Խ������ƽ̨�޷�����ͨ��������
- ���Tuner,Demux����״̬��ѯ���ܣ����Tuner��Demux�������ӵĴ������˵��
- �޸Ļ�ȡTuner��Ϣ�ӿڣ�ʹ�����ڿ��Ե�����ȡ������Ϣ�����Ч��
- ����һЩ�ĵ����������ԵĴ���

@version <B>SDI_V2.1.0</B> 2009/09/09
- ���ӿ��ƶ��豸��֧�֣�����Tuner,�洢�豸;ͳһ�˿��ƶ��洢�豸�Ľӿ�

@version <B>SDI_V2.0.3</B> 2009/08/28
- ������ͼƬӲ����ӿڣ�������demux����tuner�Ľӿ�

@version <B>SDI_V2.0.2</B> 2009/08/25
- ������һ���ۺ�����

@version <B>SDI_V2.0.1</B> 2009/08/16
- ��ʼ�汾
*/

#ifndef _SDI2_TYPEDEF_H_
#define _SDI2_TYPEDEF_H_

#ifdef __cplusplus
extern "C" {
#endif

/***********���������ھ������ƽ̨��,����Ҫ�Ķ�*********************/

typedef int                 SDI_BOOL;           ///< ��������
typedef void *			    SDI_HANDLE;         ///< �������,�䳤�ȵ���ָ�볤�ȡ�note Eastwin�ὫSDI_NULL����һ���Ƿ��ľ����������ʵ�ر�ע������Handle��ȡֵ��Χ

//������Ҫ��ȷ���Ƴ���,���򲻽���ʹ�����¶���
typedef signed char	        SDI_INT8;             ///< 8λ�з�����
typedef unsigned char	    SDI_UINT8;            ///< 8λ�޷�����

typedef signed short	    SDI_INT16;            ///< 16λ�з�����
typedef unsigned short	    SDI_UINT16;           ///< 16λ�޷�����

typedef signed long	        SDI_INT32;            ///< 32λ�з�����
typedef unsigned long	    SDI_UINT32;           ///< 32λ�޷�����,ע���ֹʹ��SDI_UINT32�洢ָ��

//gcc,VC�ṩ��ͷ�ļ������˷�ʽ����
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


/***********�������ݿ��ܻ����ƽ̨�Ĳ�ͬ,�����ı�,�������½ṹ��Ϊ���ݲ��ֵ������������,�뾡����Ҫʹ��*********************/


/**@brief ��ƽ̨֧��64λ��,����붨����������,����ɲ���ע

@note �ú궨�������ƽ̨�����Ƿ�֧�֣������ж���
*/

#ifdef MMCP_SUPPORT_LL

typedef long long           SDI_INT64;            ///< 64λ�з�����,������MMCP_SUPPORT_LLʱ��Ч
typedef unsigned long long  SDI_UINT64;          ///< 64λ�޷�����,������MMCP_SUPPORT_LLʱ��Ч

#else

/**@brief 64λ�з������ṹ��*/
typedef	struct
{
	SDI_UINT32	low; ///< ��32λ
	SDI_INT32	    high;///< ��32λ
}SDI_INT64;

/**@brief 64λ�޷������ṹ��*/
typedef	struct
{
	SDI_UINT32	low;///< ��32λ
	SDI_UINT32	high;///< ��32λ
}SDI_UINT64;

#endif

#ifdef __cplusplus
}
#endif
/** @} */
#endif  //_SDI2_TYPEDEF_H_

