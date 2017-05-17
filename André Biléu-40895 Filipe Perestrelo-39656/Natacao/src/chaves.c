/*
 * iterador.h
 *
 *  Created on: 17 de Abr de 2013
 *      Author: André
 */


#include <string.h>
#include "chaves.h"

int igualChaves (void * ch1, void * ch2, int tipo){
	switch (tipo){
	case 0:
		if ( *((int*) ch1) == *((int*) ch2))
			return 1;
		return 0;
	case 1:
		if (strcmp ((char*) ch1, (char *)ch2) == 0)
			return 1;
		return 0;
	}
	return 0;
}
