#include "advanced_while_programs.h"

#include <algorithm>
#include <stdexcept>

namespace while_programs {

// -------------------------------------------------------
// UTILITY

// Listing implementation
namespace {

//using Listing = std::vector<Program>;

Program make_sequence_impl(const Listing::const_iterator& begin,
	const Listing::const_iterator& end)
{
	if (std::next(begin) == end)
		return *begin;
	else
		return Seq(*begin, make_sequence_impl(std::next(begin), end));
}

}

Program make_sequence(const Listing& listing) {
	return make_sequence_impl(std::cbegin(listing), std::cend(listing));
}

// -------------------------------------------------------
// ADDITION



Program while_add_and_erase(RegisterIndex add_to, RegisterIndex erase_from) {
	return While(erase_from, Seq(Dec(erase_from), Inc(add_to)));
}

Program while_add_and_move(RegisterIndex add_to,
	RegisterIndex move_from, RegisterIndex move_to)
{
	const auto add_and_move
		= Seq(Inc(add_to), Seq(Dec(move_from), Inc(move_to)));
	return While(move_from, add_and_move);
}

Program while_add_and_restore(RegisterIndex add_to,
	RegisterIndex add_from, RegisterIndex restore_from)
{
	const auto add_and_move
		= while_add_and_move(add_to, add_from, restore_from);
	const auto restore
		= While(restore_from, Seq(Dec(restore_from), Inc(add_from)));
	return Seq(add_and_move, restore);
}

Program while_inc_n(RegisterIndex target, Nat n) {
	Listing sequence;
	std::fill_n(std::back_inserter(sequence), n, Inc(target));
	return make_sequence(sequence);
}

Program while_plus() {
	return while_sum(2);
}

Program while_sum(std::size_t n) {
	const auto add_register_n
		= while_add_and_erase(0, n);
	if (n > 1)
		return Seq(add_register_n, while_sum(n - 1));
	else if (n == 1)
		return add_register_n;
	else
		return Skip();
}

// -------------------------------------------------------
// MULTIPLICATION

Program while_multiply() {
	/*const auto add_and_move_from_2
		= while_add_and_move(0, 2, 3);
	const auto add_and_move_from_3
		= while_add_and_move(0, 3, 2);
	const auto add_from_2_or_3
		= IfZ(3, add_and_move_from_2, add_and_move_from_3);
	return While(1, Seq(Dec(1), add_from_2_or_3));*/
	return while_product(2);
}

// While product implementation
namespace {

Program while_product_impl_dec_and_store_level(std::size_t level,
	std::size_t last_level)
{
	const auto level_copy_register = last_level + level;
	return Seq(Dec(level), Inc(level_copy_register));
}

Program while_product_impl_restore_level(std::size_t level,
	std::size_t last_level) 
{
	const auto level_copy_register = last_level + level;
	return while_add_and_erase(level, level_copy_register);
}

Program while_product_impl(std::size_t level, std::size_t last_level) {
	Listing body;

	// First level doesn't need to store level
	if (level == 1)
		body.push_back(Dec(level));
	else
		body.push_back(while_product_impl_dec_and_store_level(level, last_level));

	// Outer levels recurse and restore next level
	if (level < last_level) {
		body.push_back(while_product_impl(level + 1, last_level));
		// Second to last level does not need to restore
		if(level < last_level - 1)
			body.push_back(while_product_impl_restore_level(level + 1, last_level));
	}
	// Last level performs add and move
	else {
		const auto add_from_original
			= while_add_and_move(0, level, level + 1);
		const auto add_from_copy
			= while_add_and_move(0, level + 1, level);
		return IfZ(level + 1, add_from_original, add_from_copy);
	}

	return While(level, make_sequence(body));
}

// Alternative implementation
namespace {

std::size_t alt_get_store_reg(std::size_t level, std::size_t last_level) {
	return last_level + level;
}

Program alt_dec_and_store(std::size_t level, std::size_t last_level) {
	return Seq(Dec(level), Inc(alt_get_store_reg(level, last_level)));
}

Program alt_restore(std::size_t level, std::size_t last_level) {
	return while_add_and_erase(level, alt_get_store_reg(level, last_level));
}

}

Program while_product_impl_alt(std::size_t level, std::size_t last_level) {
	Listing body;

	// First level doesn't store
	if (level == 1)
		body.push_back(Dec(level));
	else
		body.push_back(alt_dec_and_store(level, last_level));

	// Outer levels recurse and restore next level
	if (level < last_level) {
		body.push_back(while_product_impl_alt(level + 1, last_level));
		body.push_back(alt_restore(level + 1, last_level));
	}
	// Last level performs inc of 0
	else
		body.push_back(Inc(0));

	return make_sequence(body);
}

}

Program while_product(std::size_t n) {
	if (n == 0)
		return Skip();
	else
		return while_product_impl(1, n);
}

// -------------------------------------------------------
// CONSTANTS

// Base b representation of natural numbers
BaseBRepresentation::BaseBRepresentation()
	: BaseBRepresentation(2, { 0 })
{
}

BaseBRepresentation::BaseBRepresentation(Nat base,
	const BigEndianRepresentation& rep)
	: base_(base), rep_(rep)
{
	// Check validity
	const auto valid_digits = [this] {
		return std::all_of(std::cbegin(rep_), std::cend(rep_),
			[this](const Nat& n) { return n < base_; });
	};
	// Leading digit must be different from zero
	// except for the rep { 0 } which represents 0
	const auto valid_leading_digit = [this] {
		if (rep_.size() < 2)
			return true;
		else
			return rep_[0] != 0;
	};
	if (base_ < 2 || !valid_leading_digit() || !valid_digits())
		throw std::invalid_argument("Incorrenct base b representation.");

	// Initialize little endian representation
	std::reverse_copy(std::cbegin(rep_), std::cend(rep_),
		std::back_inserter(little_endian_rep_));
}

Nat BaseBRepresentation::getBase() const noexcept {
	return base_;
}

const BaseBRepresentation::BigEndianRepresentation& 
	BaseBRepresentation::getBigEndianRepresentation() const noexcept
{
	return rep_;
}

const BaseBRepresentation::LittleEndianRepresentation& 
	BaseBRepresentation::getLittleEndianRepresentation() const noexcept
{
	return little_endian_rep_;
}

// Write constant programs
Program while_write_constant_sequentially(Nat n) {
	const auto add_1 = Inc(0);
	if (n > 1)
		return Seq(add_1, while_write_constant_sequentially(n - 1));
	else if (n == 1)
		return add_1;
	else
		return Skip();
}

Program while_constant_from_factors(const std::vector<Nat>& factors)
{
	return Program();
}

// Write constant from base b implementation
namespace {

Program constant_from_base_b_body(std::size_t level, 
	const BaseBRepresentation& base_b_rep,
	RegisterIndex target)
{
	const auto rep = base_b_rep.getLittleEndianRepresentation();
	const auto base = base_b_rep.getBase();
	const auto max_level = rep.size() - 1;
	Listing body;

	// Level 0 does not dec
	if (level > 0)
		body.push_back(Dec(level));

	// Inc as many times as the current digit
	std::fill_n(std::back_inserter(body), rep[level], Inc(target));

	// Setup next level
	if (level < max_level) {
		std::fill_n(std::back_inserter(body), base, Inc(level + 1));
		body.push_back(While(level + 1,
			constant_from_base_b_body(level + 1, base_b_rep, target)));
	}

	return make_sequence(body);
}

}

Program while_write_constant_from_base_b_rep(const BaseBRepresentation& rep,
	RegisterIndex target)
{
	const auto little_rep = rep.getLittleEndianRepresentation();
	if (little_rep.size() == 1 && little_rep[0] == 0)
		return Skip();
	else
		return constant_from_base_b_body(0, rep, target);
}

// Write constant from bitshift implementation
namespace {

Program constant_bitshift_impl(std::size_t i, 
	const BaseBRepresentation& base_b_rep) 
{
	const auto& rep = base_b_rep.getBigEndianRepresentation();
	const auto n = rep.size();
	const auto work_r = i + 1;
	const auto target_r = 
		(i < n - 1) ? work_r + 1 : 0;

	Listing body;
	if (rep[i] == 1)
		body.push_back(Inc(work_r));
	body.push_back(While(work_r,
		make_sequence({ Dec(work_r), Inc(target_r), Inc(target_r) })));
	if (i < n - 1)
		body.push_back(constant_bitshift_impl(i + 1, base_b_rep));
	return make_sequence(body);
}

}

Program while_write_constant_by_bitshift(const BaseBRepresentation& rep) {
	return constant_bitshift_impl(0, rep);
}

Program loop_program_power(RegisterIndex i, Nat n, const Program& p) {
	if (n > 1)
		return Loop(i, loop_program_power(i, n - 1, p));
	else if (n == 1)
		return Loop(i, p);
	else
		return Skip();
}


// -------------------------------------------------------

}
