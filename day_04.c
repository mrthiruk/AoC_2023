#include <common.h>

u32 check_line(char *winning, char *mine, u16 *num_winning) {
	u8 num_mine[100] = {0}, j = 0, num = 0;
	char *eptr = NULL;
	u32 points = 0;
	while (*mine != '\n') {
		num_mine[j] = strtoul(mine, &eptr, 10);
		j++;
		mine = eptr;
	}
	while (*(winning + 1) != '|') {
		num = strtoul(winning, &eptr, 10);
		winning = eptr;
		for (j = 0; num_mine[j]; j++) {
			if (num == num_mine[j]) {
				(*num_winning)++;
				if (points) points *= 2;
				else points = 1;
			}
		}
	}
	return points;
}

u32 scratchcards_a(char *buf) {
	u32 points = 0, i = 0;
	u16 num_winning = 0;
	char *winning, *mine;
	while (buf[i]) {
		while (buf[i++] != ':');
		winning = buf + i;
		mine = strchr(winning, '|') + 1;
		points += check_line(winning, mine, &num_winning);
		i += strchr(winning, '\n') - winning + 1;
	}
	return points;
}

u32 scratchcards_b(char *buf) {
	u32 i = 0, cards[201] = {0};
	u16 num_winning = 0;
	u8 card = 0;
	char *winning, *mine;
	while (buf[i]) {
		while (buf[i++] != ':');
		winning = buf + i;
		mine = strchr(winning, '|') + 1;
		check_line(winning, mine, &num_winning);
		cards[card]++;
		for (u8 j = 0; j < num_winning; j++) cards[card + j + 1]  += cards[card];
		card++;
		num_winning = 0;
		i += strchr(winning, '\n') - winning + 1;
	}
	i = 0;
	for (u8 j = 0; j < 201; j++) i += cards[j];
	return i;
}

i32 main(void) {
	char *buf = NULL;
	u32 len = 0;
	get_file("day_04.in", &len, &buf);
	printf("[Scratchcards A]: %u\n", scratchcards_a(buf));
	printf("[Scratchcards B]: %u\n", scratchcards_b(buf));
	free(buf);
	return 0;
}
