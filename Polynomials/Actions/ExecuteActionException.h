/*
 * Polynomials Calculator and Graph Drawing
 * Created By: Haim Adrian
 * Final Project for OOP course at Holon Institute of Technology
 * 2019-2020
 */

#pragma once

#ifndef POLYNOMIALS_EXECUTEACTIONEXCEPTION_H
#define POLYNOMIALS_EXECUTEACTIONEXCEPTION_H

#include <exception>
#include <string>

class ExecuteActionException : public std::exception
{
public:
	ExecuteActionException() { }
	explicit ExecuteActionException(char const* const _Message) :exception(_Message) { }
	ExecuteActionException(char const* const _Message, int code) :exception(_Message, code) { }
	ExecuteActionException(exception const& _Other) :exception(_Other) { }
	ExecuteActionException(const std::string & _Message) :exception(_Message.c_str()) { }
	virtual ~ExecuteActionException() = default;
};

#endif