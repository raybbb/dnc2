
// Copyright (c) 2015-2016 darknetspace developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <QDialog>

namespace Ui {
class NewGroupDialog;
}

namespace WalletGui
{
	class NewGroupDialog : public QDialog
	{
		Q_OBJECT
			Q_DISABLE_COPY(NewGroupDialog)
			
	public:
		NewGroupDialog(QWidget* _parent);
		~NewGroupDialog();
		
		QString getAddress() const;
		QString getLabel() const;
		QString getViewKey() const;
		QString getSpendKey() const;
		
	private:
		QScopedPointer<Ui::NewGroupDialog> m_ui;
	};
}
