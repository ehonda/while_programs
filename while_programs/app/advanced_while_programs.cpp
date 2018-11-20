#include "advanced_while_programs.h"

#include <algorithm>
#include <stdexcept>

namespace while_programs {

// -------------------------------------------------------
// INTERNAL

namespace {

using Listing = std::vector<Program>;

Program make_sequence(const Listing::const_iterator& begin,
	const Listing::const_iterator& end)
{
	if (std::next(begin) == end)
		return *begin;
	else
		return Seq(*begin, make_sequence(std::next(begin), end));
}

Program make_sequence(const std::vector<Program>& programs) {
	return make_sequence(std::cbegin(programs), std::cend(programs));
}

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
	const auto add_and_move_from_2
		= while_add_and_move(0, 2, 3);
	const auto add_and_move_from_3
		= while_add_and_move(0, 3, 2);
	const auto add_from_2_or_3
		= IfZ(3, add_and_move_from_2, add_and_move_from_3);
	return While(1, Seq(Dec(1), add_from_2_or_3));
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
Program while_write_constant_sequentually(Nat n) {
	const auto add_1 = Inc(0);
	if (n > 1)
		return Seq(add_1, while_write_constant_sequentually(n - 1));
	else if (n == 1)
		return add_1;
	else
		return Skip();
}

// Write constant from base b implementation
namespace {

// Uses little endian rep
Program constant_from_base_b_body(std::size_t level, 
	const BaseBRepresentation& base_b_rep)
{
	const auto rep = base_b_rep.getLittleEndianRepresentation();
	const auto base = base_b_rep.getBase();
	const auto max_level = rep.size() - 1;
	Listing body;

	// Level 0 does not dec
	if (level > 0)
		body.push_back(Dec(level));

	// Inc as many times as the current digit
	std::fill_n(std::back_inserter(body), rep[level], Inc(0));

	// Setup next level
	if (level < max_level) {
		std::fill_n(std::back_inserter(body), base, Inc(level + 1));
		body.push_back(While(level + 1,
			constant_from_base_b_body(level + 1, base_b_rep)));
	}

	return make_sequence(body);
}

}

Program while_write_constant_from_base_b_rep(const BaseBRepresentation& rep)
{
	const auto little_rep = rep.getLittleEndianRepresentation();
	if (little_rep.size() == 1 && little_rep[0] == 0)
		return Skip();
	else
		return constant_from_base_b_body(0, rep);
}


// -------------------------------------------------------

}
