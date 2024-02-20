#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static char neighbors[255][2] =
{
	/* lowercase */
	['q'] = { '\0', 'w'  },
	['w'] = { 'q',  'e'  },
	['e'] = { 'w',  'r'  },
	['r'] = { 'e',  't'  },
	['t'] = { 'r',  'y'  },
	['y'] = { 't',  'u'  },
	['u'] = { 'y',  'i'  },
	['i'] = { 'u',  'o'  },
	['o'] = { 'i',  'p'  },
	['p'] = { 'o',  '\0' },
	['a'] = { '\0', 's'  },
	['s'] = { 'a',  'd'  },
	['d'] = { 's',  'f'  },
	['f'] = { 'd',  'g'  },
	['g'] = { 'f',  'h'  },
	['h'] = { 'g',  'j'  },
	['j'] = { 'h',  'k'  },
	['k'] = { 'j',  'l'  },
	['l'] = { 'k',  '\0' },
	['z'] = { '\0', 'x'  },
	['x'] = { 'z',  'c'  },
	['c'] = { 'x',  'v'  },
	['v'] = { 'c',  'b'  },
	['b'] = { 'v',  'n'  },
	['n'] = { 'b',  'm'  },
	['m'] = { 'n',  '\0' },

	/* uppercase */
	['Q'] = { '\0', 'W'  },
	['W'] = { 'Q',  'E'  },
	['E'] = { 'W',  'R'  },
	['R'] = { 'E',  'T'  },
	['T'] = { 'R',  'Y'  },
	['Y'] = { 'T',  'U'  },
	['U'] = { 'Y',  'I'  },
	['I'] = { 'U',  'O'  },
	['O'] = { 'I',  'P'  },
	['P'] = { 'O',  '\0' },
	['A'] = { '\0', 'S'  },
	['S'] = { 'A',  'D'  },
	['D'] = { 'S',  'F'  },
	['F'] = { 'D',  'G'  },
	['G'] = { 'F',  'H'  },
	['H'] = { 'G',  'J'  },
	['J'] = { 'H',  'K'  },
	['K'] = { 'J',  'L'  },
	['L'] = { 'K',  '\0' },
	['Z'] = { '\0', 'X'  },
	['X'] = { 'Z',  'C'  },
	['C'] = { 'X',  'V'  },
	['V'] = { 'C',  'B'  },
	['B'] = { 'V',  'N'  },
	['N'] = { 'B',  'M'  },
	['M'] = { 'N',  '\0' },
};

/*
 * Returns either the left or right neighbor of a character, or null (\0) if no neighbor was found/picked.
 *
 * A neighbor may not be found, either because the input was non-alphabetic, or because the randomly chosen neighbor would have gone off the sides of the QWERTY keyboard (for the Q, P, A, L, Z, and M keys).
 *
 * Seed rand before calling.
 */
char map_to_neighbor(const char c)
{
	if (rand() % 2 == 0) {
		return neighbors[(int) c][0];
	} else {
		return neighbors[(int) c][1];
	}
}

int main(int argc, char **argv)
{
	char *tail;
	char c;
	char sc;
	int n;

	if (argc != 2) {
		printf("no chance provided, see --help\n");
		return 1;
	}

	if (!strcmp(argv[1], "--help")) {
		printf(
			"Usage: %s <N>\n"
			"Repeat stdin to stdout, adding typos determined at a rate of one in N chance\n"
			"\n"
			"Examples:\n"
			"\techo Hello, world! | %s 5\n",
			argv[0],
			argv[0]
		);
		return 2;
	}

	errno = 0;
	n = strtol(argv[1], &tail, 0);
	if (errno) {
		printf("Overflow in strtol!\n");
		return -1;
	}

	srand((int) time(NULL));

	while ((c = getchar()) != EOF) {
		if (rand() % n == 0 && (sc = map_to_neighbor(c)) != '\0') {
			c = sc;
		}

		putchar(c);
	}


	return 0;
}
