/*
 * LibrePCB - Professional EDA for everyone!
 * Copyright (C) 2013 LibrePCB Developers, see AUTHORS.md for contributors.
 * http://librepcb.org/
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

#ifndef LIBREPCB_PROJECT_BES_DRAWTRACE_H
#define LIBREPCB_PROJECT_BES_DRAWTRACE_H

/*****************************************************************************************
 *  Includes
 ****************************************************************************************/
#include <QtCore>
#include <QtWidgets>
#include "bes_base.h"

/*****************************************************************************************
 *  Namespace / Forward Declarations
 ****************************************************************************************/
namespace PNS {
class ROUTER;
class PNS_LIBREPCB_IFACE;
class ITEM;
class MEANDER_PLACER_BASE;
} // namespace PNS

namespace librepcb {
namespace project {

class BI_NetPoint;
class BI_NetLine;

namespace editor {

/*****************************************************************************************
 *  Class BES_DrawTrace
 ****************************************************************************************/

/**
 * @brief The BES_DrawTrace class
 *
 * @todo This class is incredible ugly and buggy :-D
 */
class BES_DrawTrace final : public BES_Base
{
        Q_OBJECT

    public:

        // Constructors / Destructor
        explicit BES_DrawTrace(BoardEditor& editor, Ui::BoardEditor& editorUi,
                               GraphicsView& editorGraphicsView, UndoStack& undoStack);
        ~BES_DrawTrace();

        // General Methods
        ProcRetVal process(BEE_Base* event) noexcept override;
        bool entry(BEE_Base* event) noexcept override;
        bool exit(BEE_Base* event) noexcept override;

    private:

        // Private Types

        /// Internal FSM States (substates)
        enum SubState {
            SubState_Idle,                  ///< idle state [initial state]
            SubState_PositioningNetPoint    ///< in this state, an undo command is active!
        };


        // Private Methods
        ProcRetVal processSubStateIdle(BEE_Base* event) noexcept;
        ProcRetVal processSubStatePositioning(BEE_Base* event) noexcept;
        ProcRetVal processIdleSceneEvent(BEE_Base* event) noexcept;
        ProcRetVal processPositioningSceneEvent(BEE_Base* event) noexcept;
        bool startPositioning(Board& board, const Point& pos,
                              BI_NetPoint* fixedPoint = nullptr) noexcept;
        bool abortPositioning(bool showErrMsgBox) noexcept;
        void layerComboBoxIndexChanged(int index) noexcept;
        void wireWidthComboBoxTextChanged(const QString& width) noexcept;


        // General Attributes
        SubState mSubState; ///< the current substate
        QString mCurrentLayerName; ///< the current board layer name
        PositiveLength mCurrentWidth; ///< the current wire width

        PNS::ROUTER *router = nullptr;
        PNS::PNS_LIBREPCB_IFACE *iface = nullptr;
        PNS::MEANDER_PLACER_BASE *meander_placer = nullptr;
        bool shove = false;

        // Widgets for the command toolbar
        QList<QAction*> mActionSeparators;
        QLabel* mLayerLabel;
        QComboBox* mLayerComboBox;
        QLabel* mWidthLabel;
        QComboBox* mWidthComboBox;
};

/*****************************************************************************************
 *  End of File
 ****************************************************************************************/

} // namespace editor
} // namespace project
} // namespace librepcb

#endif // LIBREPCB_PROJECT_BES_DRAWTRACE_H
