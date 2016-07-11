
//==========================================================================
// MD5算法：用于完成数字签名的计算
//			本算法为128为MD5算法
//			参考RFC 1321相关文档
// 创建		:
// 最后修改 :
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
	unsigned int 	buf[4];		//用来计算MD5的4个32Bit无符号整数(大素数)
	unsigned int 	bits[2];	//数字的位数 (用2^64 进行求摸后的结果)
	unsigned char 	in[64];		//需要进行转换的数据
} MD5Context;					//MD5核心数据结构

class MD5
{
public:
	//==========================================================================
	// 函数 : MD5::MD5Generate
	// 用途 : 根据传入的数据内容进行MD5分析,并返回128位的数字签名
	// 原型 : TCString MD5Generate(unsigned char * buf, unsigned int len = 0);
	// 参数 : buf		-- 需要进行转换的数据
	//		  len		-- 需要转换的数据长度,默认为全部长度
	// 返回 : 128位的数字签名
	// 说明 : 无
	//==========================================================================
	string	MD5Generate(char * buf,unsigned int len = 0);

	//==========================================================================
	// 函数 : MD5::MD5FileGenerate
	// 用途 : 根据指定文件的内容进行MD5分析,并返回128位的数字签名
	// 原型 : void MD5FileGenerate(TCString strFileName);
	// 参数 : strFileName		-- 需要进行签名的文件名称
	// 返回 : 128位的数字签名
	// 说明 : 无
	//==========================================================================
	string	MD5FileGenerate(string strFileName);

protected:
	//==========================================================================
	// 函数 : MD5::MD5Init
	// 用途 : 对MD5Context对核心结构进行初始化赋值(4个32Bit的大整数)
	// 原型 : void	MD5Init(MD5Context * ctx)
	// 参数 : ctx	核心数据结构
	// 返回 : 128位的数字签名
	// 说明 : 无
	//==========================================================================
	void	MD5Init(MD5Context * ctx);

	//==========================================================================
	// 函数 : MD5::MD5Transform
	// 用途 : 对每128位长度进行转换
	// 原型 : void	MD5Transform(unsigned int buf[4], unsigned int in[16])
	// 参数 : buf			--	转换后的结果
	//		  in			--	需要转换的数据
	// 返回 : 无
	// 说明 : 无
	//==========================================================================
	void	MD5Transform(unsigned int buf[4], unsigned int in[16]);

	//==========================================================================
	// 函数 : MD5::MD5Update
	// 用途 : 计算MD5的数字签名
	// 原型 : void MD5Update(MD5Context * ctx,unsigned char * buf, 
	//												unsigned int len);
	// 参数 : buf			--	转换后的结果
	//		  in			--	需要转换的数据
	// 返回 : 无
	// 说明 : 无
	//==========================================================================
	void MD5Update(MD5Context * ctx,unsigned char * buf, unsigned int len);

	//==========================================================================
	// 函数 : MD5::MD5FileUpdate
	// 用途 : 计算MD5的数字签名
	// 原型 : void MD5FileUpdate(MD5Context * ctx, string strFileName)
	// 参数 : ctx			--  MD5核心的数据结构
	//		  srcFileName	--	需要处理的文件
	// 返回 : 无
	// 说明 : 无
	//==========================================================================
	void MD5FileUpdate(MD5Context * ctx, string strFileName);

	//==========================================================================
	// 函数 : MD5::MD5Final
	// 用途 : 完成数字的签名，对数据结构进行补零
	// 原型 : void	MD5Final(unsigned char digest[16], MD5Context * ctx);
	// 参数 : digest			-- 计算后的数字签名信息
	//		  ctx				-- 核心数据结构
	// 返回 : 无
	// 说明 : 无
	//==========================================================================
	void MD5Final(unsigned char digest[16], MD5Context * ctx);
};

#endif

//===END========================================================================
