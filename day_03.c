#include <common.h>

bool check_for_symbols(char *buf, u16 start, u16 end) {
	if (start) start--;
	if (buf[end + 1] != '\n') end++;
	while (start <= end) {
		if ((buf[start] < 48 || buf[start] > 57) && buf[start] != '.') return 1;
		start++;
	}
	return 0;
}

u32 gear_ratios_a(char *buf) {
	u32 sum = 0, i = 0;
	u16 start, end, line_end, num;
	char *prev = NULL, *curr = buf, *next = strchr(buf, '\n') + 1, *eptr = NULL;
	while (curr[i]) {
		if (!i) line_end = (strchr(curr, '\n') - curr);
		if (47 < curr[i] && curr[i] < 58) {
			num = strtoul(curr + i, &eptr, 10);
			start = i;
			if ((end = eptr - curr - 1) >= line_end) end = line_end;
			i = end;
			if ((prev &&check_for_symbols(prev, start, end)) || 
					(next && check_for_symbols(next, start, end)) ||
					check_for_symbols(curr, start, end)) {
				sum += num;
			}
		}
		if (curr[i] == '\n') {
			prev = curr;
			curr = next;
			if (!next) break;
			if (!next[i + 1]) next = NULL;
			else next += i + 1;
			i = 0;
			continue;
		}
		i++;
	}
	return sum;
}

void get_adjs(char *buf, u16 ind, u64 *product, u8 *num_adjs) {
	u16 i = 0, start, end, num;
	start = ind - 1;
	end = ind + 1;

	if (!ind) {
		start = ind;
		end = 1;
	}
	if (buf[ind + 1] == '\n') {
		start = ind - 1;
		end = ind;
	}
	char *eptr = NULL;
	while (buf[i] != '\n') {
		if (47 < buf[i] && buf[i] < 58) {
			num = strtoul(buf + i, &eptr, 10);
			if (start <= (eptr - buf - 1) && end >= i) {
				*product = (*product * num);
				(*num_adjs)++;
			}
			i  = eptr - buf;
			continue;
		}
		i++;
	}
}

u64 gear_ratios_b(char *buf) {
	u64 sum = 0, product = 1;
	u16 i = 0;
	u8 num_adjs = 0;
	char *prev = NULL, *curr = buf, *next = strchr(buf, '\n') + 1;
	while (curr[i]) {
		if (curr[i] == '*') {
			if (prev) get_adjs(prev, i, &product, &num_adjs);
			get_adjs(curr, i, &product, &num_adjs);
			if (next) get_adjs(next, i, &product, &num_adjs);
			if (num_adjs == 2) sum += product;
			num_adjs = 0;
			product = 1;
		}
		if (curr[i] == '\n') {
			prev = curr;
			curr = next;
			if (!next) break;
			if (!next[i + 1]) next = NULL;
			else next += i + 1;
			i = 0;
			product = 1;
			num_adjs = 0;
			continue;
		}
		i++;
	}
	return sum;
}

i32 main(void) {
	u32 len = 0;
	char *buf = NULL;
	get_file("day_03.in", &len, &buf);
	printf("[Gear ratios part A]: %u\n", gear_ratios_a(buf));
	printf("[Gear ratios part B]: %lu\n", gear_ratios_b(buf));
	return SUCCESS;
}
