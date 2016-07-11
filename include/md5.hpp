
//==========================================================================
// MD5�㷨�������������ǩ���ļ���
//			���㷨Ϊ128ΪMD5�㷨
//			�ο�RFC 1321����ĵ�
// ����		:
// ����޸� :
// EMail	:
//==========================================================================

#ifndef _lib_Public_MD5_H_
#define _lib_Public_MD5_H_

//#include "lib_Public_Sys_include.h"
//#include "lib_Public_String.h"
//#include "lib_Public_FileStream.h"
#include <string>
#include <fstream>
#include <stdexcept>
using namespace std;

typedef struct
{
	unsigned int 	buf[4];		//��������MD5��4��32Bit�޷�������(������)
	unsigned int 	bits[2];	//���ֵ�λ�� (��2^64 ����������Ľ��)
	unsigned char 	in[64];		//��Ҫ����ת��������
} MD5Context;					//MD5�������ݽṹ

class MD5
{
public:
	//==========================================================================
	// ���� : MD5::MD5Generate
	// ��; : ���ݴ�����������ݽ���MD5����,������128λ������ǩ��
	// ԭ�� : TCString MD5Generate(unsigned char * buf, unsigned int len = 0);
	// ���� : buf		-- ��Ҫ����ת��������
	//		  len		-- ��Ҫת�������ݳ���,Ĭ��Ϊȫ������
	// ���� : 128λ������ǩ��
	// ˵�� : ��
	//==========================================================================
	string	MD5Generate(char * buf,unsigned int len = 0);

	//==========================================================================
	// ���� : MD5::MD5FileGenerate
	// ��; : ����ָ���ļ������ݽ���MD5����,������128λ������ǩ��
	// ԭ�� : void MD5FileGenerate(TCString strFileName);
	// ���� : strFileName		-- ��Ҫ����ǩ�����ļ�����
	// ���� : 128λ������ǩ��
	// ˵�� : ��
	//==========================================================================
	string	MD5FileGenerate(string strFileName);

protected:
	//==========================================================================
	// ���� : MD5::MD5Init
	// ��; : ��MD5Context�Ժ��Ľṹ���г�ʼ����ֵ(4��32Bit�Ĵ�����)
	// ԭ�� : void	MD5Init(MD5Context * ctx)
	// ���� : ctx	�������ݽṹ
	// ���� : 128λ������ǩ��
	// ˵�� : ��
	//==========================================================================
	void	MD5Init(MD5Context * ctx);

	//==========================================================================
	// ���� : MD5::MD5Transform
	// ��; : ��ÿ128λ���Ƚ���ת��
	// ԭ�� : void	MD5Transform(unsigned int buf[4], unsigned int in[16])
	// ���� : buf			--	ת����Ľ��
	//		  in			--	��Ҫת��������
	// ���� : ��
	// ˵�� : ��
	//==========================================================================
	void	MD5Transform(unsigned int buf[4], unsigned int in[16]);

	//==========================================================================
	// ���� : MD5::MD5Update
	// ��; : ����MD5������ǩ��
	// ԭ�� : void MD5Update(MD5Context * ctx,unsigned char * buf, 
	//												unsigned int len);
	// ���� : buf			--	ת����Ľ��
	//		  in			--	��Ҫת��������
	// ���� : ��
	// ˵�� : ��
	//==========================================================================
	void MD5Update(MD5Context * ctx,unsigned char * buf, unsigned int len);

	//==========================================================================
	// ���� : MD5::MD5FileUpdate
	// ��; : ����MD5������ǩ��
	// ԭ�� : void MD5FileUpdate(MD5Context * ctx, string strFileName)
	// ���� : ctx			--  MD5���ĵ����ݽṹ
	//		  srcFileName	--	��Ҫ�������ļ�
	// ���� : ��
	// ˵�� : ��
	//==========================================================================
	void MD5FileUpdate(MD5Context * ctx, string strFileName);

	//==========================================================================
	// ���� : MD5::MD5Final
	// ��; : ������ֵ�ǩ���������ݽṹ���в���
	// ԭ�� : void	MD5Final(unsigned char digest[16], MD5Context * ctx);
	// ���� : digest			-- ����������ǩ����Ϣ
	//		  ctx				-- �������ݽṹ
	// ���� : ��
	// ˵�� : ��
	//==========================================================================
	void MD5Final(unsigned char digest[16], MD5Context * ctx);
};

#endif

//===END========================================================================