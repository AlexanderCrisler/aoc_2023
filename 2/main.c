/*
--- Day 1: Trebuchet?! ---

Something is wrong with global snow production, and you've been selected to take a look. The Elves have even given you a map; on it, they've used stars to mark the top fifty locations that are likely to be having problems.

You've been doing this long enough to know that to restore snow operations, you need to check all fifty stars by December 25th.

Collect stars by solving puzzles. Two puzzles will be made available on each day in the Advent calendar; the second puzzle is unlocked when you complete the first. Each puzzle grants one star. Good luck!

You try to ask why they can't just use a weather machine ("not powerful enough") and where they're even sending you ("the sky") and why your map looks mostly blank ("you sure ask a lot of questions") and hang on did you just say the sky ("of course, where do you think snow comes from") when you realize that the Elves are already loading you into a trebuchet ("please hold still, we need to strap you in").

As they're making the final adjustments, they discover that their calibration document (your puzzle input) has been amended by a very young Elf who was apparently just excited to show off her art skills. Consequently, the Elves are having trouble reading the values on the document.

The newly-improved calibration document consists of lines of text; each line originally contained a specific calibration value that the Elves now need to recover. On each line, the calibration value can be found by combining the first digit and the last digit (in that order) to form a single two-digit number.

For example:

1abc2
pqr3stu8vwx
a1b2c3d4e5f
treb7uchet

In this example, the calibration values of these four lines are 12, 38, 15, and 77. Adding these together produces 142.

Consider your entire calibration document. What is the sum of all of the calibration values?
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const char num_strings[10][6] = {
		"zero", "one", "two",
		"three", "four", "five",
		"six", "seven", "eight",
		"nine"
	};

int check_substring(char substring[]);
void reset_num_word(char string[6], int *iter);

int main() {
	FILE *fp;
	fp = fopen("puzzle_input.txt", "r");

	char first_int = '0';
	char last_int = '0';
	char num_word[6];
	char result[] = "00";
	int word_iter = 0;
	int total = 0;

	char cur_char;

	while(cur_char != EOF) {
		cur_char = fgetc(fp);
		if (isdigit(cur_char)) {
			if (first_int == '0') {
				first_int = cur_char;
			}

			last_int = cur_char;
			memset(num_word, 0, sizeof(num_word));
			word_iter = 0;
		} else if (isalpha(cur_char)) {

			num_word[word_iter] = cur_char;
			word_iter = strlen(num_word);
			//printf("numword: %s\n", num_word);
			//printf("numword length: %i\n", (int)strlen(num_word));

			while (strlen(num_word) > 1 && !check_substring(num_word)) {
				printf("no substring: %s; num word remove first letter\n", num_word);
				reset_num_word(num_word, &word_iter);
			}

			if (strlen(num_word) <= 7) {
				for (int i=0; i<=9; i++) {
					if (strcmp(num_word, num_strings[i]) == 0) {
						if (first_int == '0') {
							first_int = i + '0';
						}
						last_int = i + '0';

						reset_num_word(num_word, &word_iter);
						// char last_letter[2] = {num_word[strlen(num_word) - 1]};

						// if (check_substring(last_letter)) {
						// 	memset(num_word, 0, sizeof(num_word));
						// 	num_word[0] = last_letter[0];
						// 	word_iter = 1;

						// 	break;
						// } else {
						// 	memset(num_word, 0, sizeof(num_word));
						// 	word_iter = 0;
						// }
					}
				}
			} else {
				//printf("reset num word");
				// memset(num_word, 0, sizeof(num_word));
				// word_iter = 0;
				reset_num_word(num_word, &word_iter);
			}
		} else if (cur_char == '\n') {
			result[0] = first_int;
			result[1] = last_int;
			printf("%s\n", result);
			total += atoi(result);

			first_int = '0';
			last_int = '0';
			strcpy(result, "00");

			memset(num_word, 0, sizeof(num_word));
			word_iter = 0;
		}

	}

	printf("Total: %i\n", total);
	return 0;
}

int check_substring(char substring[]) {
		char temp_str[6];
		for (int i=0; i<=9; i++) {
			//if (strspn(num_strings[i], substring) == strlen(substring)) {
			strncpy(temp_str, num_strings[i], strlen(substring));

			if (strstr(temp_str, substring) != NULL) {
				//printf("substring found: %s, %s, %s\n", num_strings[i], temp_str, substring);
				return 1;
			}
		}
		memset(temp_str, 0, sizeof(temp_str));
		return 0;
}

void reset_num_word(char string[6], int *iter) {
	char temp_str[6];
	memset(temp_str, 0, sizeof(temp_str));
	strcpy(temp_str, string+1);
	memset(string, 0, sizeof(&string));
	strcpy(string, temp_str);
	*iter = strlen(string);
	return;
}
