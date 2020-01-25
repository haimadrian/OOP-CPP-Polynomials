/*
 * Polynomials Calculator and Graph Drawing
 * Created By: Haim Adrian
 * Final Project for OOP course at Holon Institute of Technology
 * 2019-2020
 */

#pragma once

#ifndef POLYNOMIALS_ICLONEABLE_H
#define POLYNOMIALS_ICLONEABLE_H

template <class ReturnType>
class ICloneable
{
public:
	virtual ReturnType clone() = 0;
};

#endif