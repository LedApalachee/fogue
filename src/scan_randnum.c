#include <stdlib.h>
#include <randnum.h>
#include "errors.h"


int scan_randint64_t(randint64_t* rn, char* str, char terminator)
{
	char str2[200];
	int ig = 0;
	int i2 = 0;
	int sel_count = 0;
	// the number is range-based random
	if (str[0] == 'r')
	{
		// scanning the lower
		for (ig = 1; str[ig] != '-'; ++ig)
			str2[ig-1] = str[ig];
		str2[ig-1] = '-';
		rn->start = atoi(str2);
		// scanning the higher
		++ig;
		for (i2 = 0; str[ig] != terminator; ++ig, ++i2)
			str2[i2] = str[ig];
		str2[i2] = terminator;
		rn->end = atoi(str2);
	}
	// the number is select-based random
	else if (str[0] == 's')
	{
		for (ig = 1, i2 = 0; sel_count < MAX_RANDNUM_MEMBERS; ++ig, ++i2)
		{
			str2[i2] = str[ig];
			if (str[ig] == '%')
			{
				rn->set[sel_count].i = atoi(str2);
				i2 = -1;
			}
			else if (str[ig] == '|')
			{
				rn->set[sel_count].p = atoi(str2);
				i2 = -1;
				++sel_count;
			}
			else if (str[ig] == terminator)
			{
				rn->set[sel_count].p = atoi(str2);
				break;
			}
		}
	}
	// the number is not random
	else
	{
		for (i2 = 0; str[i2] != terminator; ++i2)
			str2[i2] = str[i2];
		str2[i2] = str[i2];
		rn->start = rn->end = atoi(str2);
		rn->set[0].p = 0;
	}
	return ALL_GOOD;
}




int scan_randint32_t(randint32_t* rn, char* str, char terminator)
{
	char str2[200];
	int ig = 0;
	int i2 = 0;
	int sel_count = 0;
	// the number is range-based random
	if (str[0] == 'r')
	{
		// scanning the lower
		for (ig = 1; str[ig] != '-'; ++ig)
			str2[ig-1] = str[ig];
		str2[ig-1] = '-';
		rn->start = atoi(str2);
		// scanning the higher
		++ig;
		for (i2 = 0; str[ig] != terminator; ++ig, ++i2)
			str2[i2] = str[ig];
		str2[i2] = terminator;
		rn->end = atoi(str2);
	}
	// the number is select-based random
	else if (str[0] == 's')
	{
		for (ig = 1, i2 = 0; sel_count < MAX_RANDNUM_MEMBERS; ++ig, ++i2)
		{
			str2[i2] = str[ig];
			if (str[ig] == '%')
			{
				rn->set[sel_count].i = atoi(str2);
				i2 = -1;
			}
			else if (str[ig] == '|')
			{
				rn->set[sel_count].p = atoi(str2);
				i2 = -1;
				++sel_count;
			}
			else if (str[ig] == terminator)
			{
				rn->set[sel_count].p = atoi(str2);
				break;
			}
		}
	}
	// the number is not random
	else
	{
		for (i2 = 0; str[i2] != terminator; ++i2)
			str2[i2] = str[i2];
		str2[i2] = str[i2];
		rn->start = rn->end = atoi(str2);
		rn->set[0].p = 0;
	}
	return ALL_GOOD;
}




int scan_randint16_t(randint16_t* rn, char* str, char terminator)
{
	char str2[200];
	int ig = 0;
	int i2 = 0;
	int sel_count = 0;
	// the number is range-based random
	if (str[0] == 'r')
	{
		// scanning the lower
		for (ig = 1; str[ig] != '-'; ++ig)
			str2[ig-1] = str[ig];
		str2[ig-1] = '-';
		rn->start = atoi(str2);
		// scanning the higher
		++ig;
		for (i2 = 0; str[ig] != terminator; ++ig, ++i2)
			str2[i2] = str[ig];
		str2[i2] = terminator;
		rn->end = atoi(str2);
	}
	// the number is select-based random
	else if (str[0] == 's')
	{
		for (ig = 1, i2 = 0; sel_count < MAX_RANDNUM_MEMBERS; ++ig, ++i2)
		{
			str2[i2] = str[ig];
			if (str[ig] == '%')
			{
				rn->set[sel_count].i = atoi(str2);
				i2 = -1;
			}
			else if (str[ig] == '|')
			{
				rn->set[sel_count].p = atoi(str2);
				i2 = -1;
				++sel_count;
			}
			else if (str[ig] == terminator)
			{
				rn->set[sel_count].p = atoi(str2);
				break;
			}
		}
	}
	// the number is not random
	else
	{
		for (i2 = 0; str[i2] != terminator; ++i2)
			str2[i2] = str[i2];
		str2[i2] = str[i2];
		rn->start = rn->end = atoi(str2);
		rn->set[0].p = 0;
	}
	return ALL_GOOD;
}




int scan_randint8_t(randint8_t* rn, char* str, char terminator)
{
	char str2[200];
	int ig = 0;
	int i2 = 0;
	int sel_count = 0;
	// the number is range-based random
	if (str[0] == 'r')
	{
		// scanning the lower
		for (ig = 1; str[ig] != '-'; ++ig)
			str2[ig-1] = str[ig];
		str2[ig-1] = '-';
		rn->start = atoi(str2);
		// scanning the higher
		++ig;
		for (i2 = 0; str[ig] != terminator; ++ig, ++i2)
			str2[i2] = str[ig];
		str2[i2] = terminator;
		rn->end = atoi(str2);
	}
	// the number is select-based random
	else if (str[0] == 's')
	{
		for (ig = 1, i2 = 0; sel_count < MAX_RANDNUM_MEMBERS; ++ig, ++i2)
		{
			str2[i2] = str[ig];
			if (str[ig] == '%')
			{
				rn->set[sel_count].i = atoi(str2);
				i2 = -1;
			}
			else if (str[ig] == '|')
			{
				rn->set[sel_count].p = atoi(str2);
				i2 = -1;
				++sel_count;
			}
			else if (str[ig] == terminator)
			{
				rn->set[sel_count].p = atoi(str2);
				break;
			}
		}
	}
	// the number is not random
	else
	{
		for (i2 = 0; str[i2] != terminator; ++i2)
			str2[i2] = str[i2];
		str2[i2] = str[i2];
		rn->start = rn->end = atoi(str2);
		rn->set[0].p = 0;
	}
	return ALL_GOOD;
}




int scan_randuint64_t(randuint64_t* rn, char* str, char terminator)
{
	char str2[200];
	int ig = 0;
	int i2 = 0;
	int sel_count = 0;
	// the number is range-based random
	if (str[0] == 'r')
	{
		// scanning the lower
		for (ig = 1; str[ig] != '-'; ++ig)
			str2[ig-1] = str[ig];
		str2[ig-1] = '-';
		rn->start = atoi(str2);
		// scanning the higher
		++ig;
		for (i2 = 0; str[ig] != terminator; ++ig, ++i2)
			str2[i2] = str[ig];
		str2[i2] = terminator;
		rn->end = atoi(str2);
	}
	// the number is select-based random
	else if (str[0] == 's')
	{
		for (ig = 1, i2 = 0; sel_count < MAX_RANDNUM_MEMBERS; ++ig, ++i2)
		{
			str2[i2] = str[ig];
			if (str[ig] == '%')
			{
				rn->set[sel_count].i = atoi(str2);
				i2 = -1;
			}
			else if (str[ig] == '|')
			{
				rn->set[sel_count].p = atoi(str2);
				i2 = -1;
				++sel_count;
			}
			else if (str[ig] == terminator)
			{
				rn->set[sel_count].p = atoi(str2);
				break;
			}
		}
	}
	// the number is not random
	else
	{
		for (i2 = 0; str[i2] != terminator; ++i2)
			str2[i2] = str[i2];
		str2[i2] = str[i2];
		rn->start = rn->end = atoi(str2);
		rn->set[0].p = 0;
	}
	return ALL_GOOD;
}




int scan_randuint32_t(randuint32_t* rn, char* str, char terminator)
{
	char str2[200];
	int ig = 0;
	int i2 = 0;
	int sel_count = 0;
	// the number is range-based random
	if (str[0] == 'r')
	{
		// scanning the lower
		for (ig = 1; str[ig] != '-'; ++ig)
			str2[ig-1] = str[ig];
		str2[ig-1] = '-';
		rn->start = atoi(str2);
		// scanning the higher
		++ig;
		for (i2 = 0; str[ig] != terminator; ++ig, ++i2)
			str2[i2] = str[ig];
		str2[i2] = terminator;
		rn->end = atoi(str2);
	}
	// the number is select-based random
	else if (str[0] == 's')
	{
		for (ig = 1, i2 = 0; sel_count < MAX_RANDNUM_MEMBERS; ++ig, ++i2)
		{
			str2[i2] = str[ig];
			if (str[ig] == '%')
			{
				rn->set[sel_count].i = atoi(str2);
				i2 = -1;
			}
			else if (str[ig] == '|')
			{
				rn->set[sel_count].p = atoi(str2);
				i2 = -1;
				++sel_count;
			}
			else if (str[ig] == terminator)
			{
				rn->set[sel_count].p = atoi(str2);
				break;
			}
		}
	}
	// the number is not random
	else
	{
		for (i2 = 0; str[i2] != terminator; ++i2)
			str2[i2] = str[i2];
		str2[i2] = str[i2];
		rn->start = rn->end = atoi(str2);
		rn->set[0].p = 0;
	}
	return ALL_GOOD;
}




int scan_randuint16_t(randuint16_t* rn, char* str, char terminator)
{
	char str2[200];
	int ig = 0;
	int i2 = 0;
	int sel_count = 0;
	// the number is range-based random
	if (str[0] == 'r')
	{
		// scanning the lower
		for (ig = 1; str[ig] != '-'; ++ig)
			str2[ig-1] = str[ig];
		str2[ig-1] = '-';
		rn->start = atoi(str2);
		// scanning the higher
		++ig;
		for (i2 = 0; str[ig] != terminator; ++ig, ++i2)
			str2[i2] = str[ig];
		str2[i2] = terminator;
		rn->end = atoi(str2);
	}
	// the number is select-based random
	else if (str[0] == 's')
	{
		for (ig = 1, i2 = 0; sel_count < MAX_RANDNUM_MEMBERS; ++ig, ++i2)
		{
			str2[i2] = str[ig];
			if (str[ig] == '%')
			{
				rn->set[sel_count].i = atoi(str2);
				i2 = -1;
			}
			else if (str[ig] == '|')
			{
				rn->set[sel_count].p = atoi(str2);
				i2 = -1;
				++sel_count;
			}
			else if (str[ig] == terminator)
			{
				rn->set[sel_count].p = atoi(str2);
				break;
			}
		}
	}
	// the number is not random
	else
	{
		for (i2 = 0; str[i2] != terminator; ++i2)
			str2[i2] = str[i2];
		str2[i2] = str[i2];
		rn->start = rn->end = atoi(str2);
		rn->set[0].p = 0;
	}
	return ALL_GOOD;
}




int scan_randuint8_t(randuint8_t* rn, char* str, char terminator)
{
	char str2[200];
	int ig = 0;
	int i2 = 0;
	int sel_count = 0;
	// the number is range-based random
	if (str[0] == 'r')
	{
		// scanning the lower
		for (ig = 1; str[ig] != '-'; ++ig)
			str2[ig-1] = str[ig];
		str2[ig-1] = '-';
		rn->start = atoi(str2);
		// scanning the higher
		++ig;
		for (i2 = 0; str[ig] != terminator; ++ig, ++i2)
			str2[i2] = str[ig];
		str2[i2] = terminator;
		rn->end = atoi(str2);
	}
	// the number is select-based random
	else if (str[0] == 's')
	{
		for (ig = 1, i2 = 0; sel_count < MAX_RANDNUM_MEMBERS; ++ig, ++i2)
		{
			str2[i2] = str[ig];
			if (str[ig] == '%')
			{
				rn->set[sel_count].i = atoi(str2);
				i2 = -1;
			}
			else if (str[ig] == '|')
			{
				rn->set[sel_count].p = atoi(str2);
				i2 = -1;
				++sel_count;
			}
			else if (str[ig] == terminator)
			{
				rn->set[sel_count].p = atoi(str2);
				break;
			}
		}
	}
	// the number is not random
	else
	{
		for (i2 = 0; str[i2] != terminator; ++i2)
			str2[i2] = str[i2];
		str2[i2] = str[i2];
		rn->start = rn->end = atoi(str2);
		rn->set[0].p = 0;
	}
	return ALL_GOOD;
}




int scan_randdouble(randdouble* rn, char* str, char terminator)
{
	char str2[200];
	int ig = 0;
	int i2 = 0;
	int sel_count = 0;
	// the number is range-based random
	if (str[0] == 'r')
	{
		// scanning the lower
		for (ig = 1; str[ig] != '-'; ++ig)
			str2[ig-1] = str[ig];
		str2[ig-1] = '-';
		rn->start = atof(str2);
		// scanning the higher
		++ig;
		for (i2 = 0; str[ig] != terminator; ++ig, ++i2)
			str2[i2] = str[ig];
		str2[i2] = terminator;
		rn->end = atof(str2);
	}
	// the number is select-based random
	else if (str[0] == 's')
	{
		for (ig = 1, i2 = 0; sel_count < MAX_RANDNUM_MEMBERS; ++ig, ++i2)
		{
			str2[i2] = str[ig];
			if (str[ig] == '%')
			{
				rn->set[sel_count].i = atof(str2);
				i2 = -1;
			}
			else if (str[ig] == '|')
			{
				rn->set[sel_count].p = atoi(str2);
				i2 = -1;
				++sel_count;
			}
			else if (str[ig] == terminator)
			{
				rn->set[sel_count].p = atoi(str2);
				break;
			}
		}
	}
	// the number is not random
	else
	{
		for (i2 = 0; str[i2] != terminator; ++i2)
			str2[i2] = str[i2];
		str2[i2] = str[i2];
		rn->start = rn->end = atof(str2);
		rn->set[0].p = 0;
	}
	return ALL_GOOD;
}




int scan_randfloat(randfloat* rn, char* str, char terminator)
{
	char str2[200];
	int ig = 0;
	int i2 = 0;
	int sel_count = 0;
	// the number is range-based random
	if (str[0] == 'r')
	{
		// scanning the lower
		for (ig = 1; str[ig] != '-'; ++ig)
			str2[ig-1] = str[ig];
		str2[ig-1] = '-';
		rn->start = atof(str2);
		// scanning the higher
		++ig;
		for (i2 = 0; str[ig] != terminator; ++ig, ++i2)
			str2[i2] = str[ig];
		str2[i2] = terminator;
		rn->end = atof(str2);
	}
	// the number is select-based random
	else if (str[0] == 's')
	{
		for (ig = 1, i2 = 0; sel_count < MAX_RANDNUM_MEMBERS; ++ig, ++i2)
		{
			str2[i2] = str[ig];
			if (str[ig] == '%')
			{
				rn->set[sel_count].i = atof(str2);
				i2 = -1;
			}
			else if (str[ig] == '|')
			{
				rn->set[sel_count].p = atoi(str2);
				i2 = -1;
				++sel_count;
			}
			else if (str[ig] == terminator)
			{
				rn->set[sel_count].p = atoi(str2);
				break;
			}
		}
	}
	// the number is not random
	else
	{
		for (i2 = 0; str[i2] != terminator; ++i2)
			str2[i2] = str[i2];
		str2[i2] = str[i2];
		rn->start = rn->end = atof(str2);
		rn->set[0].p = 0;
	}
	return ALL_GOOD;
}
