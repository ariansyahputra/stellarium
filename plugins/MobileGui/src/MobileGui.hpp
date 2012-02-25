/*
 * Stellarium
 * Copyright (C) 2008 Fabien Chereau
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
 * Foundation, Inc., 51 Franklin Street, Suite 500, Boston, MA  02110-1335, USA.
 */

#ifndef _MOBILEGUI_HPP_
#define _MOBILEGUI_HPP_

#include "StelGuiBase.hpp"

//! @class MobileGui
//! Main class for the MobileGui, using QML/QDeclarative on top of the QGraphicsView
class MobileGui : public QObject, public StelGuiBase
{
	Q_OBJECT
public:
	MobileGui();
	virtual ~MobileGui();

	virtual void init(QGraphicsWidget* topLevelGraphicsWidget, class StelAppGraphicsWidget* stelAppGraphicsWidget);

	//! Load color scheme matchin the section name.
	virtual void setStelStyle(const QString& section)
	{
		Q_UNUSED(section)
	}

	//! Get a pointer on the info panel used to display selected object info
	virtual void setInfoTextFilters(const StelObject::InfoStringGroup& aflags);
	virtual const StelObject::InfoStringGroup& getInfoTextFilters() const;

	//! Add a new progress bar in the lower right corner of the screen.
	//! When the progress bar is deleted  the layout is automatically rearranged.
	//! @return a pointer to the progress bar.
	virtual class QProgressBar* addProgressBar();

	//! Add a new action managed by the GUI. This method should be used to add new shortcuts to the program
	//! @param actionName qt object name. Used as a reference for later uses
	//! @param text the text to display when hovering, or in the help window
	//! @param shortCut the qt shortcut to use
	//! @param helpGroup hint on how to group the text in the help window
	//! @param checkable whether the action should be checkable
	//! @param autoRepeat whether the action should be autorepeated
	virtual QAction* addGuiActions(const QString& actionName, const QString& text, const QString& shortCut, const QString& helpGroup, bool checkable=true, bool autoRepeat=false);

	virtual void forceRefreshGui();

	//! Get the current visible status of the GUI.
	virtual bool getVisible() const;
	//! Show wether the Gui is currently used.
	//! This can then be used to optimize the rendering to increase reactivity.
	virtual bool isCurrentlyUsed() const;

public slots:
	//! Show whether the GUI is visible.
	//! @param b when true, GUI will be shown, else it will be hidden.
	virtual void setVisible(bool b);


protected:
	class StelAppGraphicsWidget* stelAppGraphicsWidget;
	//! Translate all texts to the new Locale.
	void updateI18n();

private:
	QGraphicsWidget* topLevelGraphicsWidget;
};

//! Allow to load the GUI as a static plugin
class StelMobileGuiPluginInterface : public QObject, public StelGuiPluginInterface
{
	Q_OBJECT
	Q_INTERFACES(StelGuiPluginInterface)
public:
	virtual class StelGuiBase* getStelGuiBase() const;
};

#endif // _STELGUI_HPP_
