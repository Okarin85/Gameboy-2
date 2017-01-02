/* io.h --- 
 * 
 * Filename: io.h
 * Author: Jules <archjules>
 * Created: Sun Dec 11 23:20:25 2016 (+0100)
 * Last-Updated: Sun Dec 11 23:21:06 2016 (+0100)
 *           By: Jules <archjules>
 */

#ifndef IO_H
#define IO_H

uint8_t io_handle_read(struct CPU *, uint8_t port);
void io_handle_write(struct CPU *, uint8_t port, uint8_t value);

#endif /* IO_H */
