#include <common.h>


char *colors[3] = {"red", "green", "blue"};
u8 num_colors[3] = {12, 13, 14}, len_colors[3] = {3, 5, 4};

bool check_token(char *buf, u32 *i) {
	char num[3] = {0};
	u8 j = 0, n;
	u32 ind = *i;
	while (47 < buf[ind] && buf[ind] < 58) num[j++] = buf[ind++];
	n = strtoul(num, NULL, 10);
	ind++;
	for (j = 0; j < 3; j++) {
		if (!strncmp(buf + ind, colors[j], len_colors[j])) {
			ind += len_colors[j];
			break;
		}
	}
	*i = ind;
	if (n > num_colors[j]) return 1;
	return 0;
}

u16 get_valid_game_ids_sum(char *buf) {
	u16 sum = 0, curr_id = 1;
	u32 i = 0;
	bool found_colon = 1, not_valid = 1;
	while (buf[i]) {
		if (found_colon) {
			while (buf[i++] != ':');
			not_valid = 1;
			found_colon = 0;
		}
		if (buf[i] == ' ') {
			i++;
			continue;
		}
		if (check_token(buf, &i)) {
			not_valid = 0;
			while (buf[i] != '\n') i++;
		}
		if (buf[i] == '\n') {
			if(not_valid) {
				sum += curr_id;
			}
			curr_id++;
			found_colon = 1;
		}
		i++;
	}
	return sum;
}

void get_token(char *buf, u32 *i, u8 min_colors[static 3], 
		u8 found_colors[static 3]) {
	char num[3] = {0};
	u8 j = 0, n;
	u32 ind = *i;
	while (47 < buf[ind] && buf[ind] < 58) num[j++] = buf[ind++];
	n = strtoul(num , NULL, 10);
	ind++;
	for (j = 0; j < 3; j++) {
		if (!strncmp(buf + ind, colors[j], len_colors[j])) {
			if (!found_colors[j]) {
				min_colors[j] = n;
				found_colors[j] = 1;
			}
			else if (found_colors[j] && n > min_colors[j]) min_colors[j] = n;
			ind += len_colors[j];
			break;
		}
	}
	*i = ind;
}

u64 get_sum_of_powers_of_min(char *buf) {
	u64 sum = 0;
	u8 min_colors[3], found_colors[3] = {0};
	bool found_colon = 1;
	u32 i = 0;
	while (buf[i]) {
		if (found_colon) {
			while (buf[i++] != ':');
			found_colon = 0;
		}
		if (buf[i] == ' ') {
			i++;
			continue;
		}
		get_token(buf, &i, min_colors, found_colors);
		if (buf[i] == '\n') {
			sum += (min_colors[0] * min_colors[1] * min_colors[2]);
			found_colon = 1;
			memset(found_colors, 0, 3);
		}
		i++;
	}
	return sum;
}

i32 main(void) {
	char *buf = NULL;
	u32 len = 0;
	get_file("day_02.in", &len, &buf);
	printf("Sum of valid game IDs: %u\n", get_valid_game_ids_sum(buf));
	printf("Sum of powers: %lu\n", get_sum_of_powers_of_min(buf));
	free(buf);
	return SUCCESS;
}
