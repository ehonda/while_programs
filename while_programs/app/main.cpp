#include <iostream>

#include "advanced_while_programs.h"
#include "while_programs.h"

void block() {
	std::cout << "Press Enter to end" << std::endl;
	std::cin.get();
}

void print_112_in_different_bases() {
	using namespace while_programs;

	// 1110000_2 = 112
	const auto base_2 = while_write_constant_from_base_b_rep(
		{ 2, { 1, 1, 1, 0, 0, 0, 0 } });
	std::cout << "BASE 2" << std::endl;
	std::cout << base_2 << std::endl;
	std::cout << std::endl << std::endl;


	// 11011_3 = 112
	const auto base_3 = while_write_constant_from_base_b_rep(
		{ 3, { 1, 1, 0, 1, 1 } });
	std::cout << "BASE 3" << std::endl;
	std::cout << base_3 << std::endl;
	std::cout << std::endl << std::endl;


	// 1300_4 = 112
	const auto base_4 = while_write_constant_from_base_b_rep(
		{ 4, { 1, 3, 0, 0 } });
	std::cout << "BASE 4" << std::endl;
	std::cout << base_4 << std::endl;
	std::cout << std::endl << std::endl;


	// 422_5 = 112
	const auto base_5 = while_write_constant_from_base_b_rep(
		{ 5, { 4, 2, 2 } });
	std::cout << "BASE 5" << std::endl;
	std::cout << base_5 << std::endl;
	std::cout << std::endl << std::endl;


	// 304_6 = 112
	const auto base_6 = while_write_constant_from_base_b_rep(
		{ 6, { 3, 0, 4 } });
	std::cout << "BASE 6" << std::endl;
	std::cout << base_6 << std::endl;
	std::cout << std::endl << std::endl;


	// 220_7 = 112
	const auto base_7 = while_write_constant_from_base_b_rep(
		{ 7, { 2, 2, 0 } });
	std::cout << "BASE 7" << std::endl;
	std::cout << base_7 << std::endl;
	std::cout << std::endl << std::endl;


	// 160_8 = 112
	const auto base_8 = while_write_constant_from_base_b_rep(
		{ 8, { 1, 6, 0 } });
	std::cout << "BASE 8" << std::endl;
	std::cout << base_8 << std::endl;
	std::cout << std::endl << std::endl;


	// 134_9 = 112
	const auto base_9 = while_write_constant_from_base_b_rep(
		{ 9, { 1, 3, 4 } });
	std::cout << "BASE 9" << std::endl;
	std::cout << base_9 << std::endl;
	std::cout << std::endl << std::endl;


	// 112_10 = 112
	const auto base_10 = while_write_constant_from_base_b_rep(
		{ 10, { 1, 1, 2 } });
	std::cout << "BASE 10" << std::endl;
	std::cout << base_10 << std::endl;
	std::cout << std::endl << std::endl;
}

int main(int argc, char** argv) {
	using namespace while_programs;
	//print_112_in_different_bases();

	const auto p = while_multiply();
	std::cout << p << std::endl;

	block();
	return 0;
}
