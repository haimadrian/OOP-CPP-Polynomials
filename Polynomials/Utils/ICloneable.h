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