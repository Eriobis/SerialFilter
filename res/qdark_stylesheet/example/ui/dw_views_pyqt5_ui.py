# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'dw_views.ui'
#
# Created by: PyQt5 UI code generator 5.10
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_DockWidget(object):
    def setupUi(self, DockWidget):
        DockWidget.setObjectName("DockWidget")
        DockWidget.resize(266, 387)
        self.dockWidgetContents = QtWidgets.QWidget()
        self.dockWidgetContents.setObjectName("dockWidgetContents")
        self.gridLayout = QtWidgets.QGridLayout(self.dockWidgetContents)
        self.gridLayout.setObjectName("gridLayout")
        self.label_70 = QtWidgets.QLabel(self.dockWidgetContents)
        font = QtGui.QFont()
        font.setBold(True)
        font.setWeight(75)
        self.label_70.setFont(font)
        self.label_70.setObjectName("label_70")
        self.gridLayout.addWidget(self.label_70, 0, 1, 1, 1)
        self.label_80 = QtWidgets.QLabel(self.dockWidgetContents)
        font = QtGui.QFont()
        font.setBold(True)
        font.setWeight(75)
        self.label_80.setFont(font)
        self.label_80.setObjectName("label_80")
        self.gridLayout.addWidget(self.label_80, 0, 2, 1, 1)
        self.label_27 = QtWidgets.QLabel(self.dockWidgetContents)
        font = QtGui.QFont()
        font.setBold(True)
        font.setWeight(75)
        self.label_27.setFont(font)
        self.label_27.setObjectName("label_27")
        self.gridLayout.addWidget(self.label_27, 1, 0, 1, 1)
        self.listView = QtWidgets.QListView(self.dockWidgetContents)
        self.listView.setObjectName("listView")
        self.gridLayout.addWidget(self.listView, 1, 1, 1, 1)
        self.listViewDis = QtWidgets.QListView(self.dockWidgetContents)
        self.listViewDis.setEnabled(False)
        self.listViewDis.setObjectName("listViewDis")
        self.gridLayout.addWidget(self.listViewDis, 1, 2, 1, 1)
        self.label_59 = QtWidgets.QLabel(self.dockWidgetContents)
        font = QtGui.QFont()
        font.setBold(True)
        font.setWeight(75)
        self.label_59.setFont(font)
        self.label_59.setObjectName("label_59")
        self.gridLayout.addWidget(self.label_59, 2, 0, 1, 1)
        self.treeView = QtWidgets.QTreeView(self.dockWidgetContents)
        self.treeView.setObjectName("treeView")
        self.gridLayout.addWidget(self.treeView, 2, 1, 1, 1)
        self.treeViewDis = QtWidgets.QTreeView(self.dockWidgetContents)
        self.treeViewDis.setEnabled(False)
        self.treeViewDis.setObjectName("treeViewDis")
        self.gridLayout.addWidget(self.treeViewDis, 2, 2, 1, 1)
        self.label_60 = QtWidgets.QLabel(self.dockWidgetContents)
        font = QtGui.QFont()
        font.setBold(True)
        font.setWeight(75)
        self.label_60.setFont(font)
        self.label_60.setObjectName("label_60")
        self.gridLayout.addWidget(self.label_60, 3, 0, 1, 1)
        self.tableView = QtWidgets.QTableView(self.dockWidgetContents)
        self.tableView.setObjectName("tableView")
        self.gridLayout.addWidget(self.tableView, 3, 1, 1, 1)
        self.tableViewDis = QtWidgets.QTableView(self.dockWidgetContents)
        self.tableViewDis.setEnabled(False)
        self.tableViewDis.setObjectName("tableViewDis")
        self.gridLayout.addWidget(self.tableViewDis, 3, 2, 1, 1)
        self.label_61 = QtWidgets.QLabel(self.dockWidgetContents)
        font = QtGui.QFont()
        font.setBold(True)
        font.setWeight(75)
        self.label_61.setFont(font)
        self.label_61.setObjectName("label_61")
        self.gridLayout.addWidget(self.label_61, 4, 0, 1, 1)
        self.columnView = QtWidgets.QColumnView(self.dockWidgetContents)
        self.columnView.setObjectName("columnView")
        self.gridLayout.addWidget(self.columnView, 4, 1, 1, 1)
        self.columnViewDis = QtWidgets.QColumnView(self.dockWidgetContents)
        self.columnViewDis.setEnabled(False)
        self.columnViewDis.setObjectName("columnViewDis")
        self.gridLayout.addWidget(self.columnViewDis, 4, 2, 1, 1)
        DockWidget.setWidget(self.dockWidgetContents)

        self.retranslateUi(DockWidget)
        QtCore.QMetaObject.connectSlotsByName(DockWidget)

    def retranslateUi(self, DockWidget):
        _translate = QtCore.QCoreApplication.translate
        DockWidget.setWindowTitle(_translate("DockWidget", "Views"))
        self.label_70.setText(_translate("DockWidget", "Enabled"))
        self.label_80.setText(_translate("DockWidget", "Disabled"))
        self.label_27.setText(_translate("DockWidget", "ListView"))
        self.label_59.setText(_translate("DockWidget", "TreeView"))
        self.label_60.setText(_translate("DockWidget", "TableView"))
        self.label_61.setText(_translate("DockWidget", "ColunmView"))

