/* arguments.c --- 
 * 
 * Filename: arguments.c
 * Author: Jules <archjules>
 * Created: Wed Jun 14 17:39:27 2017 (+0200)
 * Last-Updated: Thu Jun 15 01:33:44 2017 (+0200)
 *           By: Jules <archjules>
 */
#include "debug/debug.h"
#include "logger.h"

int read_arg_int_default(char ** tokens, int def) {
    char * s = strtok_r(NULL, " \n", tokens);
    char * end;
    int resultat;
    
    if ((s == NULL) || (*s == 0)) return def;

    if (s[0] == '0') {
	switch (s[1]) {
	case 'x':
	    resultat = strtol(s + 2, &end, 16);
	    break;
	case 'b':
	    resultat = strtol(s + 2, &end, 2);
	    break;
	default:
	    resultat = strtol(s + 2, &end, 8);
	    break;
	}
    } else {
	resultat = strtol(s, &end, 10);
    }

    if (*end != 0) {
	log_debug("Wrong argument");
	return def;
    }

    return resultat;
}
