
//==========================================================================
// AES算法：用于完成应用程序的加密
//			本算法为128为AES算法,CFB动态加密
//			参考RFC 相关文档
// 创建		:
// 最后修改 :
// EMail	:
//==========================================================================

#ifndef AES_HPP
#define AES_HPP
#include <string.h>
#include <unistd.h>
#include "md5.hpp"

#define	AES_KEY_LENGTH	16			//加密关键字长度，16的整数倍 16 = 128Bit
#define	AES_BLOCK_SIZE	16			//每次读取记录块进行加密的长度,不能修改
#define	AES_MAX_ROUNDS	14
#define	AES_MAX_KC		8
#define	AES_MAX_BC		8

class AES
{
public:
	AES();

	//==========================================================================
	// 函数 : MakeKey
	// 用途 : 产生新的加密关键字
	// 原型 : void	MakeKey(const char * key);
	// 参数 : key				-- 计算关键字
	// 返回 : 无
	// 说明 : key的长度决定于AES_KEY_LENGTH
	//==========================================================================
	void	MakeKey(const char * key);

	//==========================================================================
	// 函数 : Encrypt
	// 用途 : 加密指定的字符串
	// 原型 : void	Encrypt(const char * in,char * result,int nSize);
	// 参数 : in				-- 需要加密的字符串
	//		  result			-- 加密后的结果
	//        nSize				-- 加密字符串的长度
	// 返回 : 无
	// 说明 : 加密的字符串和原来的字符串长度相等
	//==========================================================================
	void	Encrypt(const char * in,char * result,int nSize);

	//==========================================================================
	// 函数 : Decrypt
	// 用途 : 解密指定的字符串
	// 原型 : void	Decrypt(const char * in,char * result,int nSize);
	// 参数 : in				-- 需要解密的字符串
	//		  result			-- 解密后的结果
	//        nSize				-- 解密字符串的长度
	// 返回 : 无
	// 说明 : 加密的字符串和原来的字符串长度相等
	//==========================================================================
	void	Decrypt(const char * in,char * result,int nSize);

	//==========================================================================
	// 函数 : Encrypt
	// 用途 : 加密指定的文件
	// 原型 : void	Encrypt(const string strInFileName, 
	//							const string strOutFileName);
	// 参数 : strInFileName		-- 需要加密的文件
	//		  strOutFileName	-- 加密后的文件
	// 返回 : 无
	// 说明 : 无
	//==========================================================================
	void	Encrypt(const string strInFileName,const string strOutFileName);

	//==========================================================================
	// 函数 : Decrypt
	// 用途 : 解密指定的文件
	// 原型 : void	Decrypt(const string strInFileName, 
	//							const TCString strOutFileName);
	// 参数 : strInFileName		-- 需要解密的文件
	//		  strOutFileName	-- 解密后的文件
	// 返回 : 无
	// 说明 : 无
	//==========================================================================
	void	Decrypt(const string strInFileName,const string strOutFileName);

private:
	//==========================================================================
	// 函数 : DefEncryptBlock
	// 用途 : 用默认的长度(BLOCK_SIZE)加密指定的字符串
	// 原型 : void	DefEncryptBlock(const char * in,char * result);
	// 参数 : in				-- 需要加密的字符串
	//		  result			-- 加密后的结果
	// 返回 : 无
	// 说明 : 无
	//==========================================================================
	void	DefEncryptBlock(char const* in, char* result);

private:
	bool	bKeyInit;			// 定义Key已经被初始化
	int		Mul(int a, int b);
	int		Mul4(int a, char b[]);
	void	Xor(char* buff, char const* chain);
	int		m_Ke[AES_MAX_ROUNDS+1][AES_MAX_BC];
	int		m_Kd[AES_MAX_ROUNDS+1][AES_MAX_BC];
	int		m_iROUNDS;
	char	m_chain[AES_BLOCK_SIZE];
	int		tk[AES_MAX_KC];
};

#endif

//==============================================================================
