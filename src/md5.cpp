
//==========================================================================
#include "md5.hpp"
//==========================================================================

//第一次运算时运算规则
#define MD5_F1(x, y, z) (z ^ (x & (y ^ z)))
#define MD5_F2(x, y, z) MD5_F1(z, x, y)
#define MD5_F3(x, y, z) (x ^ y ^ z)
#define MD5_F4(x, y, z) (y ^ (x | ~z))

//第二次翻转运算时的运算规则
#define MD5STEP(f,w,x,y,z,data,s) (w+=f(x,y,z)+data,w=w<<s|w>>(32-s),w += x )

//==========================================================================
// 函数 : MD5::Init
// 用途 : 对MD5Context对核心结构进行初始化赋值(4个32Bit的大整数)
// 原型 : void	MD5Init(MD5Context * ctx)
// 参数 : ctx	核心数据结构
// 返回 : 128位的数字签名
// 说明 : 无
//==========================================================================
void MD5::MD5Init(MD5Context * ctx)
{
    ctx->buf[0] = 0x67452301;
    ctx->buf[1] = 0xefcdab89;
    ctx->buf[2] = 0x98badcfe;
    ctx->buf[3] = 0x10325476;

    ctx->bits[0] = 0;
    ctx->bits[1] = 0;
}

//==========================================================================
// 函数 : MD5::MD5Transform
// 用途 : 对每128位长度进行转换
// 原型 : void	MD5Transform(unsigned int buf[4], unsigned int in[16])
// 参数 : buf			--	转换后的结果
//		  in			--	需要转换的数据
// 返回 : 无
// 说明 : 无
//==========================================================================
void MD5::MD5Transform(unsigned int buf[4],unsigned int in[16])
{
    register unsigned int a, b, c, d;


    a = buf[0];
    b = buf[1];
    c = buf[2];
    d = buf[3];

	//第一轮运算
    MD5STEP(MD5_F1, a, b, c, d, in[0] + 0xd76aa478, 7);
    MD5STEP(MD5_F1, d, a, b, c, in[1] + 0xe8c7b756, 12);
    MD5STEP(MD5_F1, c, d, a, b, in[2] + 0x242070db, 17);
    MD5STEP(MD5_F1, b, c, d, a, in[3] + 0xc1bdceee, 22);
    MD5STEP(MD5_F1, a, b, c, d, in[4] + 0xf57c0faf, 7);
    MD5STEP(MD5_F1, d, a, b, c, in[5] + 0x4787c62a, 12);
    MD5STEP(MD5_F1, c, d, a, b, in[6] + 0xa8304613, 17);
    MD5STEP(MD5_F1, b, c, d, a, in[7] + 0xfd469501, 22);
    MD5STEP(MD5_F1, a, b, c, d, in[8] + 0x698098d8, 7);
    MD5STEP(MD5_F1, d, a, b, c, in[9] + 0x8b44f7af, 12);
    MD5STEP(MD5_F1, c, d, a, b, in[10] + 0xffff5bb1, 17);
    MD5STEP(MD5_F1, b, c, d, a, in[11] + 0x895cd7be, 22);
    MD5STEP(MD5_F1, a, b, c, d, in[12] + 0x6b901122, 7);
    MD5STEP(MD5_F1, d, a, b, c, in[13] + 0xfd987193, 12);
    MD5STEP(MD5_F1, c, d, a, b, in[14] + 0xa679438e, 17);
    MD5STEP(MD5_F1, b, c, d, a, in[15] + 0x49b40821, 22);

	//第二轮运算
    MD5STEP(MD5_F2, a, b, c, d, in[1] + 0xf61e2562, 5);
    MD5STEP(MD5_F2, d, a, b, c, in[6] + 0xc040b340, 9);
    MD5STEP(MD5_F2, c, d, a, b, in[11] + 0x265e5a51, 14);
    MD5STEP(MD5_F2, b, c, d, a, in[0] + 0xe9b6c7aa, 20);
    MD5STEP(MD5_F2, a, b, c, d, in[5] + 0xd62f105d, 5);
    MD5STEP(MD5_F2, d, a, b, c, in[10] + 0x02441453, 9);
    MD5STEP(MD5_F2, c, d, a, b, in[15] + 0xd8a1e681, 14);
    MD5STEP(MD5_F2, b, c, d, a, in[4] + 0xe7d3fbc8, 20);
    MD5STEP(MD5_F2, a, b, c, d, in[9] + 0x21e1cde6, 5);
    MD5STEP(MD5_F2, d, a, b, c, in[14] + 0xc33707d6, 9);
    MD5STEP(MD5_F2, c, d, a, b, in[3] + 0xf4d50d87, 14);
    MD5STEP(MD5_F2, b, c, d, a, in[8] + 0x455a14ed, 20);
    MD5STEP(MD5_F2, a, b, c, d, in[13] + 0xa9e3e905, 5);
    MD5STEP(MD5_F2, d, a, b, c, in[2] + 0xfcefa3f8, 9);
    MD5STEP(MD5_F2, c, d, a, b, in[7] + 0x676f02d9, 14);
    MD5STEP(MD5_F2, b, c, d, a, in[12] + 0x8d2a4c8a, 20);

	//第三轮运算
    MD5STEP(MD5_F3, a, b, c, d, in[5] + 0xfffa3942, 4);
    MD5STEP(MD5_F3, d, a, b, c, in[8] + 0x8771f681, 11);
    MD5STEP(MD5_F3, c, d, a, b, in[11] + 0x6d9d6122, 16);
    MD5STEP(MD5_F3, b, c, d, a, in[14] + 0xfde5380c, 23);
    MD5STEP(MD5_F3, a, b, c, d, in[1] + 0xa4beea44, 4);
    MD5STEP(MD5_F3, d, a, b, c, in[4] + 0x4bdecfa9, 11);
    MD5STEP(MD5_F3, c, d, a, b, in[7] + 0xf6bb4b60, 16);
    MD5STEP(MD5_F3, b, c, d, a, in[10] + 0xbebfbc70, 23);
    MD5STEP(MD5_F3, a, b, c, d, in[13] + 0x289b7ec6, 4);
    MD5STEP(MD5_F3, d, a, b, c, in[0] + 0xeaa127fa, 11);
    MD5STEP(MD5_F3, c, d, a, b, in[3] + 0xd4ef3085, 16);
    MD5STEP(MD5_F3, b, c, d, a, in[6] + 0x04881d05, 23);
    MD5STEP(MD5_F3, a, b, c, d, in[9] + 0xd9d4d039, 4);
    MD5STEP(MD5_F3, d, a, b, c, in[12] + 0xe6db99e5, 11);
    MD5STEP(MD5_F3, c, d, a, b, in[15] + 0x1fa27cf8, 16);
    MD5STEP(MD5_F3, b, c, d, a, in[2] + 0xc4ac5665, 23);

	//第四轮运算
    MD5STEP(MD5_F4, a, b, c, d, in[0] + 0xf4292244, 6);
    MD5STEP(MD5_F4, d, a, b, c, in[7] + 0x432aff97, 10);
    MD5STEP(MD5_F4, c, d, a, b, in[14] + 0xab9423a7, 15);
    MD5STEP(MD5_F4, b, c, d, a, in[5] + 0xfc93a039, 21);
    MD5STEP(MD5_F4, a, b, c, d, in[12] + 0x655b59c3, 6);
    MD5STEP(MD5_F4, d, a, b, c, in[3] + 0x8f0ccc92, 10);
    MD5STEP(MD5_F4, c, d, a, b, in[10] + 0xffeff47d, 15);
    MD5STEP(MD5_F4, b, c, d, a, in[1] + 0x85845dd1, 21);
    MD5STEP(MD5_F4, a, b, c, d, in[8] + 0x6fa87e4f, 6);
    MD5STEP(MD5_F4, d, a, b, c, in[15] + 0xfe2ce6e0, 10);
    MD5STEP(MD5_F4, c, d, a, b, in[6] + 0xa3014314, 15);
    MD5STEP(MD5_F4, b, c, d, a, in[13] + 0x4e0811a1, 21);
    MD5STEP(MD5_F4, a, b, c, d, in[4] + 0xf7537e82, 6);
    MD5STEP(MD5_F4, d, a, b, c, in[11] + 0xbd3af235, 10);
    MD5STEP(MD5_F4, c, d, a, b, in[2] + 0x2ad7d2bb, 15);
    MD5STEP(MD5_F4, b, c, d, a, in[9] + 0xeb86d391, 21);

    buf[0] += a;
    buf[1] += b;
    buf[2] += c;
    buf[3] += d;
}

//==========================================================================
// 函数 : MD5::MD5Update
// 用途 : 计算MD5的数字签名
// 原型 : void MD5Update(MD5Context * ctx,unsigned char * buf, 
//												unsigned int len);
// 参数 : ctx			--  MD5核心数据结构
//		  buf			--	转换后的结果
//		  in			--	需要转换的数据
// 返回 : 无
// 说明 : 无
//==========================================================================
void MD5::MD5Update(MD5Context * ctx,unsigned char * buf, unsigned int len)
{
    unsigned int t;

    t = ctx->bits[0];
    if ((ctx->bits[0] = t + ((unsigned int) len << 3)) < t)
	{
		ctx->bits[1]++;
	}
    ctx->bits[1] += len >> 29;

    t = (t >> 3) & 0x3f;

    if (t)
    {
		unsigned char *p = (unsigned char *) ctx->in + t;

		t = 64 - t;
		if (len < t)
		{
	    	memcpy(p, buf, len);
	    	return;
		}
		memcpy(p, buf, t);
		MD5Transform(ctx->buf, (unsigned int *) ctx->in);
		buf += t;
		len -= t;
		printf("t = [%u]\n",t);

    }

    while (len >= 64)
    {
		memcpy(ctx->in, buf, 64);
		MD5Transform(ctx->buf, (unsigned int *) ctx->in);
		buf += 64;
		len -= 64;
    }

    memcpy(ctx->in, buf, len);
}


//==========================================================================
// 函数 : MD5::MD5FileUpdate
// 用途 : 计算MD5的数字签名
// 原型 : void MD5FileUpdate(MD5Context * ctx, string strFileName)
// 参数 : ctx			--  MD5核心的数据结构
//		  srcFileName	--	需要处理的文件
// 返回 : 无
// 说明 : 无
//==========================================================================
void MD5::MD5FileUpdate(MD5Context * ctx, string strFileName)
{
    unsigned int	t;
	unsigned int	len;
	unsigned char	* buf;
	ifstream fp(strFileName.c_str());
	fp.seekg(0, ios_base::end);
	len = fp.tellg();
	fp.seekg(0, ios_base::beg);

	t = ctx->bits[0];
    if ((ctx->bits[0] = t + ((unsigned int) len << 3)) < t)
	ctx->bits[1]++;
    ctx->bits[1] += len >> 29;

    t = (t >> 3) & 0x3f;

    if (t)
    {
		unsigned char *p = (unsigned char *) ctx->in + t;
		t = 64 - t;
		buf = new unsigned char[(sizeof(unsigned char)*t)];
		if (len < t)
		{
			fp.read((char *)buf,t);
	    	memcpy(p, buf, len);
			delete []buf;
	    	return;
		}
		fp.read((char *)buf,t);
		memcpy(p, buf, t);
		MD5Transform(ctx->buf, (unsigned int *) ctx->in);
		len -= t;
		delete []buf;
    }

	buf = new unsigned char[(sizeof(unsigned char)*64)];
    while (len >= 64)
    {
		fp.read((char *)buf,64);
		memcpy(ctx->in, buf, 64);
		MD5Transform(ctx->buf, (unsigned int *) ctx->in);
		len -= 64;
    }

	fp.read((char *)buf,64);
	memcpy(ctx->in, buf, len);
	delete []buf;
}

//==========================================================================
// 函数 : MD5::MD5Final
// 用途 : 完成数字的签名，对数据结构进行补零
// 原型 : void	MD5Final(unsigned char digest[16], MD5Context * ctx);
// 参数 : digest			-- 计算后的数字签名信息
//		  ctx				-- 核心数据结构
// 返回 : 无
// 说明 : 无
//==========================================================================
void MD5::MD5Final(unsigned char digest[16], MD5Context * ctx)
{
    unsigned count;
    unsigned char *p;

    //计算数据长度的64余数
    count = (ctx->bits[0] >> 3) & 0x3F;

    //填充第一个字符0x80
    p = ctx->in + count;
    *p++ = 0x80;

    //填充数据长度到64字节
    count = 64 - 1 - count;

    if (count < 8)
    {
		memset(p, 0, count);
		MD5Transform(ctx->buf, (unsigned int *) ctx->in);
		memset(ctx->in, 0, 56);
    }
    else
    {
		memset(p, 0, count - 8);
    }

    //设置需要转换的位数，并进行转换
    ((unsigned int *) ctx->in)[14] = ctx->bits[0];
    ((unsigned int *) ctx->in)[15] = ctx->bits[1];

    MD5Transform(ctx->buf, (unsigned int *) ctx->in);
    memcpy(digest, ctx->buf, 16);
    memset(ctx, 0, sizeof(ctx));
}

//==========================================================================
// 函数 : MD5::MD5Generate
// 用途 : 根据传入的数据内容进行MD5分析,并返回128位的数字签名
// 原型 : TCString MD5Generate(unsigned char * buf, unsigned int len = 0);
// 参数 : buf		-- 需要进行转换的数据
//		  len		-- 需要转换的数据长度,默认为全部长度
// 返回 : 128位的数字签名
// 说明 : 无
//==========================================================================
string	MD5::MD5Generate(char * buf,unsigned int len)
{
	string			s;
	unsigned char	digest[17];
    MD5Context		md5c;
	unsigned	int	m_len;
	char			m_szTempData[33];

	m_len = len;
	if (len == 0)
	{
		m_len = (unsigned int)strlen(buf);
	}
    MD5Init(&md5c);
    MD5Update(&md5c,(unsigned char *)buf,m_len);
    MD5Final(digest, &md5c);
	digest[16] = '\0';

	sprintf(m_szTempData,
		"%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X",
		digest[0],digest[1],digest[2],digest[3],digest[4],
		digest[5],digest[6],digest[7],digest[8],digest[9],
		digest[10],digest[11],digest[12],digest[13],digest[14],
		digest[15]
		);

	s = m_szTempData;

	return s;
}

//==========================================================================
// 函数 : MD5::MD5FileGenerate
// 用途 : 根据指定文件的内容进行MD5分析,并返回128位的数字签名
// 原型 : void MD5FileGenerate(TCString strFileName);
// 参数 : strFileName		-- 需要进行签名的文件名称
// 返回 : 128位的数字签名
// 说明 : 无
//==========================================================================
string	MD5::MD5FileGenerate(string strFileName)
{
	string			s;
	unsigned char	digest[17];
    MD5Context		md5c;
	char			m_szTempData[33];

    MD5Init(&md5c);
    MD5FileUpdate(&md5c,strFileName);
    MD5Final(digest, &md5c);
	digest[16] = '\0';

	sprintf(m_szTempData,
		"%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X",
		digest[0],digest[1],digest[2],digest[3],digest[4],
		digest[5],digest[6],digest[7],digest[8],digest[9],
		digest[10],digest[11],digest[12],digest[13],digest[14],
		digest[15]
		);
	s = m_szTempData;

	return s;
}

//===END====================================================================
