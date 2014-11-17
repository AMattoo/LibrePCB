/*
 * EDA4U - Professional EDA for everyone!
 * Copyright (C) 2013 Urban Bruhin
 * http://eda4u.ubruhin.ch/
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PROJECT_SES_SELECT_H
#define PROJECT_SES_SELECT_H

/*****************************************************************************************
 *  Includes
 ****************************************************************************************/

#include <QtCore>
#include "schematiceditorstate.h"
#include "../../../common/units.h"

/*****************************************************************************************
 *  Forward Declarations
 ****************************************************************************************/

class UndoCommand;

namespace project {
class CmdSymbolInstanceMove;
}

/*****************************************************************************************
 *  Class SES_Select
 ****************************************************************************************/

namespace project {


/**
 * @brief The SES_Select class
 */
class SES_Select final : public SchematicEditorState
{
        Q_OBJECT

    public:

        // Constructors / Destructor
        explicit SES_Select(SchematicEditor& editor);
        ~SES_Select();

        // General Methods
        State process(SchematicEditorEvent* event) noexcept;
        void entry(State previousState) noexcept;
        void exit(State nextState) noexcept;

    private:

        // Private Methods
        State processSubStateIdle(SchematicEditorEvent* event) noexcept;
        State processSubStateIdleSceneEvent(SchematicEditorEvent* event) noexcept;
        State processSubStateMoving(SchematicEditorEvent* event) noexcept;
        State processSubStateMovingSceneEvent(SchematicEditorEvent* event) noexcept;


        State mPreviousState;

        // Substates
        enum SubState {
            SubState_Idle,
            SubState_Moving
        };
        SubState mSubState;

        Point mMoveStartPos; // not mapped to grid!
        Point mLastMouseMoveDeltaPos; // mapped to grid
        UndoCommand* mParentCommand;
        QList<CmdSymbolInstanceMove*> mSymbolInstanceMoveCommands;
};

} // namespace project

#endif // PROJECT_SES_SELECT_H