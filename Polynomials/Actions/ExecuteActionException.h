#pragma once

#ifndef POLYNOMIALS_EXECUTEACTIONEXCEPTION_H
#define POLYNOMIALS_EXECUTEACTIONEXCEPTION_H

#include <exception>

class ExecuteActionException : public std::exception {
public:
	ExecuteActionException() {}
	explicit ExecuteActionException(char const* const _Message) :exception(_Message) {}
	ExecuteActionException(char const* const _Message, int code):exception(_Message, code) {}
	ExecuteActionException(exception const& _Other):exception(_Other) {}
	virtual ~ExecuteActionException() = default;
};

#endif