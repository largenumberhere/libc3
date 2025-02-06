#include "../../include/ints.hpp"
#include "../../include/mangled.hpp"

enum : size_t {
    LEN = 32,	// NB: must be the same as header file
};

// #define LEN 32	//

extern "C" void libc3IntegerToString(size_t val, char *buff_out) {
	libc3Memset(buff_out, 0, LEN);

	int len_outa = 0;
	int* len_out = &len_outa;

	if (val ==0) {
		buff_out[0] = '0';
		*len_out = 1;
		return;
	}
	
	char tmp[32] = {0};

	size_t string_pos = 0;

	size_t c = 0;
	char m = '\0';

	while (val > 0)
	{
		c = val % 10;
		val = val / 10;
		m = (char) '0' + c;
		tmp[string_pos++] = m;
	}

	int len = 0;
	for (ssize_t i = string_pos; i >=0; i--) {
		if (tmp[i] == '\0') {continue;}	// workaround for the off-by-one bug hidden in here
		buff_out[len++] = tmp[i];
	}
	
	*len_out = len;
	
    return;
}