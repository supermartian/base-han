/**
 * Copyright (C) 2017 Yuzhong Wen <supermartian@gmail.com>
 *
 * basehan test cases
 *
 * Distributed under terms of the MIT license.
 */

#include <string.h>
#include <stdio.h>

ssize_t get_encode_len(ssize_t in)
{
	return ((in + 7) / 8) * 15;
}

ssize_t get_decode_len(ssize_t out)
{
	return (out / 15) * 8;
}

void test_000()
{
	char in[1024]="这是一个测试项，用来测试utf8";
	char out[1024];
	ssize_t len_in = strlen(in);

	printf("\n==Testing UTF-8 encoding/decoding ===\n");

	printf("%s\n", in);

	memset(out, 0, 1024);
	len_in = cjk_mapping_encode(in, len_in, out, get_encode_len(len_in));
	printf("%s\n", out);

	memset(in, 0, 1024);
	cjk_mapping_decode(out, len_in, in, get_decode_len(len_in));
	printf("%s\n", in);
}

void test_001()
{
	char in[1024]="lel";
	char out[1024];
	ssize_t len_in = strlen(in);

	printf("\n==Testing ASCII encoding/decoding ===\n");

	printf("%s\n", in);

	memset(out, 0, 1024);
	len_in = cjk_mapping_encode(in, len_in, out, get_encode_len(len_in));
	printf("%s\n", out);

	memset(in, 0, 1024);
	cjk_mapping_decode(out, len_in, in, get_decode_len(len_in));
	printf("%s\n", in);
}

void test_002()
{
	char in[1024]="llellellellellellellellellellellellellellellellellellelel";
	char out[1024];
	ssize_t len_in = strlen(in);

	printf("\n==Testing Long ASCII encoding/decoding ===\n");

	printf("%s\n", in);

	memset(out, 0, 1024);
	len_in = cjk_mapping_encode(in, len_in, out, get_encode_len(len_in));
	printf("%s\n", out);

	memset(in, 0, 1024);
	cjk_mapping_decode(out, len_in, in, get_decode_len(len_in));
	printf("%s\n", in);
}

void test_003()
{
	char in[1024]={0x2, 0x3, 0x4, 0x5, 0x6, 0x7};
	char out[1024];
	int i;
	ssize_t len_in = 6;

	printf("\n==Testing binary encoding/decoding ===\n");

	for (i = 0; i < 6; i++)
		printf("%x ", in[i]);
	printf("\n");

	memset(out, 0, 1024);
	len_in = cjk_mapping_encode(in, len_in, out, get_encode_len(len_in));
	printf("%s\n", out);

	memset(in, 0, 1024);
	cjk_mapping_decode(out, len_in, in, get_decode_len(len_in));
	for (i = 0; i < 6; i++)
		printf("%x ", in[i]);

	printf("\n");

	printf("=====\n");
}

void test_004()
{
	char in[1024]={0x2, 0x3, 0x4, 0x5,
					0x6, 0x7, 0x3, 0x4,
					0x5, 0x6, 0x7, 0x3,
					0x4, 0x5, 0x6, 0x7};
	char out[1024];
	int i;
	ssize_t len_in = 16;

	printf("\n==Testing long binary encoding/decoding ===\n");

	for (i = 0; i < 16; i++)
		printf("%x ", in[i]);
	printf("\n");

	memset(out, 0, 1024);
	len_in = cjk_mapping_encode(in, len_in, out, get_encode_len(len_in));
	printf("%s\n", out);

	memset(in, 0, 1024);
	cjk_mapping_decode(out, len_in, in, get_decode_len(len_in));
	for (i = 0; i < 16; i++)
		printf("%x ", in[i]);

	printf("\n");

	printf("=====\n");
}
int main()
{
	test_000();
	test_001();
	test_002();
	test_003();
	test_004();
	return 0;
}
