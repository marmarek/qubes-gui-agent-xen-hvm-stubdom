#ifndef _QUBES_GUI_QEMU_H
#define _QUBES_GUI_QEMU_H
/*
 * The Qubes OS Project, http://www.qubes-os.org
 *
 * Copyright (C) 2012  Marek Marczykowski <marmarek@invisiblethingslab.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

/* header file for qemu in stubdom */

extern uint32_t qubesgui_domid;
int qubesgui_pv_display_init(int log_level);
uint8_t *qubesgui_alloc_surface_data(int width, int height, uint32_t **refs);

#endif /* _QUBES_GUI_QEMU_H */
