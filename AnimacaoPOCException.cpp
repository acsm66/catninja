#include "stdafx.h"
#include "AnimacaoPOCException.h"

AnimacaoPOCException::AnimacaoPOCException(const std::string &msg) : _msg(msg) {}

const char *AnimacaoPOCException::what() {
	if (_msg.empty()) {
		return "Erro generico";
	}
	return _msg.c_str();
}
