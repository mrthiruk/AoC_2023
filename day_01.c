#include "common.h"

char *digits[10] = {
	"zero", "one", "two", "three", "four", 
	"five", "six", "seven", "eight", "nine"
};

u8 digit_lens[10] = {4, 3, 3, 5, 4, 4, 3, 5, 5, 4};

u64 get_calib_sum_v1(u32 len, char *buf) {
	u8 first, last;
	u64 sum = 0;
	bool found_first = 1;
	u32 i = 0;
	while (buf[i]) {
		if (buf[i] == '\n') {
			sum += (first * 10 + last);
			found_first = 1;
		} else if (buf[i] > 47 && buf[i] < 58) {
			if (found_first) {
				first = buf[i] - '0';
				found_first = 0;
			}
			last = buf[i] - '0';
		}
		i++;
	}
	return sum;
}

bool cmp_digit_str(char *buf, u8 *res) {
	for (u8 i = 0; i < 10; i++) {
		if (!strncmp(buf, digits[i], digit_lens[i])) {
			*res = i;
			return 1;
		}
	}
	return 0;
}

u64 get_calib_sum_v2(u32 len, char *buf) {
	u8 first, last, temp;
	u64 sum = 0;
	bool found_first = 1;
	u32 i = 0;
	while (buf[i]) {
		if (buf[i] == '\n') {
			sum += (first * 10 + last);
			found_first = 1;
		} else if (buf[i] > 47 && buf[i] < 58) {
			if (found_first) {
				first = buf[i] - '0';
				found_first = 0;
			}
			last = buf[i] - '0';
		} else if (cmp_digit_str(buf + i, &temp)) {
			if (found_first) {
				first = temp;
				found_first = 0;
			}
			last = temp;
		}
		i++;
	}
	return sum;
}

int main(void) {
	char *filename = "day_01.in";
	char *buf = NULL;
	u32 len = 0;
	get_file(filename, &len, &buf);
	printf("Sum of calibration values v1: %lu\n", get_calib_sum_v1(len, buf));
	printf("Sum of calibration values v2: %lu\n", get_calib_sum_v2(len, buf));
	return SUCCESS;
}
