#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define u8			uint8_t
#define u16			uint16_t
#define u32 		uint32_t
#define u64			uint64_t
#define i8			int8_t
#define i16			int16_t
#define i32			int32_t
#define i64			int64_t
#define bool		_Bool

#define SUCCESS		0
#define FAILURE		-1


i8 get_file(char *filename, u32 *len, char **buf) {
	FILE *fp = fopen(filename, "r");
	fseek(fp, 0, SEEK_END);
	*len = ftell(fp);
	rewind(fp);
	*buf = calloc(1, *len + 1);
	fread(*buf, *len, 1, fp);
	fclose(fp);
	return SUCCESS;
}
