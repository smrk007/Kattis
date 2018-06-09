#include <iostream>

int main() {

	int R, C;
	std::cin >> R >> C;

	char display[R][C];
	char model[R][C];

	for (int r = 0; r < R; r++) {

		char newline;
		std::cin >> std::noskipws >> newline;

		for (int c = 0; c < C; c++) {
			char next;
			std::cin >> std::noskipws >> next;
			display[r][c] = next;
			if (next == " ") {
				model[r][c] = 0;
			} else {
				model[r][c] = 1;
			}
		}

		std::cout << std::endl;
	}	

	

	return 0;
}
