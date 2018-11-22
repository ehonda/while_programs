#include <algorithm>
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

void print_56_in_different_bases() {
	using namespace while_programs;
	// 111000_2 = 56
	const auto base_2 = while_write_constant_from_base_b_rep(
		{ 2, { 1, 1, 1, 0, 0, 0,  } });
	std::cout << "BASE 2" << std::endl;
	std::cout << base_2 << std::endl;
	std::cout << std::endl << std::endl;

	// 2002_3 = 56
	const auto base_3 = while_write_constant_from_base_b_rep(
		{ 3, { 2, 0, 0, 2 } });
	std::cout << "BASE 3" << std::endl;
	std::cout << base_3 << std::endl;
	std::cout << std::endl << std::endl;

	// 320_4 = 56
	const auto base_4 = while_write_constant_from_base_b_rep(
		{ 4, { 3, 2, 0 } });
	std::cout << "BASE 4" << std::endl;
	std::cout << base_4 << std::endl;
	std::cout << std::endl << std::endl;

	// 211_5 = 56
	const auto base_5 = while_write_constant_from_base_b_rep(
		{ 5, { 2, 1, 1 } });
	std::cout << "BASE 5" << std::endl;
	std::cout << base_5 << std::endl;
	std::cout << std::endl << std::endl;

	// 132_6 = 56
	const auto base_6 = while_write_constant_from_base_b_rep(
		{ 6, { 1, 3, 2 } });
	std::cout << "BASE 6" << std::endl;
	std::cout << base_6 << std::endl;
	std::cout << std::endl << std::endl;

	// 110_7 = 56
	const auto base_7 = while_write_constant_from_base_b_rep(
		{ 7, { 1, 1, 0 } });
	std::cout << "BASE 7" << std::endl;
	std::cout << base_7 << std::endl;
	std::cout << std::endl << std::endl;

	// 70_8 = 56
	const auto base_8 = while_write_constant_from_base_b_rep(
		{ 8, { 7, 0 } });
	std::cout << "BASE 8" << std::endl;
	std::cout << base_8 << std::endl;
	std::cout << std::endl << std::endl;
}

int main(int argc, char** argv) {
	using namespace while_programs;
	//print_112_in_different_bases();
	//print_56_in_different_bases();

	/*const auto p = while_write_constant_by_bitshift(
		{ 2, {1, 1, 0, 0} });
	std::cout << p << std::endl;*/

	//// 320_4 = 56
	//const auto base_4 = while_write_constant_from_base_b_rep(
	//	{ 4, { 3, 2, 0 } }, 3);
	//std::cout << "BASE 4" << std::endl;
	//std::cout << base_4 << std::endl;
	//std::cout << std::endl << std::endl;

	//const auto dbl_3_to_0 = While(3, Seq(Dec(3), Seq(Inc(0), Inc(0))));

	//const auto p = Seq(base_4, dbl_3_to_0);
	//std::cout << p << std::endl;

	/*const auto base_4 = while_write_constant_from_base_b_rep(
		{ 4,{ 3, 2, 0 } });
	Listing body = { Inc(3), Inc(3) };
	body.push_back(While(3, Seq(Dec(3), base_4)));
	const auto p = make_sequence(body);
	std::cout << p << std::endl;*/

	//const auto base_5 = while_write_constant_from_base_b_rep(
	//	{ 5, { 4, 4} }, 2);
	////Listing body = { Inc(3)}
	////std::cout << base_5 << std::endl;
	//Listing body = { base_5, Inc(2), Inc(2) };
	//std::fill_n(std::back_inserter(body), 4, Inc(3));
	//body.push_back(While(3, make_sequence({ Dec(3), Inc(0) })));
	//const auto p = make_sequence(body);
	//std::cout << p << std::endl;

	// While-112 in of size 35
	/*Listing body_2 = { Dec(2) };
	std::fill_n(std::back_inserter(body_2), 7, Inc(0));

	Listing body_1 = { Dec(1) };
	std::fill_n(std::back_inserter(body_1), 4, Inc(2));
	body_1.push_back(While(2, make_sequence(body_2)));

	Listing body_0;
	std::fill_n(std::back_inserter(body_0), 4, Inc(1));
	body_0.push_back(While(1, make_sequence(body_1)));

	const auto p = make_sequence(body_0);
	std::cout << p << std::endl;

	RegisterMemory m;
	p(m);
	std::cout << "c = " << readOutput(m) << std::endl;*/

	// Loop-117
	/*Listing body;
	std::fill_n(std::back_inserter(body), 3, Inc(1));
	body.push_back(
		Loop(1,
			Seq(Seq(Inc(2), Inc(2)), Loop 1, 
				(Loop 1)))*/

	// Loop-117 (failed)
	/*Listing body;
	body.push_back(Inc(1));
	body.push_back(loop_program_power(1, 3, Seq(Inc(1), Inc(2))));
	body.push_back(loop_program_power(2, 2,
	make_sequence({ Loop(1, Inc(0)), loop_program_power(2, 2, Inc(0)) })));
	const auto p = make_sequence(body);*/

	// Exponentiation
	/*body.push_back(while_inc_n(1, 3));
	body.push_back(loop_program_power(1, 5, Inc(0)));*/

	// Loop-117
	Listing body;
	body.push_back(while_inc_n(1, 2));
	body.push_back(loop_program_power(1, 1, while_inc_n(2, 2)));
	body.push_back(While(1, loop_program_power(2, 3, Inc(0))));
	const auto p = make_sequence(body);
	std::cout << p << std::endl;

	RegisterMemory m;
	p(m);
	std::cout << "c = " << readOutput(m) << std::endl;

	block();
	return 0;
}
