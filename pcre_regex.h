#define PCRE_STATIC // 静态库编译选项

#include "pcre.h"


#define OVECCOUNT	30 /* should be a multiple of 3 */
#define OVECCOUNTJIT 64 /*for jit*/
#define EBUFLEN		128
#define BUFLEN		1024
#define PCRE_BUG	0x80000000

#define MUA     (PCRE_MULTILINE | PCRE_UTF8 | PCRE_NEWLINE_ANYCRLF)
#define MUAP    (PCRE_MULTILINE | PCRE_UTF8 | PCRE_NEWLINE_ANYCRLF | PCRE_UCP)
#define CMUA    (PCRE_CASELESS | PCRE_MULTILINE | PCRE_UTF8 | PCRE_NEWLINE_ANYCRLF)
#define CMUAP   (PCRE_CASELESS | PCRE_MULTILINE | PCRE_UTF8 | PCRE_NEWLINE_ANYCRLF | PCRE_UCP)
#define MA      (PCRE_MULTILINE | PCRE_NEWLINE_ANYCRLF)
#define MAP     (PCRE_MULTILINE | PCRE_NEWLINE_ANYCRLF | PCRE_UCP)
#define CMA     (PCRE_CASELESS | PCRE_MULTILINE | PCRE_NEWLINE_ANYCRLF)

/** 
* @_ismatch  实现字符串并返回是否匹配 
* @param   src 源字符串
* @param   pattern  正则表达式 
* @return  如果返回非 -1 就是已匹配到 
*/ 

int _ismatch( char* src, char* pattern)
{   
	pcre  *re;
	const char *error;
	int  erroffset;
	int  ovector[OVECCOUNT];
	int  result;

	re = pcre_compile(pattern,// pattern, 输入参数，将要被编译的字符串形式的正则表达式
		0,            // options, 输入参数，用来指定编译时的一些选项
		&error,       // errptr, 输出参数，用来输出错误信息
		&erroffset,   // erroffset, 输出参数，pattern中出错位置的偏移量
		NULL);        // tableptr, 输入参数，用来指定字符表，一般情况用NULL


	if (re == NULL) {  //如果编译失败，返回错误信息
		return -1;
	}
	result = pcre_exec(re, // code, 输入参数，用pcre_compile编译好的正则表达结构的指针
		NULL,          // extra, 输入参数，用来向pcre_exec传一些额外的数据信息的结构的指针
		src,           // subject, 输入参数，要被用来匹配的字符串
		strlen(src),   // length, 输入参数， 要被用来匹配的字符串的指针
		0,             // startoffset, 输入参数，用来指定subject从什么位置开始被匹配的偏移量
		0,             // options, 输入参数， 用来指定匹配过程中的一些选项
		ovector,       // ovector, 输出参数，用来返回匹配位置偏移量的数组
		OVECCOUNT);    // ovecsize, 输入参数， 用来返回匹配位置偏移量的数组的最大大小

	if (result < 0) {
		pcre_free(re);
		return -1;
	}

	pcre_free(re);

	return result;
}  

/** 
* @_ismatch_char   实现字符串并返回匹配到的字符串 
* @param   src 源字符串
* @param   pattern  正则表达式 
* @return  返回修改后的串 如果反回的字符不是NULL就是所匹配到的值了 
*/ 
// char* _ismatch_char( char* src, char* pattern)
// {   
//     pcre  *re;
//     const char *error;
//     int  erroffset;
//     int  ovector[OVECCOUNT];
//     int  result,i;
//     char* dst = "NULL";
// 
//     re = pcre_compile(pattern,// pattern, 输入参数，将要被编译的字符串形式的正则表达式
//         0,            // options, 输入参数，用来指定编译时的一些选项
//         &error,       // errptr, 输出参数，用来输出错误信息
//         &erroffset,   // erroffset, 输出参数，pattern中出错位置的偏移量
//         NULL);        // tableptr, 输入参数，用来指定字符表，一般情况用NULL
// 
// 
//     if (re == NULL) {  //如果编译失败，返回错误信息
//         return dst;
//     }
//     result = pcre_exec(re, // code, 输入参数，用pcre_compile编译好的正则表达结构的指针
//         NULL,          // extra, 输入参数，用来向pcre_exec传一些额外的数据信息的结构的指针
//         src,           // subject, 输入参数，要被用来匹配的字符串
//         strlen(src),   // length, 输入参数， 要被用来匹配的字符串的指针
//         0,             // startoffset, 输入参数，用来指定subject从什么位置开始被匹配的偏移量
//         0,             // options, 输入参数， 用来指定匹配过程中的一些选项
//         ovector,       // ovector, 输出参数，用来返回匹配位置偏移量的数组
//         OVECCOUNT);    // ovecsize, 输入参数， 用来返回匹配位置偏移量的数组的最大大小
// 
//     if (result < 0) {
//         pcre_free(re);
//         return dst;
//     }
// 
//     /*return result;*/
//     for (i = 0; i < result; i++) {
//         char *substring_start = src + ovector[2*i];
//         int substring_length = ovector[2*i+1] - ovector[2*i];
//         char tempstr[260];
//         sprintf(tempstr,"%.*s",substring_length, substring_start);
// 		dst = tempstr;
//     }
// 
// 	pcre_free(re);
// 
//     return dst;
// }  
