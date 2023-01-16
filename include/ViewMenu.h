/**
 * @file ViewMenu.h
 * @author Fabian Grubba (grubba.fabiandavidjonah@fh-swf.de)
 * @brief
 * @version 0.1
 * @date 2022-12-21
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef VIEWMENU_H
#define VIEWMENU_H

/**
 * @brief Zeige das Menu an.
 * 
 */
void ViewMenuShow();

/**
 * @brief Nimmt die Tastatur eingaben fuer das Menu entgegen.
 * @param pressedKey
 */
void ViewMenuPressedKeyCall(int pressedKey);

/**
 * @brief Stellt das Menu dar.
 */
void ViewMenuPaintCall();

#endif