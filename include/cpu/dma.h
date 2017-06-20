/* dma.h --- 
 * 
 * Filename: dma.h
 * Author: Jules <archjules>
 * Created: Mon Jan  2 09:22:06 2017 (+0100)
 * Last-Updated: Mon Jun 19 17:08:54 2017 (+0200)
 *           By: Jules <archjules>
 */

#ifndef DMA_H
#define DMA_H

void dma_oam_handle(struct CPU *);
void hblank_dma_handle(struct CPU *);
void general_dma_handle(struct CPU *, uint8_t);
#endif /* DMA_H */
