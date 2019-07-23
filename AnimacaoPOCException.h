#pragma once

#include "stdafx.h"

class AnimacaoPOCException : public std::exception {
public:
	AnimacaoPOCException(const std::string &msg);
	const char *what();

private:
	std::string _msg;
};
