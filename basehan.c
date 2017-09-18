/**
 * Copyright (C) 2017 Yuzhong Wen <supermartian@gmail.com>
 *
 * basehan: An algorithm that maps bytes to Chinese characters.
 * What we use here is from U+4E00 ~ U+8E00, which maps to CJK character space.
 *
 * Distributed under terms of the MIT license.
 */

/*
 * Algorithm in detail:
 * 1. Take the input string by every two bytes
 * 2. Maps the bytes to 4E00-8E00 space, similar to what base64 does
 * 3. Maps the transfromed bytes to UTF-8 space.
 *
 * CJK Symbols and Punctuation: U+3000 ~ U+303F
 * Those characters will be chosen randomly as paddings
 */

#include <unistd.h>

static inline void to_utf8_3(unsigned short in, unsigned char *out)
{
	out[0] = ((in >> 12) & 0x0F) | 0xE0;
	out[1] = ((in >> 6) & 0x3F) | 0x80;
	out[2] = (in & 0x3F) | 0x80;
}

static inline void encode_process(const unsigned char *in, unsigned char *out)
{
	unsigned char *c;
	unsigned long long *u;
	unsigned short s;
	int i;

	u = (unsigned long long *) in;
	c = (unsigned char *) in;

	for (i = 0; i < 4; i++) {
		s = 0x4E00 + (((*u) >> (i * 14)) & 0x3fff);
		to_utf8_3(s, out + i * 3);
	}

	// The last byte goes to one hanzi
	to_utf8_3(0x4E00 + in[7], out + 12);
	// 5 hanzi in total -> 15bytes output
}

static inline unsigned short from_utf8_3(const unsigned char *in)
{
	unsigned short ret = 0;
	ret = ((unsigned short) (in[0] & 0x0F)) << 12;
	ret |= ((unsigned short) (in[1] & 0x3F)) << 6;
	ret |= ((unsigned short) (in[2] & 0x3F));
	ret -= 0x4E00;
	return ret;
}

static inline void decode_process(const unsigned char *in, unsigned char *out)
{
	unsigned long long *c;
	unsigned char *u;
	unsigned short s;
	int i;

	// 5 hanzi in total -> 15bytes input
	c = (unsigned long long *) out;
	u = (unsigned char *) out;

	// First 4 hanzi
	for (i = 0; i < 4; i++) {
		s = from_utf8_3(in + i * 3);
		*c |= ((unsigned long long) (s & 0x3FFF)) << (i * 14);
	}

	// Last 1 hanzi
	s = from_utf8_3(in + 12);
	*c |= ((unsigned long long) (s & 0xFF)) << 56;
}

/**
 * From normal bytes to CJK space
 */
int cjk_mapping_encode(const char *in, ssize_t in_len, char *out, ssize_t out_len)
{
	int r_len = 0;
	unsigned char padding[8] = {0};
	int not_aligned = 0;
	int i;

	// Padding it to 8 bytes
	not_aligned = in_len % 8;

	if (out_len < 15 * (in_len / 8))
		// Not enough output buffer
		return -1;

	memset(out, 0, out_len);

	for (i = 0; i < in_len - not_aligned; i += 8) {
		encode_process(in + i, out + r_len);
		r_len += 15;
	}

	// If input is not aligned to 8 bytes, deal with the unaligned
	// bytes now
	if (not_aligned || in_len < 8) {
		memcpy(padding, in + i, not_aligned + 1);
		encode_process(padding, out + r_len);
		r_len += 15;
	}

	return r_len;
}

/**
 * From CJK space to normal bytes
 */
int cjk_mapping_decode(const char *in, ssize_t in_len, char *out, ssize_t out_len)
{
	int r_len = 0;
	unsigned char padding[8] = {0};
	int not_aligned = 0;
	int i;

	if (out_len < (in_len / 15) * 8)
		// Not enough output buffer
		return -1;

	memset(out, 0, out_len);

	for (i = 0; i < in_len; i += 15) {
		decode_process(in + i, out + r_len);
		r_len += 8;
	}

	return r_len;
}
