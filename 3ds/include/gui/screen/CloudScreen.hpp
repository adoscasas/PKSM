/*
 *   This file is part of PKSM
 *   Copyright (C) 2016-2019 Bernardo Giordano, Admiral Fish, piepie62
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *   Additional Terms 7.b and 7.c of GPLv3 apply to this file:
 *       * Requiring preservation of specified reasonable legal notices or
 *         author attributions in that material or in the Appropriate Legal
 *         Notices displayed by works containing it.
 *       * Prohibiting misrepresentation of the origin of that material,
 *         or requiring that modified versions of such material be marked in
 *         reasonable ways as different from the original version.
 */

#ifndef CLOUDSCREEN_HPP
#define CLOUDSCREEN_HPP

#include "CloudAccess.hpp"
#include "Screen.hpp"
#include <array>

class Button;
class PKFilter;
class PKX;

class CloudScreen : public Screen
{
public:
    CloudScreen(int storageBox, std::shared_ptr<PKFilter> filter = nullptr);

    void update(touchPosition* touch) override;
    void drawTop() const override;
    void drawBottom() const override;

private:
    bool showViewer();
    bool releasePkm();
    bool dumpPkm();
    bool backButton();
    // Have to basically reimplement Hid because two Hids don't go well together
    bool prevBox(bool forceBottom = false);
    bool nextBox(bool forceBottom = false);
    bool prevBoxTop();
    bool nextBoxTop();
    bool clickBottomIndex(int index);
    // Clones from storage (bottom), clones and increments download counter (top), places in storage (bottom), or uploads (top)
    void pickup();

    static bool isValidTransfer(std::shared_ptr<PKX> pkm);

    void shareSend();
    void shareReceive();

    std::array<std::unique_ptr<Button>, 7> mainButtons;
    std::array<std::unique_ptr<Button>, 31> clickButtons;
    std::shared_ptr<PKX> infoMon = nullptr;
    std::shared_ptr<PKX> moveMon;
    CloudAccess access;
    std::shared_ptr<PKFilter> filter;
    int cursorIndex   = 0;
    int storageBox    = 0;
    bool justSwitched = true;
    bool cloudChosen  = false;
    bool saveChosen   = false;
};

#endif
