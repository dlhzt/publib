
//==========================================================================
// AES�㷨���������Ӧ�ó���ļ���
//			���㷨Ϊ128ΪAES�㷨,CFB��̬����
//			�ο�RFC ����ĵ�
// ����		:
// ����޸� :
// EMail	:
//==========================================================================

#ifndef AES_HPP
#define AES_HPP
#include <string.h>
#include <unistd.h>
#include "md5.hpp"

#define	AES_KEY_LENGTH	16			//���ܹؼ��ֳ��ȣ�16�������� 16 = 128Bit
#define	AES_BLOCK_SIZE	16			//ÿ�ζ�ȡ��¼����м��ܵĳ���,�����޸�
#define	AES_MAX_ROUNDS	14
#define	AES_MAX_KC		8
#define	AES_MAX_BC		8

class AES
{
public:
	AES();

	//==========================================================================
	// ���� : MakeKey
	// ��; : �����µļ��ܹؼ���
	// ԭ�� : void	MakeKey(const char * key);
	// ���� : key				-- ����ؼ���
	// ���� : ��
	// ˵�� : key�ĳ��Ⱦ�����AES_KEY_LENGTH
	//==========================================================================
	void	MakeKey(const char * key);

	//==========================================================================
	// ���� : Encrypt
	// ��; : ����ָ�����ַ���
	// ԭ�� : void	Encrypt(const char * in,char * result,int nSize);
	// ���� : in				-- ��Ҫ���ܵ��ַ���
	//		  result			-- ���ܺ�Ľ��
	//        nSize				-- �����ַ����ĳ���
	// ���� : ��
	// ˵�� : ���ܵ��ַ�����ԭ�����ַ����������
	//==========================================================================
	void	Encrypt(const char * in,char * result,int nSize);

	//==========================================================================
	// ���� : Decrypt
	// ��; : ����ָ�����ַ���
	// ԭ�� : void	Decrypt(const char * in,char * result,int nSize);
	// ���� : in				-- ��Ҫ���ܵ��ַ���
	//		  result			-- ���ܺ�Ľ��
	//        nSize				-- �����ַ����ĳ���
	// ���� : ��
	// ˵�� : ���ܵ��ַ�����ԭ�����ַ����������
	//==========================================================================
	void	Decrypt(const char * in,char * result,int nSize);

	//==========================================================================
	// ���� : Encrypt
	// ��; : ����ָ�����ļ�
	// ԭ�� : void	Encrypt(const string strInFileName, 
	//							const string strOutFileName);
	// ���� : strInFileName		-- ��Ҫ���ܵ��ļ�
	//		  strOutFileName	-- ���ܺ���ļ�
	// ���� : ��
	// ˵�� : ��
	//==========================================================================
	void	Encrypt(const string strInFileName,const string strOutFileName);

	//==========================================================================
	// ���� : Decrypt
	// ��; : ����ָ�����ļ�
	// ԭ�� : void	Decrypt(const string strInFileName, 
	//							const TCString strOutFileName);
	// ���� : strInFileName		-- ��Ҫ���ܵ��ļ�
	//		  strOutFileName	-- ���ܺ���ļ�
	// ���� : ��
	// ˵�� : ��
	//==========================================================================
	void	Decrypt(const string strInFileName,const string strOutFileName);

private:
	//==========================================================================
	// ���� : DefEncryptBlock
	// ��; : ��Ĭ�ϵĳ���(BLOCK_SIZE)����ָ�����ַ���
	// ԭ�� : void	DefEncryptBlock(const char * in,char * result);
	// ���� : in				-- ��Ҫ���ܵ��ַ���
	//		  result			-- ���ܺ�Ľ��
	// ���� : ��
	// ˵�� : ��
	//==========================================================================
	void	DefEncryptBlock(char const* in, char* result);

private:
	bool	bKeyInit;			// ����Key�Ѿ�����ʼ��
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
