/* load.h --- 
 * 
 * Filename: load.h
 * Author: Jules <archjules>
 * Created: Mon Jan  2 18:24:27 2017 (+0100)
 * Last-Updated: Tue Jan  3 00:57:55 2017 (+0100)
 *           By: Jules <archjules>
 */

#ifndef LOAD_H
#define LOAD_H

void rom_load(struct CPU *, char *);
void rom_free(struct CPU *);

#endif /* LOAD_H */
